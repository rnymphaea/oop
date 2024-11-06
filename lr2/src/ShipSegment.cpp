#include "../include/ShipSegment.h"

ShipSegment::ShipSegment() :
    HP(2),  coordinates(Coordinates{0, 0})
{}

int ShipSegment::getHP() {
    return HP;
}

void ShipSegment::damage(int damage) {
    if (HP < 1) {
        throw std::runtime_error("Segment is already destroyed!");
    }
    HP -= damage;
    if (HP < 0) {
        HP = 0;
    }
//    switch (state) {
//        case SegmentState::Undamaged:
//            setState(SegmentState::Damaged);
//            break;
//        case SegmentState::Damaged:
//            setState(SegmentState::Destroyed);
//            break;
//        case SegmentState::Destroyed:
//            throw std::runtime_error("Segment is already destroyed!");
//    }
}

void ShipSegment::printInfo() {
    std::cout << "SEGMENT INFO" << std::endl;
    std::cout << "HP: " << HP << std::endl;
    std::cout << "Coordinantes" << coordinates.x << "  " << coordinates.y << std::endl;
}

Coordinates ShipSegment::getCoordinates() {
    return coordinates;
}

void ShipSegment::setCoordinates(Coordinates coords) {
    coordinates = coords;
}

ShipSegment::~ShipSegment() = default;

