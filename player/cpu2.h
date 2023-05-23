#ifndef _CPU2_H_
#define _CPU2_H_

#include "player.h"
#include <tuple>
#include "../game/game.h"
#include <istream>
#include "../board/board.h"
#include "../board/piece.h"
#include <vector>

class Game;
struct pos;

/** CPU2 player subclass */
class CPU2 : public Player
{
Game* game;

public:
    CPU2(int colour, Game* game);

    ~CPU2() override; // dtor

    Game* getGame();
    
    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif