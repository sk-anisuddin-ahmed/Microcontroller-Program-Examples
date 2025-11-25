#include <WiFi.h>
#include <WebServer.h>

WebServer server(80);

const int LED_PIN = 2;
bool ledState = false;

void handleRoot()
{
  String page;

  page += "<h1>ESP32 LED Control Panel</h1>";
  page += "<p><b>Current LED State: ";
  page += (ledState ? "ON" : "OFF");
  page += "</b></p>";

  page += "<p><a href=\"/on\"><button>LED ON</button></a></p>";
  page += "<p><a href=\"/off\"><button>LED OFF</button></a></p>";

  server.send(200, "text/html", page);
}

void handleLedOn()
{
  digitalWrite(LED_PIN, HIGH);
  ledState = true;

  // Redirect to root, show updated LED state
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void handleLedOff()
{
  digitalWrite(LED_PIN, LOW);
  ledState = false;

  // Redirect to root, show updated LED state
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "");
}

void onClientConnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Device Connected!");
}

void onClientDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  Serial.println("Device Disconnected!");
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.onEvent(onClientConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STACONNECTED);
  WiFi.onEvent(onClientDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);

  bool ap_status = WiFi.softAP("ESP32-Anis", "ANISUDDIN");

  if (ap_status)
      Serial.println("Hotspot created successfully!");
  else
  {
      Serial.println("Hotspot creation FAILED!");
      return;
  }

  server.on("/", handleRoot);
  server.on("/on", handleLedOn);
  server.on("/off", handleLedOff);

  server.begin();
  Serial.println("Server started!");

  Serial.print("Local Server Address: http://");
  Serial.println(WiFi.softAPIP());
}

void loop()
{
  server.handleClient();
}