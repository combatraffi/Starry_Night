//Starry_Night_Board_Checkout.cpp
//#include<SPI.h>


byte lighting_command;
unsigned int pwm_register_set[] = {4096, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608, 4608} ; //I would like this to go into a library
unsigned int ss1 = 8;
unsigned int ss2 = 9;
unsigned int high_side_command = 256;
unsigned int cmd_set;





void setup()
{
  Serial1.begin(115200);
  Serial1.println("Ping");
  //SPI.begin();
  // SPI.setClockDivider(SPI_CLOCK_DIV8);//divide the clock by 8
  pinMode(ss1, OUTPUT);
  pinMode(ss2, OUTPUT);
  
}

void loop()
{
  //command 16 LEDs on on each set.

  high_side_command = 255;
  Serial1.println("Pong");
  for (int i; i < 16; i++)
  {

    //send_data(0, high_side_command);
    high_side_command << 1;
    delay(100);
    for (int j; j <= 16; j++)
    {
      //cmd_set = ;
      //send_data(1, build_command_set(j, 1, 255));
    }
  }
}
/*
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
*/
