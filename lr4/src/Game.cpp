#include "../include/Game.h"

void Game::newGame(const std::vector<int>& lengths) {
    playerTurn = true;
    gameState = std::make_shared<GameState>(lengths);
    placeShips(lengths.size());
    playerTurn = !playerTurn;
    placeShips(lengths.size());
}

//void Game::NewRound() {
//    std::cout << "============= Battleship =============" << std::endl;
//    std::cout << "0 - New game\n1 - Load game" << std::endl;
//    int act;
//    std::cin >> act;
//    int n;
//    std::vector<int> lengths;
//    bool firstRound = true;
//    bool playerWon = false;
//    int state;
//    if (act == 1) {
//        gameState = std::make_shared<GameState>(lengths);
//        try {
//            gameState->load();
//        }
//        catch (std::exception &err) {
//            std::cout <<"Error loading" << std::endl;
//            return;
//        }
//        isLoaded = true;
//        n = gameState->getPlayerShipManager()->getShips().size();
//        lengths = gameState->getSizes();
//    } else {
//        n = getNumberShips();
//        lengths = getLengths(n);
//        gameState = std::make_shared<GameState>(lengths);
//
//    }
//    while (true) {
//        state = CycleGame(n, playerWon, firstRound);
//        firstRound = false;
//        if (state == 1) {
//            std::cout << "You won!" << std::endl;
//            playerWon = true;
//            gameState->newCompField();
//            gameState->newCompShipManager();
//            continue;
//        } else if (state == 0) {
//            gameState = std::make_shared<GameState>(lengths);
//            std::cout << "You lose!" << std::endl;
//        } else {
//            break;
//        }
//    }
//}
//
//int Game::CycleGame(int n, bool playerWon, bool firstRound) {
//    playerTurn = true;
//    bool stop = false;
//    if (!firstRound && !playerWon && !isLoaded) {
//        n = getNumberShips();
//        auto lengths = getLengths(n);
//    }
//
//    auto playerShips = gameState->getPlayerShipManager()->getShips();
//    auto compShips = gameState->getCompShipManager()->getShips();
//    auto abilityManager = gameState->getAbilityManager();
//
//    if ((firstRound || (!firstRound && !playerWon)) && !isLoaded) {
//        placeShips(n);
//    }
//    if (!isLoaded) {
//        playerTurn = !playerTurn;
//        placeShips(n);
//    }
//
//    int damage = 1;
//    AbilitySettings abilitySettings = {gameState->getCompField(), &damage};
//    playerWon = false;
//    while (!stop && !gameEnded()) {
//        if (playerTurn) {
//            std::cout << "\nChoose action:\n 0 - Save\n 1 - Load\n 2 - Attack\n 3 - Ability\n 4 - Exit" << std::endl;
//            Action action = getAction();
//            switch (action) {
//                case Attack:
//                    playerWon = attack();
//                    break;
//                case Save:
//                    std::cout << "Saving" << std::endl;
//                    gameState->save();
//                    break;
//                case Load:
//                    std::cout << "Loading" << std::endl;
//                    try {
//                        gameState->load();
//                    }
//                    catch (std::exception &err) {
//                        std::cout <<"Error loading" <<std::endl;
//                        break;
//                    }
//                    break;
//                case Ability:
//                    try {
//                        abilityManager->useNextAbility(abilitySettings);
//                    }
//                    catch (NoAbilitiesError& err) {
//                        std::cout << err.what() << std::endl;
//                        break;
//                    }
//                    playerWon = attack(damage);
//                    damage = 1;
//                    break;
//                case Exit:
//                    std::cout << "Bye <3" << std::endl;
//                    stop = true;
//                    break;
//            }
//        } else {
//            attack();
//        }
//
//
//    }
//    if (stop) {
//        return 2;
//    }
//    return static_cast<int>(playerWon);
//}
//
//

void Game::placeShips(int size) {
    std::shared_ptr<Field> field;
    Coordinates coords;
    Orientation orientation;
    std::vector<std::shared_ptr<Ship>> ships;
    if (playerTurn) {
        field = gameState->getPlayerField();
        ships = gameState->getPlayerShipManager()->getShips();
    }
    else {
        field = gameState->getCompField();
        ships = gameState->getCompShipManager()->getShips();
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
                if (playerTurn) {
                    field->printField();
                }
                isPlaced = true;
            }
            catch (InvalidPlacementError &err) {
                if (playerTurn) {
                    std::cout << err.what() << std::endl;
                }
            }
        }
    }
    if (playerTurn) {
        std::cout << "============== Your field ==============" << std::endl;
        field->printField();
    } else {
        std::cout << "============== Computer's field ==============" << std::endl;
        field->printField();
        field->setInvisibility();
    }

}

Orientation Game::getOrientation() {
    int orientation;
    bool validInput = false;

    while (!validInput) {
        std::cin >> orientation;

        if (std::cin.fail() || orientation < 0 || orientation > 1) {
            std::cout << "Please enter 0 or 1." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            validInput = true;
        }
    }
    return static_cast<Orientation>(orientation);
}
//
bool Game::attack(Coordinates coords, int damage) {
    std::shared_ptr<Field> field;
    if (playerTurn) {
        field = gameState->getCompField();
        try {
            field->attack(coords, damage);
            auto ship = gameState->getCompShipManager()->getShipByCoordinates({coords});
            if (ship) {
                if (ship->isDestroyed()) {
                    std::cout << "Ability added! " << std::endl;
                    gameState->getAbilityManager()->addAbility();
                }
            }
            std::cout << "Attack ended!" << std::endl;
        }
        catch (InvalidAttackError & err) {
            std::cout << err.what() << std::endl;
        }
    }
    else {
        field = gameState->getPlayerField();
        coords = getRandomCoordinates();
        std::cout << "Computer attacks " << coords.x << " " << coords.y << std::endl;
        field->attack(coords);
    }
    playerTurn = !playerTurn;
    return gameEnded();
}

bool Game::ability(const AbilitySettings& abilitySettings) {
    auto abilityManager = gameState->getAbilityManager();
    abilityManager->useNextAbility(abilitySettings);
    playerTurn = true;
    return gameEnded();
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


Coordinates Game::getRandomCoordinates() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    int x = std::rand() % 10;
    int y = std::rand() % 10;
    return Coordinates{x, y};
}

std::shared_ptr<Field> Game::getPlayerField() const {
    return gameState->getPlayerField();
}

std::shared_ptr<Field> Game::getCompField() const {
    return gameState->getCompField();
}

void Game::save() {
    gameState->save();
}

void Game::load() {
    if (!gameState) {
        std::vector<int> lengths;
        gameState = std::make_shared<GameState>(lengths);
    }
    gameState->load();
}


bool Game::gameEnded() {
    return gameState->getCompShipManager()->allShipsDestroyed() || gameState->getPlayerShipManager()->allShipsDestroyed();
}
