#include "pawn.h"
#include "board.h"
#include <algorithm>

using namespace std;

Pawn::Pawn(int colour, pos position, bool canMoveTwo) : Piece{colour, position}, canMoveTwo{canMoveTwo}, type{'p'} {
    if (colour == 1)
    {
        type = 'P';
    }
}

Pawn::Pawn(const Pawn &other) : Piece{other}, canMoveTwo{other.canMoveTwo}, type{other.type} {} // copy ctor

Pawn *Pawn::deepCopy() const
{ // deep copy method
    return (new Pawn{*this});
}

void Pawn::updateValidMoves(Board* board, pos p) {
    this->position.x = p.x;
    this->position.y = p.y;
    validMoves.clear();  // Remove all old valid moves
    int dir = -1;
    if (this->colour == 0) { // black pawn, can only move down
        dir = 1;
    }
    pos tmpPos = pos{this->position.x, this->position.y + (dir * 1)};
    if (tmpPos.inBounds() && board->getPiece(tmpPos) == nullptr)
    { // good
        validMoves.emplace_back(tmpPos);
        if (canMoveTwo)
        {
            tmpPos = pos{this->position.x, this->position.y + (dir * 2)};
            if (tmpPos.inBounds() && board->getPiece(tmpPos) == nullptr)
            { // nothing in the way
                validMoves.emplace_back(tmpPos);
            }
        }
    }

    // check first attack
    tmpPos = pos{this->position.x - 1, this->position.y + (dir * 1)};
    if (tmpPos.inBounds()) {
        Piece* tmpPiece = board->getPiece(tmpPos);
        if (tmpPiece != nullptr && tmpPiece->getColour() != colour) 
        {
            validMoves.emplace_back(tmpPos);
        }
        else {
            tmpPiece = board->getPiece(pos{this->position.x - 1, this->position.y});
            if (tmpPiece != nullptr && tmpPiece->getColour() != colour && tmpPiece->isPassantable()) {
                validMoves.emplace_back(tmpPos);
            }
        }
    }

    // check second attack
    tmpPos = pos{this->position.x + 1, this->position.y + (dir * 1)};
    if (tmpPos.inBounds())
    {
        Piece *tmpPiece = board->getPiece(tmpPos);
        if (tmpPiece != nullptr && tmpPiece->getColour() != colour)
        {
            validMoves.emplace_back(tmpPos);
        }
        else {
            tmpPiece = board->getPiece(pos{this->position.x + 1, this->position.y});
            if (tmpPiece != nullptr && tmpPiece->getColour() != colour && tmpPiece->isPassantable()) {
                validMoves.emplace_back(tmpPos);
            }
        }
    }
}

bool Pawn::validate(pos p, Board* board){
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end()) {
        return true;
    } else {
        return false;
    }
    // int xDist = position.x - p.x;
    // int yDist = position.y - p.y;
    // if (this->colour == 0) { // black, should only move down on the board
    //     if (xDist == 0) {  // forward down
    //         if (yDist == -1) {
    //             if (board->getPiece(pos{p.x, p.y}) != nullptr) { // moving forward on a non-kill, but being blocked
    //                 return false;
    //             } else {
    //                 return true; // free space one step ahead
    //             }
    //         } else if (yDist == -2) { // moveTwo attempt
    //             if ((board->getPiece(pos{p.x, p.y - 1}) == nullptr) && (board->getPiece(pos{p.x, p.y}) == nullptr)) {
    //                 if (canMoveTwo) {  // one-time moveTwo
    //                     canMoveTwo = false;
    //                     return true;
    //                 }
    //                 else {
    //                     return false;
    //                 } // Not blocked, depends on whether can moveTwo or not
    //             } else {
    //                 return false; // blocked
    //             }
    //         } else {
    //             return false; // Attempt to move more than 2 space forward
    //         }
    //     } else { // diagonal killing move
    //         if (abs(xDist) == 1 && yDist == -1) {
    //             if (board->getPiece(pos{p.x, p.y}) == nullptr) {
    //                 return false; // no piece to kill
    //             } else {
    //                 return true;
    //             }
    //         }
    //     }
    // } else { // white, should only move up on the board
    //     if (xDist == 0) {  // forward up
    //         if (yDist == 1) {
    //             if (board->getPiece(pos{p.x,p.y}) != nullptr) {  // moving forward on a non-kill but being blocked
    //                 return false;
    //             } else {
    //                 return true;  // valid move one step up
    //             }
    //         } else if (yDist == 2) { // moveTwo attempt
    //             if ((board->getPiece(pos{p.x, p.y + 1}) == nullptr) && (board->getPiece(pos{p.x, p.y}) == nullptr)) {
    //                 if (canMoveTwo) { // one-time moveTwo
    //                     canMoveTwo = false;
    //                     return true;
    //                 } else {
    //                     return false;
    //                 }
    //             }
    //         } else { // attempt to move more than 2 spaces
    //             return false;
    //         }
    //     } else { // diagonal killing move
    //         if (abs(xDist) == 1 && yDist == 1) {
    //             if (board->getPiece(pos{p.x, p.y}) == nullptr) {
    //                 return false;  // no piece to kill
    //             } else {
    //                 return true; // valid killing move
    //             }
    //         } 
    //     }
    // }
    // return false;
}

bool Pawn::moveTwo() {
    return canMoveTwo;
}

void Pawn::setCanMoveTwo(bool b) {
    canMoveTwo = b;
}

bool Pawn::isPassantable() {
    return passantable;
}

void Pawn::setPassantable(bool p) {
    this->passantable = p;
}

char Pawn::getType() const {
    return type;
}
