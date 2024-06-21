#include <SPI.h>

#define CS 10
#define EOC 9  //End Of Conversion

void setup() {
  Serial.begin(115200);
  pinMode(CS, OUTPUT);
  pinMode(EOC, INPUT);

  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2); //8Mhz
  digitalWrite(CS, HIGH); 
  
}

void loop() {
  
  uint16_t data_in = 3072; // 0000 1100 0000 0000
  uint16_t data_out;

  Serial.println("Data IN :");
  Serial.println(data_in, BIN);

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
     
     digitalWrite(CS, LOW);
  
    data_out = SPI.transfer(data_in);
  
  SPI.endTransaction();
  digitalWrite(CS, HIGH);


  //==== Data OUT binary  
  
  Serial.println("Data OUT before >> 4  :");
  Serial.println(data_out, BIN); 
  Serial.println(data_out);
  Serial.println();
  
  data_out = data_out >> 4;
  
  Serial.println("Data OUT :");
  Serial.println(data_out, BIN); 
  Serial.println(data_out);
  Serial.println();

  
  //==== Convertion 
  float resu1 = data_out *(1.52/4096);
  //float resu2 = data_out *(4.9134/4096);

  Serial.println("Convertion : ");
  Serial.println(resu1);
  //Serial.println(resu2);
  Serial.println();
}
