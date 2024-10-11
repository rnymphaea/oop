#ifndef OOP_SHIPSEGMENT_H
#define OOP_SHIPSEGMENT_H

#include "structures.h"
#include <iostream>

class ShipSegment {
public:
    ShipSegment();
    ~ShipSegment();
    int getHP();
    void damage();
    void printInfo();
    void setCoordinates(Coordinates coordinates);
    void setState(SegmentState segmentState);
private:
    int HP;
    SegmentState state;
    Coordinates coordinates;
};

#endif //OOP_SHIPSEGMENT_H
