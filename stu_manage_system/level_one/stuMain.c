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
    
    // 打开数据文件
    FILE *fp = NULL;
    if(fopen_s(&fp , "sqldata" , "r+b")){
        printf("数据文件打开失败\t\n");
        exit(1);
    }

    printStart();
    int nFirstSelete;
    while(scanf_s("%d" , &nFirstSelete) != EOF){
        switch(nFirstSelete){
            case QUIT:
                // 释放空间、关闭文件
                exitStu(fp);
                break;
            case CREATE:
                system("cls");
                printf("%40c新建学生信息\t\n" , ' ');
                newStu(fp);
                system("pause");
                break;
            case ECHO:
                system("cls");
                printf("%40c所有学生信息\t\n" , ' ');
                echoFile(fp, FINDALL);
                system("pause");
                break;
            case DEL:
                system("cls");
                printf("%40c删除学生信息\t\n" , ' ');
                delStu(fp);
                system("pause");
                break;
            case FIND:
                system("cls");
                printf("%40c查找学生信息\t\n" , ' ');
                findStu(fp);
                system("pause");
                break;
            case COUNT:
                system("cls");
                printf("%40c统计学生信息\t\n" , ' ');
                countStuInfo(fp);
                system("pause");
                break;
            case MODIFY:
                system("cls");
                printf("%40c修改学生信息\t\n" , ' ');
                modifyStu(fp);
                system("pause");
                break;
            case VIEWMEM:
                system("cls");
                printf("%40c查看存储情况\t\n" , ' ');
                echoMem(fp);
                system("pause");
                break;
            case SORTMEM:
                system("cls");
                printf("%40c碎片整理\t\n" , ' ');
                sortMem(fp);
                system("pause");
                break;
            default:
                break;
        }
        printStart();
    }

    // 释放空间、关闭文件
    exitStu(fp);
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
    关闭文件
参数：
    *fp   : 数据文件指针
返回值：
    无
*/
void exitStu(FILE *fp){
    // 关闭文件
    fclose(fp);
    fclose(stdin);
#ifdef REOUT
    fclose(stdout);
#endif
}