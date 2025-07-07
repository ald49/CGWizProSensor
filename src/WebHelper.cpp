#include <WebHelper.h>

String getUrlVarable(String url)
{
  int urlParmStart = url.lastIndexOf("/") + 1;

  return url.substring(urlParmStart, url.length());
}

JsonDocument convertToJsonObj(String json)
{
  JsonDocument localDoc;
  DeserializationError error = deserializeJson(localDoc, json);
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    localDoc["message"] = "Error converting json";
  }
  return localDoc;
}
