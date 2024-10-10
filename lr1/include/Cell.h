//
// Created by alex on 09.10.24.
//

#ifndef OOP_CELL_H
#define OOP_CELL_H

#include "structures.h"
#include "ShipSegment.h"
#include <memory>

class Cell{
public:
    Cell();
    ~Cell();
//    CellState getState();
//    void setState(CellState cellState);
    bool isVisible();
    void setVisibility();
    void setValue(CellValue cellValue);
    void setSegment(std::shared_ptr<ShipSegment> seg);
    CellValue getValue();
    std::shared_ptr<ShipSegment> getSegment();
private:
    Coordinates coordinates;
//    CellState state;
    CellValue value;
    bool visible;
    std::shared_ptr<ShipSegment> segment;
};

#endif //OOP_CELL_H
