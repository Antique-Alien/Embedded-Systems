#include "uop_msb.h"
using namespace uop_msb;

#define secTime 1000000 

DigitalOut red(TRAF_RED1_PIN,1);         //Note the initial state
DigitalOut amber(TRAF_YEL1_PIN,0);
DigitalOut green(TRAF_GRN1_PIN,0);

LCD_16X2_DISPLAY lcd;

void redLight();
void redYellowLight();
void greenLight();
void yellowLight();

int main()
{

    while(true){
        redLight();
        wait_us(10*secTime);

        redYellowLight();
        wait_us(2*secTime);

        greenLight();    
        wait_us(10*secTime);

        yellowLight();
        wait_us(200000);
    }

}


void redLight(){
    red = 1;
    amber = 0;
    green = 0;
    lcd.cls();
    lcd.puts("Stop");
}
void redYellowLight(){
    red = 1;
    amber = 1;
    green = 0;
    lcd.cls();
    lcd.puts("Ready");
}
void greenLight(){
    red = 0;
    amber = 0;
    green = 1;
    lcd.cls();
    lcd.puts("Go!");
}
void yellowLight(){
    red = 0;
    amber = 1;
    green = 0;
    lcd.cls();
    lcd.puts("Hurry up");
}