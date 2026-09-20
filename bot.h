#ifndef BOT_H
#define BOT_H

#include "board.h"

class Bot {
public:
    Bot();

    void makeMove(Board& board);
};

#endif