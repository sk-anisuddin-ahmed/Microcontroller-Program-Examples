#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Standard Bluetooth SIG UUIDs
#define SERVICE_UUID        "1809"
#define CHARACTERISTIC_UUID "2A6E"

BLEServer* pServer = NULL;
BLECharacteristic* pTempCharacteristic = NULL;

bool deviceConnected = false;
int tempValue = 26;
unsigned long previous;

class ServerCallbacks : public BLEServerCallbacks 
{
  void onConnect(BLEServer* pServer) 
  {
    deviceConnected = true;
    Serial.println("Device Connected!");
  }

  void onDisconnect(BLEServer* pServer) 
  {
    deviceConnected = false;
    Serial.println("Device Disconnected!");
    pServer->getAdvertising()->start();
  }
};

void setup() 
{
  Serial.begin(115200);

  // Initialize BLE
  BLEDevice::init("ESP32-Thermometer");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  pTempCharacteristic = pService->createCharacteristic(
                          CHARACTERISTIC_UUID,
                          BLECharacteristic::PROPERTY_READ   |
                          BLECharacteristic::PROPERTY_NOTIFY
                        );

  pTempCharacteristic->addDescriptor(new BLE2902());
  pService->start();

  // Start advertising
  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  BLEDevice::startAdvertising();

  Serial.println("BLE Temperature Service Started");
}

void loop() 
{
  tempValue = random(2500, 2700);

  if (deviceConnected) 
  {
    pTempCharacteristic->setValue((uint8_t*)&tempValue, sizeof(tempValue));
    pTempCharacteristic->notify();
  }
  else
  {
    unsigned long now = millis();
    if (now - previous >= 2500)
    {
      previous = now;
      Serial.print("Temperature: ");
      Serial.println(tempValue);
      Serial.println("No Device Connected!");
    }
  }

  delay(2000);
}
