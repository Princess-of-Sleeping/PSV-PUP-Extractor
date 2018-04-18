
#include "main.h"

char pup_buffer[0x20000];

int scePlayStartionUpdatePackageExtractFiles(char *pup_dec_dir, SceUID file_check, int i, SceUInt32 file_count, void *header){

	char write_file_name[0x100];
	char write_file_path[0x200];

	uint32_t base_addr1 = 0x80 + (0x20 * i);
	uint32_t base_addr2 = (0x80 + (0x20 * file_count)) + (0x40 * i);

	ScePlayStartionUpdatePackageHeader2 header2;
	ScePlayStartionUpdatePackageHeader3 header3;

	sceIoPread(file_check, &header2, sizeof(ScePlayStartionUpdatePackageHeader2), base_addr1);
	sceIoPread(file_check, &header3, sizeof(ScePlayStartionUpdatePackageHeader3), base_addr2);

	printf("File Count  : %d / %d\n\n", (i+1), file_count);


	sceGetPlayStartionUpdatePackageFileEntryId(write_file_name, header2.entry_id);
	printf("FileEntry%02d : %s\n\n", i, write_file_name);

	printf("Data Offset : 0x%X\n\n", header2.data_offset);

	printf("Data Length : 0x%X / %dByte\n\n", header2.data_length, header2.data_length);

	printf("File Index  : %d\n\n", header3.index);

	printf("File Hash  :");

	for(int shi=0;shi<sizeof(header3.hash);shi++)printf(" %02X", header3.hash[shi]);


	printf("\n\n");


	sprintf(write_file_path, "%s%s", pup_dec_dir, write_file_name);

	printf("open write file ... ");

	int fd = sceIoOpen(write_file_path, SCE_O_TRUNC | SCE_O_CREAT | SCE_O_WRONLY, 0777);


	if(fd < 0){

		printf("Failed.");

		return 0;

	}

	printf(" Success.(%s)\n\n", write_file_path);


	printf("File Write ... ");



	uint32_t plus_address = 0x0, read_size = sizeof(pup_buffer);

	do {

		if((plus_address + sizeof(pup_buffer)) > header2.data_length){

			read_size = (plus_address + sizeof(pup_buffer)) - header2.data_length;

			read_size = sizeof(pup_buffer) - read_size;

		}

		int sipr = sceIoPread(file_check, pup_buffer, read_size, header2.data_offset + plus_address);

		sceIoWrite(fd, pup_buffer, sipr);

		plus_address += sizeof(pup_buffer);

	} while (plus_address < header2.data_length);

	printf("      Success.\n\n");



	sceIoClose(fd);


	return 0;

}
