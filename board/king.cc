#include "king.h"
#include "board.h"
#include <vector>
#include <algorithm>

King::King(int colour, pos position, bool canCastle) : Piece{colour, position}, canCastle{canCastle}, type{'k'} {
    if (colour == 1)
    {
        type = 'K';
    }
}

King::King(const King &other) : Piece{other}, canCastle{other.canCastle}, type{other.type} {} // copy ctor

King *King::deepCopy() const
{ // deep copy method
    return (new King{*this});
}

bool King::castle(){
    return canCastle;
}

void King::setCanCastle(bool b) {
    this->canCastle = b;
}

char King::getType() const
{
    return type;
}

void King::updateValidMoves(Board* board, pos p) {
    this->position.x = p.x;
    this->position.y = p.y;
    validMoves.clear();

    // move right
    pos tmpPos = pos{this->position.x + 1, this->position.y};
    if (tmpPos.inBounds()) {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour) {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move left
    tmpPos = pos{this->position.x - 1, this->position.y};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move down
    tmpPos = pos{this->position.x, this->position.y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move up
    tmpPos = pos{this->position.x, this->position.y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move right down
    tmpPos = pos{this->position.x + 1, this->position.y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move right up
    tmpPos = pos{this->position.x + 1, this->position.y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move left down
    tmpPos = pos{this->position.x - 1, this->position.y + 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // move left up
    tmpPos = pos{this->position.x - 1, this->position.y - 1};
    if (tmpPos.inBounds())
    {
        if (board->getPiece(tmpPos) == nullptr || board->getPiece(tmpPos)->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
    }

    // castle left
    tmpPos = pos{this->position.x - 2, this->position.y};
    if (canCastle && tmpPos.inBounds()) {
        Piece* corner = board->getPiece(pos{0, this->position.y});
        if ((corner != nullptr) && (corner->castle()) && 
        (board->getPiece(pos{this->position.x - 1, this->position.y}) == nullptr) &&
        (board->getPiece(pos{this->position.x - 2, this->position.y}) == nullptr) &&
        (board->getPiece(pos{this->position.x - 3, this->position.y}) == nullptr)) {
            Board* snapshot = new Board(*board);
            if (!snapshot->isChecked(this->getColour())) {
                snapshot->getPiece(this->position)->setCanCastle(false); // prevents an infinite loop since updateBoard calls getValidMoves
                snapshot->updateBoard(this->position, {this->position.x-1, this->position.y}); //checking for in check on the in-between space. The end space is checked in play() after the move has been made
                if (!snapshot->isChecked(this->getColour())) {
                    validMoves.emplace_back(tmpPos);
                }
            }
            delete snapshot;
        }
    }

    // castle right
    tmpPos = pos{this->position.x + 2, this->position.y};
    if (canCastle && tmpPos.inBounds()) {
        Piece* corner = board->getPiece(pos{7, this->position.y});
        if ((corner != nullptr) && (corner->castle()) && 
        (board->getPiece(pos{this->position.x + 1, this->position.y}) == nullptr) &&
        (board->getPiece(pos{this->position.x + 2, this->position.y}) == nullptr)) {
            Board* snapshot = new Board(*board);
            if (!snapshot->isChecked(this->getColour())) {
                snapshot->getPiece(this->position)->setCanCastle(false); // prevents an infinite loop since updateBoard calls getValidMoves
                snapshot->updateBoard(this->position, {this->position.x+1, this->position.y}); //checking for in check on the in-between space. The end space is checked in play() after the move has been made
                if (!snapshot->isChecked(this->getColour())) {
                    validMoves.emplace_back(tmpPos);
                }
            }
            delete snapshot;
        }
    }
}

bool King::validate(pos p, Board* board) {
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end()) //normal case
    {
        canCastle = false;
        return true;
    }
    else
    {
        return false;
    }
}
