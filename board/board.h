#ifndef _BOARD_H_
#define _BOARD_H_
#include <ostream>
#include <vector>

struct pos;
class Piece;

/** board class representing the chess board */
class Board {
    Piece*** theBoard;

public:
    Board(); // ctor

    ~Board();  // dtor

    Board(const Board& other); // copy ctor

    void updateBoard(pos a, pos b);  // add a new move onto the board

    void setToStart();  // set game board to start

    Piece* getPiece(pos a);  // get specific piece

    std::vector<Piece*> getPieces(int colour);

    void setPiece(Piece* piece, pos position);

    int countPieces(char type);  // Function that counts how many occurrences of a certain type there are

    pos findPiece(char type);  // Function that finds a particular piece within the board

    bool isChecked(int colour); // determines if the player with that colour is in check

    void resetPassantable(int colour); // sets all pawns to not be passantable

    bool isEmpty(); // determines if the board has no pieces on it

    void clear(); // clears the board

};

#endif