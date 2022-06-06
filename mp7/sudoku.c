#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7

// Introductory Paragraph
/* partners: ajaggi3, vprasad3
We first started by completing functions is_val_in_row, and is_val_in_col, where we checked if a given number (val)
was in the row, or column that we desired to check (given by i and j respectively). Next we checked if the number
was in the 3x3 box. To do this, we first split the 9x9 grid in to 3x3 blocks, and started with the top left corner.
Then we checked if the val was valid in the position. To do this, it must not be in the column, row, or box. Therefore
we simply checked to make sure that all three previously written functions returned false for the given number. We then
created a new function, where we checked to see if every box on the board was filled. If it was, then the function returned true.
Finally, to solve the sudoku, we first checked if the board was filled. If a certain position wasn't filled, we went through
every number 1 to 9, checking to see if the number fit by calling the previously written functions. If the number worked
we checked to see if the whole board was solved. If not, the solve_sudoku function ran again, until every box was filled
correctly.
*/
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  int col; 									//create variable col to iterate through the columns on row i
  for(col = 0; col < 9; col ++){						//return 1 if val is in the row
  	if(val == sudoku[i][col]){						
		return 1;	
	}
  }
  	
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  int row; 									//create variable row to iterate through the rows on column j
  for(row = 0; row < 9; row ++){						//return 1 if val is in the column
  	if(val == sudoku[row][j]){
		return 1;	
	}
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  int row;									//variable to iterate through rows
  int col;									//variable to iterate through columns
  int beginningrow = 3 * int(i/3);						//divide board into 9 3x3 blocks
  int beginningcol = 3 * int(j/3);						//start from top left corner of each block
  for(row = beginningrow; row <= beginningrow + 2; row ++){			//if val is in the block, return 1
    for(col = beginningcol; col <= beginningcol + 2; col ++){
	if(val == sudoku[row][col]){
	  return 1;
  	}
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);
  if((is_val_in_row(val, i, sudoku) == 1) || (is_val_in_col(val, j, sudoku) == 1) || (is_val_in_3x3_zone(val, i, j, sudoku) == 1)){
    return 0;               							//simply combine three functions
  }
  return 1;
  // END TODO
}

// Private Function: filled
// return true if all cells are filled
int filled(int sudoku[9][9]){							//pass array
  int i, j;
  for (i = 0; i <= 8; i++){							//if any position is 0, it's unfilled, and the code should return false
    for (j = 0; j <= 8; j++){
      if (sudoku[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}



// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  int i, j, row, col, num;
  if (filled(sudoku) == 1){							//first check if every position in the sudoku is filled
    return 1;
  }
  else{										//if any position isn't filled, it needs to be filled before we can solve the sudoku
    for(i = 0; i < 9; i ++){
	for(j = 0; j < 9; j ++){						//for loops to iterate through array
 	  if(sudoku[i][j] == 0){						//find unfilled locations
	    row = i;								//note down row position
	    col = j;								//note down column position
	    i = 9;								//break outer loop
	    j = 9;								//break inner loop
	  }
	}
    }
  }
  for (num = 1; num < 10; num ++){						//test every number from 1 to 9
    if(is_val_valid(num, row, col, sudoku) == 1){				//to see if it works with in the given position
	sudoku[row][col] = num;							//if it does, set it
    	if (solve_sudoku(sudoku) == 1){						//check if board is solved
	  return 1;
    	}
    	sudoku[row][col] = 0;							//if the number doesn't work, leave position unfilled
    }
  }
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





