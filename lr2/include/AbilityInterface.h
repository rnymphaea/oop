#ifndef ABILITYINTERFACE_H
#define ABILITYINTERFACE_H

#include <queue>
#include <memory>
#include <iostream>

class AbilityInterface {
public:
    virtual void use() = 0;
    virtual ~AbilityInterface() = default;
};

#endif //ABILITYINTERFACE_H
