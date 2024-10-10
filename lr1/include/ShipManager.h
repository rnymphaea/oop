#ifndef OOP_SHIPMANAGER_H
#define OOP_SHIPMANAGER_H

#include <memory>
#include <vector>
#include "Ship.h"

class ShipManager {
public:
    ShipManager(const std::vector<int>& sizes);
    const std::vector<std::shared_ptr<Ship>>& getShips() const;
    void printShips() const;
private:
    std::vector<std::shared_ptr<Ship>> ships;
};

#endif //OOP_SHIPMANAGER_H
