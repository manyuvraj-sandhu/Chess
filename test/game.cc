#include "game.h"
#include "pos.h"
#include <iostream>
#include "playerFactory.h"
#include "player.h"
#include "board.h"
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "pawn.h" // Consider replacing all these with a pieceFactory class
#include "textView.h"
#include "view.h"
#include "graphicsView.h"
#include <tuple>
#include <vector>

using namespace std;

Game::~Game() {
    delete theBoard;
    delete blackPlayer;
    delete whitePlayer;
    for (auto view : views) {
        delete view;
    }
}

// Function that checks the game state after a player has made a valid move
gameState Game::getState(){
    int playerThreatened = 1;
    if (curMove == 1) {
        playerThreatened = 0;
    }

    // First check that there are more than two kings on the board
    vector<Piece*> whitePieces = theBoard->getPieces(1);
    vector<Piece*> blackPieces = theBoard->getPieces(0);
    if (whitePieces.size() == 1 && blackPieces.size() == 1) { // there's only two kings left
        this->state = tieGame;
        return this->state;
    }

    // determine if the player whose move it is not is in check
    bool playerChecked = theBoard->isChecked(playerThreatened);

    vector<Piece *> remainingPieces = theBoard->getPieces(playerThreatened);
    for (Piece *piece : remainingPieces)
    {                                                    // for each piece of that colour
        vector<pos> pieceMoves = piece->getValidMoves(); // get their valid moves
        pos curPos = piece->getPos();
        for (pos p : pieceMoves)
        {
            Board *snapshot = new Board{*theBoard};
            snapshot->updateBoard(curPos, p); // try each move
            // If there exists a move that puts a player out of check
            if (!(snapshot->isChecked(playerThreatened)))
            {
                delete snapshot;
                if (playerChecked) { // the player is in check but there is a move to move them out
                    if (playerThreatened == 1)
                    {
                        this->state = whiteChecked;
                    }
                    else
                    {
                        this->state = blackChecked;
                    }
                } else { // the player is not in check and they can move to a spot not in check
                    this->state = ongoing;
                }
                return this->state;
            } else {
                delete snapshot;
            }
        }
    }
    // We've looped through all pieces and there is no move that keeps a player out of check
    if (playerChecked)
    { // the opposing player is checkmated
        if (playerThreatened == 1)
        {
            this->state = blackWin; // white has been checkmated
        }
        else
        {
            this->state = whiteWin; // black has been checkmated
        }
    }
    else
    { // The player is not in check but any move will put them in check
        this->state = stalemate;
    }
    return this->state;
}

void Game::notify(pos a, pos b) {
    for (auto view : views) {
        view->printBoard(a, b);
    }
}

void Game::addView(View* view) {
    views.emplace_back(view);
}

void Game::clearViews() {
    for (auto view : views) {
        delete view;
    }
    views.clear();
}

vector<View*> Game::getViews() { // views getter
    return views;
}

void Game::setTurn(int colour) {
    curMove = colour;
}

Board* Game::getBoard() {
    return theBoard;
}

void Game::setBoard(Board* newBoard) {
    delete theBoard;
    theBoard = newBoard;
}

// if the move is a promotion and the new piece is valid, swaps the new piece in and returns true
// if the move is not a promotion, returns true without swapping pieces, and false if the promotion is invalid
bool Game::handlePromotion(pos a, pos b, char piece) {
    bool invalidPiece = false;
    Piece* p = nullptr;

    if (theBoard->getPiece(a)->getType() == 'p' && b.y == 7) {
        switch (piece) {
            case 'q' :
                p = new Queen(0, a);
                break;
            case 'r' :
                p = new Rook(0, a, false);
                break;
            case 'n' :
                p = new Knight(0, a);
                break;
            case 'b' :
                p = new Bishop(0, a);
                break;
            default:
                invalidPiece = true;
        }
        if (invalidPiece) {
            delete p;
            return false;
        }
        theBoard->setPiece(p, a);
    }
    else if (theBoard->getPiece(a)->getType() == 'P' && b.y == 0) {
        switch (piece) {
            case 'Q' :
                p = new Queen(1, a);
                break;
            case 'R' :
                p = new Rook(1, a, false);
                break;
            case 'N' :
                p = new Knight(1, a);
                break;
            case 'B' :
                p = new Bishop(1, a);
                break;
            default:
                invalidPiece = true;
        }
        if (invalidPiece) {
            delete p;
            return false;
        }
        theBoard->setPiece(p, a);
    }
    return true;
}

void Game::handleCastle(pos a, pos b) {

    Piece* p = theBoard->getPiece(a);
    p->setCanCastle(false);




    if (p->getType() == 'k' || p->getType() == 'K') {
        if (b.x - a.x == -2) {
            theBoard->updateBoard({0, a.y}, {3, a.y});
        }
        else if (b.x - a.x == 2) {
            theBoard->updateBoard({7, a.y}, {5, a.y});
        }
    }
}

void Game::handlePassant(pos a, pos b) {
    int colour = theBoard->getPiece(a)->getColour();
    theBoard->resetPassantable(colour);
    theBoard->getPiece(a)->setCanMoveTwo(false);

    if (theBoard->getPiece(a)->getType() != 'p' && theBoard->getPiece(a)->getType() != 'P') {
        //not a pawn making the move
        return;
    }

    if (a.x != b.x && theBoard->getPiece(b) == nullptr) { // passant kill case
        theBoard->setPiece(nullptr, {b.x, a.y});
        return;
    }

    if ((a.y - b.y == 2) || (a.y - b.y == -2)) { // set passantable to true if pawn moves 2
        theBoard->getPiece(a)->setPassantable(true);
        return;
    }
}

bool Game::isBoardValid(){
    int BKings = theBoard->countPieces('k');
    int Wkings = theBoard->countPieces('K');
    // Checking if there is only one white king and one black king
    if (BKings != 1 || Wkings!= 1){
        return false;
    }
    // Checking if there are any pawns on the last rows
    int pawns = 0;

    for (int j = 0; j < 8; ++j)
    {
        if (theBoard->getPiece(pos{j, 0}) != nullptr)
        {
            if (theBoard->getPiece(pos{j, 0})->getType() == 'p' || theBoard->getPiece(pos{j, 0})->getType() == 'P')
            {
                ++pawns;
            }
        }
    }

    for (int j = 0; j < 8; ++j)
    {
        if (theBoard->getPiece(pos{j, 7}) != nullptr)
        {
            if (theBoard->getPiece(pos{j, 7})->getType() == 'p' || theBoard->getPiece(pos{j, 7})->getType() == 'P')
            {
                ++pawns;
            }
        }
    }

    if (pawns != 0){
        return false;
    }
    // Checking if either of the kings is in check
    if (theBoard->isChecked(0) == true || theBoard->isChecked(1) == true){
        return false;
    }
    return true;
}

char Game::play() {
    
    theBoard->updateBoard(pos{-1, -1}, pos{-1, -1});
    
    state = ongoing;
    delete whitePlayer;
    delete blackPlayer;
    string p1;
    string p2;
    cin >> p1;
    cin >> p2;
    try {
        whitePlayer = PlayerFactory::createPlayer(p1, 1, this);
        blackPlayer = PlayerFactory::createPlayer(p2, 0, this);
    }
    catch (...) {
        return 'i'; //return i for invalid setup
    }

    tuple<pos, pos, char> move ({-1, -1}, {-1, -1}, ' ');
    Player* curPlayer;
    curMove = 1;
    // notify(pos{0, 0}, pos{7, 7});
    while (state == whiteChecked || state == blackChecked || state == ongoing) {
        
        if (curMove == 1) {
            curPlayer = whitePlayer;
	        //move = whitePlayer->determineMove();
        }
        else {
            //move = blackPlayer->determineMove();
            curPlayer = blackPlayer;
        }

        bool moveDone = false;

        while (!moveDone) {
            // NOTE: On resign, by convention, we return <pos{-1,-1}, pos{-1,-1}>
            move = curPlayer->determineMove(cin); // get player's next move

            pos start = get<0>(move);
            if (start == pos{-1, -1})
            { // player has resigned
                if (curMove == 1)
                {
                    state = blackWin;
                    moveDone = true;
                }
                else
                {
                    state = whiteWin;
                    moveDone = true;
                }
            }
            else if (theBoard->getPiece(start) == nullptr)  // No piece in the starting position
            {
                cout << "Invalid move. Please make another move." << endl;
            }
            else
            {
                Piece *curPiece = theBoard->getPiece(start);
                pos end = get<1>(move);
                if (!(curPiece->getColour() == curMove)) 
                {
                    cout << "That is not your piece. Please make another move." << endl;
                }
                else if (curPiece->isValidMove(end, theBoard)) 
                {
                    Board *snapshot = new Board(*theBoard); 
                    handlePassant(get<0>(move), get<1>(move));
                    handleCastle(get<0>(move), get<1>(move));
                    if (!handlePromotion(get<0>(move), get<1>(move), get<2>(move)))
                    {
                        this->setBoard(snapshot);
                        cout << "You cannot promote to that piece. Please try again." << endl;
                    } else {
                        theBoard->updateBoard(start, end);
                        if (theBoard->isChecked(curMove))
                        { // player puts themselves in check
                            this->setBoard(snapshot);
                            cout << "You are in check. Please make another move." << endl;
                        } else {  // happy path
                            delete snapshot;
                            gameState curState = this->getState();
                            notify(start, end);
                            if (curState == blackChecked) {
                                cout << "black is in check." << endl;
                            } else if (curState == whiteChecked) {
                                cout << "white is in check." << endl;
                            } else if (curState == tieGame) {
                                return 't';
                            } else if (curState == stalemate) {
                                return 's';
                            } else if (curState == whiteWin) {
                                return 'w';
                            } else if (curState == blackWin) {
                                return 'b';
                            }
                            moveDone = true;
                            curMove = (curMove + 1) % 2; // Flip the player's turn
                        }
                    }
                }
                else
                {
                    cout << "invalid move. Please make another move." << endl;
                }
            }
        }
        //validate move
	    if (state == whiteWin || state == blackWin) {
	        break;
	    }
    } //while
    if (state == whiteWin) {
        return 'w'; 
    }
    else if (state == blackWin) {
        return 'b';
    } else if (state == tieGame) {
        return 't';
    }
    else {
        return 'i';
    }
}
