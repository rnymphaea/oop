#include "../include/Game.h"

void Game::CycleGame() {
    std::cout << "Выберите действие:\n 0 - сохранение\n 1 - загрузка\n 2 - атака\n 3 - способность\n" << std::endl;
    Action action = getAction();
    switch (action) {
        case Attack:
            std::cout << "Атака" << std::endl;
            break;
        case Save:
            std::cout << "Сохранение" << std::endl;
            break;
        case Load:
            std::cout << "Load" << std::endl;
            break;
        case Ability:
            std::cout << "Ability" << std::endl;
            break;
    }
    int n = getNumberShips();

    auto lengths = getLengths(n);


    ShipManager shipManager(lengths);
    Field field;

    int damage = 1;
    auto ships = shipManager.getShips();
    placeShips(ships, n, field);

}

Coordinates Game::getCoordinates() {
    Coordinates coords;
    while (true) {
        // Пытаемся считать x
        if (!(std::cin >> coords.x)) {
            std::cout << "Error: Invalid input for x-coordinate.\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Пытаемся считать y
        if (!(std::cin >> coords.y)) {
            std::cout << "Error: Invalid input for y-coordinate.\n";

            // Очищаем флаг ошибки
            std::cin.clear();

            // Очищаем остаточные данные в буфере ввода
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Если оба ввода успешны, выходим из цикла
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
            // Если ввод некорректный (не целое число или число вне диапазона)
            std::cout << "Ошибка! Пожалуйста, введите число от 0 до 3." << std::endl;

            // Сбрасываем ошибочный ввод
            std::cin.clear();  // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем остаток ввода
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
        std::cout << lengths[i];

         // Считываем длину каждого корабля
    }

    std::cout << "Длины кораблей: ";
    for (int i = 0; i < n; i++) {
        std::cout << lengths[i] << " ";  // Выводим длины кораблей
    }
    return lengths;
}

int Game::getNumberShips() {
    int n;
    std::cout << "Введите количество кораблей: ";
    std::cin >> n;  // Считываем количество кораблей
    return n;
}

void Game::placeShips(std::vector<std::shared_ptr<Ship>> ships, int size, Field &field) {
    for (int i = 0; i < size; i++) {
        bool isPlaced = false;
        while (!isPlaced) {
            std::cout << "Введите координаты для корабля длины " << ships[i]->getLength() << ": ";
            auto coords = getCoordinates();
            std::cout << "Выберите расположение корабля:\n 0 - Vertical\n 1 - Horizontal" << std::endl;
            Orientation orientation = getOrientation();
            try {
                field.placeShip(coords, ships[i], orientation);
                field.setVisibility();
                field.printField();
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
            // Если ввод некорректный (не целое число или число вне диапазона)
            std::cout << "Ошибка! Пожалуйста, введите число от 0 до 1." << std::endl;
            std::cin.clear();  // Сбрасываем флаг ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Игнорируем остаток ввода
        } else {
            validInput = true;
        }
    }
    return static_cast<Orientation>(orientation);
}

