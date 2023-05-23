#include "view.h"
#include "game.h"

View::View(Game* game) : game{game} {}

void View::printBoard(pos a, pos b) {
    printOutput(a, b);
}

View::~View() {}
