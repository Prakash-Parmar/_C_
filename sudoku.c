# include "sudoku.h"

int main(){
    int **puzzle;
    puzzle = createPuzzle();
    printPuzzle(puzzle);
    freePuzzle(puzzle);

    return 0;
}