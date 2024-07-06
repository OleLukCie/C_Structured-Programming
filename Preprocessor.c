/*   Use of Macro`s
      John Programmer
       July  6,  2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEPHANT_SEAL_WT_MALE  8800
#define MIN_ELEPHANT_SEAL_WT_MALE  4400

/*note female range is 880-2000 lbs */

/* produce a macro that randomly generates a male weight */

#define RANGE 4400
#define POPULATION	1000
#define WEIGHT_OVER	rand()% RANGE
#define WEIGHT		WEIGHT_OVER + MIN_ELEPHANT_SEAL_WT_MALE
#define FILL			for ( i = 0; i < POPULATION; i++)   \
					data[i] = WEIGHT
void print_data(int d[], int size)
{
	int i;
	for( i = 0; i < size ; i++){
		printf("%d\t", d[i]);
		if ((i + 1) % 10 == 0)	printf("\n");
	}
}

int main()
{
	int i;
	int data[POPULATION];
	srand(time(0));
	FILL;
	print_data(data, POPULATION);
	printf("\n\n");
	return 0;
}