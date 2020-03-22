#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 20, 4);  // set the LCD address to 0x3f for a 16 chars and 2 line display
bool lightStatus = false;
bool cmdLight = true;
char emptyLine[40] = "                    ";
void lcdCleanLine(int row) {
    lcd.setCursor(0, row);
    lcd.print(emptyLine);
}

void lcdDataComingLine(bool isSuccess)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    if (isSuccess)
        lcd.print("Data is coming...");
    else
         lcd.print("Not find BMP280");
}
void  lcdPMSInfo(bool isNew) {
    lcdCleanLine(0);
    lcdCleanLine(1);
    lcdCleanLine(2);
    lcdCleanLine(3);

    char line0[40];
    char line1[40];
    char line2[40];
    char line3[40];
    char str_temp[7];
    if (isNew){
        snprintf(line0, sizeof(line0), "(New)AQI2_5: %s",aqiString_25);
        /* 4 is mininum width, 3 is precision; float value is copied onto str_temp*/
    // dtostrf(pmsForm, 4, 3, str_temp);
        snprintf(line1, sizeof(line1), "(New)AQI2_5:%i",aqi2_5);
        snprintf(line2, sizeof(line0), "(New)AQI10: %s",aqiString10);
        snprintf(line3, sizeof(line2), "(New)AQI10:%i ",aqi10);
    }
    else{
        snprintf(line0, sizeof(line0), "AQI2_5: %s",aqiString_25);
    // dtostrf(pmsForm, 4, 3, str_temp);
        snprintf(line1, sizeof(line1), "AQI2_5:%i",aqi2_5);
        snprintf(line2, sizeof(line0), "AQI10: %s",aqiString10);
        snprintf(line3, sizeof(line2), "AQI10:%i ",aqi10);
    }
    //snprintf(line3, sizeof(line3), "mg/m3 ug/m3");
    lcd.setCursor(0, 0);
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print(line1);
    lcd.setCursor(0, 2);
    lcd.print(line2);
    lcd.setCursor(0, 3);
    lcd.print(line3);
    delay(DispDelay);
}

void lcdBMEInfo(bool isNew) {
    lcdCleanLine(0);
    lcdCleanLine(1);
    lcdCleanLine(2);
    lcdCleanLine(3);
    char line0[40];
    char line1[40];
    char line2[40];
    char line3[40];
    char str_temp[7];
    char str_temp2[4];
    if (isNew)
    {
        snprintf(line0, sizeof(line0), "New Data Coming...");
    }
    else
    {
        snprintf(line0, sizeof(line0), "Last measured");
    }

    /* 4 is mininum width, 2 is precision; float value is copied onto str_temp*/
    dtostrf(temp, 4, 1, str_temp);
    snprintf(line1, sizeof(line1), "Temperature: %s *C", str_temp);
    dtostrf(hum, 3, 1, str_temp);
    snprintf(line2, sizeof(line2), "Humidity: %s %%", str_temp);
    dtostrf(pres, 5, 1, str_temp);
    dtostrf(alti, 3, 1, str_temp2);
    snprintf(line3, sizeof(line3), "P:%shPa A:%sM", str_temp, str_temp2);
    lcd.setCursor(0, 0);
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print(line1);
    //lcd.write(0xdf);
    //lcd.print("C");
    lcd.setCursor(0, 2);
    lcd.print(line2);
    lcd.setCursor(0, 3);
    lcd.print(line3);
    delay(DispDelay);
}

void lcdStartScreen()
{
    char line0[40];
    char line1[40];
    char line2[40];
    char line3[40];
    snprintf(line0, sizeof(line0), "Hello, Arduino!");
    snprintf(line1, sizeof(line1), "Outdoor station");
    snprintf(line2, sizeof(line2), "Have a nice day!");
    snprintf(line3, sizeof(line3), "Power By Laserk");
    lcd.clear();
    lcd.setCursor(0, 0);// col ,row start from 0
    lcd.print(line0);
    lcd.setCursor(0, 1);
    lcd.print(line1);
    lcd.setCursor(0, 2);
    lcd.print(line2);
    lcd.setCursor(0, 3);
    lcd.print(line3);
    delay(DispDelay);
}

void setupLcd() {
    lcd.init();
    lcd.noAutoscroll();
    lcd.backlight();
    lcdStartScreen();
    delay(2000);
    lcd.clear();
}