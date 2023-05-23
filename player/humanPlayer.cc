#include "humanPlayer.h"
#include <iostream>
#include <string>
#include <istream>
#include <tuple>
#include "../pos.h"
#include <sstream>

using namespace std;

HumanPlayer::HumanPlayer(int colour) : Player{colour} {}

HumanPlayer::~HumanPlayer() {} // dtor

tuple<pos, pos, char> HumanPlayer::determineMove(istream& in) {
    string cmd;
    while (in >> cmd) {
        // breaks when EOF is given
        if (cmd == "move")
        {
            string line;
            if (getline(in, line)) {
                istringstream iss{line};
                string start, end;
                iss >> start;
                iss >> end;
                char promotePiece;
                if (iss >> promotePiece) {
                    try {
                        tuple<pos, pos, char> move = {convertPos(start), convertPos(end), promotePiece};
                        return move;
                    }
                    catch (...) {
                        cout << "invalid input. try again." << endl;
                        continue;
                    }
                } else {
                    try {
                        tuple<pos, pos, char> move ={convertPos(start), convertPos(end), ' '};
                        return move;
                    }
                    catch (...) {
                        cout << "invalid input. try again." << endl;
                        continue;
                    }
                }
            } else {
                cout << "invalid input. try again." << endl;
            }
        }
        else if (cmd == "resign")
        {
            return tuple<pos, pos, char>{pos{-1, -1}, pos{-1, -1}, ' '};
        }
        else
        {
            cout << "invalid input. Try again." << endl;
        }
    }
    return {{-1, -1}, {-1, -1}, ' '};
}