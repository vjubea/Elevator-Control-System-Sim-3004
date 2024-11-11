#include "ElevatorDestButton.h"

ElevatorDestButton::ElevatorDestButton(int floorN, int carNum) {
    floorNum = floorN;
    elNum = carNum;
    on = false;
}
ElevatorDestButton::~ElevatorDestButton() {}

void ElevatorDestButton::turn_on() {
    cout << "Destination Button #" << floorNum
         << " is toggled ON in Elevator #"<< elNum
         << ".\n" << endl;
    on = true;
}
void ElevatorDestButton::turn_off() {
    cout << "Destination Button " << floorNum
         << "is toggled OFF in Elevator #"<< elNum
         << ".\n" << endl;
    on = false;
}

int ElevatorDestButton::getFloorNum() { return floorNum; }
bool ElevatorDestButton::isOn() { return on; }
