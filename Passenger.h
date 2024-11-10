#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <iostream>
#include "header.h"
using namespace std;
class Floor;
class Elevator;

class Passenger
{
    public:
        Passenger(string, float, Floor*, int, int, int, int, int, int);
        ~Passenger();

        // Board/Unboard function
        void board_elevator(int);
        void unboard_elevator(int);
        void move_to_safety(int, string);
        void no_more_obstructs();

        // Button-triggers
        bool press_floor_button(int);
        bool press_dest_button(int);
        bool press_help_button(int);
        bool press_open_door_button(int);
        bool press_close_door_button(int);

        // Getters
        string getName();
        float getWeight();
        int getDestination();
        string getHeading();
        Floor* getFloor();
        int getPressFloorButT();
        int getPressOpenT();
        int getPressCloseT();
        int getPressHelpT();
        int getNumObstructs();

    private:
        string name;
        float totalWeight; // In KG
        int destinedFloor;
        string heading; // Used to ensure passenger enters proper Elevator
        Floor* floor;
        Elevator* elevator;
        int pressFloorButT;
        int pressOpenT;
        int pressCloseT;
        int pressHelpT;
        int numObstructs;
};
#endif
