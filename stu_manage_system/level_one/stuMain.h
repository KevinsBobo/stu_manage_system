#pragma once

/*
函数功能：
    打印初始选项
参数：
    无
返回值：
    无
*/
void printStart();

/*
函数功能：
    重复打印同一个字符
参数：
    cTemp : 要打印的字符
    nNum  : 需要打印的数量
返回值：
    无
*/
void printC(char cTemp , int nNum);

/*
函数功能：
    关闭文件
参数：
    *fp   : 数据文件指针
返回值：
    无
*/
void exitStu(FILE *fp);