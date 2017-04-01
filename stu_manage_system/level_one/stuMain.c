#include "myStu.h"

int main(){

    // ���ÿ���̨���ڴ�С
    system("mode con cols=107 lines=40");

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
    if(fopen_s(&fp , "sqldata" , "r+b")){
        printf("�����ļ���ʧ��\t\n");
        exit(1);
    }

    printStart();
    int nFirstSelete;
    while(scanf_s("%d" , &nFirstSelete) != EOF){
        switch(nFirstSelete){
            case QUIT:
                // �ͷſռ䡢�ر��ļ�
                exitStu(fp);
                break;
            case CREATE:
                newStu(fp);
                break;
            case ECHO:
                echoFile(fp, FINDALL);
                break;
            case DEL:
                delStu(fp);
                break;
            case FIND:
                findStu(fp);
                break;
            case COUNT:
                countStuInfo(fp);
                break;
            case MODIFY:
                modifyStu(fp);
                break;
            case VIEWMEM:
                echoMem(fp);
                break;
            case SORTMEM:
                break;
            default:
                break;
        }
        printStart();
    }

    // �ͷſռ䡢�ر��ļ�
    exitStu(fp);
    return 0;
}

/*
�������ܣ�
    ��ӡ��ʼѡ��
������
    ��
����ֵ��
    ��
*/
void printStart(){
    printf("%d.�½�\t\n" , CREATE);
    printf("%d.�������\t\n" , ECHO);
    printf("%d.ɾ��\t\n" , DEL);
    printf("%d.����\t\n" , FIND);
    printf("%d.ͳ��\t\n" , COUNT);
    printf("%d.�޸�\t\n" , MODIFY);
    printf("%d.�鿴�洢���\t\n" , VIEWMEM);
    printf("%d.��Ƭ����\t\n" , SORTMEM);
    printf("%d.�˳�\t\n" , QUIT);
    printf("������ѡ�\t\n");
}

/*
�������ܣ�
    �ر��ļ�
������
    *fp   : �����ļ�ָ��
����ֵ��
    ��
*/
void exitStu(FILE *fp){
    // �ر��ļ�
    fclose(fp);
    fclose(stdin);
#ifdef REOUT
    fclose(stdout);
#endif
}