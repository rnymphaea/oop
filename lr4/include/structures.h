#ifndef OOP_STRUCTURES_H
#define OOP_STRUCTURES_H

#include <iostream>
#include "InvalidPlacementError.h"
#include "InvalidAttackError.h"
#include "NoAbilitiesError.h"

enum class SegmentState{Undamaged, Damaged, Destroyed};

enum class Orientation{Vertical, Horizontal};

enum class CellValue : char {
    Empty = '.',
    Segment = 'S',
    Hit = 'W',
    Destroyed = 'X'
};

enum Command {
    Save,
    Load,
    Attack,
    Ability,
    ShowField,
    Exit,
    Unknown
};

enum class StartCommand : int {
    NewGame,
    LoadGame,
    Unknown
};



struct Coordinates{
    int x;
    int y;

    bool operator==(const Coordinates &other) const {
        return x == other.x && y == other.y;
    }
};

#endif //OOP_STRUCTURES_H
