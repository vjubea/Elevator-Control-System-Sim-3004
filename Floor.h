#ifndef FLOOR_H
#define FLOOR_H

#include "header.h"
#include "FloorButton.h"
#include "PassengerList.h"
class ECS;
class Elevator;

class Floor
{
    public:
        Floor(int num, ECS* ecs);
        ~Floor();

        void add_passenger(Passenger*);
        void remove_passenger(Passenger*);
        void set_waiting_dir(string);
        void handle_floor_button(string);
        void floor_button_off(string);
        void detect_me(Elevator*, int);
        Elevator* get_corresponding_el(string);

        int getFloorNum();
        int getNumPassengers();
        PassengerList* getPassengers();

    private:
        int floorNum;
        bool pending;
        bool waitingForUp;
        bool waitingForDown;
        FloorButton* floorButtons[2];
        PassengerList* passengers;
        ECS* ecs;
};
#endif
