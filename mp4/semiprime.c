#include <stdlib.h>
#include <stdio.h>

/* 
partners: vprasad3, ajaggi3
The first error that we encountered and fixed was fixing the missing semi-colon in main.c
Next, we flipped the return values in the function is_prime(), so that if the number is prime,
the function will return the value 1. We then added a variable called check under the function
print_semiprimes to make sure none of the semiprimes are double counted. Before the second
for loop, we initialized check as a local variable, ensuring that check is always set to 0 while 
checking for prime divisors. Once getting into the first for loop, we checked if check was equal
to 0. We then changed the % to a / on line in the second if-loop. This is because if 
the j is a prime divisor of i, then we want to divide i by j and check if the second divisor is
also a prime number. If it is, then the number is a semiprime, and we change the value of return
to 1. Else, if we never print, we never change the value of ret from 0, and we also don't count 
doubles.
*/






/*
 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { /*for each number smaller than it */
        if (number % i == 0) { 				/*check if the remainder is 0 */
            return 0;	       				/*if the number is divisble by any number between 2 and itself - 1, the number is not prime and the function should return 0*/
        }
    }
    return 1;		       				/*if the number is prime, the function should return 1*/
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
	int check = 0;					/*set check to 0 at the before checking each number between a to b to be a semiprime*/
        for (j = 2; j <= i; j++) {
            if (i%j == 0 && check == 0) { 		/*make sure that check is 0, so that we don't double count semiprimes between a and b*/
                if (is_prime(j)) { 
                    k = i/j;				/*if the first number is prime, divide original number by prime number, and then check second number*/
                    if (is_prime(k)) {
                        printf("%d ", i);
			check = 1;			/*we want to check for double counting of semiprimes*/
			ret = 1;			/*we return 1 if there is a semiprime in [a,b]*/
                    }
                }
            }
        }

    }
    printf("\n");
    return ret;

}
