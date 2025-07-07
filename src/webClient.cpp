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

void putData()
{
    // webClientInit();
    if (WiFi.status() == WL_CONNECTED)
    {
        PATH_NAME = "/putdata";
        String serverPath = HOST_NAME + PATH_NAME;
        httpclient.begin(serverPath.c_str());
        JsonDocument doc;
        doc["Unit"] = ESP.getEfuseMac();
        doc["loadvalue"] = LoadValue;
        String json;
        serializeJson(doc, json);

        httpclient.addHeader("Content-Type", "application/json");
        // Send HTTP GET request
        int httpResponseCode = httpclient.PUT(json);

        // if (httpResponseCode > 0)
        //{
        //     Serial.print("HTTP Response code: ");
        //     Serial.println(httpResponseCode);
        //     String payload = httpclient.getString();
        //     Serial.println(payload);
        // }
        // else
        //{
        //     Serial.print("Error code: ");
        //     Serial.println(httpResponseCode);
        // }
        //  Free resources
        httpclient.end();
    }
    else
    {
        createwifi();
    }
}

void getCommand()
{
    // webClientInit();
    if (WiFi.status() == WL_CONNECTED)
    {
        PATH_NAME = "/getcommand";
        String serverPath = HOST_NAME + PATH_NAME;
        httpclient.begin(serverPath.c_str());
        JsonDocument doc;
        doc["Unit"] = ESP.getEfuseMac();
        String json;
        serializeJson(doc, json);

        httpclient.addHeader("Content-Type", "application/json");
        // Send HTTP GET request
        int httpResponseCode = httpclient.POST(json);

        if (httpResponseCode > 0)
        {
            // Serial.print("HTTP Response code: ");
            // Serial.println(httpResponseCode);
            String payload = httpclient.getString();
            if (payload != "null")
            {
                Serial.println(payload);
                JsonDocument localdoc;
                localdoc = convertToJsonObj(payload);
                commandDistruder(localdoc);
            }
        }
        else
        {
            Serial.print("Error code: ");
            Serial.println(httpResponseCode);
        }
        //  Free resources
        httpclient.end();
    }
    else
    {
        createwifi();
    }
}

void putMsg()
{
    // webClientInit();
    if (WiFi.status() == WL_CONNECTED)
    {
        PATH_NAME = "/putmsg";
        String serverPath = HOST_NAME + PATH_NAME;
        httpclient.begin(serverPath.c_str());
        JsonDocument doc;
        doc["Unit"] = ESP.getEfuseMac();
        doc["loadvalue"] = LoadValue;
        String json;
        serializeJson(doc, json);

        httpclient.addHeader("Content-Type", "application/json");
        // Send HTTP GET request
        int httpResponseCode = httpclient.PUT(json);

        // if (httpResponseCode > 0)
        //{
        //     Serial.print("HTTP Response code: ");
        //     Serial.println(httpResponseCode);
        //     String payload = httpclient.getString();
        //     Serial.println(payload);
        // }
        // else
        //{
        //     Serial.print("Error code: ");
        //     Serial.println(httpResponseCode);
        // }
        //  Free resources
        httpclient.end();
    }
    else
    {
        createwifi();
    }
}

void postdata()
{
    // webClientInit();
    if (WiFi.status() == WL_CONNECTED)
    {
        PATH_NAME = "/addmodel";
        String serverPath = HOST_NAME + PATH_NAME;
        httpclient.begin(serverPath.c_str());
        JsonDocument doc;
        doc["Unit"] = ESP.getEfuseMac();
        doc["loadvalue"] = LoadValue;
        String json;
        serializeJson(doc, json);

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
