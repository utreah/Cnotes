#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <iostream>
#include <ctype.h>
#define SIZE 100
/*
int main()
{
	char arr1[SIZE];
	char arr2[SIZE];
	printf("Enter two words: ");
	scanf("%s%s", arr1, arr2);
	printf("[%s]     [%s]\n", arr1, arr2);

	int len1 = 0;
	while (arr1[len1])
		len1++;	
	int len2 = 0;
	while (arr2[len2])
		len2++;

	if (len1 != len2) {
		printf("UZUNLUKLAR AYNI DEGIL!\n");
		return 0;
	}
	int counts[26] = { 0 };
	for (int i = 0; arr1[i] != '\0'; ++i) {
		++counts[toupper(arr1[i]) - 'A'];
		--counts[toupper(arr2[i]) - 'A'];
	}

	for (int i = 0; i < 26; i++)
		if (counts[i]) {
			printf("Degil\n");
			return 0;
		}
	printf("anagram");
}
*/
			/*----------------------------------------------YAZIDAN SAYIYA/SAYIDAN YAZIYA D�N���MLER--------------------------------------*/
int main(void)
{
	char str[SIZE] = { '5' };
	printf("%d", str[0] - '0');
}
	
			/*----------------------------------------------YAZIDAN SAYIYA/SAYIDAN YAZIYA D�N���MLER--------------------------------------*/
// Comment Lines
/*
-�eviri i�lemi olmadan �nce kodtan ��kar�l�r
-Preprocessor direktiflerinden �nce kodtan ��kar�l�yor
-Nested comment block YOK!
-En iyi a��klama hi� yap�lmayan a��klama
-Code -> self explanatory (kendini a��klayan) olmal�
-Debug s�recinde baz� kodlar� comment out etmek i�in kullan�labilir
			/* #include <stdio.h> */ // -> bu ppd �al��t�r�lmaz

/*Bu bir a��klama*/
// bu bir a��klama
/*�nce yorum sonra kod olabilri*/ int test;
int test2; /*Once kod sonra yorum olabilir*/
/*
	DOSYANIN �SM� .dosya uzantisi 
	DOSYA A�IKLAMASI
	YAZAR(author)	
	last update date
	LISANS(VAR ISE)
	l�CENSE:
	*/
					/*----------------------------------------------WARNINGs--------------------------------------*/
/*
-Warningleri kodu commit etmeden �nce KESINLIKLE ��zmeliyiz.

int x; // unreferenced X 
int y = x + 5; // uninitialized X

Etkisiz kod

	5;
	a;
	a + 5; hepsi etkisiz kod. ge�erli, hata yok ama etkisiz.
	a == 10; etkisiz. Code has no effect
	if (x = 10) // "assignment withing the conditional statement" hatas� verir.

	A�a��s� unreachable code

	int foo(int a)
	{
		if(a == 1)
			return 10;
		else
			return 100;

		return 1000;  // hi�bir zaman ula�amayacak
	}

	fonksiyon i�ersinde infinite loop durumu olabilir.
	derleyiciler bunla ilgili mesaj verebiliyor ama vermek zorunda da de�il.

	Stack Overflow hatas�
	recursive fonksiyonlarda meydana gelir.

	fonksiyon s�rekli kendini �a��rd���nda, otomatik �m�rl� de�i�kenler s�rekli
	stackten yer harc�yor ve yeni �a�r�lan fonksiyonlar�nda otomatik �m�rl�
	de�i�kenleri stackten yer harc�yor ve stackte yer kalm�yor.
	Buna stack overflow deniyor.

	Derleyiciler bu durumu her zaman olmasada anlayabiliyorlar.

	if (x)
		return x
	return 10    // bu duruma base case deniyor.durdurma mekanizmas� gibi.



*/

// inline int;
/*
inline anahtar s�zc��� C99 ile eklendi. 
Fonksiyonlar� niteleyen bir anahtar s�zc�k denir.
inline fonksiyonlar�n ayr� bir semanti�i var.
C ile CPPdeki inline birebir ayn� de�il.
*/

/*
int (foo)(int x) // e�er foo isimli bir fonksiyonel bir makro var ise bu durumun �n�ne ge�mek i�in identifer parantez i�ine al�nabilir
int foo(int x) == int (foo)(int x) -> ayn� bunlar


*/

/*
------------------------------------------------------ -
�dev
ANAGRAM bo�luk karakterleri ve noktalama karakterleri ciddiye al�nmayacak, 
debit card -> bad credit
a gentlement -> elegant man

------------------------------------------------------ -

�dev
1.55
dizi i�in alt sequence lar aran�yor.

1234243456567956  i�imde 565 sequence aran�yor ama hem dizi hem sequence random.
------------------------------------------------------ -

�dev
SIZE + 1 boyutundaki dizide SIZE a kadar t�m say�lar var ama
bir say�dan 2 tane var. bunu bulaca��z.
2:00
algoritme karma��kl��� nedir?

------------------------------------------------------ -
*/