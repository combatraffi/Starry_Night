#include<spi.h>


byte lighting_command;

void setup()
{
Serial.begin(115200);

SPI.begin();
 SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
 pinMode(SS, OUTPUT);  




}

void loop(){
    
lighting_command = 255;
send_data();
delay(500);
lighting_command = 0;
send_data();
delay(500);






}

void send_data() {

  Serial.print("Entered Send Data : "); //Send Serial Flag
  Serial.println(lighting_command);  //Send Serial Flag
  digitalWrite(SS,LOW);
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
    SPI.transfer(lighting_command);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
}
