#include "../include/GameController.h"

// Реализация методов с двумя параметрами шаблона
template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::init() {
    inputHandler->init();
}

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::startGame() {
    std::cout << "============= Battleship =============" << std::endl;
    auto cmd = inputHandler->getStartCommand();
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
            std::cout << "Load" << std::endl;
            break;
        default:
            std::cout << "Unknown command!" << std::endl;
    }
}

template <typename InputHandlerType, typename PainterType>
void GameController<InputHandlerType, PainterType>::executeCommand(Command cmd) {
    switch (cmd) {
        case Save:
            std::cout << "Save" << std::endl;
            break;
        case Load:
            std::cout << "Load" << std::endl;
            break;
        case Attack:
            std::cout << "Attack" << std::endl;
            break;
        case ShowField:
            painter->showField(game->getPlayerField());
            break;
        case Exit:
            std::cout << "Exit" << std::endl;
            return;
        default:
            std::cout << "Unknown command!" << std::endl;
    }
}

// Явное инстанциирование шаблона для InputHandler и Painter
template class GameController<InputHandler, Painter>;
