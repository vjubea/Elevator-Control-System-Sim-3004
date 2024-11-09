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

        void on();
        void off();
        int getFloorNum();
        bool getState();

    private:
        int floorNum;
        int elNum;
        bool isOn;
};
#endif
