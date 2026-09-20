#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"

class TicTacToe {
private:
    Board board;
    Player player[2];
    int currentPlayerIndex;

    Player& getCurrentPlayer();
    void switchTurn();

public:
    TicTacToe();

    void play();
};

#endif