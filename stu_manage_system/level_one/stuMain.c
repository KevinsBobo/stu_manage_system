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
    
    // �����ļ�ָ��
    FILE *fp = NULL;
    // ���Դ��ļ������ļ����������½��ļ�
    if(fopen_s(&fp, "sqldata" , "a+")){
        printf("���ݿ��ļ���ʧ��\t\n");
        exitStu();
#ifndef DEBUG
        system("pause");
#endif
        exit(1);
    }
    fclose(fp);

    printStart();
    int nFirstSelect;
    while(scanf_s("%d" , &nFirstSelect) != EOF){
#ifdef DEBUG
        printf("%d\t\n\t\n" , nFirstSelect);
#endif
        switch(nFirstSelect){
            case QUIT:
                // �ͷſռ䡢�ر��ļ�
                exitStu();
                return 0;
            case CREATE:
                system("cls");
                printf("%40c�½�ѧ����Ϣ\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                newStu(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case ECHO:
                system("cls");
                printf("%40c����ѧ����Ϣ\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                echoFile(fp, FINDALL);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case DEL:
                system("cls");
                printf("%40cɾ��ѧ����Ϣ\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                delStu(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case FIND:
                system("cls");
                printf("%40c����ѧ����Ϣ\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                findStu(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case COUNT:
                system("cls");
                printf("%40cͳ��ѧ����Ϣ\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                countStuInfo(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case MODIFY:
                system("cls");
                printf("%40c�޸�ѧ����Ϣ\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                modifyStu(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case VIEWMEM:
                system("cls");
                printf("%40c�鿴�洢���\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                echoMem(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            case SORTMEM:
                system("cls");
                printf("%40c��Ƭ����\t\n" , ' ');
                if(openStuFile(&fp)){
                    return 0;
                }
                sortMem(fp);
                fclose(fp);
#ifndef DEBUG
                system("pause");
#endif
                break;
            default:
                break;
        }
        printStart();
    }

    // �ͷſռ䡢�ر��ļ�
    exitStu();
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
    �����ݿ��ļ�
������
    *fp : ָ�������ļ���ָ��
����ֵ��
    0 �����򿪣���0 ��ʧ��
*/
int openStuFile(FILE **fp){
    if(fopen_s(fp , "sqldata" , "r+b")){
        printf("�����ļ���ʧ��\t\n");
#ifndef DEBUG
        system("pause");
#endif
        return 1;
    }
    return 0;
}

/*
�������ܣ�
    �ر��ļ�
������
    ��
����ֵ��
    ��
*/
void exitStu(){
    // �ر��ļ�
#ifdef DEBUG
    fclose(stdin);
#ifdef REOUT
    fclose(stdout);
#endif
#endif
}