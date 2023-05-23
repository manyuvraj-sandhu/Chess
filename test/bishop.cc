#include "bishop.h"
#include "board.h"
#include <vector>
#include <algorithm>

Bishop::Bishop(int colour, pos position) : Piece{colour, position}, type{'b'} {
    if (colour == 1)
    {
        type = 'B';
    }
}

Bishop::Bishop(const Bishop &other) : Piece{other}, type{other.type} {} // copy ctor

Bishop *Bishop::deepCopy() const
{ // deep copy method
    return (new Bishop{*this});
}

char Bishop::getType() const {
    return type;
}

void Bishop::updateValidMoves(Board* board, pos p) {
    this->position.x = p.x;
    this->position.y = p.y;
    validMoves.clear();

    bool upRight = true, upLeft = true, downRight = true, downLeft = true;
    int i = 1;
    while (upRight || upLeft || downRight || downLeft) {
        if (upRight)
        {
            pos tmpPos = pos{this->position.x + i, this->position.y + i};
            if (!tmpPos.inBounds())
            { // position out of bounds
                upRight = false;
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
                    upRight = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        if (upLeft)
        {
            pos tmpPos = pos{this->position.x - i, this->position.y + i};
            if (!tmpPos.inBounds())
            { // position out of bounds
                upLeft = false;
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
                    upLeft = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        if (downRight)
        {
            pos tmpPos = pos{this->position.x + i, this->position.y - i};
            if (!tmpPos.inBounds())
            { // position out of bounds
                downRight = false;
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
                    downRight = false;
                }
                else
                {
                    validMoves.emplace_back(tmpPos);
                }
            }
        }
        if (downLeft)
        {
            pos tmpPos = pos{this->position.x - i, this->position.y - i};
            if (!tmpPos.inBounds())
            { // position out of bounds
                downLeft = false;
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
                    downLeft = false;
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

bool Bishop::validate(pos p, Board* board) {
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
