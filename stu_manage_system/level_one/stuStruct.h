#pragma once

/*
ѧ����Ϣ�ṹ�壺
    nStuLen   : ѧ����Ϣ����
    ushort    : �Ƿ�ɾ��
    *pszId    : ѧ���ַ�����ָ��
    nIdLen    : ѧ�ų���
    *pszName  : �����ַ�����ָ��
    nNameLen  : ��������
    *pszTel   : �绰�����ַ�����ָ��
    nTelLen   : �绰���볤��
    nYear     : �������
    nMonth    : �����·�
    nDay      : ��������
    nScore    : C���Գɼ�
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
�������ܣ�
    �ͷŽṹ����ָ����ָ����ڴ�
������
    *pStu : ָ��ѧ����Ϣ�ṹ���ָ��
*/
void freeStuArr(stuStruct *pStu);