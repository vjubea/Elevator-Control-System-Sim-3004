#ifndef FLOOR_REQUESTS_H
#define FLOOR_REQUESTS_H

#include <string>
#include "header.h"
using namespace std;

class FloorRequests
{
    public:
        FloorRequests();
        ~FloorRequests();
        
        void add_request(int);
        void remove_request(int);
        int get_next_floor_to_serve(int, string);
        void prioritize_safety(int);
        bool isEmpty();

    private:
        int numRequests;
        int requests[FLOOR_COUNT];
};
#endif
