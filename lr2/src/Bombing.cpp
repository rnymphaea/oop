#include "../include/Bombing.h"

void Bombing::use(const AbilitySettings& settings) {
    bool check = true;
    while (check) {
        std::srand(static_cast<unsigned int>(std::time(0)));
        int x = std::rand() % 10;
        int y = std::rand() % 10;
        auto cell = settings.field.getCell({x, y});
        auto segment = cell->getSegment();
        if (segment && segment->getHP() > 0) {
            std::cout << "Damage taken, coords: " << x << " " << y << std::endl;
            segment->damage();
            cell->updateValue();
            check = false;
        }
    }

    std::cout << "Bombing used!" << std::endl;
};
