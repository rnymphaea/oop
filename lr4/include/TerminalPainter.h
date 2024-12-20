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

    void printMappings(const std::unordered_map<char, Command> keyToCommand) {

        for (const auto& [key, cmd] : keyToCommand) {
            std::string command;
            switch (cmd) {
                case Save:
                    command = "Save";
                    break;
                case Load:
                    command = "Load";
                    break;
                case Attack:
                    command = "Attack";
                    break;
                case Ability:
                    command = "Ability";
                    break;
                case ShowField:
                    command = "ShowField";
                    break;
                case Exit:
                    command = "Exit";
                    break;
                default:
                    command = "Unknown";
                    break;
            }
            std::cout << "Key '" << key << "' -> " << command << std::endl;
        }
    }
};

#endif // LR4_TERMINALPAINTER_H
