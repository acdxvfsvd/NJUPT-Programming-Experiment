int readBuf(char* buf, int n)
{
    char ch;
    int i = 0;
    getchar();
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
    return i;
}
