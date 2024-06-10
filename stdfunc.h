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

char* my_strcpy(char* pdest, const char* psource)
{
	char* ptemp = pdest; // hedefin adresini geri döndüreceðimiz için ptemp deðiþkeninde adresi tutuyoruz.
	// çünkü while içerisindeki ifade'de pdest'in adresi deðiþecek.
	while (*pdest++ = *psource++) // Burada kaynaktan hedefe doðru kopyalama yapýlýr. Kaynaktan null karakter geldiðinde ve
		;						//atama operatörü ile zero deðer pdest'e atanýr ve ifade zero olacaðý için
										// döngüden çýkýlýr ve hedef deðiþkenin adresi döndürülür.
	return ptemp;
} 

char* my_strcpy2(char* pdest, const char* psource)
{
	char* ptemp = pdest;
	while (*psource) {
		*pdest++ = *psource++;
	}
	*pdest = '\0'; // burada null karakteri ekliyoruz bunun sebebi sequence point. *psource++ null karakteri geldiðinde döngüden
	return ptemp;		// çýkmasýna sebep olacaðýndan dolayý null karakterini eklemeyecek. Bizde manuel olarak ekliyoruz
}

char* my_strcat(char* p1, const char* p2)
{
	char* ptemp = p1;

	while (*p1)
		++p1; // burada kopyalama iþlemi yapýlacak yazýnýn null karakterini bulduk. Ve null karakteri dahil olmak üzere birleþtirmeye baþlayacaðýz.

	while (*p1++ = *p2++) // null karakterinin olduðu indexten itibaren yazý yapýþtýrma iþi yapýlýyor.
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
		if (*p1 == '\0') // eper *p1 NULL ise *p2'de null karakterdir. Çünkü while döngüsüne girerken ikisi de eþit olduðu için girdi.
			return 0;		// eðer farklý ise döngüden çýkacak zaten
		++p1;
		++p2;
	}

	return *p1 - *p2; // eðer *p1 büyükse pozitif, p2 büyükse negatif döndürecek. const char türünden 2 deðiþken iþleme giriyor.
	// integral promotiondan dolayý iþlem int türünde yapýlýr.
