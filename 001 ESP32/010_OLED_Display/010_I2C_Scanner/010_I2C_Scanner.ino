#include <Wire.h>

void setup() 
{
  Wire.begin(21, 22);  // SDA, SCL (default ESP32 pins)
  Serial.begin(115200);
  Serial.println("Scanning for I2C devices...");
}

void loop() 
{
  for (byte address = 1; address < 127; address++) 
  {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) 
	{
      Serial.print("I2C device found at: 0x");
      Serial.println(address, HEX);
    }
  }

  Serial.println("Scan complete.");
  while(1);
  delay(3000);
}
