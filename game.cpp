#include "game.h"
#include <iostream>

using namespace std;

TicTacToe::TicTacToe()
    : player{Player('X'), Player('O')},
      currentPlayerIndex(0) {
}

Player& TicTacToe::getCurrentPlayer() {
    return player[currentPlayerIndex];
}

void TicTacToe::switchTurn() {
    currentPlayerIndex = 1 - currentPlayerIndex;
}

void TicTacToe::play() {
    int row;
    int col;

    while (!board.isFull()) {

        board.drawBoard();

        Player& currentPlayer = getCurrentPlayer();

        cout << "Player " << currentPlayer.getSymbol()
             << ", enter your move (row and column): ";

        cin >> row >> col;

        while (!board.isValidMove(row, col)) {
            cout << "Invalid move. Try again: ";
            cin >> row >> col;
        }

        board.makeMove(row, col, currentPlayer.getSymbol());

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