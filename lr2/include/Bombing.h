#ifndef LR2_BOMBING_H
#define LR2_BOMBING_H

#include "AbilityInterface.h"
#include <random>
#include <ctime>

class Bombing : public AbilityInterface{
public:
    ~Bombing() = default;
    void use(const AbilitySettings& settings) override;
};

#endif //LR2_BOMBING_H
