#ifndef _VIEW_H_
#define _VIEW_H_

#include "pos.h"
class Game;

class View {
    virtual void printOutput(pos a, pos b) = 0;
protected:
    Game* game;

public:
    void printBoard(pos a, pos b);   // print

    View(Game* game); // ctor
    
    virtual ~View() = 0; // dtor
};

#endif
