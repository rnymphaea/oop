
#include "../include/ShipSegment.h"
#include "../include/Ship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"

int main() {

//    auto ship1 = Ship(2, Orientation::Horizontal, Coordinates{2, 8});
//
//    Field field = Field();
//    field.placeShip(ship1.getCoordinates(), std::make_shared<Ship>(ship1));
//    auto ship2 = Ship(3, Orientation::Horizontal, Coordinates{6, 2});
//    field.placeShip(ship2.getCoordinates(), std::make_shared<Ship>(ship2));
//    field.attack(Coordinates{2, 1});
//    field.printField();
//    field.attack(Coordinates{7, 2});
//    field.printField();
//    field.attack(Coordinates{7, 2});
//    field.printField();
    std::vector<int> lengths = {4, 3, 2, 1};
    try {
        ShipManager manager(lengths);
        Field field;
        auto ships = manager.getShips();
        try {
            field.placeShip({1, 1}, ships[0], Orientation::Horizontal);
            field.placeShip({3, 4}, ships[1]);
            field.placeShip({6, 8}, ships[2], Orientation::Horizontal);
            field.placeShip({1, 7}, ships[3]);
//            field.setVisibility();
            field.printField();
        }
        catch (std::invalid_argument) {
            std::cout << "Cannot place this segments!" << std::endl;
        }
        field.attack({2, 2});
        field.attack({1, 1});
        field.attack({2, 1});
        field.printField();
    }
    catch (std::invalid_argument) {
        std::cout << "Invalid length of ship!";
    }



}


