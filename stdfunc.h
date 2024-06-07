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

	if (ch == '\0') // eðer aranan null karakter ise p zaten o an orada olduðu için direkt p yi return edebiliriz.
		return (char*)p;

	return NULL; // eðer aranan bulamazsa nullptr döndür
}


char* my_strrchr(const char* p, int c)
{
	// 2 yol var. birincisi kötü. yazýnýn sonuna gidip. sonra geri gelirken 
	// ilk bulunan yerde return edilir. ama dezavantaja. çok büyük ise yazý.
	// en sona gitmek geri gelmek çok maaliyetli.

	// verimli yol aþaðýda.

	const char* pfound = NULL;

	while (*p)
	{
		if (*p == c) // burada 10 kerede denk gelse en son denk gelenin indisini tutar
			pfound = p;
		++p;
	}

	if (c == '\0') // eðer c null char ise zaten artýrýlmýþ olan p yi return eder.
		return (char*)p;	// çünkü p buraya geldiyse en son olan '\0'tedir.

	return (char*)pfound;

}