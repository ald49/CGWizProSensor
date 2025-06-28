#include <Wireless.h>

WiFiClient client;

void createwifi()
{
  const char *ssid = "CGWiz";            // Your desired SSID
  const char *password = "testpassword"; // Your desired password (minimum 8 characters for WPA2)
  Serial.print("Connecting to SSID:");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.write('.');
  }
  Serial.print("Connected");
}
