char* my_strstr(const char* pdest, const char* psrc)
{
    if (!*psrc)
        return (char*)pdest;
    const char* ptemp = pdest;
    const char* const key = psrc;
    while (*pdest++ && *psrc)
    {
        if (*pdest == *psrc) {
            psrc++;
            ptemp = pdest;
        }
        else
            psrc = key;
    }
    if (!*psrc)
        return (char*)ptemp - strlen(key) + 1;
    return NULL;
}