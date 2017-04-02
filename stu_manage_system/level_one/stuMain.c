#include "myStu.h"

int main(){

    // ���ÿ���̨���ڴ�С
    system("mode con cols=115 lines=40");

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
                system("cls");
                printf("%40c�½�ѧ����Ϣ\t\n" , ' ');
                newStu(fp);
                system("pause");
                break;
            case ECHO:
                system("cls");
                printf("%40c����ѧ����Ϣ\t\n" , ' ');
                echoFile(fp, FINDALL);
                system("pause");
                break;
            case DEL:
                system("cls");
                printf("%40cɾ��ѧ����Ϣ\t\n" , ' ');
                delStu(fp);
                system("pause");
                break;
            case FIND:
                system("cls");
                printf("%40c����ѧ����Ϣ\t\n" , ' ');
                findStu(fp);
                system("pause");
                break;
            case COUNT:
                system("cls");
                printf("%40cͳ��ѧ����Ϣ\t\n" , ' ');
                countStuInfo(fp);
                system("pause");
                break;
            case MODIFY:
                system("cls");
                printf("%40c�޸�ѧ����Ϣ\t\n" , ' ');
                modifyStu(fp);
                system("pause");
                break;
            case VIEWMEM:
                system("cls");
                printf("%40c�鿴�洢���\t\n" , ' ');
                echoMem(fp);
                system("pause");
                break;
            case SORTMEM:
                system("cls");
                printf("%40c��Ƭ����\t\n" , ' ');
                sortMem(fp);
                system("pause");
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
    system("cls");
    printf("%40cѧ������ϵͳ\t\n" , ' ');
    printC('-' , 110);
    printf("%40c%d.�½�\t\n" , ' ', CREATE);
    printf("%40c%d.�������\t\n" , ' ', ECHO);
    printf("%40c%d.ɾ��\t\n" , ' ', DEL);
    printf("%40c%d.����\t\n" , ' ', FIND);
    printf("%40c%d.ͳ��\t\n" , ' ', COUNT);
    printf("%40c%d.�޸�\t\n" , ' ', MODIFY);
    printf("%40c%d.�鿴�洢���\t\n" , ' ', VIEWMEM);
    printf("%40c%d.��Ƭ����\t\n" , ' ', SORTMEM);
    printf("%40c%d.�˳�\t\n" , ' ', QUIT);
    printC('-' , 110);
    printf(" ������ѡ�\t\n");
}

/*
�������ܣ�
    �ظ���ӡͬһ���ַ�
������
    cTemp : Ҫ��ӡ���ַ�
    nNum  : ��Ҫ��ӡ������
����ֵ��
    ��
*/
void printC(char cTemp , int nNum){
    printf(" ");
    while(nNum > 0){
        printf("%c" , cTemp);
        --nNum;
    }
    printf("\t\n");
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