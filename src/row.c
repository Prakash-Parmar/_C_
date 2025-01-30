#include "sudoku.h"

int checkRows(Square *** sudoku, Box ** boxes){
    
    int i, j, k;

    int sum[9];
    int places[9];

    // loop throught all the rows
    for(i=0; i<SIZE_ROWS; i++){

        for(j=0; j<9; j++){
            sum[j] = 0;
            places[j] = 0;
        }

        // loop through each square in a row
        for(j=0; j<9; j++){
            if(sudoku[i][j]->number != 0){
                continue;
            }

            //loop through all possible number
            for(k=0; k<9; k++){
                if(sudoku[i][j]->possible[k] == 0){
                    sum[k]++;
                    places[k] = j;
                }
            }
        }

        for(k=0; k<9; k++){
            if(sum[k] == 1){
                sudoku[i][places[k]]->number = k+1;
                sudoku[i][places[k]]->solvable = 0;
                UNSOLVED--;

                updateSudoku(sudoku, i, places[k]);
                updateBoxes(sudoku, i, places[k]);

                return 1; 
            }
        }
    }
    
    return 0;
}