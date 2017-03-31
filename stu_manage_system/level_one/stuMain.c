#include "myStu.h"

int main(){

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
    if(fopen_s(&fp , "sqldata" , "rb+")){
        printf("数据文件打开失败\t\n");
        exit(1);
    }

    int nFirstSelete;
    stuStruct *pStu = NULL;
    printf("请输入选项：\t\n");
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

    // 释放结构体内存
    free(pStu);

    // 关闭文件
    fclose(fp);
    fclose(stdin);
#ifdef REOUT
    fclose(stdout);
#endif
    return 0;
}