#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "player.h"

int main() {
    srand(time(NULL));
    int size;
    printf("Enter board size (minimum 3): ");
    scanf("%d", &size);
    
    if (size < 3) {
        printf("Board size must be at least 3x3\n");
        return 1;
    }
    
    Board* board = createBoard(size);
    Player* whitePlayer = createHumanPlayer(1);
    Player* blackPlayer = createRandomPlayer(-1);
    
    Player* currentPlayer = whitePlayer;
    bool gameOver = false;
    
    while (!gameOver) {
        printBoard(board);
        printf("%s player's turn\n", currentPlayer->playerType == 1 ? "White" : "Black");
        
        Move move = currentPlayer->getMove(board);
        makeMove(board, move.row, move.col, currentPlayer->playerType);
        
        // Check for straight line win
        if (hasStraightLine(board, currentPlayer->playerType)) {
            printBoard(board);
            printf("%s player wins with a straight line!\n",
                   currentPlayer->playerType == 1 ? "White" : "Black");
            gameOver = true;
            continue;
        }
        
        // Check for winning path
        if (hasWinningPath(board, currentPlayer->playerType)) {
            printBoard(board);
            printf("%s player wins with a connected path!\n",
                   currentPlayer->playerType == 1 ? "White" : "Black");
            gameOver = true;
            continue;
        }
        
        // Check for full board
        if (isBoardFull(board)) {
            printBoard(board);
            printf("Game over - Board is full!\n");
            gameOver = true;
            continue;
        }
        
        // Switch players
        currentPlayer = (currentPlayer == whitePlayer) ? blackPlayer : whitePlayer;
    }
    
    freeBoard(board);
    freePlayer(whitePlayer);
    freePlayer(blackPlayer);
    
    return 0;
}