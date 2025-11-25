#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ANISUDDIN";
const char* password = "ANISUDDIN";

WebServer server(80);

void handleRoot() 
{
  server.send(200, "text/html", "<h1>Hello India</h1>");
}

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

  server.on("/", handleRoot);
  server.begin();

  Serial.print("Local Server Address: http://");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  server.handleClient();
}