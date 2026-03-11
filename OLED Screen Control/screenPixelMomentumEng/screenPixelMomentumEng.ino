#include <U8g2lib.h>
#include <Wire.h>
#include <Arduino.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, U8X8_PIN_NONE, A5, A4);
auto& g = u8g2;

const int btnPin = 6, potPin = 0;
int x = 64, y = 32, xMomentum = 0, yMomentum = 0, btnPressed, cardinalDir;
bool xMoved = false, yMoved = false;

/*
void drawArrow() Should be an 8x8 sprite
{
  g.drawHLine(x - 9, y - 7, 5);
  g.drawHLine(x - 9, y + 7, 5);
  g.drawLine(x - 9, y - 7, x - 5, y);
  g.drawLine(x - 9, y + 7, x - 5, y);
  g.drawLine(x - 4, y - 7, x, y);
  g.drawLine(x - 4, y + 7, x, y);
}
*/

void setup()
{
  u8g2.begin();
  pinMode(btnPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
  g.drawPixel(x, y);
  g.sendBuffer();
}

void loop()
{
  cardinalDir = map(analogRead(potPin), 1023, 0, 0, 3); //North -> 0 ... West -> 3 (Clockwise turn of potmeter increases value)
  btnPressed = digitalRead(btnPin);
  if (btnPressed) 
  {
    if (xMomentum != 20 && cardinalDir == 1)
    {  
      xMomentum++;
      xMoved = true;
    }
    else if (xMomentum != -20 && cardinalDir == 3)
    {
      xMomentum--;
      xMoved = true;
    }
    else if (cardinalDir != 1 && cardinalDir != 3)
    {
      xMoved = false;
    }
    if (yMomentum != -20 && cardinalDir == 0)
    {  
      yMomentum--;
      yMoved = true;
    }
    else if (yMomentum != 20 && cardinalDir == 2)
    {
      yMomentum++;
      yMoved = true;
    }
    else if (cardinalDir != 0 && cardinalDir != 2)
    {
      yMoved = false;
    }
  }
  else
  {
    xMoved = false;
    yMoved = false;
  }

  if (xMomentum > 0 && !xMoved)
  {
    xMomentum--;
  }
  else if (xMomentum < 0 && !xMoved)
  {
    xMomentum++;
  }
  if (yMomentum > 0 && !yMoved)
  {
    yMomentum--;
  }
  else if (yMomentum < 0 && !yMoved)
  {
    yMomentum++;
  }

  if (xMomentum != 0 || yMomentum != 0)
  {
    g.setDrawColor(0);
    g.drawPixel(x, y);
    g.setDrawColor(1);
    if (xMomentum > 0)
    {
      if (x < 127)
      {
        x++;
      }
      else
      {
        x = 0;
      }
    }
    else if (xMomentum < 0)
    {
      if (x > 0)
      {
      x--;
      }
      else
      {
        x = 127;
      }
    }

    if (yMomentum > 0)
    {
      if (y < 63)
      {
        y++;
      }
      else
      {
        y = 0;
      }
    }
    else if (yMomentum < 0)
    {
      if (y > 0)
      {
        y--;
      }
      else
      {
        y = 63;
      }
    }    
    g.drawPixel(x, y);
    if (xMomentum == 0)
    {
      delay(210 / abs(yMomentum));
    }
    else if (yMomentum == 0)
    {
      delay(210 / abs(xMomentum));
    }
    else
    {
      delay(420 / (abs(xMomentum) + abs(yMomentum)));
    }
    g.sendBuffer();
  }
}