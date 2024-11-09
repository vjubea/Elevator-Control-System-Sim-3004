#ifndef ELEVATOR_DISPLAY_H
#define ELEVATOR_DISPLAY_H

#include <string>
#include "header.h"
#include "ElevatorDestButton.h"
using namespace std;

class ElevatorDisplay
{
    public:
        ElevatorDisplay(int, int, string);
        ~ElevatorDisplay();
        
        void dest_button_pressed(int);
        void dest_button_off(int);
        void toggle_help_button();
        void play_dialog(string);
        void display_text(string);
        void update_floor_and_dir(int, string);

        int getCurrFloor();
        string getCurrDir();
        bool isDestButtonOn(int);
        

    private:
        int elCarNum;
        int currFloorNum;
        string currDirection;
        ElevatorDestButton* elButton[FLOOR_COUNT];
};
#endif
