#include "ECS.h"

ECS::ECS(int numEls, Floor* initFloor) : underPowerOut(false) {
    numElevators = numEls;
    if (initFloor != nullptr) {
        for (int i = 0; i < numElevators; i++) {
            elevators[i] = new Elevator(i, initFloor);
        }
    }
}
ECS::~ECS() {
    for (int i = 0; i<ELEVATOR_COUNT; i++) {
        delete elevators[i];
        numElevators--;
    }
}

void ECS::serve_request(int reqFloorNum, string dir) {
    if (reqFloorNum < 0 || FLOOR_COUNT <= reqFloorNum)
        return;
    
    // Decide which car should serve floor request
    bool served = false;
    for (int i = 0; i<ELEVATOR_COUNT; i++) {
        if (dir == elevators[i]->getCurrDirection()) {
            elevators[i]->new_request(reqFloorNum, dir);
            served = true;
        }
    }
    if (!served && numElevators > 0) {
        elevators[0]->new_request(reqFloorNum, dir);
    }
}

void ECS::detect_power_out() {
    for (int i = 0; i < numElevators; i++) {
        elevators[i]->move_to_safe_floor();
    }
}
void ECS::detect_fire() {
    if (contact_fire_department() == true)
        cout << "Fire Department responded to the call. Currently Underway."
        << "\n" << endl;

    for (int i = 0; i < numElevators; i++) {
        elevators[i]->move_to_safe_floor();
    }
}

bool ECS::contact_fire_department() {
    cout << "ECS is contacting the closest Fire Department." << "\n"<< endl;
    return true;
}

Elevator* ECS::getElevator(int ind) {
    if (0 <= ind && ind < numElevators) {
        return elevators[ind];
    }
    return nullptr;
};
