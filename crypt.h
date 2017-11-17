#ifndef getchar
#include <stdio.h>
#endif

#ifndef malloc
#include <stdlib.h>
#endif

#ifndef strlen
#include <string.h>
#endif

int doCipher(char* src, int length, char* dest, int operate, char* key, int keyLength, int algorithm);

int hexEncode(unsigned char* src, int length, char* dest);
int hexDecode(char* src, int length, unsigned char* dest);

int hex2int(char hexch);

int xorCipher(char* src, int length, unsigned char* dest, char* key, int keyLength);

char* genSubkeys(char* key, int keyLength, int srcLength);

int teaEncrypt(char* src, int length, unsigned char* temp, char* key);
int teaDecrypt(char* src, int length, unsigned char* temp, char* key);



#include "crypt.c"