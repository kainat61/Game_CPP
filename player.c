#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"

Move getHumanMove(const Board* board) {
    Move move;
    do {
        printf("Enter row and column (1-%d): ", board->size);
        scanf("%d %d", &move.row, &move.col);
        move.row--; // Convert to 0-based indexing
        move.col--;
    } while (!isValidMove(board, move.row, move.col));
    return move;
}

Move getRandomMove(const Board* board) {
    int emptyCells = 0;
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j] == 0) emptyCells++;
        }
    }
    
    int target = rand() % emptyCells;
    int count = 0;
    Move move;
    
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j] == 0) {
                if (count == target) {
                    move.row = i;
                    move.col = j;
                    return move;
                }
                count++;
            }
        }
    }
    
    // Should never reach here
    move.row = move.col = -1;
    return move;
}

Player* createHumanPlayer(int playerType) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->playerType = playerType;
    player->getMove = getHumanMove;
    return player;
}

Player* createRandomPlayer(int playerType) {
    Player* player = (Player*)malloc(sizeof(Player));
    player->playerType = playerType;
    player->getMove = getRandomMove;
    return player;
}

void freePlayer(Player* player) {
    free(player);
}