#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <portmidi.h>
#include <porttime.h>
#include <assert.h>
#include <sys/types.h>
#include <dev/rndvar.h>

#define MIDI_NOTE_ON    0x90
#define MIDI_NOTE_OFF   0x80

PmDeviceID 	pm_dev_id = 7;

int
rand_0_1()
{
	return (rand() % 2);
}

char	lr = 'l';
void
send_msg_click(PortMidiStream * pm_stream)
{
	char 		chan = 9;	/* chan 9 is drums */
	int 		d2 = 120;	/* intensity */
	int 		midi_note = 76;	/* 76 77  low, high wood block */
	int		usl = 100000;

	int		hh = 42;

	midi_note = 76 + rand_0_1();
	//usl = usl * (rand() % 3);

	if (lr == 'l') {
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, midi_note, d2));
		usleep(usl);
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, midi_note, d2));
		lr = 'r';
	} else {
		lr = 'l';
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, hh, d2));
		usleep(usl);
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, hh, d2));
	}
}

void
loop_wood_block()
{
	int 		i;

	PortMidiStream *pm_stream = NULL;

	Pm_Initialize();
	if (Pm_OpenOutput(&pm_stream, pm_dev_id, NULL, 512, NULL, NULL, 0) != pmNoError)
		goto done;

	for (i = 0; i < 9000; i++) {
		usleep(100000);
		printf("click - %d %d %d %d\n", i, i%4, i%8, i%16);
		send_msg_click(pm_stream);
	}

	Pm_Close(pm_stream);
done:
	Pm_Terminate();
}

int
main()
{
	loop_wood_block();
	return EXIT_SUCCESS;
}
