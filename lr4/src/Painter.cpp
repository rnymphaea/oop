#include "../include/Painter.h"

void Painter::showField(std::shared_ptr<Field> field) {
    field->printField();
}
