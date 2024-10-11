#include "../include/ShipSegment.h"
#include "../include/Ship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"

int main() {
    std::vector<int> lengths = {4, 3, 2, 1};
    try {
        ShipManager manager(lengths);
        Field field;
        auto ships = manager.getShips();
        try {
            field.placeShip({1, 2}, ships[0], Orientation::Horizontal);
            field.placeShip({3, 4}, ships[1]);
            field.placeShip({6, 8}, ships[2], Orientation::Horizontal);
            field.placeShip({1, 7}, ships[3]);
            field.setVisibility();
            field.printField();
        }
        catch (std::invalid_argument&) {
            std::cout << "Cannot place this segments!" << std::endl;
        }
        field.attack({3, 4});
        field.attack({1, 3});
        field.attack({1, 3});
        field.printField();
    }
    catch (std::invalid_argument&) {
        std::cout << "Invalid length of ship!";
    }
}


