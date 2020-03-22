#include "LASERK_PMS5003S.h"
//#include <SoftwareSerial.h>
//SoftwareSerial dust(12,13);
int WakeMins = 0;
bool isWake = false;
int lastM = 0;
int lastH = 0;
//LASERK_PMS5003S pms(&dust);
LASERK_PMS5003S pms(&Serial3);

double us_pm2_5_category[7][4] = { {0.0, 12.0, 0, 50}, {12.1, 35.4, 51, 100},
{35.5, 55.4, 101, 150}, {55.5, 150.4, 151, 200},
{150.5, 250.4, 201, 300}, {250.5, 350.4, 301, 400}, {350.5, 500.4, 401, 500} };
double us_pm10_category[7][4] = { {0.0, 54.0, 0, 50}, {55.0, 154, 51, 100},
{155, 254, 101, 150}, {255, 354, 151, 200},
{355, 424, 201, 300}, {425, 504, 301, 400}, {505, 604, 401, 500} };

double chn_pm2_5_category[7][4] = { {0.0, 35, 0, 50}, {35.1, 75.0, 51, 100},
                      {75.1, 115, 101, 150}, {115.1, 150, 151, 200},
                      {150.1, 250, 201, 300}, {250.1, 350, 301, 400}, {350.1, 500, 401, 500} };
double chn_pm10_category[7][4] = { {0.0, 50, 0, 50}, {50.1, 150, 51, 100},
                     {150.1, 250, 101, 150}, {250.1, 350, 151, 200},
                     {350.1, 420, 201, 300}, {420.1, 500, 301, 400}, {500.1, 600, 401, 500} };

double caculator(const double* match_category, int iaqi) {
    return (match_category[3] - match_category[2]) / (match_category[1] - match_category[0])*(iaqi - match_category[0]) + match_category[2];
}

int us_pm2_5_aqi_caculator(int pm2_5_iaqi) {
    //clean char array
    memset(aqiString_25, 0, sizeof(aqiString_25));
    if (pm2_5_iaqi < us_pm2_5_category[0][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Good");
        return caculator(us_pm2_5_category[0], pm2_5_iaqi);
    }
    if (pm2_5_iaqi < us_pm2_5_category[1][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Lightly");
        return caculator(us_pm2_5_category[1], pm2_5_iaqi);
    }
    if (pm2_5_iaqi < us_pm2_5_category[2][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Moderately");
        return caculator(us_pm2_5_category[2], pm2_5_iaqi);
    }
    if (pm2_5_iaqi < us_pm2_5_category[3][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Unhealthy");
        return caculator(us_pm2_5_category[3], pm2_5_iaqi);
    }
    if (pm2_5_iaqi < us_pm2_5_category[4][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Heavily");
        return caculator(us_pm2_5_category[4], pm2_5_iaqi);
    }
    if (pm2_5_iaqi < us_pm2_5_category[5][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Hazardous");
        return caculator(us_pm2_5_category[5], pm2_5_iaqi);
    }
    if (pm2_5_iaqi < us_pm2_5_category[6][1]) {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Severely");
        return caculator(us_pm2_5_category[6], pm2_5_iaqi);
    }
    else {
        snprintf(aqiString_25, sizeof(aqiString_25) - 1, "%s", "Severely");
        return caculator(us_pm2_5_category[6], pm2_5_iaqi);
    }
}

int us_pm10_aqi_caculator(int pm10_iaqi) {
    //clean char array
    memset(aqiString10, 0, sizeof(aqiString10));
    if (pm10_iaqi < us_pm10_category[0][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Good");
        return caculator(us_pm10_category[0], pm10_iaqi);
    }
    if (pm10_iaqi < us_pm10_category[1][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Lightly");
        return caculator(us_pm10_category[1], pm10_iaqi);
    }
    if (pm10_iaqi < us_pm10_category[2][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Moderately");
        return caculator(us_pm10_category[2], pm10_iaqi);
    }
    if (pm10_iaqi < us_pm10_category[3][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Unhealthy");
        return caculator(us_pm10_category[3], pm10_iaqi);
    }
    if (pm10_iaqi < us_pm10_category[4][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Heavily");
        return caculator(us_pm10_category[4], pm10_iaqi);
    }
    if (pm10_iaqi < us_pm10_category[5][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Hazardous");
        return caculator(us_pm10_category[5], pm10_iaqi);
    }
    if (pm10_iaqi < us_pm10_category[6][1]) {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Severely");
        return caculator(us_pm10_category[6], pm10_iaqi);
    }
    else {
        snprintf(aqiString10, sizeof(aqiString10) - 1, "%s", "Severely");
        return caculator(us_pm10_category[6], pm10_iaqi);
    }
}

void setupPMS5003S() {
    Serial3.begin(9600);
    //dust.begin(9600);
    pms.begin();
    //pms.setMode(ACTIVE);
    pms.setMode(PASSIVE);
    pms.wakeUp();
    delay(500);
    isWake = true;
    WakeMins = 0;
    //Serial.println("setup dust");
}

void wake() {
    isWake = true;
    pms.wakeUp();
    delay(500);
}
void sleep() {
    isWake = false;
    pms.sleep();
    delay(500);
}

bool IsWake()
{
     return isWake;
}
bool handlePMS5003S() {
    if (isWake) {
        Serial.println("WAKE");
        pms.request();
        if (!pms.read()) {
            Serial.println("READ FAILD");
            return false;
        }
        pmsAto2_5 = pms.getPmAto(2.5);
        pmsAto10 = pms.getPmAto(10.0);
        //Serial.println(pmsAto2_5);
        //Serial.println(pmsAto10);
        aqi2_5 = us_pm2_5_aqi_caculator(pmsAto2_5);
        aqi10 = us_pm10_aqi_caculator(pmsAto10);
        //Serial.println(aqi2_5);
        //Serial.println(aqi10);
        //Serial.println("caculator done");
        return true;
    }
    else{//Serial.println("SLEEP");
        return false;
    }
    
}