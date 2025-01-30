#include "sudoku.h"

Sudoku * createSudoku(Square *** squares, Box ** boxes){
    Sudoku * sudoku;
    sudoku = malloc(sizeof(Sudoku));

    sudoku->squares = squares;
    sudoku->boxes = boxes;

    return sudoku;
}

Sudoku * setUpPuzzle(int **puzzle){
    
    Square*** sudoku;
    Box ** boxes;
    int i, j, k;
    int currBox = 0;

    //Initialize the sudoku
    sudoku = (Square***)malloc(sizeof(Square**)*9);
    boxes = createBoxes();

    for(i=0; i<SIZE_ROWS; i++){
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);

        for(j=0; j<SIZE_COLUMNS; j++){
            sudoku[i][j] = (Square*) malloc(sizeof(Square));

            sudoku[i][j]->number = puzzle[i][j];
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            //boxIndex = (row/3) * 3 + (col/3)
            currBox = (i/3) * 3 + (j/3);

            boxes[currBox]->squares[boxes[currBox]->numbers] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currBox];
            boxes[currBox]->numbers++;

            for(k=0; k<SIZE_ROWS; k++){
                sudoku[i][j]->possible[k] = 0;
            }
        }
    }

    //go through sudoku to check the possible number
    for(i=0; i<SIZE_ROWS; i++){
        for(j=0; j<SIZE_COLUMNS; j++){
            if(sudoku[i][j]->number != 0){
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }    
        }
    }

    return createSudoku(sudoku, boxes);
}

int updateSudoku(Square ***sudoku, int row, int col){
            int x;
            int digit = sudoku[row][col]->number;

            //loop through row
            for(x=0; x<SIZE_ROWS; x++){
                if(sudoku[x][col]->possible[digit-1] == 0){
                    sudoku[x][col]->solvable--;
                }
                sudoku[x][col]->possible[digit-1] = 1;
            }

            //loop through column
            for(x=0; x<SIZE_COLUMNS; x++){
                if(sudoku[row][x]->possible[digit-1] == 0){
                    sudoku[row][x]->solvable--;
                }
                sudoku[row][x]->possible[digit-1] = 1;
            }

    return 1;
}

int checkPuzzle(Square*** sudoku, Box ** boxes){
    int i,j, x;

    for(i=0; i<SIZE_ROWS; i++){
        for(j=0; j<SIZE_COLUMNS; j++){
            if(sudoku[i][j]->solvable == 1){
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
            }
        }
    }

    boxSingles(sudoku, boxes);

    return 1;
}



int ** createPuzzle(){
    int ** puzzle;
    int i,j;
    int array[9][9] = {
        {0,1,9,0,0,2,0,0,0},
        {4,7,0,6,9,0,0,0,1},
        {0,0,0,4,0,0,0,9,0},
        {8,9,4,5,0,7,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,2,0,1,9,5,8},
        {0,5,0,0,0,6,0,0,0},
        {6,0,0,0,2,8,0,7,9},
        {0,0,0,1,0,0,8,6,0}
    };

    puzzle = (int **)malloc(sizeof(int*)*9);

    for(int i=0; i<9; i++){
        puzzle[i] = (int*)malloc(sizeof(int)*9);

        for(int j=0; j<9; j++){
            puzzle[i][j] = array[i][j];
        }

    }

    return puzzle;
}

void freePuzzle(int **puzzle) {
    // Free each row
    for (int i = 0; i < 9; i++) {
        free(puzzle[i]);
    }
    // Free the array of pointers
    free(puzzle);

    // Optional: Set the pointer to NULL to avoid dangling pointers
    puzzle = NULL;
}

void printPuzzle(int **puzzle){

    printf("-------------------------------\n");
    for(int i=0; i<9; i++){
        printf("|");
        for(int j=0; j<9; j++){
            printf(" %d ",puzzle[i][j]);

            if((j+1) % 3 == 0){
                printf("|");
            }
        }
        printf("\n");
        if((i + 1) % 3 == 0){
            printf("-------------------------------\n");
        }
    }
}

void freeSpace(Square ***sudoku){
    int i, j;

    //free each square
    for(i=0; i<9; i++){
        for(j=0; j<9; j++){
            free(sudoku[i][j]);
        }
    }

    //free row
    for(i=0; i<9; i++){
        free(sudoku[i]);
    }

    //free sudoku
    free(sudoku);
}