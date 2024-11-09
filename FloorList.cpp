#include "FloorList.h"

FloorList::FloorList() {
    numFloors = 0;
    for (int i=0; i<FLOOR_COUNT; i++) {
        floors[i] = nullptr;
    }
}
FloorList::~FloorList() {}

void FloorList::add_floor(Floor* f) {
    if (numFloors < FLOOR_COUNT) {
        floors[numFloors++] = f;
    }
}
void FloorList::remove_floor(Floor* f) {
    int p_ind = 0;
    Floor* floor = nullptr;
    for (int i=0; i<numFloors; i++) {
        if (f == floors[i]) {
            floor = floors[i];
            p_ind = i;
            break;
        }
    }
    if (floor != nullptr) {
        numFloors--;
        for (int i=p_ind; i<numFloors; i++) {
            floors[i] = floors[i+1];
        }
    }
}

Floor* FloorList::get(int ind) {
    if (ind < 0 || numFloors-1 < ind)
        return nullptr;
    return floors[ind];
}

int FloorList::getNumFloors() { return numFloors; }
