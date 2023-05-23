#ifndef _BISHOP_H_
#define _BISHOP_H_
#include "piece.h"

class Bishop : public Piece {
    char type;

public:
    Bishop(int colour, pos position);  // Constructor

    Bishop(const Bishop& other); // copy ctor
    
    bool validate(pos p, Board* board) override;

    void updateValidMoves(Board* board, pos p) override;  // update all valid moves

    char getType() const override;

    Bishop *deepCopy() const override; // deep copy
};

#endif
