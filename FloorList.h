#ifndef FLOOR_LIST_H
#define FLOOR_LIST_H

#include "header.h"
class Floor;

class FloorList
{
    public:
        FloorList();
        ~FloorList();
        void add_floor(Floor*);
        void remove_floor(Floor*);
        Floor* get(int);
        int getNumFloors();

    private:
        int numFloors;
        Floor* floors[FLOOR_COUNT]; 
};
#endif
