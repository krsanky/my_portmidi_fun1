#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "mycur.h"

int
main()
{
	WINDOW         *arena;
	int 		c;

	mycur_init();

	arena = newwin(30, 80, 4, 14);
	if (arena == NULL) {
		move(2, 2);
		printw("ERROR with arena newwin");
	}
	while ((c = getch())) {
		switch (c) {
		case 'q':
			goto end;
		case 'w':
			wborder(arena, 0, 0, 0, 0, 0, 0, 0, 0);
			curs_set(0);
			wrefresh(arena);
			break;
		case 't':
			wmove(arena, 2, 2);
			waddch(arena, 'X');
			waddch(arena, 'X');
			waddch(arena, 'X');
			waddch(arena, 'X');
			waddch(arena, 'X');
			waddch(arena, 'X');
			curs_set(0);
			wrefresh(arena);
			break;
		case 'p':
			move(2, 2);
			printw("Wizard Fight!");
			refresh();

			wmove(arena, 10, 10);
			waddch(arena, 'W');
			wmove(arena, 11, 10);
			waddch(arena, '1');
			wrefresh(arena);

			wmove(arena, 20, 40);
			waddch(arena, 'W');
			wmove(arena, 21, 40);
			waddch(arena, '2');
			curs_set(0);
			wrefresh(arena);
			break;
		case 'c':
			wclear(arena);
			wrefresh(arena);
			break;
		case 'C':
			clear();
			refresh();
			break;
		}
	}

end:
	delwin(arena);
	endwin();
	return EXIT_SUCCESS;
}
