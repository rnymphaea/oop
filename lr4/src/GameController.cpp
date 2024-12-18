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
        auto res = executeCommand(cmd);
        switch (res) {
            case PlayerWon:
                std::cout << "player won!" << std::endl;
                game->newRound();
                break;
            case ComputerWon: {
                std::cout << "computer won!" << std::endl;
                int n = inputHandler->getNumberShips();
                auto lengths = inputHandler->getLengths(n);
                game->newGame(lengths);
                break;
            }
            case GameActive:
                continue;
            case Quit:
                end = true;
                break;
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
RoundResult GameController<InputHandlerType, PainterType>::executeCommand(Command cmd) {
    RoundResult res;
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
            res = game->attack(coords);
            if (res != GameActive) {
                return res;
            }
            res = game->attack(coords);
            if (res != GameActive) {
                return res;
            }
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
                game->ability(abilitySettings);
                Coordinates coords = inputHandler->getCoordinates();

                res = game->attack(coords, *abilitySettings.damage); // player turn
                if (res != GameActive) {
                    return res;
                }
                res = game->attack(coords); // computer turn
                if (res != GameActive) {
                    return res;
                }
                *abilitySettings.damage = 1;

                painter->showField(game->getCompField(), false);
            }
            catch (NoAbilitiesError& err) {
                std::cout << err.what() << std::endl;
            }
            break;
        }
        case Exit:
            std::cout << "Exit" << std::endl;
            res = Quit;
            return res;
        default:
            std::cout << "Unknown command!" << std::endl;
    }
}

// Явное инстанциирование шаблона для InputHandler и Painter
template class GameController<InputHandler, Painter>;
