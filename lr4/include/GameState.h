#ifndef LR3_GAMESTATE_H
#define LR3_GAMESTATE_H

#include "ShipManager.h"
#include "AbilityManager.h"
#include "File.h"

#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <functional>

class ShipManager;
class AbilityManager;
class Field;

class GameState {
public:
    GameState(std::vector<int> lengths);

    std::shared_ptr<ShipManager> getPlayerShipManager() const;
    std::shared_ptr<ShipManager> getCompShipManager() const;
    std::shared_ptr<AbilityManager> getAbilityManager() const;
    std::shared_ptr<Field> getPlayerField() const;
    std::shared_ptr<Field> getCompField() const;
    void newCompShipManager();
    void newCompField();
    std::vector<int> getSizes();

    friend std::ostream& operator<<(std::ostream& out, const GameState& state);
    friend std::istream& operator>>(std::istream& in, GameState& state);

    void save(const std::string& filename = "save");
    void load(const std::string& filename = "save");

private:
    std::vector<int> sizes;
    std::shared_ptr<ShipManager> playerShipManager;
    std::shared_ptr<ShipManager> compShipManager;
    std::shared_ptr<AbilityManager> abilityManager;
    std::shared_ptr<Field> playerField;
    std::shared_ptr<Field> compField;
};
#endif