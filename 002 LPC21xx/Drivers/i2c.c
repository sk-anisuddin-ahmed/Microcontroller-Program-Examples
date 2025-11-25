#include <LPC213x.h>
#include <i2c.h>

void I2C_INIT(void) 
{
    // Configure pins

    I2C0CONCLR = 0x6C;   // clear AA, SI, STA, I2EN

    // Set clock for ~100 kHz
    I2C0SCLH = 300;      // high period
    I2C0SCLL = 300;      // low period

    // Enable I2C
    I2C0CONSET = I2C0_ENABLE;
}

void I2C_START(void) 
{
    I2C0CONSET = I2C0_START;          // request START
    while (!(I2C0CONSET & I2C0_INT_FLAG)); // wait for SI=1
    if (I2C0STAT != 0x08) return;     // START transmitted
}

void I2C_STOP(void) 
{
    I2C0CONSET = I2C0_STOP;           // request STOP
    I2C0CONCLR = I2C0_INT_FLAG;       // clear SI
}

void I2C_WRITE(unsigned char data) 
{
    I2C0DAT = data;                   // load data
    I2C0CONCLR = I2C0_START;          // clear START
    I2C0CONCLR = I2C0_INT_FLAG;       // clear SI
    while (!(I2C0CONSET & I2C0_INT_FLAG)); // wait for SI=1
}

void I2C_SEND_ADDR_DATA (unsigned char slaveAddr, unsigned char data) 
{
    i2c0_start();                     // START condition

    i2c0_write(slaveAddr<<1);         // SLA+W
    if (I2C0STAT != 0x18) return;     // SLA+W ACK

    i2c0_write(data);                 // send data
    if (I2C0STAT != 0x28) return;     // data ACK

    i2c0_stop();                      // STOP condition
}