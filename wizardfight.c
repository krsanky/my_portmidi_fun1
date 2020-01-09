#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "mycur.h"


int
main()
{
	mycur_init();

	move(2, 2);
	printw("Wizard Fight!");
	refresh();

	usleep(1000000);
	endwin();
	return EXIT_SUCCESS;
}
