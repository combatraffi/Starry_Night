//TLC5955 Test Program
#include<SPI.h>

/* This program is intended to test the basic fuctionality of the TLC5955 chips
it should just command all LED to zero, up to full, back to zero and do a 10 second
fade in and out as a stretch goal */

/*  Communication with the chip is controlled through the SPI library.  Each LED can take a 16 bit greyscale value.



*/



void setup(){
    Serial.begin(115200);
    SPI.begin();



}

void loop(){





}