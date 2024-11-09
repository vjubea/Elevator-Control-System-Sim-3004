#ifndef ELEVATOR_BELL_H
#define ELEVATOR_BELL_H

#include "Elevator.h"

class ElevatorBell
{
    public:
        ElevatorBell(int);
        ~ElevatorBell();
        void ring();

    private:
        int carNum;
};
#endif
