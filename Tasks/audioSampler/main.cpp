#include "mbed.h"


// main() runs in its own thread in the OS
//Defining Inputs and Outputs
    DigitalIn upButton(PG_3,PinMode::PullDown);//Button D
    DigitalIn downButton(PG_1); // Button B
    AnalogIn mic(PA_3);
    DigitalOut ledStripEnable(PE_0);
    DigitalOut redLEDs(PE_12);
    DigitalOut grnLEDs(PE_13);
    DigitalOut blueLEDs(PE_14);
    BusOut leds(PE_2,PE_3,PE_4,PE_5,PE_6,PE_7,PE_8,PE_9);



void ledStripHeight(int);
float micLvl = 0.0;
//Conversion Functions & Variables
    int convertTo24(float);
    float scale = 0.4;


//LED Functions
    void redLatch();
    void grnLatch();
    void blueLatch();
    void ledClear();
    int waitTime = 100;//How long the LEDs are unlocked.
//Increment System
    void incrUp();
    void incrDown();
    float incrAmt = 0.01;
//Threads
    Thread upThread;
    Thread downThread;
    

int main()
{
    ledStripEnable = 0;
    upThread.start(incrUp);
    downThread.start(incrDown);
    while (true) {
        printf("Scale = %f\n",scale);
        micLvl = mic;
        ledStripHeight(convertTo24(micLvl));
        wait_us(10);
        ledClear();
    }
}

int convertTo24(float input){
    float i = 0;
    i = input-scale;
    i*=(1/(1-scale));
    i*=24;
    return static_cast<int>( i );
} // Converts an float from between 1 and zero to an integer between 0 and 24


void ledStripHeight(int num24){
    int tempNum24 = num24;
    if(tempNum24<=8){
        leds = pow(2,tempNum24)-1;
        redLatch();
    }
    else{
        leds = pow(2,8)-1;
        redLatch();
        tempNum24-=8;
        if(tempNum24<=8){
            leds = pow(2,tempNum24)-1;
            grnLatch();
        }
        else{
            leds = pow(2,8)-1;
            grnLatch();
            tempNum24-=8;
            leds = pow(2,tempNum24)-1;
            blueLatch();
            
        }
    }
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
void incrUp(){
    int uB;
    while(true){
        do{
            uB = upButton;
        }while(uB == 0);
        scale+=incrAmt;
        do{
            uB = upButton;
        }while( uB ==1);
    }
}
void incrDown(){
    int dB;
    while(true){
        do{
            dB = downButton;
        }while(dB == 0);
        scale-=incrAmt;
        do{
            dB = downButton;
        }while( dB ==1);
    }

}
