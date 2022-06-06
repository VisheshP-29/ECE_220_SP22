#include <stdio.h>
#include <stdlib.h>


/*
partners: ajaggi3, vprasad3
We started out by defining our variables, using an unsigned long integer for the row (provided by the user).
We also defined a variable, coef (coefficient) to update and print the coefficients in Pascal's triangle.
We then prompted the user to enter a row index, which we immediately moved to a variable called row.
We set variable i = to row, and then used a for loop. If both j and  i (our variables n and k from the mp page)
were 0, the output is just 1, which we accounted for using our first if statement. If this is not the case,
then we implement the equation given in the mp. The combination of row and binomial coefficient. To do this
we kept a variable coefficient (to be printed), and for every different coefficient, we multiplied the previous
coeffient by (i + 1 -j)/j (which came straight from the equation provided to us.
*/

int main()
{

   unsigned long int row, coef = 1, i, j;				/*initialize variables as unsigned long integers, set coefficient to 1*/
   printf("Enter a row index: ");					/*ask user for row input*/
   scanf("%ld", &row);							/*store input into variable called row*/
   i = row;								/*store row in variable called i*/
   for (j = 0; j <= i; j++) {						/*start for loop to print values, as long as j is less than or equal to row*/
        if (j == 0 || i == 0)						/*check if the row asked for is 0*/
            coef = 1;							/*print 1 if it is*/
       	else								/*otherwise, move on*/
            coef = coef * (i + 1 - j) / j;				/*calculate coefficient using equation provided*/
         printf("%ld ", coef);						/*print coefficient*/
   }									/*go back to for loop*/
   printf("\n");     

  return 0;								/*return 0, terminate code*/
}
