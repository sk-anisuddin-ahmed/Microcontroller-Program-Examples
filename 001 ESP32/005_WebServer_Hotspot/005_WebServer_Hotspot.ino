#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

void handleRoot() 
{
  server.send(200, "text/html", "<h1>Hello India</h1>");
}

void onClientConnected(WiFiEvent_t event, WiFiEventInfo_t info) 
{
  Serial.println("Device Connected!");
  if (info.wifi_ap_staconnected.aid) 
  {
    Serial.print("Client ID: ");
    Serial.println(info.wifi_ap_staconnected.aid);
  }
}

void onClientDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) 
{
  Serial.println("Device Disonnected!");
  if (info.wifi_ap_stadisconnected.aid)
  {
    Serial.println(info.wifi_ap_stadisconnected.aid);
  }
}

void setup() 
{
  Serial.begin(115200);

  WiFi.onEvent(onClientConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STACONNECTED);
  WiFi.onEvent(onClientDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);
  
  bool ap_status = WiFi.softAP("ESP32-Anis", "ANISUDDIN");

  if (ap_status) 
  {
      Serial.println("Hotspot created successfully!");
  } 
  else 
  {
      Serial.println("Hotspot creation FAILED!");
      return;
  }

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Server started!");

  Serial.print("Local Server Address: http://");
  Serial.println(WiFi.softAPIP());
}

void loop() 
{
  server.handleClient();
}