#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "mycur.h"


void
show_grid(char grid[4][8])
{
	int 		i        , j;
	int 		root      [2] = {2, 2};

	/* printw("COLUMNS:%d LINES:%d", max_x, max_y); OK ERR */

	move(root[0], root[1]);
	addch(ACS_ULCORNER);
	printw("-----------");
	for (i = 0; i < 4; i++) {
		move(root[0]+1+i, root[1]);

		addch(ACS_VLINE);

		for (j = 0; j < 8; j++) {
			addch(grid[i][j]);
			addch(' ');
			addch(' ');
			addch(' ');
			addch(' ');
		}
	}
	addch(ACS_LLCORNER);
	addch(' ');
	addch(ACS_LANTERN);
	addch(' ');
	addch(ACS_PI);
	addch(' ');


}

int
main()
{
	int 		ch;
	char 		gf       [4][8] = {
		{'1', ' ', '0', ' ', ' ', ' ', 'y', 'c'},
		{' ', 'y', ' ', 'p', 'k', 'x', ' ', ' '},
		{'1', '3', '0', ' ', ' ', ' ', 'i', 'c'},
		{' ', ' ', ' ', 'j', ' ', 'x', ' ', ' '},
	};

	mycur_init();

	show_grid(gf);
	while ((ch = getch())) {
		switch (ch) {
		case 'q':
			goto end;
			break;
		case 'm':
			mycur_topl_down_1();
			break;
		case 'g':
			show_grid(gf);
			break;
		case 'a':
			move(1, 1);			
			mycur_test_acs();
			refresh();
			break;
		case 'e':
			erase();
			break;
		}
	}

end:
	endwin();
	return EXIT_SUCCESS;
}
