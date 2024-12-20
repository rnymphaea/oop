#include "../include/ShipSegment.h"
#include "../include/Ship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"
#include "../include/AbilityManager.h"
#include "../include/Game.h"
#include "../include/InputHandler.h"
#include "../include/Painter.h"
#include "../include/GameController.h"
#include "../include/TerminalPainter.h"

int main() {
    GameController<InputHandler, Painter<TerminalPainter>> gameController;
    gameController.init();
    gameController.startGame();
    return 0;
}


