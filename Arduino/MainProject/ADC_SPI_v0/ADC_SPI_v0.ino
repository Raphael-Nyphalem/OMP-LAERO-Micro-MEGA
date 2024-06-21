#include <SPI.h>

#define CS 10
#define EOC 9  //End Of Conversion

void setup() {
  Serial.begin(115200);
  pinMode(CS, OUTPUT);
  pinMode(EOC, INPUT);

  SPI.begin();
  //SPI.setClockDivider(SPI_CLOCK_DIV2); //8Mhz
  digitalWrite(CS, HIGH); //desable device

}

void loop() {

  byte data = 0x00;
  byte mydata1;
  byte mydata2;
  byte mydata3;
  byte mydata4;

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
  
  if ( digitalRead(EOC) == HIGH ) {
    
    digitalWrite(CS, LOW);
    mydata1 = SPI.transfer(data);
    mydata2 = SPI.transfer(data);
    mydata3 = SPI.transfer(data);
    mydata4 = SPI.transfer(data);
  }
  digitalWrite(CS, HIGH);
  SPI.endTransaction();
  //  Serial.println(mydata,BIN);
  //  Serial.println(mydata);
  //  delay(100);
}
