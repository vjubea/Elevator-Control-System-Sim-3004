#include "PassengerList.h"
using namespace std;

PassengerList::PassengerList() {
    numPassengers = 0;
    for (int i=0; i<PASSENGER_CAP; i++) {
        passengers[i] = nullptr;
    }
}
PassengerList::~PassengerList() {}

void PassengerList::add_passenger(Passenger* p) {
    if (numPassengers < PASSENGER_CAP) {
        passengers[numPassengers] = p;
        numPassengers++;
    }
}
void PassengerList::remove_passenger(Passenger* p) {
    int p_ind = 0;
    Passenger* passenger = nullptr;
    for (int i = 0; i < numPassengers; i++) {
        if (p == passengers[i]) {
            passenger = passengers[i];
            p_ind = i;
            break;
        }
    }
    if (passenger != nullptr) {
        for (int i=p_ind; i < numPassengers-1; i++) {
            passengers[i] = passengers[i+1];
        }
        numPassengers--;
    }
}

Passenger* PassengerList::get_at(int ind) {
    if (0 <= ind && ind < numPassengers) {
        return passengers[ind];
    }
    return nullptr;
}

bool PassengerList::all_reached_dest() {
    for (int i=0; i<numPassengers; i++) {
        if (get_at(i)->getHeading() != REACHED_DEST)
            return false;
    }
    return true;
}

Passenger* PassengerList::get_next_unboarding(int currFloor) {
    for (int i = 0; i < numPassengers; i++) {
        if (passengers[i]->getDestination() == currFloor) {
            return passengers[i];
        }
    }
    return nullptr;
}

int PassengerList::getNumPassengers() { return numPassengers; }

float PassengerList::get_total_weight() {
    float totalWeight = 0;
    for (int i=0; i<numPassengers; i++) {
        totalWeight += get_at(i)->getWeight();
    }
    return totalWeight;
}
