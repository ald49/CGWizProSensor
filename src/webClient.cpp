#include <webClient.h>

int HTTP_PORT = 5000;
char HOST_NAME[] = "http://1.1.1.1:5000"; // hostname of web server:

String PATH_NAME = "/getmodels";
String HTTP_METHOD = "GET"; // or "POST"

HTTPClient httpclient;
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
// unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void webClientInit()
{
PATH_NAME = "/getmodels";
    String serverPath = HOST_NAME + PATH_NAME;
    httpclient.begin(serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = httpclient.GET();

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = httpclient.getString();
        Serial.println(payload);
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    httpclient.end();
}

void postdata()
{
    webClientInit();
    if (WiFi.status() == WL_CONNECTED)
    {
        PATH_NAME = "/addmodel";
        String serverPath = HOST_NAME + PATH_NAME;
        httpclient.begin(serverPath.c_str());
        JsonDocument doc;
        doc["Unit"] =  ESP.getEfuseMac();
        doc["loadvalue"] = LoadValue;
        String json;
        serializeJson(doc,json);


        httpclient.addHeader("Content-Type", "application/json");
        // Send HTTP GET request
        int httpResponseCode = httpclient.POST(json);

        if (httpResponseCode > 0)
        {
            Serial.print("HTTP Response code: ");
            Serial.println(httpResponseCode);
            String payload = httpclient.getString();
            Serial.println(payload);
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        // Free resources
        httpclient.end();
    }
    else
    {
        createwifi();
    }
}
