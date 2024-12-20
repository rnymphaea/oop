#include "../include/GameController.h"

int main() {
    GameController<InputHandler, Painter<TerminalPainter>> gameController;
    gameController.init();
    gameController.startGame();
    return 0;
}


