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

    // ���ļ�ָ�������ļ���ʼλ��
    fseek(fp , 0 , SEEK_SET);

    ushort nReadLen , isEmp, nTemp;
    // �������ݿ飬Ѱ�Һ��ʵ����ݿ�
    while(fread_s(&nReadLen , sizeof(ushort) , sizeof(ushort) , 1 , fp)
          != 0){
        // ����ȡ���ݿ��С����
        if(nReadLen < pStu->nStuLen){
            fseek(fp , (long)(nReadLen - sizeof(ushort)) , SEEK_CUR);
            continue;
        }
        // ��ȡ��־λ
        if(fread_s(&isEmp , sizeof(ushort) , sizeof(ushort) , 1 , fp) == 0){
            break;
        }
        // ����ȡ���ݿ鲻�ǿտ�
        if(isEmp == 0){
            fseek(fp , (long)(nReadLen - sizeof(ushort) * 2) , SEEK_CUR);
            continue;
        }
        // �����ݿ��С��Ҫд���ѧ����Ϣ��С��ͬ
        if(nReadLen == pStu->nStuLen){
            fseek(fp , -(long)(sizeof(ushort) * 2) , SEEK_CUR);
            break;
        }
        // �����ݿ��С����Ҫд���ѧ����Ϣ��С
        nTemp = nReadLen - pStu->nStuLen;

        // ��ָ���ƶ�����Ҫ�ָ�����ݿ��λ��
        fseek(fp , (long)(nReadLen - sizeof(ushort) * 2 - nTemp) , SEEK_CUR);
        // ����ȡ��Ŀ����ݿ�д�����С����
        fwrite(&nTemp , sizeof(ushort) , 1, fp);
        // ��ָ���ƻظÿ����ļ�����ʼλ��
        fseek(fp , -(long)(sizeof(ushort)) , SEEK_CUR);
        // �������ݿ�����Ϊɾ��״̬
        delFile(fp);
        
        // ��ָ���ƻ��ʺ�д���λ��
        fseek(fp , -(long)(nReadLen - nTemp) , SEEK_CUR);
        break;
    }

    // �����ļ�ָ��
    fseek(fp , 0 , SEEK_CUR);
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
    if(fp == NULL || feof(fp)){
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
    if(fp == NULL || feof(fp)){
        return;
    }
    // �ж��ļ��Ƿ����������ָ��ƫ����ɾ��λ
    ushort nIsEof = 0;
    if(fread_s(&nIsEof , sizeof(ushort) , sizeof(ushort) , 1 , fp)
       == 0 || nIsEof == 0){
        return;
    }

    // BUG: ����������ָ���������д���ļ�
    fseek(fp , 0 , SEEK_CUR);

    // ��ɾ����־λ��Ϊ 0xFFFF
    ushort isDel = 0xFFFF;
    fwrite(&isDel, sizeof(ushort), 1, fp);

    // ��ָ���ûظýṹ�����ļ��е���ʼλ��
    fseek(fp , -(long)(sizeof(ushort) * 2) , SEEK_CUR);
}

/*
�������ܣ�
    ��ӡ����δ��ɾ����ѧ����Ϣ
    ���ӡ�������ڴ�ӡ���ָ��ָ���ļ�ͷ��
    ���ӡָ�����ӡ���ָ��ָ��ýṹ�����ļ��е���ʼλ��
������
    *fp    : �����ļ�ָ��
    nPreId : �縳ֵΪ0���ӡ����ѧ����Ϣ
             ����ֻ��ӡ��nPreId��ѧ����Ϣ
����ֵ��
    0 û�в��ҵ�����0 ���ҵ�
*/
int echoFile(FILE *fp, int nPreId){
    if(fp == NULL){
        return 0;
    }
    
    // ���ļ�ָ��ָ���ļ���ʼλ��
    fseek(fp , 0 , SEEK_SET);
    stuStruct *pStu;
    // ���
    int nId = 1;
    // ѭ����ӡ
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // ��ɾ�������ݲ���ӡ
            // �ͷſռ�
            free(pStu);
            continue;
        }
        if(nPreId == 0){
            printStuInfo(pStu , nId);
        }
        else if(nId == nPreId){
            printStuInfo(pStu , nId);
            ++nId;
            break;
        }
        ++nId;
        // �ͷſռ�
        free(pStu);
    }
    // ѭ����ɺ� nId ���û�б仯��˵���ļ���û��ѧ����Ϣ
    if(nId == 1){
        printf("�ļ���û���κ�ѧ����Ϣ\t\n");
        fseek(fp , 0 , SEEK_SET);
        return 0;
    }
    // �ж��Ƿ��ҵ�ָ�������Ϣ
    if(nPreId != 0 && nId <= nPreId){
        printf("��������̫���ˣ�\t\n");
        return 0;
    }
    else if(pStu != NULL){
        // ����ҵ����ļ�ָ��ָ��ýṹ�����ļ��е���ʼλ��
        fseek(fp , -(long)(pStu->nStuLen) , SEEK_CUR);
        return 1;
    }
    
    // ���ļ�ָ��ָ���ļ�ͷ
    fseek(fp , 0 , SEEK_SET);
    return 1;
}

/*
�������ܣ�
    ���ļ��в��ҽṹ�壬
    ��ָ��ֻ����ƥ�䵽�ĵ�һ��ѧ����Ϣ���ҵ����ļ�ָ������
    ���ҵ��Ľṹ�����ļ��е���ʼλ�ã�
    ������ҽ������ļ�ָ��ָ���ļ���ʼλ��
������
    *fp     : �����ļ�ָ��
    *szBuff : �����ҵ��ַ���
    nSelect : ����ģʽ FINDALL FINDONE
����ֵ��
    0 û�в��ҵ�����0 ���ҵ�
*/
int findFile(FILE *fp , uchar *szBuff, int nSelect){
    if(fp == NULL || szBuff == NULL){
        return 0;
    }

    fseek(fp , 0 , SEEK_SET);
    stuStruct *pStu;
    // ����ѧ�š��������绰�Ķ�ά����
    uchar szStuArr[ 3 ][ MAXINFOLEN ];
    ushort nStuArrLen[ 3 ];
    // ���
    int nId = 1;
    // �Ƿ��ҵ���Ϣ��־λ
    int isFind = 0;
    // ����
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // ��ɾ�������ݲ�����
            // �ͷſռ�
            free(pStu);
            continue;
        }
        // ����ѧ�š��������绰Ϊ��ͨ�ַ���
        saveStuPInfo(pStu , nStuArrLen , szStuArr);
        // �жϵ�ǰѧ����Ϣ�Ƿ�ΪҪ���ҵ�ѧ����Ϣ
        if(strstr(szStuArr[ ID ] , szBuff) != NULL ||
           strstr(szStuArr[ NAME ] , szBuff) != NULL ||
           strstr(szStuArr[ TEL ] , szBuff) != NULL){
            // ��ӡ
            printStuInfo(pStu , nId);
            // ���Ƿ��ҵ���־λ��Ϊ���ҵ�
            isFind = 1;
            // ���ָ���˲��ҵ�һ��ƥ�䵽����Ϣ��������ң����غ���
            if(nSelect == FINDONE){
                // ���ļ�ָ��ָ��ṹ�����ļ��е���ʼλ��
                fseek(fp , -(long)(pStu->nStuLen) , SEEK_CUR);
                return 1;
            }
        }
        ++nId;
        // �ͷſռ�
        free(pStu);
    }

    // ���ļ�ָ��ָ���ļ�ͷ��
    fseek(fp , 0 , SEEK_SET);

    // ����Ƿ��ҵ�
    if(isFind == 0){
        printf("û���ҵ�ָ����ѧ����Ϣ��");
        return 0;
    }
    else{
        return 1;
    }
}

/*
�������ܣ�
    ͳ������ѧ��������C���Գɼ���߷֡���ͷ֡�ƽ���֡��ܷ�
������
    *fp : ָ�������ļ���ָ��
����ֵ��
    ��
*/
void countStuInfo(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    // ���ļ�ָ��ָ���ļ���ʼλ��
    fseek(fp , 0 , SEEK_SET);
    stuStruct *pStu;
    // ѧ������
    uint nCount = 0;
    // ��߷�
    float fMaxScore = 0;
    // ��ͷ�
    float fMinScore = 100.00;
    // ƽ����
    double fAveScore = 0;
    // �ܷ�
    double fCouScore = 0;
    // ѭ����ӡ
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // ��ɾ�������ݲ�����
            continue;
        }
        // ������߷�
        fMaxScore = ((pStu->fScore) > fMaxScore) ?
                    pStu->fScore : fMaxScore;
        // ������ͷ�
        fMinScore = ((pStu->fScore) < fMinScore) ?
                    pStu->fScore : fMinScore;
        // �����ܷ�
        fCouScore += (double)(pStu->fScore);
        ++nCount;
    }
    // ѭ����ɺ� nCount ���û�б仯��˵���ļ���û��ѧ����Ϣ
    if(nCount == 0){
        printf("�ļ���û���κ�ѧ����Ϣ\t\n");
    }
    else{
        // ����ƽ����
        fAveScore = fCouScore / (double)nCount;
        printf("һ���У�%d ��ѧ��\t\n��߷֣�%.2f��\t\n��ͷ֣�%.2f��\t\nƽ���֣�%.2lf��\t\n�ܷ֣�%.2lf��\t\n",
               nCount, fMaxScore, fMinScore, fAveScore , fCouScore);
    }
    
    // ���ļ�ָ��ָ���ļ�ͷ
    fseek(fp , 0 , SEEK_SET);

}

/*
�������ܣ�
    ��ӡ�ļ��洢���
������
    *fp : �����ļ�ָ��
����ֵ��
    ��
*/
void echoMem(FILE *fp){
    if(fp == NULL){
        return;
    }

    // ���ļ�ָ��ָ���ļ���ʼλ��
    fseek(fp , 0 , SEEK_SET);

    ushort nMem = 0 , nTemp = 0;
    int isEmp = 0;
    long long nNum = 1;
    // ѭ����ȡ�洢���С
    while(fread_s(&nMem, sizeof(ushort), sizeof(ushort), 1, fp)
          != 0){
        // ���˿��Ƿ�ɾ��
        fread_s(&nTemp , sizeof(ushort) , sizeof(ushort), 1, fp);
        isEmp = (nTemp == 0) ? 0 : 1;
        printMem(nMem , isEmp, &nNum);

        // ���ļ�ָ��ָ����һ��
        fseek(fp , (long)(nMem - sizeof(ushort) * 2) , SEEK_CUR);
    }
    printf("\t\n");
}

/*
�������ܣ�
    ��ӡ�ڴ��
������
    nMem  : ��ӡ����
    isEmp : ��ӡ���� ��0 ���ڴ� 0 ��ʹ���ڴ�
    nNum  : �����Ѵ�ӡ���ڴ���������������
����ֵ��
    ��
*/
void printMem(ushort nMem , int isEmp, long long *nNum){
    if(nMem == 0){
        return;
    }
    char cUsed[] = "��";
    char cFree[] = "��";
    while(nMem > 0){
        printf("%s" , (isEmp == 0) ? cUsed : cFree);
        if(*nNum % 4 == 0 && *nNum % 48 != 0){
            printf(" ");
        }
        --nMem;
        ++(*nNum);
    }
}