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
    void intputButtons();
    void calculateChange();
//End of Functions

//Defining inputs & outputs
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
    
    //Button IO
        DigitalIn aButton(PG_0);
        DigitalIn bButton(PG_1);
        DigitalIn cButton(PG_2, PinMode::PullDown);
        DigitalIn dButton(PG_3, PinMode::PullDown);
    //End Buttion IO
    
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
    volatile int shipAngle = 6;
    volatile int enginePower = 0;
    volatile int hSpeed = 2000;
    volatile int vSpeed = 0;
    volatile int altitude = 20000;
    volatile int fuel = 2400;
//End of Game Variables

//Threads
    Thread lcdDisplay;
    Thread LEDDisplay;
    Thread calc;
//End of Threads

//Control Functions
    int btnA;
    int btnB;
    int btnC;
    int btnD;    
    void engineUp();
    void engineDown();
    void rotClock();
    void rotCountClock();
    void inputButtons();

// End Control Functions


//LED Output Functions
    void LEDOutputs();

    //LED Bar Functions
        void LEDALL(bool);
        void enableStrip();
    //End of LED Bar Functions

    //LED Matrix Functions

        int shipAnglePic1[8][2] = {{0,0},{192,1},{64,1},{192,1},{160,2},{16,4},{16,4},{0,0}}; // Vertical Rocket (90)
        int shipAnglePic2[8][2] = {{0,0},{128,1},{112,1},{200,0},{160,0},{128,0},{64,0},{0,0}}; // 45 degrees
        int shipAnglePic3[8][2] = {{0,0},{32,0},{192,0},{0,7},{128,5},{0,7},{192,0},{32,0}}; // 0 degrees
        int shipAnglePic4[8][2] = {{0,0},{0,4},{0,8},{0,10},{128,12},{0,23},{0,8},{0,0}}; //315 degrees
        int shipAnglePic5[8][2] = {{0,0},{64,16},{128,8},{128,10},{0,7},{0,5},{0,7},{0,0}}; // 270 degrees
        int shipAnglePic6[8][2] = {{0,0},{0,1},{128,0},{128,2},{128,9},{64,7},{128,0},{0,0}};//225
        int shipAnglePic7[8][2] = {{0,0},{0,8},{0,6},{192,1},{64,3},{192,1},{0,6},{0,8}};//180
        int shipAnglePic8[8][2] = {{0,0},{128,0},{64,7},{128,9},{128,2},{128,0},{0,1},{0,0}};//135
        void matrixPrint(int[8][2]);
    
    //End LED Matrix Functions


//End LED Output Functions


//LCD Screen Display Functions
    void displaySpeedAndAltitude();
//End LCD Screen Display Functions




void test();


int main()
{
    //Set up actions




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


        //LED Display Initialisation
            //Seven Segment Display Set Up
                pwrDisplay.enable(true);
                printf("Engines: GO\n");

            //End Seven Segment Display Set Up
            //Set Up Fuel Systems
                enableStrip();
                printf("Fuel Systems: GO\n");
            //End Fuel System set up
            
            
            //Set up Angle Display
                printf("Angle System Display: GO\n");
                LEDDisplay.start(LEDOutputs);
            //End Angle System set up
               


        //End LED Display Initialisation


        //Control Initialisation
            printf("Control Systems: GO\n");
        // End Control Initialisation

        //Calculation Initialisation
            calc.start(calculateChange);
            printf("Computers: NO GO\n");

        //End Calculation Iniitialisation
    //End set up Actions


    while(true){
        inputButtons();
        //test();
    }
}

void test(){
    fuel--;
    vSpeed++;
    hSpeed++;
    altitude--;
    shipAngle++;
    if(shipAngle>8){
        shipAngle = 1;
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
    wait_us(40000);
    printf("Ship Angle: %d\n", shipAngle);
    


}

void calculateChange(){
    while(true){
        fuel-=enginePower;
        if(fuel>0){    
            switch(shipAngle){
                case 1:
                    vSpeed -=enginePower*2;
                    break;
                case 2:
                    vSpeed -= enginePower*0.707*2;
                    hSpeed += enginePower*0.707*2;
                    break;
                case 3:
                    hSpeed+=enginePower*2;
                    break;
                case 4:
                    vSpeed += enginePower*0.707*2;
                    hSpeed += enginePower*0.707*2;
                
                    break;
                case 5:
                    vSpeed +=enginePower*2;
                    break;
                case 6:
                    vSpeed += enginePower*0.707*2;
                    hSpeed -= enginePower*0.707*2;
                    break;
                case 7:
                    hSpeed-=enginePower*2;

                    break;
                case 8:
                    vSpeed -= enginePower*0.707*2;
                    hSpeed -= enginePower*0.707*2;
                    break;
                default:
                    break;

            }
        }
        altitude+=vSpeed;
        vSpeed-=1;

        wait_us(10000);

    }
}

//LED Outputs
    void LEDOutputs(){
        while(true){
            //LED Matrix Output
                switch(shipAngle){
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
            //End LED Matrix Display

            //Seven Segment Display Output

                pwrDisplay.write(enginePower);


            //End Seven Segment Display Output

            //LED Strip Output
                if(floor(fuel/10)>160){
                    LEDALL(true);
                    redStrip.write(255);
                    grnStrip.write(255);
                    blueStrip.write(pow(2,((fuel-1600)/100))-1);
                    LEDALL(false);
                
                }else if(floor(fuel/10)<=160 && floor(fuel/10) >80){
                    LEDALL(true);
                    blueStrip.write(0);
                    redStrip.write(255);
                    grnStrip.write(pow(2,((fuel-800)/100))-1);
                    LEDALL(false);

                }else {
                    LEDALL(true);
                    grnStrip.write(0);
                    blueStrip.write(0);
                    redStrip.write(pow(2,(fuel/1000))-1);
                    LEDALL(false);
                }


            //End LED Strip Output
        }
    }



//End LED Output 

//LED Matrix Functions
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


//Control Functions

    void engineUp(){
        enginePower++;
        if(enginePower>10){
            enginePower = 10;
        }
    }
    void engineDown(){
        enginePower--;
        if(enginePower<0){
            enginePower = 0;
        }

    }
    void rotClock(){
        shipAngle+=1;
        if(shipAngle>8){
            shipAngle=1;
        }

    }
    void rotCountClock(){
        shipAngle-=1;
        if(shipAngle<1){
            shipAngle=8;
        }

    }
    void inputButtons(){
        btnA = aButton;
        btnB = bButton;
        btnC = cButton;
        btnD = dButton;
        if(btnC == 1){
            printf("Rotated Counter Clockwise\n");
            rotCountClock();
        }else if(btnA == 1){
            printf("Rotated Clockwise\n");
            rotClock();
        }else if(btnB == 1){
            engineDown();
        }else if(btnD == 1){
            engineUp();
        }

        wait_us(200);
        while(btnA == 1 || btnB == 1 || btnC == 1 || btnD == 1){
            btnA = aButton;
            btnB = bButton;
            btnC = cButton;
            btnD = dButton;
            
        
        }

    }



//End Control Functions

//LED Functions
    void enableStrip(){
        redStrip.enable(true);
        grnStrip.enable(true);
        blueStrip.enable(true);
    }

    void LEDALL(bool var){
        redStrip.enable(var);
        blueStrip.enable(var);
        grnStrip.enable(var);
    }

//End of LED functions
