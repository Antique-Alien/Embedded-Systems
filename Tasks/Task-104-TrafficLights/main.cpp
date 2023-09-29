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
        

        redYellowLight();


        greenLight();    


        yellowLight();

    }

}


void redLight(){
    red = 1;
    amber = 0;
    green = 0;
    lcd.cls();
    lcd.puts("Stop");
    wait_us(10*secTime);
}
void redYellowLight(){
    red = 1;
    amber = 1;
    green = 0;
    lcd.cls();
    lcd.puts("Ready");
    wait_us(2*secTime);
}
void greenLight(){
    red = 0;
    amber = 0;
    green = 1;
    lcd.cls();
    lcd.puts("Go!");
    wait_us(10*secTime);
}
void yellowLight(){
    red = 0;
    green = 0;
    lcd.cls();
    lcd.puts("Hurry up");
    
    for(int i = 0; i<4; i++){
        amber = 1;
        wait_us(secTime/4);
        amber = 0;
        wait_us(secTime/4);

    }
    
    
}