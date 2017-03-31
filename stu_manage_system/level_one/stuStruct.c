#include "myStu.h"

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
void countStuLen(stuStruct *pStu, ushort nChLen){
    if(pStu == NULL){
        return;
    }
    // 结构体实际大小
    pStu->nStuLen = sizeof(*pStu) + nChLen - (nChLen % ALIGNED);
}

/*
函数功能：
    保存学生信息结构体中原先的学号、姓名、电话信息为普通字符串
参数：
    *pStu    : 指向学生信息结构体的指针
    *nLenArr : 保存原先数据长度的一维数组指针
    *szSave[]: 指向需要存放信息的二维数组指针
返回值：
    无
*/
void saveStuPInfo(stuStruct *pStu ,
                  ushort *nLenArr,
                  uchar szSave[][MAXINFOLEN]){
    if(pStu == NULL || nLenArr == NULL || szSave == NULL){
        return;
    }

    // 保存学号信息
    if(pStu->nIdLen != 0){
        memcpy_s(szSave[0] , pStu->nIdLen ,
                 pStu->szInfoArr , pStu->nIdLen);
        szSave[0][ pStu->nIdLen ] = '\0';
        nLenArr[ 0 ] = pStu->nIdLen;
    }
    // 保存姓名信息
    if(pStu->nNameLen != 0){
        memcpy_s(szSave[1] , pStu->nNameLen ,
                 (pStu->szInfoArr)+(pStu->nIdLen),
                 pStu->nNameLen);
        szSave[1][ pStu->nNameLen ] = '\0';
        nLenArr[ 1 ] = pStu->nNameLen;
    }
    // 保存电话信息
    if(pStu->nTelLen != 0){
        memcpy_s(szSave[2] , pStu->nTelLen ,
                 (pStu->szInfoArr) + (pStu->nIdLen) +
                 (pStu->nNameLen), pStu->nTelLen);
        szSave[2][ pStu->nTelLen ] = '\0';
        nLenArr[ 2 ] = pStu->nTelLen;
    }
}

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
void setStuPInfo(stuStruct *pStu , uint nSelect , uchar *szTemp , uint nLen){
    if(pStu == NULL){
        return;
    }
    if(szTemp == NULL){
        return;
    }

    switch(nSelect){
        case ID:
            // 设置学号
            memcpy_s(pStu->szInfoArr, nLen, szTemp, nLen);
            pStu->nIdLen = nLen;
            break;
        case NAME:
            // 设置姓名
            memcpy_s((pStu->szInfoArr) + (pStu->nIdLen) , nLen ,
                     szTemp , nLen);
            pStu->nNameLen = nLen;
            break;
        case TEL:
            // 设置电话
            memcpy_s((pStu->szInfoArr) + (pStu->nIdLen) + (pStu->nNameLen),
                     nLen, szTemp, nLen);
            pStu->nTelLen = nLen;
            break;
        default:
            break;
    }
}

/*
函数功能：
    在堆中创建一个学生信息结构体 并要求输入赋值
    最终将结构体信息写入文件
参数：
    *fp 数据文件指针
返回值：
    指向结构体的指针
*/
stuStruct *newStu(FILE *fp){
    // 用于存放用户输入的学号、姓名、电话
    uchar szTempInfo[3][ MAXINFOLEN ];
    // 用于存放学号、姓名、电话的长度
    ushort nInfoLen[ 3 ] = { 0 };
    // 三个信息总长度
    ushort nInfoCount = 0;

    // 要求输入学号、姓名、电话
    printf("请输入学号：\t\n");
    scanf_s("%s" , szTempInfo[ID], MAXINFOLEN - 1 );
    printf("请输入姓名：\t\n");
    scanf_s("%s" , szTempInfo[NAME], MAXINFOLEN - 1 );
    printf("请输入电话：\t\n");
    scanf_s("%s" , szTempInfo[TEL], MAXINFOLEN - 1 );

    // 计算学号长度
    nInfoLen[ ID ] = strlen(szTempInfo[ ID ]);
    // 计算姓名长度
    nInfoLen[ NAME ] = strlen(szTempInfo[ NAME ]);
    // 计算电话长度
    nInfoLen[ TEL ] = strlen(szTempInfo[ TEL ]);
    // 计算总长度
    nInfoCount = nInfoLen[ ID ] + nInfoLen[ NAME ] + nInfoLen[ TEL ];
    
    // 申请学生结构体内存
    // 其中 - (nInfoCount % ALIGNED) 是为了对齐结构体到固定字节
    stuStruct *pStuTemp = (stuStruct *)malloc(sizeof(stuStruct)
                                              + nInfoCount -
                                              (nInfoCount % ALIGNED));
    if(pStuTemp == NULL){
        printf("内存分配失败\t\n");
        exit(1);
    }

    // 将学号写入结构体中
    setStuPInfo(pStuTemp , ID , szTempInfo[ ID ] , nInfoLen[ ID ]);
    // 将姓名写入结构体中
    setStuPInfo(pStuTemp , NAME , szTempInfo[ NAME ] , nInfoLen[ NAME ]);
    // 将电话写入结构体中
    setStuPInfo(pStuTemp , TEL , szTempInfo[ TEL ] , nInfoLen[ TEL ]);

    // 设置被删除标志位
    pStuTemp->isDel = 0;

    // 输入生日
    printf("请输入生日（格式为：yyyy-mm-dd）：\t\n");
    scanf_s("%u-%u-%u" , &(pStuTemp->nYear),
                       &(pStuTemp->nMonth),
                       &(pStuTemp->nDay));

    // 输入C语言成绩
    printf("请输入C语言成绩（精确到小数点后一位）：\t\n");
    scanf_s("%f" , &(pStuTemp->fScore));

    // 计算并存储结构体长度
    countStuLen(pStuTemp, nInfoCount);

    // 将结构体写入文件中
    writeFile(fp , pStuTemp);

    return pStuTemp;
}