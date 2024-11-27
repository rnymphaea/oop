#include "../include/GameState.h"

GameState::GameState(std::vector<int> lengths) {
    ShipManager sm1(lengths);
    playerShipManager = &sm1;
    ShipManager sm2(lengths);
    compShipManager = &sm2;
    AbilityManager am;
    abilityManager = &am;
    auto field1 = Field{};
    auto field2 = Field{};
    playerField = &field1;
    compField = &field2;
}

ShipManager * GameState::getPlayerShipManager() {
    return playerShipManager;
}

ShipManager * GameState::getCompShipManager() {
    return playerShipManager;
}

AbilityManager * GameState::getAbilityManager() {
    return abilityManager;
}

Field * GameState::getPlayerField() {
    return playerField;
}

Field * GameState::getCompField() {
    return compField;
}
