#include "ElevatorDestButton.h"

ElevatorDestButton::ElevatorDestButton(int floorN, int elN) {
    floorNum = floorN;
    elNum = elN;
    isOn = false;
}
ElevatorDestButton::~ElevatorDestButton() {}

void ElevatorDestButton::on() {
    cout << "Floor #" << floorNum
    << " Destination Button is toggled ON in Elevator #"<< elNum
    << ".\n" << endl;
    isOn = true;
}
void ElevatorDestButton::off() {
    cout << "Floor #" << floorNum
    << " Destination Button is toggled OFF in Elevator #"<< elNum
    << ".\n" << endl;
    isOn = false;
}

int ElevatorDestButton::getFloorNum() { return floorNum; }
bool ElevatorDestButton::getState() { return isOn; }
