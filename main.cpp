/*
UOY Year 1 PaDI Final Project
7 Segment Display System
Developed by Mark Imade
*/

#include "mbed.h"
#include "displaySystem.h"

InterruptIn buttonCustomText(A0); // customText function interrupt
InterruptIn buttonFirstName(A1); // first name function interrupt
InterruptIn buttonLastName(A2); // last Name function interrupt
InterruptIn buttonPrintDelay(BUTTON1);

// threads for each process
Thread customText;
Thread firstName;
Thread lastName;
Thread printDelay;

// semaphores for interrupts
Semaphore buttonCustomTextSemaphore(0, 1);
Semaphore buttonFirstNameSemaphore(0, 1);
Semaphore buttonLastNameSemaphore(0, 1);
Semaphore buttonPrintDelaySemaphore(0, 1);

// this mutex is specifically used to prevent the display from being used by multiple functions at the same time
Mutex processKey;

// initialize the display system class and set pins to corresponding led segments (in order from segment A to DP)
DisplaySystem newDisp(D1, D2, D3, D4, D5, D6, D7, D0);

// corresponding callback functions each releasing required semaphore 
void buttonCustomTextCallback() {
    buttonCustomTextSemaphore.release();
}

void buttonFNCallback() {
    buttonFirstNameSemaphore.release();
}

void buttonLNCallback() {
    buttonLastNameSemaphore.release();
}

void buttonPrintDelayCallback() {
    buttonPrintDelaySemaphore.release();
}

/* 
corresponding threads which are started upon bootup
the external while loop ensures they continually look for their required semaphore
the processKey mutex is first locked before the print method is called to ensure only one thing is being displayed on the 7 segment display at a time
after text is done displaying mutex is unlocked
*/
void customTextThread() {
    while(true) {
        buttonCustomTextSemaphore.acquire();
        processKey.lock();
        newDisp.print(newDisp.customText_);
        processKey.unlock();
    }
}

void firstNameThread() { 
    while(true) {
        buttonFirstNameSemaphore.acquire();
        processKey.lock();
        newDisp.print("osamu");
        processKey.unlock();
    }
}

void lastNameThread() {
    while(true) {
        buttonLastNameSemaphore.acquire();
        processKey.lock();
        newDisp.print("imade");
        processKey.unlock();
    }
}

// this thread is different because it does not display anything only alters timing
void buttonPrintDelayThread() {
    while (true) {
        buttonPrintDelaySemaphore.acquire();
        newDisp.setDelay();
    }
}


int main() {

    // start up threads
    customText.start(customTextThread);
    firstName.start(firstNameThread);
    lastName.start(lastNameThread);
    printDelay.start(buttonPrintDelayThread);
    
    // check for interrupts when a button is pressed and trigger corresponding callback functions
    buttonCustomText.fall(buttonCustomTextCallback);
    buttonFirstName.fall(buttonFNCallback);
    buttonLastName.fall(buttonLNCallback);
    buttonPrintDelay.fall(buttonPrintDelayCallback);

    // initial startup animation
    newDisp.startup();
}