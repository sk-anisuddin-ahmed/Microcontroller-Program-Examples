#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ANISUDDIN";
const char* password = "ANISUDDIN";

String apiKey = "R9KR4Y7SSNCMP788";
String channelID = "3162580";

float tempValue = 26.0;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected!");
}

void loop()
{
  tempValue = random(250, 270) / 10.0;

  Serial.print("Simulated Temp: ");
  Serial.println(tempValue);

  // Upload to ThingSpeak
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + apiKey +
                 "&field1=" + String(tempValue);

    http.begin(url);
    int httpCode = http.GET();
    http.end();

    Serial.print("ThingSpeak Response: ");
    Serial.println(httpCode);
  }

  // ThingSpeak limit: 15–20 seconds minimum
  delay(1000);
}