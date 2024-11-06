#ifndef LR2_SCANNER_H
#define LR2_SCANNER_H

#include "AbilityInterface.h"

class Scanner : public AbilityInterface{
public:
    ~Scanner() = default;
    void use() override;
};

#endif //LR2_SCANNER_H
