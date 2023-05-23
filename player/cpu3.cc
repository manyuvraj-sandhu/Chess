#include "cpu3.h"
#include "../game/game.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include "../pos.h"
#include <time.h>
#include "../board/board.h"
#include "../board/piece.h"
#include <tuple>
#include <string>

using namespace std;

CPU3::CPU3(int colour, Game* game) : Player{colour}, game{game} {}

CPU3::~CPU3() {}

Game *CPU3::getGame()
{
    return game;
}

tuple<pos, pos, char> CPU3::determineMove(istream &in)
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

            // filter out moves that put us in check
            vector<tuple<pos, pos>> safeMoves;

            for (unsigned long i = 0; i < availablePieces.size(); ++i)
            {
                Piece *curPiece = availablePieces[i];
                pos myPos = curPiece->getPos();
                vector<pos> myMoves = curPiece->getValidMoves();
                for (auto movePos : myMoves)
                {
                    Board *snapshot = new Board{*theBoard};
                    snapshot->updateBoard(myPos, movePos);
                    if (!(snapshot->isChecked(this->getColour())))
                    { // this move doesn't put us in check add it to safe moves
                        tuple<pos, pos> safeMove{myPos, movePos};
                        safeMoves.emplace_back(safeMove);
                    }
                    delete snapshot;
                }
            }

            // split the safe moves into two groups: one that avoids capture and one that doesn't
            vector<tuple<pos, pos>> cap;
            vector<tuple<pos, pos>> noCap;

            for (auto move : safeMoves)
            {
                if (theBoard->getPiece(get<1>(move)) != nullptr)
                { // capturing
                    cap.emplace_back(move);
                }
                else
                {
                    Board *snapshot = new Board{*theBoard};
                    snapshot->updateBoard(get<0>(move), get<1>(move));
                    if (snapshot->isChecked((this->getColour() + 1) % 2))
                    { // puts other player in check
                        cap.emplace_back(move);
                    }
                    else
                    {
                        noCap.emplace_back(move);
                    }
                    delete snapshot;
                }
            }

            /**
             * TIER 1: Moves that remove a piece from danger and capture or check
             * TIER 2: Moves that don't put a piece in danger and capture or check
             * TIER 3: Moves that capture or check
             * TIER 4: Moves that remove a piece from danger
             * TIER 5: Moves that don't put a piece in danger
             * TIER 6: Random moves
             */

            vector<tuple<pos, pos>> tier1;
            vector<tuple<pos, pos>> tier2;
            vector<tuple<pos, pos>> tier3;
            vector<tuple<pos, pos>> tier4;
            vector<tuple<pos, pos>> tier5;
            vector<tuple<pos, pos>> tier6;

            for (auto move : cap)
            {
                bool getsCapped = false;
                bool inDanger = false;
                Board *snapshot = new Board{*theBoard};
                pos start = get<0>(move);
                pos end = get<1>(move);

                // get opponent's pieces
                vector<Piece *> oppPieces = snapshot->getPieces((this->getColour() + 1) % 2);
                vector<Piece *> oppAvailablePieces;
                for (unsigned long i = 0; i < oppPieces.size(); ++i)
                {
                    if (!((oppPieces[i]->getValidMoves()).empty()))
                    {
                        oppAvailablePieces.emplace_back(oppPieces[i]);
                    }
                }

                for (auto oppPiece : oppAvailablePieces)
                {
                    for (auto oppMove : oppPiece->getValidMoves())
                    {
                        if (oppMove == end)
                        { // opponent has a move that captures the piece before they've moved
                            inDanger = true;
                        }
                    }
                }

                snapshot->updateBoard(start, end);
                oppPieces = snapshot->getPieces((this->getColour() + 1) % 2);
                oppAvailablePieces.clear();
                for (unsigned long i = 0; i < oppPieces.size(); ++i)
                {
                    if (!((oppPieces[i]->getValidMoves()).empty()))
                    {
                        oppAvailablePieces.emplace_back(oppPieces[i]);
                    }
                }

                for (auto oppPiece : oppAvailablePieces)
                {
                    for (auto oppMove : oppPiece->getValidMoves())
                    {
                        if (oppMove == end)
                        { // opponent has a move that captures the piece after they've moved
                            getsCapped = true;
                        }
                    }
                }

                if (inDanger && !getsCapped)
                {
                    tier1.emplace_back(move);
                }
                else if (!getsCapped)
                {
                    tier2.emplace_back(move);
                }
                else
                {
                    tier3.emplace_back(move);
                }

                delete snapshot;
            }

            for (auto move : noCap)
            {
                bool getsCapped = false;
                bool inDanger = false;
                Board *snapshot = new Board{*theBoard};
                pos start = get<0>(move);
                pos end = get<1>(move);

                // get opponent's pieces
                vector<Piece *> oppPieces = snapshot->getPieces((this->getColour() + 1) % 2);
                vector<Piece *> oppAvailablePieces;
                for (unsigned long i = 0; i < oppPieces.size(); ++i)
                {
                    if (!((oppPieces[i]->getValidMoves()).empty()))
                    {
                        oppAvailablePieces.emplace_back(oppPieces[i]);
                    }
                }

                for (auto oppPiece : oppAvailablePieces)
                {
                    for (auto oppMove : oppPiece->getValidMoves())
                    {
                        if (oppMove == end)
                        { // opponent has a move that captures the piece before they've moved
                            inDanger = true;
                        }
                    }
                }

                snapshot->updateBoard(start, end);

                oppAvailablePieces.clear();
                for (unsigned long i = 0; i < oppPieces.size(); ++i)
                {
                    if (!((oppPieces[i]->getValidMoves()).empty()))
                    {
                        oppAvailablePieces.emplace_back(oppPieces[i]);
                    }
                }

                for (auto oppPiece : oppAvailablePieces)
                {
                    for (auto oppMove : oppPiece->getValidMoves())
                    {
                        if (oppMove == end)
                        { // opponent has a move that captures the piece after they've moved
                            getsCapped = true;
                        }
                    }
                }

                if (inDanger && !getsCapped)
                {
                    tier4.emplace_back(move);
                }
                else if (!getsCapped)
                {
                    tier5.emplace_back(move);
                }
                else
                {
                    tier6.emplace_back(move);
                }

                delete snapshot;
            }

            pos start = {-1, -1};
            pos end = {-1, -1};

            if (!(tier1.empty()))
            { // if a tier1 move exists
                tuple<pos, pos> selectedMove = tier1[rand() % tier1.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            else if (!(tier2.empty()))
            { // if a tier2 move exists
                tuple<pos, pos> selectedMove = tier2[rand() % tier2.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            else if (!(tier3.empty()))
            { // if a tier3 move exists
                tuple<pos, pos> selectedMove = tier3[rand() % tier3.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            else if (!(tier4.empty()))
            { // if a tier4 move exists
                tuple<pos, pos> selectedMove = tier4[rand() % tier4.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            else if (!(tier5.empty()))
            { // if a tier5 move exists
                tuple<pos, pos> selectedMove = tier5[rand() % tier5.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }
            else
            { // a tier6 move
                tuple<pos, pos> selectedMove = tier6[rand() % tier6.size()];
                start = get<0>(selectedMove);
                end = get<1>(selectedMove);
            }

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