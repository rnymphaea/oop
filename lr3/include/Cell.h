#ifndef OOP_CELL_H
#define OOP_CELL_H

#include "structures.h"
#include "ShipSegment.h"
#include <memory>

class Cell{
public:
    Cell();
    ~Cell();
    bool isVisible();
    void setVisibility();
    void setValue(CellValue cellValue);
    void setSegment(std::shared_ptr<ShipSegment> seg);
    CellValue getValue();
    std::shared_ptr<ShipSegment> getSegment();
    void updateValue();
    void setInvisibility();
private:
    Coordinates coordinates;
    CellValue value;
    bool visible;
    std::shared_ptr<ShipSegment> segment;
};

#endif //OOP_CELL_H
