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

void Cell::setSegment(std::shared_ptr<ShipSegment> seg) {
    segment = seg;
}

CellValue Cell::getValue() {
    return value;
}

std::shared_ptr<ShipSegment> Cell:: getSegment() {
    return segment;
}
