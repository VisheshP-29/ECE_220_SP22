#include "game.h"


/* Intro Paragraph:
partners: ajaggi3, vprasad3
This program works to create a working 2048 game. We started by intializing all the variables in the game struct, and intializing all cell values to -1.
We then completed the remake game function, where we reinitalize the rows and columns to the rows and columns provided to us. We also set the score to 0,
and initalized all cell values to -1 again. We then moved on to the get cell function, where we first checked that the given row and column are within the
bounds of our game, and if they were, then we returned the corresponding row column pointer pointing to the cell requested.Then we created the movement functions.
We basically traversed the width and height (depending on function), found an empty target cell to move to, and then moved all the necessary cells into the direction
specified (w,a,s,d). We also returned a variable 'moved' to determine whether or not the cells moved. Additionally, we merged any cells that could have been merged.
After we moved, we checked if the row/column before the one we are currently checking was merged. If it was then we don't want to double merge. If it isn't then we check if it has the same value as the cell we are currently on. If it does, then we double the value of the current cell, and make the other cell -1 (empty).We then implmented the legal move function, where we checked for legal moves. If any adjacent cell to the current cell (left, right, up, down) wasn't null, and the corresponding cell had a value, then it was a legal move. Additionally, if the cell is empty, then it is a legal move. Else, it's illegal and we return 0.
*/





game * make_game(int rows, int cols)
/*! Create an instance of a game structure with the given number of rows
    and columns, initializing elements to -1 and return a pointer
    to it. (See game.h for the specification for the game data structure) 
    The needed memory should be dynamically allocated with the malloc family
    of functions.
*/
{
    //Dynamically allocate memory for game and cells (DO NOT modify this)
    game * mygame = malloc(sizeof(game));
    mygame->cells = malloc(rows*cols*sizeof(cell));

    //YOUR CODE STARTS HERE:  Initialize all other variables in game struct
    mygame->rows = rows;						//access struct member using pointer
    mygame->cols = cols;						//access struct member using pointer
    mygame->score = 0;							//access struct member using pointer
    for (int i = 0; i < rows * cols; i ++) {				//quick for loop to intialize all cell values to -1
        mygame->cells[i] = -1;
    }


    return mygame;
}

void remake_game(game ** _cur_game_ptr,int new_rows,int new_cols)
/*! Given a game structure that is passed by reference, change the
	game structure to have the given number of rows and columns. Initialize
	the score and all elements in the cells to -1. Make sure that any 
	memory previously allocated is not lost in this function.	
*/
{
	/*Frees dynamically allocated memory used by cells in previous game,
	 then dynamically allocates memory for cells in new game.  DO NOT MODIFY.*/
	free((*_cur_game_ptr)->cells);
	(*_cur_game_ptr)->cells = malloc(new_rows*new_cols*sizeof(cell));

	 //YOUR CODE STARTS HERE:  Re-initialize all other variables in game struct
	(*_cur_game_ptr)->rows = new_rows;					//set struct rows in our current game pointer to the new rows variable provided
        (*_cur_game_ptr)->cols = new_cols;					//set struct columns in our current game pointer to the new columns variable provided
        (*_cur_game_ptr)->score = 0;						//set score to 0
        for (int i = 0; i < new_rows * new_cols; i ++) {			//quick for loop to set all cells to -1
        	(*_cur_game_ptr)->cells[i] = -1;
    	}

	return;	
}

void destroy_game(game * cur_game)
/*! Deallocate any memory acquired with malloc associated with the given game instance.
    This includes any substructures the game data structure contains. Do not modify this function.*/
{
    free(cur_game->cells);
    free(cur_game);
    cur_game = NULL;
    return;
}

cell * get_cell(game * cur_game, int row, int col)
/*! Given a game, a row, and a column, return a pointer to the corresponding
    cell on the game. (See game.h for game data structure specification)
    This function should be handy for accessing game cells. Return NULL
	if the row and col coordinates do not exist.
*/
{
    //YOUR CODE STARTS HERE
    if(row <0 || row >= cur_game-> rows || col < 0 || col >= cur_game->cols)		
	return NULL;

    return (cur_game -> cells) + (row * cur_game ->cols) + col; 			//first, I access the cells of the game given, multiply it by row, and sum both 											//with the column coordinate to create a pointer to the current location
    
}

int move_w(game * cur_game)
/*!Slides all of the tiles in cur_game upwards. If a tile matches with the 
   one above it, the tiles are merged by adding their values together. When
   tiles merge, increase the score by the value of the new tile. A tile can 
   not merge twice in one turn. If sliding the tiles up does not cause any 
   cell to change value, w is an invalid move and return 0. Otherwise, return 1. 
*/

{
    int width = cur_game->cols;         // get the width
    int height = cur_game->rows;        // get the height

    int moved = 0;              // variable to check if the cell moved

    for (int x = 0; x < width; x ++) {				    // for loop to traverse the width
        int last_combined_row = -1;                                 // at the start of the loop, reset the last combined row to -1
        for (int y = 0; y < height; y ++) {                         // for loop to traverse the height
            cell* current_cell = get_cell(cur_game, y, x);          // Save the address of the current cell 
            if (*current_cell == -1) {                              // if the cell is empty, skip next code 
                continue;
            } else {
                int target = y;                                     // We want to slide into the target cell, which will be y to start
                for (int i = 0; i < y; i ++) {                      // for loop from i to y
                    cell* check_cell = get_cell(cur_game, i, x);    // get address of target cell
                    if (*check_cell == -1) {                        // check if target cell is empty
                        *check_cell = *current_cell;                // if it is, move current cell value into check cell
                        *current_cell = -1;                         // reset the current cell value to -1
                        target = i;				    // check for a merge
                        moved = 1;                          	    // the cell moved, so set moved to 1
                        break;
                    }
                }

                if (target - 1 != last_combined_row) {                      // check if the cell before the target cell was merged
                    cell* cell_above = get_cell(cur_game, target-1, x);     // if it isn't we can possibly merge
                    cell* target_cell = get_cell(cur_game, target, x);      // Save these two addresses 
                    if (*cell_above == *target_cell) {                      // check if the two cells are equal
                        *cell_above *= 2;                                   // if the two cells are equal, double the value of the cell above 
                        *target_cell = -1;                                  // reset the target cell, it's been merged
                        last_combined_row = target + 1;                     // now we update the last combined row
                        cur_game->score += *cell_above;                     // add cell value to total score
                        moved = 1;                                          // the cell moved, so set moved to 1
                    }
                } 
            } 
        } 
    } 

    return moved;
};
    //YOUR CODE STARTS HERE


int move_s(game * cur_game) //slide down
{
    int width = cur_game->cols;         // get the width
    int height = cur_game->rows;        // get the height

    int moved = 0;              // variable to check if the cell moved

    for (int x = 0; x < width; x ++) {				    // for loop to traverse the width
        int last_combined_row = height;                             // at the start of the loop, reset the last combined row to height
        for (int y = height - 1; y >= 0; y --) {                    // for loop starting at the top, going down the rows
            cell* current_cell = get_cell(cur_game, y, x);          // Save the address of the current cell 
            if (*current_cell == -1) {                              // if the cell is empty, skip next code 
                continue;
            } else {
                int target = y;                                     // We want to slide into the target cell, which will be y to start
                for (int i = height -1 ; i > y; i --) {             // quick for loop
                    cell* check_cell = get_cell(cur_game, i, x);    // get address of target cell
                    if (*check_cell == -1) {                        // check if target cell is empty
                        *check_cell = *current_cell;                // if it is, move current cell value into check cell
                        *current_cell = -1;                         // reset the current cell value to -1
                        target = i;				    // check for a merge
                        moved = 1;                          	    // the cell moved, so set moved to 1
                        break;
                    }
                }

                if (target + 1 != last_combined_row) {                      // check if the cell before the target cell was merged
                    cell* cell_below = get_cell(cur_game, target+1, x);    // if it isn't we can possibly merge
                    cell* target_cell = get_cell(cur_game, target, x);      // Save these two addresses 
                    if (*cell_below == *target_cell) {                     // check if the two cells are equal
                        *cell_below *= 2;                                  // if the two cells are equal, double the value of the cell above 
                        *target_cell = -1;                                  // reset the target cell, it's been merged
                        last_combined_row = target + 1;                     // now we update the last combined row
                        cur_game->score += *cell_below;                    // add cell value to total score
                        moved = 1;                                          // the cell moved, so set moved to 1
                    }
                } 
            } 
        } 
    } 

    return moved;
};

int move_a(game * cur_game) //slide left
{
    int width = cur_game->cols;         // get the width
    int height = cur_game->rows;        // get the height

    int moved = 0;              // variable to check if the cell moved

    for (int y = 0; y < height; y ++) {				    // for loop to traverse the height
        int last_combined_col = -1;                                 // at the start of the loop, reset the last combined col to -1
        for (int x = 0; x < width; x ++) {                         // for loop to traverse the width
            cell* current_cell = get_cell(cur_game, y, x);          // Save the address of the current cell 
            if (*current_cell == -1) {                              // if the cell is empty, skip next code 
                continue;
            } else {
                int target = x;                                     // We want to slide into the target cell, which will be x to start
                for (int i = 0; i < x; i ++) {                      // for loop from i to x
                    cell* check_cell = get_cell(cur_game, y, i);    // get address of target cell
                    if (*check_cell == -1) {                        // check if target cell is empty
                        *check_cell = *current_cell;                // if it is, move current cell value into check cell
                        *current_cell = -1;                         // reset the current cell value to -1
                        target = i;				    // check for a merge
                        moved = 1;                          	    // the cell moved, so set moved to 1
                        break;
                    }
                }

                if (target - 1 != last_combined_col) {                      // check if the cell before the target cell was merged
                    cell* cell_left = get_cell(cur_game, y, target-1);     // if it isn't we can possibly merge
                    cell* target_cell = get_cell(cur_game, y, target);      // Save these two addresses 
                    if (*cell_left == *target_cell) {                      // check if the two cells are equal
                        *cell_left *= 2;                                   // if the two cells are equal, double the value of the cell to the left 
                        *target_cell = -1;                                  // reset the target cell, it's been merged
                        last_combined_col = target + 1;                     // now we update the last combined col
                        cur_game->score += *cell_left;                     // add cell value to total score
                        moved = 1;                                          // the cell moved, so set moved to 1
                    }
                } 
            } 
        } 
    } 

    return moved;
};

int move_d(game * cur_game)
{
    int width = cur_game->cols;         // get the width
    int height = cur_game->rows;        // get the height

    int moved = 0;              // variable to check if the cell moved

    for (int y = 0; y < height; y ++) {				    // for loop to traverse the height
        int last_combined_col = width;                             // at the start of the loop, reset the last combined column to width
        for (int x = width - 1; x >= 0; x --) {                    // for loop starting at the top, going down the columns
            cell* current_cell = get_cell(cur_game, y, x);          // Save the address of the current cell 
            if (*current_cell == -1) {                              // if the cell is empty, skip next code 
                continue;
            } else {
                int target = x;                                     // We want to slide into the target cell, which will be x to start
                for (int i = width -1 ; i > x; i --) {             // quick for loop
                    cell* check_cell = get_cell(cur_game, y, i);    // get address of target cell
                    if (*check_cell == -1) {                        // check if target cell is empty
                        *check_cell = *current_cell;                // if it is, move current cell value into check cell
                        *current_cell = -1;                         // reset the current cell value to -1
                        target = i;				    // check for a merge
                        moved = 1;                          	    // the cell moved, so set moved to 1
                        break;
                    }
                }

                if (target + 1 != last_combined_col) {                      // check if the cell before the target cell was merged
                    cell* cell_right = get_cell(cur_game, y, target+1);    // if it isn't we can possibly merge
                    cell* target_cell = get_cell(cur_game, y, target);      // Save these two addresses 
                    if (*cell_right == *target_cell) {                     // check if the two cells are equal
                        *cell_right *= 2;                                  // if the two cells are equal, double the value of the cell to the right 
                        *target_cell = -1;                                  // reset the target cell, it's been merged
                        last_combined_col = target + 1;                     // now we update the last combined col
                        cur_game->score += *cell_right;                    // add cell value to total score
                        moved = 1;                                          // the cell moved, so set moved to 1
                    }
                } 
            } 
        } 
    } 

    return moved;
};


int legal_move_check(game * cur_game)
/*! Given the current game check if there are any legal moves on the board. There are
    no legal moves if sliding in any direction will not cause the game to change.
	Return 1 if there are possible legal moves, 0 if there are none.
 */
{
    int width = cur_game->cols;         // get width
    int height = cur_game->rows;        // get height

    for (int y = 0; y < height; y ++) {
        for (int x = 0; x < width; x ++) {
            int value = *get_cell(cur_game, y, x);  // store the current cell's value for comparison

            							// if the current cell is empty, move is legal
            if (value == -1) {
                return 1;
            }


            cell* left  = get_cell(cur_game, y, x - 1);     // get address of left cell
            cell* right = get_cell(cur_game, y, x + 1);     // get address of right cell
            cell* up    = get_cell(cur_game, y - 1, x);     // get address of cell above
            cell* down  = get_cell(cur_game, y + 1, x);	    // get address of cell below

            if (left != NULL && *left == value) {           // if left isn't null, and it matches the value, it's a legal move
                return 1;
            }
            if (right != NULL && *right == value) {         // if right isn't null, and it matches the value, it's a legal move
                return 1;
            }
            if (up != NULL && *up == value) {               // if up isn't null, and it matches the value, it's a legal move
                return 1;
            }
            if (down != NULL && *down == value) {           // if down isn't null, and it matches the value, it's a legal move
                return 1;
            }
        }
    }
    return 0;   // return 0 if there are no legal moves remaining
}


/*! code below is provided and should not be changed */

void rand_new_tile(game * cur_game)
/*! insert a new tile into a random empty cell. First call rand()%(rows*cols) to get a random value between 0 and (rows*cols)-1.
*/
{
	
	cell * cell_ptr;
    cell_ptr = 	cur_game->cells;
	
    if (cell_ptr == NULL){ 	
        printf("Bad Cell Pointer.\n");
        exit(0);
    }
	
	
	//check for an empty cell
	int emptycheck = 0;
	int i;
	
	for(i = 0; i < ((cur_game->rows)*(cur_game->cols)); i++){
		if ((*cell_ptr) == -1){
				emptycheck = 1;
				break;
		}		
        cell_ptr += 1;
	}
	if (emptycheck == 0){
		printf("Error: Trying to insert into no a board with no empty cell. The function rand_new_tile() should only be called after tiles have succesfully moved, meaning there should be at least 1 open spot.\n");
		exit(0);
	}
	
    int ind,row,col;
	int num;
    do{
		ind = rand()%((cur_game->rows)*(cur_game->cols));
		col = ind%(cur_game->cols);
		row = ind/cur_game->cols;
    } while ( *get_cell(cur_game, row, col) != -1);
        //*get_cell(cur_game, row, col) = 2;
	num = rand()%20;
	if(num <= 1){
		*get_cell(cur_game, row, col) = 4; // 1/10th chance
	}
	else{
		*get_cell(cur_game, row, col) = 2;// 9/10th chance
	}
}

int print_game(game * cur_game) 
{
    cell * cell_ptr;
    cell_ptr = 	cur_game->cells;

    int rows = cur_game->rows;
    int cols = cur_game->cols;
    int i,j;
	
	printf("\n\n\nscore:%d\n",cur_game->score); 
	
	
	printf("\u2554"); // topleft box char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // top box char
	printf("\u2557\n"); //top right char 
	
	
    for(i = 0; i < rows; i++){
		printf("\u2551"); // side box char
        for(j = 0; j < cols; j++){
            if ((*cell_ptr) == -1 ) { //print asterisks
                printf(" **  "); 
            }
            else {
                switch( *cell_ptr ){ //print colored text
                    case 2:
                        printf("\x1b[1;31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4:
                        printf("\x1b[1;32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8:
                        printf("\x1b[1;33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 16:
                        printf("\x1b[1;34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 32:
                        printf("\x1b[1;35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 64:
                        printf("\x1b[1;36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 128:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 256:
                        printf("\x1b[32m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 512:
                        printf("\x1b[33m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 1024:
                        printf("\x1b[34m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 2048:
                        printf("\x1b[35m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 4096:
                        printf("\x1b[36m%04d\x1b[0m ",(*cell_ptr));
                        break;
                    case 8192:
                        printf("\x1b[31m%04d\x1b[0m ",(*cell_ptr));
                        break;
					default:
						printf("  X  ");

                }

            }
            cell_ptr++;
        }
	printf("\u2551\n"); //print right wall and newline
    }
	
	printf("\u255A"); // print bottom left char
	for(i = 0; i < cols*5;i++)
		printf("\u2550"); // bottom char
	printf("\u255D\n"); //bottom right char
	
    return 0;
}

int process_turn(const char input_char, game* cur_game) //returns 1 if legal move is possible after input is processed
{ 
	int rows,cols;
	char buf[200];
	char garbage[2];
    int move_success = 0;
	
    switch ( input_char ) {
    case 'w':
        move_success = move_w(cur_game);
        break;
    case 'a':
        move_success = move_a(cur_game);
        break;
    case 's':
        move_success = move_s(cur_game);
        break;
    case 'd':
        move_success = move_d(cur_game);
        break;
    case 'q':
        destroy_game(cur_game);
        printf("\nQuitting..\n");
        return 0;
        break;
	case 'n':
		//get row and col input for new game
		dim_prompt: printf("NEW GAME: Enter dimensions (rows columns):");
		while (NULL == fgets(buf,200,stdin)) {
			printf("\nProgram Terminated.\n");
			return 0;
		}
		
		if (2 != sscanf(buf,"%d%d%1s",&rows,&cols,garbage) ||
		rows < 0 || cols < 0){
			printf("Invalid dimensions.\n");
			goto dim_prompt;
		} 
		
		remake_game(&cur_game,rows,cols);
		
		move_success = 1;
		
    default: //any other input
        printf("Invalid Input. Valid inputs are: w, a, s, d, q, n.\n");
    }

	
	
	
    if(move_success == 1){ //if movement happened, insert new tile and print the game.
         rand_new_tile(cur_game); 
		 print_game(cur_game);
    } 

    if( legal_move_check(cur_game) == 0){  //check if the newly spawned tile results in game over.
        printf("Game Over!\n");
        return 0;
    }
    return 1;
}
