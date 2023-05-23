#include "view.h"

View::View(Board* board) : board{board} {}

void View::printBoard(pos a, pos b) {
    printOutput(a, b);
}

View::~View() {};