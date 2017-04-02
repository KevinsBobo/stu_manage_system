#include "myStu.h"

int main(){

    // 设置控制台窗口大小
    system("mode con cols=115 lines=40");

#ifdef DEBUG
    // 重定义输入
    freopen("data.in","r",stdin);
#ifdef REOUT
    // 重定向输出
    freopen("data.out","w",stdout);
#endif
#endif
    
    // 数据文件指针
    FILE *fp = NULL;
    // 尝试打开文件，若文件不存在则新建文件
    if(fopen_s(&fp, "sqldata" , "a+")){
        printf("数据库文件打开失败\t\n");
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
                // 释放空间、关闭文件
                exitStu();
                return 0;
            case CREATE:
                system("cls");
                printf("%40c新建学生信息\t\n" , ' ');
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
                printf("%40c所有学生信息\t\n" , ' ');
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
                printf("%40c删除学生信息\t\n" , ' ');
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
                printf("%40c查找学生信息\t\n" , ' ');
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
                printf("%40c统计学生信息\t\n" , ' ');
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
                printf("%40c修改学生信息\t\n" , ' ');
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
                printf("%40c查看存储情况\t\n" , ' ');
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
                printf("%40c碎片整理\t\n" , ' ');
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

    // 释放空间、关闭文件
    exitStu();
    return 0;
}

/*
函数功能：
    打印初始选项
参数：
    无
返回值：
    无
*/
void printStart(){
    system("cls");
    printf("%40c学生管理系统\t\n" , ' ');
    printC('-' , 110);
    printf("%40c%d.新建\t\n" , ' ', CREATE);
    printf("%40c%d.输出所有\t\n" , ' ', ECHO);
    printf("%40c%d.删除\t\n" , ' ', DEL);
    printf("%40c%d.查找\t\n" , ' ', FIND);
    printf("%40c%d.统计\t\n" , ' ', COUNT);
    printf("%40c%d.修改\t\n" , ' ', MODIFY);
    printf("%40c%d.查看存储情况\t\n" , ' ', VIEWMEM);
    printf("%40c%d.碎片整理\t\n" , ' ', SORTMEM);
    printf("%40c%d.退出\t\n" , ' ', QUIT);
    printC('-' , 110);
    printf(" 请输入选项：\t\n");
}

/*
函数功能：
    重复打印同一个字符
参数：
    cTemp : 要打印的字符
    nNum  : 需要打印的数量
返回值：
    无
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
函数功能：
    打开数据库文件
参数：
    *fp : 指向数据文件的指针
返回值：
    0 正常打开，非0 打开失败
*/
int openStuFile(FILE **fp){
    if(fopen_s(fp , "sqldata" , "r+b")){
        printf("数据文件打开失败\t\n");
#ifndef DEBUG
        system("pause");
#endif
        return 1;
    }
    return 0;
}

/*
函数功能：
    关闭文件
参数：
    无
返回值：
    无
*/
void exitStu(){
    // 关闭文件
#ifdef DEBUG
    fclose(stdin);
#ifdef REOUT
    fclose(stdout);
#endif
#endif
}