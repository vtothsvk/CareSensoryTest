#include <M5StickC.h>
#include <Adafruit_BME680.h>
#include <VL53L0X.h>
#include "care_pinout.h"

/** Sensor select directives
 * 
 *  @note select only one
 */
#define _PIR
//#define _FSR
//#define _TOF
//#define _LIGHT
//#define _BME

void update();
void printout();

#ifdef _TOF
VL53L0X tof;
#endif

#ifdef _BME
Adafruit_BME680 bme;
#endif

bool motion;
uint16_t smoke, light, distance, pressure;
float temp, hum, aPressure, smoke;

void setup() {
    Serial.begin(115200);
    Serial.printf("AP Care Sensory Test begin")

    Wire.begin();

    #ifdef _BME
    bme.begin();
    #endif

    #ifdef _TOF
    tof.setTimeout(500);
    if (!tof.init()) {
        Serial.println("Failed to detect and initialize ToF sensor!");
        while (1) {}
    }//if (!tof.init())
    tof.startContinuous(100);
    #endif    
}//setup

void loop() {
    update();
    printout();
    delay(500)
}//loop

void update() {
    #ifdef _PIR
    motion = digitalRead(PIR_PIN);
    #endif

    #ifdef _FSR
    pressure = analogRead(FSR_PIN)
    #endif

    #ifdef _TOF
    distance = tof.readRangeContinuousMillimeters();
    #endif

    #ifdef _LIGHT
    light = analogRead(LIGHT_PIN);
    #endif

    #ifdef _BME
    temp = bme.readTemperature();
    hum = bme.readHumidity();
    aPressure = bme.readPressure();
    smoke = bme.readGas();
    #endif
}//update

void printout(){
    #ifdef _PIR
    Serial.printf("Motion:  %d\r\n", motion);
    #endif

    #ifdef _FSR
    Serial.printf("Pressure: %d\r\n", pressure);
    #endif

    #ifdef _TOF
    Serial.printf("Distance: %d\r\n", distance);
    #endif

    #ifdef _LIGHT
    Serial.printf("Light:   %d\r\n", );
    #endif

    #ifdef _BME
    Serial.printf("Temperature:  %.1f\r\n", temp);
    Serial.printf("Humidity:     %.1f\r\n", hum);
    Serial.printf("At. Pressure: %.1f\r\n", aPressure);
    Serial.printf("Smoke:        %.1f\r\n", smoke);;
    #endif
}//printout