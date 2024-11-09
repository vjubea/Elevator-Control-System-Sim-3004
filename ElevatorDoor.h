#ifndef ELEVATOR_DOOR_H
#define ELEVATOR_DOOR_H

class ElevatorDoor
{
    public:
        ElevatorDoor(int);
        ~ElevatorDoor();
        void open();
        void close();
        bool isClosed();

    private:
        int carNum;
        bool isOpen;

};
#endif
