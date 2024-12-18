#include "../include/GameController.h"

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::init() {
    inputHandler->init();
}

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::startGame() {
    std::cout << "============= Battleship =============" << std::endl;
    StartCommand cmd = inputHandler->getStartCommand();
    executeStartCommand(cmd);
}

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::round() {
    bool end = false;
    while (!end) {
        Command cmd = inputHandler->getCommand();
        if (cmd == Exit) {
            end = true;
        }
        else {
            executeCommand(cmd);
        }
    }
}

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::executeStartCommand(StartCommand cmd) {
    switch (cmd) {
        case StartCommand::NewGame : {
            int n = inputHandler->getNumberShips();
            auto lengths = inputHandler->getLengths(n);
            game->newGame(lengths);
            round();
            break;
        }
        case StartCommand::LoadGame:
            try {
                game->load();
                painter->showField(game->getPlayerField(), true);
                painter->showField(game->getCompField(), false);
                round();
            }
            catch (std::exception& err) {
                std::cout << "Cannot load from file: " << err.what() << std::endl;
            }
            break;
        default:
            std::cout << "Unknown command!" << std::endl;
    }
}

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::executeCommand(Command cmd) {
    switch (cmd) {
        case Save:
            game->save();
            break;
        case Load:
            std::cout << "Load" << std::endl;
            try {
                game->load();
                painter->showField(game->getPlayerField(), true);
                painter->showField(game->getCompField(), false);
            }
            catch (std::exception& err) {
                std::cout << "Cannot load from file: " << err.what() << std::endl;
            }
            break;
        case Attack: {
            Coordinates coords = inputHandler->getCoordinates();
            game->attack(coords);
            game->attack(coords);
            painter->showField(game->getCompField(), false);
            break;
        }
        case ShowField:
            painter->showField(game->getPlayerField(), true);
            break;
        case Ability: {
            int damage = 1;
            AbilitySettings abilitySettings{game->getCompField(), &damage};
            try {
                std::cout << *abilitySettings.damage << std::endl;
                game->ability(abilitySettings);
                Coordinates coords = inputHandler->getCoordinates();

                game->attack(coords, *abilitySettings.damage); // player turn
                game->attack(coords); // computer turn

                *abilitySettings.damage = 1;

                painter->showField(game->getCompField(), false);
            }
            catch (std::exception & err) {
                std::cout << err.what() << std::endl;
            }
            break;
        }
        case Exit:
            std::cout << "Exit" << std::endl;
            return;
        default:
            std::cout << "Unknown command!" << std::endl;
    }
}

// Явное инстанциирование шаблона для InputHandler и Painter
template class GameController<InputHandler, Painter>;
