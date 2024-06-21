#include <SD.h>


int v, n = 0;
void setup() {
  while (!Serial);  //wait the user to open Serial Monitor 
    Serial.begin(9600);
  
}

void loop() {
  
  while(v != 100){
    v += 1;
    Serial.println(v);
  }
  v = 0;
  n += 1;
  
  if (n==2){
    Serial.println("Message non transmit");
    }
}
