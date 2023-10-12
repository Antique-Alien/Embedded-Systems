#include "uop_msb.h"
using namespace uop_msb;

Buzzer Buzz;
Buttons button;

int e = 200000;
int f = e*2;
int h = e*4;
int w = e*8;
void lA(int);
void lB(int);
void lC(int);
void lD(int);
void lE(int);
void lF(int);
void lG(int);
void nA(int);
void nB(int);
void nC(int);
void nD(int);
void nE(int);
void nF(int);
void nG(int);
void hA(int);
void hB(int);
void hC(int);
void hD(int);
void hE(int);
void hF(int);
void hG(int);
void note(const char, int);
void rockyRoad();

// main() runs in its own thread in the OS
int main()
{
    while (true) {
        while(button.BlueButton ==0);
        

        
        rockyRoad();



    }
}
void lowNote(const char* note, int time){
    Buzz.playTone(note,Buzz.LOWER_OCTAVE);
    wait_us(time);
    Buzz.rest();
    wait_us(10000);
}
void note(const char* note, int time){
    Buzz.playTone(note);
    wait_us(time);
    Buzz.rest();
    wait_us(10000);
}
void highNote(const char* note, int time){
    Buzz.playTone(note,Buzz.HIGHER_OCTAVE);
    wait_us(time);
    Buzz.rest();
    wait_us(10000);
}

void lA(int timer){
    lowNote("A",timer);
}
void lB(int timer){
    lowNote("B",timer);
}
void lC(int timer){
    lowNote("C",timer);
}
void lD(int timer){
    lowNote("D",timer);
}
void lE(int timer){
    lowNote("E",timer);
}
void lF(int timer){
    lowNote("F",timer);
}
void lG(int timer){
    lowNote("A",timer);
}
void nA(int timer){
    note("A",timer);
}
void nB(int timer){
    note("B",timer);
}
void nC(int timer){
    note("C",timer);
}
void nD(int timer){
    note("D",timer);
}
void nE(int timer){
    note("E",timer);
}
void nF(int timer){
    note("F",timer);
}
void nG(int timer){
    note("A",timer);
}
void hA(int timer){
    highNote("A",timer);
}
void hB(int timer){
    highNote("B",timer);
}
void hC(int timer){
    highNote("C",timer);
}
void hD(int timer){
    highNote("D",timer);
}
void hE(int timer){
    highNote("E",timer);
}
void hF(int timer){
    highNote("F",timer);
}
void hG(int timer){
    highNote("A",timer);
}
void rockyRoad(){
    hA(e);
    hA(f);
    hA(e);
    //first group
    hA(f);
    hA(e);
    nG(f);
    nE(e);
    //second group
    nD(f);
    nD(e);
    nA(f);
    nD(e);
    //Third Group
    nD(f);
    nD(e);
    nD(e);
    nE(e);
    nG(e);
    //Fourth Group
    hA(f);
    nF(e);
    nG(f);
    nE(e);
    //Fifth Group;
    nD(f);
    nF(e);
    

}

