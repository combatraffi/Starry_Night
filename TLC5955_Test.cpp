//TLC5955 Test Program
#include<SPI.h>

/* This program is intended to test the basic fuctionality of the TLC5955 chips
  it should just command all LED to zero, up to full, back to zero and do a 10 second
  fade in and out as a stretch goal */

/*  Communication with the chip is controlled through the SPI library.  Each LED can take a 16 bit greyscale value.
  Max SPI comms freq = 25 Mhz, Max Greyscales Clock Rate = 33 Mhz.  I would like to use the same clock signal for both.
  MOSI = SIN, SS = LAT, SCK = CLK

  I think a big considertation here is how to get an 8 bit byte turned into a 12 bit byte to send to the device.

*/

const unsigned int LED_QTY = 96;
unsigned int bright_command[LED_QTY];
int slaveselect = 7;    //I have this in here until I figuire out port commands.
//DDRB = DDRB | B00000001 //Should set Pin D8 to output?x

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
  pinMode(slaveselect, OUTPUT);
  pinMode(SS, OUTPUT);
}

void loop() {

  send_data();
  delay(500);
  set_bright_zero();
  send_data();
  delay(500);
  set_bright_max();
}

void send_data() {
  Serial.print("Entered Send Data : ");
  Serial.println(bright_command[0]);
  //This funciton sends data via SPI to the TLC5955 Set
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));  //1 Mhz should be more than fast enough for this application.
  //PORTB = B00000001 // This is intended to bring pin D8 HIGH
  digitalWrite(SS, LOW);
  digitalWrite(slaveselect, LOW);
  for (int j; j < LED_QTY; j++) {
    SPI.transfer16(bright_command[j]);
  }
  //PORTB = B00000000 // This is intended to bring pin D8 LOW
  digitalWrite(SS, HIGH);
  digitalWrite(slaveselect, HIGH);
  SPI.endTransaction();
}

void set_bright_zero() {
  for (int j; j < LED_QTY; j++) {
    bright_command[j] = 0;
  }

}

void set_bright_max() {
  for (int j; j < LED_QTY; j++) {
    bright_command[j] = 4000;
  }

}