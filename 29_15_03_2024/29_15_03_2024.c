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
			/*----------------------------------------------YAZIDAN SAYIYA/SAYIDAN YAZIYA DÖNÜÞÜMLER--------------------------------------*/
int main(void)
{
	char str[SIZE] = { '5' };
	printf("%d", str[0] - '0');
}
	
			/*----------------------------------------------YAZIDAN SAYIYA/SAYIDAN YAZIYA DÖNÜÞÜMLER--------------------------------------*/
// Comment Lines
/*
-Çeviri iþlemi olmadan önce kodtan çýkarýlýr
-Preprocessor direktiflerinden önce kodtan çýkarýlýyor
-Nested comment block YOK!
-En iyi açýklama hiç yapýlmayan açýklama
-Code -> self explanatory (kendini açýklayan) olmalý
-Debug sürecinde bazý kodlarý comment out etmek için kullanýlabilir
			/* #include <stdio.h> */ // -> bu ppd çalýþtýrýlmaz

/*Bu bir açýklama*/
// bu bir açýklama
/*önce yorum sonra kod olabilri*/ int test;
int test2; /*Once kod sonra yorum olabilir*/
/*
	DOSYANIN ÝSMÝ .dosya uzantisi 
	DOSYA AÇIKLAMASI
	YAZAR(author)	
	last update date
	LISANS(VAR ISE)
	lÝCENSE:
	*/
					/*----------------------------------------------WARNINGs--------------------------------------*/
/*
-Warningleri kodu commit etmeden önce KESINLIKLE çözmeliyiz.

int x; // unreferenced X 
int y = x + 5; // uninitialized X

Etkisiz kod

	5;
	a;
	a + 5; hepsi etkisiz kod. geçerli, hata yok ama etkisiz.
	a == 10; etkisiz. Code has no effect
	if (x = 10) // "assignment withing the conditional statement" hatasý verir.

	Aþaðýsý unreachable code

	int foo(int a)
	{
		if(a == 1)
			return 10;
		else
			return 100;

		return 1000;  // hiçbir zaman ulaþamayacak
	}

	fonksiyon içersinde infinite loop durumu olabilir.
	derleyiciler bunla ilgili mesaj verebiliyor ama vermek zorunda da deðil.

	Stack Overflow hatasý
	recursive fonksiyonlarda meydana gelir.

	fonksiyon sürekli kendini çaðýrdýðýnda, otomatik ömürlü deðiþkenler sürekli
	stackten yer harcýyor ve yeni çaðrýlan fonksiyonlarýnda otomatik ömürlü
	deðiþkenleri stackten yer harcýyor ve stackte yer kalmýyor.
	Buna stack overflow deniyor.

	Derleyiciler bu durumu her zaman olmasada anlayabiliyorlar.

	if (x)
		return x
	return 10    // bu duruma base case deniyor.durdurma mekanizmasý gibi.



*/

// inline int;
/*
inline anahtar sözcüðü C99 ile eklendi. 
Fonksiyonlarý niteleyen bir anahtar sözcük denir.
inline fonksiyonlarýn ayrý bir semantiði var.
C ile CPPdeki inline birebir ayný deðil.
*/

/*
int (foo)(int x) // eðer foo isimli bir fonksiyonel bir makro var ise bu durumun önüne geçmek için identifer parantez içine alýnabilir
int foo(int x) == int (foo)(int x) -> ayný bunlar


*/

/*
------------------------------------------------------ -
Ödev
ANAGRAM boþluk karakterleri ve noktalama karakterleri ciddiye alýnmayacak, 
debit card -> bad credit
a gentlement -> elegant man

------------------------------------------------------ -

Ödev
1.55
dizi için alt sequence lar aranýyor.

1234243456567956  içimde 565 sequence aranýyor ama hem dizi hem sequence random.
------------------------------------------------------ -

Ödev
SIZE + 1 boyutundaki dizide SIZE a kadar tüm sayýlar var ama
bir sayýdan 2 tane var. bunu bulacaðýz.
2:00
algoritme karmaþýklýðý nedir?

------------------------------------------------------ -
*/