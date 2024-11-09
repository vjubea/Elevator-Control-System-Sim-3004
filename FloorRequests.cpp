#include "FloorRequests.h"

FloorRequests::FloorRequests() : numRequests(0) {}
FloorRequests::~FloorRequests() {}

void FloorRequests::add_request(int floorNum, string dir) {
    if (numRequests < FLOOR_COUNT) {
        requests[numRequests++] = floorNum;
        directions[numRequests] = dir;
    }
}
void FloorRequests::remove_request(int floorNum, string dir) {
    int p_ind = -1;
    for (int i=0; i<FLOOR_COUNT; i++) {
        if (floorNum == requests[i] && dir == directions[i]) {
            p_ind = i;
            break;
        }
    }
    if (-1 < p_ind && p_ind < FLOOR_COUNT) {
        for (int i = p_ind; i < numRequests-1; i++) {
            requests[i] = requests[i+1];
            directions[i] = directions[i+1];
        }
        numRequests--;
    }
}

int FloorRequests::get_next_floor_to_serve(int elFloorNum, string elDir) {
    int nextFloor = NONE;
    int minFloorDiff = INT8_MAX;
    int currReqFloorNum;

    for (int i=0; i<numRequests; i++) {
        currReqFloorNum = requests[i];
        if (elDir == UP && directions[i] == elDir) {
            if (currReqFloorNum >= elFloorNum && currReqFloorNum - elFloorNum < minFloorDiff) {
                minFloorDiff = currReqFloorNum - elFloorNum;
                nextFloor = requests[i];
            }
        }
        else if (elDir == DOWN && directions[i] == elDir) {
            if (elFloorNum >= currReqFloorNum && elFloorNum - currReqFloorNum < minFloorDiff) {
                minFloorDiff = elFloorNum - currReqFloorNum;
                nextFloor = requests[i];
            }
        }
    }
    return nextFloor;
}

bool FloorRequests::isEmpty() {
    return (numRequests == 0); 
}

void FloorRequests::prioritize_safety(int safeFloorNum, string safeDir) {
    for (int i = numRequests-1; i >= 0; i--) {
        remove_request(requests[i], directions[i]);
    }
    add_request(safeFloorNum, safeDir);
}
