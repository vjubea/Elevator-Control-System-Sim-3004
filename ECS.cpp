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

    bool served = false; // indicates if an elevator got new request
    Elevator* bestEl = nullptr;

    // Decide which car should serve floor request
    for (int i = 0; i < numElevators; i++) {
        Elevator* el = getElevator(i);
        int elCurrFloorNum = el->getCurrFloor()->getFloorNum();
        string elCurrDir = el->getCurrDirection();

        if (elCurrFloorNum < reqFloorNum && (elCurrDir == UP || elCurrDir == IDLE)) {
            el->new_request(reqFloorNum);
            served = true;
            break;
        }
        else if (reqFloorNum < elCurrFloorNum && (elCurrDir == DOWN || elCurrDir == IDLE)) {
            el->new_request(reqFloorNum);
            served = true;
            break;
        }
        else if (elCurrDir == IDLE && bestEl == nullptr) {
            bestEl = el;
        }
    }
    if (bestEl != nullptr && !served) {
        bestEl->new_request(reqFloorNum);
    }
    // If no suitable elevator found
    else if (!served && numElevators >= 1) {
        getElevator(0)->new_request(reqFloorNum);
    }
}

void ECS::detect_power_out(int timestep) {
    // Simulates backup power being turned on
    underPowerOut = true;

    cout << "ECS DETECTED POWER OUT at [timestep : " << timestep << "]\n" << endl;
    for (int i = 0; i < numElevators; i++) {
        elevators[i]->move_to_safe_floor();
    }
}
void ECS::detect_fire(int timestep) {
    cout << "ECS DETECTED FIRE at [timestep : " << timestep << "]\n" << endl;
    if (contact_fire_department(timestep) == true)
        cout << "Fire Department responded to the call. Currently Underway."
        << "\n" << endl;

    for (int i = 0; i < numElevators; i++) {
        elevators[i]->move_to_safe_floor();
    }
}

bool ECS::contact_fire_department(int timestep) {
    cout << "ECS is contacting the closest Fire Department at [timestep : "
         << timestep << "]\n" << endl;
    return true;
}

Elevator* ECS::getElevator(int ind) {
    if (0 <= ind && ind < numElevators) {
        return elevators[ind];
    }
    return nullptr;
};
