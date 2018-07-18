

#include "main.h"


int scePlayStartionUpdatePackageExtractStage1(char *ext_pup_path) {

	printf("PUP Path : %s\n\n\n", ext_pup_path);

	printf("Start Extractor");

	for(int i=0;i<3;i++){
		sceKernelDelayThread(0.2*1000*1000);
		printf(".");
	}

	sceKernelDelayThread(0.1*1000*1000);
	printf("\n\n\n");


	SceUID file_check = sceIoOpen(ext_pup_path, SCE_O_RDONLY, 0);
	if(file_check < 0){

		printf("File Open Error.\n\n");
		printf("res : 0x%08X\n\n", file_check);
		return file_check;
	}

	ScePlayStartionUpdatePackageHeader1 header;

	sceIoPread(file_check, &header, sizeof(ScePlayStartionUpdatePackageHeader1), 0);
	sceIoPread(file_check, temp_buff, sizeof(temp_buff), 0);


	printf("PUP magic check ... ");


	if(BYTE_SWAP_64(header.magic) != 0x5343455546000001){

		printf("Failed, Not PUP file.\n\n");
		printf("0x%llX\n\n", BYTE_SWAP_64(header.magic));

		return -1;
	}

	printf("ok, SONY PSV PUP file.\n\n");


	sceGetPlayStartionUpdatePackageInfo(&header);

	press_next();

	printf("\n\n");

	sprintf(pup_dec_dir, "%s%s_0x%08X/", file_output_dir, pup_type_buf, header.image_version);


	NotExistMkdir(pup_dec_dir);

	SceCtrlData buf;

	for(int i=0;i<header.file_count;i++){

		if (sceCtrlPeekBufferPositive(0, &buf, 1) < 0) {
			return 0;
		}

		if (buf.buttons & SCE_CTRL_START) {
			sceKernelExitProcess(0);
		}



		scePlayStartionUpdatePackageExtractFiles(pup_dec_dir, file_check, i, header.file_count, temp_buff);


		printf("\n\n");

	}



	sceIoClose(file_check);
	printf("\n\n");
	
	return 0;
}



int NotExistMkdir(char *path){

	int dfd = sceIoDopen(path);
	if(dfd >= 0){

		sceIoDclose(dfd);

	}else{

		sceIoMkdir(path, 0777);

	}

	return 0;

}


int main(int argc, char *argv[]) {

	psvDebugScreenInit();

	NotExistMkdir(file_read_dir);

	NotExistMkdir(file_output_dir);


	SceUID gc_update_check = sceIoOpen("gro0:psp2/update/psp2updat.pup", SCE_O_RDONLY, 0);
	if(gc_update_check >= 0){

		sceIoClose(gc_update_check);

		printf("Game Card mode\n\n");

		scePlayStartionUpdatePackageExtractStage1("gro0:psp2/update/psp2updat.pup");

	}else{



		SceUID dfd2 = sceIoDopen(file_read_dir);

		int res = 0;

		do {



			SceIoDirent dir;
			memset(&dir, 0, sizeof(SceIoDirent));

			res = sceIoDread(dfd2, &dir);
			if (res > 0 && (!SCE_S_ISDIR(dir.d_stat.st_mode))) {

				psvDebugScreenInit();
				printf("Memory Card mode\n\n");

				char read_pup_dir_path[0x100];
				sprintf(read_pup_dir_path, "%s%s", file_read_dir, dir.d_name);

				scePlayStartionUpdatePackageExtractStage1(read_pup_dir_path);

				printf("output dir - %s\n\n", pup_dec_dir);

				press_next();

			}

		} while (res > 0);

		sceIoDclose(dfd2);

	}


	printf("*** ALL DONE ***\n\n");

	press_exit();

	sceKernelExitProcess(0);
	return 0;
}
