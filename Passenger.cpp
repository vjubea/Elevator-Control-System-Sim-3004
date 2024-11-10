#include "Passenger.h"
#include "Elevator.h"
#include "Floor.h"
using namespace std;

Passenger::Passenger(string n, float weight, Floor* startFloor, int destFloor,
                     int floorButT, int openT, int closeT, int helpT, int numObs) {
    name = n;
    totalWeight = weight;
    destinedFloor = destFloor;
    if (destFloor > startFloor->getFloorNum())
        heading = UP;
    else if (destFloor < startFloor->getFloorNum())
        heading = DOWN;
    else
        heading = REACHED_DEST;
    floor = startFloor;
    elevator = nullptr;

    // Set timings and obstructions
    pressFloorButT = floorButT;
    pressOpenT = openT;
    pressCloseT = closeT;
    pressHelpT = helpT;
    numObstructs = numObs;
}
Passenger::~Passenger() {}

bool Passenger::press_floor_button(int timestep) {
    // Checks if passenger is on a Floor
    if (floor != nullptr) {
        cout << name << " pressed the Floor Button " << heading
             << " on Floor #" << floor->getFloorNum()
             << " at timestep " << timestep << ".\n" << endl;
        
        floor->handle_floor_button(heading);
        return true;
    }
    return false;
}
bool Passenger::press_dest_button(int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed Dest Button " << destinedFloor
        << " at timestep " << timestep << ".\n" << endl;

        elevator -> dest_button_pressed(destinedFloor);
        return true;
    }
    return false;
}
bool Passenger::press_open_door_button(int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed OPEN DOOR Button in Elevator #" 
        << elevator->getCarNum() << " at timestep " << timestep << ".\n" << endl;
        
        elevator -> open_door(timestep);
        return true;
    }
    return false;
}
bool Passenger::press_close_door_button(int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed CLOSE DOOR Button in Elevator #" 
        << elevator->getCarNum() << " at timestep " << timestep << ".\n" << endl;
        
        elevator->ready_to_move(0, timestep);
        return true;
    }
    return false;
}
bool Passenger::press_help_button(int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed HELP Button in Elevator #"
        << elevator->getCarNum() << " at timestep " << timestep << ".\n" << endl;

        elevator -> help_button_pressed(timestep);
        return true;
    }
    return false;
}

void Passenger::board_elevator(int timestep) {
    // Handles whole boarding process
    Elevator* el = floor->get_corresponding_el(heading);
    if (el != nullptr) {
        cout << name << " is boarding Elevator #" << el->getCarNum()
             << " at timestep " << timestep << ".\n" << endl;

        //Elevator checks if passenger was added
        if (el->add_passenger(this, timestep) == true) {
            // Removes passenger from Floor if no overload
            floor->remove_passenger(this);
            floor = nullptr;
            elevator = el;
            press_dest_button(timestep);
        }
        else {
            cout << name << " unboards Elevator #" << el->getCarNum()
                 << " and returns to Floor #" << floor->getFloorNum()
                 << " because of OVERLOAD.\n" << endl;
        }
    }
}
void Passenger::unboard_elevator(int timestep) {
    // Handles whole unboarding process
    if (elevator != nullptr) {
        Floor* elCurrFloor = elevator->getCurrFloor();
        // elCurrFloor has ECS with 7 elevators
        int elCurrFloorNum = elCurrFloor->getFloorNum();
        // Ensures passenger is unboarding at the right Floor
        if (destinedFloor == elCurrFloorNum) {
            cout << name << " unboards Elevator #" << elevator->getCarNum()
                 << " and reached Floor #" << elCurrFloor->getFloorNum()
                 << " at timestep " << timestep << ".\n" << endl;

            elCurrFloor->add_passenger(this);
            floor = elCurrFloor;
            elevator->remove_passenger(this);
            elevator = nullptr;

            heading = REACHED_DEST;
            cout << name << " REACHED THEIR DESTINATION at timestep "
                 << timestep << "\n" << endl;
        }
    }
}

void Passenger::move_to_safety(int safeFloorNum, string safeDir) {
    if (elevator != nullptr) {
        destinedFloor = safeFloorNum;
        heading = safeDir;
    }
}

void Passenger::no_more_obstructs() { numObstructs = 0; }

string Passenger::getName() { return name; }
float Passenger::getWeight() { return totalWeight; }
int Passenger::getDestination() { return destinedFloor; }
string Passenger::getHeading() { return heading; }
Floor* Passenger::getFloor() { return floor; }
int Passenger::getPressFloorButT() { return pressFloorButT; }
int Passenger::getPressOpenT() { return pressOpenT; }
int Passenger::getPressCloseT() { return pressCloseT; }
int Passenger::getPressHelpT() { return pressHelpT; }
int Passenger::getNumObstructs() { return numObstructs; }
