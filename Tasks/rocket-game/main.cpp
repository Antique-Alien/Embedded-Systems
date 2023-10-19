#include "mbed.h"
//#include "F429_Mega_Shell_Header.h"
#include "uop_msb.h"
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
        uop_msb::LatchedLED redStrip(uop_msb::LatchedLED::STRIP,uop_msb::LatchedLED::RED);
        uop_msb::LatchedLED grnStrip(uop_msb::LatchedLED::STRIP,uop_msb::LatchedLED::GREEN);
        uop_msb::LatchedLED blueStrip(uop_msb::LatchedLED::STRIP,uop_msb::LatchedLED::BLUE);
        
        //DigitalOut ledStripEnable(PE_0);
        //DigitalOut redLEDs(PE_12);
        //DigitalOut grnLEDs(PE_13);
        //DigitalOut blueLEDs(PE_14);
        //BusOut leds(PE_2,PE_3,PE_4,PE_5,PE_6,PE_7,PE_8,PE_9);
        
    //End LED Strip IO
    //LED Matrix IO
        SPI spi(PC_12, PC_11, PC_10);   // MOSI, MISO, SCLK
        DigitalOut cs(PB_6);            //Chip Select ACTIVE LOW
        DigitalOut oe(PB_12);           //Output Enable ACTIVE LOW
    //End LED Matrix IO

    //LCD IO
        uop_msb::LCD_16X2_DISPLAY lcd;
    //End LCD IO

    //7 seg IO
        uop_msb::LatchedLED pwrDisplay(uop_msb::LatchedLED::SEVEN_SEG);
    //End 7 seg IO

// End of Inputs

//Game Variables
    volatile int shipAngle = 0;
    volatile int enginePower = 0;
    volatile int hSpeed = 0;
    volatile int vSpeed = 0;
    volatile int altitude = 5000;
    volatile int fuel = 240;
//End of Game Variables

//Threads
    Thread ledStrip;
    Thread ledMatrix;
    Thread lcdDisplay;
    Thread sevenSegDisplay;

//End of Threads

//LED Bar Functions
    void displayFuelLevel();
    void LEDALL(bool);
    /*
    void allFull();
    void redLatch();
    void grnLatch();
    void blueLatch();
    void ledClear();
    void blueClear();
    void redClear();
    void grnClear();
    int waitTime = 100;//How long the LEDs are unlocked.
    */
//End of LED Bar Functions

//LED Matrix Functions
    int shipDisplayAngle = 0;
    int pastShipDisplayAngle = 0;

    int shipAnglePic1[8][2] = {{0,0},{192,1},{64,1},{192,1},{160,2},{16,4},{16,4},{0,0}}; // Vertical Rocket (90)
    int shipAnglePic2[8][2] = {{0,0},{128,1},{112,1},{200,0},{160,0},{128,0},{64,0},{0,0}}; // 45 degrees
    int shipAnglePic3[8][2] = {{0,0},{32,0},{192,0},{0,7},{128,5},{0,7},{192,0},{32,0}}; // 0 degrees
    int shipAnglePic4[8][2] = {{0,0},{0,4},{0,8},{0,10},{128,12},{0,23},{0,8},{0,0}}; //315 degrees
    int shipAnglePic5[8][2] = {{0,0},{64,16},{128,8},{128,10},{0,7},{0,5},{0,7},{0,0}}; // 270 degrees
    int shipAnglePic6[8][2] = {{0,0},{0,1},{128,0},{128,2},{128,9},{64,7},{128,0},{0,0}};//225
    int shipAnglePic7[8][2] = {{0,0},{0,8},{0,6},{192,1},{64,3},{192,1},{0,6},{0,8}};//180
    int shipAnglePic8[8][2] = {{0,0},{128,0},{64,7},{128,9},{128,2},{128,0},{0,1},{0,0}};//135
    void displayShipAngle();
    void matrixPrint(int[8][2]);
    
//End LED Matrix Functions

//LCD Screen Display Functions
    void displaySpeedAndAltitude();
//End LCD Screen Display Functions

//Seven Segment Display Functions
    void displayEnginePower();
//End Seven Segment Display Functions

void test();



int main()
{
    //Set up actions

        //Set Up Fuel Systems
            redStrip.enable(true);
            grnStrip.enable(true);
            blueStrip.enable(true);
            ledStrip.start(displayFuelLevel);
            printf("Fuel Systems: NO GO\n");
        //End Fuel System set up
        
        //Set up Angle Display
            ledMatrix.start(displayShipAngle);
            printf("Angle System Display: GO\n");
        //End Angle System set up
        
        //LCD Screen Set up
            lcd.locate(0,0);
            lcd.printf("VS:");
            lcd.locate(0,8);
            lcd.printf("HS:");
            lcd.locate(1,0);
            lcd.printf("Alt:");
            lcdDisplay.start(displaySpeedAndAltitude);
            printf("Velocity Display System: GO\n");
        //End LCD Screen Set Up

        //Seven Segment Display Set Up
            pwrDisplay.enable(true);
            sevenSegDisplay.start(displayEnginePower);
            printf("Engines: GO\n");

        //End Seven Segment Display Set Up

    //End set up Actions
    while(true){
        test();
    }
}

void test(){
    shipAngle++;
    fuel--;
    vSpeed++;
    hSpeed++;
    altitude--;
    enginePower++;
    if(shipAngle>359){
        shipAngle = 0;
    }
    if(fuel<0){
        fuel = 240;
    }
    if(vSpeed> 99){
        vSpeed = -99;
    }
        if(hSpeed> 99){
        hSpeed = -99;
    }
    if(altitude<0){
        altitude = 5000;
    }
    if(enginePower>99){
        enginePower = 0;
    }
    wait_us(2000);


}




//LED Bar Functions
    void displayFuelLevel(){
        //allFull();
        redStrip.write(255);
        grnStrip.write(255);
        blueStrip.write(255);
        while (true){
            if(fuel>160){
                LEDALL(true);
                redStrip.write(255);
                grnStrip.write(255);
                blueStrip.write(pow(2,((fuel-160)/10))-1);
                LEDALL(false);
                /*
                leds = 255;
                redLatch();
                grnLatch();
                leds = pow(2,((fuel-160)/10))-1;
                blueLatch();
                */
            }
            if(fuel<=160 && fuel >80){
                LEDALL(true);
                blueStrip.write(0);
                redStrip.write(255);
                grnStrip.write(pow(2,((fuel-80)/10))-1);
                LEDALL(false);

                
                /*
                leds = 0;
                blueLatch();
                leds = pow(2,((fuel-80)/10))-1;
                grnLatch();
                */
            }
            if(fuel<=80){
                LEDALL(true);
                grnStrip.write(0);
                blueStrip.write(0);
                redStrip.write(pow(2,(fuel/10))-1);
                LEDALL(false);
                /*
                leds = 0;
                blueLatch();
                grnLatch();
                leds = pow(2,(fuel/10))-1;
                redLatch();
                */
            }
        }   
    }
    void LEDALL(bool var){
        redStrip.enable(var);
        blueStrip.enable(var);
        grnStrip.enable(var);
    }
    /*
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
    */
//End of LED functions


//LED Matrix Functions
    void displayShipAngle(){
        
        while(true){
            pastShipDisplayAngle = shipDisplayAngle;
            if(shipAngle<22 || shipAngle>=337){
               shipDisplayAngle = 3;
            }
            if(shipAngle<67 && shipAngle>=22){
               shipDisplayAngle = 2;
            }
            if(shipAngle<112 && shipAngle>=67){
               shipDisplayAngle = 1;
            }
            if(shipAngle<157 && shipAngle>=112){
               shipDisplayAngle = 8;
            }           
            if(shipAngle<202 && shipAngle>=157){
               shipDisplayAngle = 7;
            }           
            if(shipAngle<247 && shipAngle>=202){
               shipDisplayAngle = 6;
            }           
            if(shipAngle<292 && shipAngle>=247){
               shipDisplayAngle = 5;
            }           
            if(shipAngle<337 && shipAngle>=292){
               shipDisplayAngle = 4;
            }
            switch(shipDisplayAngle){
                case 1:
                    matrixPrint(shipAnglePic1);
                    break;
                case 2:
                    matrixPrint(shipAnglePic2);
                    break;
                case 3:
                    matrixPrint(shipAnglePic3);
                    break;
                case 4:
                    matrixPrint(shipAnglePic4);
                    break;
                case 5:
                    matrixPrint(shipAnglePic5);
                    break;
                case 6:
                    matrixPrint(shipAnglePic6);
                    break;
                case 7:
                    matrixPrint(shipAnglePic7);
                    break;
                case 8:
                    matrixPrint(shipAnglePic8);
                    break;
                default:
                    matrixPrint(shipAnglePic1);
                    break;
                
                }  
        }
    }
    void matrixPrint(int picNum[8][2]){


        
        for(int i = 7; i>-1; i--){
            cs = 0;
            spi.write(picNum[i][1]); // RHS Write
            spi.write(picNum[i][0]); // LHS write
            spi.write(i); // Row Write
            cs = 1;            
        }
        
        
        

    }
//End LED Matrix Functions


//LCD Display Functions
    void displaySpeedAndAltitude(){
        while(true){
            lcd.locate(0,4);
            lcd.printf("%d ",vSpeed);
            lcd.locate(0,12);
            lcd.printf("%d ",hSpeed);
            lcd.locate(1,5);
            lcd.printf("%d ",altitude);

        }

    }


//End LCD Display Functions


//Seven Segment Display Functions
    void displayEnginePower(){
        while(true){
            pwrDisplay.write(enginePower);
        }
    }

//End Seven Segment Display Functions