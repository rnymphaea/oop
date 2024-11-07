#include "../include/AbilityManager.h"


std::shared_ptr<AbilityInterface> AbilityManager::addAbility() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    int randomNumber = std::rand() % 3;

    std::shared_ptr<AbilityInterface> ability;
    switch (randomNumber) {
        case 0:
            ability = std::make_shared<DoubleDamage>();
            break;
        case 1:
            ability = std::make_shared<Scanner>();
            break;
        case 2:
            ability = std::make_shared<Bombing>();
            break;
    }
    abilitiesQueue.push(ability);
    return ability;
}

void AbilityManager::useNextAbility(const AbilitySettings& settings) {
    if (!abilitiesQueue.empty()) {
        abilitiesQueue.front() -> use(settings);
        abilitiesQueue.pop();
    } else {
        throw NoAbilitiesError("You have no abilities right now!");
    }
}

bool AbilityManager::isEmpty() const {
    return abilitiesQueue.empty();
}