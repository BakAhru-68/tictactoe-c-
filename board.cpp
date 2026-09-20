#include "board.h"
#include <iostream>

using namespace std;

Board::Board() {
    reset();
}

void Board::reset() {
    filledCells = 0;

    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            grid[row][col] = ' ';
        }
    }
}

bool Board::isValidMove(int row, int col) const {
    return row >= 0 &&
           row < 3 &&
           col >= 0 &&
           col < 3 &&
           grid[row][col] == ' ';
}

bool Board::makeMove(int row, int col, char symbol) {
    if (!isValidMove(row, col)) {
        return false;
    }

    grid[row][col] = symbol;
    filledCells++;

    return true;
}

bool Board::checkWinner(char symbol) const {
    // Rows dan columns
    for (int i = 0; i < 3; i++) {

        // Row
        if (grid[i][0] == symbol &&
            grid[i][1] == symbol &&
            grid[i][2] == symbol) {
            return true;
        }

        // Column
        if (grid[0][i] == symbol &&
            grid[1][i] == symbol &&
            grid[2][i] == symbol) {
            return true;
        }
    }

    // Main diagonal
    if (grid[0][0] == symbol &&
        grid[1][1] == symbol &&
        grid[2][2] == symbol) {
        return true;
    }

    // Other diagonal
    if (grid[0][2] == symbol &&
        grid[1][1] == symbol &&
        grid[2][0] == symbol) {
        return true;
    }

    return false;
}

bool Board::isFull() const {
    return filledCells == 9;
}

int Board::getFilledCells() const {
    return filledCells;
}

char Board::getCell(int row, int col) const {
    if (row < 0 || row >= 3 || col < 0 || col >= 3) {
        return ' ';
    }

    return grid[row][col];
}

void Board::drawBoard() const {
    cout << "\n";

    cout << " " << grid[0][0] << " | "
         << grid[0][1] << " | "
         << grid[0][2] << "\n";

    cout << "---+---+---\n";

    cout << " " << grid[1][0] << " | "
         << grid[1][1] << " | "
         << grid[1][2] << "\n";

    cout << "---+---+---\n";

    cout << " " << grid[2][0] << " | "
         << grid[2][1] << " | "
         << grid[2][2] << "\n";

    cout << "\n";
}