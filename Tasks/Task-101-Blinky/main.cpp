#include "mbed.h"

// Create a DigitalOut “object” called greenLED. Pass constant LED1 as a “parameter”
DigitalOut greenLED(LED1);
DigitalOut blueLED(LED2);
DigitalOut redLED (LED3);

//The amount of time waited while each LED is lit
int waitTime = 100000;


//These are "commented out" and so are not part of the program. You can uncomment them by removing the // characters
//Your task is to make a sequence alternating between Green+Red and just Blue 


//The main function - all executable C / C++ applications have a main function. This is our entry point in the software
int main() 
{
    // ALL the repeating code is contained in a  “while loop”
    while(true)
    { 
        //The code between the { curly braces } is the code that is repeated forever

        // Turn on green & red LEDs  
        greenLED = 1;
        redLED = 1;
        // Turn off blue LED
        blueLED = 0;

        // Wait
        wait_us(waitTime); 

        // Turn red & green LEDs off
        greenLED = 0;
        redLED = 0;
        // Turn blue LED on
        blueLED = 1;

        // Wait 
        wait_us(waitTime); 
    }
    
}