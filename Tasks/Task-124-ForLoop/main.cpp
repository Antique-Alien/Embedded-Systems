#include "mbed.h"
#include "myutils.hpp"
// DigitalOut redLED(PC_2,0);
// DigitalOut yellowLED(PC_3,0);
// DigitalOut greenLED(PC_6,0);
BusOut leds(PC_2, PC_3, PC_6);


// main() runs in its own thread in the OS
int main()
{
    int delay = 0, count = 0, pattern = 0, check = 0;
    printf("Press Enter to start.");

    while (true) {
        do{
            check = 0;
            flushInputBuffer();
            printf("\n\nInput count between 5 and 20, inclusive\n");
            check = scanf("%d",&count);



        }while( (check<1) || (count < 5 ) || (count >20) );
        printf("\nCount = %d",count);
        do{
            check = 0;
            flushInputBuffer();
            printf("\n\nInput pattern between 0 and 7, inclusive\n");
            check = scanf("%d",&pattern);



        }while( (check<1) || (pattern < 0 ) || (pattern >7) );
        printf("Pattern = %d",pattern);
        
        do{
            check = 0;
            flushInputBuffer();
            printf("\n\nInput delay between 50 and 2000, inclusive\n");
            check = scanf("%d",&delay);



        }while( (check<1) || (delay < 50 ) || (delay >2000) );
        printf("\nDelay = %dms",delay);
        //For-Loop
        for(int i = 0; i<count; i++){
            for(int j = 0; j<pattern; j++){
                leds = j;
                wait_us(delay*1000);
            }

        }

        //2s pause
        wait_us(2000000);
    }
}

