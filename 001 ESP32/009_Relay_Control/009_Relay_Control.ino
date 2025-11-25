#define relayPin 15

void setup() 
{
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);   // relay OFF
  
  Serial.println("Relay Control Ready");
}

void loop()
{
  Serial.println("Lamp ON");
  digitalWrite(relayPin, LOW);    // Relay ON -> Lamp ON
  delay(3000);

  Serial.println("Lamp OFF");
  digitalWrite(relayPin, HIGH);   // Relay OFF -> Lamp OFF
  delay(3000);
}
