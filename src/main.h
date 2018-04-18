#include <psp2/kernel/processmgr.h>

#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>

#include <psp2/ctrl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graphics.h"

#define printf psvDebugScreenPrintf

#define base_partition "ux0:"
#define file_read_dir base_partition "PSP2UPDAT/"
#define file_output_dir file_read_dir "dec/"


#define _BYTE1(x) ( (x >> 0x00) & 0xFF )
#define _BYTE2(x) ( (x >> 0x08) & 0xFF )
#define _BYTE3(x) ( (x >> 0x10) & 0xFF )
#define _BYTE4(x) ( (x >> 0x18) & 0xFF )
#define _BYTE5(x) ( (x >> 0x20) & 0xFF )
#define _BYTE6(x) ( (x >> 0x28) & 0xFF )
#define _BYTE7(x) ( (x >> 0x30) & 0xFF )
#define _BYTE8(x) ( (x >> 0x38) & 0xFF )

#define BYTE_SWAP_16(x) ((uint16_t)( _BYTE1(x)<<8 | _BYTE2(x) ))
#define BYTE_SWAP_32(x) ((uint32_t)( _BYTE1(x)<<0x18 | _BYTE2(x)<<0x10 | _BYTE3(x)<<8 | _BYTE4(x) ))
#define BYTE_SWAP_64(x) ((SceUInt64)( _BYTE1(x)<<0x38 | _BYTE2(x)<<0x30 | _BYTE3(x)<<0x28 | _BYTE4(x)<<0x20 | _BYTE5(x)<<0x18 | _BYTE6(x)<<0x10 | _BYTE7(x)<<0x8 | _BYTE8(x)<<0x0 ))

typedef struct {
	SceUInt64	magic;
	SceUInt32	package_version;	//0x00000008
	SceUInt32	unknown_0x0C;
	SceUInt32	image_version;		//0x00000010
	SceUInt32	unknown_0x14;
	SceUInt32	file_count;		//0x00000018
	SceUInt32	unknown_0x1C;
	SceUInt32	header_length;		//0x00000020
	SceUInt32	unknown_0x24;
	SceUInt32	package_length;		//0x00000028
	SceUInt32	unknown_0x2C;
	SceUInt32	unknown_0x30;
	SceUInt32	unknown_0x34;
	SceUInt32	unknown_0x38;
	SceUInt32	pup_type;		//0x0000003C
	SceUInt32	unknown_0x40;
	SceUInt32	unknown_0x44;
	SceUInt32	unknown_0x48;
	SceUInt32	unknown_0x4C;
	SceUInt32	unknown_0x50;
	SceUInt32	unknown_0x54;
	SceUInt32	unknown_0x58;
	SceUInt32	unknown_0x5C;
	SceUInt32	unknown_0x60;
	SceUInt32	unknown_0x74;
	SceUInt32	unknown_0x78;
	SceUInt32	unknown_0x7C;
} __attribute__((packed)) ScePlayStartionUpdatePackageHeader1;

typedef struct {
	SceUInt32	entry_id;
	SceUInt32	unknown_0x04;
	SceUInt32	data_offset;		//0x00000008
	SceUInt32	unknown_0x0C;
	SceUInt32	data_length;		//0x00000010
	SceUInt32	unknown_0x14;
	SceUInt32	unknown_0x18;		// 2?
	SceUInt32	unknown_0x1C;
} __attribute__((packed)) ScePlayStartionUpdatePackageHeader2;

typedef struct {
	SceUInt32	index;
	SceUInt32	unknown_0x04;
	char		hash[0x20];		//HMAC-sha256?
	SceUInt32	unknown_0x28;
	SceUInt32	unknown_0x2C;
	SceUInt32	unknown_0x30;
	SceUInt32	unknown_0x34;
	SceUInt32	unknown_0x38;
	SceUInt32	unknown_0x3C;
} __attribute__((packed)) ScePlayStartionUpdatePackageHeader3;

char pup_type_buf[0x20];
char pup_dec_dir[0x100];
char temp_buff[0x2000];


int get_key(int type);

void press_next(void);

void press_exit(void);


int scePlayStartionUpdatePackageExtractFiles(char *pup_dec_dir, SceUID file_check, int i, SceUInt32 file_count, void *header);

void sceGetPlayStartionUpdatePackageFileEntryId(void *buff, int entry_id);

int sceGetPlayStartionUpdatePackageInfo(ScePlayStartionUpdatePackageHeader1 *header);