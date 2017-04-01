#include "myStu.h"

/*
函数功能：
    将结构体信息写入到文件中
参数：
    *fp   : 数据文件指针
    *pStu : 学生结构体指针
返回值：
    无
*/
void writeFile(FILE *fp , stuStruct *pStu){
    if(fp == NULL){
        return;
    }
    if(pStu == NULL){
        return;
    }

    // 将文件指针置向文件起始位置
    fseek(fp , 0 , SEEK_SET);

    ushort nReadLen , isEmp, nTemp;
    // 遍历数据块，寻找合适的数据块
    while(fread_s(&nReadLen , sizeof(ushort) , sizeof(ushort) , 1 , fp)
          != 0){
        // 所读取数据块大小不够
        if(nReadLen < pStu->nStuLen){
            fseek(fp , (long)(nReadLen - sizeof(ushort)) , SEEK_CUR);
            continue;
        }
        // 读取标志位
        if(fread_s(&isEmp , sizeof(ushort) , sizeof(ushort) , 1 , fp) == 0){
            break;
        }
        // 所读取数据块不是空块
        if(isEmp == 0){
            fseek(fp , (long)(nReadLen - sizeof(ushort) * 2) , SEEK_CUR);
            continue;
        }
        // 空数据块大小与要写入的学生信息大小相同
        if(nReadLen == pStu->nStuLen){
            fseek(fp , -(long)(sizeof(ushort) * 2) , SEEK_CUR);
            break;
        }
        // 空数据块大小大于要写入的学生信息大小
        nTemp = nReadLen - pStu->nStuLen;

        // 将指针移动到需要分割空数据块的位置
        fseek(fp , (long)(nReadLen - sizeof(ushort) * 2 - nTemp) , SEEK_CUR);
        // 给截取后的空数据块写入其大小数据
        fwrite(&nTemp , sizeof(ushort) , 1, fp);
        // 将指针移回该块在文件中起始位置
        fseek(fp , -(long)(sizeof(ushort)) , SEEK_CUR);
        // 将该数据块设置为删除状态
        delFile(fp);
        
        // 将指针移回适合写入的位置
        fseek(fp , -(long)(nReadLen - nTemp) , SEEK_CUR);
        break;
    }

    // 重置文件指针
    fseek(fp , 0 , SEEK_CUR);
    // 写入数据
    fwrite(pStu , sizeof(char) , pStu->nStuLen , fp);
}

/*
函数功能：
    从文件中读取指针所在位置的数据到结构体中
参数：
    *fp : 数据文件指针
返回值：
    指向在堆中的学生信息结构体的地址
*/
stuStruct *readFile(FILE *fp){
    if(fp == NULL || feof(fp)){
        return NULL;
    }
    stuStruct *pStuTemp = NULL;
    ushort nStuLen = 0;

    // 读取结构体大小
    if(fread_s(&nStuLen , sizeof(nStuLen) , sizeof(ushort) , 1 , fp)
       == 0){
        return NULL;
    }
    // 为结构体分配空间
    pStuTemp = (stuStruct *)malloc(nStuLen * sizeof(uchar));
    if(pStuTemp == NULL){
        printf("内存分配失败\t\n");
        exit(1);
    }
    // 将指针置回结构体起始位置
    fseek(fp , -(long)(sizeof(ushort)), SEEK_CUR);
    // 从文件中读取结构体数据到结构体内存中
    fread_s(pStuTemp , nStuLen , sizeof(uchar) , nStuLen , fp);
    
    return pStuTemp;
}

/*
函数功能：
    删除文件中文件指针所在位置的学生结构体信息
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void delFile(FILE *fp){
    if(fp == NULL || feof(fp)){
        return;
    }
    // 判断文件是否结束，并将指针偏移至删除位
    ushort nIsEof = 0;
    if(fread_s(&nIsEof , sizeof(ushort) , sizeof(ushort) , 1 , fp)
       == 0 || nIsEof == 0){
        return;
    }

    // BUG: 必须重置下指针才能正常写入文件
    fseek(fp , 0 , SEEK_CUR);

    // 将删除标志位置为 0xFFFF
    ushort isDel = 0xFFFF;
    fwrite(&isDel, sizeof(ushort), 1, fp);

    // 将指针置回该结构体在文件中的起始位置
    fseek(fp , -(long)(sizeof(ushort) * 2) , SEEK_CUR);
}

/*
函数功能：
    打印所有未被删除的学生信息
    如打印所有则在打印完后将指针指向文件头部
    如打印指定则打印完后将指针指向该结构体在文件中的起始位置
参数：
    *fp    : 数据文件指针
    nPreId : 如赋值为0则打印所有学生信息
             否则只打印第nPreId个学生信息
返回值：
    0 没有查找到；非0 查找到
*/
int echoFile(FILE *fp, int nPreId){
    if(fp == NULL){
        return 0;
    }
    
    // 将文件指针指向文件起始位置
    fseek(fp , 0 , SEEK_SET);
    stuStruct *pStu;
    // 序号
    int nId = 1;
    // 循环打印
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // 被删除的数据不打印
            // 释放空间
            free(pStu);
            continue;
        }
        if(nPreId == 0){
            printStuInfo(pStu , nId);
        }
        else if(nId == nPreId){
            printStuInfo(pStu , nId);
            ++nId;
            break;
        }
        ++nId;
        // 释放空间
        free(pStu);
    }
    // 循环完成后 nId 如果没有变化则说明文件中没有学生信息
    if(nId == 1){
        printf("文件中没有任何学生信息\t\n");
        fseek(fp , 0 , SEEK_SET);
        return 0;
    }
    // 判断是否找到指定序号信息
    if(nPreId != 0 && nId <= nPreId){
        printf("输入的序号太大了！\t\n");
        return 0;
    }
    else if(pStu != NULL){
        // 如果找到则将文件指针指向该结构体在文件中的起始位置
        fseek(fp , -(long)(pStu->nStuLen) , SEEK_CUR);
        return 1;
    }
    
    // 将文件指针指向文件头
    fseek(fp , 0 , SEEK_SET);
    return 1;
}

/*
函数功能：
    在文件中查找结构体，
    若指定只查找匹配到的第一个学生信息，找到后将文件指针置向
    查找到的结构体在文件中的起始位置；
    否则查找结束后将文件指针指向文件起始位置
参数：
    *fp     : 数据文件指针
    *szBuff : 待查找的字符串
    nSelect : 查找模式 FINDALL FINDONE
返回值：
    0 没有查找到；非0 查找到
*/
int findFile(FILE *fp , uchar *szBuff, int nSelect){
    if(fp == NULL || szBuff == NULL){
        return 0;
    }

    fseek(fp , 0 , SEEK_SET);
    stuStruct *pStu;
    // 保存学号、姓名、电话的二维数组
    uchar szStuArr[ 3 ][ MAXINFOLEN ];
    ushort nStuArrLen[ 3 ];
    // 序号
    int nId = 1;
    // 是否找到信息标志位
    int isFind = 0;
    // 遍历
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // 被删除的数据不遍历
            // 释放空间
            free(pStu);
            continue;
        }
        // 保存学号、姓名、电话为普通字符串
        saveStuPInfo(pStu , nStuArrLen , szStuArr);
        // 判断当前学生信息是否为要查找的学生信息
        if(strstr(szStuArr[ ID ] , szBuff) != NULL ||
           strstr(szStuArr[ NAME ] , szBuff) != NULL ||
           strstr(szStuArr[ TEL ] , szBuff) != NULL){
            // 打印
            printStuInfo(pStu , nId);
            // 将是否找到标志位置为已找到
            isFind = 1;
            // 如果指定了查找第一个匹配到的信息则结束查找，返回函数
            if(nSelect == FINDONE){
                // 将文件指针指向结构体在文件中的起始位置
                fseek(fp , -(long)(pStu->nStuLen) , SEEK_CUR);
                return 1;
            }
        }
        ++nId;
        // 释放空间
        free(pStu);
    }

    // 将文件指针指向文件头部
    fseek(fp , 0 , SEEK_SET);

    // 检查是否找到
    if(isFind == 0){
        printf("没有找到指定的学生信息！");
        return 0;
    }
    else{
        return 1;
    }
}

/*
函数功能：
    统计所有学生人数，C语言成绩最高分、最低分、平均分、总分
参数：
    *fp : 指向数据文件的指针
返回值：
    无
*/
void countStuInfo(FILE *fp){
    if(fp == NULL){
        return;
    }
    
    // 将文件指针指向文件起始位置
    fseek(fp , 0 , SEEK_SET);
    stuStruct *pStu;
    // 学生总数
    uint nCount = 0;
    // 最高分
    float fMaxScore = 0;
    // 最低分
    float fMinScore = 100.00;
    // 平均分
    double fAveScore = 0;
    // 总分
    double fCouScore = 0;
    // 循环打印
    while((pStu = readFile(fp)) != NULL){
        if(pStu->isDel == 0xFFFF){
            // 被删除的数据不遍历
            continue;
        }
        // 更新最高分
        fMaxScore = ((pStu->fScore) > fMaxScore) ?
                    pStu->fScore : fMaxScore;
        // 更新最低分
        fMinScore = ((pStu->fScore) < fMinScore) ?
                    pStu->fScore : fMinScore;
        // 更新总分
        fCouScore += (double)(pStu->fScore);
        ++nCount;
    }
    // 循环完成后 nCount 如果没有变化则说明文件中没有学生信息
    if(nCount == 0){
        printf("文件中没有任何学生信息\t\n");
    }
    else{
        // 更新平均分
        fAveScore = fCouScore / (double)nCount;
        printf("一共有：%d 个学生\t\n最高分：%.2f分\t\n最低分：%.2f分\t\n平均分：%.2lf分\t\n总分：%.2lf分\t\n",
               nCount, fMaxScore, fMinScore, fAveScore , fCouScore);
    }
    
    // 将文件指针指向文件头
    fseek(fp , 0 , SEEK_SET);

}

/*
函数功能：
    打印文件存储情况
参数：
    *fp : 数据文件指针
返回值：
    无
*/
void echoMem(FILE *fp){
    if(fp == NULL){
        return;
    }

    // 将文件指针指向文件初始位置
    fseek(fp , 0 , SEEK_SET);

    ushort nMem = 0 , nTemp = 0;
    int isEmp = 0;
    long long nNum = 1;
    // 循环读取存储块大小
    while(fread_s(&nMem, sizeof(ushort), sizeof(ushort), 1, fp)
          != 0){
        // 检查此块是否被删除
        fread_s(&nTemp , sizeof(ushort) , sizeof(ushort), 1, fp);
        isEmp = (nTemp == 0) ? 0 : 1;
        printMem(nMem , isEmp, &nNum);

        // 将文件指针指向下一块
        fseek(fp , (long)(nMem - sizeof(ushort) * 2) , SEEK_CUR);
    }
    printf("\t\n");
}

/*
函数功能：
    打印内存块
参数：
    nMem  : 打印数量
    isEmp : 打印类型 非0 空内存 0 已使用内存
    nNum  : 计算已打印的内存的数量，控制输出
返回值：
    无
*/
void printMem(ushort nMem , int isEmp, long long *nNum){
    if(nMem == 0){
        return;
    }
    char cUsed[] = "■";
    char cFree[] = "□";
    while(nMem > 0){
        printf("%s" , (isEmp == 0) ? cUsed : cFree);
        if(*nNum % 4 == 0 && *nNum % 48 != 0){
            printf(" ");
        }
        --nMem;
        ++(*nNum);
    }
}