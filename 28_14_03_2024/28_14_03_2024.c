#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
/*
int main()
{
	char str[100] = { "UGUR ERSOY" };

	puts(str);// sonuna newline koyuyor puts foncksiyonu.
	char str2[100]; // E�er first initiliazation yap�lmaz ise dizinin elementlar� garbage value ile ba�lar. Bu �ekilde ba�lamakta s�k�nt� yok
				// e�er bu dizi kullan�l�r ise UB olu�ur.

	str2[0] = 'U';
	str2[1] = 'G'; // E�er sonuna '\0' koyulmaz ise UB.
	str2[2] = '\0';// bu eklendi�inde UB de�il art�k ve legal.
	// str[2] = '0'; -> 13. sat�rdaki yerine bu eklenirse UB durumu devam eder. '0' 0 karakterinin tam say� kar��l���n� verir bize.
}*/

// YAZI TUTACAK CHAR D�Z�LER�N� �LK DE�ER VERMEK/BA�LATMAK
/*
int main(void)
{
	char str[100] = { 'U', 'G', 'U', 'R' }; // �lk de�er vererek ba�lat�lan dizilerde kullan�lmayan dizi elementlar� 0 olarak set edilir.
											// yani ilk 4 element U G U R harflerini tutarken geri kalan 96 dizi elemtlar� 0'� tutar.
	char str2[4] = { 'U', 'G', 'U', 'R' }; // UB var. ��nk� t�m de�er tutabilen yerler dolu ve null karakteri i�in yer yok.
	char str3[] = { 'U', 'G', 'U', 'R' }; // Sentaks hatas� yok UB var. Dizi boyutu verilmez ise dizinin boyutu i�erisindeki tutulan elemanlar kadard�.
										// yani str3 dizisinin 4 eleman� var yani boyutu 4. Fakat null karakteri i�in yer olmad��� i�in UB.
										// tan�ms�z davran�� NTBS'nin olmamas�na kar��n bu dizinin kullan�lmas�. A�a��daki for d�ng�s�n� �rnek alabiliriz.
										// Dizide null karakter olmad��� i�in diziden ta�acak ve bu tan�ms�z davran�� olu�turur.
	for (int i = 0; str[i] != '\0'; ++i)
		putchar(str[i]);
}
*/
/*int main(void)
{
	char str[] = "UGUR"; // �ift t�rnak aras�nda yaz�lan yaz�n�n sonunda otomatik olarak null karakter koyuluyor. Bu dizinin uzunlu�u "5"
	char str[4] = "UGUR"; // Dizinin boyutu null karakteri i�ine alm�yor ise bu CPP'de bu sentaks hatas�. C'de legal sonunda null karakter yok.
						// kullan�lmad��� s�rece UB yok. Alttaki d�ng� oldu�u i�in bu deyim UB!
	// char str[] = "UGUR"; == char str[] = { 'U', 'G', 'U', 'R' }; -> bu iki dizide ayn� anlama geliyor fakat soldaki dizide null karakter 
															// var iken sa�daki dizi de null karakter YOK. En temel farklar� bu.
		
	for (int i = 0; str[i] != '\0'; ++i)
		putchar(str[i]);
}*/

// scanf'te whitespace karakteri ay�ra� olarak i� g�r�yor. Ugur Ersoy ismini girdi�imizde ekrana Ugur yazd�r�r ve Ersoy bufferda kal�r.
// 	scanf ile s��amayacak yaz�y� char array elemanlar�na atamak runtime hatas� 
								/*--------------------------------�RNEKLER--------------------------------*/
/*
int main(void)
{
	char name[20];
	char surname[20];
	int age;

	printf("Isim, soyisim ve yas giriniz:");
	scanf("%s%s%d", name, surname, &age);
	// scanf("%s", name); -> burada input olarak ugur ersoy girseydim sadece ugur'u yazd�r�rd� ve whitespace'e ay�ra�m�� gibi davran�rd�.
	printf("[%s] [%s] Hosgeldiniz, Yas: %d", name, surname, age);
	// gets() adres al�p, bufferdan t�m karakterleri al�yordu(whitespace dahil)
		// C99 ile deprecate(kullan�lmas� tavsiye edilmemesi) edildi sonraki standartlarda kald�r�ld�. 
	// sgets(name); // grts deprecate edildi�inden ve IDE hata vermesin diye necati hoca kendi fonksiyonunu yazd�.
}*/
/*
#define SIZE 100
int main(void)
{
	char str[SIZE];
	printf("Isminizi Giriniz: ");
	sgets(str);
	printf("[%s]\n", str);
	int i = 0;
	for (i = 0; str[i] != '\0'; i++)
		;
	printf("Girilen ismin uzunlugu : [%d]\n", i);
	printf("|--------------------------------------|\n");
	// Yaz�n�n sonuna karakter ekleme.
	int j = 0;
	for (j = 0; str[j] != '\0'; j++)
		;
	str[j] = 'x';
	str[j + 1] = '\0';
	printf("Karakter eklendi! -> [%s]\n", str);
	printf("|--------------------------------------|\n");
	// Yaz�y� tersten yazd�rma.
	int k = 0;
	while (str[k] != '\0')
		k++;
	for (k--; k >= 0; --k)
		putchar(str[k]);
	printf("\n");
	printf("|--------------------------------------|\n");
	// Birle�tirme!
	char s1[SIZE];
	char s2[SIZE];
	printf("Iki isim giriniz: \n");
	scanf("%s%s", &s1, &s2);
	printf("1: %s, 2: %s\n", s1, s2);
	int z;
	for (z = 0; s1[z] != '\0'; z++)
		;
	for (int b = 0; s2[b] != '\0'; b++)
		s1[z++] = s2[b];
	s1[z] = '\0';
	printf("1: %s, 2: %s", s1, s2);
	printf("|--------------------------------------|\n");
}
*/
#define SIZE 100
// Karakter arama/sayma kodu
#include <ctype.h>
int main(void)
{
	/*char str[SIZE];
	int ch;
	int cnt = 0;
	printf("Uzun bir kelime giriniz: ");
	sgets(str);
	printf("Aranacak karakteri giriniz: ");
	ch = getchar();
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ch) // b�y�k k���k ayr�m� yap�yor. Her birini bulmak i�in toupper() kullan�labilir.
			cnt++;
	}
	printf("%d adet [%c] bulundu\n", cnt, ch);
	printf("|--------------------------------------|\n");
	// Hangi karakterden ka� tane oldu�unu buluyor.
	char str2[SIZE];
	printf("Bir yazi giriniz: ");
	sgets(str2);	
	int counts[26] = { 0 };
	for(int i = 0; str2[i] != '\0'; i++)
		if(isalpha(str2[i]))
			counts[toupper(str2[i]) - 'A']++;
	for (int i = 0; i < 26; i++)
		if(counts[i])
			printf("%c:%d\n", 'A' + i, counts[i]);
	printf("|--------------------------------------|\n");
	// bir yaz�n�n ters �evrimesi.reverse algoritmas� g�r�ld� zaten.
	char str[SIZE];
	printf("bir yazi girin : ");
	sgets(str);
	printf("(%s)\n", str);

	int len = 0;

	for (int i = 0; str[i] != '\0'; i++)
		len++;

	for (int i = 0; i < len / 2; i++)
	{
		char temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
	printf("tersi = (%s)\n", str);*/

// Copy

	char s1[SIZE];
	char s2[SIZE];

	printf("iki kelime giriniz ");
	scanf("%s%s", s1, s2);

	printf("(%s) (%s)\n", s1, s2);

	int i;
	for (i = 0; s1[i] != '\0'; i++)
		;

	int k;
	for (k = 0; s2[k] != '\0'; k++)
	{
		s1[i + k] = s2[k];
	}

	s1[i + k] = '\0';

	printf("%s\n", s1);

	// remove copy

	char str[SIZE];
	char str2[SIZE];
	int ch;

	printf("bir yazi girin: ");
	sgets(str); // Ankara Antalya kahramanmaras
	printf("(%s)\n", str);

	printf("silinecek karakteri girin: ");
	ch = getchar(); //a
	int indx = 0;
	for (int i = 0; str[i] != '\0'; i++)
		if (toupper(str[i]) != toupper(ch))
			str2[indx++] = str[i];

	printf("%s", str2);
	// remove copy tek dizi ile

	char str3[SIZE];
	int ch;

	printf("bir yazi girin: ");
	sgets(str); // Ankara Antalya kahramanmaras
	printf("(%s)\n", str);

	printf("silinecek karakteri girin: ");
	ch = getchar(); //a
	int wrt_indx = 0;
	for (int i = 0; str[i] != '\0'; i++)
		if (toupper(str[i]) != toupper(ch))
			str[wrt_indx++] = str[i];

	printf("%s", str3);
	
}
/*int main() // benim yazd���m
{
    char s1[SIZE];
    char s2[SIZE];
    sgets(s1);
    sgets(s2);
    int flag = 0;
    for(int i = 0; s1[i] != '\0';i++)
        if(s1[i] != s2[i]){
            flag = 1;
            break;
        }
    if(flag)
        printf("AYNI DEG�L");
    else
        printf("AYNI");
    
}


	2 metnin kar��la�t�r�lmas� // hocan�n yazd��� -> iki metinin kar��la�t�r�lmas�


	char s1[SIZE];
	char s2[SIZE];
	printf("iki adet dizi giriniz\n");
	(void)scanf("%s%s", s1, s2);

	int i = 0;
	int flag = 0;

	while(s1[i] == s2[i])
	{
		if (s1[i] == '\0')
		{
			flag = 1;
			break;
		}
		i++;
	}

	if (flag)
		printf("diziler esit\n");
	else
		printf("diziler esit degil\n");
*/

// CUMLEDEK� KELIMELER� SAYMA
#define IN_WORD 1 // kelimenin i�inde
#define OUT_WORD 0 // kelimenin d���nda

int main(void)
{
	char str[SIZE];
	printf("yazi girin: ");
	sgets(str);

	int word_count = 0;
	int flag = 0;
	int i = 0;
	while (str[i] != '\0')
	{
		if (isspace(str[i])) // seperat�rler i�in isspunct(expr) fonksiyonu da kullan�labilir. Bu sayede bo�luk ve seperat�rler say�lmaz.
			flag = OUT_WORD;
		else if (flag == OUT_WORD)
		{
			flag = IN_WORD;
			word_count++;
		}
		i++;
	}
	printf("[%s]", str);
	printf("kelime sayisi %d", word_count);
}


/*
------------------------------------------------------

�dev

bir yaz�n�n palindrom olup olmad���na bakan kodu yaz.bo�luklar, virg�ller... �nemsenmiyor burada.
at sahibi gibi, hasta!
tra� neden �art ?

2 yol var.kolay� ilave dizi kullanarak yap�lan.
str dizisini kullanarak ve bu diziyi de�i�tirmeden.

--------------------------------------------------------

�dev

iki kelime girin.
kod bu kelimelerin yerini de�i�tirecek.
can sevdiren->sevdiren can olarak de�i�tirilecek.

de�i�ken tan�m� ok ama 2. dizi olmayacak.

------------------------------------------------------ -

�dev

bir yaz� olacak.bo�luklar olabilir kelimeler aras�nda, istenildi�i kadar bo�luk.yaz�lan kod kelime say�s�n� bulacak.
noktalama i�aretleri olmayacak verilen yaz�lar aras�nda.
yaz�n�n ba��nda ve sonunda da b�y�k bo�luklar olabilir.

------------------------------------------------------ -

�dev

char s1[SIZE]
char s2[SIZE]

ikikelime kullan�c�dan al�nacak.E�itse e�it, de�ilse de�il yazacak.

--------------------------------------------------------
	�dev

	char str[SIZE];
	int ch;

	printf("bir yazi girin: ");
	gets(str); // Ankara Antalya kahramanmaras
	printf("(%s)\n",str);

	printf("silinecek karakteri girin: ");
	ch = getchar(); //a
	for(int i = 0; str[i] != '\0'; i++)
		if(str[i] == ch)
			str{i] = '';
	kodun ��kt�s� a�a��daki gibi olacak.
	// nkr ntly khrmnmr�


	*/
// Cracking the Coding Interview 
// leetcode hackerrank 



