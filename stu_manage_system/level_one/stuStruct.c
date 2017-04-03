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
void setStuPInfo(stuStruct *pStu ,
                 uint nSelect ,
                 uchar *szTemp ,
                 uint nLen){
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
void newStu(FILE *fp){
    // 用于存放用户输入的学号、姓名、电话
    uchar szTempInfo[3][ MAXINFOLEN ];
    // 用于存放学号、姓名、电话的长度
    ushort nInfoLen[ 3 ] = { 0 };
    // 三个信息总长度
    ushort nInfoCount = 0;

    printC('-' , 110);
    // 要求输入学号、姓名、电话
    printf(" 请输入学号：\t\n");
    scanf_s("%s" , szTempInfo[ID], MAXINFOLEN - 1 );
    fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[ID]);
#endif

    printf(" 请输入姓名：\t\n");
    scanf_s("%s" , szTempInfo[NAME], MAXINFOLEN - 1 );
    fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[NAME]);
#endif
    printf(" 请输入电话：\t\n");
    scanf_s("%s" , szTempInfo[TEL], MAXINFOLEN - 1 );
    fflush(stdin);

#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[TEL]);
#endif

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
        exitStu(fp);
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
    printf(" 请输入生日（格式为：yyyy-mm-dd）：\t\n");
    scanf_s("%hu-%hu-%hu" , &(pStuTemp->nYear),
                       &(pStuTemp->nMonth),
                       &(pStuTemp->nDay));
    fflush(stdin);
#ifdef DEBUG
        printf("%hu-%hu-%hu\t\n\t\n" , pStuTemp->nYear,
                                       pStuTemp->nMonth,
                                       pStuTemp->nDay);
#endif
    // 输入检查
    while((pStuTemp->nYear < 1900 || pStuTemp->nYear > 2017) ||
          (pStuTemp->nMonth < 1 || pStuTemp->nMonth > 12) ||
          (pStuTemp->nDay < 1 || pStuTemp->nDay   > 31)){
        printf(" 输入有误，请重新输入（格式为：yyyy-mm-dd）：\t\n");
        scanf_s("%hu-%hu-%hu" , &(pStuTemp->nYear),
                           &(pStuTemp->nMonth),
                           &(pStuTemp->nDay));
        fflush(stdin);
#ifdef DEBUG
        printf("%hu-%hu-%hu\t\n\t\n" , pStuTemp->nYear,
                                       pStuTemp->nMonth,
                                       pStuTemp->nDay);
#endif
    }
    // 输入C语言成绩
    printf(" 请输入C语言成绩（精确到小数点后二位）：\t\n");
    scanf_s("%f" , &(pStuTemp->fScore));
    fflush(stdin);
#ifdef DEBUG
        printf("%f\t\n\t\n" , pStuTemp->fScore);
#endif
    // 输入检查
    while(pStuTemp->fScore < 0.0 || pStuTemp->fScore > 100.0){
        printf(" 输入有误，请重新输入：\t\n");
        scanf_s("%f" , &(pStuTemp->fScore));
        fflush(stdin);
#ifdef DEBUG
        printf("%f\t\n\t\n" , pStuTemp->fScore);
#endif
    }

    // 计算并存储结构体长度
    countStuLen(pStuTemp, nInfoCount);

    // 将结构体写入文件中
    writeFile(fp , pStuTemp);

    // 释放结构体空间
    free(pStuTemp);

    printC('-' , 110);
    printf(" 新建成功！\t\n");
}

/*
函数功能：
    打印学生结构体信息
参数：
    *pStu  : 指向学生信息结构体的指针
    nPreId : 该结构体序号
返回值：
    无
*/
void printStuInfo(stuStruct *pStu , int nPreId){
        // 保存学号、姓名、电话的二维数组
        uchar szStuArr[ 3 ][ MAXINFOLEN ];
        ushort nStuArrLen[ 3 ];
        ushort age = 0;
        time_t nowTime;
        struct tm *pNowTime;
        // 保存学号、姓名、电话为普通字符串
        saveStuPInfo(pStu , nStuArrLen , szStuArr);
        // 获取当前时间
        time(&nowTime);
        pNowTime = localtime(&nowTime);
        printf(" %d. 学号：%s | 姓名：%s | 电话：%s | 年龄：%d | C语言成绩：%.2f\t\n" ,
               nPreId , szStuArr[ ID ] , szStuArr[ NAME ] , szStuArr[ TEL],
               pNowTime->tm_year + 1900 - (int)pStu->nYear, pStu->fScore);
}

/*
函数功能：
    通过用户的输入进行查找操作
参数：
    *fp : 指向数据文件的指针
返回值：
    无
*/
void findStu(FILE *fp){
    int nSelect;
    int nPreId = 0;
    uchar szBuff[ MAXINFOLEN ];

    printC('-' , 110);
    printf("%40c1.按序号查找\t\n%40c2.按学号模糊查找\t\n%40c3.按姓名模糊查找\t\n%40c4.按电话模糊查找\t\n%40c0.返回\t\n", ' ', ' ', ' ', ' ', ' ');
    printC('-' , 110);
    printf(" 请输入序号：\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif

    while(nSelect < 0 || nSelect > 4){
            printf(" 输入有误，请重新输入：\t\n");
            scanf("%d" , &nSelect);
            fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    }

    if(nSelect == 1){
        printf(" 请输入要查找的学生序号：\t\n");
        scanf("%d" , &nPreId);
        fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif

        while(nPreId <= 0){
            printf(" 输入有误，请重新输入：\t\n");
            scanf("%d" , &nPreId);
            fflush(stdin);
#ifdef DEBUG
            printf("%d\t\n\t\n" , nSelect);
#endif
        }
        echoFile(fp , nPreId);
    }
    else{
        printf(" 请输入要查找的内容：\t\n");
        scanf_s("%s" , szBuff , MAXINFOLEN - 1);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szBuff);
#endif
        
        printC('-' , 110);
        findFile(fp , szBuff , nSelect);
        printC('-' , 110);
    }
}

/*
函数功能：
    根据用户输入修改学生信息
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void modifyStu(FILE *fp){
    printf(" 可修改的学生列表：\t\n");
    echoFile(fp , 0);

    int nSelect;
    printf(" 请输入要修改的学生信息序号（输入0则退出修改）：\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    
    while(nSelect < 0){
        printf(" 输入有误！请重新输入：\t\n");
        scanf("%d" , &nSelect);
        fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    }
    if(nSelect == 0){
        return;
    }

    system("cls");
    // 获取并打印查找到的学生信息
    printf(" 修改：\t\n");
    if(echoFile(fp , nSelect) == 0){
        return;
    }
    
    printf("%40c1.学号\t\n%40c2.姓名\t\n%40c3.电话\t\n%40c4.生日\t\n%40c5.C语言成绩\t\n%40c0.退出修改\t\n",
           ' ', ' ', ' ', ' ', ' ', ' ');
    printC('-' , 110);
    printf(" 请输入选项：\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    while(nSelect < 0 || nSelect > 5){
        printf(" 输入有误！请重新输入：\t\n");
        scanf("%d" , &nSelect);
        fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    }
    if(nSelect == 0){
        return;
    }

    // 开始修改
    if(nSelect == 4){
        // 修改生日
        ushort nYear;
        ushort nMonth;
        ushort nDay;
        printf(" 请输入新的生日（格式为yyyy-mm-dd）：\t\n");
        scanf("%hu-%hu-%hu" , &nYear , &nMonth , &nDay);
        fflush(stdin);
#ifdef DEBUG
        printf("%hu-%hu-%hu\t\n\t\n" , nYear, nMonth, nDay);
#endif
        // 输入检查
        while((nYear < 1900 || nYear > 2017) ||
              (nMonth < 1 || nMonth > 12) ||
              (nDay < 1 || nDay   > 31)){
            printf(" 输入有误，请重新输入（格式为：yyyy-mm-dd）：\t\n");
            scanf("%hu-%hu-%hu" , &nYear , &nMonth , &nDay);
            fflush(stdin);
#ifdef DEBUG
            printf("%hu-%hu-%hu\t\n\t\n" , nYear, nMonth, nDay);
#endif
        }
        // 将文件指针偏移到年份的位置
        fseek(fp , (long)sizeof(ushort) * 5 , SEEK_CUR);
        // 更新年份
        fwrite(&nYear, sizeof(ushort), 1, fp);
        // 将文件指针偏移到月份的位置
        fseek(fp , (long)sizeof(ushort) , SEEK_CUR);
        // 更新月份
        fwrite(&nMonth , sizeof(ushort) , 1 , fp);

        // 将文件指针偏移到日期的位置
        fseek(fp , (long)sizeof(ushort) , SEEK_CUR);
        // 更新日期
        fwrite(&nDay , sizeof(ushort) , 1 , fp);
        printf(" 修改成功！\t\n");
    }
    else if(nSelect == 5){
        // 修改C语言成绩
        float fScore;
        printf(" 请输入新的C语言成绩（精确到小数点后两位）：\t\n");
        scanf("%f" , &fScore);
        fflush(stdin);
#ifdef DEBUG
        printf("%f\t\n\t\n" , fScore);
#endif
        // 输入检查
        while(fScore < 0.0 || fScore > 100.0){
            printf(" 输入有误，请重新输入：\t\n");
            scanf("%f" , &fScore);
            fflush(stdin);
#ifdef DEBUG
            printf("%f\t\n\t\n" , fScore);
#endif
        }

        // 将文件指针偏移到成绩的位置
        fseek(fp, (long)sizeof(ushort) * 8, SEEK_CUR);
        // 更新成绩
        fwrite(&fScore , sizeof(float), 1, fp);
        printf(" 修改成功！\t\n");
    }
    else{
        // 修改学号、姓名、电话
        resetPInfo(fp , nSelect);
    }

    // 将文件指针指向文件初始位置
    fseek(fp , 0 , SEEK_SET);
}

/*
函数功能：
    重新设置学号、姓名、电话
参数：
    *fp    : 数据文件指针
    nSelect: 修改选项
返回值：
    无
*/
void resetPInfo(FILE *fp , int nSelect){
    // 修改学号、姓名、电话
    // 从文件中读出学生信息到结构体
    stuStruct *pStu = readFile(fp);
    if(pStu == NULL){
        printf(" 修改失败\t\n");
        return;
    }
    // 将文件指针指回该结构体在文件中的起始位置
    fseek(fp , -(long)(pStu->nStuLen), SEEK_CUR);

    // 用于存放用户输入的学号、姓名、电话
    uchar szTempInfo[3][ MAXINFOLEN ];
    // 用于存放学号、姓名、电话的长度
    ushort nInfoLen[ 3 ] = { 0 };
    // 三个信息总长度
    ushort nInfoCount = 0;
    // 保存原来的数据为普通字符串
    saveStuPInfo(pStu , nInfoLen , szTempInfo);

    if(nSelect == 1){
        printf(" 请输入新的学号：\t\n");
        scanf("%s" , szTempInfo[ ID ]);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[ID]);
#endif
    }
    else if(nSelect == 2){
        printf(" 请输入新的姓名：\t\n");
        scanf("%s" , szTempInfo[ NAME ]);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[NAME]);
#endif
    }
    else{
        printf(" 请输入新的电话：\t\n");
        scanf("%s" , szTempInfo[ TEL ]);
        fflush(stdin);
#ifdef DEBUG
        printf("%s\t\n\t\n" , szTempInfo[TEL]);
#endif
    }
    
    // 如果数据长度没变则写入原来的位置，
    // 否则删除原数据，重新写入文件
    if(strlen(szTempInfo[ ID ]) == nInfoLen[ ID ] &&
       strlen(szTempInfo[NAME]) == nInfoLen[NAME] &&
       strlen(szTempInfo[TEL])  == nInfoLen[TEL]){
        // 将新的数据保存到结构体中
        // 将学号写入结构体中
        setStuPInfo(pStu , ID , szTempInfo[ ID ] , nInfoLen[ ID ]);
        // 将姓名写入结构体中
        setStuPInfo(pStu , NAME , szTempInfo[ NAME ] , nInfoLen[ NAME ]);
        // 将电话写入结构体中
        setStuPInfo(pStu , TEL , szTempInfo[ TEL ] , nInfoLen[ TEL ]);
        
        // 写入前先设置文件指针
        fseek(fp , 0 , SEEK_CUR);

        // 写入文件
        fwrite(pStu , sizeof(uchar) , pStu->nStuLen , fp);
    }
    else{

        nInfoLen[ ID ] = strlen(szTempInfo[ ID ]);
        nInfoLen[ NAME ] = strlen(szTempInfo[ NAME ]);
        nInfoLen[ TEL ] = strlen(szTempInfo[ TEL ]);
        nInfoCount = nInfoLen[ ID ] +
                     nInfoLen[ NAME ] +
                     nInfoLen[ TEL ];

        // 申请新的学生结构体内存
        // 其中 - (nInfoCount % ALIGNED) 是为了对齐结构体到固定字节
        stuStruct *pStuTemp = (stuStruct *)malloc(sizeof(stuStruct)
                                                  + nInfoCount -
                                                  (nInfoCount % ALIGNED));
        if(pStuTemp == NULL){
            printf(" 修改失败\t\n");
            return;
        }
        // 计算并存储结构体长度
        countStuLen(pStuTemp, nInfoCount);
        // 将旧结构体中的信息拷进新的结构体中
        memcpy_s(pStuTemp , pStuTemp->nStuLen, pStu,
                 (pStu->nStuLen > pStuTemp->nStuLen) ? pStuTemp->nStuLen :
                                                       pStu->nStuLen);
        // 计算并存储结构体长度
        countStuLen(pStuTemp, nInfoCount);

        // 将新的数据保存到结构体中
        // 将学号写入结构体中
        setStuPInfo(pStuTemp , ID , szTempInfo[ ID ] , nInfoLen[ ID ]);
        // 将姓名写入结构体中
        setStuPInfo(pStuTemp , NAME , szTempInfo[ NAME ] , nInfoLen[ NAME ]);
        // 将电话写入结构体中
        setStuPInfo(pStuTemp , TEL , szTempInfo[ TEL ] , nInfoLen[ TEL ]);

        // 删除旧的学生信息
        delFile(fp);
        // 写入新的学生信息
        writeFile(fp , pStuTemp);

        free(pStuTemp);
        printf(" 修改成功！\t\n");
    }
}

/*
函数功能：
    根据用户输入删除指定学生信息
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void delStu(FILE *fp){
    printf(" 可删除的学生列表：\t\n");
    echoFile(fp , 0);

    int nSelect;
    printf(" 请输入要删除的学生信息序号（输入0则退出删除）：\t\n");
    scanf("%d" , &nSelect);
    fflush(stdin);
#ifdef DEBUG
        printf("%d\t\n\t\n" , nSelect);
#endif
    
    if(nSelect == 0){
        return;
    }

    // 获取并打印查找到的学生信息
    printf(" 删除：\t\n");
    if(echoFile(fp , nSelect) == 0){
        return;
    }

    // 删除指定的学生信息
    delFile(fp);
    sortMemJustDel(fp);
    printf(" 删除成功！\t\n");
}