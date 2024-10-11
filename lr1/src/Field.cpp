#include "../include/Field.h"
#include <iostream>

Field::Field() : height(10), width(10) {
    cells.resize(height);
    for (int i = 0; i < height; i++) {
        cells[i].resize(width);
        for (int j = 0; j < height; j++) {
            cells[i][j] = std::make_shared<Cell>();
        }
    }
}

Field::Field(int height, int width) : height(height), width(width){
    cells.resize(height);
    for (int i = 0; i < height; i++) {
        cells[i].resize(width);
        for (int j = 0; j < height; j++) {
            cells[i][j] = std::make_shared<Cell>();
        }
    }
}

Field::Field(const Field &other)
        : height(other.height),
          width(other.width),
          cells(other.cells){
}

Field::Field(Field &&other)
        : height(other.height), width(other.width),
          cells(std::move(other.cells)){}

Field &Field::operator=(const Field &other) {
    if (this != &other) {
        height = other.height;
        width = other.width;
        cells = other.cells;
    }
    return *this;
}

Field &Field::operator=(Field &&other) {
    if (this != &other) {
        height = other.height;
        width = other.width;
        cells = std::move(other.cells);
    }
    return *this;
}

void Field::printField() {
    const char* resetColor = "\033[0m";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            CellValue value = cells[i][j]->getValue();
            if (cells[i][j] -> isVisible()) {
                std::cout << "\033[32m" << static_cast<char>(value) << resetColor << " ";
            }
            else {
                std::cout << "\033[34m" << "~" << resetColor << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Field::isValidPlace(Coordinates coordinates, int length, Orientation orientation) {
    int startX = coordinates.x;
    int startY = coordinates.y;

    if (orientation == Orientation::Vertical) {
        if (startY + length > height) {
            return false;
        }
    } else {
        if (startX + length > width) {
            return false;
        }
    }

    for (int segmentIndex = 0; segmentIndex < length; ++segmentIndex) {
        for (int yOffset = -1; yOffset <= 1; ++yOffset) {
            for (int xOffset = -1; xOffset <= 1; ++xOffset) {
                int checkY = startY + (orientation == Orientation::Vertical ? segmentIndex : 0) + yOffset;
                int checkX = startX + (orientation == Orientation::Horizontal ? segmentIndex : 0) + xOffset;

                if (checkY >= 0 && checkY < height && checkX >= 0 && checkX < width) {
                    if (cells[checkY][checkX]->getValue() != CellValue::Empty) {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void Field::placeShip(Coordinates coordinates, const std::shared_ptr<Ship>& ship, Orientation orientation) {
    int length = ship->getLength();
    int x = coordinates.x;
    int y = coordinates.y;
    auto segments = ship->getSegments();
    if (isValidPlace(coordinates, length, orientation)) {
        ship ->setCoordinates(coordinates);
        for (int i = 0; i < length; i++) {
            if (orientation == Orientation::Vertical) {
                cells[y+i][x]->setValue(CellValue::Segment);
                cells[y+i][x]->setSegment(segments[i]);
            }
            else {
                cells[y][x+i]->setValue(CellValue::Segment);
                cells[y][x+i]->setSegment(segments[i]);
            }
        }
    }
    else {
        throw std::invalid_argument("Cannot place this ship!");
    }
}

void Field::attack(Coordinates coordinates) {
    int x = coordinates.x;
    int y = coordinates.y;
    if (x < 0 || x > 9 || y < 0 || y > 9) {
        throw std::invalid_argument("Invalid coordinates!");
    }

    auto cell = cells[y][x];
    auto value = cell->getValue();
    auto segment = cell->getSegment();

    switch (value) {
        case CellValue::Empty:
            std::cout << "Miss" << std::endl;
            cell -> setVisibility();
            break;
        case CellValue::Segment:
            std::cout << "Hit" << std::endl;
            cell->setValue(CellValue::Hit);
            cell -> setVisibility();
            segment->damage();
            break;
        case CellValue::Hit:
            std::cout << "Destroyed" << std::endl;
            cell->setValue(CellValue::Destroyed);
            segment->damage();
            break;
        case CellValue::Destroyed:
            std::cout << "Segment is already destroyed!";
            break;
    }
}

void Field::setVisibility() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            cells[i][j]->setVisibility();
        }
    }
}

Field::~Field() = default;
