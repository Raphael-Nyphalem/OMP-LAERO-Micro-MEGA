#include <SPI.h>

#define CS 10
#define EOC 9  //End Of Conversion

byte data;

void setup() {
  Serial.begin(115200);
  pinMode(CS, OUTPUT);
  pinMode(EOC, INPUT);
  digitalWrite(CS, HIGH); //desable device

  SPI.begin();


}

void loop() {

  if ( EOC == HIGH) {
    Serial.print("EOC HIGH");
  }

  Serial.println("EOC LOW");

  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS, LOW);
  Serial.print("Data recieved : ");
  Serial.println(SPI.transfer(data));
  digitalWrite(CS, HIGH);
  SPI.endTransaction();


  delay(400);


}
