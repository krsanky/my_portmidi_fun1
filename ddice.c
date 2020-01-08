#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <portmidi.h>
#include <sys/types.h>
#include <dev/rndvar.h>

#include "mymidi.h"

#include "ddice.h"

struct tick    *
make_tick()
{
	struct tick * t;
	assert((t = malloc(sizeof(struct tick))) != NULL);
	t->rhand = HIHAT;
	return t;
}

void
zero_tick(struct tick *t)
{
	t->lhand = NONE;
	t->rhand = NONE;
	t->rfoot = NONE;
}

enum target
rand_rfoot_1()
{
	int r = rand() % 2;
	switch(r) {
	case 0:
		return KICK;
		break;
	case 1:
		return NONE;
		break;
	default:
		return NONE;
	}
}

enum target
rand_lhand_1()
{
	int r = rand() % 2;
	switch(r) {
	case 0:
		return SNARE;
		break;
	case 1:
		return NONE;
		break;
	default:
		return NONE;
	}
}

/*
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, midi_note, d2));
		usleep(usl);
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, midi_note, d2));

	SNARE,
	HIHAT,
	KICK,
	NONE,
38 Acoustic Snare
35 Acoustic Bass Drum
36 Bass Drum 1
42 Closed Hi Hat
	int 		midi_note = 76;	* 76 77  low, high wood block *
*/
void
play_tick(PortMidiStream *pms, struct tick *t)
{
	int chan = 9;
	int wood_block = 76;
	int		usl = 100000;

	Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_ON | chan, wood_block, 60));

	if (t->rhand != NONE)
		Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_ON | chan, t->rhand, 120));
	if (t->lhand != NONE)
		Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_ON | chan, t->lhand, 120));
	if (t->rfoot != NONE)
		Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_ON | chan, t->rfoot, 120));

	usleep(usl);

	Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_OFF | chan, wood_block, 60));

	if (t->rhand != NONE)
		Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_OFF | chan, t->rhand, 120));
	if (t->lhand != NONE)
		Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_OFF | chan, t->lhand, 120));
	if (t->rfoot != NONE)
		Pm_WriteShort(pms, 0, Pm_Message(MIDI_NOTE_OFF | chan, t->rfoot, 120));
}


