#include "Barometre_HTU21D-F.h"

Adafruit_BMP3XX bmp;



void init_barometre()
{
  if (! bmp.begin_SPI(BMP_CS, BMP_SCK, BMP_MISO, BMP_MOSI)) {  // software SPI mode
    Serial.println("Could not find a valid BMP3 sensor, check wiring!");
  }
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X); // Set up oversampling and filter initialization
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void lecture_barometre(char pres[TAILLE_PRES],char temp_baro[TAILLE_TEMP_BARO])
{
    float Data;
    String strFloat;   
    if (! bmp.performReading()) {
      Serial.println("Failed to perform reading :(");
    }
    //Pression
    Data = (bmp.pressure / 100.0);
    if ((Data < 300) || (Data > 1100)) {
      strFloat = "Nan";
      strFloat.toCharArray(pres, TAILLE_PRES);
      Data = -1.00;
    }
    else {
    strFloat = String(Data,2);
    strFloat.toCharArray(pres, TAILLE_PRES);
    }

    //Temperature
    float Data2  =bmp.temperature;
    strFloat = String(Data2,2);
    strFloat.toCharArray(temp_baro, TAILLE_TEMP_BARO);
}

