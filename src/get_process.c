#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "main.h"


int SfcGetPupInfo(header_buffer_){

	const uint8_t *header_buffer;
	const uint32_t *header_buffer_u32t;

	header_buffer = header_buffer_;
	header_buffer_u32t = header_buffer_;


	printf("Package Version : %d\n\n",header_buffer_u32t[0x8 / 4]);


	//FW
	image_version = header_buffer_u32t[0x10 / 4];
	printf("Image Version : %X\n\n",image_version);


	file_count = header_buffer[0x18];
	printf("File Count : %d\n\n",file_count);


	header_length = header_buffer_u32t[0x20 / 4];
	printf("Header Length : 0x%X\n\n",header_length);


	package_length = header_buffer_u32t[0x28 / 4];
	printf("Package Length : %dByte\n\n",package_length);


	pup_type = SfcGetPupType(header_buffer[0x3C]);
	printf("PUP Type : %s\n\n\n",pup_type);



}


int SfcGetPupType(a1){

	int pup_type;

	switch (a1){

		case 4:pup_type = "TestKit";break;
		//case 3:pup_type = "???";break;
		case 2:pup_type = "Retail";break;
		case 1:pup_type = "DevKit";break;

		default:pup_type = "unknown";break;

	}

	return pup_type;

}


int GetFileEntryID(e1){

	int Entry_File;

	switch (e1) {

			case 0x100:Entry_File = "version.txt";break;
			case 0x101:Entry_File = "license.xml";break;
			case 0x200:Entry_File = "psp2swu.self";break;
			case 0x204:Entry_File = "cui_setupper.self";break;

			case 0x221:Entry_File = "psv_package_data01.pkg";break;
			case 0x231:Entry_File = "psv_package_data02.pkg";break;


			case 0x301:Entry_File = "package_data01.pkg";break;
			case 0x302:Entry_File = "package_data02.pkg";break;
			case 0x303:Entry_File = "package_data03.pkg";break;
			case 0x304:Entry_File = "package_data04.pkg";break;
			case 0x305:Entry_File = "package_data05.pkg";break;
			case 0x306:Entry_File = "package_data06.pkg";break;
			case 0x307:Entry_File = "package_data07.pkg";break;
			case 0x308:Entry_File = "package_data08.pkg";break;
			case 0x309:Entry_File = "package_data09.pkg";break;
			case 0x30A:Entry_File = "package_data10.pkg";break;
			case 0x30B:Entry_File = "package_data11.pkg";break;
			case 0x30C:Entry_File = "package_data12.pkg";break;
			case 0x30D:Entry_File = "package_data13.pkg";break;
			case 0x30E:Entry_File = "package_data14.pkg";break;
			case 0x30F:Entry_File = "package_data15.pkg";break;
			case 0x310:Entry_File = "package_data16.pkg";break;
			case 0x311:Entry_File = "package_data17.pkg";break;
			case 0x312:Entry_File = "package_data18.pkg";break;
			case 0x313:Entry_File = "package_data19.pkg";break;
			case 0x314:Entry_File = "package_data20.pkg";break;
			case 0x315:Entry_File = "package_data21.pkg";break;
			case 0x316:Entry_File = "package_data22.pkg";break;
			case 0x317:Entry_File = "package_data23.pkg";break;
			case 0x318:Entry_File = "package_data24.pkg";break;
			case 0x319:Entry_File = "package_data25.pkg";break;
			case 0x31A:Entry_File = "package_data26.pkg";break;

			case 0x31B:Entry_File = "unknown_0x31B";break;
			case 0x31C:Entry_File = "unknown_0x31C";break;
			case 0x31D:Entry_File = "unknown_0x31D";break;
			case 0x31E:Entry_File = "unknown_0x31E";break;
			case 0x31F:Entry_File = "unknown_0x31F";break;
			case 0x320:Entry_File = "unknown_0x320";break;
			case 0x321:Entry_File = "unknown_0x321";break;
			case 0x322:Entry_File = "unknown_0x322";break;
			case 0x323:Entry_File = "unknown_0x323";break;
			case 0x324:Entry_File = "unknown_0x324";break;
			case 0x325:Entry_File = "unknown_0x325";break;


			case 0x326:Entry_File = "debug_data00.pkg";break;
			case 0x327:Entry_File = "debug_data01.pkg";break;
			case 0x328:Entry_File = "debug_data02.pkg";break;
			case 0x329:Entry_File = "debug_data03.pkg";break;
			case 0x32A:Entry_File = "debug_data04.pkg";break;
			case 0x32B:Entry_File = "debug_data05.pkg";break;
			case 0x32C:Entry_File = "debug_data06.pkg";break;


			case 0x32D:Entry_File = "unknown_0x32D";break;
			case 0x32E:Entry_File = "unknown_0x32E";break;
			case 0x32F:Entry_File = "unknown_0x32F";break;
			case 0x330:Entry_File = "unknown_0x330";break;
			case 0x331:Entry_File = "unknown_0x331";break;
			case 0x332:Entry_File = "unknown_0x332";break;
			case 0x333:Entry_File = "unknown_0x333";break;
			case 0x334:Entry_File = "unknown_0x334";break;
			case 0x335:Entry_File = "unknown_0x335";break;
			case 0x336:Entry_File = "unknown_0x336";break;
			case 0x337:Entry_File = "unknown_0x337";break;
			case 0x338:Entry_File = "unknown_0x338";break;


			case 0x400:Entry_File = "package_scewm.wm";break;
			case 0x401:Entry_File = "package_sceas.as";break;

			default:{

				char entry_id[128];
				sprintf(entry_id, "unk_0x%X", e1);


				Entry_File = entry_id;break;

			}


	}



	return Entry_File;

}