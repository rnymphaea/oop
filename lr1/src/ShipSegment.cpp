#include "../include/ShipSegment.h"

ShipSegment::ShipSegment() :
    HP(2), state(SegmentState::Undamaged), coordinates(Coordinates{0, 0})
{}

int ShipSegment::getHP() {
    return HP;
}

void ShipSegment::damage() {
    switch (state) {
        case SegmentState::Undamaged:
            setState(SegmentState::Damaged);
            break;
        case SegmentState::Damaged:
            setState(SegmentState::Destroyed);
            break;
        case SegmentState::Destroyed:
            throw std::runtime_error("Segment is already destroyed!");
    }
    HP--;
}

void ShipSegment::printInfo() {
    std::cout << "SEGMENT INFO" << std::endl;
    std::cout << "HP: " << HP << std::endl;
    std::cout << "Coordinantes" << coordinates.x << "  " << coordinates.y << std::endl;
}

void ShipSegment::setCoordinates(Coordinates coords) {
    coordinates = coords;
}

void ShipSegment::setState(SegmentState segmentState) {
    state = segmentState;
}

ShipSegment::~ShipSegment() = default;

