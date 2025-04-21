#include <stdio.h>
#include <stdlib.h>
#include "board.h"

Board* createBoard(int size) {
    Board* board = (Board*)malloc(sizeof(Board));
    board->size = size;
    board->cells = (int**)malloc(size * sizeof(int*));
    
    for (int i = 0; i < size; i++) {
        board->cells[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            board->cells[i][j] = 0;
        }
    }
    
    return board;
}

void freeBoard(Board* board) {
    for (int i = 0; i < board->size; i++) {
        free(board->cells[i]);
    }
    free(board->cells);
    free(board);
}

void printBoard(const Board* board) {
    printf(" ");
    for (int i = 1; i <= board->size; i++) {
        printf(" %d", i);
    }
    printf("\n --------------------------------\n");
    
    for (int i = 0; i < board->size; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j] == 1) {
                printf("W|");
            } else if (board->cells[i][j] == -1) {
                printf("B|");
            } else {
                printf(" |");
            }
        }
        printf("\n");
    }
    printf(" --------------------------------\n");
}

bool isBoardFull(const Board* board) {
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->cells[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

bool isValidMove(const Board* board, int row, int col) {
    return row >= 0 && row < board->size && 
           col >= 0 && col < board->size && 
           board->cells[row][col] == 0;
}

bool makeMove(Board* board, int row, int col, int player) {
    if (!isValidMove(board, row, col)) {
        return false;
    }
    board->cells[row][col] = player;
    return true;
}

// Get all neighboring cells with the same player value
int* getNeighbors(const Board* board, int player, int row, int col, int* count) {
    const int directions[6][2] = {
        {-1, 0},  // up
        {1, 0},   // down
        {0, -1},  // left
        {0, 1},   // right
        {-1, 1},  // up-right
        {1, -1}   // down-left
    };
    
    int* neighbors = (int*)malloc(12 * sizeof(int));  // max 6 neighbors, each with row and col
    *count = 0;
    
    for (int i = 0; i < 6; i++) {
        int newRow = row + directions[i][0];
        int newCol = col + directions[i][1];
        
        if (newRow >= 0 && newRow < board->size && 
            newCol >= 0 && newCol < board->size && 
            board->cells[newRow][newCol] == player) {
            neighbors[(*count) * 2] = newRow;
            neighbors[(*count) * 2 + 1] = newCol;
            (*count)++;
        }
    }
    
    return neighbors;
}

bool hasStraightLine(const Board* board, int player) {
    // Check for vertical line (Black player)
    if (player == -1) {
        for (int col = 0; col < board->size; col++) {
            bool complete = true;
            for (int row = 0; row < board->size; row++) {
                if (board->cells[row][col] != player) {
                    complete = false;
                    break;
                }
            }
            if (complete) return true;
        }
    }
    // Check for horizontal line (White player)
    else if (player == 1) {
        for (int row = 0; row < board->size; row++) {
            bool complete = true;
            for (int col = 0; col < board->size; col++) {
                if (board->cells[row][col] != player) {
                    complete = false;
                    break;
                }
            }
            if (complete) return true;
        }
    }
    return false;
}

bool dfs(const Board* board, int player, int row, int col, bool** visited) {
    if (player == 1) {  // White player (left to right)
        if (col == board->size - 1) return true;
    } else {  // Black player (top to bottom)
        if (row == board->size - 1) return true;
    }
    
    visited[row][col] = true;
    int neighborCount;
    int* neighbors = getNeighbors(board, player, row, col, &neighborCount);
    
    bool found = false;
    for (int i = 0; i < neighborCount && !found; i++) {
        int newRow = neighbors[i * 2];
        int newCol = neighbors[i * 2 + 1];
        if (!visited[newRow][newCol]) {
            found = dfs(board, player, newRow, newCol, visited);
        }
    }
    
    free(neighbors);
    return found;
}

bool hasWinningPath(const Board* board, int player) {
    bool** visited = (bool**)malloc(board->size * sizeof(bool*));
    for (int i = 0; i < board->size; i++) {
        visited[i] = (bool*)calloc(board->size, sizeof(bool));
    }
    
    bool won = false;
    if (player == 1) {  // White player (left to right)
        for (int row = 0; row < board->size && !won; row++) {
            if (board->cells[row][0] == player && !visited[row][0]) {
                won = dfs(board, player, row, 0, visited);
            }
        }
    } else {  // Black player (top to bottom)
        for (int col = 0; col < board->size && !won; col++) {
            if (board->cells[0][col] == player && !visited[0][col]) {
                won = dfs(board, player, 0, col, visited);
            }
        }
    }
    
    for (int i = 0; i < board->size; i++) {
        free(visited[i]);
    }
    free(visited);
    
    return won;
}