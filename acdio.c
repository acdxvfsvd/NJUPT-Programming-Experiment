int readNum()
{
    char* buf = malloc(11);
    memset(buf, 0, 11);
    char ch;
    int i = 0;
    int result;
    while(i < 10)
    {
        *(buf + i) = 0;
        ch = getchar();
        if (ch == '\n' || ch == '\r')
        {
        	if (ch == '\r') getchar();
            break;
        }
        if (ch < '0' || ch > '9')
        {
            memset(buf, 0, 11);
            free(buf);
            fflush(stdin);
            return -1;
        }
        *(buf + i) = ch;
        i++;
    }
    result = atoi(buf);
    free(buf);
    return result;
}

int readBuf(char* buf, int n)
{
    char ch;
    int i = 0;
    while (i < n)
    {
    	*(buf + i) = 0;
        ch = getchar();
        if (ch == '\n' || ch == '\r')
        {
        	if (ch == '\r') getchar();
            break;
        }
        *(buf + i) = ch;
        i++;
    }
    fflush(stdin);
    return i;
}
