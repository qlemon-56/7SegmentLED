#include "mbed.h"
#include <map>
#include <array>

DigitalOut ledDP(D0); //segment DP
DigitalOut ledA(D1); //segment A
DigitalOut ledB(D2); //segment B
DigitalOut ledC(D3); //segment C
DigitalOut ledD(D4); //segment D
DigitalOut ledE(D5); //segment E
DigitalOut ledF(D6); //segment F
DigitalOut ledG(D7); //segment G

class DisplaySystem {
    
    char const * text;

    map<char, array<bool, 8>> characterSet;

    public:
    
    DisplaySystem(char const * text_g) {
        text = text_g;

        // power saving mode encoding
        characterSet[' '] = {false, false, false, false, false, false, false, false};
        characterSet['a'] = {true, true, false, false, false, true, false, false};
        characterSet['b'] = {false, false, true, true, false, true, true, false};
        characterSet['c'] = {true, false, false, false, false, true, true, false};
        characterSet['d'] = {false, true, false, true, true, false, true, false};
        characterSet['e'] = {true, false, false, true, false, false, true, false};
        characterSet['f'] = {true, false, false, false, true, false, true, false};
        characterSet['g'] = {false, false, true, true, false, false, true, true};
        characterSet['h'] = {false, false, true, false, true, true, true, false};
        characterSet['i'] = {false, false, false, false, true, false, false, true};
        characterSet['j'] = {false, false, true, true, false, false, false, true};
        characterSet['k'] = {false, false, false, false, true, true, true, true};
        characterSet['l'] = {false, false, false, true, true, false, false, false};
        characterSet['m'] = {true, false, true, false, true, false, false, false};
        characterSet['n'] = {false, false, true, false, false, false, true, false};
        characterSet['o'] = {true, true, false, false, false, true, true, false};
        characterSet['p'] = {true, true, false, false, true, false, true, false};
        characterSet['q'] = {true, false, true, false, false, true, true, false};
        characterSet['r'] = {false, false, false, false, true, false, true, false};
        characterSet['s'] = {true, false, true, true, false, false, true, false};
        characterSet['t'] = {true, false, false, false, true, true, false, false};
        characterSet['u'] = {false, false, true, true, true, false, false, false};
        characterSet['v'] = {false, false, true, true, true, false, false, true};
        characterSet['w'] = {false, true, false, false, false, true, true, true};
        characterSet['x'] = {false, true, true, false, true, true, false, false};
        characterSet['y'] = {false, false, true, false, false, true, true, true};
        characterSet['z'] = {true, true, false, true, false, false, true, true};
        characterSet['0'] = {true, true, true, true, true, true, false, false};
        characterSet['1'] = {false, true, true, false, false, false, false, false};    
        characterSet['2'] = {true, true, false, true, true, false, true, false};
        characterSet['3'] = {true, true, true, true, false, false, true, false};
        characterSet['4'] = {false, true, true, false, false, true, true, false};
        characterSet['5'] = {true, false, true, true, false, true, true, false};
        characterSet['6'] = {true, false, true, true, true, true, true, false};
        characterSet['7'] = {true, true, true, false, false, false, false, false};
        characterSet['8'] = {true, true, true, true, true, true, true, false};
        characterSet['9'] = {true, true, true, true, false, true, true, false};
        
    }
    
    void print() {
        
        int i = 0;
        while (text[i] != 0) {
            dispLetter(text[i]);
            
            i = i+1;
            thread_sleep_for(3000);
        }
    }
    
    void dispLetter(char letter) {
             
        ledA = characterSet[letter][0];
        ledB = characterSet[letter][1];
        ledC = characterSet[letter][2];
        ledD = characterSet[letter][3];
        ledE = characterSet[letter][4];
        ledF = characterSet[letter][5];
        ledG = characterSet[letter][6];
        ledDP = characterSet[letter][7];     
    }
};

int main() {

    DisplaySystem X("kenneth imade 9876543210");
    X.print();

    while (true) {sleep();}
}
