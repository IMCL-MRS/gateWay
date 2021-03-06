
#ifndef _ROBOT_H
#define _ROBOT_H

const int NROBOT = 8;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long uint32_t;
typedef char int8_t;
typedef short int int16_t;
typedef long int32_t;

/*
 * package information for robot-v2
*/
#pragma pack(push)
#pragma pack(1)
//typedef struct rbNode{
//	uint16_t id;
//	int16_t  magX;
//	int16_t  magY;
//	int16_t  maxX;
//	int16_t  minX;
//	int16_t  maxY;
//	uint8_t  minY;
//	uint16_t crc16Res;
//}rbNode;

typedef struct rbNode{
	uint16_t id;           //ID of robot
	int16_t  speedL;       //left wheel speed of robot
	int16_t  speedR;       //right wheel speed of robot
	int16_t  dir;          //direction angle according to x axis
	int16_t  locationX;    //x location
	int16_t  locationY;    //y location
	uint8_t  infSensor;    //Infra-Red sensor
	uint16_t crc16Res;     //checksum value
}rbNode;
#pragma pack(pop)

typedef struct dataPack{
	uint8_t nodeID;
    signed long timeTick;
	uint16_t r2B1;
	uint16_t r2B2;
	uint16_t angle2n;
	uint32_t xValue;
	uint32_t yValue;
}dataPack;

extern void SerialTest(int com_id);
extern void DispPackInfo(uint16_t id, FILE* fp);

#endif
