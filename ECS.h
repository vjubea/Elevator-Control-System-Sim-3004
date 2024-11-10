#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <string>
#include "header.h"
#include "Elevator.h" //includes Passenger, Floor, ElevatorDisplay, Door, Bell
using namespace std;

class ECS
{
    public:
        ECS();
        ~ECS();
        void set_elevator_start_floor(int, Floor*);
        void serve_request(int, int);
        void detect_power_out();
        void detect_fire();
        bool contact_building_safety(int);
        bool contact_fire_department();

        Elevator* getElevator(int);

    private:
        bool underPowerOut;
        int numElevators;
        Elevator* elevators[ELEVATOR_COUNT];
};
#endif
