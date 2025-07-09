#include <saveMem.h>

String STATION_SSID;
String STATION_PASSWORD;

// to store Preferences
Preferences preferences;

//  Prototypes
void readDataWifi();
void saveDataWifi();

void initpreferences()
{
    preferences.begin("Config", false);
    readDataWifi();
}

void saveDataScale()
{
    preferences.begin("Config", false);
    String ps = "LCellcal";
    preferences.putFloat(ps.c_str(), LoadCellcalibrationValue);
}

void readDataScale()
{
    preferences.begin("Config", false);
    String ps = "LCellcal";
    LoadCellcalibrationValue = preferences.getFloat(ps.c_str(), 100);
}
