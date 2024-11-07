#ifndef LR2_ABILITYSETTINGS_H
#define LR2_ABILITYSETTINGS_H

#include "structures.h"
#include "Field.h"

struct AbilitySettings {
    Coordinates coordinates;
    Field & field;
    int * damage;
};

#endif //LR2_ABILITYSETTINGS_H
