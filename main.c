#include <stdio.h>
#include <stdlib.h>
#include <portmidi.h>

void
pm_display_devs()
{
	const PmDeviceInfo	*pm_dev_info;
	int				pm_num_devs;
	pm_num_devs = Pm_CountDevices();
	for (int i=0; i<pm_num_devs; i++) {
		printf("id %d: ", i);
		pm_dev_info = Pm_GetDeviceInfo(i);
		if (pm_dev_info != NULL) {
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
	Pm_Initialize();
	pm_display_devs();
	Pm_Terminate();
	return EXIT_SUCCESS;
}

