#ifndef LR2_SCANNER_H
#define LR2_SCANNER_H

#include "AbilityInterface.h"

class Scanner : public AbilityInterface{
public:
    ~Scanner() = default;
    void use(const AbilitySettings& settings) override;
    void info() override;
    Coordinates getCoordinates();
};

#endif //LR2_SCANNER_H
