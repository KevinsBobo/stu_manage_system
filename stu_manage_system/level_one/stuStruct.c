#include "myStu.h"

/*
�������ܣ�
    �ͷŽṹ����ָ����ָ����ڴ�
������
    *pStu : ָ��ѧ����Ϣ�ṹ���ָ��
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
