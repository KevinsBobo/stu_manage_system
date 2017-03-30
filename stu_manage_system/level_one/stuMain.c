#include "myStu.h"

int main(){

#ifdef DEBUG // 重定义输出输出
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif

    char a[] = "中文长度";

    printf("字符内容：%s\n字符长度：%d\n数组大小：%d\n" , a , strlen(a) , sizeof(a));

    system("pause");
    return 0;
}