#ifndef ABILITYINTERFACE_H
#define ABILITYINTERFACE_H

#include <queue>
#include <memory>
#include <iostream>
#include "AbilitySettings.h"

class AbilityInterface {
public:
    virtual void use(const AbilitySettings& settings) = 0;
    virtual void info() = 0;
    virtual ~AbilityInterface() = default;
};

#endif //ABILITYINTERFACE_H
