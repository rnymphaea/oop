#ifndef LR2_ABILITYSETTINGS_H
#define LR2_ABILITYSETTINGS_H

#include "Field.h"
#include "structures.h"


struct AbilitySettings {
    std::shared_ptr<Field> field;
    int * damage;
};

#endif //LR2_ABILITYSETTINGS_H
