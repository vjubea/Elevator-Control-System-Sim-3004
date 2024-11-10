#include "ElevatorDisplay.h"

ElevatorDisplay::ElevatorDisplay(int carNum, int currFloor, string dir) {
    elCarNum = carNum;
    currFloorNum = currFloor;
    currDirection = dir;
    for (int i=0; i<FLOOR_COUNT; i++) {
        // i+1 because First floor is 1, not 0
        elButton[i] = new ElevatorDestButton(i+1, elCarNum);
    }
}
ElevatorDisplay::~ElevatorDisplay() {}

// Button Interactions
void ElevatorDisplay::dest_button_pressed(int num) {
    if (1 < num && num <= FLOOR_COUNT)
        elButton[num-1]->turn_on();
}
void ElevatorDisplay::dest_button_off(int num) {
    if (0 < num && num <= FLOOR_COUNT)
        elButton[num]->turn_off();
}
void ElevatorDisplay::toggle_help_button() {
    cout << "Help Button TURNS ON in Elevator #"
         << elCarNum << "\".\n" << endl;
}

// Text and Dialog Players
void ElevatorDisplay::play_dialog(string text) {
    cout << "Elevator #" << elCarNum
    << " plays dialog: \"" << text << "\".\n" << endl;
}
void ElevatorDisplay::display_text(string text) {
    cout << "Elevator #" << elCarNum
    << " displays text: \"" << text << "\".\n" << endl;
}

// Updater
void ElevatorDisplay::update_floor_and_dir(int floorN, string dir) {
    currFloorNum = floorN;
    currDirection = dir;
}

// Getters
int ElevatorDisplay::getCurrFloor() { return currFloorNum; }
string ElevatorDisplay::getCurrDir() { return currDirection; }
bool ElevatorDisplay::isDestButtonOn(int num) {
    if (0 < num && num <= FLOOR_COUNT)
       return elButton[num]->isOn();
    return false;
}
