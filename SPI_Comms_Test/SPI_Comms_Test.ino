
//SPI COMMS TEST
#include <SPI.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("Serial Active")

}

void loop() {
  // put your main code here, to run repeatedly:


SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));

}
