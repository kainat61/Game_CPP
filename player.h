#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

typedef struct {
    int row;
    int col;
} Move;

typedef struct {
    int playerType;  // 1 for White, -1 for Black
    Move (*getMove)(const Board* board);
} Player;

// Player types
Player* createHumanPlayer(int playerType);
Player* createRandomPlayer(int playerType);
Player* createSmartPlayer(int playerType);
Player* createMonteCarloPlayer(int playerType);
void freePlayer(Player* player);

#endif