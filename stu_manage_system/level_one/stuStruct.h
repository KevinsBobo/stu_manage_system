#pragma once

/*
学生信息结构体：
    nStuLen   : 学生信息长度
    isDel     : 是否被删除
    nIdLen    : 学号长度
    nNameLen  : 姓名长度
    nTelLen   : 电话号码长度
    nYear     : 生日年份
    nMonth    : 生日月份
    nDay      : 生日日期
    fScore    : C语言成绩，精确到小数点后1位
    szInfoArr : 用于存放学号、姓名、电话信息
                最终通过分配空间实现可变长数组
    通过上面的顺序结构体默认大小为 20 + ALIGNED 字节
*/
typedef struct _stuStruct
{
    ushort nStuLen;
    ushort isDel;
    ushort nIdLen;
    ushort nNameLen;
    ushort nTelLen;
    ushort nYear;
    ushort nMonth;
    ushort nDay;
    float  fScore;
    uchar  szInfoArr[ ALIGNED ];
} stuStruct;

/*
函数功能：
    计算学生信息结构体所存信息在文件中存储需要的大小
    并将结构赋值给结构体中的 nStuLen
参数：
    *pStu : 指向学生信息结构体的指针
    nChLen: 扩展长度
返回值：
    无
*/
void countStuLen(stuStruct *stuTemp, ushort nChLen);

/*
函数功能：
    保存学生信息结构体中原先的学号、姓名、电话信息
参数：
    *pStu    : 指向学生信息结构体的指针
    *nLenArr : 保存原先数据长度的一维数组指针
    *szSave[]: 指向需要存放信息的二维数组指针
返回值：
    无
*/
void saveStuPInfo(stuStruct *pStu ,
                  ushort *nLenArr,
                  uchar szSave[][MAXINFOLEN]);

/*
函数功能：
    通过传入的选项设置学号、姓名、电话
    在被调用之前调用函数应分配好足够的结构体空间
参数：
    *pStu   : 指向学生信息的结构体
    nSelect : 操作选项（0、学号 1、姓名 2、电话）
    *szTemp : 设置内容字符串
    nLen    : 字符串长度
返回值：
    无
*/
void setStuPInfo(stuStruct *pStu , uint nSelect , uchar *szTemp , uint nLen);

/*
函数功能：
    在堆中创建一个学生信息结构体 并要求输入赋值
    最终将结构体信息写入文件
参数：
    *fp 数据文件指针
返回值：
    指向结构体的指针
*/
stuStruct *newStu(FILE *fp);

/*
函数功能：
    从文件中读取指针所在位置的数据到结构体中
参数：
    *fp : 数据文件指针
返回值：
    指向在堆中的学生信息结构体的地址
*/
stuStruct *readFile(FILE *fp);