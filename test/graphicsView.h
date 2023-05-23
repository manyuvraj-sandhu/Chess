#ifndef _GRAPHICSVIEW_H_
#define _GRAPHICSVIEW_H_

#include "view.h"
#include "window.h"

struct pos;
class Game;

class GraphicsView : public View {
    Xwindow* window; 

public:
    GraphicsView(Game* game); // ctor

    void printOutput(pos a, pos b) override;

    ~GraphicsView() override;
};

#endif
