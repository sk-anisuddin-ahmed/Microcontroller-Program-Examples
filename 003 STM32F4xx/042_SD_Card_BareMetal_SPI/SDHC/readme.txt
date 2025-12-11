/**********************************************************/
Message appended
Reading file: /hello.txt
Read from file: Hello World!
Deleting file: /foo.txt
File deleted
Renaming file /hello.txt to /foo.txt
File renamed
Reading file: /foo.txt
Read from file: Hello World!
1048576 bytes read for 2384 ms
1048576 bytes written for 2706 ms
Total space: 7572MB
Used space: 1MB

/**********************************************************/
SD Card Initialization Sequence
CMD0 – GO_IDLE_STATE
Code
CMD0 packet: 0x40 0x00 0x00 0x00 0x00 0x95
Response: 0x01 (card entered idle state)
→ Reset card, put into idle mode.

CMD59 – CRC_ON_OFF
Code
CMD59 packet: 0x7B 0x00 0x00 0x00 0x01 0x83
Response: 0x01
→ Enable CRC checking (optional, often used during init).

CMD8 – SEND_IF_COND
Code
CMD8 packet: 0x48 0x00 0x00 0x01 0xAA 0x87
Response: 0x000001AA
→ Voltage check (2.7–3.6 V) and pattern check. Confirms card supports SD2.0.

CMD58 – READ_OCR
Code
CMD58 packet: 0x7A 0x00 0x00 0x00 0x00 0xFD
Response: 0x40FF8000
→ Read operating conditions register (OCR). Shows voltage range and card type bits.

CMD55 + ACMD41 – APP_SEND_OP_COND
Code
CMD55 packet: 0x77 ...
CMD41 packet: 0x69 0x40 0x10 0x00 0x00 0xCD
Response: 0x01 → still initializing
Response: 0x00 → card ready
→ Loop until card leaves idle. This is the critical init handshake.

CMD58 – Final READ_OCR
Code
Response: 0xC0FF8000
→ Confirms card is SDHC/SDXC (bit 30 set).

CMD42 – APP_CLR_CARD_DETECT
Code
CMD42 packet: 0x6A ...
Response: 0x00
→ Clears card detect function (optional housekeeping).

CMD9 – SEND_CSD
Code
CMD9 packet: 0x49 ...
Response: data block (16 bytes)
→ Reads CSD register (card specific data). Used to calculate capacity.

CMD17 – READ_SINGLE_BLOCK
Code
CMD17 packet: 0x51 ...
Response: 0xFE (data token)
Reading 512 data bytes
→ Test read of sector(s). Confirms block length and data transfer.