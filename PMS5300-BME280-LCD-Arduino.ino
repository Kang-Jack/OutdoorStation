#include <Wire.h>
#include "datad.h"
#include "ESP_PMS5003S.h"
#include "Mega_Sensor.h"
#include "Mega_LCD.h"

int workingSec = 60;
bool bmeStatus;

void setup(void){
  Serial.begin(115200);
  setupLcd();
  setupPMS5003S();
  bmeStatus=setupSensor();
  //Serial.println(String(bmeStatus));
  if (!bmeStatus) {
      lcdDataComingLine(false);
  }
}

void loop(void){
  readInput();
  //Serial.println("loop");

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
    if (bmeStatus)
      isHandleBME = handleBME280(workingSec>=1);
    if(bmeStatus && isHandleBME)
    {
      //Serial.println("LCD bme");
      readInput();
      checkLight();
      lcdBMEInfo(true);
      delay(500);
    }

    if(isHandlePMS){
      readInput();
      //Serial.println("LCD PMS");
      checkLight();
      lcdPMSInfo(true);
      delay(500);    
    }
    workingSec--;
  }
  else
  {   
    sleep();
    readInput();
    checkLight();
    delay(500);  

    lcdPMSInfo(false);
    if(bmeStatus)
    { 
      readInput();
      checkLight();
      delay(500); 
      lcdBMEInfo(false);
    }
    delay(500); 
  }

}
