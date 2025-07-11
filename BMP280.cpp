#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

float BMP_Temperature;
float BMP_Pressure;
float BMP_Approx;
unsigned int BMP280_TIME;

void BMP280_Start() {
//  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void BMP280_Run() {
    if(BMP280_TIME<10)
    {return;}BMP280_TIME=0;
    BMP_Temperature=bmp.readTemperature();
    BMP_Pressure=bmp.readPressure();
    BMP_Approx=bmp.readAltitude(1013.25);

/*
    Serial.print(F("Temperature = "));
    Serial.print(BMP_Temperature);
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(BMP_Pressure);
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print( BMP_Approx);  // Adjusted to local forecast!
    Serial.println(" m");

    Serial.println();

*/
}


