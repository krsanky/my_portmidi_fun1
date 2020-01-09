#include <curses.h>
#include <unistd.h>

#include "mycur.h"

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
mycur_init()
{
	initscr();
	start_color();
	cbreak();
	noecho();
	/* Most programs would additionally use the sequence: */
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
}

void
mycur_test_acs()
{
        printw("Upper left corner           "); addch(ACS_ULCORNER); printw("\n"); 
        printw("Lower left corner           "); addch(ACS_LLCORNER); printw("\n");
        printw("Lower right corner          "); addch(ACS_LRCORNER); printw("\n");
        printw("Tee pointing right          "); addch(ACS_LTEE); printw("\n");
        printw("Tee pointing left           "); addch(ACS_RTEE); printw("\n");
        printw("Tee pointing up             "); addch(ACS_BTEE); printw("\n");
        printw("Tee pointing down           "); addch(ACS_TTEE); printw("\n");
        printw("Horizontal line             "); addch(ACS_HLINE); printw("\n");
        printw("Vertical line               "); addch(ACS_VLINE); printw("\n");
        printw("Large Plus or cross over    "); addch(ACS_PLUS); printw("\n");
        printw("Scan Line 1                 "); addch(ACS_S1); printw("\n");
        printw("Scan Line 3                 "); addch(ACS_S3); printw("\n");
        printw("Scan Line 7                 "); addch(ACS_S7); printw("\n");
        printw("Scan Line 9                 "); addch(ACS_S9); printw("\n");
        printw("Diamond                     "); addch(ACS_DIAMOND); printw("\n");
        printw("Checker board (stipple)     "); addch(ACS_CKBOARD); printw("\n");
        printw("Degree Symbol               "); addch(ACS_DEGREE); printw("\n");
        printw("Plus/Minus Symbol           "); addch(ACS_PLMINUS); printw("\n");
        printw("Bullet                      "); addch(ACS_BULLET); printw("\n");
        printw("Arrow Pointing Left         "); addch(ACS_LARROW); printw("\n");
        printw("Arrow Pointing Right        "); addch(ACS_RARROW); printw("\n");
        printw("Arrow Pointing Down         "); addch(ACS_DARROW); printw("\n");
        printw("Arrow Pointing Up           "); addch(ACS_UARROW); printw("\n");
        printw("Board of squares            "); addch(ACS_BOARD); printw("\n");
        printw("Lantern Symbol              "); addch(ACS_LANTERN); printw("\n");
        printw("Solid Square Block          "); addch(ACS_BLOCK); printw("\n");
        printw("Less/Equal sign             "); addch(ACS_LEQUAL); printw("\n");
        printw("Greater/Equal sign          "); addch(ACS_GEQUAL); printw("\n");
        printw("Pi                          "); addch(ACS_PI); printw("\n");
        printw("Not equal                   "); addch(ACS_NEQUAL); printw("\n");
        printw("UK pound sign               "); addch(ACS_STERLING); printw("\n");
}

void
mycur_topl_down_1()
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



