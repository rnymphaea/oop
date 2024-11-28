#ifndef OOP_SHIPSEGMENT_H
#define OOP_SHIPSEGMENT_H

#include "structures.h"
#include <iostream>

class ShipSegment {
public:
    ShipSegment();
    ~ShipSegment();
    int getHP();
    void damage(int damage = 1);
    void printInfo();
    Coordinates getCoordinates();
    void setCoordinates(Coordinates coords);
    void setHP(int hp);
private:
    int HP;
    Coordinates coordinates;
};

#endif //OOP_SHIPSEGMENT_H
