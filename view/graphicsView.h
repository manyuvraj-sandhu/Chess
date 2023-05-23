#ifndef _GRAPHICSVIEW_H_
#define _GRAPHICSVIEW_H_

#include "view.h"
#include "window.h"

struct pos;
class Board;

class GraphicsView : public View {
    Xwindow* window; 

public:
    GraphicsView(Board* board); // ctor

    void printOutput(pos a, pos b) override;

    ~GraphicsView() override;
};

#endif