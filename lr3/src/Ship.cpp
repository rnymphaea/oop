#include "../include/Ship.h"

Ship::Ship(int length, Orientation orientation, Coordinates start) : length(length), orientation(orientation), head(start){
    for (int i = 0; i < length; i++) {
        segments.push_back(std::make_shared<ShipSegment>());
    }

}

int Ship::getLength() {
    return length;
}

const std::vector<std::shared_ptr<ShipSegment>>& Ship::getSegments() const {
    return segments;
}

Orientation Ship::getOrientation() {
    return orientation;
}

Coordinates Ship::getCoordinates() {
    return head;
}

void Ship::setCoordinates(Coordinates start) {
    head = start;
}

void Ship::printInfoShip() {
    for (const auto segment : segments) {
        segment->printInfo();
    }
}

bool Ship::isDestroyed() {
    for (const auto segment : segments) {
        if (segment->getHP() > 0) {
            return false;
        }
    }
    return true;
}

Ship::~Ship() = default;

