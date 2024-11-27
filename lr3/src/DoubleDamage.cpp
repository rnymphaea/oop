#include "../include/DoubleDamage.h"

void DoubleDamage::use(const AbilitySettings& settings) {
    std::cout << "Double damage used!" << std::endl;
    *settings.damage = 2;
};
