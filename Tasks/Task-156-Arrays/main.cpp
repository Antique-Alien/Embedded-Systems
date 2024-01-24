#include "uop_msb.h"
#include <chrono>
#include <cstdint>
using namespace uop_msb;
using namespace chrono;

//Output
DigitalOut redLED(TRAF_RED1_PIN);
DigitalOut yellowLED(TRAF_YEL1_PIN);
DigitalOut greenLED(TRAF_GRN1_PIN);

//Analogue Inputs
AnalogIn ldr(AN_LDR_PIN);
Buzzer buzz;

enum {OFF = 0, ON} state;


int main()
{
    double samples[100];

    for (unsigned int m=0; m<100; m++) {
        double ldrVal   = ldr.read_u16();
        samples[m] = ldrVal;
        printf("%f ", samples[m]);
    }

    // Automatic headlamp 
    while (true) {

        for (unsigned int m=0; m<99; m++) {
            samples[m] = samples[m+1];
        }
        {
            double ldrVal   = ldr.read_u16();
            samples[99] = ldrVal;
            wait_us(1000000);          // 1000ms

        }
        double sum = 0;
        for(unsigned int i = 0; i< 100; i++){
            sum+=samples[i];
        }
        printf("Total = %f\n", sum );
        printf("Average of Samples = %f\n", sum/100);
        switch (state){
            case OFF:
                if(sum/100>45000){
                    greenLED = 1;
                    state = ON;
                }
                break;
            case ON:
                if(sum/100<30000){
                    greenLED = 0;
                    state = OFF;
                }
                break;
            default:
                break;


        }


        // TASK a. Calculate the average value in samples

        // TASK b. Display to 1dp

        // TASK c. Switch green LED on when dark;

    }  
}


