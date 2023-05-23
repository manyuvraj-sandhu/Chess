#include "playerFactory.h"
#include "string"
#include "humanPlayer.h"
#include "cpu1.h"
#include "cpu2.h"
#include "cpu3.h"
#include "cpu4.h"
#include "game.h"

using namespace std;

/** method that creates a new player based on what the user calls */
Player* PlayerFactory::createPlayer(string& player, int colour, Game* game) {
    if (player == "human") {
        return new HumanPlayer{colour};
    } else if (player == "computer1") {
        return new CPU1{colour, game};
    } else if (player == "computer2") {
        return new CPU2{colour, game};
    } else if (player == "computer3") {
        return new CPU3{colour, game};
    } else { // player == "computer4"
        return new CPU4{colour, game};
    }
}
