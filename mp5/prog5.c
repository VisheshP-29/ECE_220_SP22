/*			
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 */


/*
 * partners: ajaggi3, vprasad3
 * We first implemented the functions set_seed, start_game, and make_guess. For set_seed, we first created an array (post), to grab integers
 * from the string that the user provides us. We ensured that exactly one integer is passed, and invalidated any thing after receiving one integer.
 * In the function start game, we initialized the solution array, with 4 random integers between the numbers 1 and 8. We also updated guess_number
 * to be 1. Finally, in the function make_guess, we first used sscanf to make sure we received 4 integers from the user, and invalidated any other
 * inputs they gave us. We stored these values in an array, and ensured that they were within the bounds 1 and 8, else we printed back an error. 
 * Next, we created two arrays, filled with 0's initially (paired and paired2), which we used to help track perfect and misplaced matches. In the
 * second for loop of the function, we checked if the any of the users numbers were the same and in the same position as the solution. If we found
 * a match, we updated that index in paired and paired 2 to invalidate further guesses there, and also incremented the perfect matches count. 
 * Finally, in the nested for loop, we then checked the guess against each value of the solution, and if we found a match (can't be perfect match 
 * as described above), then we incremented the mismatched count.  
*/


#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"


/*
 * You will need to keep track of the solution code using file scope
 * variables as well as the guess number.
 */

static int guess_number;
static int solution[4]; //we initalize an array to hold the solution


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[])
{
	int seed;
	char post[2];
	if (sscanf(seed_str, "%d%1s", &seed, post) == 1){       //ensure the input is just one integer 
		srand(seed);		
		return 1;				        //return 1 if successful
	}	
	else{
	  printf("set_seed: invalid seed\n");           	//if unsuccessful, return 0 and print "set_seed: invalid seed"	
		return 0;
	}


	
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
  
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */

void
start_game (int* one, int* two, int* three, int* four)
{
	solution[0] = *one = (rand()%8)+1;                      //set first number of solution to a random number between 1 and 8
    	solution[1] = *two = (rand()%8)+1;                      //set second number of solution to a random number between 1 and 8
    	solution[2] = *three = (rand()%8)+1;                    //set third number of solution to a random number between 1 and 8
    	solution[3] = *four = (rand()%8)+1;                     //set fourth number of solution to a random number between 1 and 8

    	guess_number = 1; 		                        //set the guess number to 1
   //your code here
    
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, 
	    int* three, int* four)
{
//  One thing you will need to read four integers from the string guess_str, using a process
//  similar to set_seed
//  The statement, given char post[2]; and four integers w,x,y,z,
//  sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post)
//  will read four integers from guess_str into the integers and read anything else present into post
//  The return value of sscanf indicates the number of items sucessfully read from the string.
//  You should check that exactly four integers were sucessfully read.
//  You should then check if the 4 integers are between 1-8. If so, it is a valid guess
//  Otherwise, it is invalid.  
//  Feel free to use this sscanf statement, delete these comments, and modify the return statement as needed
    char post[2];
    int w,x,y,z;
    int guess[4];
    int result = sscanf (guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post); //ensure that we receive four numbers, put them into variables w, x, y, z
    if(result == 4) {							  //if successful, continue with code, otherwise terminate
        guess[0] = w;							  //set first number of guess array to w	
        guess[1] = x;							  //set second number of guess array to x
        guess[2] = y;							  //set third number of guess array to y
        guess[3] = z;    						  //set fourth number of guess array to z
        if((w <= 8) && (w>=1) && (x>=1) && (x <= 8) && (y>=1) && ( y <= 8) &&(z>=1) && ( z <= 8)) {
            *one = w;							  //if w, x, y, z are within bounds [1,8], set pointer one to w
            *two = x;							  //set pointer two to x	
            *three = y;							  //set pointer three to y
            *four = z;							  //set pointer four to z

            int paired[4];						  //initialize paired array
	    int paired2[4]; 						  //initialize paired2 array
	    for(int fill=0; fill < 4; fill ++){				  //for loop to fill both arrays with 0
		paired[fill] = 0;
		paired2[fill] = 0;
		}

	    
            int matches = 0;						  //create variable to track perfect matches
            int misplaced = 0;						  //create variables to track misplaced matches
           
            
            int i;
            for (i=0; i<4; i++) {					  //for loop to check solution and guess
                if (guess[i] == solution[i]) {				  //loop through guess and solution simultaneously, and if the numbers match, move on
                    matches++;						  //if the numbers match, increment perfect matches count
                    paired[i] = 1;					  //set appropriate index of paired and paired2 to 1
		    paired2[i] = 1;
                    
                }
            }
           
            int j;
            for (i=0; i<4; i++) {
                for (j=0; j<4; j++) {
                    if (paired[i] != 1 && guess[i] == solution[j] && paired2[j] != 1) { //if paired and paired 2, not equal to 1, and the guess is somewhere in solution
                        misplaced++;							//this means the gues is in the solution, just not in the right spot
			paired2[j] = 1;							//increment misplaced matches count
                        paired[i] = 1;							//set appropriate indexes of paired and paired 2 to 1
                        
                    }
                }
            }            

            printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, matches, misplaced);
            guess_number++;
        } else {
            printf("make_guess: invalid guess\n");
            return 0;
        }
    } else {
        printf("make_guess: invalid guess\n");
        return 0;
    }
    return 1;
}


