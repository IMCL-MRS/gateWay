/*
 * GateWay
 *
 * Written by sundy 28/5/2016
 *
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <tchar.h>
#include <string>
#include "Serial/inc/SerialClass.h"


void SerialTest(int com_id){
    printf("Welcome to the serial test app!\n\n");

    char comm[64];
    sprintf(comm, "\\\\.\\COM%d", com_id);
	Serial* SP = new Serial(comm);    // adjust as needed

	if (SP->IsConnected())
		printf("We're connected");

	char incomingData[2048] = "";			// don't forget to pre-allocate memory
//	printf("%s\n",incomingData);
	int dataLength = 256;
	int readResult = 0;
	int i = 0;

	while(SP->IsConnected())
	{
		readResult = SP->ReadData(incomingData,dataLength);
//      printf("Bytes read: (0 means no data available) %i\n",readResult);
        incomingData[readResult] = 0;

        printf("size:%d->data: ",readResult);
        if(readResult)
		{
			for(i = 0; i < readResult; i++)
			{
				printf("0x%X ",incomingData[i]);
			}

			printf("\n");
		}

        printf("\n");
/*size:33->data: 0x7E 0x45 0xFFFFFFA1 0x1C 0x1 0x0 0x0 0x0 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0x71 0x3D 0xFFFFFF8A 0x3E 0xFFFFFFFA 0xFFFFFFBF 0xFFFFFFA4 0x42 0x1 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0x0 0xFFFFFF93*/
		Sleep(200);
	}
}

int main(int argc, char *argv[])
{
    SerialTest(3); //3 is COM3

    return EXIT_SUCCESS;
}
