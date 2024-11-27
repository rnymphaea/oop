#ifndef LR3_GAMESTATE_H
#define LR3_GAMESTATE_H

#include "ShipManager.h"
#include "AbilityManager.h"
#include "Field.h"

class GameState {
public:
    GameState(std::vector<int> lengths);
    ShipManager* getPlayerShipManager();
    ShipManager* getCompShipManager();
    Field* getPlayerField();
    Field* getCompField();
    AbilityManager* getAbilityManager();
private:
    ShipManager * playerShipManager;
    ShipManager * compShipManager;
    Field * playerField;
    Field * compField;
    AbilityManager * abilityManager;
};

#endif //LR3_GAMESTATE_H
