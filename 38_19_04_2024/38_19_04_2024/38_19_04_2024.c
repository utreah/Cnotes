/*
		YAZILARIN KAR�ILA�TIRILMASI - 2
	char s1[SIZE] = {0};
	char s2[SIZE] = {0};

	printf("iki adet isim girin : ");
	(void)scanf("%s%s", s1, s2);

	int cmp_result = strcmp(s1, s2);

	if (cmp_result > 0) // herhangibir pozitif de�er 1 de�il
		printf("%s > %s", s1, s2);
	else if (cmp_result < 0) // herhangibir negatif de�er -1 de�il
		printf("%s < %s", s1, s2);
	else
		printf("%s = %s", s1, s2);

*/

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

}
/*
	M�LAKAT:
		M�lakatlarda belirli bir kelimenin sonda olup olmad���n� bulabilecek bir program yazd�r�labiliyor.
			-Sonda olup olmad���n� kontrol etmek i�in arama yap�lacak metinin sonuna adresle yaz�n�n boyutu toplanarak gidilir. (p1 + strlen(p1))
			-E�er aranan kelime metinden/yaz�dan uzun ise UB olu�turaca��ndan false(0) de�eri return edilir.
			-strcmp fonksiyonu kullanarak sonda olup olmad��� kontrol edilir.
			-Parametre olarak, ilk parametre -> 'yaz�n�n adresi + yaz�n�n uzunlu�u - aranan yaz�n�n uzunlu�u' olur. ikinci parametre ise
				aranan yaz�n�n adresi.

*/
#include <stddef.h>
int is_at_end(const char* p1, const char* p2)
{
	size_t len1 = strlen(p1);
	size_t len2 = strlen(p2);
	if (len2 > len1)
		return 0; // p1 bizim i�erisinde yaz� arayaca��m�z metin. E�er aranacak kelime/yaz�n�n uzunlu�u ana metinden uzunsa bu
					// ub olu�turaca�� i�in uzunluklar�n� kar��la�t�r�yoruz. E�er p2 daha uzunsa boolean 0 d�nd�r�yoruz.

	return !my_strcmp(p1 + len1 - len2, p2); // p1 + len1 - len2 i�lemi bize ilk dizinin bitti�i yerden arad���m�z kelimenin
												// uzunlu�unu ��kararak strcmp'de ar�yor. E�er sonu� 0 ise kelime bulunmu�tur demek.
													// true olmas� i�in 'not' operat�r� ile tersine �eviriyoruz. ��nk� fonksiyon yanl��l�k durumunda
													// non-zero bir de�er d�nd�r�yor.
}

char* prepend(char* p1, const char* p2) // �dev, append fonksiyonun tersi bu. Append yaz�n�n sonuna ekleme yaparken prepend ba��na ekleme yap�yor.
{											// bunun kodunu yazmam gerek.

}


/*
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	
*/
// �u anl�k std fonksiyonlar�na ara verdik. �imdi EN ZOR KISIMA BA�LIYORUZ.
/*
	Neler bu konular?
-string literals
-pointer arrays
-pointer to pointer
-void pointers
-function pointers
-multi-dimensional arrays
-Dynamic Memory Management

*/
/*
		STRING LITERALS
	-�ift t�rnak i�inde bulunan yaz�lar birer tokend�r. "UGUR" -> bu bir token ve adresi var. Bu tokenlara 'string literals' denir.
		Asl�nda "ugur" != "ersoy" gibi string literalleri kar��la�t�r�l�rsa burada yaz�lar de�il adresler kar��la�t�r�lm�� olur.
	-Literal, constant(sabit) anlam�na gelebiliyor. Baz� yerlerde constant baz� yerlerde literal denmesiyle kar��la�abiliriz.
	-C'de 'A' -> bir karakter sabiti, CPP'de ise karakter literali olarak adland�r�lm��.
	-String literallarinin sonunda da null karakteri vard�r.
	-"UGUR" -> bu 5 karakterli bir string literal� ve veri t�r� -> char[5] (Sonunda null karakter var ondan 5 karakter)
	-char str[3]; ben str'yi bir ifade i�erisinde kulland���mda array decayden dolay� str'nin adresini nas�l yerini al�yorsa
		bir string literalini ifadede kulland���mda string literalinin adresi yerini al�r.
		-|*"ugur" -> string literali dereferencing(i�erik) operat�r�n� alabilir. 
			-| string literalinde i�erik operat�r� kullan�ld���nda de�eri o stringin ilk karakteridir.
				Mesela *"ugur" i�in -> 'u'
	-E�er bir string literalinin yan�na subscript operat�r� kullan�l�rsa: 
		-| "ugur"[2] -> burada 2. 'u' karakterinin adresi g�sterilmi�.
		-| 2["ugur"] -> burada da 2. 'u' karakterinin adresi g�steriliyor. Bu subscript operat�r� kullan�ld���nda derleyicinin �retti�i koddan dolay�.
			p[i] asl�nda *(p + i) bundan dolay� i[p] oldu�unda da �retilen kod -> *(i + p) 

	-String literallar� fonksiyonlara adres de�i�keni alan parametrelere direkt yollanabilir.
		char str[100];
		strcpy(str, "UGUR ERSOY"); // str dizisine UGUR ERSOY'u kopyalar

		char *p = "Oyku Ersoy"; // "Oyku Ersoy" �eklinde bir string literal� olu�turarak derleyiciye bir dizi olu�turtuyorum
									// ve bu dizinin adresini bir pointerda tutuyorum.
		puts(p); yukar�dakini yazd�r�r

		printf("uzunluk : %zu\n",strlen(p)); -> uzunluk 10 yazar.
		printf("uzunluk : %zu\n",strlen("OYKU ERSOY")); -> uzunluk 10 yazar.

	-String literallari hem C dilinde hem de CPP dilinde salt okuma(read-only) ama�l� kullan�labilir.
		string literallarini de�i�tirme giri�imi her iki dilde de tan�ms�z davran��t�r.
		-| char* p = "cetin";
		   puts(p); // ekrana cetin yazd�r�r
		   *p = 'M'; // hop tan�ms�z davran��
	-String literalleri veri t�r� olarak char[SIZE] olsa da sadece okuma ama�l� kullan�labilirler. 
		-|Bundan dolay� string literalinin adresini bir de�i�kende tutacaksak o de�i�keni 'const' keywordu ile bildirmeliyiz.
			-| const char* p = "string literali";
		-|C dilinde string literali char t�r�nde, CPP'de ise const char t�r�ndedir.

	-Bir string literalini parametresi pointer olan bir fonksiyona arg�man olarak g�nderilecekse, parametrenin
		const char* t�r�nden olmas� gerek!
	-string literalleri statik �m�rl� dizilerdir.
		a)program�n sonuna kadar bellekte tutuldu�u anlam�na geliyor
		b)�zel bir segmentte tutuluyor
		c)�al��t��� sistemin ne oldu�una belli olarak alan� �ok ya da az olabilir.
	
	-Bir fonksiyon asla dinamik �m�rl� bir nesnenin adresini/de�erini d�nd�rmemelidir.	
		-|Adres d�nd�ren bir fonksiyon bir string literalini d�nd�rebilir.

	-Ayn� string literali ayn� yerde ya da farkl� yerlerde tutulmas� tamamen derleyiciye ba�l�(line 184)
		Yani ayn� string literali i�in de�i�ik adreste kullanabilir, ayn� adresi de kullanabilir. Tamamen derleyiciye ba�l�.
		 "ahmet" == "ahmet" unspecified behaviour
			char *p1 = "emre";
			char *p2 = "emre";

			if(p1 == p2)
				printf("evet esit\n");			
			else
				printf("hayir degil\n");

			Evette yanl��
			hay�rda yanl��
			Unspecified behavior.belirsiz davran��.
			Bir�ok derleyicide evet yada yanl�� olmas� durumunu se�ebiliyoruz.


		soru
	1. char p[] = "maya";  UB mi
	2. char * ptr = "maya";  UB mi


	1. char diziye ilk de�er verme sentaks�n�n bile�eni.yani buradaki mert yaz�s� bellekte ayr� bir
	dizide tutulmayacak.Ayr�ca derleyici taraf�ndan olu�turulan bir dizi yok.
	yani burada p[0] = 'K'; yap�labilir. UB YOK.

	2. burada iki ayr� de�i�ken var asl�nda.Az �nce diziyi de�i�tirmek UB de�il dedik ama
	burada ptr bir string literalini g�sterdi�i i�in bu yaz�y�(string literalini) de�i�tirmek UB dir.
	Ayr�ca "maya" yaz�s�(yani str literali) program�n ba��ndan sonuna kadar memoryde kalacak.

	String Literalleri bir istisna hari� / yukar�daki hari� yani
	------------------------------------------------------------

	1 compile time da static olarak bak�l�nca t�r� char olan dizilerdir.

	2 bu dizilerin set ama�l� kullan�lmas� UB dir.

	3 bu diziler static �m�rl� dizilerdir.

	-printf("UGUR");
		-| printf'in parametresi const char* idf biz burada char*'a string literalinin adresini yollayarak ekrana 
			'UGUR' yazd�r�yoruz. Yani string literalini bir parametre olarak kullanabiliriz. Ek olarak, bunu bir kere �a��rm�� olsakta
				UGUR string literali program�n sonuna kadar bellekte kalacak.
	-string literallerinin statik olmas�n�n bizi ilgilendiren baz� �eyleri var.
		-| Dinamik �m�rl� adres de�i�kenlerinin tuttuklar� adresler return edilemez. Bu Undefined Behaviour fakat string literallarinin adresi
			d�nd�r�lebilir ��nk� statik.
				char * get_month_name(int m)
					{
						switch(m)
							{
								case 1: return "ocak";
								case 2: return "subat";
								....
								....
								....
								case 12: return "aralik";
			
							}
						return "";
					}

					mesela yukar�daki kodda UB yok.
					��nk� string literalleri static �m�rl�.
	-String literallarinin statik olmas�n�n dezavantajlar�da var. Mesela diyelim ki, �yle bir sistemde �al���yoruz ki belle�imiz k�s�tl�. 
		Bu durumda s�rekli string literali kullanamay�z ��nk� bellekte program sonuna kadar yer kapl�yor.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
M�LAKAT SORUSU: Benzerlikler ve farkl�l�klar

	int main(void){
		char str[] = "UGUR"; // Burada str ad�nda bir dizi tan�ml�yorz ve buna ilk de�er veriyoruz.
								// Bulundu�u blok/fonksiyondan ��k�nca �mr� sona erer.
								//Burada tan�mlanan 1 varl�k var, str.
		char* p = "ERSOY"; // Burada ise "ERSOY" string literalinin adresini bir adres tutan de�i�ken t�r�ne cast ediyoruz.
							// string literali program�n sonuna kadar bellekte tutulur
							// Burada tan�mlanan 2 varl�k var, p ve "ERSOY"
	
	}

		
*/
#include <string.h>
#include <stdio.h>
int main(void) {
	char str[] = "ugur";
	char* p = "ersoy";
	strcpy(p, str); // UB

}
int main(void) {
	char* p1 = "Ugur Ersoy";
	char* p2 = "Ugur Ersoy";

	if (p1 == p2) 
		printf("Dogru");
	else
		printf("Yanl��");


}

char old_file_name[SIZE];
char new_file_name[SIZE];

printf("Dosya ismini girin \n");
sgets(old_file_name);

//tasklar a�a��da �imdi.

// dosya ismini new file name e kopyala.
strcpy(new_file_name, old_file_name);
printf("(%s) ---> (%s)\n", old_file_name, new_file_name);

// dosyan�n uzant�s� yoksa uzant�s�n� txt yap.
// dosya uzant�s� jpg ise dosya uzant�s�n� gif olarak de�i�tirin
// E�er dosyan�n uzant�s� .xls ise uzant�s� silinecek.
// di�er t�m durumlarda uzant�y� .dat yap�n�z.

char* p = strrchr(new_file_name, '.'); // son nokta �nemli ��nk� dosya ad�nda da . olabilir.

if (!p)
strcat(new_file_name, ".txt");

else if (!strcmp(p, ".jpg"))
strcpy(p, ".gif");

else if (!strcmp(p, ".xls"))
*p = '\0';  // strcmp(p,"") te olurdu

else
strcpy(p, ".dat");

printf("(%s) ---> (%s)\n", old_file_name, new_file_name);
/*

	puts("Ayhan\n");->ayhan yazar ve newline b�rak�r.
	puts("Ayhan\tnecati\thasan"); tab b�rak�r.
	mesela

	"mustafa" yazd�rmak istiyorum
	puts("\"mustafa\"");

	ba�a ve sona \ i�areti koymak istersek
	puts("\\ahmet\\");

	puts("\\\\\"jale\"\\\\\n");

	file path yazarkende
	(void)fopen("c:\\files\\file.txt", "r");

	const char p* = "\x42URS\x41"; -> ekrana yazd�rd���m�z zaman BURSA yazar. \x42 -> B , \x41 -> A
	const char p* = 
	0"" -> string literalleri asl�nda karakter sabitleriyle de�erini alm�� dizilerdir.
	"burak" -> b nin kod no su, u nun kod nosu .... �eklinde gidiyor.

	mesela

	"\x42URS\x41" -> "BURSA" demektir. x42 B nin kodudur.
	burada U hexadecimal bir char e�il.
	puts("\x42ebe") burada hexadecimal digit g�rd��� s�rece dahil ediyor ve hata al�n�r burada.
	too big for character hatas� al�n�r.
	puts("\101") -> buras� octal say� sisteminde yaz�lm�� ve 3 karakter limiti var.hata olu�muyor.
	puts("\10132") -> mesela 32 yi dahil etmedi ��nk� 3 karakter limiti var.

	puts("\10132\10243") -> A32B43 yazar.

	�ift t�rnak kullanmak i�in
	""ugur"" -> �eklinde yazarsak hata.  T�rnaklar� escape sequence olarak yazmal�y�z.
	"\"ugur\"" -> b�yle olursa "ugur" yaz�l�r

	Alttaki bu string literali yanl�� ��nk� bir alt sat�ra ge�ti�inden dolay� literal bozuldu. Bunu b�yle kullanmak i�in ara�lar var.
	"UGUR ERSOY C DERSLER�NE MART AYINDAN BER� KATILMIYOR VE
	KAYITLARDA �OK GER�"

	1- Ters b�l� karakteri koymak. (makrolardaki gibi) // Ters slash kullan�ld���nda aradaki bo�luklarda say�l�yor.
		"UGUR ERSOY \
xxxxxxxxxxxVE OYKU ERSOY" // x'leri bo�luk olarak d���n :D string literali print edildi�inde normalde 1 karakter bo�luk olsa bile
							// alt sat�ra ge�tikten sonra alignment i�in koyulan bo�luklarda yaz�ya dahil edilir.

	2-Whitespace ile ayr�lm��, aralar�nda ba�ka bir karakter bulunmayan string literalleri compile time'da birle�tirilir
		-| "UGUR" "ve" "OYKU" "ERSOY" -> bu birle�tirilecek ve "UGUR ve OYKU ERSOY" olacak.
		-| char* p = "UGUR"
				"ve"
				"OYKU"
				"ERSOY"; // bu da birle�tirilir ��nk� aralar�nda sadece whitespace karakteri var.



	"" -> null string literal -> '\0'null karakter.

*/


/*
	�DEV
	char *strprepen(char *pdest,const char * psource)
	pdest in ba��na psource u ekliyor. bunu yaz. umut kotankiran -> kotankiran umut yazacak

	========================================================================
	========================================================================
	========================================================================

	Birde fonksiyonlar�n n li hali var.fonksiyon bildiriminde fazladan n parametresi var.

	strcpy i�in strncpy  -> source adresteki yaz�n�n ilk n karakterini dest e kopyalar.
	strcat i�in strncat  -> source adresteki yaz�n�n ilk n karakterini dest in sonuna ekler
	strcmp i�in strncmp  -> source adresteki yaz�n�n ilk n karakterini dest ile k�yaslar.

*/