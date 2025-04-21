#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef struct {
    int** cells;
    int size;
} Board;

// Board operations
Board* createBoard(int size);
void freeBoard(Board* board);
void printBoard(const Board* board);
bool isBoardFull(const Board* board);
bool isValidMove(const Board* board, int row, int col);
bool makeMove(Board* board, int row, int col, int player);
bool hasStraightLine(const Board* board, int player);
bool hasWinningPath(const Board* board, int player);
int* getNeighbors(const Board* board, int player, int row, int col, int* count);

#endif