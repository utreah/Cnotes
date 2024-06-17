#include <stdio.h>
#include <string.h>
#include <ctype.h>
char* strichr(const char* ptr, int ch)
{
	while (*ptr) {
		if (toupper(*ptr) == toupper(ch))
			return (char*)ptr;
		ptr++;
	}
	return NULL;
}
void remove_char(char* pchr, int ch) {
	while (*pchr) {
		*pchr = *(pchr + 1);
		pchr++;
	}
}
int anagram(char* p1, char* p2)
{
	if (!*p1 || !*p2)
		return 0;
	while (*p1) {
		char* get_char_addr = strichr(p2, *p1);
		if (get_char_addr) {
			remove_char(get_char_addr, *p1);
			remove_char(p1, *p1);
		}
		!isalpha(*p1) ? p1++ : !isalpha(*p2) ? p2++ : (p1++, p2++);
	}
	return strlen(p1) == strlen(p2);
}