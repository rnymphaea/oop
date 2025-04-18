#ifndef LR4_GAMECONTROLLER_H
#define LR4_GAMECONTROLLER_H

#include "Game.h"
#include "InputHandler.h"
#include "Painter.h"
#include "TerminalPainter.h"
#include <memory>


template <typename InputHandlerType, typename Painter>
class GameController {
public:
    GameController()
            : game(std::make_shared<Game>()),
              inputHandler(std::make_shared<InputHandlerType>()),
              painter(std::make_shared<Painter>()) {};
    void init();
    ~GameController() = default;

    void round();
    void startGame();

private:
    void executeStartCommand(StartCommand cmd);
    RoundResult executeCommand(Command cmd);

    std::shared_ptr<Game> game;
    std::shared_ptr<InputHandlerType> inputHandler;
    std::shared_ptr<Painter> painter;
};

#endif // LR4_GAMECONTROLLER_H
