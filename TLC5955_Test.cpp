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
int gsignal = 3;    //I have this in here until I figuire out port commands.
//DDRB = DDRB | B00000001 //Should set Pin D8 to output?x

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
  pinMode(gsignal, OUTPUT);
  pinMode(SS, OUTPUT);
  analogWrite(gsignal, 127);
  set_bright_max();
  //send_data();
  delay(10000);
}

void loop() {


  delay(500);
  set_bright_zero();
  send_data();
  delay(500);
  set_bright_max();
  send_data();
}

void send_data() {
    //This function writes data to the GS shift register to control brightness
  Serial.print("Entered Send Data : ");
  Serial.println(bright_command[0]);
  //This funciton sends data via SPI to the TLC5955 Set
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  //PORTB = B00000001 // This is intended to bring pin D8 HIGH
  digitalWrite(SS, LOW);

  for (int j; j < LED_QTY; j++) {
    SPI.transfer16(bright_command[j]);
  }
  //PORTB = B00000000 // This is intended to bring pin D8 LOW
  digitalWrite(SS, HIGH);

  SPI.endTransaction();
}

void set_bright_zero() {
    //This function sets all LED brighntesses to zero
  for (int j; j < LED_QTY; j++) {
    bright_command[j] = 0;
  }

}

void set_bright_max() {
    //This function sets all LED brightnesses to maximum (16 bit 65535)
  for (int j; j < LED_QTY; j++) {
    bright_command[j] = 65534;
  }

}

void display_brightness_array() {
  for (int j; j < LED_QTY; j++) {
    Serial.print(bright_command[j]);
    Serial.print(',');
  }
  Serial.println();
}

void draino(){
    //This function clears out random vars in the 595 upon powerup.



}

void send_init_settings(){
    //This function sets the TLC5955 to its init settings 
  SPI.beginTransaction(SPISettings(3000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  //PORTB = B00000001 // This is intended to bring pin D8 HIGH
  digitalWrite(SS, LOW);





  //PORTB = B00000000 // This is intended to bring pin D8 LOW
  digitalWrite(SS, HIGH);

  SPI.endTransaction();



}
