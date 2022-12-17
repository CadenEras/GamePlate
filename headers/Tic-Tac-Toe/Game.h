#pragma once
#ifndef GAME_H
#define GAME_H

void resetBoard();
void printBoard();
int checkFreeSpaces();
void computerMove();
void playerMove();
char checkWin();
void printWinner(char);

#endif