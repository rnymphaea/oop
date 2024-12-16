#ifndef LR4_GAMECONTROLLER_H
#define LR4_GAMECONTROLLER_H

#include "Game.h"
#include "InputHandler.h"
#include "Painter.h"
#include <memory>

template <typename InputHandlerType, typename PainterType>
class GameController {
public:
    GameController()
            : game(std::make_shared<Game>()),
              inputHandler(std::make_shared<InputHandlerType>()),
              painter(std::make_shared<PainterType>()) {};
    void init();
    ~GameController() = default;

    void round();
    void startGame();

private:
    void executeStartCommand(StartCommand cmd);
    void executeCommand(Command cmd);

    std::shared_ptr<Game> game;                      // Разделяемый указатель на объект Game
    std::shared_ptr<InputHandlerType> inputHandler;  // Разделяемый указатель на InputHandlerType
    std::shared_ptr<PainterType> painter;           // Разделяемый указатель на PainterType
};

#endif // LR4_GAMECONTROLLER_H
