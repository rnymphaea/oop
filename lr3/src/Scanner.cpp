#include "../include/Scanner.h"

void Scanner::use(const AbilitySettings& settings) {
    if (settings.field.checkArea(settings.coordinates)) {
        std::cout << "There is a ship!" << std::endl;
    } else {
        std::cout << "There is no ship!" << std::endl;
    }
};
