#include "../include/Game.h"

void Game::CycleGame() {
    int n = getNumberShips();
    auto lengths = getLengths(n);
    playerTurn = true;
    bool stop;
    GameState gs(lengths);
    gameState = &gs;
    auto playerShips = gs.getPlayerShipManager()->getShips();
    auto compShips = gs.getCompShipManager()->getShips();
    placeShips(playerShips, n);
    placeShips(compShips, n);
//    while (!stop) {
//
//    }
    int damage = 1;




//    std::cout << "Choose action:\n 0 - Save\n 1 - Load\n 2 - Attack\n 3 - Ability\n" << std::endl;
//    Action action = getAction();
//    switch (action) {
//        case Attack:
//            std::cout << "Attacking" << std::endl;
//            break;
//        case Save:
//            std::cout << "Saving" << std::endl;
//            break;
//        case Load:
//            std::cout << "Loading" << std::endl;
//            break;
//        case Ability:
//            std::cout << "Ability" << std::endl;
//            break;
//    }

}

Coordinates Game::getCoordinates() {
    Coordinates coords;
    while (true) {
        if (!(std::cin >> coords.x)) {
            std::cout << "Error: Invalid input for x-coordinate.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (!(std::cin >> coords.y)) {
            std::cout << "Error: Invalid input for y-coordinate.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    return coords;
}

Action Game::getAction() {
    int action;
    bool validInput = false;

    while (!validInput) {
        std::cin >> action;

        if (std::cin.fail() || action < 0 || action > 3) {
            std::cout << "Ошибка! Пожалуйста, введите число от 0 до 3." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    }
    return static_cast<Action>(action);
}

std::vector<int> Game::getLengths(int n) {
    std::vector<int> lengths(n);

    std::cout << "Введите длины кораблей: ";
    for (int i = 0; i < n; i++) {
        std::cin >> lengths[i];
    }
    return lengths;
}

int Game::getNumberShips() {
    int n;
    std::cout << "Введите количество кораблей: ";
    std::cin >> n;
    return n;
}

void Game::placeShips(std::vector<std::shared_ptr<Ship>> ships, int size) {
    Field * field;
    Coordinates coords;
    Orientation orientation;
    if (playerTurn) {
        field = gameState->getPlayerField();
    }
    else {
        field = gameState->getCompField();
    }

    for (int i = 0; i < size; i++) {
        bool isPlaced = false;
        while (!isPlaced) {
            if (playerTurn) {
                std::cout << "Введите координаты для корабля длины " << ships[i]->getLength() << ": ";
                coords = getCoordinates();
                std::cout << "Выберите расположение корабля:\n 0 - Vertical\n 1 - Horizontal" << std::endl;
                orientation = getOrientation();
            }
            else {
                coords = getRandomCoordinates();
                std::srand(static_cast<unsigned int>(std::time(0)));
                orientation = static_cast<Orientation>(std::rand() % 2);
            }

            try {
                field->placeShip(coords, ships[i], orientation);
                field->setVisibility();
                field->printField();
                isPlaced = true;
            }
            catch (InvalidPlacementError &err) {
                std::cout << err.what() << std::endl;
            }
        }
    }

}

Orientation Game::getOrientation() {
    int orientation;
    bool validInput = false;

    while (!validInput) {
        std::cin >> orientation;

        if (std::cin.fail() || orientation < 0 || orientation > 3) {
            std::cout << "Ошибка! Пожалуйста, введите число от 0 до 1." << std::endl;
            std::cin.clear();  // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем остаток ввода
        } else {
            validInput = true;
        }
    }
    return static_cast<Orientation>(orientation);
}

void Game::attack(int damage) {
    Coordinates coords;
    if (playerTurn) {
        coords = getCoordinates();
        try {
            gameState->getCompField()->attack(coords, damage);
            if (gameState->getCompShipManager()->getShipByCoordinates({1, 7})->isDestroyed()) {
                std::cout << "Ability added! " << std::endl;
                gameState->getAbilityManager()->addAbility();
            }
        }
        catch (InvalidAttackError & err) {
            std::cout << err.what() << std::endl;
        }
    }
    else {
        coords = getRandomCoordinates();
        gameState->getPlayerField()->attack(coords);
    }

}

Coordinates Game::getRandomCoordinates() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    int x = std::rand() % 10;
    int y = std::rand() % 10;
    return Coordinates{x, y};
}
