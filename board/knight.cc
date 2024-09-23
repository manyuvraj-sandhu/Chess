#include "knight.h"
#include "board.h"
#include <vector>
#include <algorithm>

using namespace std;

Knight::Knight(int colour, pos position) : Piece{colour, position}, type{'n'} {
    if (colour == 1)
    {
        type = 'N';
    }
}

Knight::Knight(const Knight &other) : Piece{other}, type{other.type} {} // copy ctor

Knight *Knight::deepCopy() const
{ // deep copy method
    return (new Knight{*this});
}

char Knight::getType() const {
    return type;
}

void Knight::updateValidMoves(Board* board, pos p) {
    this->position.x = p.x;
    this->position.y = p.y;
    validMoves.clear();

    pos tmpPos = pos{this->position.x + 2, this->position.y + 1};
    if (tmpPos.inBounds()) {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour) {
            validMoves.emplace_back(tmpPos);
        } else if (board->getPiece(tmpPos) == nullptr) {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x + 2, this->position.y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x + 1, this->position.y + 2};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x + 1, this->position.y - 2};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x - 2, this->position.y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x - 2, this->position.y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x - 1, this->position.y + 2};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
    tmpPos = pos{this->position.x - 1, this->position.y - 2};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) != nullptr && board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else if (board->getPiece(tmpPos) == nullptr)
        {
            validMoves.emplace_back(tmpPos);
        }
    }
}

bool Knight::validate(pos p, Board* board) {
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
