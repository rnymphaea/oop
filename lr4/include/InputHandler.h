#ifndef LR4_INPUTHANDLER_H
#define LR4_INPUTHANDLER_H

#include <unordered_map>
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "File.h"  // Подключение класса FileReader
#include "structures.h"

class InputHandler {
public:
    InputHandler();
    void init(const std::string& filename = "commands.txt");
    StartCommand getStartCommandForKey(int key) const;
    Command getCommandForKey(char key) const;
    char getKeyForCommand(Command cmd) const;
    void printMappings() const;

    StartCommand getStartCommand();
    Command getCommand();

    std::vector<int> getLengths(int n);
    int getNumberShips();

    Coordinates getCoordinates();


private:
    void loadFromFile(const std::string& filename = "commands.txt");
    void setDefaultCommands();

    std::unordered_map<char, Command> keyToCommand;  // Соответствие клавиша -> команда
    std::unordered_map<Command, char> commandToKey;  // Соответствие команда -> клавиша

    Command stringToCommand(const std::string& commandStr) const;
    std::string commandToString(Command cmd) const;

};

#endif //LR4_INPUTHANDLER_H
