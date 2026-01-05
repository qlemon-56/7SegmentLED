#pragma once
#include "mbed.h"
#include <map>
#include <array>

class DisplaySystem {
    
    int timer_;

    map<char, array<bool, 8>> characterSet;

    DigitalOut ledA_;
    DigitalOut ledB_;
    DigitalOut ledC_;
    DigitalOut ledD_;
    DigitalOut ledE_;
    DigitalOut ledF_;
    DigitalOut ledG_;
    DigitalOut ledDP_;
    
    public:
    
    DisplaySystem(PinName ledA, PinName ledB, PinName ledC, PinName ledD, PinName ledE, PinName ledF, PinName ledG, PinName ledDP);
    
    void startup();

    void print(char const * text_);
    
    void dispLetter(char letter_);

};
