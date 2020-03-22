#include <Wire.h>
#include "datad.h"
#include "ESP_PMS5003S.h"
#include "Mega_Sensor.h"
#include "Mega_LCD.h"

const int sensorWaitting = 60;
int workingSec = 60;
bool bmeStatus;
void setup(void){
  Serial.begin(115200);
  setupLcd();
  setupPMS5003S();
  bmeStatus=setupSensor();
  Serial.println(String(bmeStatus));
  if (!bmeStatus) {
      lcdDataComingLine(false);
  }
}

void loop(void){
  readInput();
  Serial.println("loop");

  if(reading==HIGH)
  {
    reading = LOW;
    lcdDataComingLine(true);
    if (!isWake)
    {
      wake();
    }
      workingSec=sensorWaitting;
  }
  if (workingSec>=1)
  {
    bool isHandlePMS=false;
    bool isHandleBME=false;
    isHandlePMS = handlePMS5003S();
    if(!isHandlePMS){
      int i =workingSec;
      while ((i<workingSec+10)&&(!isHandlePMS))
      {
        isHandlePMS=handlePMS5003S();
        i++;
      }
    }
    Serial.println("out pms");
    Serial.println(isHandlePMS);
    Serial.println(workingSec);
    if (bmeStatus)
      isHandleBME = handleBME280(workingSec>=1);

     Serial.println("out pms3");
      if(bmeStatus && isHandleBME)
      {
        Serial.println("LCD bme");
        readInput();
        lcdBMEInfo(true);
        delay(500);
      }

      readInput();
      Serial.println("LCD PMS");
      if(isHandlePMS){
        lcdPMSInfo(true);
        delay(500);    
      }
      workingSec--;
  }
  else
  {   
    sleep();
    Serial.println("LCD history");
    readInput();
    delay(500);  
    lcdPMSInfo(false);
    if(bmeStatus)
    { 
      readInput();
      delay(500); 
      lcdBMEInfo(false);
    }
    delay(500); 
  }

}
