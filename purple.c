#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>

#include "mycur.h"

/*
def main(stdscr):
    curses.start_color()
    curses.use_default_colors()
    for i in range(0, curses.COLORS):
        curses.init_pair(i + 1, i, -1)
    try:
        for i in range(0, 255):
            stdscr.addstr(str(i), curses.color_pair(i))
    except curses.ERR:
        # End of screen reached
        pass
    stdscr.getch()

curses.wrapper(main)







int ch;
     nodelay(stdscr, TRUE);
     for (;;) {
          if ((ch = getch()) == ERR) {
              * user hasn't responded
               ...
              *
          }
          else {
              * user has pressed a key ch
               ...
              *
          }
     }

*/

int
main()
{
	WINDOW         *statw;
	int 		max_x    , max_y, x, y;
	char 		c;
	int 		ch;
	char 		input_buf[128];
	int 		input_idx;

	input_buf[0] = '\0';
	input_idx = 0;

	mycur_init();
	getmaxyx(stdscr, max_y, max_x);

	statw = newwin(18, 4, max_y - 10, max_x - 30);
	box(statw, 0, 0);
	wrefresh(statw);

	/* ***************************** */
	for (x = 0; x < max_x; x++) {
		for (y = 0; y < max_y; y++) {
			move(y, x);
			addch('x');
		}
	}
	curs_set(0);
	refresh();

	c = getch();
	waddch(statw, c);




	nodelay(stdscr, TRUE);
	int i=0;
	for (;;) {
		i++;
		if ((ch = getch()) == ERR) {
			/* user hasn't responded ...  */
			wmove(statw, 1, 1);
			wprintw(statw, "no resp %d", i);
			wrefresh(statw);
		} else {
			/* user has pressed a key ch ...  */
			wprintw(statw, "key:");
			waddch(statw, ch);
			wrefresh(statw);
			if (ch == 'q') {
				goto end;
			}
		}
	}








	/* ***************************** */
	init_pair(1, COLOR_YELLOW, COLOR_GREEN);
	attron(COLOR_PAIR(1));
	for (x = 0; x < max_x; x++) {
		for (y = 0; y < max_y; y++) {
			move(y, x);
			addch('@');
		}
	}
	curs_set(0);
	attroff(COLOR_PAIR(1));
	refresh();



	c = getch();

end:
	delwin(statw);
	endwin();
	return EXIT_SUCCESS;
}
