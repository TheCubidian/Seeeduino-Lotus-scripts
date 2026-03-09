int ledPin = 4;
void setup()
{
  pinMode(ledPin, OUTPUT);
}

void loop()
{
  digitalWrite(ledPin, 1);
  delay(1);
  digitalWrite(ledPin, 0);
  delay(1);
}