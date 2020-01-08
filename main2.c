#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <portmidi.h>
#include <assert.h>
#include <sys/types.h>
#include <dev/rndvar.h>

#include "ddice.h"
#include "mymidi.h"

struct tick *the_tick;

void
next_tick()
{
	the_tick->rhand = HIHAT;

	if ((rand() % 2) == 0) {
		the_tick->lhand = rand_lhand_1();
		if (the_tick->lhand == NONE)
			the_tick->rfoot = rand_rfoot_1();
	} else {
		the_tick->rfoot = rand_rfoot_1();
		if (the_tick->rfoot == NONE)
			the_tick->lhand = rand_lhand_1();
	}
}

void
loop()
{
	int 		i;
	PmDeviceID 	pm_dev_id = 7;

	PortMidiStream *pm_stream = NULL;

	Pm_Initialize();
	if (Pm_OpenOutput(&pm_stream, pm_dev_id, NULL, 512, NULL, NULL, 0) != pmNoError)
		goto done;
	
	zero_tick(the_tick);
	for (i = 0; i < 9000; i++) {
		printf("%.8d %d %d %.2d\n", i, i%4, i%8, i%16);
		next_tick();
		//send_msg_click(pm_stream);
		play_tick(pm_stream, the_tick);
	}

	Pm_Close(pm_stream);
done:
	Pm_Terminate();
}

int
main()
{
	the_tick = make_tick();
	loop();
	free(the_tick);
	return EXIT_SUCCESS;
}
