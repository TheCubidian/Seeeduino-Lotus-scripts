const int lgtPin = A6;

void setup()
{
  pinMode(lgtPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(lgtPin)); //Max value is 823
}