#include <scale.h>

HX711_ADC LoadCell(HX711_dout, HX711_sck);

int NumberOfLoadcells = 1;
float LoadCellcalibrationValue = 100;
float LoadValue;
float loadMoment;
float TotalWeight = 0;
unsigned long stabilizingtime = 2000;
float lrdiff = 0;

boolean _tare = true;
float cg = 0;
boolean loadcell_rdy;
unsigned long t = 0;

void InitScale()
{
    Serial.println("Start scale");
    // readDataScale();

    LoadCell.begin();
    LoadCell.start(stabilizingtime, _tare);
    if (LoadCell.getTareTimeoutFlag())
    {
        Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
        while (1)
            ;
    }
    else
    {
        LoadCell.setCalFactor(LoadCellcalibrationValue); // set calibration value (float)
        Serial.println("Startup is complete");
    }
}

boolean CheckLoadCell(HX711_ADC LoadCell_Local, int LoadCellNumber)
{
    boolean loadcell_rdy = false;
    if (LoadCell_Local.getTareTimeoutFlag())
    {
        if (LoadCellNumber != 0)
        {
            Serial.println("Timeout, check MCU>HX711 no." + String(LoadCellNumber) + " wiring and pin designations");
        }
        loadcell_rdy = false;
    }
    return loadcell_rdy;
}

void updateScale()
{

    static boolean newDataReady = 0;
    const int serialPrintInterval = 0; // increase value to slow down serial print activity

    // check for new data/start next conversion:
    if (LoadCell.update())
        newDataReady = true;

    // get smoothed value from the dataset:
    if (newDataReady)
    {
        if (millis() > t + serialPrintInterval)
        {
            //Serial.print("Load_cell output val: ");
            //Serial.println(i);
            newDataReady = 0;
            t = millis();
            LoadValue=LoadCell.getData();
        }
    }

    // receive command from serial terminal, send 't' to initiate tare operation:
    if (Serial.available() > 0)
    {
        char inByte = Serial.read();
        if (inByte == 't')
            LoadCell.tareNoDelay();
    }

    // check if last tare operation is complete:
    if (LoadCell.getTareStatus() == true)
    {
        Serial.println("Tare complete");
    }

    // check for new data/start next conversion:

    // LoadCell.update();
    // if (LoadCell.getDataSetStatus())
    // {
    //     LoadValue = LoadCell.getData();
    //     Serial.println(LoadValue);
    // }
    // check if last tare operation is complete
    // if (LoadCell.getTareStatus() == true)
    // {
    //     Serial.println("Tare load cell");
    // addMassage("Tare load cell " + String(i) + " complete");
    // }
}

boolean setscaletar()
{
    Serial.println("Start Tare");
    // addMassage("Starting Tare");

    LoadCell.tareNoDelay();

    return true;
}

boolean setscaletar(int id)
{
    Serial.println("Start Tare LoadCell " + String(id));
    // addMassage("Starting Tare");

    LoadCell.tareNoDelay();

    return true;
}

JsonDocument getscaledata()
{
    JsonDocument doc;

    doc["cg"] = cg;
    doc["L0L2diff"] = lrdiff;
    doc["TotalWeight"] = TotalWeight;
    JsonArray models = doc["scalevalues"].to<JsonArray>();

    JsonObject scalevalue = models.add<JsonObject>();
    scalevalue["id"] = 0;
    scalevalue["weight"] = LoadValue;
    scalevalue["loadMoment"] = loadMoment;
    scalevalue["LoadCellcalibrationValue"] = LoadCellcalibrationValue;

    return doc;
}

boolean setCalibrationscalet(int id, JsonDocument jsono)
{

    float knownmass = jsono["knownmass"];
    // float knownmass = 139.30;
    // addMassage("Starting calibration");

    // check for new data/start next conversion:

    if (LoadCell.update())
    {
        LoadValue = LoadCell.getData();
    }

    LoadCell.getNewCalibration(knownmass);
    LoadCellcalibrationValue = LoadCell.getCalFactor();

    // saveDataScale();
    return true;
}
