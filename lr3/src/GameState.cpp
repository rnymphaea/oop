#include "../include/GameState.h"

GameState::GameState(std::vector<int> lengths)
        : playerShipManager(std::make_shared<ShipManager>(lengths)),
          compShipManager(std::make_shared<ShipManager>(lengths)),
          abilityManager(std::make_shared<AbilityManager>()),
          playerField(std::make_shared<Field>()),
          compField(std::make_shared<Field>()) { }

std::shared_ptr<ShipManager> GameState::getPlayerShipManager() const {
    return playerShipManager;
}

std::shared_ptr<ShipManager> GameState::getCompShipManager() const {
    return compShipManager;
}

std::shared_ptr<AbilityManager> GameState::getAbilityManager() const {
    return abilityManager;
}

std::shared_ptr<Field> GameState::getPlayerField() const {
    return playerField;
}

std::shared_ptr<Field> GameState::getCompField() const {
    return compField;
}
