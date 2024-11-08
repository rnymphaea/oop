#include "../include/ShipSegment.h"
#include "../include/Ship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"
#include "../include/AbilityManager.h"

int main() {
    std::vector<int> lengths = {4, 3, 2, 1, 1};
    ShipManager shipManager(lengths);
    AbilityManager abilityManager;
    std::shared_ptr<AbilityInterface> currentAbility;
    Field field;

    auto ships = shipManager.getShips();

    int damage = 1;
    AbilitySettings abilitySettings = {{1, 1}, field, &damage};

    field.placeShip({1, 2}, ships[0], Orientation::Horizontal);
    field.placeShip({3, 4}, ships[1]);
    field.placeShip({8, 8}, ships[2], Orientation::Horizontal);
    field.placeShip({1, 7}, ships[3]);
//    field.setVisibility();
    field.printField();

    try {
        field.placeShip({99, 4}, ships[4]);
    }

    catch (InvalidPlacementError& err) {
        std::cout << err.what() << std::endl;
    }

    try {
        field.attack({3, 44}, damage);
    }
    catch (InvalidAttackError& err) {
        std::cout << err.what() << std::endl;
    }

    field.attack({3, 4}, damage);
    field.attack({3, 4}, damage);
    field.attack({1, 3}, damage);
    abilityManager.useNextAbility(abilitySettings);

    field.attack({1, 7}, damage);
    field.attack({1, 7});
    if (shipManager.getShipByCoordinates({1, 7})->isDestroyed()) {
        std::cout << "Ability added! " << std::endl;
        abilityManager.addAbility();
    }


    field.attack({1, 2}, damage);

    try {
        abilityManager.useNextAbility(abilitySettings);
        abilityManager.useNextAbility(abilitySettings);
        abilityManager.useNextAbility(abilitySettings);
        abilityManager.useNextAbility(abilitySettings);
        abilityManager.useNextAbility(abilitySettings);
        abilityManager.useNextAbility(abilitySettings);
    }
    catch (NoAbilitiesError& err) {
        std::cout << err.what() << std::endl;
    }

    field.printField();

}


