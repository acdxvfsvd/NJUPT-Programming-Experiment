#include "crypt.h"

int main()
{
    char key[] = "asdfghjk";
    char buf[] = "flag{coding_gay}";
    char temp[40] = {0};
    char dest1[40] = {0};
    xorCipher(buf, 16, temp, key, 8);
    hexEncode(temp, 16, dest1);
    printf("%s\n", dest1);
    char dest2[40] = {0};
    memset(temp, 0, 40);
    hexDecode(dest1, 32, temp);
    xorCipher(temp, 16, dest2, key, 8);
    printf("%s\n", dest2);
}