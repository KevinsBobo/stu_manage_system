#include "myStu.h"

int main(){

#ifdef DEBUG
    // �ض�������
    freopen("data.in","r",stdin);
#ifdef REOUT
    // �ض������
    freopen("data.out","w",stdout);
#endif
#endif
    
    // �������ļ�
    FILE *fp = NULL;
    if(fopen_s(&fp , "sqldata" , "rb+")){
        printf("�����ļ���ʧ��\t\n");
        exit(1);
    }

    int nFirstSelete;
    stuStruct *pStu = NULL;
    printf("������ѡ�\t\n");
    while(scanf_s("%d" , &nFirstSelete) != EOF){
        switch(nFirstSelete){
            case CREATE:
                pStu = newStu(fp);
                break;
            case READ:
                readFile(fp);
                break;
            case ECHO:
                echoFile(fp);
                break;
            case DEL:
                delFile(fp);
                break;
            default:
                break;
        }
    }

    // �ͷŽṹ���ڴ�
    free(pStu);

    // �ر��ļ�
    fclose(fp);
    fclose(stdin);
#ifdef REOUT
    fclose(stdout);
#endif
    return 0;
}