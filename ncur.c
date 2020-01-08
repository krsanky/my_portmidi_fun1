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
	/* noecho(); */
	keypad(stdscr, TRUE);
	/* clear(); */


	printw("123........\n");
	refresh();

	while ((ch = getch()) != KEY_F(1)) {
		switch (ch) {
		case 'q':
			goto end;
			break;
		case KEY_LEFT:
			break;
		case KEY_RIGHT:
			break;
		case KEY_UP:
			break;
		case KEY_DOWN:
			break;
		}
	}

	 main_stuff(); 

end:
	endwin();
	return EXIT_SUCCESS;
}
