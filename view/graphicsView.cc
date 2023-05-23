#include "graphicsView.h"
#include "../board/board.h"
#include "window.h"
#include "../board/piece.h"
#include <string>

using namespace std;

GraphicsView::GraphicsView(Board* board) : View{board}, window{new Xwindow(1200, 1200)} {
    for (int i = 0; i < 8; ++i) {
        window->drawString(32, i * 75 + 32, to_string(8 - i));
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 1)
            {
                window->fillRectangle(j * 75 + 75, i * 75, 75, 75, 4);
            }
            else
            {
                window->fillRectangle(j * 75 + 75, i * 75, 75, 75, 2);
            }
            Piece* curPiece = board->getPiece(pos{j,i});
            if (curPiece != nullptr) {
                string pieceName;
                pieceName.push_back(curPiece->getType());
                window->drawString(j * 75 + 32 + 75, i * 75 + 32, pieceName);
            }
        }
    }

    char legend = 'a';
    for (int i = 0 ; i < 8; ++i) {
        string s;
        s.push_back(legend);
        window->drawString(i * 75 + 32 + 75, 8 * 75 + 32, s);
        ++legend;
    }
} // ctor

void GraphicsView::printOutput(pos a, pos b) {
    Piece* startPiece = board->getPiece(a);
    int colour;
    if ((a.x + a.y) % 2 == 1)
    {
        colour = 4;
    }
    else
    {
        colour = 2;
    }
    window->fillRectangle(a.x * 75 + 75, a.y * 75, 75, 75, colour);
    if (startPiece != nullptr) {
        char pieceType = startPiece->getType();
        string s;
        s.push_back(pieceType);
        window->drawString(a.x * 75 + 32 + 75, a.y * 75 + 32, s);
    }
    Piece *endPiece = board->getPiece(b);
    if ((b.x + b.y) % 2 == 1)
    {
        colour = 4;
    }
    else
    {
        colour = 2;
    }
    window->fillRectangle(b.x * 75 + 75, b.y * 75, 75, 75, colour);
    if (endPiece != nullptr)
    {
        char pieceType = endPiece->getType();
        string s;
        s.push_back(pieceType);
        window->drawString(b.x * 75 + 32 + 75, b.y * 75 + 32, s);
    }
}

GraphicsView::~GraphicsView() {
    delete window;
}
