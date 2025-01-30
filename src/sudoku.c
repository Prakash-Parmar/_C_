# include "sudoku.h"

int UNSOLVED = 81; 
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main(){
    int **puzzle;
    int progress;
    Sudoku * sudoku;

    puzzle = createPuzzle();
    printPuzzle(sudoku->squares);
    freePuzzle(sudoku->squares);

    sudoku = setUpPuzzle(puzzle);

    while(UNSOLVED){
        progress = checkPuzzle(sudoku->squares, sudoku->boxes);

        if(progress == 0){
            break;
        }
    }


    return 0;
}