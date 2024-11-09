#include "ElevatorDoor.h"

ElevatorDoor::ElevatorDoor(int carN) : carNum(carN), isOpen(false) {}
ElevatorDoor::~ElevatorDoor() {}

void ElevatorDoor::open() { isOpen = true; }

void ElevatorDoor::close() { isOpen = false; }

bool ElevatorDoor::isClosed() { return !isOpen; }
