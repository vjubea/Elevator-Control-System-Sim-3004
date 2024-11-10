#ifndef ELEVATOR_DEST_BUTTON_H
#define ELEVATOR_DEST_BUTTON_H

#include <iostream>
using namespace std;
class ElevatorDisplay;

class ElevatorDestButton
{
    public:
        ElevatorDestButton(int, int);
        ~ElevatorDestButton();

        void turn_on();
        void turn_off();
        int getFloorNum();
        bool isOn();

    private:
        int floorNum;
        int elNum;
        bool on;
};
#endif
