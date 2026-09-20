#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include "bot.h"

class TicTacToe {
private:
    Board board;
    Player player[2];
    Bot bot;

    int currentPlayerIndex;
    bool gameOver;
    char winner;

    Player& getCurrentPlayer();
    const Player& getCurrentPlayer() const;
    void switchTurn();

public:
    TicTacToe();

    // CLI version
    void play();

    // GUI functions
    bool makePlayerMove(int row, int col);
    bool makeBotMove();

    bool checkWinner() const;
    bool isDraw() const;
    bool isGameOver() const;

    char getCell(int row, int col) const;
    char getCurrentSymbol() const;
    char getWinner() const;

    void reset();
};

#endif