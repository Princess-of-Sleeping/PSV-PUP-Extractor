
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>


#include "main.h"



int SfcExtractPupFiles(pup_dec_dir, file_check, i, file_count, header_buffer){

	const uint32_t *header_buffer_u32t;

	header_buffer_u32t = header_buffer;


	int base_addr1 = 0x80 + (0x20 * i);
	int base_addr2 = (0x80 + (0x20 * file_count)) + (0x40 * i);


	printf("File Count : %d / %d\n\n", (i+1), file_count);


	int file_entry_id = header_buffer_u32t[base_addr1 / 4];
	int entry_file_name = GetFileEntryID(file_entry_id);
	printf("FileEntry%d : %s\n\n",i, entry_file_name);


	int data_offset = header_buffer_u32t[(base_addr1 + 0x8) / 4];
	printf("Data Offset : 0x%X\n\n",data_offset);


	int data_length = header_buffer_u32t[(base_addr1 + 0x10) / 4];
	printf("Data Length : 0x%X / %dByte\n\n",data_length,data_length);


	int file_index = header_buffer_u32t[base_addr2 / 4];
	printf("File Index : %d\n\n",file_index);



	char write_file_name[0x100];
	sprintf(write_file_name, "%s%s", pup_dec_dir, entry_file_name);

	printf("open write file ... ");

	int fd = sceIoOpen(write_file_name, SCE_O_TRUNC | SCE_O_CREAT | SCE_O_WRONLY, 0777);

	int pup_buffer = malloc(data_length);


	if(fd >= 0){

		printf("Success.(%s)\n\n",write_file_name);

		printf("Read File Offset ... ");

		int sipr = sceIoPread(file_check, pup_buffer, data_length, data_offset);

		if(sipr >= 0){

			printf("Success.\n\n");

			printf("File Write ... ");

			int siw = sceIoWrite(fd, pup_buffer, data_length);

			if(siw == data_length){

				printf("Success.\n\n");

				printf("File Close ... ");

				int sic = sceIoClose(fd);

				if(sic >= 0){

					printf("Success.");

				}else{

					printf("Failed.");

				}

			}else{

				printf("Failed.");

			}

		}else{

			printf("Failed.");

		}

	}else{

		printf("Failed.");

	}

	free(pup_buffer);

}
