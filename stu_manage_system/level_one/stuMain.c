#include "myStu.h"

int main(){

#ifdef DEBUG // �ض���������
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
#endif

    char a[] = "���ĳ���";

    printf("�ַ����ݣ�%s\n�ַ����ȣ�%d\n�����С��%d\n" , a , strlen(a) , sizeof(a));

    system("pause");
    return 0;
}