typedef unsigned int size_t;
int my_strncmp(const char* p1, const char* p2, size_t nword) {
	while (nword--){
		if (!*p2)
			break;
		if (*p1 != *p2)
			return p1 - p2;
		p1++;
		p2++;
	}
	return 0;
}