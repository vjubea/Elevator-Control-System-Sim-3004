#ifndef FLOOR_BUTTON_H
#define FLOOR_BUTTON_H

#include <string>
#include <iostream>
using namespace std;
class Floor;

class FloorButton
{
    public:
        FloorButton(int, string);
        ~FloorButton();

        void switch_on();
        void switch_off();

    private:
        string direction;
        bool isOn;
        int floorNum;
};
#endif
