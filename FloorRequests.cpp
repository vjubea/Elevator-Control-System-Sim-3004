#include "FloorRequests.h"

FloorRequests::FloorRequests() : numRequests(0) {
    for (int i = 0; i < FLOOR_COUNT; i++) {
        requests[i] = 0;
    }
}
FloorRequests::~FloorRequests() {}

void FloorRequests::add_request(int floorNum) {
    if (numRequests < FLOOR_COUNT) {
        requests[numRequests++] = floorNum;
    }
}
void FloorRequests::remove_request(int floorNum) {
    int p_ind = -1;
    for (int i=0; i<FLOOR_COUNT; i++) {
        if (floorNum == requests[i]) {
            p_ind = i;
            break;
        }
    }
    if (-1 < p_ind && p_ind < FLOOR_COUNT) {
        for (int i = p_ind; i < numRequests-1; i++) {
            requests[i] = requests[i+1];
        }
        numRequests--;
    }
}

int FloorRequests::get_next_floor_to_serve(int elFloorNum, string elDir) {
    int nextFloor = NONE;
    int minFloorDiff = FLOOR_COUNT;
    int currReqFloorNum;

    for (int i=0; i<numRequests; i++) {
        currReqFloorNum = requests[i];
        if (elDir == UP) {
            if (currReqFloorNum >= elFloorNum && currReqFloorNum - elFloorNum < minFloorDiff) {
                minFloorDiff = currReqFloorNum - elFloorNum;
                nextFloor = requests[i];
            }
        }
        else if (elDir == DOWN) {
            if (elFloorNum >= currReqFloorNum && elFloorNum - currReqFloorNum < minFloorDiff) {
                minFloorDiff = elFloorNum - currReqFloorNum;
                nextFloor = requests[i];
            }
        }
        else if (elDir == IDLE && numRequests > 0) {
            return requests[0];
        }
    }
    return nextFloor;
}

bool FloorRequests::isEmpty() {
    return (numRequests == 0); 
}

void FloorRequests::prioritize_safety(int safeFloorNum) {
    for (int i = numRequests-1; i >= 0; i--) {
        remove_request(requests[i]);
    }
    add_request(safeFloorNum);
}
