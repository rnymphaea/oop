#ifndef OOP_FIELD_H
#define OOP_FIELD_H

#include "structures.h"
#include "Ship.h"
#include <memory>
#include <vector>
#include "Cell.h"

class Field {
public:
    Field();
    Field(const Field& other);
    Field(Field&& other);
    ~Field();

    Field& operator=(const Field& other);
    Field& operator=(Field&& other);

    bool isValidPlace(Coordinates coordinates, int length, Orientation orientation);
    void placeShip(Coordinates coordinates, const std::shared_ptr<Ship>& ship, Orientation orientation = Orientation::Vertical);
    void attack(Coordinates coordinates, int damage = 1);
    bool checkArea(Coordinates coords);
    std::shared_ptr<Cell> getCell(Coordinates coords);
    void loadCellValue(Coordinates coords, CellValue cellValue, bool visibility);

    void setVisibility();
    void setInvisibility();
    void printField();

private:
    int height;
    int width;
    std::vector<std::vector<std::shared_ptr<Cell>>> cells;
};

#endif //OOP_FIELD_H
