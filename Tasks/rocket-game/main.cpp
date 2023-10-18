#include "mbed.h"

// main() runs in its own thread in the OS

/*
The goal of the game is to land your moon lander safely on the moon, with a horizontal speed near zero, and a vertical speed of slow. If you run out of fuel, then you will accelerate downward until you crash.
The data you have: Your fuel level (RBG LED bar), your altitude, your horizontal speed, and your vertical speed.
Your altitude and speeds can be displayed on the LCD screen.

The inputs you have: Your angle, and the rate of burning. 
your angle is shown by a crude picture of your rocket on the LED matrix. Your angle is displayed on the LED number Display.

There will need to be a couple threads running. The main thread will be running the Inputs, allowing the button presses to be converted into chnages in the angle and power of the engines
This thread will also check victory conditions (If Ship is upright, if horizongal speed is near zero, if vertical speed is near zero)

A thread will run, displaying the current Power (LED Numbers)

A thread will show the Altitude and Speeds (LCD Display)
A thread will show the fuel levels (RBG Bar)
A thread will show the angle of the ship


*/
//Functions
    void displayFuelLevel();
    void displayShipAngle();
    void displayEnginePower();
    void displaySpeedAndAltitude();
    void getInputs();
//End of Functions

//Defining inputs & outputs
    //Button IO
        DigitalIn aButton(PG_0);
        DigitalIn bButton(PG_1);
        DigitalIn cButton(PG_2, PinMode::PullDown);
        DigitalIn dButton(PG_3, PinMode::PullDown);
    //End Buttion IO
    //LED Strip IO
        DigitalOut ledStripEnable(PE_0);
        DigitalOut redLEDs(PE_12);
        DigitalOut grnLEDs(PE_13);
        DigitalOut blueLEDs(PE_14);
        BusOut leds(PE_2,PE_3,PE_4,PE_5,PE_6,PE_7,PE_8,PE_9);
    //End LED Strip IO
    //LED Matrix IO


    //End LED Matrix IO
// End of Inputs

//Game Variables
    int shipAngle;
    int enginePower;
    int hSpeed;
    int vSpeed;
    int altitude;
    volatile int fuel = 240;
//End of Game Variables

//Threads
    Thread ledStrip;

//End of Threads

//LED Bar Functions
    void allFull();
    void redLatch();
    void grnLatch();
    void blueLatch();
    void ledClear();
    void blueClear();
    void redClear();
    void grnClear();
    int waitTime = 100;//How long the LEDs are unlocked.
//End of LED Bar Functions

//LED Matrix Functions
    int shipAnglePic1[2][8] = [[000,000],
                                [192,001],
                                [064,001],
                                [192,001],
                                [160,002],
                                [016,004],
                                [016,004],
                                [000,000]];
    int shipAnglePic2[8];
    int shipAnglePic3[8];
    int shipAnglePic4[8];
    int shipAnglePic5[8];
    int shipAnglePic6[8];
    int shipAnglePic7[8];
    int shipAnglePic8[8];
    void encodeShipPic(int, int*);
    void displayShipAngle();
    
//End LED Matrix Functions


int main()
{
    //Set up actions

        //Set Up Fuel Systems
            ledStripEnable = 0;
            ledStrip.start(displayFuelLevel);
        //End Fuel System set up


    //End set up Actions
    while (true) {
                

    }
}
void displayFuelLevel(){
    allFull();
    while (true){
        if(fuel>160){
            leds = 255;
            redLatch();
            grnLatch();
            leds = pow(2,((fuel-160)/10))-1;
            blueLatch();
        }
        if(fuel<=160 && fuel >80){
            leds = 0;
            blueLatch();
            leds = pow(2,((fuel-80)/10))-1;
            grnLatch();
        }
        if(fuel<=80){
            leds = 0;
            blueLatch();
            grnLatch();
            leds = pow(2,(fuel/10))-1;
            redLatch();
        }
    }


}

//LED Bar Functions
    void allFull(){
        leds = 255;
        redLatch();
        grnLatch();
        blueLatch();
    }
    void redLatch(){
        redLEDs = 1;
        wait_us(waitTime);
        redLEDs = 0;
    }
    void grnLatch(){
        grnLEDs = 1;
        wait_us(waitTime);
        grnLEDs = 0;
    }
    void blueLatch(){
        blueLEDs = 1;
        wait_us(waitTime);
        blueLEDs = 0;
    }
    void ledClear(){
        leds = 0;
        redLatch();
        grnLatch();
        blueLatch();
    }
    void blueClear(){
        leds = 0;
        blueLatch();
    }
    void redClear(){
        leds = 0;
        redLatch();
    }
    void grnClear(){
        leds = 0;
        grnLatch();
    }
//End of LED functions


//LED Matrix Functions
    void encodeShipPic(int shipPic[8][16], int* shipPicVar[8]){
        for(int i = 0; i<8; i++){
            for(int j = 0; j<16; j++){
                *shipPicVar[i] += pow(2,j*shipPic[i][j]);

            }

        }
        

    }

//End LED Matrix Functions
