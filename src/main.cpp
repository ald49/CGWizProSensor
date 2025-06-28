#include <Arduino.h>
#include <webClient.h>
#include <scale.h>
#include <Wireless.h>


void setup()
{
  Serial.begin(115200);
  delay(1000);
  createwifi();
  InitScale();
  webClientInit();

  
}

void loop()
{
  updateScale();
   postdata();
}
