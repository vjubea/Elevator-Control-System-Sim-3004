#include "Passenger.h"
#include "Elevator.h"
#include "Floor.h"
using namespace std;

Passenger::Passenger(string n, float weight, Floor* startFloor, int destFloor) {
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
}
Passenger::~Passenger() {}

bool Passenger::press_floor_button(int floorNum, int timestep, string dir) {
    // Checks if passenger is on a Floor
    if (floor != nullptr) {
        cout << name << " on Floor #" << floorNum << " pressed "
        << dir << " Floor Button at timestep " << timestep
        << ".\n" << endl;
        
        floor->handle_floor_button(dir);
        return true;
    }
    return false;
}
bool Passenger::press_dest_button(int num, int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed Dest Button " << num
        << " at timestep " << timestep << ".\n" << endl;

        elevator -> dest_button_pressed(num);
        return true;
    }
    return false;
}
bool Passenger::press_help_button(int carNum, int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed HELP Button in Elevator #" 
        << carNum << " at timestep " << timestep << ".\n" << endl;
        
        elevator -> help_button_pressed();
        return true;
    }
    return false;
}
bool Passenger::press_open_door_button(int carNum, int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed OPEN DOOR Button in Elevator #" 
        << carNum << " at timestep " << timestep << ".\n" << endl;
        
        elevator -> open_door();
        return true;
    }
    return false;
}
bool Passenger::press_close_door_button(int carNum, int timestep) {
    // Checks if passenger is in Elevator
    if (elevator != nullptr) {
        cout << name << " pressed CLOSE DOOR Button in Elevator #" 
        << carNum << " at timestep " << timestep << ".\n" << endl;
        
        elevator -> close_door(false);
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
        }
        else {
            cout << name << " unboards Elevator #" << el->getCarNum()
                 << "and returns to Floor #" << floor->getFloorNum()
                 << " at timestep " << timestep << ".\n" << endl;
        }
    }
}
void Passenger::unboard_elevator(int timestep) {
    // Handles whole unboarding process
    cout << name << " unboards Elevator #" << elevator->getCarNum()
         << "and reached Floor #" << floor->getFloorNum()
         << " at timestep " << timestep << ".\n" << endl;

    Floor* elCurrFloor = elevator->getCurrFloor();
    if (elCurrFloor == nullptr) return;
    // Ensures passenger is unboarding at the right Floor
    if (destinedFloor == elCurrFloor->getFloorNum()) {
        elCurrFloor->add_passenger(this);
        floor = elCurrFloor;
        elevator->remove_passenger(this);
        elevator = nullptr;
        heading = REACHED_DEST;
        cout << name << " REACHED THEIR DESTINATION.\n" << endl;
    }
}

void Passenger::move_to_safety(int safeFloorNum, string safeDir) {
    if (elevator != nullptr) {
        destinedFloor = safeFloorNum;
        heading = safeDir;
    }
}

string Passenger::getName() { return name; }
float Passenger::getWeight() { return totalWeight; }
int Passenger::getDestination() { return destinedFloor; }
string Passenger::getHeading() { return heading; }
Floor* Passenger::getFloor() { return floor; }