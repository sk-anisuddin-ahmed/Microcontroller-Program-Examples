#define I2C0_INT_FLAG   (1<<3)
#define I2C0_ENABLE     (1<<6)
#define I2C0_START      (1<<5)
#define I2C0_STOP       (1<<4)

// Slave address (7-bit)
#define SLAVE_ADDR  0x50

void I2C_INIT(void);
void I2C_START(void);
void I2C_STOP(void);
void I2C_WRITE(unsigned char);
void I2C_SEND_ADDR_DATA (unsigned char, unsigned char);