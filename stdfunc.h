#pragma once
// <string.h>
#include <stddef.h>


size_t my_strlen(const char* p) {
	size_t str_len = 0;
	while (*p++)
		str_len++;
	return str_len;

}

char* my_strchr(const char* p, int ch) {

	while (*p++)
		if (*p == ch)
			return (char*)p;

	if (ch == '\0') // e�er aranan null karakter ise p zaten o an orada oldu�u i�in direkt p yi return edebiliriz.
		return (char*)p;

	return NULL; // e�er aranan bulamazsa nullptr d�nd�r
}


char* my_strrchr(const char* p, int c)
{
	// 2 yol var. birincisi k�t�. yaz�n�n sonuna gidip. sonra geri gelirken 
	// ilk bulunan yerde return edilir. ama dezavantaja. �ok b�y�k ise yaz�.
	// en sona gitmek geri gelmek �ok maaliyetli.

	// verimli yol a�a��da.

	const char* pfound = NULL;

	while (*p)
	{
		if (*p == c) // burada 10 kerede denk gelse en son denk gelenin indisini tutar
			pfound = p;
		++p;
	}

	if (c == '\0') // e�er c null char ise zaten art�r�lm�� olan p yi return eder.
		return (char*)p;	// ��nk� p buraya geldiyse en son olan '\0'tedir.

	return (char*)pfound;

}