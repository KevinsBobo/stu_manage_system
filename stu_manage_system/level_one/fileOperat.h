#pragma once

/*
函数功能：
    将结构体信息写入到文件中
参数：
    *fp   : 数据文件指针
    *pStu : 学生结构体指针
返回值：
    无
*/
void writeFile(FILE *fp , stuStruct *pStu);

/*
函数功能：
    从文件中读取指针所在位置的数据到结构体中
参数：
    *fp : 数据文件指针
返回值：
    指向在堆中的学生信息结构体的地址
*/
stuStruct *readFile(FILE *fp);

/*
函数功能：
    删除文件中文件指针所在位置的学生结构体信息
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void delFile(FILE *fp);

/*
函数功能：
    打印所有未被删除的学生信息
    如打印所有则在打印完后将指针指向文件头部
    如打印指定则打印完后将指针指向该结构体在文件中的起始位置
参数：
    *fp    : 数据文件指针
    nPreId : 如赋值为0则打印所有学生信息
             否则只打印第nPreId个学生信息
返回值：
    0 没有查找到；非0 查找到
*/
int echoFile(FILE *fp, int nPreId);

/*
函数功能：
    在文件中查找结构体，
    若指定只查找匹配到的第一个学生信息，找到后将文件指针置向
    查找到的结构体在文件中的起始位置；
    否则查找结束后将文件指针指向文件起始位置
参数：
    *fp     : 数据文件指针
    *szBuff : 待查找的字符串
    nSelect : 查找模式 FINDALL FINDONE
返回值：
    0 没有查找到；非0 查找到
*/
int findFile(FILE *fp , uchar *szBuff, int nSelect);

/*
函数功能：
    统计所有学生人数，C语言成绩最高分、最低分、平均分、总分
参数：
    *fp : 指向数据文件的指针
返回值：
    无
*/
void countStuInfo(FILE *fp);

/*
函数功能：
    打印文件存储情况
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void echoMem(FILE *fp);

/*
函数功能：
    打印内存块
参数：
    nMem  : 打印数量
    isEmp : 打印类型 非0 空内存 0 已使用内存
    nNum  : 计算已打印的内存的数量，控制输出
返回值：
    无
*/
void printMem(ushort nMem , int isEmp, long long *nNum);

/*
函数功能：
    碎片整理
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void sortMem(FILE *fp);