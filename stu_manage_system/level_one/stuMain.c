#include "myStu.h"

int main(){

    // 设置控制台窗口大小
    system("mode con cols=107 lines=40");

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
    printf("%d.新建\t\n" , CREATE);
    printf("%d.输出所有\t\n" , ECHO);
    printf("%d.删除\t\n" , DEL);
    printf("%d.查找\t\n" , FIND);
    printf("%d.统计\t\n" , COUNT);
    printf("%d.修改\t\n" , MODIFY);
    printf("%d.查看存储情况\t\n" , VIEWMEM);
    printf("%d.碎片整理\t\n" , SORTMEM);
    printf("%d.退出\t\n" , QUIT);
    printf("请输入选项：\t\n");
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