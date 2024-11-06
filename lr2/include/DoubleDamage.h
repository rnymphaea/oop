#ifndef LR2_DOUBLEDAMAGE_H
#define LR2_DOUBLEDAMAGE_H

#include "AbilityInterface.h"

class DoubleDamage : public AbilityInterface{
public:
    ~DoubleDamage() = default;
    void use() override;
};

#endif //LR2_DOUBLEDAMAGE_H
