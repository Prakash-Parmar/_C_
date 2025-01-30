#ifndef SUDOKU_H
#define SUDOKU_H

#include<stdio.h>
#include<stdlib.h>

extern int UNSOLVED;
extern int SIZE_ROWS;
extern int SIZE_COLUMNS;

typedef struct Sudoku{
    struct Square *** squares;
    struct Box ** boxes;
} Sudoku;

typedef struct Box
{
    struct Square ** squares;
    int numbers;
    int possible[9];
    int solvable;  
    struct Box* next;
} Box;

typedef struct Square
{
    int number;
    int possible[9];
    int solvable;   
    Box *box;
    int row;
    int column;
} Square;




int **createPuzzle();
void printPuzzle(int** puzzle);
void freePuzzle(int **puzzle);
Sudoku * setUpPuzzle(int **puzzle);
int updateSudoku(Square ***sudoku, int row, int col);
int checkPuzzle(Square*** sudoku, Box ** boxes);

Sudoku * createSudoku(Square *** square, Box ** boxes);

// Box functions
Box ** createBoxes();
int updateBoxes(Square *** sudoku, int row, int col);

#endif