#include "ECS.h"

ECS::ECS() : underPowerOut(false), numElevators(0) {
    for (int i = 0; i < ELEVATOR_COUNT; i++) {
        elevators[i] = nullptr;
    }
}
ECS::~ECS() {
    for (int i = 0; i<ELEVATOR_COUNT; i++) {
        delete elevators[i];
        numElevators--;
    }
}
void ECS::set_elevator_start_floor(int numEls, Floor* initFloor) {
    if (initFloor != nullptr) {
        for (int i = 0; i < numEls; i++) {
            elevators[i] = new Elevator(i, initFloor);
            numElevators++;
        }
    }
}

void ECS::serve_request(int reqFloorNum) {
    if (reqFloorNum < 0 || FLOOR_COUNT < reqFloorNum)
        return;
    
    // Decide which car should serve floor request
    bool served = false;
    for (int i = 0; i < numElevators; i++) {
        Elevator* el = getElevator(i);
        int elCurrFloorNum = el->getCurrFloor()->getFloorNum();
        string elCurrDir = el->getCurrDirection();

        if (elCurrDir == IDLE) {
            getElevator(i)->new_request(reqFloorNum);
            served = true;
            break;
        }
        else if (elCurrFloorNum < reqFloorNum && el->getCurrDirection() == UP) {
            getElevator(i)->new_request(reqFloorNum);
            served = true;
            break;
        }
        else if (reqFloorNum < elCurrFloorNum && el->getCurrDirection() == DOWN) {
            getElevator(i)->new_request(reqFloorNum);
            served = true;
            break;
        }
    }
    if (!served && numElevators >= 1) {
        getElevator(0)->new_request(reqFloorNum);
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
