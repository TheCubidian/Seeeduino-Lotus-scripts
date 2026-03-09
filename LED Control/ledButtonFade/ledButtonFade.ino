int ledPin = 4, btnPin = 6, flag = 0, index = 0, tempBuff;
char serBuff[3] = {0};
bool flashing;

void ledFade(bool fadeIn)
{
  int delayOn, delayOff;
  for (int fadeCycle = 1; fadeCycle < 21; fadeCycle++)
  {
    if (fadeIn)
    {
      delayOn = fadeCycle;
      delayOff = 20 - fadeCycle;
    }
    else
    {
      delayOn = 20 - fadeCycle;
      delayOff = fadeCycle;          
    }
    digitalWrite(ledPin, 1);
    delay(delayOn);
    digitalWrite(ledPin, 0);
    delay(delayOff);
  }
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT);
  Serial.begin(9600);

  Serial.println("Would you like to have the LED flash when the button is held down, or just stay on? [1/2]");
  while (true)
  {

    for (int x = 0; x < 2; x++)
    {
      while (Serial.available() == 0) {}
      tempBuff = Serial.read();
      if (x == 0 && (tempBuff == '\n' || tempBuff == '\r'))
      {
        break;
      }
      else if (tempBuff != -1)
      {
        tempBuff = (char)tempBuff;
        serBuff[x] = tempBuff;
      }
    }
    while (!(tempBuff == '\n' || tempBuff == '\r'))
    {
      tempBuff = Serial.read();
    }
    if (serBuff[0] == '1' && (serBuff[1] == '\n' || serBuff[1] == '\r'))
    {
      flag = 1;
      break;
    }
    else if (serBuff[0] == '2' && (serBuff[1] == '\n' || serBuff[1] == '\r'))
    {
      flag = 2;
      break;
    }
    else
    {
      Serial.println("Invalid input. Try again.");
    }
  }
  flashing = (flag == 1);
  Serial.print("The LED will ");
  if (!flashing)
  {
    Serial.print("not ");
  }
  Serial.println("flash.");
}

void loop()
{
  if (digitalRead(btnPin) == 1)
  {
    ledFade(true);
    if (!flashing)
    {
      while (digitalRead(btnPin) == 1)
      {
        digitalWrite(ledPin, 1);
      }
    }

    ledFade(false);
  }
}