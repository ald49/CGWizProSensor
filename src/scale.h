#pragma once
#include <Arduino.h>
#include <HX711_ADC.h>
#include <ArduinoJson.h>
#include <webClient.h>
#include <saveMem.h>

const int HX711_dout = 0;
const int HX711_sck = 1;


void InitScale();
void updateScale();
boolean setscaletar();
boolean setscaletar(int id);
boolean setCalibrationscalet(int id, JsonDocument jsono);
extern float LoadValue;
extern float LoadCellcalibrationValue;
extern int NumberOfLoadcells;

extern JsonDocument docmsg;
JsonDocument getscaledata();
