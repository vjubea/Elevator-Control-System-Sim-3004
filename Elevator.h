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
        Elevator(int, Floor*);
        ~Elevator();
        
        bool add_passenger(Passenger*, int);
        void remove_passenger(Passenger*);
        bool ready_to_move(int);
        void reached_new_floor(Floor*);
        void new_request(int, string);
        void update_to(int);
        void stop();
        void open_door();
        void close_door(int);
        void dest_button_pressed(int);
        bool contact_building_safety();
        void help_button_pressed();
        bool overload_detected();
        bool obstacle_detected();
        void move_to_safe_floor();

        Floor* getCurrFloor();
        PassengerList* getPassengers();
        string getCurrDirection();
        float getCurrWeight();
        float getMaxWeight();
        int getCarNum();
        bool getIsMoving();
        
    private:
        int carNum;
        float maxWeight;
        bool isMoving;
        string currDirection;
        Floor* currFloor;
        FloorRequests* floorRequests;
        PassengerList* passengers;
        ElevatorDisplay* display;
        ElevatorDoor* door;
        ElevatorBell* bell;
};
#endif
