/*   math.c

       use asserts within a trivial program
       John Programmer
       July 6, 2024
*/

#include <assert.h>
#include <stdio.h>

int main()
{
	double x , y;
	while(1)
	{
		printf("Read in 2 floats:\n");
		scanf("%lf %lf", &x, &y);
		assert(y != 0);
		printf("when divided x/y = %lf\n", x/y);
	}
	return 0;
}