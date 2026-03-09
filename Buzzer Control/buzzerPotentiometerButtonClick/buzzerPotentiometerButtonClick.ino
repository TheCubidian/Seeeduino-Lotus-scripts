const int buzPin = 5, potPin = 0, btnPin = 6;
bool deviceOff = true;

/*
void offRequested()
{
  static int lastBtn;
  static bool btnPressed = false;
  if (digitalRead(btnPin) == 1 && !btnPressed)
  {
    lastBtn = millis();
    btnPressed = true;
  }
  else
  {
    btnPressed = false;
  }

  if ((millis() - lastBtn) >= 1000 && btnPressed)
  {
    deviceOff = true;
    btnPressed = false;
  }
}
*/

void setup()
{
  pinMode(buzPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(btnPin, INPUT);
}

void loop()
{
  static bool modeFlag = false, cycledBtnPress = 0;
  if (cycledBtnPress == 0)
    {
      cycledBtnPress = digitalRead(btnPin);
    }
  if (!deviceOff)
  {
    //offRequested(); doesn't work yet
    modeFlag = !modeFlag;

    if (modeFlag)
    {
      tone(buzPin, map(analogRead(potPin), 0, 1023, 2600, 2000), 100);
    }
    else
    {
      digitalWrite(buzPin, 1);
      delay(1);
      digitalWrite(buzPin, 0);
      delay(map(analogRead(potPin), 0, 1023, 20, 800));
    }
  }
  else if (cycledBtnPress)  
  {
    deviceOff = false;
  }
}