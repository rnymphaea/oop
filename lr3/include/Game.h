#ifndef LR3_GAME_H
#define LR3_GAME_H

#include "Field.h"
#include "AbilityManager.h"
#include "ShipManager.h"
#include "structures.h"

enum Action {
    Save, Load, Attack, Ability
};

class Game {
public:
    Game() = default;
    void CycleGame();
private:
    Coordinates getCoordinates();
    Action getAction();
    void save();
    std::vector<int> getLengths(int n);
    int getNumberShips();
    void placeShips(std::vector<std::shared_ptr<Ship>> ships, int size, Field &field);
    Orientation getOrientation();
};

#endif //LR3_GAME_H
