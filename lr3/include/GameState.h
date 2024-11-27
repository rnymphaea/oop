#ifndef LR3_GAMESTATE_H
#define LR3_GAMESTATE_H

#include "ShipManager.h"
#include "AbilityManager.h"
#include <memory>
#include <vector>

class ShipManager;
class AbilityManager;
class Field;

class GameState {
public:
    explicit GameState(std::vector<int> lengths);

    std::shared_ptr<ShipManager> getPlayerShipManager() const;
    std::shared_ptr<ShipManager> getCompShipManager() const;
    std::shared_ptr<AbilityManager> getAbilityManager() const;
    std::shared_ptr<Field> getPlayerField() const;
    std::shared_ptr<Field> getCompField() const;

private:
    std::shared_ptr<ShipManager> playerShipManager;
    std::shared_ptr<ShipManager> compShipManager;
    std::shared_ptr<AbilityManager> abilityManager;
    std::shared_ptr<Field> playerField;
    std::shared_ptr<Field> compField;
};
#endif