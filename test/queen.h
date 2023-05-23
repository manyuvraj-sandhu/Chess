#ifndef _QUEEN_H_
#define _QUEEN_H_
#include "piece.h"

class Queen : public Piece{
    char type;
    
 public:
    Queen(int colour, pos position);  // Constructor

    Queen(const Queen& other); // copy ctor

    char getType() const override;

    bool validate(pos p, Board* board) override;

    void updateValidMoves(Board* board, pos p) override;

    Queen* deepCopy() const override;  // deep copy
};

#endif
