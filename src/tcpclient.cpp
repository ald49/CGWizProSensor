#include <tcpclient.h>

const char *ssid = "ESP32-AP";
const uint16_t portNumber = 50000;
IPAddress serverIP;
WiFiClient client;
bool connected = false;

void initTcpClient()
{
    Serial.print("Connecting to SSID:");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.begin(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.write('.');
    }
    Serial.println(".\nConnected");
    Serial.print("Local IP = ");
    Serial.println(WiFi.localIP());
    serverIP = WiFi.gatewayIP();
    Serial.flush();
}

void updateTcpClient()
{
    if (!connected)
    {
        if (client.connect(serverIP, portNumber))
        {
            Serial.print("Connected to Gateway IP = ");
            Serial.println(serverIP);
            connected = true;
        }
        else
        {
            Serial.print("Could NOT connect to Gateway IP = ");
            Serial.println(serverIP);
            delay(500);
        }
    }
    else
    {

        while (client.available())
            Serial.write(client.read());
            updateScale();
            String a = String(LoadValue,2);
            client.write(a.c_str());
        while (Serial.available())
        {
            char r = Serial.read();
            Serial.write(r);
            int a = client.write(r);
            a = client.write("rr");
            // Serial.println(a);
            if (a)
            {
            }
            else
            {
                Serial.println("false");
                client.connect(serverIP, portNumber);
            }
        }
    }
}