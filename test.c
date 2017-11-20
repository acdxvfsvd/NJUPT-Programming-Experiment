#include "crypt.h"

int main()
{
    char key[] = "asdfghjklzxcvbnm";
    char buf[60];
    strcpy(buf, "THIS IS A TEST MESSAGE");
    char temp[60] = {0};
    char dest1[60] = {0};
    int i = 0;
    teaEncrypt(buf, strlen(buf), temp, key);
    hexEncode(temp, 24, dest1);
    printf("%s\n", dest1);
    char dest2[60] = {0};
    memset(temp, 0, 40);
    hexDecode(dest1, 48, temp);
    teaDecrypt(temp, 24, dest2, key);
    for (i = 0; i < 24; i++)
    {
        printf("%c", dest2[i]);
    }
    printf("\n%d\n",sizeof(unsigned long));
}