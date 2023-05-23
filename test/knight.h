#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include "piece.h"

class Knight : public Piece{
    char type;

public:
    Knight(int colour, pos position);  // Constructor

    Knight(const Knight& other); // copy ctor
    
    bool validate(pos p, Board* board) override;

    void updateValidMoves(Board* board, pos p) override;

    char getType() const override;

    Knight *deepCopy() const override; // deep copy
};

#endif
