#pragma once
#include "mbed.h"
#include <map>
#include <array>

class DisplaySystem {
    
    // timer variable controlling space between successive characters being displayed
    int timer_ = 1000;

    // hashmap which contains keys of type char and values of type bool array of size 8
    map<char, array<bool, 8>> characterSet;

    // digitalOut pins for each led segment
    DigitalOut ledA_, ledB_, ledC_, ledD_,ledE_, ledF_, ledG_, ledDP_;
    
    public:
    
    // constructor to initialize a variable of class DisplaySystem
    DisplaySystem(PinName ledA, PinName ledB, PinName ledC, PinName ledD, PinName ledE, PinName ledF, PinName ledG, PinName ledDP);

     // variable which holds custom text set by user
    char customText_[21];

    // yes or no option to input custom text when prompted at startup
    char setCustomTextOption_;

    // startup method which displays animation and calls setCustomText method
    void startup();

    // print method passes each char as argument to displayChar method
    void print(char const * text_);

    // displayChar method sets each led segment to appropriate state 
    void displayChar(char letter_);

    // setDelay method is trigger when button1 is press and alters inter-character delay
    void setDelay();

    // setCustomText method is used to store custom text to be displayed
    void setCustomText();
};
