#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

float tempValue = 26.0;
unsigned long lastUpdate = 0;

void setup() 
{
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
    Serial.println("OLED NOT FOUND!");
    return;
  }

  display.clearDisplay();
  display.display();
}

void loop() 
{
  if (millis() - lastUpdate >= 1000) 
  {
    lastUpdate = millis();

    tempValue = random(250, 270) / 10.0;

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Temp:");
    display.print(tempValue);
    display.println(" C");
    display.display();
  }
}
