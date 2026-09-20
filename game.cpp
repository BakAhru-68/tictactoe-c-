#include "game.h"

#include <iostream>

using namespace std;

TicTacToe::TicTacToe()
    : player{Player('X'), Player('O')},
      currentPlayerIndex(0),
      gameOver(false),
      winner(' ') {
}

Player& TicTacToe::getCurrentPlayer() {
    return player[currentPlayerIndex];
}

const Player& TicTacToe::getCurrentPlayer() const {
    return player[currentPlayerIndex];
}

void TicTacToe::switchTurn() {
    currentPlayerIndex = 1 - currentPlayerIndex;
}

void TicTacToe::reset() {
    board.reset();

    currentPlayerIndex = 0;
    gameOver = false;
    winner = ' ';
}

bool TicTacToe::makePlayerMove(int row, int col) {

    if (gameOver) {
        return false;
    }

    // Player selalu X
    if (currentPlayerIndex != 0) {
        return false;
    }

    if (!board.makeMove(row, col, 'X')) {
        return false;
    }

    // Cek kemenangan X
    if (board.checkWinner('X')) {
        gameOver = true;
        winner = 'X';
        return true;
    }

    // Cek draw
    if (board.isFull()) {
        gameOver = true;
        winner = ' ';
        return true;
    }

    // Ganti ke Bot
    switchTurn();

    return true;
}

bool TicTacToe::makeBotMove() {

    if (gameOver) {
        return false;
    }

    // Bot selalu O
    if (currentPlayerIndex != 1) {
        return false;
    }

    bot.makeMove(board);

    // Cek kemenangan O
    if (board.checkWinner('O')) {
        gameOver = true;
        winner = 'O';
        return true;
    }

    // Cek draw
    if (board.isFull()) {
        gameOver = true;
        winner = ' ';
        return true;
    }

    // Kembali ke Player
    switchTurn();

    return true;
}

bool TicTacToe::checkWinner() const {
    return board.checkWinner('X') ||
           board.checkWinner('O');
}

bool TicTacToe::isDraw() const {
    return board.isFull() && !checkWinner();
}

bool TicTacToe::isGameOver() const {
    return gameOver;
}

char TicTacToe::getCell(int row, int col) const {
    return board.getCell(row, col);
}

char TicTacToe::getCurrentSymbol() const {
    return getCurrentPlayer().getSymbol();
}

char TicTacToe::getWinner() const {
    return winner;
}

void TicTacToe::play() {

    int row;
    int col;

    while (!board.isFull()) {

        board.drawBoard();

        Player& currentPlayer = getCurrentPlayer();

        cout << "Player "
             << currentPlayer.getSymbol()
             << ", enter your move (row and column): ";

        cin >> row >> col;

        while (!board.isValidMove(row, col)) {

            cout << "Invalid move. Try again: ";

            cin >> row >> col;
        }

        board.makeMove(
            row,
            col,
            currentPlayer.getSymbol()
        );

        if (board.checkWinner(currentPlayer.getSymbol())) {

            board.drawBoard();

            cout << "Player "
                 << currentPlayer.getSymbol()
                 << " wins!\n";

            return;
        }

        switchTurn();
    }

    board.drawBoard();

    cout << "It's a draw!\n";
}