#include "FloorButton.h"

FloorButton::FloorButton(int flNum, string dir) {
    floorNum = flNum;
    direction = dir;
    on = false;
}
FloorButton::~FloorButton() {}

void FloorButton::switch_on() {
    cout << direction << " Button " << "has lit up on Floor #" 
    << floorNum << ".\n" << endl;
    on = true;
}
void FloorButton::switch_off() {
    cout << direction << " Button " << "has turned off on Floor #" 
    << floorNum << ".\n" << endl;
    on = false;
}

bool FloorButton::isOn() { return on; }
