#include "bot.h"

#include <cstdlib>
#include <ctime>

Bot::Bot() {
    srand(time(nullptr));
}

void Bot::makeMove(char board[3][3]) {

    int emptyRows[9];
    int emptyCols[9];

    int count = 0;

    // Cari semua cell yang kosong
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {

            if (board[row][col] == ' ') {
                emptyRows[count] = row;
                emptyCols[count] = col;
                count++;
            }
        }
    }

    // Board penuh
    if (count == 0) {
        return;
    }

    // Pilih cell kosong secara random
    int choice = rand() % count;

    board[emptyRows[choice]][emptyCols[choice]] = 'O';
}