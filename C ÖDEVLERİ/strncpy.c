typedef unsigned int size_t;
char* my_strncpy(char* pdest, const char* psrc, size_t nwords) {
	size_t i = 0;
	const char* ptemp = pdest;
	while (i++ < nwords && (*pdest++ = *psrc++))
		;
	return (char*)ptemp;
}