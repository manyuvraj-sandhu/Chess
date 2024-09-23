#include "rook.h"
#include "board.h"
#include <vector>
#include <algorithm>

Rook::Rook(int colour, pos position, bool canCastle) : Piece{colour, position}, canCastle{canCastle}, type{'r'} {
    if (colour == 1)
    {
        type = 'R';
    }
}

Rook::Rook(const Rook &other) : Piece{other}, canCastle{other.canCastle}, type{other.type} {} // copy ctor

Rook *Rook::deepCopy() const
{ // deep copy method
    return (new Rook{*this});
}

void Rook::updateValidMoves(Board* board, pos p) { 
    this->position.x = p.x;
    this->position.y = p.y;
    validMoves.clear();

    bool up = true, down = true, right = true, left = true;
    int i = 1;
    while (up || down || right || left) {
        if (up)
        {
            pos tmpPos = pos{this->position.x, this->position.y + i};
            if (!tmpPos.inBounds())
            { // position out of bounds
                up = false;
            }
            else
            {
                Piece *tmpPiece = board->getPiece(tmpPos);
                if (tmpPiece != nullptr)
                {
                    if (tmpPiece->getColour() != this->colour)
                    { // killing move
                        validMoves.emplace_back(tmpPos);
                    }
                    up = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        if (down)
        {
            pos tmpPos = pos{this->position.x, this->position.y - i};
            if (!tmpPos.inBounds())
            { // position out of bounds
                down = false;
            }
            else
            {
                Piece *tmpPiece = board->getPiece(tmpPos);
                if (tmpPiece != nullptr)
                {
                    if (tmpPiece->getColour() != this->colour)
                    { // killing move
                        validMoves.emplace_back(tmpPos);
                    }
                    down = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        if (left)
        {
            pos tmpPos = pos{this->position.x - i, this->position.y};
            if (!tmpPos.inBounds())
            { // position out of bounds
                left = false;
            }
            else
            {
                Piece *tmpPiece = board->getPiece(tmpPos);
                if (tmpPiece != nullptr)
                {
                    if (tmpPiece->getColour() != this->colour)
                    { // killing move
                        validMoves.emplace_back(tmpPos);
                    }
                    left = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        if (right)
        {
            pos tmpPos = pos{this->position.x + i, this->position.y};
            if (!tmpPos.inBounds())
            { // position out of bounds
                right = false;
            }
            else
            {
                Piece *tmpPiece = board->getPiece(tmpPos);
                if (tmpPiece != nullptr)
                {
                    if (tmpPiece->getColour() != this->colour)
                    { // killing move
                        validMoves.emplace_back(tmpPos);
                    }
                    right = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        ++i;
    }
}
    

bool Rook::validate(pos p, Board* board){
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end())
    {
        canCastle = false;
        return true;
    }
    else
    {
        return false;
    }
}

bool Rook::castle() {
    return canCastle;
}

void Rook::setCanCastle(bool b) {
    this->canCastle = b;
}

char Rook::getType() const {
    return type;
}