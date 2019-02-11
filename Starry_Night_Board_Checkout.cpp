//Starry_Night_Board_Checkout.cpp
#include<SPI.h>


byte lighting_command;

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  // SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
  pinMode(SS1, OUTPUT);
  pinMode(SS2, OUTPUT);
}

void loop()
{
    //command 16 LEDs on on each set.
    high_side_command = B0000000000000001;  //recall that these are 16 bit signals
    low_side_command = B1111111111111111
    send_data();
    delay(100);

    for(int i; i<=16, i++){
        high_side_command << 1;
        send_data();
        delay(100);
    }
}

void send_data(uint_16t cmd1, uint_16t cmd2) {
    //This sends both high side and low side data
  Serial.print("Entered Send Data : "); //Send Serial Flag
  Serial.println(lighting_command);  //Send Serial Flag
  digitalWrite(SS, LOW);
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  SPI.transfer(lighting_command);
  digitalWrite(SS, HIGH);
  SPI.endTransaction();
}