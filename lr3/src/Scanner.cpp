#include "../include/Scanner.h"

void Scanner::use(const AbilitySettings& settings) {
    std::cout << "Enter coordinates for scanning: ";
    auto coords = getCoordinates();
    if (settings.field->checkArea(coords)) {
        std::cout << "There is a ship!" << std::endl;
    } else {
        std::cout << "There is no ship!" << std::endl;
    }
};

void Scanner::info() {
    std::cout << "Scanner" << std::endl;
}

Coordinates Scanner::getCoordinates() {
    Coordinates coords;
    while (true) {
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
        break;
    }
    return coords;
}
