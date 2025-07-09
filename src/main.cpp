#include <Arduino.h>
#include <webClient.h>
#include <scale.h>
#include <Wireless.h>

int commandDelay = 1000;
int commandNext = 0;

int putDataDelay = 300;
int putDataNext = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println(ESP.getEfuseMac());
  createwifi();
  InitScale();
  commandNext = millis() + commandDelay;
  putDataNext = millis() + putDataDelay;
}

void loop()
{
  updateScale();
  int now = millis();

  if (now >= putDataNext)
  {
    putData();
    putDataNext = millis() + putDataDelay;
  }

  if (now >= commandNext)
  {
    getCommand();
    commandNext = millis() + commandDelay;
    ;
  }
}
