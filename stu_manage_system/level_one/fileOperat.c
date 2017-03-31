#include "myStu.h"

/*
函数功能：
    将结构体信息写入到文件中
参数：
    *fp   : 数据文件指针
    *pStu : 学生结构体指针
返回值：
    无
*/
void writeFile(FILE *fp , stuStruct *pStu){
    if(fp == NULL){
        return;
    }
    if(pStu == NULL){
        return;
    }

    // 将文件指针置向文件末尾
    fseek(fp , 0 , SEEK_END);

    // 写入数据
    fwrite(pStu , sizeof(char) , pStu->nStuLen , fp);
}

/*
函数功能：
    从文件中读取指针所在位置的数据到结构体中
参数：
    *fp : 数据文件指针
返回值：
    指向在堆中的学生信息结构体的地址
*/
stuStruct *readFile(FILE *fp){
    if(fp == NULL){
        return NULL;
    }
    stuStruct *pStuTemp = NULL;
    ushort nStuLen = 0;

    // 读取结构体大小
    if(fread_s(&nStuLen , sizeof(nStuLen) , sizeof(ushort) , 1 , fp)
       == 0){
        return NULL;
    }
    // 为结构体分配空间
    pStuTemp = (stuStruct *)malloc(nStuLen * sizeof(uchar));
    if(pStuTemp == NULL){
        printf("内存分配失败\t\n");
        exit(1);
    }
    // 将指针置回结构体起始位置
    fseek(fp , -(long)(sizeof(ushort)), SEEK_CUR);
    // 从文件中读取结构体数据到结构体内存中
    fread_s(pStuTemp , nStuLen , sizeof(uchar) , nStuLen , fp);
    
    return pStuTemp;
}

/*
函数功能：
    删除文件中文件指针所在位置的学生结构体信息
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void delFile(FILE *fp){
    if(fp == NULL){
        return;
    }
    // 将指针偏移至删除标志位
    fseek(fp , (long)(sizeof(ushort)) , SEEK_CUR);

    if(fp->_ptr == NULL){
        return;
    }
    // 将删除标志位置为 0xFFFF
    ushort isDel = 0xFFFF;
    fwrite(&isDel, sizeof(ushort), 1, fp);

    // 将指针置回该结构体在文件中的起始位置
    fseek(fp , -(long)(sizeof(ushort) * 2) , SEEK_CUR);
}

/*
函数功能：
    打印所有未被删除的学生信息
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void echoFile(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    stuStruct *pStu;
    // 序号
    int nId = 1;
    // 保存学号、姓名、电话的二维数组
    uchar szStuArr[ 3 ][ MAXINFOLEN ];
    ushort nStuArrLen[ 3 ];
    ushort age = 0;
    time_t nowTime;
    struct tm *pNowTime;
    // 循环打印
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // 被删除的数据不打印
            continue;
        }
        // 保存学号、姓名、电话为普通字符串
        saveStuPInfo(pStu , nStuArrLen , szStuArr);
        // 获取当前时间
        time(&nowTime);
        pNowTime = localtime(&nowTime);
        printf("序号：%d\t\n学号：%s\t\n姓名：%s\t\n电话：%s\t\n年龄：%d\t\nC语言成绩：%.2f\t\n\t\n" ,
               nId , szStuArr[ ID ] , szStuArr[ NAME ] , szStuArr[ TEL],
               pNowTime->tm_year + 1900 - (int)pStu->nYear, pStu->fScore);
        ++nId;
    }
}