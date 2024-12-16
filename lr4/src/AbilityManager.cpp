#include "../include/AbilityManager.h"

AbilityManager::AbilityManager() {
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

AbilityManager::AbilityManager(const std::vector<std::string>& info) {
    for (const auto& typeStr : info) {
        std::shared_ptr<AbilityInterface> ability;

        if (typeStr == "0") {
            ability = std::make_shared<Bombing>();
        } else if (typeStr == "1") {
            ability = std::make_shared<DoubleDamage>();
        } else if (typeStr == "2") {
            ability = std::make_shared<Scanner>();
        } else {
            std::cerr << "Invalid ability type: " << typeStr << std::endl;
            continue;
        }

        abilitiesQueue.push(ability);
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

std::string AbilityManager::getInfo() {
    std::string out;
    std::queue<std::shared_ptr<AbilityInterface>> tempQueue = abilitiesQueue;
    while (!tempQueue.empty()) {
        auto ability = tempQueue.front();
        tempQueue.pop();
        if (std::dynamic_pointer_cast<Bombing>(ability)) {
            out += "0 "; // Для Bombing - 0
        } else if (std::dynamic_pointer_cast<DoubleDamage>(ability)) {
            out += "1 "; // Для DoubleDamage - 1
        } else if (std::dynamic_pointer_cast<Scanner>(ability)) {
            out += "2 "; // Для Scanner - 2
        }
    }

    return out;
}
