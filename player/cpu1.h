#ifndef _CPU1_H_
#define _CPU1_H_

#include "player.h"
#include <tuple>
#include <istream>
#include "../game/game.h"
#include "../board/board.h"
#include "../board/piece.h"

struct pos;

/** CPU1 player subclass */
class CPU1 : public Player
{
Game* theGame;

public:
    CPU1(int colour, Game* theGame); // ctor

    ~CPU1() override; // dtor

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;

    Game* getGame();
};

#endif