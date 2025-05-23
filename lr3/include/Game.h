#ifndef LR3_GAME_H
#define LR3_GAME_H
#include "GameState.h"

#include <random>
#include <ctime>
#include <memory>
#include <exception>

enum Action {
    Save, Load, Attack, Ability, Exit
};

class Game {
public:
    Game() = default;
    int CycleGame(int n, bool playerWon, bool firstRound);
    void NewRound();
private:
    bool isLoaded;
    bool playerTurn;
    std::shared_ptr<GameState> gameState;
    Coordinates getCoordinates();
    Action getAction();
    void save();
    std::vector<int> getLengths(int n);
    int getNumberShips();
    void placeShips(int size);
    Orientation getOrientation();
    bool attack(int damage = 1);
    bool gameEnded();
    Coordinates getRandomCoordinates();
};

#endif //LR3_GAME_H
