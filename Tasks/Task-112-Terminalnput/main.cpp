#include "uop_msb.h"
using namespace uop_msb;

Buzzer buzz;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);


int main()
{
    int offDelay;
    int onDelay;
    
    printf("\nTASK-112\n");
    //scanf
    printf("\n\nTo set the off time in milliseconds, please enter an integer.\n");
    int offParsed = scanf("%d", &offDelay);
    printf("You entered %dms.\n",offDelay);
    

    printf("\n\nTo set the on time in milliseconds, please enter an integer.\n");
    int onParsed = scanf("%d", &onDelay);
    printf("You entered %dms\n",onDelay);

    // Stop
    while ((offParsed > 0)&&(onParsed>0)) {
        wait_us(offDelay * 1000);
        led1 = 1;
        led2 = 1;
        led3 = 1;
        wait_us(onDelay * 1000);
        led1 = 0;
        led2 = 0;
        led3 = 0;        
    } 

    printf("Invalid - please restart and try again\n");
    while(1);    
}