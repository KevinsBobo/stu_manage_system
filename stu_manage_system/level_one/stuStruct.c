#include "myStu.h"

/*
函数功能：
    释放结构体中指针所指向的内存
参数：
    *pStu : 指向学生信息结构体的指针
*/
void freeStuArr(stuStruct *pStu){
    if(pStu->pszId != NULL){
        free(pStu->pszId);
        pStu->nIdLen = 0;
    }
    if(pStu->pszName != NULL){
        free(pStu->pszName);
        pStu->nNameLen = 0;
    }
    if(pStu->pszTel != NULL){
        free(pStu->pszTel);
        pStu->nTelLen = 0;
    }
}
