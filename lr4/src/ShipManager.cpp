#include "../include/ShipManager.h"

ShipManager::ShipManager(const std::vector<int>& lengths) {
    for (const auto& length : lengths) {
        if (length < 1 || length > 4) {
            throw std::invalid_argument("Invalid length of ship!");
        }
        ships.push_back(std::make_shared<Ship>(length));
    }
}

ShipManager::ShipManager(const std::vector<std::shared_ptr<Ship>> Ships) {
    ships = Ships;
}

const std::vector<std::shared_ptr<Ship>>& ShipManager::getShips() const {
    return ships;
}

const std::shared_ptr<Ship> ShipManager::getShipByCoordinates(Coordinates coords) const {
    for (auto ship : ships) {
        for (auto segment : ship->getSegments()) {
            if (segment->getCoordinates() == coords) {
                return ship;
            }
        }
    }
    return nullptr;
}

void ShipManager::printShips() const {
    for (const auto &ship: ships) {
        ship->printInfoShip();
    }
}

bool ShipManager::allShipsDestroyed() {
    bool check = false;
    for (const auto &ship: ships) {
        if (!ship->isDestroyed()) {
            return false;
        }
    }
    return true;
}

std::string ShipManager::getInfo() {
    std::string out;
    for (const auto &ship: ships) {
        out += ship->getInfo();
    }
}
