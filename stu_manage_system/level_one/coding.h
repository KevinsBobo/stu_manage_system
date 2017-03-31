#pragma once

// 基本数据类型别名 和 宏定义数据

typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned int   uint;
typedef unsigned long long ulong;

// 结构体对齐长度，以short类型双倍空间对齐
#define ALIGNED (sizeof(short) * 2)

// 可变长信息最大长度
#define MAXINFOLEN 51

// 学号、姓名、电话下标别名
#define ID   0
#define NAME 1
#define TEL  2

// 操作选项
#define CREATE 1
#define READ   2
#define ECHO   3
#define DEL    4