//TLC5955 Test Program
#include<SPI.h>

/* This program is intended to test the basic fuctionality of the TLC5955 chips
it should just command all LED to zero, up to full, back to zero and do a 10 second
fade in and out as a stretch goal */

/*  Communication with the chip is controlled through the SPI library.  Each LED can take a 16 bit greyscale value.
Max SPI comms freq = 25 Mhz, Max Greyscales Clock Rate = 33 Mhz.  I would like to use the same clock signal for both.
MOSI = SIN, SS = LAT, SCK = CLK

*/


int bright_command={4096};

void setup(){
    Serial.begin(115200);
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
}

void loop(){

send_data(bright_command);
delay(5000);
bright_command[0] = 0;
send_data(bright_command);
delay(5000);
bright_command[0] = 4096;
}

void send_data(data){
    //This funciton sends data via SPI to the TLC5955 Set
    SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
    digitalWrite(SS,LOW);
    SPI.transfer(data);
    digitalWrite(SS, HIGH);
    SPI.endTransaction();
}


