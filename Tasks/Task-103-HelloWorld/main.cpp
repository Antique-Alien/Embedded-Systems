#include "uop_msb.h"
using namespace uop_msb;

#define WAIT_TIME_MS 1000

//Initialise the DigitalOut objects with a default value of 1
DigitalOut gLED(LED1,1);
DigitalOut bLED(LED2,1);
DigitalOut rLED(LED3,1);

LCD_16X2_DISPLAY lcd;

void startUp();


int main()
{
    // Write to serial terminal on host PC
    startUp();


    // Clear the LCD screen
    lcd.cls();

    //Small pause for 1s
    wait_us(1000 * WAIT_TIME_MS);

    //Turn off all the LEDs
    rLED = 0;
    gLED = 0;
    bLED = 0;

    // Write to LCD using the LCD_16X2_DISPLAY driver class
    lcd.printf("Hello World");
    lcd.locate(1, 0);   //Row 1, Col 0
    lcd.printf("Proj 100");

    // This is a variable (not an object as it has no functions) that stores a whole number (integer) in memory
    // (I used the keyword volatile to force it to use memory... long story and one for later)
    volatile int counter = 0;
    wait_us(WAIT_TIME_MS*1000);
    lcd.locate(1,0);
    lcd.printf("Count: ");
    while (counter < 10)
    {
        //Toggle the LED
        bLED = !bLED;
        gLED = !gLED;
        rLED = !rLED;

        //Add 1 to the counter "variable"
        counter = counter + 1;

        //Display in the terminal
        lcd.locate(1,7);
        lcd.printf("%d", counter);

        //Wait
        wait_us(WAIT_TIME_MS * 1000);
    }
}

void startUp(){
    gLED = 0;
    rLED = 0;
    bLED = 0;
    wait_us(100000);
    gLED = 1;
    wait_us(100000);
    bLED = 1;
    wait_us(100000);    
    rLED = 1;
    wait_us(100000);    
    gLED = 0;
    bLED = 0;
    rLED = 0;
}
