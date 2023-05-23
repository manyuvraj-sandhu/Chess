#ifndef _CPU4_H_
#define _CPU4_H_

#include "player.h"
#include <tuple>
#include <istream>

class Game;
struct pos;

/** CPU4 player subclass */
class CPU4 : public Player
{
Game* game;

public:
    CPU4(int colour, Game* game);

    ~CPU4() override;

    Game* getGame();

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif
