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
#define QUIT   0  // �˳�
#define CREATE 1  // �½�
#define ECHO   2  // ���
#define DEL    3  // ɾ��
#define FIND   4  // ����
#define COUNT  5  // ͳ��
#define MODIFY 6  // �޸�
#define VIEWMEM 7 // �鿴�洢
#define SORTMEM 8 // ����洢

// ����ѡ��
#define FINDALL 0
#define FINDONE 1