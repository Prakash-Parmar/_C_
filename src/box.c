#include "sudoku.h"

Box ** createBoxes(){
    
    Box ** boxes;
    int x, y;

    boxes = (Box **)malloc(sizeof(Box *)*9);

    for(x=0; x<9; x++){
        boxes[x] = (Box *)malloc(sizeof(Box));
        boxes[x]->squares = malloc(sizeof(Square *) * 9);
        boxes[x]->numbers = 0;
        boxes[x]->solvable = 9;

        for(y=0; y<9; y++){
            boxes[x]->possible[y] = 0;
        }
    }

    return boxes;
}

int updateBoxes(Square *** sudoku, int row, int col){

    int i;
    int number = sudoku[row][col]->number;
    Box * box = sudoku[row][col]->box;

    for(i=0; i<9; i++){
        if(box->squares[i]->possible[number-1] == 0){
            box->squares[i]->solvable--;
            box->squares[i]->possible[number - 1] = 1;
        }
    }
}

int boxSingles(Square *** sudoku, Box ** boxes){
    int i,j,k;
    int count;
    int temp;

    //loop through boxes
    for(i=0; i<9; i++){
        //loop through possible array
        for(j=0; j<9; j++){
            count = 0;
            //loop through squares
            for(k=0; k<9; k++){
                if(boxes[i]->squares[k]->number != 0)
                    continue;
                if(boxes[i]->squares[k]->possible[j] == 0){
                    count++;
                    temp = k;
                }
                if(count == 1)
                    break;
            }

            if(count == 1){
                boxes[i]->squares[temp]->number = j + 1;
                UNSOLVED--;
                boxes[i]->squares[temp]->solvable = 0;
                updateBoxes(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->column);
            }
        }
    }
}