#include "../include/Cell.h"

Cell::Cell() : coordinates({0, 0}), visible(false), value(CellValue::Empty), segment(nullptr) {}

Cell::~Cell() = default;

void Cell::setValue(CellValue cellValue) {
    value = cellValue;
}

bool Cell::isVisible() {
    return visible;
}

void Cell::setVisibility() {
    visible = true;
}

void Cell::setInvisibility() {
    visible = false;
}

void Cell::setSegment(std::shared_ptr<ShipSegment> seg) {
    segment = seg;
}

CellValue Cell::getValue() {
    return value;
}

void Cell::loadValue(CellValue cellValue, bool visibility) {
    value = cellValue;
    visible = visibility;
    switch (value) {
        case CellValue::Segment:
            segment->setHP(2);
            break;
        case CellValue::Hit:
            segment->setHP(1);
            break;
        case CellValue::Destroyed:
            segment->setHP(0);
            break;
        case CellValue::Empty:
            break;
    }
}

void Cell::updateValue() {
    if (!segment) {
        value = CellValue::Empty;
        return;
    }
    switch (segment->getHP()) {
        case 2:
            value = CellValue::Segment;
            break;
        case 1:
            value = CellValue::Hit;
            break;
        case 0:
            value = CellValue::Destroyed;
            break;
    }

}

void Cell::setCoordinates(Coordinates coords) {
    coordinates = coords;
}

std::shared_ptr<ShipSegment> Cell:: getSegment() {
    return segment;
}
