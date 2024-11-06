#include "../include/AbilityManager.h"
#include "../include/DoubleDamage.h"
#include "../include/Scanner.h"
#include "../include/Bombing.h"

void AbilityManager::addAbility() {
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
}

void AbilityManager::useNextAbility() {
    if (!abilitiesQueue.empty()) {
        abilitiesQueue.front() -> use();
        abilitiesQueue.pop();
    } else {
        std::cout << "No abilities in the queue!" << std::endl;
    }
}

bool AbilityManager::isEmpty() const {
    return abilitiesQueue.empty();
}
