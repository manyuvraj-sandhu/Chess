#include "textView.h"
#include "../board/piece.h"
#include "../board/board.h"
#include <iostream>


using namespace std;

TextView::TextView(Board* board, std::ostream& out) : View{board}, out{out} {
    for (int i = 0; i < 8; ++i)
    {
        out << (8 - i) << " ";
        for (int j = 0; j < 8; ++j)
        {
            Piece *curPiece = board->getPiece(pos{j, i});
            if (curPiece == nullptr)
            {
                if ((i + j) % 2 == 1)
                {
                    out << "_"; // dark space
                }
                else
                {
                    out << " "; // white space
                }
            }
            else
            {
                out << curPiece->getType();
            }
        }
        out << endl;
    }
    out << endl;
    out << "  " << 'a' << 'b' << 'c' << 'd' << 'e' << 'f' << 'g' << 'h' << endl;
    out << endl;
}

void TextView::printOutput(pos a, pos b) {
    for (int i = 0; i < 8; ++i)
    {
        out << (8 - i) << " ";
        for (int j = 0; j < 8; ++j)
        {
            Piece *curPiece = board->getPiece(pos{j, i});
            if (curPiece == nullptr)
            {
                if ((i + j) % 2 == 1)
                {
                    out << "_"; // dark space
                }
                else
                {
                    out << " "; // white space
                }
            }
            else
            {
                out << curPiece->getType();
            }
        }
        out << endl;
    }
    out << endl;
    out << "  " << 'a' << 'b' << 'c' << 'd' << 'e' << 'f' << 'g' << 'h' << endl;
    out << endl;
}
