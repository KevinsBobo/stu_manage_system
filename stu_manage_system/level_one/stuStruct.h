#pragma once

/*
学生信息结构体：
*pszId    : 学号字符数组指针
*pszName  : 姓名字符数组指针
*pszTel   : 电话号码字符数组指针
nScore    : C语言成绩
nStuLen   : 学生信息长度
ushort    : 是否被删除
nIdLen    : 学号长度
nNameLen  : 姓名长度
nTelLen   : 电话长度
nYear     : 生日年份
nMonth    : 生日月份
nDay      : 生日日期

以上顺序是按照数据存储的严格程度排序的
以节省内存空间
*/
typedef struct _stuStruct
{
    char   *pszId;
    char   *pszName;
    char   *pszTel;
    float nScore;
    ushort nStuLen;
    ushort isDel;
    ushort nIdLen;
    ushort nNameLen;
    ushort nTelLen;
    ushort nYear;
    ushort nMonth;
    ushort nDay;
} stuStruct;