#pragma once

/*
ѧ����Ϣ�ṹ�壺
*pszId    : ѧ���ַ�����ָ��
*pszName  : �����ַ�����ָ��
*pszTel   : �绰�����ַ�����ָ��
nScore    : C���Գɼ�
nStuLen   : ѧ����Ϣ����
ushort    : �Ƿ�ɾ��
nIdLen    : ѧ�ų���
nNameLen  : ��������
nTelLen   : �绰����
nYear     : �������
nMonth    : �����·�
nDay      : ��������

����˳���ǰ������ݴ洢���ϸ�̶������
�Խ�ʡ�ڴ�ռ�
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