#include <Arduino.h>

#include <scale.h>
#include <tcpclient.h>


void setup()
{
  Serial.begin(115200);
  InitScale();
  initTcpClient();
  
}

void loop()
{
  
 updateTcpClient();
  
}
