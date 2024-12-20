#include "../include/InputHandler.h"

// Преобразование строки в команду
Command InputHandler::stringToCommand(const std::string &commandStr) const {
    if (commandStr == "Save") return Save;
    if (commandStr == "Load") return Load;
    if (commandStr == "Attack") return Attack;
    if (commandStr == "Ability") return Ability;
    if (commandStr == "ShowField") return ShowField;
    if (commandStr == "Exit") return Exit;
    return Unknown;
}

// Преобразование команды в строку
std::string InputHandler::commandToString(Command cmd) const {
    switch (cmd) {
        case Save: return "Save";
        case Load: return "Load";
        case Attack: return "Attack";
        case Ability: return "Ability";
        case ShowField: return "ShowField";
        case Exit: return "Exit";
        default: return "Unknown";
    }
}

InputHandler::InputHandler() {};

void InputHandler::init(const std::string &filename) {
    try {
        loadFromFile(filename);
    }
    catch (std::exception &err) {
        std::cout << err.what() << std::endl;
        std::cout << "Default command set used" << std::endl;
        setDefaultCommands();
    }
}


void InputHandler::setDefaultCommands() {
    keyToCommand.clear();
    commandToKey.clear();

    for (int cmd = Save; cmd <= Exit; ++cmd) {
        keyToCommand[static_cast<char>('0' + cmd)] = static_cast<Command>(cmd);  // Пример: '0', '1', '2' и т.д.
        commandToKey[static_cast<Command>(cmd)] = static_cast<char>('0' + cmd);
    }
}

void InputHandler::loadFromFile(const std::string& filename) {
    keyToCommand.clear();
    commandToKey.clear();

    FileReader fileReader(filename);
    std::ifstream& infile = fileReader.getInfile();

    std::string commandStr;
    char key;

    while (infile >> commandStr >> key) {
        Command cmd = stringToCommand(commandStr);

        if (cmd == Unknown) {
            throw std::runtime_error("Unknown command in file: " + commandStr);
        }

        if (commandToKey.find(cmd) != commandToKey.end()) {
            throw std::runtime_error("Command " + commandStr + " is already assigned to a key");
        }

        if (keyToCommand.find(key) != keyToCommand.end()) {
            throw std::runtime_error(std::string("Key '") + key + "' is already assigned to another command");
        }

        keyToCommand[key] = cmd;
        commandToKey[cmd] = key;
    }

    for (int cmd = Save; cmd <= Exit; ++cmd) {
        if (commandToKey.find(static_cast<Command>(cmd)) == commandToKey.end()) {
            throw std::runtime_error("Command " + commandToString(static_cast<Command>(cmd)) + " is not assigned to any key");
        }
    }
}

StartCommand InputHandler::getStartCommandForKey(int key) const {
    switch (key) {
        case 0:
            return StartCommand::NewGame;
        case 1:
            return StartCommand::LoadGame;
        default:
            return StartCommand::Unknown;
    }
}

Command InputHandler::getCommandForKey(char key) const {
    auto it = keyToCommand.find(key);
    if (it != keyToCommand.end()) {
        return it->second;
    }
    return Unknown;
}

char InputHandler::getKeyForCommand(Command cmd) const {
    auto it = commandToKey.find(cmd);
    if (it != commandToKey.end()) {
        return it->second;
    }
    throw std::runtime_error("No key assigned to command " + commandToString(cmd));
}

void InputHandler::printMappings() const {
    for (const auto& [key, cmd] : keyToCommand) {
        std::cout << "Key '" << key << "' -> " << commandToString(cmd) << std::endl;
    }
}

StartCommand InputHandler::getStartCommand() {
    StartCommand cmd = StartCommand::Unknown;
    int key;
    while (cmd == StartCommand::Unknown) {
        std::cout << "0 - New game\n1 - Load game" << std::endl;
        std::cin >> key;
        if (std::cin.fail()) {
            std::cout << "Invalid input" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        cmd = getStartCommandForKey(key);
        if (cmd == StartCommand::Unknown) {
            std::cout << "Unknown key! Please try again." << std::endl;
        }
    }
    return cmd;
}

Command InputHandler::getCommand() {
    printMappings();
    std::cout << std::endl;
    std::cout << "Enter a key for a command: ";
    char key;
    std::cin >> key;

    Command cmd = getCommandForKey(key);
    if (cmd == Unknown) {
        std::cout << "Unknown key! Please try again." << std::endl;
    }
    return cmd;
}

std::vector<int> InputHandler::getLengths(int n) {
    std::vector<int> lengths(n);

    std::cout << "Enter sizes of " << n << " ships:\n";
    for (int i = 0; i < n; i++) {
        bool validInput = false;
        while (!validInput) {
            std::cout << "Size of ship " << i + 1 << ": ";
            std::cin >> lengths[i];

            if (std::cin.fail() || lengths[i] <= 0 || lengths[i] > 4) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid size. Please enter a positive integer between 1 and 4.\n";
            } else {
                validInput = true;
            }
        }
    }
    return lengths;
}

int InputHandler::getNumberShips() {
    int n;
    bool validInput = false;
    while (!validInput) {
        std::cout << "Enter the count of ships: ";
        std::cin >> n;

        if (std::cin.fail() || n <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid number. Please enter a positive integer.\n";
        } else {
            validInput = true;
        }
    }
    return n;
}

Coordinates InputHandler::getCoordinates() {
    std::cout << "Enter coordinates: ";
    Coordinates coords;
    bool validInput = false;
    while (!validInput) {
        if (!(std::cin >> coords.x)) {
            std::cout << "Error: Invalid input for x-coordinate.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (!(std::cin >> coords.y)) {
            std::cout << "Error: Invalid input for y-coordinate.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        validInput = true;
    }
    return coords;
}

