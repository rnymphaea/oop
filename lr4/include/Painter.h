#ifndef LR4_PAINTER_H
#define LR4_PAINTER_H

#include "Field.h"

class Painter {
public:
    Painter() = default;
    void showField(std::shared_ptr<Field> field);
};

#endif //LR4_PAINTER_H
