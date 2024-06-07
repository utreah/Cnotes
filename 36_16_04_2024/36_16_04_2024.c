/*
	-Standart K�t�phanedeki T�r-E� isimleri;
		strlen(const char* p); -> bu fonksiyonun geri d�n�� de�eri size_t;
			size_t bir t�r de�il bir t�r�n e� ismi. uint veya ulong t�r�nden olabilir. Derleyiciye ba�l�
				T�r�ne derleyici karar verecek fakat 'unsigned' olma garantisi VARDIR.
					typedef unsigned int size_t
					char arr[100] = "UGUR";
					size_t len = strlen(name); // Ba�ka bir derleyici de farkl� t�rden olabilir. T�r�n�n derleyiciye ba�l� olmas� sebebiyle
						hi�bir de�i�iklik yapmam�za gerek yok.
	-C std komitesi belirliyor her �eyi.
	-sizeof() T�r�ne derleyici karar verecek fakat 'unsigned' olma garantisi VARDIR.
	////////////////////////////////////////////////////////////////////
			Standart C k�t�phanesinin kulland��� baz� t�r e� isimleri

		size_t
		time_t
		ptrdiff_t
		clock_t
		fpos_t
		lfiv_t
		int32_t
		int16_t ...
		gibi

		Ama hangi t�r�n e� ismi oldu�unun karar� derleyiciye ba�l�.
	-size_t t�r e� ismini �u yerlerde kullan�yoruz;
		a)Fonksiyon parametreleri sizeof de�eri istiyor olabilir.
			yani size_t
		b)Fonksiyon parametreleri dizi-boyut istiyor olabilir.
			nutility'de size de�i�kenlerinin t�rlerini size_t ile de�i�tiriyoruz. ��nk� fonksiyon sizeof de�eri istiyor yani size_t
		c)Fonksiyon parametreleri tane-adet istiyor olabilir.
			strncpy() bunun i�i adresteki yaz�n�n di�erine n kadar karakterini kopyalamak
			3. parametre karakter adedi. yani size_t t�r�nden.
		d)Yaz� uzunlu�u t�r� ya da yaz�larda index
			strlen() geri d�n�� de�eri size_t
		
		#include <stddef.h>
		#include <stdio.h>
		int foo(void);
		int main(void){
			size_t size = foo();
			printf("size = ??, size); // -> burada size yerine ne gelecek?
										// e�er size_t long long int ise llu, long int ise lu. size_t'nin t�r� derleyici taraf�ndan belirleniyor
										// o y�zden her seferinde tekrar d�zenlemek gerekirdi. C99 ile %zu specifier'� eklendi.
			printf("size = %zu", size); // size_t t�r� i�in %zu format specifier�n� kullanarak derleyici'de bulunan t�r�ne g�re i�lem yapt�rabiliriz.

		}

//////////////////////////////////////////////

	NUTILITY.H header dosyas�ndaki size tutan b�t�n de�i�kenlerin t�r�n� size_t ile g�ncellendi.
		En hafif header dosyas� stddef.h oldu�u i�in o include edildi.

	-Bir adresten adres ��kart�l�rsa ortaya i�aretli tam say� t�r�nden bir de�er ��kar.
		�ki adresin fark� bir t�r e� ismi ile ifade ediliyor -> ptrdiff_t;
		p1 - p2 -> Bu i�lemin sonucu i�aretsiz tam say� olur. int de�il ��nk� long, long long, short vs. de olabilir.
/////////////////////////////////////////////

	Derleciyiler standarta uygun halde olabilir veya olmayabilir -> biz olmas�n� tercih ediyoruz :D
		Baz� typedef, fonksiyon gibi �eyler standartta olsa da opsiyonel olarak derleyicide olmayabilir. 
			E�er opsiyonel ise, derleyicde olmamas� derleyiciyi standartlara ayk�r� yapmaz hala standartlara uygundur.
	Bazi sistemlerde 1 byte 8 bit de�ilde 12 bit olabilir. Bundan dolay� int32_t uint32_t gibi t�r-e� isimleri opsiyonel oluyor.
		stdint.h

		i�erisinde

		uint32_t -> hangi derleyiciyi kullan�rsan kullan 4 byte yani 32 bit
		bu 4 byte int veya long olabilir. �nemli olan 4 byte olmas�.
		Ta��nabilirlik olarak m�kemmel.

		stdint include edilerek buradaki typedef isimlerine eri�ilir.

			Macrolar
			i�aretliler
			int8_t
			int16_t
			int32_t
			int64_t

			i�aretsizler
			uint8_t
			uint16_t
			uint32_t
			uint64_t
		Opsiyonel olmayan kesinlikle olmas� gereken typedeflerde var. Mesela;
			int_least16_t -> en az 16 bitlik yerin olmas� gerekti�ini s�yl�yor. Yani short 2 byte ise buna uyar, char 1 byte ise uymaz.
				bu kesinlikle 16 bit olmas� gerekti�ni s�ylemez, EN AZ 16 bit olmas� gerekti�ini belirtir. Di�erleri de �u �ekilde
short			int_lesat8_t;
long			int_least32_t;
long long		int_least64_t;

			uint_least8_t;
			uint_least16_t;
			uint_least32_t;
			uint_least64_t;
*/

/*
													YAZILAR �ZER�NDE ��LEM YAPAN FONKS�YONLAR
	-C'de aksi belirtilmedik�e yaz�lar char t�r�nde tutuluyor ve son karakteri '\0' dir.
	-Bir fonksiyon bir yaz�n�n adresini sadece 'okuma' amac� ile al�yorsa o yaz�n�n boyutunu parametre olarak almas�na gerek yoktur.
		void read_text(const char* p); -> Yaz�n�n son karakteri null-terminator olmas�ndan dolay� zaten o yaz�n�n uzunlu�u d���na ��k�lmayacak.
	-Bir fonksiyon bir yaz�n�n adresini hem okuma hem de de�i�tirme amac�yla al�yor ise o fonksiyon yaz�n�n boyutunu alabilir(zorunluluk yok)
		Baz� standart fonksiyonlar� yaz�da de�i�iklik yapacak olmas�na ra�men yaz�n�n boyutunu parametre olarak alm�yor.
			��nk� o yaz�n�n ta��p ta�mayaca�� fonksiyonu �a��ran ki�inin sorumlulu�unda.
				Mesela; scanf
			int main(void){
				char str[10];
				scanf("%s", &str); // cumhuriyetimizin -> bunu yaz�nca dizi ta�ar. ��nk� str dizisi sadece 9 karakter tutabilir.
									// bu scanf'in problemi de�il, kodu yazan/fonksiyonu �a��ran�n su�u :D "Merhamet edin efendim"
			}
				puts(str) -> bu da sadece yaz�n�n adresini al�yor(const) size alm�yor.
	-E�er bir diziye tutamayaca�� boyutta bir text atan�r ise bu UB olu�turur. 	
	-Bir diziyi daha k���k bir diziye kopyalamak UB olu�turur.
	-C'de sonu _s == secure anlam�na geliyor. Ald�klar� parametreleri ba�ka bir diziye aktararak ta�ma probleminin �nemine ge�iyor.
		Fakat bu durumun maliyete etkisi var. Sonu�ta dizi bitti mi bitmedi mi diye kontrol ediyor
*/
#include <stdio.h>
void my_puts(const char* p)
{
	while(*p)
		putchar(*p++);
	// veya
	/*
		for (; *p; p++) // bu benim :D
			putchar(*p);
	*/
	/*
		for(size_t i = 0; p[i]; i++)
			putchar(p[i]);
	*/
}


/*
																
	<string.h>
	---------------------	size_t strlen(const char* p) --------------------- 
			#define SIZE 100
			int main(void){
				char str[SIZE]; // Tutulan "Ugur Ersoy" olsun.
									// printf'e sadece str yazar isem Ugur Ersoy'u ekrana yazd�r�r (array decay)
										// ama str+1 yazar isem gur Ersoy yazd�r�r. bu subscript. Sadece 1 karakter tutuluyor ayn� yerde
				printf("Bir yazi girin:");
				sgets(str);
				size_t len = strlen(str);
				printf("Uzunluk: %zu", len);
			}
	
size_t my_strlen(const char* p){
		size_t str_len = 0;
		while(	*p++)
			str_len++;
		return str_len;
}
size_t alt_my_strlen(const char* p){
	const char* ptrtemp = p
	while(*p)
		++p;
	return (size_t)(p - ptrtemp);
			
}
///////////////////////////////////////////////////////////////////////////////////////////

	---------------------	char* strchr(const char* p, int ch) ---------------------
	-Bir kelimede/c�mlede belirli karakterleri arar. E�er arad��� karakteri bulursa o karakterin adresini geri d�nd�r�r, bulamaz ise nullptr d�nd�r�r.
	int main(void){
		char* str[100];
		printf("yaz dostum:");
		sgets(str);

		int ch = getchar(); 
		char* p = strchr(str, c);
		if(p)
			printf("Karakter %d. s�rada bulundu. Devam�: %p ", p - str, p);
		else
			printf("Bulunamad�");
	
	}

char* my_strchr(const char* p, int ch){
	
	while(*p++)
		if(*p == ch)
			return (char*)p;

	if(ch == '\0') // e�er aranan null karakter ise p zaten o an orada oldu�u i�in direkt p yi return edebiliriz.
		return (char*)p;

	return NULL; // e�er aranan bulamazsa nullptr d�nd�r

}
char* my_strrchr(const char * p, int c)
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
*/












































/*
	---------------------------------------------------------------
		M�lakat Sorusu

		typedef int *IPTR;

		int x = 10;
		const IPTR ptr = &x;

		// const int * ptr = &x; 1
		// int * const ptr = &x; 2

		do�ru cevap iki. top level ptr

		const keyword bir typedef ismi ile kullan�l�rsa
		her zaman kendisi const yap�yor pointer�.

		yani int * const ptr olur. ptr const olmu� oldu yani

		*ptr = 11; ve ptr =	herhangibir adres		ile test edilebilir.
		E�er bunu low level const yapmak istersek

		 typedef const int * CIPTR;
		 int x= 20;
		 int y = 30;
		 CIPTR ptr = &x;
		 // const int *ptr = &x; demek bu.

		 typedef globalde de function scopeta da tan�mlanabilir
		 -------------------------------
*/