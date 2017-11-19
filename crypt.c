int doCipher(char* buf, int length, char* dest, int operate, char* key, int keyLength, int algorithm)
{
    unsigned char* temp = (char*)malloc(length * 2 + 10);
    memset(temp, 0, sizeof(temp));
    int result = 0;
    if (algorithm == 1)
    {
        if (operate == 0)
        {
            result = teaEncrypt(buf, length, temp, key);
            if (result)
                result = hexEncode(temp, length, dest);
            else 
            {
                free(temp);
                return result;
            }
        }
        else
        {
            result = hexDecode(buf, length, temp);
            if (result)
                result = teaDecrypt(temp, length / 2, buf, key);
            else
            {
                free(temp);
                return result;
            }
        }
    }
    else
    {
        if (operate == 0)
        {
            result = xorCipher(buf, length, temp, key, keyLength);
            if (result)
                result = hexEncode(temp, length, dest);
            else 
            {
                free(temp);
                return result;
            }
        }
        else
        {
            result = hexDecode(buf, length, temp);
            if (result)
                result = xorCipher(temp, length, dest, key, keyLength);
            else
            {
                free(temp);
                return result;
            }
        }
    }
    free(temp);
    return result;
}

int hexEncode(unsigned char* src, int length, char* dest)
{
    int i = 0, result = 0;
    while (i < length)
    {
        snprintf((dest + 2 * i), 3, "%02X", *(src + i));
        i++;
    }
    result = 1;
    return result;
}

int hexDecode(char* src, int length, unsigned char* dest)
{
    int i = 0, result = 0;
    unsigned char ch = 0;
    if (length % 2 == 1)
    {
        return result;
    }
    for (i = 0; i < length; i += 2)
    {
        ch = hex2int(src[i]) * 16;
        ch += hex2int(src[i + 1]);
        *(dest + i / 2) = ch;
    }
    result = 1;
    return result;
}

int hex2int(char hexch)
{
    if (hexch >= '0' && hexch <= '9')
    {
        return hexch - '0';
    }
    else if (hexch >= 'a' && hexch <= 'f')
    {
        return hexch - 'a' + 10;
    }
    else if (hexch >= 'A' && hexch <= 'F')
    {
        return hexch - 'A' + 10;
    }
    return -1;
}

int xorCipher(char* src, int length, unsigned char* dest, char* key, int keyLength)
{
    int result = 0;
    char* subkeys = genSubkeys(key, keyLength, length);
    int i;
    for (i = 0; i < length; i++)
    {
        dest[i] = src[i] ^ subkeys[i];
    }
    free(subkeys);
    result = 1;
    return result;
}


char* genSubkeys(char* key, int keyLength, int srcLength)
{
    char* res = (char* )malloc(srcLength + 10);
    memset(res, 0, sizeof(res));
    int i = 0, offset = 0;
    while(i < srcLength)
    {
        offset = (offset + 53) % keyLength;
        *(res + i) = key[offset];
        i++;
    }
    return res;
}

int encodePKCS5Padding(unsigned char* buf, int length, int blockLength)
{
    int pad = 1;
    int i;
    while((pad + length) % blockLength != 0)
    {
        pad++;
    }
    for (i = 0; i < pad; i++)
    {
        buf[length + i] = pad;
    }
    return length + pad;
}

int decodePKCS5Padding(unsigned char* buf, int length, int blockLength)
{
    int i;
    int pad = buf[length - 1];
    for (i = 0; i < pad; i++)
    {
        buf[length - i] = 0;
    }
    return length - pad;
}

int teaEncrypt(unsigned char* src, int length, unsigned char* dest, char* key)
{
    int result = 0;
    int i = 0, j = 0;
    length = encodePKCS5Padding(src, length, 8);
    unsigned long* k = (unsigned long*)key;
    unsigned long a = k[0], b = k[1], c = k[2], d = k[3];
    unsigned long delta = 0x9E3779B9;
    unsigned long* v = NULL;
    unsigned long sum = 0;
    unsigned long y, z;
    for (i = 0; i < length; i += 8)
    {
        v = (unsigned long*)(src + i);
        sum = 0;
        y = v[0];
        z = v[1];
        for (j = 0; j < 48; j++)
        {
            sum += delta;
            y += ((z<<4) + a) ^ (z + sum) ^ ((z>>5) + b);
            z += ((y<<4) + c) ^ (y + sum) ^ ((y>>5) + d);
        }
        v[0] = y;
        v[1] = z;
    }
    result = 1;
    return result;
}

int teaDecrypt(unsigned char* src, int length, unsigned char* dest, char* key)
{
    int result = 0;

    return result;
}