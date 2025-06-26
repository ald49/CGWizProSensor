#include <Arduino.h>

#include <scale.h>
#include <netMeshClient.h>


void setup()
{
  Serial.begin(115200);
  InitScale();
setupNetMeshClient();
  
}

void loop()
{
  
 loopNetMeshClient();
  
}
