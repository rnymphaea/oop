//
// Created by alex on 08.10.24.
//

#include "../include/ShipSegment.h"

ShipSegment::ShipSegment() :
    HP(2), state(SegmentState::Undamaged), coordinates(Coordinates{0, 0})
{}

int ShipSegment::getHP() {
    return HP;
}

void ShipSegment::damage() {
    if (HP == 0) {
        std::cout << "Segment is already destroyed!";
    }
    else {
        HP--;
    }
}

void ShipSegment::printInfo() {
    std::cout << "HP: " << HP << std::endl;
}

void ShipSegment::setCoordinates(Coordinates coords) {
    coordinates = coords;
}

ShipSegment::~ShipSegment() = default;

