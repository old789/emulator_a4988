define LED_BUILTIN 8

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, digitalRead(LED_BUILTIN) ^ HIGH);
  delay(2000);
}