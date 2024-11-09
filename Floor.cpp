#include "Floor.h"
#include "ECS.h"
using namespace std;

Floor::Floor(int num) {
    floorNum = num;
    pending = waitingForDown = waitingForUp = false;
    floorButtons[0] = new FloorButton(floorNum, UP);
    floorButtons[1] = new FloorButton(floorNum, DOWN);
    passengers = new PassengerList();
}
Floor::~Floor() {}

void Floor::handle_floor_button(string dir) {
    if (dir == UP)
        floorButtons[0]->switch_on();
    else if (dir == DOWN)
        floorButtons[1]->switch_on();
    ecs->serve_request(floorNum, dir); // Adds actual request
}

void Floor::add_passenger(Passenger* p) {
    passengers->add_passenger(p);
}
void Floor::remove_passenger(Passenger* p) {
    passengers->remove_passenger(p);
}

void Floor::set_waiting_dir(string dir) {
    pending = true;

    if (dir == UP)
        waitingForUp = true;
    if (dir == DOWN)
        waitingForDown = true;
    
    if (waitingForUp && waitingForDown) {
        waitingForUp = false;
        waitingForDown = false;
        pending = false;
    }
}

void Floor::floor_button_off(string dir) {
    if (dir == UP)
        floorButtons[0]->switch_off();
    else if (dir == DOWN)
        floorButtons[1]->switch_off();
}

void Floor::detect_me(Elevator* el) {
    cout << "Floor #" << floorNum << " detected Elevator Car #"
         << el->getCarNum() << ".\n" << endl;

    // Checks for bottom/top floor
    if (floorNum == 0 || floorNum == FLOOR_COUNT) {
        if (waitingForUp == true) {
            waitingForUp = false;
            floor_button_off(UP);
        }
        else if (waitingForDown == true) {
            waitingForDown = false;
            floor_button_off(DOWN);
        }
    }
    else if (waitingForUp == true && el->getCurrDirection() == UP) {
        waitingForUp = false;
        floor_button_off(UP);
    }
    else if (waitingForDown == true && el->getCurrDirection() == DOWN) {
        waitingForDown = false;
        floor_button_off(DOWN);
    }
    el->reached_new_floor(this);
}

Elevator* Floor::get_corresponding_el(string passengerDir) {
    for (int i = 0; i < ELEVATOR_COUNT; i++) {
        Elevator* currEl = ecs->getElevator(i);
        if (currEl->getCurrDirection() == passengerDir)
            return currEl;
    }
    return nullptr;
}
int Floor::getFloorNum() { return floorNum; }
PassengerList* Floor::getPassengers() { return passengers; }
