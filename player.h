#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    char symbol;

public:
    Player(char sym);

    char getSymbol() const;
};

#endif