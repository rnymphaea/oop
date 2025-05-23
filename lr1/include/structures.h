#ifndef OOP_STRUCTURES_H
#define OOP_STRUCTURES_H

#include <iostream>

enum class SegmentState{Undamaged, Damaged, Destroyed};

enum class Orientation{Vertical, Horizontal};

enum class CellValue : char {
    Empty = '.',
    Segment = 'S',
    Hit = 'W',
    Destroyed = 'X'
};


struct Coordinates{
    int x;
    int y;

    bool operator==(const Coordinates &other) const {
        return x == other.x && y == other.y;
    }
};

#endif //OOP_STRUCTURES_H
