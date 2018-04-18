
#include "main.h"

int sceGetPlayStartionUpdatePackageType(int pup_type){

	memset(pup_type_buf, 0, sizeof(pup_type_buf));

	switch (pup_type){

		case 4:sprintf(pup_type_buf, "TestKit");break;
		//case 3:sprintf(pup_type_buf, "???\n");break;
		case 2:sprintf(pup_type_buf, "Retail");break;
		case 1:sprintf(pup_type_buf, "DevKit");break;

		default:sprintf(pup_type_buf, "unknown");break;

	}

	return 0;

}

int sceGetPlayStartionUpdatePackageInfo(ScePlayStartionUpdatePackageHeader1 *header){

	sceGetPlayStartionUpdatePackageType(header->pup_type);


	printf("Package Version : %d\n\n", header->package_version);

	printf("Image Version : 0x%08X\n\n", header->image_version);

	printf("File Count : %d\n\n", header->file_count);

	printf("Header Length : 0x%X\n\n", header->header_length);

	printf("Package Length : %dByte\n\n", header->package_length);

	printf("PUP Type : %s\n\n\n", pup_type_buf);

	return 0;

}





void sceGetPlayStartionUpdatePackageFileEntryId(void *buff, int entry_id){

	switch (entry_id) {

			case 0x100:sprintf(buff, "version.txt");break;
			case 0x101:sprintf(buff, "license.xml");break;
			case 0x200:sprintf(buff, "psp2swu.self");break;
			case 0x204:sprintf(buff, "cui_setupper.self");break;

			case 0x221:sprintf(buff, "psv_package_data01.pkg");break;
			case 0x231:sprintf(buff, "psv_package_data02.pkg");break;

			case 0x301:sprintf(buff, "package_data01.pkg");break;
			case 0x302:sprintf(buff, "package_data02.pkg");break;
			case 0x303:sprintf(buff, "package_data03.pkg");break;
			case 0x304:sprintf(buff, "package_data04.pkg");break;
			case 0x305:sprintf(buff, "package_data05.pkg");break;
			case 0x306:sprintf(buff, "package_data06.pkg");break;
			case 0x307:sprintf(buff, "package_data07.pkg");break;
			case 0x308:sprintf(buff, "package_data08.pkg");break;
			case 0x309:sprintf(buff, "package_data09.pkg");break;
			case 0x30A:sprintf(buff, "package_data10.pkg");break;
			case 0x30B:sprintf(buff, "package_data11.pkg");break;
			case 0x30C:sprintf(buff, "package_data12.pkg");break;
			case 0x30D:sprintf(buff, "package_data13.pkg");break;
			case 0x30E:sprintf(buff, "package_data14.pkg");break;
			case 0x30F:sprintf(buff, "package_data15.pkg");break;
			case 0x310:sprintf(buff, "package_data16.pkg");break;
			case 0x311:sprintf(buff, "package_data17.pkg");break;
			case 0x312:sprintf(buff, "package_data18.pkg");break;
			case 0x313:sprintf(buff, "package_data19.pkg");break;
			case 0x314:sprintf(buff, "package_data20.pkg");break;
			case 0x315:sprintf(buff, "package_data21.pkg");break;
			case 0x316:sprintf(buff, "package_data22.pkg");break;
			case 0x317:sprintf(buff, "package_data23.pkg");break;
			case 0x318:sprintf(buff, "package_data24.pkg");break;
			case 0x319:sprintf(buff, "package_data25.pkg");break;
			case 0x31A:sprintf(buff, "package_data26.pkg");break;

			case 0x31B:sprintf(buff, "unknown_0x31B");break;
			case 0x31C:sprintf(buff, "unknown_0x31C");break;
			case 0x31D:sprintf(buff, "unknown_0x31D");break;
			case 0x31E:sprintf(buff, "unknown_0x31E");break;
			case 0x31F:sprintf(buff, "unknown_0x31F");break;
			case 0x320:sprintf(buff, "unknown_0x320");break;
			case 0x321:sprintf(buff, "unknown_0x321");break;
			case 0x322:sprintf(buff, "unknown_0x322");break;
			case 0x323:sprintf(buff, "unknown_0x323");break;
			case 0x324:sprintf(buff, "unknown_0x324");break;
			case 0x325:sprintf(buff, "unknown_0x325");break;

			case 0x326:sprintf(buff, "debug_data00.pkg");break;
			case 0x327:sprintf(buff, "debug_data01.pkg");break;
			case 0x328:sprintf(buff, "debug_data02.pkg");break;
			case 0x329:sprintf(buff, "debug_data03.pkg");break;
			case 0x32A:sprintf(buff, "debug_data04.pkg");break;
			case 0x32B:sprintf(buff, "debug_data05.pkg");break;
			case 0x32C:sprintf(buff, "debug_data06.pkg");break;

			case 0x32D:sprintf(buff, "unknown_0x32D");break;
			case 0x32E:sprintf(buff, "unknown_0x32E");break;
			case 0x32F:sprintf(buff, "unknown_0x32F");break;
			case 0x330:sprintf(buff, "unknown_0x330");break;
			case 0x331:sprintf(buff, "unknown_0x331");break;
			case 0x332:sprintf(buff, "unknown_0x332");break;
			case 0x333:sprintf(buff, "unknown_0x333");break;
			case 0x334:sprintf(buff, "unknown_0x334");break;
			case 0x335:sprintf(buff, "unknown_0x335");break;
			case 0x336:sprintf(buff, "unknown_0x336");break;
			case 0x337:sprintf(buff, "unknown_0x337");break;
			case 0x338:sprintf(buff, "unknown_0x338");break;

			case 0x400:sprintf(buff, "package_scewm.wm");break;
			case 0x401:sprintf(buff, "package_sceas.as");break;


			default:{

				sprintf(buff, "unknown_0x%X", entry_id);

			}


	}




}