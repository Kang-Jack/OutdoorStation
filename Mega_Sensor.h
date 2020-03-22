#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
int ripVal = LOW;                    // variable for reading the pin status

bool setupSensor() {
  bool status;
  pinMode(inputPin, INPUT);
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Not find BMP280");
  }
  return status;
    
}

bool handleBME280(bool isWorking) {
  //Serial.println("handleBME280");
  //Serial.println(isWorking);
  if(isWorking)
  {
    //Serial.println("read temp");
    temp = bme.readTemperature();  // Get Temperature value
    hum = bme.readHumidity();  // Get Humidity value
    //dtostrf(temp, 4, 2, str_temp);
    pres = bme.readPressure() / 100.0F;
    alti = bme.readAltitude(SEALEVELPRESSURE_HPA);
    //Serial.println("read temp done");
    return true;
  }
  return false;
}

void readInput(){
  if(reading==LOW){
     reading = digitalRead(inputPin);
  }
}