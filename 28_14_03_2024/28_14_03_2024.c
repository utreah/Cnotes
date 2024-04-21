#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
/*
int main()
{
	char str[100] = { "UGUR ERSOY" };

	puts(str);// sonuna newline koyuyor puts foncksiyonu.
	char str2[100]; // Eðer first initiliazation yapýlmaz ise dizinin elementlarý garbage value ile baþlar. Bu þekilde baþlamakta sýkýntý yok
				// eðer bu dizi kullanýlýr ise UB oluþur.

	str2[0] = 'U';
	str2[1] = 'G'; // Eðer sonuna '\0' koyulmaz ise UB.
	str2[2] = '\0';// bu eklendiðinde UB deðil artýk ve legal.
	// str[2] = '0'; -> 13. satýrdaki yerine bu eklenirse UB durumu devam eder. '0' 0 karakterinin tam sayý karþýlýðýný verir bize.
}*/

// YAZI TUTACAK CHAR DÝZÝLERÝNÝ ÝLK DEÐER VERMEK/BAÞLATMAK
/*
int main(void)
{
	char str[100] = { 'U', 'G', 'U', 'R' }; // Ýlk deðer vererek baþlatýlan dizilerde kullanýlmayan dizi elementlarý 0 olarak set edilir.
											// yani ilk 4 element U G U R harflerini tutarken geri kalan 96 dizi elemtlarý 0'ý tutar.
	char str2[4] = { 'U', 'G', 'U', 'R' }; // UB var. Çünkü tüm deðer tutabilen yerler dolu ve null karakteri için yer yok.
	char str3[] = { 'U', 'G', 'U', 'R' }; // Sentaks hatasý yok UB var. Dizi boyutu verilmez ise dizinin boyutu içerisindeki tutulan elemanlar kadardý.
										// yani str3 dizisinin 4 elemaný var yani boyutu 4. Fakat null karakteri için yer olmadýðý için UB.
										// tanýmsýz davranýþ NTBS'nin olmamasýna karþýn bu dizinin kullanýlmasý. Aþaðýdaki for döngüsünü örnek alabiliriz.
										// Dizide null karakter olmadýðý için diziden taþacak ve bu tanýmsýz davranýþ oluþturur.
	for (int i = 0; str[i] != '\0'; ++i)
		putchar(str[i]);
}
*/
/*int main(void)
{
	char str[] = "UGUR"; // Çift týrnak arasýnda yazýlan yazýnýn sonunda otomatik olarak null karakter koyuluyor. Bu dizinin uzunluðu "5"
	char str[4] = "UGUR"; // Dizinin boyutu null karakteri içine almýyor ise bu CPP'de bu sentaks hatasý. C'de legal sonunda null karakter yok.
						// kullanýlmadýðý sürece UB yok. Alttaki döngü olduðu için bu deyim UB!
	// char str[] = "UGUR"; == char str[] = { 'U', 'G', 'U', 'R' }; -> bu iki dizide ayný anlama geliyor fakat soldaki dizide null karakter 
															// var iken saðdaki dizi de null karakter YOK. En temel farklarý bu.
		
	for (int i = 0; str[i] != '\0'; ++i)
		putchar(str[i]);
}*/

// scanf'te whitespace karakteri ayýraç olarak iþ görüyor. Ugur Ersoy ismini girdiðimizde ekrana Ugur yazdýrýr ve Ersoy bufferda kalýr.
// 	scanf ile sýðamayacak yazýyý char array elemanlarýna atamak runtime hatasý 
								/*--------------------------------ÖRNEKLER--------------------------------*/
/*
int main(void)
{
	char name[20];
	char surname[20];
	int age;

	printf("Isim, soyisim ve yas giriniz:");
	scanf("%s%s%d", name, surname, &age);
	// scanf("%s", name); -> burada input olarak ugur ersoy girseydim sadece ugur'u yazdýrýrdý ve whitespace'e ayýraçmýþ gibi davranýrdý.
	printf("[%s] [%s] Hosgeldiniz, Yas: %d", name, surname, age);
	// gets() adres alýp, bufferdan tüm karakterleri alýyordu(whitespace dahil)
		// C99 ile deprecate(kullanýlmasý tavsiye edilmemesi) edildi sonraki standartlarda kaldýrýldý. 
	// sgets(name); // grts deprecate edildiðinden ve IDE hata vermesin diye necati hoca kendi fonksiyonunu yazdý.
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
	// Yazýnýn sonuna karakter ekleme.
	int j = 0;
	for (j = 0; str[j] != '\0'; j++)
		;
	str[j] = 'x';
	str[j + 1] = '\0';
	printf("Karakter eklendi! -> [%s]\n", str);
	printf("|--------------------------------------|\n");
	// Yazýyý tersten yazdýrma.
	int k = 0;
	while (str[k] != '\0')
		k++;
	for (k--; k >= 0; --k)
		putchar(str[k]);
	printf("\n");
	printf("|--------------------------------------|\n");
	// Birleþtirme!
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
		if (str[i] == ch) // büyük küçük ayrýmý yapýyor. Her birini bulmak için toupper() kullanýlabilir.
			cnt++;
	}
	printf("%d adet [%c] bulundu\n", cnt, ch);
	printf("|--------------------------------------|\n");
	// Hangi karakterden kaç tane olduðunu buluyor.
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
	// bir yazýnýn ters çevrimesi.reverse algoritmasý görüldü zaten.
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
/*int main() // benim yazdýðým
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
        printf("AYNI DEGÝL");
    else
        printf("AYNI");
    
}


	2 metnin karþýlaþtýrýlmasý // hocanýn yazdýðý -> iki metinin karþýlaþtýrýlmasý


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

// CUMLEDEKÝ KELIMELERÝ SAYMA
#define IN_WORD 1 // kelimenin içinde
#define OUT_WORD 0 // kelimenin dýþýnda

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
		if (isspace(str[i])) // seperatörler için isspunct(expr) fonksiyonu da kullanýlabilir. Bu sayede boþluk ve seperatörler sayýlmaz.
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

Ödev

bir yazýnýn palindrom olup olmadýðýna bakan kodu yaz.boþluklar, virgüller... önemsenmiyor burada.
at sahibi gibi, hasta!
traþ neden þart ?

2 yol var.kolayý ilave dizi kullanarak yapýlan.
str dizisini kullanarak ve bu diziyi deðiþtirmeden.

--------------------------------------------------------

Ödev

iki kelime girin.
kod bu kelimelerin yerini deðiþtirecek.
can sevdiren->sevdiren can olarak deðiþtirilecek.

deðiþken tanýmý ok ama 2. dizi olmayacak.

------------------------------------------------------ -

Ödev

bir yazý olacak.boþluklar olabilir kelimeler arasýnda, istenildiði kadar boþluk.yazýlan kod kelime sayýsýný bulacak.
noktalama iþaretleri olmayacak verilen yazýlar arasýnda.
yazýnýn baþýnda ve sonunda da büyük boþluklar olabilir.

------------------------------------------------------ -

Ödev

char s1[SIZE]
char s2[SIZE]

ikikelime kullanýcýdan alýnacak.Eþitse eþit, deðilse deðil yazacak.

--------------------------------------------------------
	Ödev

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
	kodun çýktýsý aþaðýdaki gibi olacak.
	// nkr ntly khrmnmrþ


	*/
// Cracking the Coding Interview 
// leetcode hackerrank 



