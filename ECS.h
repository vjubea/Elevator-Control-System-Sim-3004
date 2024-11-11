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

        void serve_request(int);
        void detect_power_out(int);
        void detect_fire(int);
        bool contact_fire_department(int);

        void set_elevator_start_floor(int, Floor*);
        Elevator* getElevator(int);

    private:
        bool underPowerOut;
        int numElevators;
        Elevator* elevators[ELEVATOR_COUNT];
};
#endif
