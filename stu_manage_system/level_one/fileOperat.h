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
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void echoFile(FILE *fp);