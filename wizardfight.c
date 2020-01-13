#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "wizardfight.h"
#include "mycur.h"

int
main()
{
	WINDOW         *arena, *statw;
	int 		c;
	char		sbuf[128];

	mycur_init();

	statw = newwin(11, 30, 34, 4);
	if (statw == NULL) {
		move(2, 2);
		printw("ERROR with statw newwin");
	}

	arena = newwin(30, 80, 4, 14);
	if (arena == NULL) {
		move(2, 2);
		printw("ERROR with arena newwin");
	}

	while ((c = getch())) {
		box(statw, 0, 0);
		sprintf(sbuf, "<< %c >>", c);
		wf_update_status(statw, sbuf);
		switch (c) {
		case 'h':
			wf_show_help();
			break;
		case 'q':
			goto end;
		case 'w':
			box(arena, 0, 0);
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
			move(1, 5);
			printw("Wizard Fight?");
			move(2, 5);
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
		case 'r':
			wf_allred();
			break;
		case 'T':
			move(0,0);
			mycur_test_acs();
			curs_set(0); 
			refresh();
			break;
		case 'j':
			box(statw, 0, 0);
			wrefresh(statw);
			break;
		case '1':	
			wmove(arena, 1, 1);
			wprintw(arena, "has_colors:%d", has_colors());
			wmove(arena, 2, 1);
			wprintw(arena, "can_change_color:%d", can_change_color());
			wmove(arena, 3, 1);
			wprintw(arena, "COLORS:%d COLOR_PAIRS:", COLORS, COLOR_PAIRS);
			wrefresh(arena);
			break;
		}
	}

end:
	delwin(arena);
	delwin(statw);
	endwin();
	return EXIT_SUCCESS;
}

void
wf_show_help()
{
	WINDOW         *h = newwin(30, 50, 4, 4);
	box(h, 0, 0);
	wmove(h, 1, 1);
	wprintw(h, "h - help");
	wmove(h, 2, 1);
	wprintw(h, "q - quit");
	wmove(h, 3, 1);
	wprintw(h, "c - clear window");
	wmove(h, 4, 1);
	wprintw(h, "C - Clear");
	wmove(h, 5, 1);
	wprintw(h, "w - window");
	wmove(h, 6, 1);
	wprintw(h, "t - test");
	wmove(h, 7, 1);
	wprintw(h, "p - put wizards in window");
	wmove(h, 8, 1);
	wprintw(h, "r - all red");
	wmove(h, 9, 1);
	wprintw(h, "T - show ACS_* chars");
	wmove(h, 10, 1);
	wprintw(h, "j - statw");
	wmove(h, 11, 1);
	wprintw(h, "1 - ncurses color stats");

	curs_set(0);
	wrefresh(h);

	delwin(h);
}

/*
    COLOR_BLACK
    COLOR_RED
    COLOR_GREEN
    COLOR_YELLOW
    COLOR_BLUE
    COLOR_MAGENTA
    COLOR_CYAN
    COLOR_WHITE
*/
void
wf_allred()
{
	int 		max_x    , max_y;
	int 		x        , y;

	getmaxyx(stdscr, max_y, max_x);
	/*
	init_pair(1, COLOR_YELLOW, COLOR_GREEN);
	attron(COLOR_PAIR(PLAYER_PAIR));
	mvaddch(y, x, PLAYER);
	attroff(COLOR_PAIR(PLAYER_PAIR));
	*/
	init_pair(1, COLOR_YELLOW, COLOR_RED);
	attron(COLOR_PAIR(1));
	for (x = 0; x < max_x; x++) {
		for (y = 0; y < max_y; y++) {
			move(y, x);
			addch('X');
		}
	}
	refresh();
	attroff(COLOR_PAIR(1));
}

void
wf_update_status(WINDOW *w, char * s)
{
	wmove(w, 2, 2);
	wprintw(w, s);
	curs_set(0);
	wrefresh(w);
}


