
#define printf psvDebugScreenPrintf

#define base_partition "ux0:"
#define read_pup_dir base_partition "PSP2UPDAT/"
#define pup_dec_base_dir base_partition "PSP2UPDAT_Dec/"


#define _BYTE1(x) (  x        & 0xFF )
#define _BYTE2(x) ( (x >>  8) & 0xFF )
#define _BYTE3(x) ( (x >> 16) & 0xFF )
#define _BYTE4(x) ( (x >> 24) & 0xFF )
 
#define BYTE_SWAP_16(x) ((uint16_t)( _BYTE1(x)<<8 | _BYTE2(x) ))
#define BYTE_SWAP_32(x) ((uint32_t)( _BYTE1(x)<<24 | _BYTE2(x)<<16 | _BYTE3(x)<<8 | _BYTE4(x) ))



char pup_dec_dir[0x100];

int pup_type;

int file_count;
int image_version;
int pup_type;
int file_count;
int header_length;
int package_length;


int SfcGetPupInfo(header_buffer);

int SfcExtractPupFiles(pup_dec_dir, file_check, i, file_count, header_buffer);

int GetFileEntryID(a1);

int SfcGetPupType(a1);