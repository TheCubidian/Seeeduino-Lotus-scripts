#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, SCL, SDA, U8X8_PIN_NONE);
auto& g = u8g2;
const int potPin = 0, btnPin = 4;
int x = 0, y = 0, tileSize, lastTileSize;
bool offset = false, invertScreen = false;

void drawCheckerboard()
{
  g.setDrawColor(1);
  for (y; y < 64; y += tileSize)
  {
    if (offset)
    {
      x+= tileSize;
      offset = false;
    }
    else
    {
      offset = true;
    }

    for (x; x < 128; x += 2 * tileSize)
    {
      g.drawBox(x, y, tileSize, tileSize);
    }
    x = 0;
  }
  y = 0;
}

void setTileSize()
{
  lastTileSize = tileSize;
  tileSize = map(analogRead(potPin), 1023, 0, 1, 10);
  static int lastTileSize = tileSize;
}

void setup()
{
  pinMode(potPin, INPUT);
  pinMode(btnPin, INPUT);
  g.begin();
  setTileSize();
  drawCheckerboard();
}

void loop()
{
  setTileSize();
  invertScreen = analogRead(btnPin);
  if (tileSize != lastTileSize || invertScreen)
  {
    g.clearBuffer();
    drawCheckerboard();
    if (invertScreen)
      {
      g.setDrawColor(2);
      g.drawBox(0, 0, 128, 64);
      invertScreen = false;
      }
    g.sendBuffer();  
  }
}
