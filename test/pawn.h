#ifndef _PAWN_H_
#define _PAWN_H_
#include "piece.h"
#include <vector>
#include "pos.h"

class Pawn : public Piece {
    bool canMoveTwo;
    bool passantable = false;
    char type;

public:
    Pawn(int colour, pos position, bool canMoveTwo);  // Constructor

    Pawn(const Pawn& other);  // copy ctor
    
    bool validate(pos p, Board* board) override;

    void updateValidMoves(Board* board, pos p) override;  // Updates a list of all valid moves

    bool moveTwo();

    void setCanMoveTwo(bool b);

    bool isPassantable();

    void setPassantable(bool p);

    char getType() const override;

    Pawn *deepCopy() const override; // deep copy
};

#endif
