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
void setStuPInfo(stuStruct *pStu ,
                 uint nSelect ,
                 uchar *szTemp ,
                 uint nLen){
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
void newStu(FILE *fp){
    // ���ڴ���û������ѧ�š��������绰
    uchar szTempInfo[3][ MAXINFOLEN ];
    // ���ڴ��ѧ�š��������绰�ĳ���
    ushort nInfoLen[ 3 ] = { 0 };
    // ������Ϣ�ܳ���
    ushort nInfoCount = 0;

    printC('-' , 110);
    // Ҫ������ѧ�š��������绰
    printf(" ������ѧ�ţ�\t\n");
    scanf_s("%s" , szTempInfo[ID], MAXINFOLEN - 1 );
    fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[ID]);
#endif

    printf(" ������������\t\n");
    scanf_s("%s" , szTempInfo[NAME], MAXINFOLEN - 1 );
    fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[NAME]);
#endif
    printf(" ������绰��\t\n");
    scanf_s("%s" , szTempInfo[TEL], MAXINFOLEN - 1 );
    fflush(stdin);

#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[TEL]);
#endif

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
        exitStu(fp);
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
    printf(" ���������գ���ʽΪ��yyyy-mm-dd����\t\n");
    scanf_s("%hu-%hu-%hu" , &(pStuTemp->nYear),
                       &(pStuTemp->nMonth),
                       &(pStuTemp->nDay));
    fflush(stdin);
#ifdef DEBUG
        printf("%hu-%hu-%hu\t\n\t\n" , pStuTemp->nYear,
                                       pStuTemp->nMonth,
                                       pStuTemp->nDay);
#endif
    // ������
    while((pStuTemp->nYear < 1900 || pStuTemp->nYear > 2017) ||
          (pStuTemp->nMonth < 1 || pStuTemp->nMonth > 12) ||
          (pStuTemp->nDay < 1 || pStuTemp->nDay   > 31)){
        printf(" �����������������루��ʽΪ��yyyy-mm-dd����\t\n");
        scanf_s("%hu-%hu-%hu" , &(pStuTemp->nYear),
                           &(pStuTemp->nMonth),
                           &(pStuTemp->nDay));
        fflush(stdin);
#ifdef DEBUG
        printf("%hu-%hu-%hu\t\n\t\n" , pStuTemp->nYear,
                                       pStuTemp->nMonth,
                                       pStuTemp->nDay);
#endif
    }
    // ����C���Գɼ�
    printf(" ������C���Գɼ�����ȷ��С������λ����\t\n");
    scanf_s("%f" , &(pStuTemp->fScore));
    fflush(stdin);
#ifdef DEBUG
        printf("%f\t\n\t\n" , pStuTemp->fScore);
#endif
    // ������
    while(pStuTemp->fScore < 0.0 || pStuTemp->fScore > 100.0){
        printf(" �����������������룺\t\n");
        scanf_s("%f" , &(pStuTemp->fScore));
        fflush(stdin);
#ifdef DEBUG
        printf("%f\t\n\t\n" , pStuTemp->fScore);
#endif
    }

    // ���㲢�洢�ṹ�峤��
    countStuLen(pStuTemp, nInfoCount);

    // ���ṹ��д���ļ���
    writeFile(fp , pStuTemp);

    // �ͷŽṹ��ռ�
    free(pStuTemp);

    printC('-' , 110);
    printf(" �½��ɹ���\t\n");
}

/*
�������ܣ�
    ��ӡѧ���ṹ����Ϣ
������
    *pStu  : ָ��ѧ����Ϣ�ṹ���ָ��
    nPreId : �ýṹ�����
����ֵ��
    ��
*/
void printStuInfo(stuStruct *pStu , int nPreId){
        // ����ѧ�š��������绰�Ķ�ά����
        uchar szStuArr[ 3 ][ MAXINFOLEN ];
        ushort nStuArrLen[ 3 ];
        ushort age = 0;
        time_t nowTime;
        struct tm *pNowTime;
        // ����ѧ�š��������绰Ϊ��ͨ�ַ���
        saveStuPInfo(pStu , nStuArrLen , szStuArr);
        // ��ȡ��ǰʱ��
        time(&nowTime);
        pNowTime = localtime(&nowTime);
        printf(" %d. ѧ�ţ�%s | ������%s | �绰��%s | ���䣺%d | C���Գɼ���%.2f\t\n" ,
               nPreId , szStuArr[ ID ] , szStuArr[ NAME ] , szStuArr[ TEL],
               pNowTime->tm_year + 1900 - (int)pStu->nYear, pStu->fScore);
}

/*
�������ܣ�
    ͨ���û���������в��Ҳ���
������
    *fp : ָ�������ļ���ָ��
����ֵ��
    ��
*/
void findStu(FILE *fp){
    int nSelect;
    int nPreId = 0;
    uchar szBuff[ MAXINFOLEN ];

    printC('-' , 110);
    printf("%40c1.����Ų���\t\n%40c2.��ѧ��ģ������\t\n%40c3.������ģ������\t\n%40c4.���绰ģ������\t\n%40c0.����\t\n", ' ', ' ', ' ', ' ', ' ');
    printC('-' , 110);
    printf(" ��������ţ�\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif

    while(nSelect < 0 || nSelect > 4){
            printf(" �����������������룺\t\n");
            scanf("%d" , &nSelect);
            fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    }

    if(nSelect == 1){
        printf(" ������Ҫ���ҵ�ѧ����ţ�\t\n");
        scanf("%d" , &nPreId);
        fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif

        while(nPreId <= 0){
            printf(" �����������������룺\t\n");
            scanf("%d" , &nPreId);
            fflush(stdin);
#ifdef DEBUG
            printf("%d\t\n\t\n" , nSelect);
#endif
        }
        echoFile(fp , nPreId);
    }
    else{
        printf(" ������Ҫ���ҵ����ݣ�\t\n");
        scanf_s("%s" , szBuff , MAXINFOLEN - 1);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szBuff);
#endif
        
        printC('-' , 110);
        findFile(fp , szBuff , nSelect);
        printC('-' , 110);
    }
}

/*
�������ܣ�
    �����û������޸�ѧ����Ϣ
������
    *fp : �����ļ�ָ��
����ֵ��
    ��
*/
void modifyStu(FILE *fp){
    printf(" ���޸ĵ�ѧ���б�\t\n");
    echoFile(fp , 0);

    int nSelect;
    printf(" ������Ҫ�޸ĵ�ѧ����Ϣ��ţ�����0���˳��޸ģ���\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    
    while(nSelect < 0){
        printf(" �����������������룺\t\n");
        scanf("%d" , &nSelect);
        fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    }
    if(nSelect == 0){
        return;
    }

    system("cls");
    // ��ȡ����ӡ���ҵ���ѧ����Ϣ
    printf(" �޸ģ�\t\n");
    if(echoFile(fp , nSelect) == 0){
        return;
    }
    
    printf("%40c1.ѧ��\t\n%40c2.����\t\n%40c3.�绰\t\n%40c4.����\t\n%40c5.C���Գɼ�\t\n%40c0.�˳��޸�\t\n",
           ' ', ' ', ' ', ' ', ' ', ' ');
    printC('-' , 110);
    printf(" ������ѡ�\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    while(nSelect < 0 || nSelect > 5){
        printf(" �����������������룺\t\n");
        scanf("%d" , &nSelect);
        fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    }
    if(nSelect == 0){
        return;
    }

    // ��ʼ�޸�
    if(nSelect == 4){
        // �޸�����
        ushort nYear;
        ushort nMonth;
        ushort nDay;
        printf(" �������µ����գ���ʽΪyyyy-mm-dd����\t\n");
        scanf("%hu-%hu-%hu" , &nYear , &nMonth , &nDay);
        fflush(stdin);
#ifdef DEBUG
        printf("%hu-%hu-%hu\t\n\t\n" , nYear, nMonth, nDay);
#endif
        // ������
        while((nYear < 1900 || nYear > 2017) ||
              (nMonth < 1 || nMonth > 12) ||
              (nDay < 1 || nDay   > 31)){
            printf(" �����������������루��ʽΪ��yyyy-mm-dd����\t\n");
            scanf("%hu-%hu-%hu" , &nYear , &nMonth , &nDay);
            fflush(stdin);
#ifdef DEBUG
            printf("%hu-%hu-%hu\t\n\t\n" , nYear, nMonth, nDay);
#endif
        }
        // ���ļ�ָ��ƫ�Ƶ���ݵ�λ��
        fseek(fp , (long)sizeof(ushort) * 5 , SEEK_CUR);
        // �������
        fwrite(&nYear, sizeof(ushort), 1, fp);
        // ���ļ�ָ��ƫ�Ƶ��·ݵ�λ��
        fseek(fp , (long)sizeof(ushort) , SEEK_CUR);
        // �����·�
        fwrite(&nMonth , sizeof(ushort) , 1 , fp);

        // ���ļ�ָ��ƫ�Ƶ����ڵ�λ��
        fseek(fp , (long)sizeof(ushort) , SEEK_CUR);
        // ��������
        fwrite(&nDay , sizeof(ushort) , 1 , fp);
        printf(" �޸ĳɹ���\t\n");
    }
    else if(nSelect == 5){
        // �޸�C���Գɼ�
        float fScore;
        printf(" �������µ�C���Գɼ�����ȷ��С�������λ����\t\n");
        scanf("%f" , &fScore);
        fflush(stdin);
#ifdef DEBUG
        printf("%f\t\n\t\n" , fScore);
#endif
        // ������
        while(fScore < 0.0 || fScore > 100.0){
            printf(" �����������������룺\t\n");
            scanf("%f" , &fScore);
            fflush(stdin);
#ifdef DEBUG
            printf("%f\t\n\t\n" , fScore);
#endif
        }

        // ���ļ�ָ��ƫ�Ƶ��ɼ���λ��
        fseek(fp, (long)sizeof(ushort) * 8, SEEK_CUR);
        // ���³ɼ�
        fwrite(&fScore , sizeof(float), 1, fp);
        printf(" �޸ĳɹ���\t\n");
    }
    else{
        // �޸�ѧ�š��������绰
        resetPInfo(fp , nSelect);
    }

    // ���ļ�ָ��ָ���ļ���ʼλ��
    fseek(fp , 0 , SEEK_SET);
}

/*
�������ܣ�
    ��������ѧ�š��������绰
������
    *fp    : �����ļ�ָ��
    nSelect: �޸�ѡ��
����ֵ��
    ��
*/
void resetPInfo(FILE *fp , int nSelect){
    // �޸�ѧ�š��������绰
    // ���ļ��ж���ѧ����Ϣ���ṹ��
    stuStruct *pStu = readFile(fp);
    if(pStu == NULL){
        printf(" �޸�ʧ��\t\n");
        return;
    }
    // ���ļ�ָ��ָ�ظýṹ�����ļ��е���ʼλ��
    fseek(fp , -(long)(pStu->nStuLen), SEEK_CUR);

    // ���ڴ���û������ѧ�š��������绰
    uchar szTempInfo[3][ MAXINFOLEN ];
    // ���ڴ��ѧ�š��������绰�ĳ���
    ushort nInfoLen[ 3 ] = { 0 };
    // ������Ϣ�ܳ���
    ushort nInfoCount = 0;
    // ����ԭ��������Ϊ��ͨ�ַ���
    saveStuPInfo(pStu , nInfoLen , szTempInfo);

    if(nSelect == 1){
        printf(" �������µ�ѧ�ţ�\t\n");
        scanf("%s" , szTempInfo[ ID ]);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[ID]);
#endif
    }
    else if(nSelect == 2){
        printf(" �������µ�������\t\n");
        scanf("%s" , szTempInfo[ NAME ]);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[NAME]);
#endif
    }
    else{
        printf(" �������µĵ绰��\t\n");
        scanf("%s" , szTempInfo[ TEL ]);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[TEL]);
#endif
    }
    
    // ������ݳ���û����д��ԭ����λ�ã�
    // ����ɾ��ԭ���ݣ�����д���ļ�
    if(strlen(szTempInfo[ ID ]) == nInfoLen[ ID ] &&
       strlen(szTempInfo[NAME]) == nInfoLen[NAME] &&
       strlen(szTempInfo[TEL])  == nInfoLen[TEL]){
        // ���µ����ݱ��浽�ṹ����
        // ��ѧ��д��ṹ����
        setStuPInfo(pStu , ID , szTempInfo[ ID ] , nInfoLen[ ID ]);
        // ������д��ṹ����
        setStuPInfo(pStu , NAME , szTempInfo[ NAME ] , nInfoLen[ NAME ]);
        // ���绰д��ṹ����
        setStuPInfo(pStu , TEL , szTempInfo[ TEL ] , nInfoLen[ TEL ]);
        
        // д��ǰ�������ļ�ָ��
        fseek(fp , 0 , SEEK_CUR);

        // д���ļ�
        fwrite(pStu , sizeof(uchar) , pStu->nStuLen , fp);
    }
    else{

        nInfoLen[ ID ] = strlen(szTempInfo[ ID ]);
        nInfoLen[ NAME ] = strlen(szTempInfo[ NAME ]);
        nInfoLen[ TEL ] = strlen(szTempInfo[ TEL ]);
        nInfoCount = nInfoLen[ ID ] +
                     nInfoLen[ NAME ] +
                     nInfoLen[ TEL ];

        // �����µ�ѧ���ṹ���ڴ�
        // ���� - (nInfoCount % ALIGNED) ��Ϊ�˶���ṹ�嵽�̶��ֽ�
        stuStruct *pStuTemp = (stuStruct *)malloc(sizeof(stuStruct)
                                                  + nInfoCount -
                                                  (nInfoCount % ALIGNED));
        if(pStuTemp == NULL){
            printf(" �޸�ʧ��\t\n");
            return;
        }
        // ���㲢�洢�ṹ�峤��
        countStuLen(pStuTemp, nInfoCount);
        // ���ɽṹ���е���Ϣ�����µĽṹ����
        memcpy_s(pStuTemp , pStuTemp->nStuLen, pStu,
                 (pStu->nStuLen > pStuTemp->nStuLen) ? pStuTemp->nStuLen :
                                                       pStu->nStuLen);
        // ���㲢�洢�ṹ�峤��
        countStuLen(pStuTemp, nInfoCount);

        // ���µ����ݱ��浽�ṹ����
        // ��ѧ��д��ṹ����
        setStuPInfo(pStuTemp , ID , szTempInfo[ ID ] , nInfoLen[ ID ]);
        // ������д��ṹ����
        setStuPInfo(pStuTemp , NAME , szTempInfo[ NAME ] , nInfoLen[ NAME ]);
        // ���绰д��ṹ����
        setStuPInfo(pStuTemp , TEL , szTempInfo[ TEL ] , nInfoLen[ TEL ]);

        // ɾ���ɵ�ѧ����Ϣ
        delFile(fp);
        // д���µ�ѧ����Ϣ
        writeFile(fp , pStuTemp);

        free(pStuTemp);
        printf(" �޸ĳɹ���\t\n");
    }
}

/*
�������ܣ�
    �����û�����ɾ��ָ��ѧ����Ϣ
������
    *fp : �����ļ�ָ��
����ֵ��
    ��
*/
void delStu(FILE *fp){
    printf(" ��ɾ����ѧ���б�\t\n");
    echoFile(fp , 0);

    int nSelect;
    printf(" ������Ҫɾ����ѧ����Ϣ��ţ�����0���˳�ɾ������\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    
    if(nSelect == 0){
        return;
    }

    // ��ȡ����ӡ���ҵ���ѧ����Ϣ
    printf(" ɾ����\t\n");
    if(echoFile(fp , nSelect) == 0){
        return;
    }

    // ɾ��ָ����ѧ����Ϣ
    delFile(fp);
    sortMemJustDel(fp);
    printf(" ɾ���ɹ���\t\n");
}