#include "Elevator.h"
#include <iostream>
ElevatorBell::ElevatorBell(int carN) : carNum(carN) {}
ElevatorBell::~ElevatorBell() {}

void ElevatorBell::ring() {
    std::cout << "Elevator #" << carNum << " RANG ITS BELL.\n" << std::endl;
}
