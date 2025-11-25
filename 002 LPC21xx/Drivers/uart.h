#define CLOCK_FREQ	60000000.0
#define UART_BAUD_RATE(x) (CLOCK_FREQ / (16.0 * x))

void UART_INIT (void);
void sendChar(uint8_t);