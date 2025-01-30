# include "sudoku.h"

int UNSOLVED = 81; 
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main(){
    int **puzzle;
    Sudoku * sudoku;

    puzzle = createPuzzle();
    printPuzzle(sudoku->squares);
    freePuzzle(sudoku->squares);

    sudoku = setUpPuzzle(puzzle);

    checkPuzzle(sudoku);

    return 0;
}