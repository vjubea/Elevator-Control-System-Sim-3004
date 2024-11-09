#ifndef HEADER_H
#define HEADER_H

#define ELEVATOR_COUNT 2
#define PASSENGER_CAP 4
#define FLOOR_COUNT 5
#define ELEV_MAX_WEIGHT 360
#define START_FLOOR_IND 0
#define NONE -1

#define UP "UP"
#define DOWN "DOWN"
#define IDLE "IDLE"
#define REACHED_DEST "REACHED DEST"

#define DOOR_OBST_DETECTED_WARNING """Door Obstacle Detected|| Please Clear Door Blockage!"
#define OVERLOAD_DETECTED_WARNING "||Overload Dectected|| Please reduce load!"
#define FIRE_WARNING "||Fire Detected|| Please don't panic and leave the Elevator once it reached the Safe Floor"
#define POWEROUT_DETECTED_WARNING "||Power Out Detected|| Please don't panic and leave the Elevator once it reached the Safe Floor"
#define SAFE_FLOOR_REACHED "||Safe Floor Reached|| Please unboard the elevator to safety."

#endif
