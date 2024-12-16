#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "AbilityInterface.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Bombing.h"
#include "structures.h"
#include <random>
#include <ctime>
#include <algorithm>

class AbilityManager {
private:
    std::queue<std::shared_ptr<AbilityInterface>> abilitiesQueue;

public:
    AbilityManager();
    AbilityManager(const std::vector<std::string>& info);
    void addAbility();
    void useNextAbility(const AbilitySettings& settings);
    bool isEmpty() const;
    std::string getInfo();
};

#endif //ABILITYMANAGER_H
