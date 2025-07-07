#include <Arduino.h>
#include <webClient.h>
#include <scale.h>
#include <Wireless.h>

int commandDelay = 1000;
int commandDelayNr = 0;

int putDataDelay = 100;
int putDataDelayNr = 0;

void setup()
{
  Serial.begin(115200);
  delay(1000);
  createwifi();
  InitScale();
  // webClientInit();
}

void loop()
{
  updateScale();
  

if(putDataDelay=putDataDelayNr)
  {
    putData();
    putDataDelayNr=0;
  }
  else
  {
    putDataDelayNr+=1;
  }


  if(commandDelay=commandDelayNr)
  {
    getCommand();
    commandDelayNr=0;
  }
  else
  {
    commandDelayNr+=1;
  }
  vTaskDelay(pdMS_TO_TICKS(5));
  
}
