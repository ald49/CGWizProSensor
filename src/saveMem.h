#pragma once
#include <Arduino.h>
#include <Preferences.h>
#include <ArduinoJson.h>
#include <scale.h>
//#include <scale_model.h>

void initpreferences();

void readDataWifi();
void saveDataWifi();

void readDataScale();
void saveDataScale();

void saveDistanceScale();
void readDistanceScale();

extern String STATION_SSID;
extern String STATION_PASSWORD;