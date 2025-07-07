#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>

String getUrlVarable(String url);
JsonDocument convertToJsonObj(String json);