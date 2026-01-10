#include "mbed.h"
#include "displaySystem.h"

/*
ledA(D1); segment A
ledB(D2); segment B
ledC(D3); segment C
ledD(D4); segment D
ledE(D5); segment E
ledF(D6); segment F
ledG(D7); segment G
ledDP(D0); segment DP
*/

// displaySystem constructor accepts 8 DigitalOut pins as arguments to control segments A to DP
DisplaySystem::DisplaySystem(PinName ledA, PinName ledB, PinName ledC, PinName ledD, PinName ledE, PinName ledF, PinName ledG, PinName ledDP) : ledA_(ledA), ledB_(ledB), ledC_(ledC), ledD_(ledD), ledE_(ledE), ledF_(ledF), ledG_(ledG), ledDP_(ledDP) {

    // here we add chars a-z, space ' ', and 0-9 in power saving mode encoding to characterSet (Each bool defines the state of each led segment)
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

// definition of startup method
void DisplaySystem::startup() {

    // ledArray used here for simplicity
    DigitalOut ledArray[6] = {ledA_, ledB_, ledC_, ledD_, ledE_, ledF_};

    // the outer loop repeats the animation sequence
    for (int x = 0; x < 4; x++) {

        // inner loop sets the leds on and off in sequence
        // it iterates over the ledArray altering the value of each segment at each cycle to make a simple animation
        for (int i = 0; i < 6; i++) {
            
            ledArray[i] = true;
            thread_sleep_for(150);
            ledArray[i] = false;
        
        }
    }
    
    // after animation we print the following text to serial monitor and wait for user response
    printf("Would you like to display some custom text? \nEnter y/n: ");
    scanf("%c", &setCustomTextOption_);

    if (setCustomTextOption_ == 'y') {

        // if input is y print the following then set customText using scanf
        printf("\nEnter text:\n(20 character limit, only numbers and lowercase letters)");
        scanf("%s", customText_);
        printf("\nText set as: %s", customText_ );

    } else if (setCustomTextOption_ == 'n') {

        // if input is n print the following
        printf("Okay no custom text set.");

    } else {

        // handles any input other than y or n
        printf("Invalid option. No custom text set.");
    
    }
}

// print method simply iterates over a string literal and passes each char as an argument to displayChar method
void DisplaySystem::print(char const * text_) {
    
    // print function displays a sequence of letters on the 7 segment display when called (displayChar method does the heavylifting)
    int i = 0;
    while (text_[i] != 0) {
        
        // displetter function is used to display each character one by one
        displayChar(text_[i]);
        i = i+1;
        thread_sleep_for(timer_);
    }
    
    // clears display after printing by turning all segments off
    ledA_ = false;
    ledB_ = false;
    ledC_ = false;
    ledD_ = false;
    ledE_ = false;
    ledF_ = false;
    ledG_ = false;
    ledDP_ = false;  

};

// displayChar method looks up the value of the given char in the characterSet map then sets each led to the appropriate state
void DisplaySystem::displayChar(char letter_) {
    ledA_ = characterSet[letter_][0];
    ledB_ = characterSet[letter_][1];
    ledC_ = characterSet[letter_][2];
    ledD_ = characterSet[letter_][3];
    ledE_ = characterSet[letter_][4];
    ledF_ = characterSet[letter_][5];
    ledG_ = characterSet[letter_][6];
    ledDP_ = characterSet[letter_][7];     
};

// setDelay method alters inter-character display time
void DisplaySystem::setDelay() {

    // this function is triggered whenever blue button is pressed (button1)
    // the if statement below checks if the timer is less than 3s, if yes it increments it by 1 second up until it hits 3 seconds then it resets
    if (timer_ < 3000) {
        timer_ = timer_ + 1000;
    } else {
        timer_ = 1000;
    }
}