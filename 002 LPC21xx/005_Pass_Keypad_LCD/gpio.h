void GPIO_INIT(void);

void LED_ON(void);
void LED_OFF(void);

// Define row pins (outputs)
#define ROWA (1 << 3)   // P0.3
#define ROWB (1 << 4)   // P0.4
#define ROWC (1 << 5)   // P0.5
#define ROWD (1 << 6)   // P0.6

// Define column pins (inputs)
#define COL1 (1 << 2)   // P0.2
#define COL2 (1 << 1)   // P0.1
#define COL3 (1 << 0)   // P0.0

void KEYPAD_INIT(void);
