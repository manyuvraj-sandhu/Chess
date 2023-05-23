#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_

#include "view.h"
#include <ostream>

struct pos;

class TextView : public View {
    std::ostream& out;

public:
    void printOutput(pos a, pos b) override;

    TextView(Board* board, std::ostream& out); // ctor
};

#endif