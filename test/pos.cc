#include "pos.h"
#include <string>
#include <stdexcept>

// constructor
pos::pos(int x, int y) : x{x}, y{y} {}

// equality
bool pos::operator==(const pos &other)
{
    return this->x == other.x && this->y == other.y;
}

// inequality
bool pos::operator!=(const pos &other)
{
    return !(*this == other);
}

// copy assignment
pos& pos::operator=(const pos& other) {
    this->x = other.x;
    this->y = other.y;
    return *this;
}

// determine if it is in the board bounds
bool pos::inBounds() {
    return 0 <= x && x < 8 && 0 <= y && y < 8;
}

// addition
pos operator+(const pos &pos1, const pos &pos2)
{
    return pos{pos1.x + pos2.x, pos1.y + pos2.y};
}

// subtraction
pos operator-(const pos &pos1, const pos &pos2)
{
    return pos(pos1.x - pos2.x, pos1.y - pos2.y);
}

// convert chess coordinates to array coordinates
pos convertPos(std::string& s)
{
    if (s.size() != 2) {
	throw std::length_error{"size must be 2"};
    }
    char c1 = s[0];
    char c2 = s[1];
    if (c1 < 'a' || c1 > 'h' || c2 < '1' || c2 > '8') {
	throw std::out_of_range{"coordinates out of bounds"};
    }
    int x = c1 - 'a';
    int yc = c2 - '0'; // converts '1' to 1
    int y = 8 - yc; // converts from chessboard y to array y
    return pos(x, y);
}

std::string convertBack(pos p) {
    char x = p.x + 'a';
    int yi = 8 - p.y;
    char y = yi + '0';
    std::string s = "";
    s.append(1, x);
    s.append(1, y);
    return s;
}
