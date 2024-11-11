#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <string>
#include "Floor.h" //Includes Passenger, PassengerList
#include "FloorRequests.h"
#include "ElevatorDoor.h"
#include "ElevatorBell.h"
#include "ElevatorDisplay.h"
using namespace std;

class Elevator
{
public:
    Elevator(int, Floor *);
    ~Elevator();

    bool add_passenger(Passenger *, int);
    void remove_passenger(Passenger *);
    bool ready_to_move(int, int);
    void reached_floor(Floor *, int);
    void new_request(int);
    void stop();
    void open_door(int);
    void close_door(int, int);
    void dest_button_pressed(int);
    bool contact_building_safety(int);
    void help_button_pressed(int);
    void move_to_safe_floor();

    bool door_is_open();
    Floor *getCurrFloor();
    PassengerList *getPassengers();
    string getCurrDirection();
    float getMaxWeight();
    int getCarNum();
    bool getIsMoving();

private:
    int carNum;
    float maxWeight;
    bool isMoving;
    string currDirection;
    Floor *currFloor;
    FloorRequests *floorRequests;
    PassengerList *passengers;
    ElevatorDisplay *display;
    ElevatorDoor *door;
    ElevatorBell *bell;

    float getCurrWeight();
    bool make_decision();
    void update_to(int);
    bool obstacle_detected(int);
    bool overload_detected(int);
};
#endif
