#include "main.h"
#include <iostream>
#include <string>
#include "player/player.h"
#include "player/playerFactory.h"
#include "board/board.h"
#include "pos.h"
#include "game/game.h"
#include "board/king.h"
#include "board/queen.h"
#include "board/knight.h"
#include "board/bishop.h"
#include "board/rook.h"
#include "board/pawn.h"
#include "view/view.h"
#include "view/textView.h"
#include "view/graphicsView.h"
#include <iomanip>

using namespace std;

/**
 * White: 1
 * Black: 0
 * 
 * Use this when referencing colour
*/

int main() {
    float whiteWins = 0;
    float blackWins = 0;
	char winner;
    string s;
    Game* game = new Game();
	Board* board = new Board();
	game->setBoard(board);
    while (cin >> s){
		bool invalid = false;
		if (s == "game") 
		{ // start a new game
			if (board->isEmpty()) {
				board->setToStart();
			} 
			if (game->getViews().empty()) 
			{ // If we haven't entered the game from setup mode add views
				game->addView(new TextView{board, cout});
				game->addView(new GraphicsView{board});
			}

			// Function that plays a game
			winner = game->play();
			if (winner == 'w') {
				whiteWins = whiteWins + 1;
				cout << "White wins! Congratulations!" << endl;
			} else if (winner == 'b') {
				blackWins = blackWins + 1;
				cout << "Black wins! Congratulations!" << endl;
			} else if (winner == 't') {
				whiteWins = whiteWins + 0.5;
				blackWins = blackWins + 0.5;
				cout << "Tie game! Congratulations to both players!" << endl;
			} else if (winner == 's') {
				whiteWins = whiteWins + 0.5;
				blackWins = blackWins + 0.5;
				cout << "Stalemate! Congratulations to both players!" << endl;
			}
			else {
				cout << "invalid players" << endl;
			}
			board->clear();
			game->clearViews();
		}
		else if (s == "setup") 
		{ // enter setup mode
			setupLoop(game);
		}
		else 
		{ // some other input
			invalid = true;
		}
		if (invalid) 
		{
			cout << "invalid input" << endl;
		}
    } //while
	delete game;

	cout << "Final Score:" << endl;

	// check to see if there is a decimal
	if (whiteWins == int(whiteWins)) 
	{ // no fractional part
		cout << setprecision(0) << fixed;
	} else {
		cout << setprecision(1) << fixed;
	}
	cout << "White: " << whiteWins << endl;

	if (blackWins == int(blackWins))
	{ // no fractional part
		cout << setprecision(0) << fixed;
	}
	else
	{
		cout << setprecision(1) << fixed;
	}
	cout << "Black: " << blackWins << endl;

    return 0;
}


void setupLoop(Game* game) {
	Board* board = game->getBoard();

	// add views
	game->addView(new TextView{board, cout});
	game->addView(new GraphicsView{board});
	string s;
	
    while (cin >> s) {
		bool invalid = false;
		string chesspos = "";

		if (s == "+") {
			cin >> s;
			cin >> chesspos;
			pos arraypos = {0, 0};
			Piece* p = nullptr;
			try 
			{ // convert to x,y-coords from 0-7
				arraypos = convertPos(chesspos);
			}
			catch(length_error& e) {
				invalid = true;
			} catch (out_of_range& e) {
				invalid = true;
			}
			if (!invalid) 
			{ // add a piece
				//white
				if (s == "K") {
					p = new King(1, arraypos, false);
				}
				else if (s == "Q") {
					p = new Queen(1, arraypos);
				}
				else if (s == "R") {
					p = new Rook(1, arraypos, false);
				}
				else if (s == "N") {
					p = new Knight(1, arraypos);
				}
				else if (s == "B") {
					p = new Bishop(1, arraypos);
				}
				else if (s == "P") {
					p = new Pawn(1, arraypos, false);
				}
				//black
				else if (s == "k") {
					p = new King(0, arraypos, false);
				}
				else if (s == "q") {
					p = new Queen(0, arraypos);
				}
				else if (s == "r") {
					p = new Rook(0, arraypos, false);
				}
				else if (s == "n") {
					p = new Knight(0, arraypos);
				}
				else if (s == "b") {
					p = new Bishop(0, arraypos);
				}
				else if (s == "p") {
					p = new Pawn(0, arraypos, false);
				}
				//otherwise
				else {
					invalid = true;
				}
			}
			if (!invalid) {
				board->setPiece(p, arraypos);
			}
			game->notify(arraypos, arraypos);
		}

		else if (s == "-") {
			cin >> chesspos;
			pos arraypos = {0, 0};
			try 
			{ // convert piece to x,y-coords
				arraypos = convertPos(chesspos);
			}
			catch(length_error& e) {
				invalid = true;
			} catch (out_of_range& e) {
				invalid = true;
			}
			if (!invalid) 
			{ // set that position to nullptr
				game->getBoard()->setPiece(nullptr, arraypos);
			}
			game->notify(arraypos, arraypos);
		}

		else if (s == "=") {
			cin >> s;
			if (s == "white") {
				game->setTurn(1);
			}
			else if (s == "black") {
				game->setTurn(0);
			}
			else {
				invalid = true;
			}
		}

		else if (s == "done") 
		{ // exit setup mode
			board->updateBoard(pos{-1, -1}, pos{-1, -1}); // this just makes it updateValidMoves for all pieces
			if (game->isBoardValid()) {
				return;
			} else {
				cout << "This board setup is not valid." << endl;
			}
		}

		else if (s == "default") {
			board->clear();
			board->setToStart();

			// notify all relevant spaces
			for (int i = 6; i < 8; ++i) {
				for (int j = 0; j < 8; ++j) {
					game->notify({j, i}, {j, i});
				}
			}

			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 8; ++j) {
					game->notify({j, i}, {j, i});
				}
			}
		}

		else if (s == "clear") {
			board->clear();
			game->notify({0, 0}, {7, 7});
		}

		else {
			invalid = true;
		}

		if (invalid) {
			cout << "invalid input" << endl;
		}
    }
}

