#include <stdio.h>
#include <stdlib.h>
#include <portmidi.h>

int
main()
{
	printf("portmidi....\n");
	Pm_Initialize();
//const PmDeviceInfo* Pm_GetDeviceInfo  (  PmDeviceID   id   )   
/*
typedef int PmDeviceID;
    206 #define pmNoDevice -1
    207 typedef struct {
    208     int structVersion; < this internal structure version 
    209     const char *interf; < underlying MIDI API, e.g. MMSystem or DirectX 
    210     const char *name;   < device name, e.g. USB MidiSport 1x1 
    211     int input; < true iff input is available 
    212     int output; < true iff output is available 
    213     int opened; *< used by generic PortMidi code to do error checking on arguments 
    214
    215 } PmDeviceInfo;
*/
	const PmDeviceInfo	*pm_dev_info;
	int				pm_num_devs;
	pm_num_devs = Pm_CountDevices();
	for (int i=0; i<pm_num_devs; i++) {
		printf("device %d: ", i);
		pm_dev_info = Pm_GetDeviceInfo(i);
		if (pm_dev_info != NULL) {
			printf("name: %s\n", pm_dev_info->name);
		}
	}


	Pm_Terminate();
	return EXIT_SUCCESS;
}

