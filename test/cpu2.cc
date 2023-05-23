#include "cpu2.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "board.h"
#include "pos.h"
#include <time.h>
#include <string>

using namespace std;

CPU2::CPU2(int colour, Game* game) : Player{colour}, game{game} {}

CPU2::~CPU2() {}

Game* CPU2::getGame(){
    return game;
}

tuple<pos, pos, char> CPU2::determineMove(istream& in)
{
    string s;
    while (cin >> s) 
    {
        if (s == "move") 
        {
            srand(time(NULL));
            Board *theBoard = getGame()->getBoard();

            vector<Piece *> teamPieces = theBoard->getPieces(this->getColour());
            vector<Piece *> availablePieces;
            for (unsigned long i = 0; i < teamPieces.size(); ++i)
            {
                if (!((teamPieces[i]->getValidMoves()).empty()))
                {
                    availablePieces.emplace_back(teamPieces[i]);
                }
            }

            vector<tuple<pos, pos>> preferredMoves;
            vector<tuple<pos, pos>> safeMoves;

            for (unsigned long i = 0; i < availablePieces.size(); ++i)
            {
                Piece *selectedPiece = availablePieces[i];
                vector<pos> curValidMoves = selectedPiece->getValidMoves();
                for (unsigned long j = 0; j < curValidMoves.size(); ++j)
                {
                    if (theBoard->getPiece(curValidMoves[j]) != nullptr)
                    { // capturing move
                        tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
                        Board *snapshot = new Board(*theBoard);
                        snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
                        if (!snapshot->isChecked(this->getColour()))
                        {
                            preferredMoves.emplace_back(move);
                        }
                        delete snapshot;
                    }
                    else
                    {
                        // look for checkng move
                        Board *snapshot = new Board(*theBoard);
                        snapshot->updateBoard(selectedPiece->getPos(), curValidMoves[j]);
                        if (snapshot->isChecked(this->getColour()))
                        {
                            delete snapshot;
                            continue; // go next if this move puts us in check
                        }
                        pos opKingPos = {-1, -1};
                        if (this->getColour() == 1)
                        { // opponent has black king
                            opKingPos = snapshot->findPiece('k');
                        }
                        else
                        { // opponent has white king
                            opKingPos = snapshot->findPiece('K');
                        }
                        tuple<pos, pos> move = {selectedPiece->getPos(), curValidMoves[j]};
                        if (selectedPiece->isValidMove(opKingPos, snapshot))
                        { // checking move
                            preferredMoves.emplace_back(move);
                        }
                        else
                        {
                            safeMoves.emplace_back(move); // non-checking or capturing move but doesn't put us in check
                        }
                        delete snapshot;
                    }
                }
            }

            pos start = {-1, -1};
            pos end = {-1, -1};
            if (!(preferredMoves.empty()))
            { // if any capturing or checking moves exist, pick a random one
                tuple<pos, pos> selectedMove = preferredMoves[rand() % preferredMoves.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            else
            { // otherwise, pick any move
                tuple<pos, pos> selectedMove = safeMoves[rand() % safeMoves.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            // the fact that we aren't in checkmate means there must be at least one available move, so we don't need
            // to worry about the case where both preferredMoves and safeMoves are empty. If preferredMoves is empty,
            // then safeMoves must not be

            // pawn promotion
            char newPieceType = ' ';
            if ((theBoard->getPiece(start)->getType() == 'P' && end.y == 0) || (theBoard->getPiece(start)->getType() == 'p' && end.y == 7))
            {
                int pieceChoice = rand() % 4;
                switch (pieceChoice)
                {
                case 0: // Queen
                    newPieceType = 'Q';
                    break;
                case 1: // Rook
                    newPieceType = 'R';
                    break;
                case 2: // Bishop
                    newPieceType = 'B';
                    break;
                default: // Knight
                    newPieceType = 'N';
                }
                if (this->getColour() == 0)
                {
                    newPieceType += 32; // converts to lowercase if black
                }
            }

            tuple<pos, pos, char> move = {start, end, newPieceType};
            cout << "moving " << theBoard->getPiece(start)->getType() << " from " << convertBack(start) << " to " << convertBack(end) << endl;
            return move;
        }
        else
        {
            cout << "invalid input." << endl;
        }
    }
    return {{-1, -1}, {-1, -1}, ' '};
}
