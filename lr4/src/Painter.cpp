#include "../include/Painter.h"

void Painter::showField(std::shared_ptr<Field> field, bool playerTurn) {
    if (playerTurn) {
        std::cout << "============== Your field ==============" << std::endl;
    }
    else {
        std::cout << "============== Computer's field ==============" << std::endl;
    }
    field->printField();
}
