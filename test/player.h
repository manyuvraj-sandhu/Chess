#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <tuple>
#include <istream>

struct pos;

/** Player class representing an abstract player */
class Player {
    int colour;
    bool checked;

protected:
    //idk why determineMove was protected, I need to use it in Game

public:
    virtual std::tuple<pos, pos, char> determineMove(std::istream& in) = 0;

    virtual ~Player(); // dtor
    
    Player(int colour); // ctor

    bool isChecked();
    
    void setChecked(bool checked);
    
    int getColour();
};

#endif
