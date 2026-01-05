#include "mbed.h"
#include "displaySystem.h"

/*
ledDP(D0); segment DP
ledA(D1); segment A
ledB(D2); segment B
ledC(D3); segment C
ledD(D4); segment D
ledE(D5); segment E
ledF(D6); segment F
ledG(D7); segment G
*/

DisplaySystem::DisplaySystem(PinName ledA, PinName ledB, PinName ledC, PinName ledD, PinName ledE, PinName ledF, PinName ledG, PinName ledDP) : ledA_(ledA), ledB_(ledB), ledC_(ledC), ledD_(ledD), ledE_(ledE), ledF_(ledF), ledG_(ledG), ledDP_(ledDP) {

    // default timer
    timer_ = 1000;

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

void DisplaySystem::startup() {

    // ledArray used here for simplification
    DigitalOut ledArray[6] = {ledA_, ledB_, ledC_, ledD_, ledE_, ledF_};

    // inner loop sets the leds on and off in sequence, while the outer loop repeats the animation sequence
    for (int x = 0; x < 4; x++) {

        for (int i = 0; i < 6; i++) {
            
            ledArray[i] = true;
            thread_sleep_for(150);
            ledArray[i] = false;
        
        }
    }
}

void DisplaySystem::print(char const * text_) {
    
    // print function displays a sequence of letters on the 7 segment display
    int i = 0;
    while (text_[i] != 0) {

        // displetter function is used to display each character one by one
        dispLetter(text_[i]);
        
        i = i+1;
        thread_sleep_for(timer_);
    }
    
    // clears display after printing
    ledA_ = false;
    ledB_ = false;
    ledC_ = false;
    ledD_ = false;
    ledE_ = false;
    ledF_ = false;
    ledG_ = false;
    ledDP_ = false;  

};

void DisplaySystem::dispLetter(char letter_) {

    // this function looks up the value of the given letter in the characterSet map then sets each led to the appropriate state         
    
    ledA_ = characterSet[letter_][0];
    ledB_ = characterSet[letter_][1];
    ledC_ = characterSet[letter_][2];
    ledD_ = characterSet[letter_][3];
    ledE_ = characterSet[letter_][4];
    ledF_ = characterSet[letter_][5];
    ledG_ = characterSet[letter_][6];
    ledDP_ = characterSet[letter_][7];     
};

