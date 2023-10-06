#include "mbed.h"

// main() runs in its own thread in the OS

DigitalOut rLED (PC_2);
DigitalOut yLED (PC_3);
DigitalOut gLED (PC_6);

void trafficSignal();

int main()
{
    while (true) {
        trafficSignal();
    }
}


void trafficSignal(){
    int ticTime = 500000;
    rLED = 1;
    yLED = 0;
    gLED = 0;
    wait_us(ticTime*4);
    yLED = 1;
    wait_us(ticTime*4);
    rLED = 0;
    yLED = 0;
    gLED = 1;
    wait_us(ticTime*4);
    gLED = 0;
    for (int i = 0; i<8; i++){
        yLED = !yLED;
        wait_us(ticTime/2);
    }
    yLED = 0;
}

