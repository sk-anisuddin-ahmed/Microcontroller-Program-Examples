#include <WiFi.h>

const char* ssid = "ANISUDDIN";
const char* password = "ANISUDDIN";

void setup() 
{
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() 
{

}