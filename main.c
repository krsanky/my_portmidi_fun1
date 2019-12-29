#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <portmidi.h>
#include <porttime.h>

#define MD_NOTEON 0x90
#define MD_NOTEOFF 0x80
#define MD_PRG 0xC0
#define SBYTE(mess, chan) mess | chan 

void
pm_display_devs()
{
	const PmDeviceInfo	*pm_dev_info;
	int				pm_num_devs;

	pm_num_devs = Pm_CountDevices();
	for (int i=0; i<pm_num_devs; i++) {
		printf("id %d: ", i);
		pm_dev_info = Pm_GetDeviceInfo(i);
		if ((pm_dev_info != NULL)) {
			printf("name: %s ", pm_dev_info->name);
			printf("input: %d ", pm_dev_info->input);
			printf("output: %d ", pm_dev_info->output);
/*			printf("interf: %s ", pm_dev_info->interf);*/
/*			printf("opened: %d ", pm_dev_info->opened);*/
			printf("\n");
		}
	}
}

int
main()
{
	PortMidiStream	*pm_stream = NULL;
	PmError			pmerr;
	PmDeviceID		id;


	Pm_Initialize();
	pm_display_devs();
	printf("choose: ");
	scanf("%d", &id);
	printf("\n");

	pmerr = Pm_OpenOutput(&pm_stream, id, 
				NULL, 512, NULL, NULL, 0);
	
    if (pmerr != pmNoError) {
		printf("pmerr: %s\n", Pm_GetErrorText(pmerr));
		Pm_Terminate();
		return EXIT_FAILURE;
	}

	char	chan = 0;
	int		prg = 0;
	long	time = 0;
	int		i;
	for (i=60; i<72; i++) {
		prg+=4;
		Pm_WriteShort(pm_stream, 0, 
			Pm_Message(SBYTE(MD_PRG, chan), prg, 0));
		time = Pt_Time(NULL);
		Pm_WriteShort(pm_stream, 0, 
			Pm_Message(SBYTE(MD_NOTEON, chan), i, 120));
		while (Pt_Time(NULL) - time < 1000)
			usleep(100);
		Pm_WriteShort(pm_stream, 0, 
			Pm_Message(SBYTE(MD_NOTEOFF, chan), i, 120));
	}


	Pm_Close(pm_stream);
	Pm_Terminate();
	return EXIT_SUCCESS;
}
/*
    pMidiOut->NoteOn(channel, scale[i], volume);
    ::wxMilliSleep(200);    // wait 200ms
    pMidiOut->NoteOff(channel, scale[i], volume);    


	PortMidiStream *pm_stream;
PmError  Pm_OpenOutput (PortMidiStream **stream, PmDeviceID outputDevice, 
void *outputDriverInfo, long bufferSize, PmTimeProcPtr time_proc, void *time_info, long latency)

*/

