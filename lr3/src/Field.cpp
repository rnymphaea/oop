#include "../include/Field.h"
#include <iostream>

Field::Field() : height(10), width(10) {
    cells.resize(height);
    for (int i = 0; i < height; i++) {
        cells[i].resize(width);
        for (int j = 0; j < width; j++) {
            cells[i][j] = std::make_shared<Cell>();
        }
    }
}

//Field::Field(int height, int width) : height(height), width(width){
//    cells.resize(height);
//    for (int i = 0; i < height; i++) {
//        cells[i].resize(width);
//        for (int j = 0; j < height; j++) {
//            cells[i][j] = std::make_shared<Cell>();
//        }
//    }
//}

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
    std::cout << "  ";
    for (int i = 0; i < height; i++) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < height; i++) {
        std::cout << i << " ";
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
    if (startX > width || startY > height || startX < 0 || startY < 0) {
        return false;
    }
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
                segments[i]->setCoordinates({x, y+i});
            }
            else {
                cells[y][x+i]->setValue(CellValue::Segment);
                cells[y][x+i]->setSegment(segments[i]);
                segments[i]->setCoordinates({x+i, y});
            }
        }
    }
    else {
        throw InvalidPlacementError("Cannot place this ship!");
    }
}

void Field::attack(Coordinates coordinates, int damage) {
    int x = coordinates.x;
    int y = coordinates.y;
    if (x < 0 || x > width || y < 0 || y > height) {
        throw InvalidAttackError("coordinate X or Y of attack is out of bounds");
    }

    auto cell = cells[y][x];
    auto segment = cell->getSegment();
    cell -> setVisibility();
    if (!segment) {
        std::cout << "Miss" << std::endl;
        return;
    }

    try {
        segment->damage(damage);
        if (segment->getHP() == 1) {
            cell->setValue(CellValue::Hit);
        } else {
            cell->setValue(CellValue::Destroyed);
        }
    }
    catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }
}

void Field::setVisibility() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            cells[i][j]->setVisibility();
        }
    }
}

void Field::setInvisibility() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < height; j++) {
            cells[i][j]->setInvisibility();
        }
    }
}

bool Field::checkArea(Coordinates coords) {
    int x = coords.x;
    int y = coords.y;
    if (x >= width || y >= height) {
        std::cout << "Invalid coordinates" << std::endl;
        return false;
    }
    if (cells[y][x]->getSegment()) {
        return true;
    }

    if (y + 1 < height) {
        if (cells[y + 1][x]->getSegment()) {
            return true;
        }
    }
    if (x + 1 < width) {
        if (cells[y][x + 1]->getSegment()) {
            return true;
        }
    }

    if (x + 1 < width && y + 1 < height) {
        if (cells[y+1][x+1]->getSegment()) {
            return true;
        }
    }

    return false;
}

std::shared_ptr<Cell> Field::getCell(Coordinates coords) {
    return cells[coords.y][coords.x];
}

Field::~Field() = default;
