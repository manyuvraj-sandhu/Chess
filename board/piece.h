#ifndef _PIECE_H_
#define _PIECE_H_
#include "../pos.h"
#include <iostream>
#include <vector>

class Board;

class Piece {

protected:
   virtual bool validate(pos, Board* board) = 0;
   int colour;
   pos position;
   std::vector<pos> validMoves;

public:
   Piece(int colour, pos position); // Constructor

   virtual char getType() const = 0;

   int getColour();

   bool isValidMove(pos p, Board* board);

   virtual void updateValidMoves(Board* board, pos p) = 0;  // Updates a list of all valid moves

   std::vector<pos> getValidMoves();  // returns all valid moves

   void setPos(pos p);

   pos getPos();

   virtual ~Piece() = 0;

   Piece(const Piece& other); // copy ctor

   virtual Piece *deepCopy() const = 0; // Allows us to deep copy a subtype of piece without knowing which one

   virtual bool castle(); //Needed so we can call castle() on Rooks and Kings stored in Piece pointers

   virtual void setCanCastle(bool b); //Needed so we can call set whether a king or rook can castle

   virtual bool isPassantable(); //Needed so we can call isPassantable() on Pawns stored in Piece pointers

   virtual void setPassantable(bool p);
   // These ^ v are needed so we can set those variables in Pawn from Piece pointers (I know casting exists but we just learned it and it seems more complicated)
   virtual void setCanMoveTwo(bool b);
};

#endif

