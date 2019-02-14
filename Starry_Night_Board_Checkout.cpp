//Starry_Night_Board_Checkout.cpp
#include<SPI.h>


byte lighting_command;
int pwm_register_set[]={B0001000, B0001001, B0001010,}  //I would like this to go into a library

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
  high_side_command = B0000000000000001;  //recall that these are 16 bit signalss
  delay(100);

  for (int i, i<16, i++)
  {
    high_side_command << 1;
    send_data(0, high_side_command);
    delay(100);
    for(int j; j<=16, j++)
    {
        send_data(1, build_command_set(j, 1, 255));
    }
  }
}

void send_data(int target, int cmd) {
    //This sends both high side and low side data
    //target value of 0 sends to high side, 1 to low side.
      //operationally that means changing the lat lines used
  Serial.println("Entered Send Data : "); //Send Serial Flag
  Serial.print("Command: ");
  Serial.print(cmd);
  Serial.println();
  if (target ==0){}
    digitalWrite(ss1, LOW);
  }
  else{
    digitalWrite(ss2, LOW)
  }
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
  SPI.transfer(cmd);
  if (target ==0){}
    digitalWrite(ss1, HIGH);
  }
  else{
    digitalWrite(ss2, HIGH)
  }
  SPI.endTransaction();
}


int build_command_set(int lednum, int readwrite, int command_val){
    //this function takes command registers and combines them with commands to form an instruction set
    // command set for PCA9745B
    int regset=0;
    int typebit;
    if (readwrite ==1){
        typebit = B0000000100000000;
    }
    else {

        typebit = 0;
    }
    regset = pwm_register_set[lednum];
    regset << 1;
    regset = regset | typebit;
    regset << 6;
    regset = regset | command_val;
    return(regset)
}
