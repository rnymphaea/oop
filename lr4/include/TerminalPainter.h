#ifndef LR4_TERMINALPAINTER_H
#define LR4_TERMINALPAINTER_H

#include "Field.h"
#include <iostream>
#include <string>

class TerminalPainter {
public:
    void showField(std::shared_ptr<Field> field, bool playerTurn) {
        if (playerTurn) {
            std::cout << "============== Your field ==============" << std::endl;
        } else {
            std::cout << "============== Computer's field ==============" << std::endl;
        }
        field->printField();
    }

    void printMessage(const std::string& message) {
        std::cout << message << std::endl;
    }
};

#endif // LR4_TERMINALPAINTER_H
