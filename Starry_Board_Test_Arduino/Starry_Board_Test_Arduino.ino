//Starry_Night_Board_Checkout.cpp
#include<SPI.h>


byte lighting_command;
unsigned int pwm_register_set[] = {4096, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608} ; //I would like this to go into a library
unsigned int ss1 = 8;
unsigned int ss2 = 9;
unsigned int high_side_command = 1;
unsigned int cmd_set;





void setup()
{
  SerialUSB.begin(115200);
  SerialUSB.println("Ping");
  SPI.begin();
  // SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
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
  //readwrite = 1 = digitalWrite

  unsigned int regset = 0; //register construct
  unsigned int typebit;
  if (readwrite == 1)
  {
    typebit = 256;
  }
  else
  {
    typebit = 0;
  }
  regset = pwm_register_set[lednum];  //pulls the correct register from the LUT
  //regset = regset << 1;  //shift over one to add in the read/write bit
  regset += typebit;
  regset += command_val;
  regset = regset | typebit;  //add the read/write bit
  regset = regset << 6;  //shift over to add value
  regset = regset | command_val;  //add in value (0-255)
  return (regset);
}

void send_data(unsigned int target, unsigned int cmd)
{
  //This sends both high side and low side data
  //target value of 0 sends to high side, 1 to low side.
  //operationally that means changing the lat lines used
  //SerialUSB.println("Entered Send Data : "); //Send Serial Flag
  //SerialUSB.print("Command: ");
  // SerialUSB.print(cmd);
  // SerialUSB.println();
  if (target == 0) {
    digitalWrite(ss1, LOW);
  }
  else {
    digitalWrite(ss2, LOW);
  }
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  SPI.transfer(cmd);
  if (target == 0) {
    digitalWrite(ss1, HIGH);
  }
  else {
    digitalWrite(ss2, HIGH);
  }
  SPI.endTransaction();
}
