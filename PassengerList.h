#ifndef PASSENGER_LIST_H
#define PASSENGER_LIST_H

#include "Passenger.h"

class PassengerList
{
    public:
        PassengerList();
        ~PassengerList();

        void add_passenger(Passenger*);
        void remove_passenger(Passenger*);
        bool all_reached_dest();

        Passenger* get_at(int);
        Passenger* get_next_unboarding(int);
        int getNumPassengers();
        float get_total_weight();

    private:
        int numPassengers;
        Passenger* passengers[PASSENGER_CAP]; 
};
#endif
