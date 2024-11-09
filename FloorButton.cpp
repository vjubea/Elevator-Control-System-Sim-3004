#include "FloorButton.h"

FloorButton::FloorButton(int flNum, string dir) {
    direction = dir;
    isOn = false;
    floorNum = flNum;
}
FloorButton::~FloorButton() {}

void FloorButton::switch_on() {
    cout << direction << " Button " << "has lit up on Floor #" 
    << floorNum << ".\n" << endl;
    isOn = true;
}
void FloorButton::switch_off() {
    cout << direction << " Button " << "has turned off on Floor #" 
    << floorNum << ".\n" << endl;
    isOn = false;
}
