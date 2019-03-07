//Starry_Night_Board_Checkout.cpp
#include<SPI.h>
#include "wiring_private.h" // pinPeripheral() function this is for the SeR

byte lighting_command;
unsigned int pwm_register_set[] = {4096, 4608, 5120, 5632, 6144, 6656, 7168, 7680, 8192, 8704, 9216, 9728, 10240, 10752, 11264, 11776} ; //I would like this to go into a library
unsigned int ss1 = 8;
unsigned int ss2 = 9;
unsigned int high_side_command = 1; //initial shift reg cmd
unsigned int cmd_set;



SPIClass SPI2 (&sercom2, 3, 5, 4, SPI_PAD_0_SCK_3, SERCOM_RX_PAD_1);


void setup()
{
  SerialUSB.begin(115200);
  SerialUSB.println("Ping");
  SPI2.begin();
  // SPI2.setClockDivider(SPI2_CLOCK_DIV8);//divide the clock by 8
  pinMode(ss1, OUTPUT);
  pinMode(ss2, OUTPUT);

}

void loop()
{
  //command 16 LEDs on on each set.
  SerialUSB.println("Ping");
  high_side_command = 1;

  for (int i = 0; i < 16; i++)
  {
    SerialUSB.println("Pong");
    send_data(0, high_side_command);
    SerialUSB.print("High Command: ");
    SerialUSB.println(high_side_command);
    high_side_command = high_side_command << 1;
    delay(100);
    for (int j = 0; j <= 16; j++)
    {
      SerialUSB.print("Low Command: ");
      SerialUSB.println(build_command_set(j, 1, 255));
      //cmd_set = ;
      send_data(1, build_command_set(j, 1, 255));
    }
  }
}

unsigned int build_command_set(unsigned int lednum, unsigned int readwrite, unsigned int command_val) {
  //this function takes command registers and combines them with commands to form an instruction set
  // command set for PCA9745B
  //readwrite = 1 = write

  unsigned int regset = 0; //register container, returned value
  unsigned int typebit;
  if (readwrite == 1)
  {
    typebit = 256;
  }
  else
  {
    typebit = 0;
  }
  regset = pwm_register_set[lednum];  //pulls the correct register from the LUT  //regset = regset << 1;  //shift over one to add in the read/write bit
  regset += typebit;
  regset += command_val;
  return (regset);
}

void send_data(unsigned int target, unsigned int cmd)
{
  //This function can send both high side and low side data
  //target value of 0 sends to high side, 1 to low side.
  //operationally that means changing the lat lines used
  SerialUSB.println("Entered Send Data : "); //Send Serial Flag
  SerialUSB.print("Command: ");
  SerialUSB.println(cmd);
  if (target == 0) {
    digitalWrite(ss1, LOW);
  }
  else {
    digitalWrite(ss2, LOW);
  }
  SPI2.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  SPI2.transfer16(cmd);
  if (target == 0) {
    digitalWrite(ss1, HIGH);
  }
  else {
    digitalWrite(ss2, HIGH);
  }
  SPI2.endTransaction();
}
