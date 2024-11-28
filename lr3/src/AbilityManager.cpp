#include "../include/AbilityManager.h"

AbilityManager::AbilityManager() {
//    abilitiesQueue.push(std::make_shared<DoubleDamage>());
//    abilitiesQueue.push(std::make_shared<Scanner>());
//    abilitiesQueue.push(std::make_shared<Bombing>());
    std::vector<std::shared_ptr<AbilityInterface>> abilities = {
            std::make_shared<DoubleDamage>(),
            std::make_shared<Scanner>(),
            std::make_shared<Bombing>()
    };

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(abilities.begin(), abilities.end(), g);

    for (const auto& ability : abilities) {
        abilitiesQueue.push(ability);
    }

    std::cout << "Next ability: ";
    if (!abilitiesQueue.empty()) {
        abilitiesQueue.front()->info();
    }
}

void AbilityManager::addAbility() {
    std::cout << "Added new ability: ";
    std::srand(static_cast<unsigned int>(std::time(0)));
    int randomNumber = std::rand() % 3;

    std::shared_ptr<AbilityInterface> ability;
    switch (randomNumber) {
        case 0:
            ability = std::make_shared<DoubleDamage>();
            std::cout << "Double damage" << std::endl;
            break;
        case 1:
            ability = std::make_shared<Scanner>();
            std::cout << "Scanner" << std::endl;
            break;
        case 2:
            ability = std::make_shared<Bombing>();
            std::cout << "Bombing" << std::endl;
            break;
    }
    abilitiesQueue.push(ability);
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
