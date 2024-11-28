#ifndef LR2_BOMBING_H
#define LR2_BOMBING_H

#include "AbilityInterface.h"
#include <random>
#include <ctime>
#include <algorithm>

class Bombing : public AbilityInterface{
public:
    ~Bombing() = default;
    void use(const AbilitySettings& settings) override;
    void info() override;
};

#endif //LR2_BOMBING_H
