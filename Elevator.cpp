#include "Elevator.h"

Elevator::Elevator(int num, Floor* startingFloor) {
    carNum = num;
    maxWeight = ELEV_MAX_WEIGHT;
    isMoving = false;
    currDirection = IDLE;
    currFloor = startingFloor;
    floorRequests = new FloorRequests();
    passengers = new PassengerList();
    display = new ElevatorDisplay(carNum, currFloor->getFloorNum(), currDirection);
    door = new ElevatorDoor(carNum);
    bell = new ElevatorBell(carNum);
}
Elevator::~Elevator() {
    delete floorRequests;
    delete passengers;
    delete display;
    delete door;
    delete bell;
}

bool Elevator::add_passenger(Passenger* p, int timestep) {
    // Add p to Elevator's passengers
    passengers->add_passenger(p);
    if (overload_detected(timestep)) {
        remove_passenger(p);
        return false;
    }
    else {
        p->press_dest_button(timestep);
        return true;
    }
}
void Elevator::remove_passenger(Passenger* p) {
    // Remove p to Elevator's passengers
    passengers->remove_passenger(p);
}

void Elevator::new_request(int floorNum) {
    floorRequests->add_request(floorNum);
    make_decision();
}
void Elevator::dest_button_pressed(int destFloorNum) {
    display->dest_button_pressed(destFloorNum);
    new_request(destFloorNum);
    make_decision();
}

bool Elevator::make_decision() {
    // Sets Elevator's Direction for next move
    int currFloorNum = currFloor->getFloorNum();
    int reqFloorNum = floorRequests->get_next_floor_to_serve(currFloorNum, currDirection);
    // No requests served currently
    if (reqFloorNum == NONE) {
        currDirection = IDLE;
        return false;
    }
    else if (reqFloorNum < currFloorNum) {
        currDirection = DOWN;
    }
    else if (reqFloorNum > currFloorNum) {
        currDirection = UP;
    }
    // Elevator requested on current floor
    else {
        currDirection = IDLE;
    }
    return true;
}
bool Elevator::ready_to_move(int numObs, int timestep) {
    close_door(numObs, timestep);
    isMoving = make_decision();
    return isMoving;
}

void Elevator::reached_floor(Floor* fl, int timestep) {
    if (currFloor->getFloorNum() != fl->getFloorNum()) {
        cout << "Elevator #" << carNum << " moved from Floor #" << currFloor->getFloorNum()
             << " to Floor #" << fl->getFloorNum() 
             << " at [timestep : " << timestep << "].\n" << endl;
        update_to(fl->getFloorNum());
    }
    // Elevator can access next floor
    int prevFloorNum = currFloor->getFloorNum();
    currFloor = fl;
    int currFloorNum = fl->getFloorNum();

    // Finds the floor number of the request being served
    int reqFloorNum = floorRequests->
        get_next_floor_to_serve(currFloorNum, currDirection);

    // Checks if a destined floor was reached
    if (currFloorNum == reqFloorNum) {
        // Checks if the previous Floor is not current one
        if (currFloorNum != prevFloorNum) {
            display->dest_button_off(reqFloorNum);
            stop();
        }
        else {
            isMoving = false;
        }
        open_door(timestep);
        // Removes serviced floor from floorRequests
        floorRequests->remove_request(reqFloorNum);
        if (currFloorNum == 1 | currFloorNum == FLOOR_COUNT | floorRequests->isEmpty()) {
            currDirection = IDLE;
        }
        // Passengers allowed to  board and unboard after
    }
}

void Elevator::stop() {
    cout << "Elevator #" << carNum << " stopped.\n" << endl;
    isMoving = false;
}

void Elevator::open_door(int timestep) {
    // Safety check
    if (!isMoving) {
        bell->ring();
        door->open();
        cout << "Elevator #" << carNum << " OPENED ITS DOOR at [timestep : "
             << timestep << "].\n" << endl;
    }
}
void Elevator::close_door(int numObs, int timestep) {
    if (!door->isClosed()) {
        for (int i = 0; i < numObs; i++) {
            bell->ring();
            door->close();
            cout << "Elevator #" << carNum << " TRIES CLOSING its DOOR."
                 <<"\n" << endl;
            obstacle_detected(timestep);
        }
        bell->ring();
        door->close();
        cout << "Elevator #" << carNum << " CLOSED its DOOR"
             <<".\n" << endl;
    }
}

void Elevator::update_to(int floorNum) {
    display->update_floor_and_dir(floorNum, currDirection);
    display->display_text("Reached Floor #" + to_string(floorNum));
    display->play_dialog("Reached Floor #" + to_string(floorNum));
}

// Safety Operations
void Elevator::move_to_safe_floor() {
    currDirection = DOWN;
    for (int i = 0; i < passengers->getNumPassengers(); i++) {
        passengers->get_at(i)->move_to_safety(SAFE_FLOOR_NUM, DOWN);
    }
    floorRequests->prioritize_safety(SAFE_FLOOR_NUM);
    make_decision();
}

bool Elevator::contact_building_safety(int timestep) {
    cout << "Elevator CONTACTED Building Safety"
        << " at [timestep : " << timestep <<"].\n" << endl;
    return true;
}
void Elevator::help_button_pressed(int timestep) {
    cout << "A passenger CLICKED the HELP Button" 
         << " at [timestep : " << timestep <<"].\n"
         << "Elevator #" << carNum << " is now handling HELP request.\n" << endl;
    
    if (contact_building_safety(timestep) == true) {
        cout << "Building Safety responded to the request.\n" << endl;
    }
}
bool Elevator::overload_detected(int timestep) {
    if (getCurrWeight() >= maxWeight) {
        cout << "OVERLOAD DETECTED in Elevator #" << carNum
             << " at [timestep : " << timestep << "].\n" << endl;
        display->display_text(OVERLOAD_DETECTED_WARNING);
        display->play_dialog(OVERLOAD_DETECTED_WARNING);
        return true;
    }
    return false;
}
bool Elevator::obstacle_detected(int timestep) {
    cout << "DOOR OBSTACLE DETECTED in Elevator #" << carNum
         << " at [timestep : " << timestep <<"].\n" << endl;
    open_door(timestep);
    display->display_text(DOOR_OBST_DETECTED_WARNING);
    display->play_dialog(DOOR_OBST_DETECTED_WARNING);
    return true;
}
bool Elevator::door_is_open() { return !(door->isClosed()); }
Floor* Elevator::getCurrFloor() { return currFloor; }
string Elevator::getCurrDirection() { return currDirection; }
float Elevator::getCurrWeight() { return passengers->get_total_weight(); }
float Elevator::getMaxWeight() { return maxWeight; }
int Elevator::getCarNum() { return carNum; }
bool Elevator::getIsMoving() { return isMoving; }
PassengerList* Elevator::getPassengers() { return passengers; }
