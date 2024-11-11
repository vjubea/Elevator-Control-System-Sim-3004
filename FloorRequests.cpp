#include "FloorRequests.h"

FloorRequests::FloorRequests() : numRequests(0) {
    for (int i = 0; i < FLOOR_COUNT; i++) {
        requests[i] = 0;
    }
}
FloorRequests::~FloorRequests() {}

void FloorRequests::add_request(int floorNum) {
    if (numRequests < FLOOR_COUNT && floorNum > 0 && floorNum <= FLOOR_COUNT) {
        for (int i = 0; i < numRequests; i++) {
            // Does not add duplicates
            if (requests[i] == floorNum)
                return;
        }
        requests[numRequests] = floorNum;
        numRequests++;
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

    // If the elevator is idle, return the first request
    if (elDir == IDLE && numRequests > 0) {
        return requests[0];
    }

    for (int i = 0; i < numRequests; i++) {
        currReqFloorNum = requests[i];
        // The next floor is the current Floor
        if (elFloorNum == currReqFloorNum)
            return currReqFloorNum;

        bool isEligible = false;
        if (elDir == UP) {
            // Serve request if it's above the current floor
            if (currReqFloorNum >= elFloorNum) {
                isEligible = true;
            }
        }
        else if (elDir == DOWN) {
            // Serve request if it's below the current floor
            if (currReqFloorNum <= elFloorNum) {
                isEligible = true;
            }
        }
        // If the request is eligible, check the floor difference
        if (isEligible) {
            int floorDiff = abs(currReqFloorNum - elFloorNum);
            if (floorDiff < minFloorDiff) {
                minFloorDiff = floorDiff;
                nextFloor = currReqFloorNum;
            }
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
