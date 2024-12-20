#ifndef LR4_PAINTER_H
#define LR4_PAINTER_H

#include "Field.h"
#include <iostream>
#include <memory>
#include <string>

template <typename RenderStrategy>
class Painter {
public:
    Painter() : renderer(std::make_shared<RenderStrategy>()) {}

    void showField(std::shared_ptr<Field> field, bool playerTurn) {
        renderer->showField(field, playerTurn);
    }

    void printMessage(const std::string& message) {
        renderer->printMessage(message);
    }

private:
    std::shared_ptr<RenderStrategy> renderer;
};

#endif // LR4_PAINTER_H
