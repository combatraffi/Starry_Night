//Starry_Night_Board_Checkout.cpp
#include<SPI.h>


byte lighting_command;
unsigned int pwm_register_set[] = {B0001000, B0001001, B0001010, B0001011, B0001100, B0001101, B0001110, B0001111, B0010000, B0010001, B0010010, B0010011, B0010100, B0010101, B0010110, B0010111} ; //I would like this to go into a library
unsigned int ss1, ss2;
unsigned int high_side_command = 256;
unsigned int cmd_set;


unsigned int build_command_set(unsigned int lednum, unsigned int readwrite, unsigned int command_val) {
  //this function takes command registers and combines them with commands to form an instruction set
  // command set for PCA9745B
  //readwrite = 1 = digitalWrite

  unsigned int regset = 0; //register construct
  unsigned int typebit;
  if (readwrite == 1)
  {
    typebit = 128;
  }
  else
  {
    typebit = 0;
  }
  regset = pwm_register_set[lednum];  //pulls the correct register from the LUT
  regset << 1;  //shift over one to add in the read/write bit
  regset = regset | typebit;  //add the read/write bit
  regset << 6;  //shift over to add value
  regset = regset | command_val;  //add in value (0-255)
  return (regset);
}


void setup()
{
  Serial.begin(115200);
  SPI.begin();
  // SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
  pinMode(ss1, OUTPUT);
  pinMode(ss2, OUTPUT);
}

void loop()
{
  //command 16 LEDs on on each set.

  delay(100);

  for (int i; i < 16; i++)
  {
    high_side_command << 1;
    send_data(0, high_side_command);
    delay(100);
    for (int j; j <= 16; j++)
    {
      //cmd_set = ;
      send_data(1, build_command_set(j, 1, 255));
    }
  }
}

void send_data(unsigned int target, unsigned int cmd)
{
  //This sends both high side and low side data
  //target value of 0 sends to high side, 1 to low side.
  //operationally that means changing the lat lines used
  Serial.println("Entered Send Data : "); //Send Serial Flag
  Serial.print("Command: ");
  Serial.print(cmd);
  Serial.println();
  if (target == 0) {
    digitalWrite(ss1, LOW);
  }
  else {
    digitalWrite(ss2, LOW);
  }
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  SPI.transfer(cmd);
  if (target == 0) {
    digitalWrite(ss1, HIGH);
  }
  else {
    digitalWrite(ss2, HIGH);
  }
  SPI.endTransaction();
}
