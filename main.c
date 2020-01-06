#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <portmidi.h>
#include <porttime.h>

/* from portmid.c (why arent they in a header file?) */
#define MIDI_NOTE_ON    0x90
#define MIDI_NOTE_OFF   0x80
#define MIDI_PROGRAM    0xC0

void
pm_display_devs()
{
	const PmDeviceInfo *pm_dev_info;
	int 		pm_num_devs;

	pm_num_devs = Pm_CountDevices();
	for (int i = 0; i < pm_num_devs; i++) {
		printf("id %d: ", i);
		pm_dev_info = Pm_GetDeviceInfo(i);
		if ((pm_dev_info != NULL)) {
			printf("name: %s ", pm_dev_info->name);
			printf("input: %d ", pm_dev_info->input);
			printf("output: %d ", pm_dev_info->output);
			/* printf("interf: %s ", pm_dev_info->interf); */
			/* printf("opened: %d ", pm_dev_info->opened); */
			printf("\n");
		}
	}
}

int
main()
{
	PortMidiStream *pm_stream = NULL;
	PmError 	pmerr;
	PmDeviceID 	id;

	Pm_Initialize();
	pm_display_devs();
	printf("choose: ");
	scanf("%d", &id);
	printf("\n");

	pmerr = Pm_OpenOutput(&pm_stream, id, NULL, 512, NULL, NULL, 0);
	if (pmerr != pmNoError) {
		printf("pmerr: %s\n", Pm_GetErrorText(pmerr));
		Pm_Terminate();
		return EXIT_FAILURE;
	}
	char 		chan = 0;
	int 		prg = 0;
	int 		d2 = 120;
	long 		time = 0;
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_PROGRAM | chan, prg, 0));

	/* note on events to play C major chord */
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, 60, d2));
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, 64, d2));
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, 67, d2));
	time = Pt_Time(NULL);
	while (Pt_Time(NULL) - time < 1000)
		usleep(100);
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, 60, d2));
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, 64, d2));
	Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, 67, d2));

	/*
	// notes will be sustained for 2 seconds
	time.Sleep(2 * time.Second)
	
	// note off events
	out.WriteShort(0x80, 60, d2)
	out.WriteShort(0x80, 64, d2)
	out.WriteShort(0x80, 67, d2)
	*/




	int 		i;
	for (i = 60; i < 72; i++) {
		prg += 4;
		//Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_PROGRAM | chan, prg, 0));
		time = Pt_Time(NULL);
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan, i, 120));
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_ON | chan + 1, i + 1, 120));
		while (Pt_Time(NULL) - time < 1000)
			usleep(100);
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan, i, 120));
		Pm_WriteShort(pm_stream, 0, Pm_Message(MIDI_NOTE_OFF | chan + 1, i + 1, 120));
	}

	Pm_Close(pm_stream);
	Pm_Terminate();
	return EXIT_SUCCESS;
}
