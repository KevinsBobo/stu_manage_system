#pragma once

/*
学生信息结构体：
    nStuLen   : 学生信息长度
    ushort    : 是否被删除
    *pszId    : 学号字符数组指针
    nIdLen    : 学号长度
    *pszName  : 姓名字符数组指针
    nNameLen  : 姓名长度
    *pszTel   : 电话号码字符数组指针
    nTelLen   : 电话号码长度
    nYear     : 生日年份
    nMonth    : 生日月份
    nDay      : 生日日期
    nScore    : C语言成绩
*/
typedef struct _stuStruct
{
    ushort nStuLen;
    ushort isDel;
    uchar  *pszId;
    ushort nIdLen;
    uchar  *pszName;
    ushort nNameLen;
    uchar  *pszTel;
    ushort nTelLen;
    ushort nYear;
    ushort nMonth;
    ushort nDay;
    float nScore;
} stuStruct;

/*
函数功能：
    释放结构体中指针所指向的内存
参数：
    *pStu : 指向学生信息结构体的指针
*/
void freeStuArr(stuStruct *pStu);