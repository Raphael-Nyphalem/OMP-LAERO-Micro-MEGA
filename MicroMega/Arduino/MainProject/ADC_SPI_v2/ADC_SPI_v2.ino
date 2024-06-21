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
  
  //Bit Test//
  int adr_bit = 0;        // 0000  -> AIN0
  //int adr_bit = 1;        // 0001  -> AIN1
  //int adr_bit = 2;        // 0010  -> AIN2
  //int LenForm_bit = 3328; // 1101 0000 0000 ->  (1-2) 16bit length ; (3) MSB first ;  (4)Bipolar BIP ; (5-12) padding ;
  int LenForm_bit = 3072; // 1100 0000 0000 
  
  int shift_data_byte = adr_bit << 4; //0001 0000
  int shift_LenForm_bit = LenForm_bit >> 8; //0000 1101

  int byte1 = shift_data_byte | shift_LenForm_bit; // 0001 1101 
  byte byte2 = B0000; // 0000 0000 -> padding 
  //========//  
  //Serial.print("byte1 : ");
  //Serial.println(byte1, BIN);
  
  //byte data_in = B00001001; // Input-Register Format
  Serial.println("Data IN :");
  Serial.println(byte1, BIN); 
  Serial.println(byte2,BIN);
  
  byte data_out1; 
  byte data_out2; 

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
     
     digitalWrite(CS, LOW);
    //data_out = SPI.transfer(data_in);   
    data_out1 = SPI.transfer(byte1);   
    data_out2 = SPI.transfer(byte2);   

  SPI.endTransaction();
  digitalWrite(CS, HIGH);


  //==== Data OUT binary  
  uint16_t data_out = (data_out1 << 8) | data_out2;
  data_out = data_out >> 4;
  
  Serial.println("Data OUT :");
  Serial.println(data_out1, BIN); 
  Serial.println(data_out2,BIN);
  Serial.println();
  Serial.println(data_out,BIN);
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
