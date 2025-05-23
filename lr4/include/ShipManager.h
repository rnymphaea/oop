#ifndef OOP_SHIPMANAGER_H
#define OOP_SHIPMANAGER_H

#include <memory>
#include <vector>
#include "Ship.h"

class ShipManager {
public:
    ShipManager(const std::vector<int>& sizes);
    ShipManager(const std::vector<std::shared_ptr<Ship>> Ships);
    const std::vector<std::shared_ptr<Ship>>& getShips() const;
    void printShips() const;
    const std::shared_ptr<Ship> getShipByCoordinates(Coordinates coords) const;
    bool allShipsDestroyed();
    std::string getInfo();
private:
    std::vector<std::shared_ptr<Ship>> ships;
};

#endif //OOP_SHIPMANAGER_H
