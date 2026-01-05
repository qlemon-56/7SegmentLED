#include "mbed.h"
#include "displaySystem.h"

InterruptIn buttonA(A0); // Display animation function interrupt
InterruptIn buttonFN(A1); // first name function interrupt
InterruptIn buttonLN(A2); // last Name function interrupt

// threads for each process
Thread animation;
Thread firstName;
Thread lastName;

// semaphores for interrupts
Semaphore buttonASemaphore(0, 1);
Semaphore buttonFNSemaphore(0, 1);
Semaphore buttonLNSemaphore(0, 1);

// this prevents clash
Mutex processKey;

int execution = 0;

// Initialize the display system class and set pins to corresponding led segments
DisplaySystem newDisp(D1, D2, D3, D4, D5, D6, D7, D0);

// corresponding callback functions
void buttonACallback() {
    buttonASemaphore.release();
}

void buttonFNCallback() {
    buttonFNSemaphore.release();
}

void buttonLNCallback() {
    buttonLNSemaphore.release();
}

// corresponding threads
void animationThread() {

    while(true) {

        buttonASemaphore.acquire();
        thread_sleep_for(100);

        processKey.lock();
        newDisp.startup();
        processKey.unlock();

    }
}

void firstNameThread() {

    while(true) {
        
        buttonFNSemaphore.acquire();
        thread_sleep_for(100);
        processKey.lock();
        newDisp.print("osamu");
        processKey.unlock();
    }
}

void lastNameThread() {

    while(true) {

        buttonLNSemaphore.acquire();
        thread_sleep_for(100);
        processKey.lock();
        newDisp.print("imade");
        processKey.unlock();

    }
}

int main() {

    // Start up threads
    animation.start(animationThread);
    firstName.start(firstNameThread);
    lastName.start(lastNameThread);
    
    // Check for interrupts and call corresponding callback functions
    buttonA.fall(buttonACallback);
    buttonFN.fall(buttonFNCallback);
    buttonLN.fall(buttonLNCallback);

    // initial startup animation
    newDisp.startup();

}
