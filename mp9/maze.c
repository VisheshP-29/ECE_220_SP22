#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/* 
 * partners: vprasad3, ajaggi3
 * This program works to solve a maze by finding a path from start to end by using a recursive
 * depth-first search. We read in the maze from a text file, and then make and solve the maze.
 * We then print the maze solution and free any memory to prevent memory leaks. Our first function
 * works to create a maze from the fiven text file. In order to accomplish this, we open the file,
 * allocate memory for the maze and read in the rows and columns. We then allocate memory for each row,
 * and then each cell. After all the memory is allocated, we fill the 2D array with the given maze board.
 * The next function that we implemented was destroyMaze, where we free up any memory that we had previously
 * allocated. Our third function was where we printed the maze board to the output screen. Our last function
 * was our depth-first recursive algorithm to solve the maze. Given the original maze board and current 
 * position, the algorithm performs a depth-frist search to find a path to the end, and marks each cell
 * that had been checked as being visited. The function returns 0 if no solution is found, and 1 if
 * any solution is found.
 */




/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
  // Your code here. Make sure to replace following line with your own code.
  int rows, cols;

  FILE *mazeFile = fopen(fileName, "r");     //open file
  fscanf(mazeFile, "%d %d", &rows, &cols);     //read  in rows and columns from file
  maze_t *createdMaze = malloc(sizeof(maze_t));     //allocate memory for maze structure
  createdMaze -> height = rows;     //set maze height
  createdMaze -> width = cols;     //set maze width
  createdMaze -> cells = (char**)malloc(rows * sizeof(char*));     //allocate memory for maze rows
  int i, j;
  for(i = 0; i < rows; i++) {
    createdMaze -> cells[i] = (char*)malloc(cols * sizeof(char*));     //allocate memory for individual cells
  }

  char cell;
  for(i = 0; i < rows; i++) {
    for(j = 0; j < cols; j ++) {
      cell = fgetc(mazeFile);     //read in next character from file
      if(cell != '\n') {     //check if character is not new line character
	createdMaze -> cells[i][j] = cell;     //fill 2D array with read in character
      }
      else {
	j--;     //loop again if new line character found
      }
      if(cell == START) {     //set start row and column if start is found
	createdMaze -> startRow = i;
	createdMaze -> startColumn = j;
      }
      if(cell == END) {     //set end row and column if end if found
	createdMaze -> endRow = i;
	createdMaze -> endColumn = j;
      }
    }
  }
  fclose(mazeFile);     //close file after finished reading it

  return createdMaze;     //return maze read from file
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
  int i;
  for(i = 0; i < maze -> height; i++) {
    free(maze -> cells[i]);     //free allocated memory for each cell
  }
  free(maze -> cells);     //free allocated memory for each row
  free(maze);    //free allocated memory for whole maze structure
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
  int i, j;
  for(i = 0; i < maze-> height; i++) {
    for(j = 0; j < maze -> width; j++) {
      printf("%c", maze -> cells[i][j]);     //print each cell in maze 2D array
    }
    printf("\n");     //print new line character
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.
  int wide, tall;
  char current;

  wide = maze -> width;     //get maze width
  tall = maze -> height;     //get maze height
  current = maze -> cells[row][col];     //get current maze character
  
  if((col < 0) || (col >=  wide) || (row < 0) || (row >= tall)) {     //check if column and row are in bounds of maze
    return 0;
  }

  if((current  == WALL) || (current == PATH) || (current == VISITED)) {     //check if current cell is an empty cell
    return 0;
  }
  
  if(current == END) {     //check if current cell is at the end
    maze -> cells[maze -> startRow][maze -> startColumn] = START;     //reset start cell to be 'S'
    return 1;
  }

  if(current != END) {     //if current cell is not end, set current cell as part of path
    maze -> cells[row][col] = PATH;
  }
  
  if(solveMazeDFS(maze, col - 1, row)) {     //recursively check cell to the left
    return 1;
  }

  if(solveMazeDFS(maze, col + 1, row)) {     //recursively check cell to the right
    return 1;
  }

  if(solveMazeDFS(maze, col, row - 1)) {     //recursively check cell to the top
    return 1;
  }

  if(solveMazeDFS(maze, col, row + 1)) {     //recursively check cell to the bottom
    return 1;
  }

  if(current != END) {
    maze -> cells[row][col] = VISITED;     //if cell is not part of solution, mark it as visited
  }

  return 0;
}
