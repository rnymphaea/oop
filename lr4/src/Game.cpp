#include "../include/Game.h"

void Game::newGame(const std::vector<int>& lengths) {
    playerTurn = true;
    gameState = std::make_shared<GameState>(lengths);
    placeShips(lengths.size());
    playerTurn = !playerTurn;
    placeShips(lengths.size());
}

void Game::newRound() {
    playerTurn = false;
    auto sizes = gameState->getSizes();
    gameState->newCompField();
    gameState->newCompShipManager();
    placeShips(sizes.size());
}

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
                std::cout << "Enter coordinates for ship with length " << ships[i]->getLength() << ": ";
                coords = getCoordinates();
                std::cout << "Orientation:\n 0 - Vertical\n 1 - Horizontal" << std::endl;
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

RoundResult Game::attack(Coordinates coords, int damage) {
    std::shared_ptr<Field> field;
    if (playerTurn) {
        field = gameState->getCompField();
        try {
            field->attack(coords, damage);
            auto ship = gameState->getCompShipManager()->getShipByCoordinates({coords});
            if (ship) {
                if (ship->isDestroyed()) {
                    gameState->getAbilityManager()->addAbility();
                }
            }
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
    bool validInput = false;
    while (!validInput) {
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
        validInput = true;
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


RoundResult Game::gameEnded() {
    if (gameState->getCompShipManager()->allShipsDestroyed()) {
        return PlayerWon;
    }
    if (gameState->getPlayerShipManager()->allShipsDestroyed()) {
        return ComputerWon;
    }
    return GameActive;
}
