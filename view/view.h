#ifndef _VIEW_H_
#define _VIEW_H_

#include "../pos.h"
class Board;

class View {
    virtual void printOutput(pos a, pos b) = 0;
protected:
    Board* board;

public:
    void printBoard(pos a, pos b);   // print

    View(Board* board); // ctor
    
    virtual ~View() = 0; // dtor
};

#endif