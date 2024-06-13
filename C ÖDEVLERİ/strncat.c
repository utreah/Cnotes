typedef unsigned int size_t;
char* my_strncat(char* pdest, const char* psrc, size_t nwords)
{
	const char* ptemp = pdest;
	while (*pdest)
		++pdest;
	while (nwords-- && (*pdest++ = *psrc++))
		;

	return (char*)ptemp;
}