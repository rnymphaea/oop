#ifndef LR2_BOMBING_H
#define LR2_BOMBING_H

#include "AbilityInterface.h"

class Bombing : public AbilityInterface{
public:
    ~Bombing() = default;
    void use() override;
};

#endif //LR2_BOMBING_H
