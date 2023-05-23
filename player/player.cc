#include "player.h"
#include "../game/game.h"

Player::Player(int colour) : colour{colour}, checked{false} {} // Ctor

Player::~Player() {}

bool Player::isChecked() {
    return checked;
}

void Player::setChecked(bool checked) {
    checked = checked;
}

int Player::getColour() {
    return colour;
}