#include <CommandExec.h>


void commandDistruder(JsonDocument doc)
{
    String Command = doc["Command"];

    if(Command=="Tar")
    {
        Serial.println("tar");
        setscaletar();
    }
    if(Command=="Calibration")
    {
        Serial.println("Calibration");
        setCalibrationscalet(0,doc);
    }
}

