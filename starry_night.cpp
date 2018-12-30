
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
dimming_set[16];    //instruction set for dimmer chip
int current_time;
unsigned int comspeed = 3000000;    //Sets the SPI communication speed
int output_enable = 6;  //output enable pin LOW ENABLE, triggers both chips






void setup()
{
pinMode(output_enable, INPUT);

Serial.begin(115200);


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

void send_data(int chipsel)
//This function sends instructions to both 74HC595's and the PCA9745B over SPI
{
  digitalWrite(chipsel,LOW);
  SPI.beginTransaction(SPISettings(comspeed, MSBFIRST, SPI_MODE0));  //3 Mhz should be more than fast enough for this application.
    SPI.transfer16(lighting_command);
  digitalWrite(chipsel, HIGH);
  SPI.endTransaction();
}

void construct_dim_command(){





    
}

uint16_t build_dimset (){






}

