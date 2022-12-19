#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
	int a = 0, b = 0, c = 0;

	for (int i = 0; i < 10000000; ++i)
	{
		if ((i % 5) == 0) a = 2;
		else a = 0;
		if ((i % 4) == 0) b = 2;
		else b = 0;
		if ((a * b) == 1) c = 1; // spy branch
	}

	// it is necessary that during optimization
	// it is not deleted as unused variable
	if (a == 12345) printf("Wow");
	if (b == 12345) printf("Wow");
	if (c == 12345) printf("Wow");

	return EXIT_SUCCESS;
}