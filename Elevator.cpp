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
    if (overload_detected()) {
        remove_passenger(p);
        return false;
    }
    else {
        p->press_dest_button(p->getDestination(), timestep);
        return true;
    }
}
void Elevator::remove_passenger(Passenger* p) {
    // Remove p to Elevator's passengers
    passengers->remove_passenger(p);
}

bool Elevator::ready_to_move(int numObstructs) {
    close_door(numObstructs);

    // Sets Elevator's Direction for next move
    int currFloorNum = currFloor->getFloorNum();
    int nextFloorNum = floorRequests->get_next_floor_to_serve(currFloorNum, currDirection);
    isMoving = true;
    if (nextFloorNum == NONE) {
        currDirection = IDLE;
        isMoving = false;
    }
    else if (nextFloorNum < currFloorNum) {
        currDirection = DOWN;
    }
    else if (nextFloorNum > currFloorNum) {
        currDirection = UP;
    }   
    return isMoving;
}

void Elevator::reached_new_floor(Floor* fl) {
    // Elevator can access next floor
    currFloor = fl;
    update_to(fl->getFloorNum());
    // Finds the floor number of the request being served
    int reqFloorNum = floorRequests->
        get_next_floor_to_serve(currFloor->getFloorNum(), currDirection);
    // Checks if a destined floor was reached
    if (currFloor->getFloorNum() == reqFloorNum) {
        display->dest_button_off(reqFloorNum);
        // Removes serviced floor from floorRequests
        floorRequests->remove_request(reqFloorNum, currDirection);
        stop();
        open_door();
        // Passengers allowed to  board and unboard after;
    }
    if (floorRequests->isEmpty())
        currDirection = IDLE;
}

void Elevator::stop() { isMoving = false; }

void Elevator::open_door() {
    // Safety check
    if (!isMoving) {
        bell->ring();
        door->open();
    }
}
void Elevator::close_door(int numObstructs) {
    for (int i = 0; i < numObstructs; i++) {
        bell->ring();
        door->close();
        obstacle_detected();
    }
    bell->ring();
    door->close();
}

void Elevator::new_request(int floorNum, string direction) {
    floorRequests->add_request(floorNum, direction);
}
void Elevator::dest_button_pressed(int destFloorNum) {
    string direction = IDLE;
    display->dest_button_pressed(destFloorNum);
    new_request(destFloorNum, direction);
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
        passengers->get_at(i)->move_to_safety(0, DOWN);
    }
    floorRequests->prioritize_safety(0, DOWN);
}

bool Elevator::contact_building_safety() {
    cout << "Elevator is contacting Building Safety." << "\n" << endl;
    return true;
}
void Elevator::help_button_pressed() {
    cout << "Help button pressed in Elevator #" << carNum << "\n"
    << "Elevator #" << carNum << " is handling a help request.\n" << endl;
    
    if (contact_building_safety() == true) {
        cout << "Building Safety responded to the request.\n" << endl;
    }
}
bool Elevator::overload_detected() {
    if (getCurrWeight() >= maxWeight) {
        cout << "Overload detected in Elevator #" << carNum << "\n" << endl;
        display->display_text(OVERLOAD_DETECTED_WARNING);
        display->play_dialog(OVERLOAD_DETECTED_WARNING);
        return true;
    }
    return false;
}
bool Elevator::obstacle_detected() {
    door->open();
    cout << "Obstacle detected in Elevator #" << carNum << "\n" << endl;
    display->display_text(DOOR_OBST_DETECTED_WARNING);
    display->play_dialog(DOOR_OBST_DETECTED_WARNING);
    return true;
}


Floor* Elevator::getCurrFloor() { return currFloor; }
string Elevator::getCurrDirection() { return display->getCurrDir(); }
float Elevator::getCurrWeight() { return passengers->get_total_weight(); }
float Elevator::getMaxWeight() { return maxWeight; }
int Elevator::getCarNum() { return carNum; }
bool Elevator::getIsMoving() { return isMoving; }
PassengerList* Elevator::getPassengers() { return passengers; }