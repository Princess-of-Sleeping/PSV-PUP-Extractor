#include "main.h"

int get_key(int type) {


	SceCtrlData pad;

	if(type == 0){

		while (1) {
			sceCtrlPeekBufferPositive(0, &pad, 1);

				if (pad.buttons != 0)
					return pad.buttons;
		}

	}else{

		while (1) {
			sceCtrlPeekBufferPositive(0, &pad, 1);
			if(pad.buttons == 0){
				break;
			}
		}

	}

	return 0;

}


void press_next(void) {

	printf("Press any key to next this application.\n\n");

	get_key(1);
	get_key(0);
	get_key(1);

}


void press_exit(void) {

	printf("Press any key to exit this application.\n\n");

	get_key(1);
	get_key(0);
	get_key(1);

	sceKernelExitProcess(0);

}