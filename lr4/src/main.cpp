#include "../include/ShipSegment.h"
#include "../include/Ship.h"
#include "../include/Field.h"
#include "../include/ShipManager.h"
#include "../include/AbilityManager.h"
#include "../include/Game.h"
#include "../include/InputHandler.h"
#include "../include/Painter.h"
#include "../include/GameController.h"

int main() {
//    Game game;
//    game.NewRound();
//    InputHandler ih;
//    ih.init();
//    Game game;
    GameController<InputHandler, Painter> gameController;
    gameController.init();
    gameController.startGame();
//    ih.printMappings();
}


