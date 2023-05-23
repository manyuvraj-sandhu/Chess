#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "player.h"
#include <tuple>
#include "../pos.h"
#include <istream>

/** Human player subclass */
class HumanPlayer : public Player {
public:
    HumanPlayer(int colour);

    ~HumanPlayer() override;

    std::tuple<pos, pos, char> determineMove(std::istream& in) override;
};

#endif