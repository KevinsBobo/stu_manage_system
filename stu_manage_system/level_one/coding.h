#pragma once

// �����������ͱ��� �� �궨������

typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned int   uint;
typedef unsigned long long ulong;

// �ṹ����볤�ȣ���short����˫���ռ����
#define ALIGNED (sizeof(short) * 2)

// �ɱ䳤��Ϣ��󳤶�
#define MAXINFOLEN 51

// ѧ�š��������绰�±����
#define ID   0
#define NAME 1
#define TEL  2

// ����ѡ��
#define CREATE 1
#define READ   2
#define ECHO   3
#define DEL    4