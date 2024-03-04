#include <iostream>
#include <stdio.h>      /* printf */
#include <math.h>       /* signbit, sqrt */

/*
 * bool signbit (float x);
 * bool signbit (double x);
 * bool signbit (long double x);
 * A non-zero value (true) if the sign of x is negative; and zero (false) otherwise.
 * 负数 return 1, 正数和0 return 0;
 * */

int main()
{
	printf ("signbit(0.0)       : %d\n",signbit(0.0));
	printf ("signbit(1.0)       : %d\n",signbit(1.0));
	printf ("signbit(-1.0/0.0)  : %d\n",signbit(-1.0/0.0));
	printf ("signbit(sqrt(-1.0)): %d\n",signbit(sqrt(-1.0)));
	return 0;
}
