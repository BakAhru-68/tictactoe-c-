#include "player.h"

Player::Player(char sym) {
    symbol = sym;
}

char Player::getSymbol() const {
    return symbol;
}