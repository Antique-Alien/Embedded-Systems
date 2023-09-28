// You need this to use the Module Support Board
#include "uop_msb.h"
using namespace uop_msb;

#define dotTime 150000 
DigitalOut greenLED(TRAF_GRN1_PIN);
DigitalOut gLED(LED1);
DigitalOut rLED(LED3);
DigitalOut bLED(LED2);
Buzzer buzz;
Buttons buttons;

void startUp();
void bitBreak();
void letterBreak();
void wordBreak();
void dot();
void dash();
void S();
void O();


// TIP: (I suggest you read this!)
//
// Press the black reset button to restart the code (and stop the sound)
// Otherwise, the noise can be "distracting" :)

int main()
{

    
    startUp();
    //Wait for the BLUE button to be pressed (otherwise this becomes super annoying!)
    while (buttons.BlueButton == 0);
    
    //Repeat everything "forever" (until the power is removed or the chip is reset)
    while (true)
    {
       S();
       O();
       S();
       wordBreak();

    }
}

void startUp(){
    gLED = 1;
    wait_us(300000);
    bLED = 1;
    wait_us(300000);    
    rLED = 1;
    wait_us(300000);    
    gLED = 0;
    bLED = 0;
    rLED = 0;
}
void bitBreak(){
    greenLED = 0;
    buzz.rest();
    wait_us(dotTime);
}
void letterBreak(
){
    wait_us(dotTime*2);
}
void wordBreak(){
    wait_us(dotTime*3);
}
void dot(){
    greenLED = 1;
    buzz.playTone("C");
    wait_us(dotTime);
    bitBreak();
}
void dash(){
    greenLED = 1;
    buzz.playTone("C");
    wait_us(dotTime*3);
    bitBreak();
}
void S(){
    dot();
    dot();
    dot();
    letterBreak();
}
void O(){
    dash();
    dash();
    dash();
    letterBreak();
}