#include "../include/ShipSegment.h"
#include "../include/Ship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"
#include "../include/AbilityManager.h"

int main() {
    std::vector<int> lengths = {4, 3, 2, 1};
    ShipManager shipManager(lengths);
    AbilityManager abilityManager;
    Field field;
    auto ships = shipManager.getShips();

    int damage = 1;

    try {
        field.placeShip({1, 2}, ships[0], Orientation::Horizontal);
        field.placeShip({3, 4}, ships[1]);
        field.placeShip({6, 8}, ships[2], Orientation::Horizontal);
        field.placeShip({1, 7}, ships[3]);
        shipManager.printShips();
//        field.setVisibility();
        field.printField();
    }
    catch (std::invalid_argument&) {
        std::cout << "Cannot place this segments!" << std::endl;
    }
    field.attack({3, 4}, damage);
    std::cout << shipManager.getShipByCoordinates({3, 4})->isDestroyed() << std::endl;
    field.attack({3, 4}, damage);
    field.attack({1, 3}, damage);
    field.attack({1, 7}, 2);
    std::cout << shipManager.getShipByCoordinates({1, 7})->isDestroyed() << std::endl;

    if (shipManager.getShipByCoordinates({1, 7})->isDestroyed()) {
        abilityManager.addAbility();
        abilityManager.useNextAbility();
    }

//    field.printField();

}


