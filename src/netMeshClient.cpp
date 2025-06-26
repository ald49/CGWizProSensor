#include <netMeshClient.h>

Scheduler userScheduler; // to control your personal task
painlessMesh mesh;

// Prototype
void receivedCallback(uint32_t from, String &msg);

size_t logServerId = 0;

// Send message to the logServer every 10 seconds
Task myLoggingTask(300, TASK_FOREVER, []()
{
    JsonDocument jsonBuffer;
    JsonObject msg = jsonBuffer.to<JsonObject>();

    updateScale();
    msg["topic"] = mesh.getNodeId();
    msg["value"] = LoadValue;

    String str;
    serializeJson(msg, str);

    if (logServerId == 0) // If we don't know the logServer yet
        mesh.sendBroadcast(str);
    else
        mesh.sendSingle(logServerId, str);

    // log to serial
    // serializeJson(msg, Serial);

    // Serial.printf("\n");
});

void setupNetMeshClient()
{
    Serial.begin(115200);

    mesh.setDebugMsgTypes(ERROR); // set before init() so that you can see startup messages

    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT, WIFI_AP_STA);
    mesh.onReceive(&receivedCallback);

    // Add the task to the your scheduler
    userScheduler.addTask(myLoggingTask);
    myLoggingTask.enable();
}

void loopNetMeshClient()
{
    // it will run the user scheduler as well
    mesh.update();
}

void receivedCallback(uint32_t from, String &msg)
{
    Serial.printf("logClient: Received from %u msg=%s\n", from, msg.c_str());

    // Saving logServer

    JsonDocument jsonBuffer;
    DeserializationError error = deserializeJson(jsonBuffer, msg);
    if (error)
    {
        Serial.printf("DeserializationError\n");
        return;
    }
    JsonObject root = jsonBuffer.as<JsonObject>();

    if (root["topic"].is<String>())
    {
        if (String("CGWisServer").equals(root["topic"].as<String>()))
        {
            // check for on: true or false
            logServerId = root["nodeId"];
            Serial.printf("CGWisServer detected!!!\n");
        }
        Serial.printf("Handled from %u msg=%s\n", from, msg.c_str());
    }
}
