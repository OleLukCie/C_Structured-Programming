/*  Enumerated Types
      John Coder
      July  5,  2024
*/

#include <stdio.h>

enum day { sun, mon, tue, wed, thu, fri, sat};  // declare type
typedef enum day day;

void print_day(day d)
{
	switch(d){
	case sun: printf(" sunday "); break;
	case mon: printf(" monday "); break;
	case tue: printf(" tuesday "); break;
	case wed: printf(" wednesday "); break;
	case thu: printf(" thursday "); break;
	case fri: printf(" friday "); break;
	case sat: printf(" saturday "); break;
	default: printf("%d is an error", d); 
	}
}
day next_day(day d)
{
	return( d + 1 % 7);
}

int main()
{
	enum day today = fri;
	print_day(today);
	printf("\n\n");
	print_day(7);
	printf("\n\n");
	print_day(next_day(today));
	printf("\n\n");
	return 0;
}