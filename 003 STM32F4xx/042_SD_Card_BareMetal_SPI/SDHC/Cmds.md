# SD Card SPI Mode Essential Commands with Wait Instructions

CMD0 (GO_IDLE_STATE)
Send: 0x40 00 00 00 00 95
CRC: 0x95 (fixed)
Wait: Send 0xFF repeatedly until R1 response != 0xFF
Check: Expect R1 = 0x01 (Idle)
Purpose: Reset card, enter SPI mode

---

CMD8 (SEND_IF_COND)
Send: 0x48 00 00 01 AA 87
CRC: 0x87 (fixed)
Wait: Send 0xFF until R1 response != 0xFF
Check: R1 should be 0x01 (Idle)
Then: Continue clocking 4 more bytes (send 0xFF) → get echo pattern (0x000001AA)
Purpose: Voltage check & SDHC/SDXC support

---

CMD55 (APP_CMD)
Send: 0x77 00 00 00 00 65
CRC: 0x65 (fixed)
Wait: Send 0xFF until R1 response != 0xFF
Check: R1 = 0x01 (Idle) or 0x00 (Ready)
Purpose: Prefix for application commands

---

ACMD41 (SD_SEND_OP_COND)
Send: CMD55 first, then CMD41
CMD41: 0x69 40 00 00 00 77
CRC: 0x77 (fixed)
Wait: Send 0xFF until R1 response != 0xFF
Check: Loop until R1 = 0x00 (Ready)
Purpose: Initialize card, exit idle

---

CMD58 (READ_OCR)
Send: 0x7A 00 00 00 00 FD
CRC: 0xFD (fixed)
Wait: Send 0xFF until R1 response != 0xFF
Check: R1 = 0x00 (Ready)
Then: Continue clocking 4 more bytes (send 0xFF) → OCR register
Purpose: Read operating conditions register

---

CMD16 (SET_BLOCKLEN)
Send: 0x50 00 00 02 00 FF
CRC: 0xFF (dummy, ignored after init)
Wait: Send 0xFF until R1 response != 0xFF
Check: R1 = 0x00 (Ready)
Purpose: Set block length (usually 512 bytes)

---

CMD17 (READ_SINGLE_BLOCK)
Send: 0x51 [block addr] CRC=0xFF
Wait: Send 0xFF until R1 response != 0xFF
Check: R1 = 0x00 (Ready)
Then: Keep sending 0xFF until Data Token 0xFE
Then: Read 512 bytes data + 2‑byte CRC
Purpose: Read one block

---

CMD24 (WRITE_BLOCK)
Send: 0x58 [block addr] CRC=0xFF
Wait: Send 0xFF until R1 response != 0xFF
Check: R1 = 0x00 (Ready)
Then: Send Data Token 0xFE
Then: Send 512 bytes data + 2‑byte CRC
Then: Read Data Response (expect 0x05 = Accepted)
Then: Keep sending 0xFF until card releases busy (MISO returns 0xFF)
Purpose: Write one block

---

# Response Types
R1 = 1‑byte status (Idle, Erase Reset, Illegal Command, CRC Error, etc.)
R3 = R1 + 4‑byte OCR register
R7 = R1 + 4‑byte echo pattern

# Typical Initialization Sequence
1. Power up card
2. Send ≥74 clock pulses with CS=High, MOSI=High
3. CMD0 → wait for R1=0x01
4. CMD8 → wait for R7 (R1 + 4 bytes)
5. Loop CMD55 + ACMD41 until R1=0x00
6. CMD58 → wait for R3 (R1 + 4 bytes OCR)
7. CMD16 → wait for R1=0x00
8. Ready for CMD17/CMD24


# CMD58 (READ_OCR) – Decoding the OCR Register

Send: 0x7A 00 00 00 00 FD
CRC: 0xFD (fixed)

Wait:
- After sending, keep clocking 0xFF until R1 response != 0xFF
- Expect R1 = 0x00 (Ready)

Then:
- Continue clocking 4 more bytes (send 0xFF) → OCR register (32 bits)

OCR Register Format (bit positions):

Bit 31 : Card power up status (busy flag)
         0 = Card still powering up
         1 = Card ready

Bit 30 : Card Capacity Status (CCS)
         0 = Standard Capacity (SDSC)
         1 = High Capacity (SDHC/SDXC)

Bit 29 : Reserved

Bits 28–15 : Voltage window (VDD voltage range)
             Each bit corresponds to 0.1V step from 2.7V to 3.6V
             Example: Bit 20 set → supports 3.2–3.3V

Bits 14–8 : Reserved

Bit 7 : Reserved for low voltage

Bits 6–0 : Reserved

---

# Example OCR Value
Suppose OCR = 0xC0FF8000

Binary: 1100 0000 1111 1111 1000 0000 0000 0000

Interpretation:
- Bit 31 = 1 → Card powered up
- Bit 30 = 1 → High Capacity (SDHC/SDXC)
- Voltage window bits (28–15) show supported range (e.g. 2.7–3.6V)
- Other bits reserved

---

# Usage in Initialization
1. After ACMD41 returns R1=0x00, send CMD58.
2. Read OCR:
   - Check Bit 31 → must be 1 (card ready).
   - Check Bit 30 → tells if card is SDHC/SDXC (block addressing).
   - Check voltage bits → confirm card supports host voltage.
3. If CCS=1 → use block addressing (no CMD16 needed).
   If CCS=0 → use byte addressing (CMD16 to set 512‑byte block length).


# CMD16 (SET_BLOCKLEN)

Send: 0x50 00 00 [blocklen_hi] [blocklen_lo] CRC=0xFF
Example for 512 bytes: 0x50 00 00 02 00 FF

CRC: 0xFF (dummy, ignored after init)

Wait:
- After sending, keep clocking 0xFF until R1 response != 0xFF
- Expect R1 = 0x00 (Ready)

Purpose:
- Set the block length for subsequent read/write commands.

---

# When to Choose Block Length

1. **Standard Capacity SD (SDSC, ≤2GB)**
   - CMD16 is required.
   - You can set block length to any power‑of‑2 value up to 2048 bytes.
   - Common choice: 512 bytes (industry standard, matches filesystem sector size).
   - Example: CMD16 with argument 0x0200 → block length = 512 bytes.

2. **High Capacity SD (SDHC, 2–32GB) and SDXC (≥32GB)**
   - CMD16 is **ignored**.
   - Block length is fixed at 512 bytes.
   - Always use 512‑byte blocks for CMD17 (read) and CMD24 (write).
   - CMD16 will return R1=0x00 but has no effect.

3. **MMC Cards (older standard)**
   - CMD16 is used to set block length.
   - Values can vary depending on card spec.
   - Still, 512 bytes is the most compatible choice.

---

# Practical Notes
- Filesystems (FAT16/FAT32/exFAT) assume 512‑byte sectors → always use 512 for compatibility.
- Even if SDSC supports larger blocks, most host drivers stick to 512.
- For SDHC/SDXC, you must not attempt other values; card will reject or ignore.
- After CMD16, all subsequent CMD17/CMD24 operations use the chosen block length (if SDSC).

---

# Typical Usage in Initialization
- After CMD58 (READ_OCR):
  - If CCS=0 (SDSC) → send CMD16 with 512 bytes.
  - If CCS=1 (SDHC/SDXC) → skip CMD16, block length fixed at 512.
