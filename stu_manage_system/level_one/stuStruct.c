#include "myStu.h"

/*
�������ܣ�
    ����ѧ����Ϣ�ṹ��������Ϣ���ļ��д洢��Ҫ�Ĵ�С
    �����ṹ��ֵ���ṹ���е� nStuLen
������
    *pStu : ָ��ѧ����Ϣ�ṹ���ָ��
    nChLen: ��չ����
����ֵ��
    ��
*/
void countStuLen(stuStruct *pStu, ushort nChLen){
    if(pStu == NULL){
        return;
    }
    // �ṹ��ʵ�ʴ�С
    pStu->nStuLen = sizeof(*pStu) + nChLen - (nChLen % ALIGNED);
}

/*
�������ܣ�
    ����ѧ����Ϣ�ṹ����ԭ�ȵ�ѧ�š��������绰��ϢΪ��ͨ�ַ���
������
    *pStu    : ָ��ѧ����Ϣ�ṹ���ָ��
    *nLenArr : ����ԭ�����ݳ��ȵ�һά����ָ��
    *szSave[]: ָ����Ҫ�����Ϣ�Ķ�ά����ָ��
����ֵ��
    ��
*/
void saveStuPInfo(stuStruct *pStu ,
                  ushort *nLenArr,
                  uchar szSave[][MAXINFOLEN]){
    if(pStu == NULL || nLenArr == NULL || szSave == NULL){
        return;
    }

    // ����ѧ����Ϣ
    if(pStu->nIdLen != 0){
        memcpy_s(szSave[0] , pStu->nIdLen ,
                 pStu->szInfoArr , pStu->nIdLen);
        szSave[0][ pStu->nIdLen ] = '\0';
        nLenArr[ 0 ] = pStu->nIdLen;
    }
    // ����������Ϣ
    if(pStu->nNameLen != 0){
        memcpy_s(szSave[1] , pStu->nNameLen ,
                 (pStu->szInfoArr)+(pStu->nIdLen),
                 pStu->nNameLen);
        szSave[1][ pStu->nNameLen ] = '\0';
        nLenArr[ 1 ] = pStu->nNameLen;
    }
    // ����绰��Ϣ
    if(pStu->nTelLen != 0){
        memcpy_s(szSave[2] , pStu->nTelLen ,
                 (pStu->szInfoArr) + (pStu->nIdLen) +
                 (pStu->nNameLen), pStu->nTelLen);
        szSave[2][ pStu->nTelLen ] = '\0';
        nLenArr[ 2 ] = pStu->nTelLen;
    }
}

/*
�������ܣ�
    ͨ�������ѡ������ѧ�š��������绰
    �ڱ�����֮ǰ���ú���Ӧ������㹻�Ľṹ��ռ�
������
    *pStu   : ָ��ѧ����Ϣ�Ľṹ��
    nSelect : ����ѡ�0��ѧ�� 1������ 2���绰��
    *szTemp : ���������ַ���
    nLen    : �ַ�������
����ֵ��
    ��
*/
void setStuPInfo(stuStruct *pStu , uint nSelect , uchar *szTemp , uint nLen){
    if(pStu == NULL){
        return;
    }
    if(szTemp == NULL){
        return;
    }

    switch(nSelect){
        case ID:
            // ����ѧ��
            memcpy_s(pStu->szInfoArr, nLen, szTemp, nLen);
            pStu->nIdLen = nLen;
            break;
        case NAME:
            // ��������
            memcpy_s((pStu->szInfoArr) + (pStu->nIdLen) , nLen ,
                     szTemp , nLen);
            pStu->nNameLen = nLen;
            break;
        case TEL:
            // ���õ绰
            memcpy_s((pStu->szInfoArr) + (pStu->nIdLen) + (pStu->nNameLen),
                     nLen, szTemp, nLen);
            pStu->nTelLen = nLen;
            break;
        default:
            break;
    }
}

/*
�������ܣ�
    �ڶ��д���һ��ѧ����Ϣ�ṹ�� ��Ҫ�����븳ֵ
    ���ս��ṹ����Ϣд���ļ�
������
    *fp �����ļ�ָ��
����ֵ��
    ָ��ṹ���ָ��
*/
stuStruct *newStu(FILE *fp){
    // ���ڴ���û������ѧ�š��������绰
    uchar szTempInfo[3][ MAXINFOLEN ];
    // ���ڴ��ѧ�š��������绰�ĳ���
    ushort nInfoLen[ 3 ] = { 0 };
    // ������Ϣ�ܳ���
    ushort nInfoCount = 0;

    // Ҫ������ѧ�š��������绰
    printf("������ѧ�ţ�\t\n");
    scanf_s("%s" , szTempInfo[ID], MAXINFOLEN - 1 );
    printf("������������\t\n");
    scanf_s("%s" , szTempInfo[NAME], MAXINFOLEN - 1 );
    printf("������绰��\t\n");
    scanf_s("%s" , szTempInfo[TEL], MAXINFOLEN - 1 );

    // ����ѧ�ų���
    nInfoLen[ ID ] = strlen(szTempInfo[ ID ]);
    // ������������
    nInfoLen[ NAME ] = strlen(szTempInfo[ NAME ]);
    // ����绰����
    nInfoLen[ TEL ] = strlen(szTempInfo[ TEL ]);
    // �����ܳ���
    nInfoCount = nInfoLen[ ID ] + nInfoLen[ NAME ] + nInfoLen[ TEL ];
    
    // ����ѧ���ṹ���ڴ�
    // ���� - (nInfoCount % ALIGNED) ��Ϊ�˶���ṹ�嵽�̶��ֽ�
    stuStruct *pStuTemp = (stuStruct *)malloc(sizeof(stuStruct)
                                              + nInfoCount -
                                              (nInfoCount % ALIGNED));
    if(pStuTemp == NULL){
        printf("�ڴ����ʧ��\t\n");
        exit(1);
    }

    // ��ѧ��д��ṹ����
    setStuPInfo(pStuTemp , ID , szTempInfo[ ID ] , nInfoLen[ ID ]);
    // ������д��ṹ����
    setStuPInfo(pStuTemp , NAME , szTempInfo[ NAME ] , nInfoLen[ NAME ]);
    // ���绰д��ṹ����
    setStuPInfo(pStuTemp , TEL , szTempInfo[ TEL ] , nInfoLen[ TEL ]);

    // ���ñ�ɾ����־λ
    pStuTemp->isDel = 0;

    // ��������
    printf("���������գ���ʽΪ��yyyy-mm-dd����\t\n");
    scanf_s("%u-%u-%u" , &(pStuTemp->nYear),
                       &(pStuTemp->nMonth),
                       &(pStuTemp->nDay));

    // ����C���Գɼ�
    printf("������C���Գɼ�����ȷ��С�����һλ����\t\n");
    scanf_s("%f" , &(pStuTemp->fScore));

    // ���㲢�洢�ṹ�峤��
    countStuLen(pStuTemp, nInfoCount);

    // ���ṹ��д���ļ���
    writeFile(fp , pStuTemp);

    return pStuTemp;
}