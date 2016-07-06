
#ifndef _ROBOT_H
#define _ROBOT_H


const int NROBOT = 6;

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long uint32;

typedef uint32  u32;
typedef uint16 u16;
typedef uint8  u8;


typedef struct robotPos{
  float x;        //4bytes
  float y;        //4bytes
}robotPos;                //8bytes

//package information 28 Bytes
typedef struct rbNode
{
	u8 nodeID;           //1 byte
	robotPos rpos;       //8 bytes
	float angle2n;       //4 bytes
	u8 isActive;         //1 byte
	u8 isLeaderOK;       //1 byte
	u8 isReady;          //1 bytes
	u8 isFoundPath;      //1 byte
	u8 type;		     //1 byte
	u8 isStop;           //1 byte
	u8 nbrList[NROBOT];  //6 byte
}rbNode;

typedef struct dataPack{
    u8 nodeID;
    signed long timeTick;
  	float r2B1;
	float r2B2;
	float angle2n;
	u32 xValue;
	u32 yValue;
}dataPack;

extern void SerialTest(int com_id);
extern u8 GetRobotID(u8 id);
extern robotPos GetCoordinate(u8 id);
extern float GetNorthAngle(u8 id);
extern u8 GetActiveInfo(u8 id);
extern u8 GetReadyInfo(u8 id);
extern u8 GetPathFoundInfo(u8 id);
extern u8 GetRobotType(u8 id);
extern u8 GetStopInfo(u8 id);
extern void DispNbrList(u8 id);
extern void DispPackInfo(int id,FILE* fp);
extern void Log(char *str);

#endif
