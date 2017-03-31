#include "myStu.h"

/*
�������ܣ�
    ���ṹ����Ϣд�뵽�ļ���
������
    *fp   : �����ļ�ָ��
    *pStu : ѧ���ṹ��ָ��
����ֵ��
    ��
*/
void writeFile(FILE *fp , stuStruct *pStu){
    if(fp == NULL){
        return;
    }
    if(pStu == NULL){
        return;
    }

    // ���ļ�ָ�������ļ�ĩβ
    fseek(fp , 0 , SEEK_END);

    // д������
    fwrite(pStu , sizeof(char) , pStu->nStuLen , fp);
}

/*
�������ܣ�
    ���ļ��ж�ȡָ������λ�õ����ݵ��ṹ����
������
    *fp : �����ļ�ָ��
����ֵ��
    ָ���ڶ��е�ѧ����Ϣ�ṹ��ĵ�ַ
*/
stuStruct *readFile(FILE *fp){
    if(fp == NULL){
        return NULL;
    }
    stuStruct *pStuTemp = NULL;
    ushort nStuLen = 0;

    // ��ȡ�ṹ���С
    if(fread_s(&nStuLen , sizeof(nStuLen) , sizeof(ushort) , 1 , fp)
       == 0){
        return NULL;
    }
    // Ϊ�ṹ�����ռ�
    pStuTemp = (stuStruct *)malloc(nStuLen * sizeof(uchar));
    if(pStuTemp == NULL){
        printf("�ڴ����ʧ��\t\n");
        exit(1);
    }
    // ��ָ���ûؽṹ����ʼλ��
    fseek(fp , -(long)(sizeof(ushort)), SEEK_CUR);
    // ���ļ��ж�ȡ�ṹ�����ݵ��ṹ���ڴ���
    fread_s(pStuTemp , nStuLen , sizeof(uchar) , nStuLen , fp);
    
    return pStuTemp;
}

/*
�������ܣ�
    ɾ���ļ����ļ�ָ������λ�õ�ѧ���ṹ����Ϣ
������
    *fp : �����ļ�ָ��
����ֵ��
    ��
*/
void delFile(FILE *fp){
    if(fp == NULL){
        return;
    }
    // ��ָ��ƫ����ɾ����־λ
    fseek(fp , (long)(sizeof(ushort)) , SEEK_CUR);

    if(fp->_ptr == NULL){
        return;
    }
    // ��ɾ����־λ��Ϊ 0xFFFF
    ushort isDel = 0xFFFF;
    fwrite(&isDel, sizeof(ushort), 1, fp);

    // ��ָ���ûظýṹ�����ļ��е���ʼλ��
    fseek(fp , -(long)(sizeof(ushort) * 2) , SEEK_CUR);
}

/*
�������ܣ�
    ��ӡ����δ��ɾ����ѧ����Ϣ
������
    *fp : �����ļ�ָ��
����ֵ��
    ��
*/
void echoFile(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    stuStruct *pStu;
    // ���
    int nId = 1;
    // ����ѧ�š��������绰�Ķ�ά����
    uchar szStuArr[ 3 ][ MAXINFOLEN ];
    ushort nStuArrLen[ 3 ];
    ushort age = 0;
    time_t nowTime;
    struct tm *pNowTime;
    // ѭ����ӡ
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // ��ɾ�������ݲ���ӡ
            continue;
        }
        // ����ѧ�š��������绰Ϊ��ͨ�ַ���
        saveStuPInfo(pStu , nStuArrLen , szStuArr);
        // ��ȡ��ǰʱ��
        time(&nowTime);
        pNowTime = localtime(&nowTime);
        printf("��ţ�%d\t\nѧ�ţ�%s\t\n������%s\t\n�绰��%s\t\n���䣺%d\t\nC���Գɼ���%.2f\t\n\t\n" ,
               nId , szStuArr[ ID ] , szStuArr[ NAME ] , szStuArr[ TEL],
               pNowTime->tm_year + 1900 - (int)pStu->nYear, pStu->fScore);
        ++nId;
    }
}