#include <windows.h>
#include <stdio.h>
#include "../inc/Robot.h"

extern rbNode bCastInfo[NROBOT];
extern dataPack dataInfo[NROBOT];

//void DispPackInfo(uint16_t id, FILE* fp){
//    if(id < 0){
//        printf("id(%d) error!\n",id);
//        return;
//    }
//	uint16_t index = id - 1;
//    char str[256] = {'\0'};
//#if 1
///*##########################Received Data###############################*/
//	sprintf_s(str, "%d: {(%d,%d),%d,(%d,%d),%d", id, bCastInfo[index].locationX, bCastInfo[index].locationY,\
//		bCastInfo[index].dir, bCastInfo[index].speedL, bCastInfo[index].speedR,bCastInfo[index].crc16Res);
//   fprintf_s(fp, "%s", str);
//   printf("%s",str);
//   printf("}\n");
//   fprintf_s(fp, "}\n");
///*##########################Collect Data###############################*/
//#endif 
//}

void Log(char *str){
   printf("%s",str);  
   FILE *fp = fopen("log.txt", "w");
   if(fp == NULL){
    printf("Open failed!\n");
    return;
   }
   fclose(fp);
}

