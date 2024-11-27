#ifndef OOP_SHIP_H
#define OOP_SHIP_H

#include "structures.h"
#include "ShipSegment.h"

#include <vector>
#include <memory>
#include <iostream>

class Ship {
public:
    Ship(int length = 1, Orientation orientation = Orientation::Vertical, Coordinates start = {0, 0});
    ~Ship();
    void printInfoShip();
    int getLength();
    Orientation getOrientation();
    const std::vector<std::shared_ptr<ShipSegment>>& getSegments() const;
    void setCoordinates(Coordinates start);
    Coordinates getCoordinates();
    bool isDestroyed();
private:
    std::vector<std::shared_ptr<ShipSegment>> segments;
    int length;
    Orientation orientation;
    Coordinates head;
};

#endif //OOP_SHIP_H
