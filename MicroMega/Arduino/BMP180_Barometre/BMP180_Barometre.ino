///////////////////////////////////////////////////////////////////////////////////////////
// BMP388_DEV - SPI Communications, Default Configuration, Normal Conversion, Interrupts
///////////////////////////////////////////////////////////////////////////////////////////

#include <BMP388_DEV.h>                             // Include the BMP388_DEV.h library

volatile boolean dataReady = false;                  // Define the data ready flag
volatile float temperature, pressure, altitude;     // Declare the measurement variables

BMP388_DEV bmp388(10);                              // Instantiate (create) a BMP388_DEV object and set-up for SPI operation on digital pin D10

void setup() 
{
  Serial.begin(115200);                             // Initialise the serial port
  bmp388.begin();                                   // Default initialisation, place the BMP388 into SLEEP_MODE 
  bmp388.enableInterrupt();                         // Enable the BMP388's interrupt (INT) pin
  bmp388.usingInterrupt(digitalPinToInterrupt(2));  // Invoke the SPI usingInterrupt() function
  attachInterrupt(digitalPinToInterrupt(2), interruptHandler, RISING);   // Set interrupt to call interruptHandler function on D2
  bmp388.setTimeStandby(TIME_STANDBY_1280MS);       // Set the standby time to 1.3 seconds
  bmp388.startNormalConversion();                   // Start BMP388 continuous conversion in NORMAL_MODE 
}

void loop() 
{
  if (dataReady)                                    // Check if the measurement is complete
  {   
    dataReady = false;                              // Clear the data ready flag
    Serial.print(temperature);                      // Display the results    
    Serial.print(F("*C   "));
    Serial.print(pressure);    
    Serial.print(F("hPa   "));
    Serial.print(altitude);
    Serial.println(F("m"));  
  }
}

void interruptHandler()                             // Interrupt handler function
{
  bmp388.getMeasurements(temperature, pressure, altitude);    // Read the measurement data
  dataReady = true;                                 // Set the data ready flag
}
