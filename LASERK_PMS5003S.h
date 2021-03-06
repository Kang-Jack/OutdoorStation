#ifndef LASERK_PMS5003S_H
#define LASERK_PMS5003S_H

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include <SoftwareSerial.h>

#define foreach(x)  for(int i=0,row = x[i],size = sizeof(x)/sizeof(x[0]);i < size;row=x[++i])

#define UART_BAUD             9600

#define PMS_HEAD1             0x42
#define PMS_HEAD2             0x4d

/* CMD parameters */
#define PMS_CMD_READ          0xe2
//only works in passive mode

#define PMS_CMD_MODE          0xe1
#define PMS_CMD_MODE_PASSIVE  0x00
#define PASSIVE               0x00
#define PMS_CMD_MODE_ACTIVE   0x01
#define ACTIVE                0x01
#define PMS_CMD_SLEEP         0xe4
#define PMS_CMD_SLEEP_SLEEP   0x00
#define PMS_CMD_SLEEP_WAKEUP  0x01

/* receive packet prameters */

#define DATA_FORMALDE         3
#define DATA_PCS100ug         4
#define DATA_PCS50ug          5
#define DATA_PCS25ug          6
#define DATA_PCS10ug          7
#define DATA_PCS05ug          8
#define DATA_PCS03ug          9
#define DATA_PM100ATO         10
#define DATA_PM25ATO          11
#define DATA_PM10ATO          12
#define DATA_PM100CF1         13
#define DATA_PM25CF1          14
#define DATA_PM10CF1          15

/* class */

class LASERK_PMS5003S {
public:
    unsigned int data[16];

    LASERK_PMS5003S(SoftwareSerial *);
    LASERK_PMS5003S(HardwareSerial *);
    //Setup
    int begin();
    void sleep();
    void wakeUp();
    void setMode(byte);
    void request();
    int read(unsigned long = 900);

    //Get the parameters
    double getForm();
    unsigned int getPcs(double);    //available to 10, 5, 2.5, 1, 0.5, 0.3
    unsigned int getPmAto(double);  //availalbe to 10, 2.5, 1
    unsigned int getPmCf1(double);  //availalbe to 10, 2.5, 1

private:
    byte Packet[5] = { 0x42,0x4d,0, };
    byte buffer[32];

    SoftwareSerial *sofSeri;
    HardwareSerial *hwSeri;
    Stream *Seri;
    unsigned int LRC = 0;
    void send(byte, byte, byte);
    void parseG5s(unsigned char ucData);
};

#endif
