
//THINGS TO DO IN THIS SCRIPT
    //Create Event Controller
    //Create SPI Comms Function that can send to either chipset AND send variable commands
    //


//activate low side with 0-15 brightness control pulled form star array
//



//This is a script to twinkle approximately 100 stars (0402 LED's)
struct Twinkle_star {
    //This class carries status information for the LED's
    //The intent is that these will be updated through and _array
    //of star objects.
    uint16_t brightval=255;
    uint16_t event_time;
    uint16_t start_time;
    uint16_t dimming_active=0;
}


Twinkle_star star[100]; //Stars array
uint16_t dimming_set[16];    //instruction set for dimmer chip
unsigned int current_time;
unsigned int comspeed = 3000000;    //Sets the SPI communication speed DONT KNOW IF THIS NEEDS TO BE HERE
int output_enable = 6;  //output enable pin LOW ENABLE, triggers both chips






void setup()
{
pinMode(output_enable, INPUT);

SerialUSB.begin(115200);


pinmode(3, OUTPUT);
}


void loop()
{
    current_time = millis();

    for (int j, j<=101; j++)
    {
        if (star[j].event_time <= current_time)
        {
            set_brightness();
            set_eventtime();
        }
    }
}


void set_brightness()
//This function sets the brightness to a value other than maximum
//approximately 40% of the time.  Dimming value is randomized.
{
    int dimchoose=0;
    for (int i, i<101, i++)
    {

        dimchoose= random(0,10);
        if (dimchoose >= 4)
        {
            star[i].dimming_active = 1;
            star[i].brightval = random(200, 255);
        }
        else
        {
            star[i].dimming_active = 0;
            star[i].brightval = 255;
        }
    }
}

void set_eventtime():
//This function sets the ammount of time to remain dimmed.
//It is randomized between 0 and 1/4 seconds.
{
int e_delay = 0
    for (int i, i<101, i++)
    {
        e_delay = random(0, 250);
        star[i].event_time = millis()+e_delay;
    }
}



void construct_dim_command(){
    //This function updates the array which holds 16 dimming commands
    for(int i=0;i<8;i++){

        dimming_set[i]=build_dimset[i];

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
  regset = pwm_register_set[lednum];  //pulls the correct register from the LUT
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
