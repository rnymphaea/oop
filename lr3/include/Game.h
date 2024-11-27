#ifndef LR3_GAME_H
#define LR3_GAME_H

//#include "Field.h"
//#include "AbilityManager.h"
//#include "ShipManager.h"
//#include "structures.h"
#include "GameState.h"

#include <random>
#include <ctime>
#include <memory>

enum Action {
    Save, Load, Attack, Ability, Exit
};

class Game {
public:
    Game() = default;
    void CycleGame();
private:
    bool playerTurn;
    std::shared_ptr<GameState> gameState;
    Coordinates getCoordinates();
    Action getAction();
    void save();
    std::vector<int> getLengths(int n);
    int getNumberShips();
    void placeShips(int size);
    Orientation getOrientation();
    void attack(int damage = 1);
    Coordinates getRandomCoordinates();
};

#endif //LR3_GAME_H
