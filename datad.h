unsigned pmsAto10;
unsigned pmsAto2_5;

int aqi2_5;
int aqi10;
char aqiString_25[10];
char aqiString10[10];


const int max_length = 40;
char msg[40];
char playload[40];

char float_str_temp[8];


float temp;
float hum;
float pres;
float alti;

const int DispDelay = 5000; 
const int sensorWaitting = 60;

int ripPin = 8;
int reading = HIGH;

int inputPin = 9;
bool isLightOn=true;