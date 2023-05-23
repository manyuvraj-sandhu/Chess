#include "board.h"
#include "pos.h"
#include "piece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <ostream>
#include <cctype>

using namespace std;

Board::~Board() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete theBoard[i][j];
        }
        delete[] theBoard[i];
    }
    delete[] theBoard;
}  // dtor

Board::Board() {
    theBoard = new Piece**[8];
    for (int i = 0; i < 8; ++i) {
        theBoard[i] = new Piece*[8];
        for (int j = 0; j < 8; ++j) {
            theBoard[i][j] = nullptr;
        }
    }
}

Board::Board(const Board& other) { // copy ctor
    theBoard = new Piece**[8];
    for (int i = 0; i < 8; ++i) {
        theBoard[i] = new Piece*[8];
        for (int j = 0; j < 8; ++j) {
            theBoard[i][j] = (other.theBoard[i][j]) != nullptr ? other.theBoard[i][j]->deepCopy() : nullptr;
        }
    }
}

// Method that moves a piece from one location to another
void Board::updateBoard(pos a, pos b) {
    if (a.inBounds() && b.inBounds() && a != b) {
        Piece *curPiece = theBoard[a.y][a.x];
        this->setPiece(curPiece, b);
        theBoard[a.y][a.x] = nullptr;
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] != nullptr) {
                theBoard[i][j]->updateValidMoves(this, pos{j,i});
            }
        }
    }
}

// Count number of pieces of a certain type (case sensitive)
int Board::countPieces(char type) {
    int typeCount = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (this->getPiece(pos{i, j}) != nullptr) {
                if (this->getPiece(pos{i,j})->getType() == type) {
                    ++typeCount;
                } 
                    
            }
        }
    }
    return typeCount;
}

// A function that finds a certain piece in the board
pos Board::findPiece(char type) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((theBoard[i][j] != nullptr) && (theBoard[i][j]->getType() == type)) {
                return pos{j, i};
            }
        }
    }
    return pos{-1, -1};
}

// Sets the board to the start of a default game
void Board::setToStart() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0 || i == 7)
            {
                int curColour = 0;
                if (i == 7)
                {
                    curColour = 1;
                } // white
                if (j == 0 || j == 7)
                {
                    theBoard[i][j] = new Rook{curColour, pos{i, j}, true};
                }
                else if (j == 1 || j == 6)
                {
                    theBoard[i][j] = new Knight{curColour, pos{i, j}};
                }
                else if (j == 2 || j == 5)
                {
                    theBoard[i][j] = new Bishop{curColour, pos{i, j}};
                }
                else if (j == 3)
                {
                    theBoard[i][j] = new Queen{curColour, pos{i, j}};
                }
                else
                { // j == 4; king
                    theBoard[i][j] = new King{curColour, pos{i, j}, true};
                }
            }
            else if (i == 1 || i == 6)
            {
                int curColour = 0;
                if (i == 6)
                {
                    curColour = 1;
                } // white
                theBoard[i][j] = new Pawn{curColour, pos{i, j}, true};
            } else {
                theBoard[i][j] = nullptr;
            }
        }
    }
}

// Returns a piece from the board
Piece* Board::getPiece(pos a){
    if (theBoard[a.y][a.x] != nullptr) {
        return theBoard[a.y][a.x];
    } else {
        return nullptr;
    }
}

// Get all pieces of one player
vector<Piece*> Board::getPieces(int col){
    vector<Piece*> AvailablePieces = {};
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((theBoard[i][j] != nullptr) && (theBoard[i][j]->getColour() == col)) {
                AvailablePieces.emplace_back(theBoard[i][j]);
            }
        }
    }
    return AvailablePieces;
}

// method that sets piece piece at position on the board
void Board::setPiece(Piece* piece, pos position) {
    delete theBoard[position.y][position.x];
    theBoard[position.y][position.x] = piece;
    if (piece != nullptr) {
        piece->setPos(position);
    }
}

// determine whether a player is in check
bool Board::isChecked(int colour) { 
    pos kingPos = pos{-1,-1};
    if (colour == 1) { // white king
        kingPos = this->findPiece('K');
    } else { // black king
        kingPos = this->findPiece('k');
    }
    if (kingPos == pos{-1,-1}) { // this condition should never run, is an invariant
        return false;
    } else {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Piece* curPiece = this->getPiece(pos{i,j});
                if (curPiece != nullptr) {
                    if (curPiece->isValidMove(kingPos, this)) {  // check if any piece can move onto the king's position
                        return true;
                    }
                }
            }
        }
        return false;
    }
 }

// sets all of the current player's pawns to not be passantable
void Board::resetPassantable(int colour) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] != nullptr && theBoard[i][j]->getColour() == colour) {
                theBoard[i][j]->setPassantable(false);
            }
        }
    }
}

// determines if the board has no pieces on it
bool Board::isEmpty() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] != nullptr) {
                return false;
            }
        }
    }
    return true;
} 

// clears the board
void Board::clear() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (theBoard[i][j] != nullptr) {
                delete theBoard[i][j];
                theBoard[i][j] = nullptr;
            }
        }
    }
}

