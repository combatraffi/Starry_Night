

struct Twinkle_star {
    uint16_t brightval=255;
    uint16_t event_time;
    uint16_t start_time;
    uint16_t dimming_active=0;
}


Twinkle_star star[100];
int current_time;


void setup()
{


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
{
    int dimchoose=0;
    for (int i, i<101, i++)
    {
       
        dimchoose= random(0,10);
        if (dimchoose >= 4)
        {
            star[i].dimming_active = 1
            star[i].brightval = random(200, 255);
        }
        else
        {
            star[i].dimming_active = 0
            star[i].brightval = 255;
        }
    }
}

void set_eventtime():
{
int e_delay = 0
    for (int i, i<101, i++)
    {
        e_delay = random(0, 2500);
        star[i].event_time = millis()+e_delay;
    }
}