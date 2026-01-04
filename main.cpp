#include "mbed.h"
#include "displaySystem.h"


int main() {

    DisplaySystem newDisp(D1, D2, D3, D4, D5, D6, D7, D0);

    newDisp.print("testing abcdefghijklmnopqrstuvwxyz 0123456789");

    while (true) {sleep();}
}
