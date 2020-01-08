#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

/*
 *               The screen (stdscr)
 * (0,0)*----------------------------------* (0, COLS-1)
 *         |                                  |
 *         |                                  |
 *         |    (y0,x0)                       |
 *         |      ---------------             |
 *         |      |             |             |
 *         |      |             |             |
 *         |      |     win     |nlines       |
 *         |      |             |             |
 *         |      |             |             |
 *         |      |             |             |
 *         |      ---------------             |
 *         |          ncols                   |
 *         |                                  |
 *         *----------------------------------*
 * (LINES-1, 0)                              (LINES-1, COLS-1)
 */

void
main_stuff()
{
	int 		max_x    , max_y;

	getmaxyx(stdscr, max_y, max_x);

	refresh();
	sleep(2);

	int 		x        , y = 0;
	for (x = 0; x < max_x; x++) {
		mvaddch(y, x, '*');
		y += 1;
		usleep(1000);
		refresh();
	}
}

int
main()
{
	int 		ch;
	int 		height   , width;
	int 		starty   , startx;

	height = 3;
	width = 10;

	starty = (LINES - height) / 2;
	startx = (COLS - width) / 2;

	initscr();
	cbreak();
	noecho();
	/* Most programs would additionally use the sequence: */
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);


	printw("123........\n");
	refresh();

	while ((ch = getch())) {
		switch (ch) {
		case 'q':
			goto end;
			break;
		}
	}

	main_stuff();

end:
	endwin();
	return EXIT_SUCCESS;
}
