#include "queen.h"
#include "board.h"
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

Queen::Queen(int colour, pos position) : Piece{colour, position}, type{'q'} {
    if (colour == 1) { type = 'Q'; }
}

char Queen::getType() const {
    return type;
}

Queen::Queen(const Queen& other) : Piece{other}, type{other.type} {} // copy ctor

Queen* Queen::deepCopy() const { // deep copy method
    return (new Queen{*this});
}

void Queen::updateValidMoves(Board* board, pos p) {
    this->position.x = p.x;
    this->position.y = p.y;
    validMoves.clear();

    bool up = true, down = true, left = true, right = true;
    bool upRight = true, upLeft = true, downRight = true, downLeft = true;
    int i = 1;
    while (up || down || left || right || upRight || upLeft || downRight || downLeft) {
        if (up) {
            pos tmpPos = pos{this->position.x, this->position.y + i};
            if (!tmpPos.inBounds()) {  // position out of bounds
                up = false;
            } else {
                Piece *tmpPiece = board->getPiece(tmpPos);
                if (tmpPiece != nullptr) {
                    if (tmpPiece->getColour() != this->colour) {  // killing move
                        validMoves.emplace_back(tmpPos);
                    } 
                    up = false;
                } else {
                    validMoves.emplace_back(tmpPos);
                } 
            }            
        }
        if (down) {
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
        if (left) {
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
        if (right) {
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
        if (upRight) {
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
        if (upLeft) {
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
        if (downRight) {
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
        if (downLeft) {
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

bool Queen::validate(pos p, Board* board){
    if (find(validMoves.begin(), validMoves.end(), p) != validMoves.end())
    {
        return true;
    }
    else
    {
        return false;
    }

    // // Check for valid move type for a queen:
    // // Check for diagonal move
    // int xDist = position.x - p.x;
    // int yDist = position.y - p.y;
    // if (abs(xDist) != abs(yDist)) { // not diagonal
    //     // Check for a horizontal move
    //     if (position.y == p.y) {
    //         int xStart = position.x;
    //         int xEnd = p.x;
    //         if (xDist > 0) {
    //             xStart = p.x;
    //             xEnd = position.x;
    //         }
    //         for (int i = xStart + 1; i < xEnd; ++i) {
    //             if (board->getPiece(pos{i, p.y}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //         return true;  // vertical with no blocking

    //     } else if (position.x == p.x) { // horizontal move
    //         int yStart = position.y;
    //         int yEnd = p.y;
    //         if (yDist > 0)
    //         {
    //             yStart = p.y;
    //             yEnd = position.y;
    //         }
    //         for (int i = yStart + 1; i < yEnd; ++i)
    //         {
    //             if (board->getPiece(pos{p.x, i}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //         return true;  // horizontal with no blocking

    //     } else {
    //         return false;  // not diagonal, horizontal, or vertical
    //     }

        
    // } else { // Diagonal, check if there is anything blocking the diagonal
    //     // right upwards diagonal
    //     if (xDist < 0 && yDist > 0) {
    //         for (int i = 1; i < abs(xDist); ++i) {
    //             if (board->getPiece(pos{position.x + i, position.y - i}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //     } else if (xDist < 0 && yDist < 0) {  // right downwards diagonal
    //         for (int i = 1; i < abs(xDist); ++i)
    //         {
    //             if (board->getPiece(pos{position.x + i, position.y + i}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //     } else if (xDist > 0 && yDist > 0) { // left upwards diagonal
    //         for (int i = 1; i < abs(xDist); ++i)
    //         {
    //             if (board->getPiece(pos{position.x - i, position.y - i}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //     } else { // left downwards diagonal
    //         for (int i = 1; i < abs(xDist); ++i)
    //         {
    //             if (board->getPiece(pos{position.x - i, position.y + i}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //     }
    //     if (xDist * yDist < 0) {
    //         int xStart = position.x;
    //         int yStart = position.y;
    //         if (xStart > p.x) {  // We want to start our checking at the smaller x value 
    //             xStart = p.x;
    //             yStart = p.y;
    //         }
    //         for (int i = 1; i < abs(xDist); ++i) {
    //             if (board->getPiece(pos{xStart + i, yStart - i}) != nullptr) {
    //                 return false;
    //             }
    //         }
    //         return true;  // nothing blocking a right diagonal play
    //     }
    //     //left diagonal
    //     else {
    //         int xStart = position.x;
    //         int yStart = position.y;
    //         if (xStart > p.x) {
    //             xStart = p.x;
    //             yStart = p.y;
    //         }
    //         for (int i = 1; i < xDist; ++i) {
    //             if (board->getPiece(pos{xStart + i, yStart + i}) != nullptr)
    //             {
    //                 return false;
    //             }
    //         }
    //         return true; // nothing blocking a left diagonal play
    //     }
    // }

    return true;
}