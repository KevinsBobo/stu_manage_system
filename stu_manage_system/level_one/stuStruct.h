#pragma once

/*
ѧ����Ϣ�ṹ�壺
    nStuLen   : ѧ����Ϣ����
    isDel     : �Ƿ�ɾ��
    nIdLen    : ѧ�ų���
    nNameLen  : ��������
    nTelLen   : �绰���볤��
    nYear     : �������
    nMonth    : �����·�
    nDay      : ��������
    fScore    : C���Գɼ�����ȷ��С�����1λ
    szInfoArr : ���ڴ��ѧ�š��������绰��Ϣ
                ����ͨ������ռ�ʵ�ֿɱ䳤����
    ͨ�������˳��ṹ��Ĭ�ϴ�СΪ 20 + ALIGNED �ֽ�
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
�������ܣ�
    ����ѧ����Ϣ�ṹ��������Ϣ���ļ��д洢��Ҫ�Ĵ�С
    �����ṹ��ֵ���ṹ���е� nStuLen
������
    *pStu : ָ��ѧ����Ϣ�ṹ���ָ��
    nChLen: ��չ����
����ֵ��
    ��
*/
void countStuLen(stuStruct *stuTemp, ushort nChLen);

/*
�������ܣ�
    ����ѧ����Ϣ�ṹ����ԭ�ȵ�ѧ�š��������绰��Ϣ
������
    *pStu    : ָ��ѧ����Ϣ�ṹ���ָ��
    *nLenArr : ����ԭ�����ݳ��ȵ�һά����ָ��
    *szSave[]: ָ����Ҫ�����Ϣ�Ķ�ά����ָ��
����ֵ��
    ��
*/
void saveStuPInfo(stuStruct *pStu ,
                  ushort *nLenArr,
                  uchar szSave[][MAXINFOLEN]);

/*
�������ܣ�
    ͨ�������ѡ������ѧ�š��������绰
    �ڱ�����֮ǰ���ú���Ӧ������㹻�Ľṹ��ռ�
������
    *pStu   : ָ��ѧ����Ϣ�Ľṹ��
    nSelect : ����ѡ�0��ѧ�� 1������ 2���绰��
    *szTemp : ���������ַ���
    nLen    : �ַ�������
����ֵ��
    ��
*/
void setStuPInfo(stuStruct *pStu , uint nSelect , uchar *szTemp , uint nLen);

/*
�������ܣ�
    �ڶ��д���һ��ѧ����Ϣ�ṹ�� ��Ҫ�����븳ֵ
    ���ս��ṹ����Ϣд���ļ�
������
    *fp �����ļ�ָ��
����ֵ��
    ָ��ṹ���ָ��
*/
stuStruct *newStu(FILE *fp);

/*
�������ܣ�
    ���ļ��ж�ȡָ������λ�õ����ݵ��ṹ����
������
    *fp : �����ļ�ָ��
����ֵ��
    ָ���ڶ��е�ѧ����Ϣ�ṹ��ĵ�ַ
*/
stuStruct *readFile(FILE *fp);