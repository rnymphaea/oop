#include "../include/Bombing.h"

void Bombing::use(const AbilitySettings& settings) {
    bool check = true;
    std::vector<int> randomArray(10);
    for (int i = 0; i < 10; ++i) {
        randomArray[i] = i;
    }
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::random_device rd;
    std::mt19937 g(rd());
    int x, y;
    std::shuffle(randomArray.begin(), randomArray.end(), g);
    for (int i = 0; i < 10 && check; i++) {
        x = randomArray[i];
        for (int j = 0; j < 10 && check; j++) {
            y = j;
            auto cell = settings.field->getCell({x, y});
            auto segment = cell->getSegment();
            if (segment && segment->getHP() > 0) {
                std::cout << "Damage taken, coords: " << x << " " << y << std::endl;
                segment->damage();
                cell->updateValue();
                check = false;
            }
        }
    }

    std::cout << "Bombing used!" << std::endl;
};

void Bombing::info() {
    std::cout << "Bombing" << std::endl;
}
