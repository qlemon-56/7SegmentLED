#pragma once
#include "mbed.h"
#include <map>
#include <array>

class DisplaySystem {
    
    // timer variable controlling space between successive characters being displayed
    int timer_ = 1000;

    // yes or no option to input custom text when prompted at startup
    char setCustomTextOption_;

    // hashmap which contains keys of type char and values of type bool array of size 8
    map<char, array<bool, 8>> characterSet;

    // digitalOut pins for each led segment
    DigitalOut ledA_;
    DigitalOut ledB_;
    DigitalOut ledC_;
    DigitalOut ledD_;
    DigitalOut ledE_;
    DigitalOut ledF_;
    DigitalOut ledG_;
    DigitalOut ledDP_;
    
    public:
    
    // variable which holds custom text set by user
    char customText_[21];

    // constructor to initialize a variable of class DisplaySystem
    DisplaySystem(PinName ledA, PinName ledB, PinName ledC, PinName ledD, PinName ledE, PinName ledF, PinName ledG, PinName ledDP);
    
    // startup method which sets custom text and displays animation
    void startup();

    // print method passes each char as argument to displayChar method
    void print(char const * text_);

    // displayChar method sets each led segment to appropriate state 
    void displayChar(char letter_);

    // setDelay method is trigger when button1 is press and alters inter-character delay
    void setDelay();
};
