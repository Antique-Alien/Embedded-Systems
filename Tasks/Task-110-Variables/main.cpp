#include "uop_msb.h"
using namespace uop_msb;

Buzzer buzz;

PortOut LED_PORTE(PortE, LED_MASK);

DigitalOut LED_BAR_OE(LED_BAR_OE_PIN,1);      //Off by default
DigitalOut LED_DIGIT_OE(LED_DIGIT_OE_PIN,1);   //Off by default

DigitalOut LED_D1_LE(LED_D1_LE_PIN,0);
DigitalOut LED_D2_LE(LED_D2_LE_PIN,0);
DigitalOut LED_RED_LE(LED_RED_LE_PIN,0);
DigitalOut LED_GRN_LE(LED_GRN_LE_PIN,0);
DigitalOut LED_BLUE_LE(LED_BLUE_LE_PIN,0);

DigitalIn BlueButton(USER_BUTTON);

BusOut ledData(LED_D0_PIN, LED_D1_PIN, LED_D2_PIN, LED_D3_PIN, LED_D4_PIN, LED_D5_PIN, LED_D6_PIN, LED_D7_PIN);

int mode = 0;
int modeMax = 2;
void allOn();
void checkSwitch();


int main()
{
    printf("\nTASK-110\n");
    int count = 1;
    LED_BAR_OE = 0;

    
    while(true){
        if(mode == 0){
            while (count<128){
                printf("Count = %i\n",count);
                ledData = count;
                allOn();
                count*=2;
            }
            while(count>1){
                printf("Count = %i\n",count);
                ledData = count;
                allOn();
                count = count/2;
            }
        }
        else if(mode == 1){
            while(count<8){
                printf("Count = %i. ledData = %f \n",count,(pow(2,count)-1));
                ledData = pow(2,count)-1;
                allOn();
                count++;
            }
            count = 1;
            while(count<7){
                ledData = 256-pow(2,count);
                allOn();
                count++;
            }
            while(count>1){
                ledData = 256-pow(2,count);
                allOn();
                count--;
            }
            count = 8;

            while(count>1){
                printf("Count = %i. ledData = %f \n",count,(pow(2,count)-1));
                ledData = pow(2,count)-1;
                allOn();
                count--;
            }
        }
        else if(mode == 2){
            for(int i = 8; i>0; i--){
                count = 0;
                while(count<i){
                    ledData = 256-(pow(2,i))+pow(2,count);
                    allOn();
                    count++;
                }
            }
            for (int i = 0;i>8; i++){
                count = 8;
                while(count>i){
                    ledData = (pow(2,i)-1)+pow(2,count);
                    allOn();
                    count--;
                }
            }
        }

    }    
}

void allOn(){
    checkSwitch();
    LED_RED_LE = 1;
    LED_BLUE_LE = 1;
    LED_GRN_LE = 1;
    wait_us(100);
    LED_GRN_LE = 0;
    LED_RED_LE = 0;
    LED_BLUE_LE = 0;
    wait_us(100000);
}

void checkSwitch(){
    if(BlueButton){
        if(mode ==modeMax){
            mode = 0;
        }
        else{
            mode++;
        }
    }
}