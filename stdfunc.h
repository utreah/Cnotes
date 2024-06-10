	#pragma once
// <string.h>
#include <stddef.h>
#include <string.h>


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

char* my_strcpy(char* pdest, const char* psource)
{
	char* ptemp = pdest; // hedefin adresini geri d�nd�rece�imiz i�in ptemp de�i�keninde adresi tutuyoruz.
	// ��nk� while i�erisindeki ifade'de pdest'in adresi de�i�ecek.
	while (*pdest++ = *psource++) // Burada kaynaktan hedefe do�ru kopyalama yap�l�r. Kaynaktan null karakter geldi�inde ve
		;						//atama operat�r� ile zero de�er pdest'e atan�r ve ifade zero olaca�� i�in
										// d�ng�den ��k�l�r ve hedef de�i�kenin adresi d�nd�r�l�r.
	return ptemp;
} 

char* my_strcpy2(char* pdest, const char* psource)
{
	char* ptemp = pdest;
	while (*psource) {
		*pdest++ = *psource++;
	}
	*pdest = '\0'; // burada null karakteri ekliyoruz bunun sebebi sequence point. *psource++ null karakteri geldi�inde d�ng�den
	return ptemp;		// ��kmas�na sebep olaca��ndan dolay� null karakterini eklemeyecek. Bizde manuel olarak ekliyoruz
}

char* my_strcat(char* p1, const char* p2)
{
	char* ptemp = p1;

	while (*p1)
		++p1; // burada kopyalama i�lemi yap�lacak yaz�n�n null karakterini bulduk. Ve null karakteri dahil olmak �zere birle�tirmeye ba�layaca��z.

	while (*p1++ = *p2++) // null karakterinin oldu�u indexten itibaren yaz� yap��t�rma i�i yap�l�yor.
		;
	return ptemp;
}

char* mystrcat(char* p1, const char* p2)
{
	strcpy(p1 + strlen(p1), p2);
	return p1;
}

char* mystr_cat(char* p1, const char* p2) {

	strcpy(strchr(p1, '\0'), p2);
	return p1;
}

int my_strcmp(const char* p1, const char* p2)
{
	while (*p1 == *p2) {
		if (*p1 == '\0') // eper *p1 NULL ise *p2'de null karakterdir. ��nk� while d�ng�s�ne girerken ikisi de e�it oldu�u i�in girdi.
			return 0;		// e�er farkl� ise d�ng�den ��kacak zaten
		++p1;
		++p2;
	}

	return *p1 - *p2; // e�er *p1 b�y�kse pozitif, p2 b�y�kse negatif d�nd�recek. const char t�r�nden 2 de�i�ken i�leme giriyor.
	// integral promotiondan dolay� i�lem int t�r�nde yap�l�r.
