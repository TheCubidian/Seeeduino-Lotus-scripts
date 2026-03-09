const int sndPin = 2;

void setup()
{
  pinMode(sndPin, INPUT);
  Serial.begin(300);
}

void loop()
{
  Serial.println(analogRead(sndPin)); //Max value is 818
}
