#ifndef BOARD_H
#define BOARD_H

class Board {
private:
    char grid[3][3];
    int filledCells;

public:
    Board();

    bool isValidMove(int row, int col) const;
    bool makeMove(int row, int col, char symbol);
    bool checkWinner(char symbol) const;
    bool isFull() const;

    int getFilledCells() const;

    char getCell(int row, int col) const;

    void reset();
    void drawBoard() const;
};

#endif