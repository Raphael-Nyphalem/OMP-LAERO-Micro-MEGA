#include "Alphasense_A4.h"

void init_alphasense()
{
  pinMode(ADC1_CS, OUTPUT);
  pinMode(ADC1_EOC, INPUT);
  pinMode(ADC2_CS, OUTPUT);
  pinMode(ADC2_EOC, INPUT);
  SPI.begin();
  digitalWrite(ADC1_CS, HIGH);
  digitalWrite(ADC2_CS, HIGH);
  init_ADC(B00001100, ADC1_CS); //Requête de la première data (CH0)
  init_ADC(B00001100, ADC2_CS);
}


void init_ADC(byte data_IN_8b, int ADC_CS) {

  byte data_out_1_ADC;
  byte data_out_2_ADC;

  SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0));
  digitalWrite(ADC_CS, LOW);
  data_out_1_ADC = SPI.transfer(data_IN_8b);   // envoie des 8 bits d'input data register + reception 8 premiers bits de Data OUT
  data_out_2_ADC = SPI.transfer(B00000000);   // Pading -> bits ignore + reception 8 derniers bits de Data OUT
  SPI.endTransaction();
  digitalWrite(ADC_CS, HIGH);
}


void alphasens(struct donnee_Alphasense *adc1,struct donnee_Alphasense *adc2,char tab_adc_brut_radio[TAILLE_TAB_DATA_ADC_RADIO] )
{
    //===== Alphasense ====//
  //ADC1
  uint16_t data_out_ch0_ADC1;
  uint16_t data_out_ch1_ADC1;
  uint16_t data_out_ch2_ADC1;
  uint16_t data_out_ch3_ADC1;
  uint16_t data_out_ch4_ADC1;
  uint16_t data_out_ch5_ADC1;
  uint16_t data_out_ch6_ADC1;
  uint16_t data_out_ch7_ADC1;
  uint16_t data_out_ch8_ADC1;
  uint16_t data_out_ch10_ADC1;
  byte data_out_init_1_ADC1;
  byte data_out_init_2_ADC1;
  byte data_out_ch0_1_ADC1;
  byte data_out_ch0_2_ADC1;
  byte data_out_ch1_1_ADC1;
  byte data_out_ch1_2_ADC1;
  byte data_out_ch2_1_ADC1;
  byte data_out_ch2_2_ADC1;
  byte data_out_ch3_1_ADC1;
  byte data_out_ch3_2_ADC1;
  byte data_out_ch4_1_ADC1;
  byte data_out_ch4_2_ADC1;
  byte data_out_ch5_1_ADC1;
  byte data_out_ch5_2_ADC1;
  byte data_out_ch6_1_ADC1;
  byte data_out_ch6_2_ADC1;
  byte data_out_ch7_1_ADC1;
  byte data_out_ch7_2_ADC1;
  byte data_out_ch8_1_ADC1;
  byte data_out_ch8_2_ADC1;
  byte data_out_ch10_1_ADC1;
  byte data_out_ch10_2_ADC1;
  //ADC2
  uint16_t data_out_ch0_ADC2;
  uint16_t data_out_ch1_ADC2;
  uint16_t data_out_ch2_ADC2;
  uint16_t data_out_ch3_ADC2;
  uint16_t data_out_ch4_ADC2;
  uint16_t data_out_ch5_ADC2;
  uint16_t data_out_ch6_ADC2;
  uint16_t data_out_ch7_ADC2;
  uint16_t data_out_ch8_ADC2;
  uint16_t data_out_ch10_ADC2;
  byte data_out_init_1_ADC2;
  byte data_out_init_2_ADC2;
  byte data_out_ch0_1_ADC2;
  byte data_out_ch0_2_ADC2;
  byte data_out_ch1_1_ADC2;
  byte data_out_ch1_2_ADC2;
  byte data_out_ch2_1_ADC2;
  byte data_out_ch2_2_ADC2;
  byte data_out_ch3_1_ADC2;
  byte data_out_ch3_2_ADC2;
  byte data_out_ch4_1_ADC2;
  byte data_out_ch4_2_ADC2;
  byte data_out_ch5_1_ADC2;
  byte data_out_ch5_2_ADC2;
  byte data_out_ch6_1_ADC2;
  byte data_out_ch6_2_ADC2;
  byte data_out_ch7_1_ADC2;
  byte data_out_ch7_2_ADC2;
  byte data_out_ch8_1_ADC2;
  byte data_out_ch8_2_ADC2;
  byte data_out_ch10_1_ADC2;
  byte data_out_ch10_2_ADC2;
  //=============== Alphasens ===============//
        //Acquisition Data ch0-ch8 ADC1 :
    SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0)); //SPI_CLOCK_DIV2
    digitalWrite(ADC1_CS, LOW);
    //ch0 + requête ch1
    SPI.transfer(0x00 | 0x0C);
    SPI.transfer(0x00);
    delayMicroseconds(20);
    data_out_ch0_1_ADC1 = SPI.transfer(0x10 | 0x0C);
    data_out_ch0_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch1 + requête ch2
    data_out_ch1_1_ADC1 = SPI.transfer(0x20 | 0x0C);
    data_out_ch1_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch2 + requête ch3
    data_out_ch2_1_ADC1 = SPI.transfer(0x30 | 0x0C);
    data_out_ch2_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch3 + requête ch4
    data_out_ch3_1_ADC1 = SPI.transfer(0x40 | 0x0C);
    data_out_ch3_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch4 + requête ch5
    data_out_ch4_1_ADC1 = SPI.transfer(0x50 | 0x0C);
    data_out_ch4_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch5 + requête ch6
    data_out_ch5_1_ADC1 = SPI.transfer(0x60 | 0x0C);
    data_out_ch5_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch6 + requête ch7
    data_out_ch6_1_ADC1 = SPI.transfer(0x70 | 0x0C);
    data_out_ch6_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch7 + requête ch8
    data_out_ch7_1_ADC1 = SPI.transfer(0x80 | 0x0C);
    data_out_ch7_2_ADC1 = SPI.transfer(0x00);
    delayMicroseconds(20);
    //ch8 + requête ch0
    data_out_ch8_1_ADC1 = SPI.transfer(0xA0 | 0x0C);
    data_out_ch8_2_ADC1 = SPI.transfer(0x00);

    delayMicroseconds(20);
    //ch8 + requête ch0
    data_out_ch10_1_ADC1 = SPI.transfer(0x00 | 0x0C);
    data_out_ch10_2_ADC1 = SPI.transfer(0x00);
    SPI.endTransaction();
    digitalWrite(ADC1_CS, HIGH);
    //Acquisition Data ch0-ch8 ADC2 :
    SPI.beginTransaction(SPISettings(SPI_CLOCK_DIV2, MSBFIRST, SPI_MODE0)); 
    digitalWrite(ADC2_CS, LOW);
    //ch0 + requête ch1
    data_out_ch0_1_ADC2 = SPI.transfer(B00011100);
    data_out_ch0_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch1 + requête ch2
    data_out_ch1_1_ADC2 = SPI.transfer(B00101100);
    data_out_ch1_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch2 + requête ch3
    data_out_ch2_1_ADC2 = SPI.transfer(B00111100);
    data_out_ch2_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch3 + requête ch4
    data_out_ch3_1_ADC2 = SPI.transfer(B01001100);
    data_out_ch3_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch4 + requête ch5
    data_out_ch4_1_ADC2 = SPI.transfer(B01011100);
    data_out_ch4_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch5 + requête ch6
    data_out_ch5_1_ADC2 = SPI.transfer(B01101100);
    data_out_ch5_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch6 + requête ch7
    data_out_ch6_1_ADC2 = SPI.transfer(B01111100);
    data_out_ch6_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch7 + requête ch8
    data_out_ch7_1_ADC2 = SPI.transfer(B10001100);
    data_out_ch7_2_ADC2 = SPI.transfer(B00000000);
    delayMicroseconds(20);
    //ch8 + requête ch0
    data_out_ch8_1_ADC2 = SPI.transfer(0xA0 | 0x0C);
    data_out_ch8_2_ADC2 = SPI.transfer(0x00);

    delayMicroseconds(20);
    //ch8 + requête ch0
    data_out_ch10_1_ADC2 = SPI.transfer(0x00 | 0x0C);
    data_out_ch10_2_ADC2 = SPI.transfer(0x00);
    SPI.endTransaction();
    digitalWrite(ADC2_CS, HIGH);

    //Reconstruction de Data_OUT ADC1 :
    data_out_ch0_ADC1 = (data_out_ch0_1_ADC1 << 8) | data_out_ch0_2_ADC1;  //Reconstruction de Data_OUT (16 bits)
    data_out_ch0_ADC1 = data_out_ch0_ADC1 >> 4;                           //Suppression des 4 zéros de fin
    data_out_ch1_ADC1 = (data_out_ch1_1_ADC1 << 8) | data_out_ch1_2_ADC1;
    data_out_ch1_ADC1 = data_out_ch1_ADC1 >> 4;
    data_out_ch2_ADC1 = (data_out_ch2_1_ADC1 << 8) | data_out_ch2_2_ADC1;
    data_out_ch2_ADC1 = data_out_ch2_ADC1 >> 4;
    data_out_ch3_ADC1 = (data_out_ch3_1_ADC1 << 8) | data_out_ch3_2_ADC1;
    data_out_ch3_ADC1 = data_out_ch3_ADC1 >> 4;
    data_out_ch4_ADC1 = (data_out_ch4_1_ADC1 << 8) | data_out_ch4_2_ADC1;
    data_out_ch4_ADC1 = data_out_ch4_ADC1 >> 4;
    data_out_ch5_ADC1 = (data_out_ch5_1_ADC1 << 8) | data_out_ch5_2_ADC1;
    data_out_ch5_ADC1 = data_out_ch5_ADC1 >> 4;
    data_out_ch6_ADC1 = (data_out_ch6_1_ADC1 << 8) | data_out_ch6_2_ADC1;
    data_out_ch6_ADC1 = data_out_ch6_ADC1 >> 4;
    data_out_ch7_ADC1 = (data_out_ch7_1_ADC1 << 8) | data_out_ch7_2_ADC1;
    data_out_ch7_ADC1 = data_out_ch7_ADC1 >> 4;
    data_out_ch8_ADC1 = (data_out_ch8_1_ADC1 << 8) | data_out_ch8_2_ADC1;
    data_out_ch8_ADC1 = data_out_ch8_ADC1 >> 4;
    data_out_ch10_ADC1 = (data_out_ch10_1_ADC1 << 8) | data_out_ch10_2_ADC1;
    data_out_ch10_ADC1 = data_out_ch10_ADC1 >> 4;
    //Reconstruction de Data_OUT ADC2 :
    data_out_ch0_ADC2 = (data_out_ch0_1_ADC2 << 8) | data_out_ch0_2_ADC2;  //Reconstruction de Data_OUT (16 bits)
    data_out_ch0_ADC2 = data_out_ch0_ADC2 >> 4;                           //Suppression des 4 zéros de fin
    data_out_ch1_ADC2 = (data_out_ch1_1_ADC2 << 8) | data_out_ch1_2_ADC2;
    data_out_ch1_ADC2 = data_out_ch1_ADC2 >> 4;
    data_out_ch2_ADC2 = (data_out_ch2_1_ADC2 << 8) | data_out_ch2_2_ADC2;
    data_out_ch2_ADC2 = data_out_ch2_ADC2 >> 4;
    data_out_ch3_ADC2 = (data_out_ch3_1_ADC2 << 8) | data_out_ch3_2_ADC2;
    data_out_ch3_ADC2 = data_out_ch3_ADC2 >> 4;
    data_out_ch4_ADC2 = (data_out_ch4_1_ADC2 << 8) | data_out_ch4_2_ADC2;
    data_out_ch4_ADC2 = data_out_ch4_ADC2 >> 4;
    data_out_ch5_ADC2 = (data_out_ch5_1_ADC2 << 8) | data_out_ch5_2_ADC2;
    data_out_ch5_ADC2 = data_out_ch5_ADC2 >> 4;
    data_out_ch6_ADC2 = (data_out_ch6_1_ADC2 << 8) | data_out_ch6_2_ADC2;
    data_out_ch6_ADC2 = data_out_ch6_ADC2 >> 4;
    data_out_ch7_ADC2 = (data_out_ch7_1_ADC2 << 8) | data_out_ch7_2_ADC2;
    data_out_ch7_ADC2 = data_out_ch7_ADC2 >> 4;
    data_out_ch8_ADC2 = (data_out_ch8_1_ADC2 << 8) | data_out_ch8_2_ADC2;
    data_out_ch8_ADC2 = data_out_ch8_ADC2 >> 4;
    data_out_ch10_ADC2 = (data_out_ch10_1_ADC2 << 8) | data_out_ch10_2_ADC2;
    data_out_ch10_ADC2 = data_out_ch10_ADC2 >> 4;

        if(PRINT_MSG_SERIAL)
    {
      Serial.print("ADC1 Binaire : ");
      Serial.print(data_out_ch0_ADC1); Serial.print(' ');
      Serial.print(data_out_ch1_ADC1); Serial.print(' ');
      Serial.print(data_out_ch2_ADC1); Serial.print(' ');
      Serial.print(data_out_ch3_ADC1); Serial.print(' ');
      Serial.print(data_out_ch4_ADC1); Serial.print(' ');
      Serial.print(data_out_ch5_ADC1); Serial.print(' ');
      Serial.print(data_out_ch6_ADC1); Serial.print(' ');
      Serial.print(data_out_ch7_ADC1); Serial.print(' ');
      Serial.print(data_out_ch8_ADC1); Serial.print(' ');
      Serial.print(data_out_ch10_ADC1); Serial.println(' ');

      Serial.print("ADC2 Binaire : ");
      Serial.print(data_out_ch0_ADC2); Serial.print(' ');
      Serial.print(data_out_ch1_ADC2); Serial.print(' ');
      Serial.print(data_out_ch2_ADC2); Serial.print(' ');
      Serial.print(data_out_ch3_ADC2); Serial.print(' ');
      Serial.print(data_out_ch4_ADC2); Serial.print(' ');
      Serial.print(data_out_ch5_ADC2); Serial.print(' ');
      Serial.print(data_out_ch6_ADC2); Serial.print(' ');
      Serial.print(data_out_ch7_ADC2); Serial.print(' ');
      Serial.print(data_out_ch8_ADC2); Serial.print(' ');
      Serial.print(data_out_ch10_ADC2); Serial.println(' ');
      Serial.println("");
      //<<--------------------------------------------------->>//
    }

  adc1->data_out_ch0 = data_out_ch0_ADC1;
  adc1->data_out_ch1 = data_out_ch1_ADC1;
  adc1->data_out_ch2 = data_out_ch2_ADC1;
  adc1->data_out_ch3 = data_out_ch3_ADC1;
  adc1->data_out_ch4 = data_out_ch4_ADC1;
  adc1->data_out_ch5 = data_out_ch5_ADC1;
  adc1->data_out_ch6 = data_out_ch6_ADC1;
  adc1->data_out_ch7 = data_out_ch7_ADC1;
  adc1->data_out_ch8 = data_out_ch8_ADC1;
  adc1->data_out_ch10 = data_out_ch10_ADC1;

  adc2->data_out_ch0 = data_out_ch0_ADC2;
  adc2->data_out_ch1 = data_out_ch1_ADC2;
  adc2->data_out_ch2 = data_out_ch2_ADC2;
  adc2->data_out_ch3 = data_out_ch3_ADC2;
  adc2->data_out_ch4 = data_out_ch4_ADC2;
  adc2->data_out_ch5 = data_out_ch5_ADC2;
  adc2->data_out_ch6 = data_out_ch6_ADC2;
  adc2->data_out_ch7 = data_out_ch7_ADC2;
  adc2->data_out_ch8 = data_out_ch8_ADC2;
  adc2->data_out_ch10 = data_out_ch10_ADC2;

  tab_adc_brut_radio[0]=data_out_ch1_1_ADC1;
  tab_adc_brut_radio[1]=data_out_ch1_2_ADC1;
  tab_adc_brut_radio[2]=data_out_ch2_1_ADC1;
  tab_adc_brut_radio[3]=data_out_ch2_2_ADC1;

  tab_adc_brut_radio[4]=data_out_ch3_1_ADC1;
  tab_adc_brut_radio[5]=data_out_ch3_2_ADC1;
  tab_adc_brut_radio[6]=data_out_ch4_1_ADC1;
  tab_adc_brut_radio[7]=data_out_ch4_2_ADC1;

  tab_adc_brut_radio[8]=data_out_ch5_1_ADC1;
  tab_adc_brut_radio[9]=data_out_ch5_2_ADC1;
  tab_adc_brut_radio[10]=data_out_ch6_1_ADC1;
  tab_adc_brut_radio[11]=data_out_ch6_2_ADC1;

  tab_adc_brut_radio[12]=data_out_ch7_1_ADC1;
  tab_adc_brut_radio[13]=data_out_ch7_2_ADC1;
  tab_adc_brut_radio[14]=data_out_ch8_1_ADC1;
  tab_adc_brut_radio[15]=data_out_ch8_2_ADC1;


  tab_adc_brut_radio[16]=data_out_ch1_1_ADC2;
  tab_adc_brut_radio[17]=data_out_ch1_2_ADC2;
  tab_adc_brut_radio[18]=data_out_ch2_1_ADC2;
  tab_adc_brut_radio[19]=data_out_ch2_2_ADC2;

  tab_adc_brut_radio[20]=data_out_ch3_1_ADC2;
  tab_adc_brut_radio[21]=data_out_ch3_2_ADC2;
  tab_adc_brut_radio[22]=data_out_ch4_1_ADC2;
  tab_adc_brut_radio[23]=data_out_ch4_2_ADC2;

  tab_adc_brut_radio[24]=data_out_ch5_1_ADC2;
  tab_adc_brut_radio[25]=data_out_ch5_2_ADC2;
  tab_adc_brut_radio[26]=data_out_ch6_1_ADC2;
  tab_adc_brut_radio[27]=data_out_ch6_2_ADC2;

  tab_adc_brut_radio[28]=data_out_ch7_1_ADC2;
  tab_adc_brut_radio[29]=data_out_ch7_2_ADC2;
  tab_adc_brut_radio[30]=data_out_ch8_1_ADC2;
  tab_adc_brut_radio[31]=data_out_ch8_2_ADC2;

}
