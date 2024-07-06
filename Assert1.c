/*   Assert.c

     use asserts     within a trivial program
     John Programmer
     July  6 , 2024
*/

#define NDEBUG	//goes before <assert.h>
#include <assert.h>
#include <stdio.h>
#include <ctype.h>

int main()
{
	assert(0);
	printf("My program runs\n");
	return 0;
}
