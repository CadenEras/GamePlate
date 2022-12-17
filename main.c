#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "headers/Tic-Tac-Toe/Game.h"



int main(int argc, char *argv[]) {

    char winner = ' ';
    resetBoard();

    while(winner == ' ' && checkFreeSpaces() != 0){
        printBoard();
        
        playerMove();
        winner = checkWin();
        if(winner != ' ' || checkFreeSpaces() == 0){
            break;
        }

        computerMove();
        winner = checkWin();
        if(winner != ' ' || checkFreeSpaces() == 0){
            break;
        }
    }

    printBoard();
    printWinner(winner);

return 0;    
}