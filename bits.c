#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void  print_bits(int r)
{
	for (int i = 6; i >= 0; i--)
	{
		if (r & (1 << i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int i = 0;
	i |= 4;
	print_bits(i);
	if ((i >> 2) & 1)
		printf("3rd bit set\n");
	i &= ~(1 << 2);
	print_bits(i);
	if ((i >> 2) & 1)
		printf("3rd bit set\n");
	return EXIT_SUCCESS;
}
