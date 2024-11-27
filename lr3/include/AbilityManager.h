#ifndef ABILITYMANAGER_H
#define ABILITYMANAGER_H

#include "AbilityInterface.h"
#include "DoubleDamage.h"
#include "Scanner.h"
#include "Bombing.h"
#include "structures.h"
#include <random>
#include <ctime>

class AbilityManager {
private:
    std::queue<std::shared_ptr<AbilityInterface>> abilitiesQueue;

public:
    AbilityManager();
    void addAbility();
    void useNextAbility(const AbilitySettings& settings);
    bool isEmpty() const;
};

#endif //ABILITYMANAGER_H
