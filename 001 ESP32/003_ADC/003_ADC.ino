void setup() 
{
  Serial.begin(115200);
  pinMode(32, INPUT);
  analogSetPinAttenuation(32, ADC_11db);  // enable 0–3.3V range
}

void loop() 
{
  int raw = analogRead(32);
  float voltage = (3.3 / 4096.0) * raw;

  Serial.printf("ADC Raw = %d\n", raw);
  Serial.printf("ADC Voltage = %.3f V\n", voltage);

  delay(100);
}
