/*
 * partners: vprasad3, ajaggi3
 * For this mp, we implemented countLiveNeighbor, updateBoard, and aliveStable in updateBoard.c.
 * To implement countLiveNeighbor, we had to check all the cells around the given cell and count up the number 
 * of live neighbors, not including the given cell. We started from the previous row and coloumn and went to the
 * next row and coloumn of the given cell. We also had to make sure that the row and coloumn counters are inside
 * the bounds. We then returned the number of alive neighbors. To implement updateBoard, we first copied the
 * original array into a temporary array. We then went through each cell in the original board and based on the 
 * number of alive cells, we updated the temporary board with the new values. We finally copied the values from
 * the temporary array back into the original array. Finally, to implement aliveStable, we went through every cell in the
 * original board and called countLiveNeighbor to count the number of alive neighbors. We then went through the same 
 * logic from updateBoard, and decided if the board would have to be updated or not. If the board has to be updated, it
 * is not stable and the function returns a 0, and if the board is stable then aliveStable returns 1.
 */







/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
  int numAlive = 0;     //decleration and initialization of variable to hold number of alive neighbors
  int i, j;     //declare and initialize variables to count loops
  for (i = row - 1; i <= row + 1; i++)     //row loop counter from row - 1 to row + 1
  {
    if ((i >= 0) && (i < boardRowSize))     //check if row counter is inside bounds
    {
      for (j = col - 1; j <= col + 1; j++)     //column counter from coloumn -1 to coloumn +1
      {
	if ((j >= 0) && (j < boardColSize))     //check if column counter is inside bounds
	{
	  if ((i != row) || (j != col))     //check if row and column counter isn't at current row and column
	  {
	    numAlive = numAlive + board[(i * boardColSize) + j];      //increment number of live neighbors
	  }
	}
      }
    }
  }
  return numAlive;     //return number of alive neighbors
}


/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int size = boardRowSize * boardColSize;     //calculate size of board array
  int tempArray[size];     //declare temp array of same size as board array
  int i, j;     //declare loop variables
  for (i = 0; i < size; i++)     //loop through all of board array
  {
    tempArray[i] = board[i];     //store board values into temp array
  }
  for (i = 0; i < boardRowSize; i++)     //row loop counter
  {
    for (j = 0; j < boardColSize; j++)     //column loop counter
    {
      int alive = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);     //get number of alive neighbors by calling countLiveNeighbor
      int spot = (i * boardColSize) + j;     //calculate spot in array using row and counter variables
      int check = board[spot];     //check current status of cell
      if (check == 1)     //if current cell is alive
      {
	if ((alive < 2) || (alive > 3))     //if alive neighbors are < 2 or > 3
	{
	  tempArray[spot] = 0;     //current cell in tempArray dies
	}
	if ((alive == 2) || (alive == 3))     //if alive neighbors equal 2 or 3
	{
	  tempArray[spot] = 1;     //current cell in tempArray lives
	}
      }
      if (check == 0)     //if current cell is dead
      {
	if (alive == 3)     //if alive neighbors equals 3
	{
	  tempArray[spot] = 1;     //current cell in tempArray lives
	}
	else
	{
	  tempArray[spot] = 0;     //current cell in tempArray dies
	}
      }
    }
  }
  for (i = 0; i < size; i++)     //loop to go through all of board array
  {
    board[i] = tempArray[i];     //update actual board array with temp array values
  }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
  int checkStable = 1;     //declare and initialize variable to check if board is stable
  int i, j;     //declare loop variables
  for (i = 0; (checkStable == 1) && (i < boardRowSize); i++)     //row loop variable, continues only if board is still stable
  {
    for (j = 0; (checkStable == 1) && (j < boardColSize); j++)     //column loop variable, continues only if board is till stable
    {
      int spot = (i * boardColSize) + j;     //calculate index for current cell in board
      int alive = countLiveNeighbor(board, boardRowSize, boardColSize, i, j);     //get number of alive neighbors by calling countLiveNeighbor
      int check = board[spot];     //get value of cell at current spot
      if (check == 1)     //if current cell is alive
      {
	if ((alive < 2) || (alive > 3))     //if alive nieghbors is < 2 or > 3, cell dies
	{
	  checkStable = 0;     //board not stable anymore
	}
      }
      if (check == 0)     //if current cell is dead
      {
	if (alive == 3)     //if alive nieghbors equals 3, cell lives
	{
	  checkStable = 0;     //board not stable anymore
	}
      }
    }
  }
  return checkStable;     //return if board is stable or not
}

				
				
			

