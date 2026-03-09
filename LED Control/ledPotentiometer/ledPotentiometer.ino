int ledPin = 4, potPin = 0, serialCounter = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop()
{
  int potValue = analogRead(potPin);
  Serial.println(potValue);

  serialCounter += 1;
  if (serialCounter == 200)
  {
    Serial.print("The LED is ON:OFF in the ratio ");
    Serial.print(potValue);
    Serial.print(":");
    Serial.println(1023 - potValue);
    serialCounter = 0;
  }

  digitalWrite(ledPin, 1);
  delayMicroseconds(1023 - potValue);
  digitalWrite(ledPin, 0);
  delayMicroseconds(potValue);
}