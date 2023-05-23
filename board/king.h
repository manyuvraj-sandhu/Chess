#ifndef _KING_H_
#define _KING_H_
#include "piece.h"

class King : public Piece{
    bool canCastle;
    char type;

public:
    King(int colour, pos position, bool canCastle);  // Constructor

    King(const King& other); // copy ctor

    bool validate(pos p, Board* board) override;

    void updateValidMoves(Board* board, pos p) override;

    bool castle();

    void setCanCastle(bool b);

    char getType() const override;

    King *deepCopy() const override;  // deep copy
};

#endif
