#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <portmidi.h>
#include <porttime.h>

int
main()
{
	printf("clicktrack\n");

	int	i;
	for (i=0; i<9000; i++) {
		usleep(100);
		printf("click - %d\n", i);
	}


	return EXIT_SUCCESS;
}

