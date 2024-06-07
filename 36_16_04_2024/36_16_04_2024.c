/*
	-Standart Kütüphanedeki Tür-Eþ isimleri;
		strlen(const char* p); -> bu fonksiyonun geri dönüþ deðeri size_t;
			size_t bir tür deðil bir türün eþ ismi. uint veya ulong türünden olabilir. Derleyiciye baðlý
				Türüne derleyici karar verecek fakat 'unsigned' olma garantisi VARDIR.
					typedef unsigned int size_t
					char arr[100] = "UGUR";
					size_t len = strlen(name); // Baþka bir derleyici de farklý türden olabilir. Türünün derleyiciye baðlý olmasý sebebiyle
						hiçbir deðiþiklik yapmamýza gerek yok.
	-C std komitesi belirliyor her þeyi.
	-sizeof() Türüne derleyici karar verecek fakat 'unsigned' olma garantisi VARDIR.
	////////////////////////////////////////////////////////////////////
			Standart C kütüphanesinin kullandýðý bazý tür eþ isimleri

		size_t
		time_t
		ptrdiff_t
		clock_t
		fpos_t
		lfiv_t
		int32_t
		int16_t ...
		gibi

		Ama hangi türün eþ ismi olduðunun kararý derleyiciye baðlý.
	-size_t tür eþ ismini þu yerlerde kullanýyoruz;
		a)Fonksiyon parametreleri sizeof deðeri istiyor olabilir.
			yani size_t
		b)Fonksiyon parametreleri dizi-boyut istiyor olabilir.
			nutility'de size deðiþkenlerinin türlerini size_t ile deðiþtiriyoruz. Çünkü fonksiyon sizeof deðeri istiyor yani size_t
		c)Fonksiyon parametreleri tane-adet istiyor olabilir.
			strncpy() bunun iþi adresteki yazýnýn diðerine n kadar karakterini kopyalamak
			3. parametre karakter adedi. yani size_t türünden.
		d)Yazý uzunluðu türü ya da yazýlarda index
			strlen() geri dönüþ deðeri size_t
		
		#include <stddef.h>
		#include <stdio.h>
		int foo(void);
		int main(void){
			size_t size = foo();
			printf("size = ??, size); // -> burada size yerine ne gelecek?
										// eðer size_t long long int ise llu, long int ise lu. size_t'nin türü derleyici tarafýndan belirleniyor
										// o yüzden her seferinde tekrar düzenlemek gerekirdi. C99 ile %zu specifier'ý eklendi.
			printf("size = %zu", size); // size_t türü için %zu format specifierýný kullanarak derleyici'de bulunan türüne göre iþlem yaptýrabiliriz.

		}

//////////////////////////////////////////////

	NUTILITY.H header dosyasýndaki size tutan bütün deðiþkenlerin türünü size_t ile güncellendi.
		En hafif header dosyasý stddef.h olduðu için o include edildi.

	-Bir adresten adres çýkartýlýrsa ortaya iþaretli tam sayý türünden bir deðer çýkar.
		Ýki adresin farký bir tür eþ ismi ile ifade ediliyor -> ptrdiff_t;
		p1 - p2 -> Bu iþlemin sonucu iþaretsiz tam sayý olur. int deðil çünkü long, long long, short vs. de olabilir.
/////////////////////////////////////////////

	Derleciyiler standarta uygun halde olabilir veya olmayabilir -> biz olmasýný tercih ediyoruz :D
		Bazý typedef, fonksiyon gibi þeyler standartta olsa da opsiyonel olarak derleyicide olmayabilir. 
			Eðer opsiyonel ise, derleyicde olmamasý derleyiciyi standartlara aykýrý yapmaz hala standartlara uygundur.
	Bazi sistemlerde 1 byte 8 bit deðilde 12 bit olabilir. Bundan dolayý int32_t uint32_t gibi tür-eþ isimleri opsiyonel oluyor.
		stdint.h

		içerisinde

		uint32_t -> hangi derleyiciyi kullanýrsan kullan 4 byte yani 32 bit
		bu 4 byte int veya long olabilir. Önemli olan 4 byte olmasý.
		Taþýnabilirlik olarak mükemmel.

		stdint include edilerek buradaki typedef isimlerine eriþilir.

			Macrolar
			iþaretliler
			int8_t
			int16_t
			int32_t
			int64_t

			iþaretsizler
			uint8_t
			uint16_t
			uint32_t
			uint64_t
		Opsiyonel olmayan kesinlikle olmasý gereken typedeflerde var. Mesela;
			int_least16_t -> en az 16 bitlik yerin olmasý gerektiðini söylüyor. Yani short 2 byte ise buna uyar, char 1 byte ise uymaz.
				bu kesinlikle 16 bit olmasý gerektiðni söylemez, EN AZ 16 bit olmasý gerektiðini belirtir. Diðerleri de þu þekilde
short			int_lesat8_t;
long			int_least32_t;
long long		int_least64_t;

			uint_least8_t;
			uint_least16_t;
			uint_least32_t;
			uint_least64_t;
*/

/*
													YAZILAR ÜZERÝNDE ÝÞLEM YAPAN FONKSÝYONLAR
	-C'de aksi belirtilmedikçe yazýlar char türünde tutuluyor ve son karakteri '\0' dir.
	-Bir fonksiyon bir yazýnýn adresini sadece 'okuma' amacý ile alýyorsa o yazýnýn boyutunu parametre olarak almasýna gerek yoktur.
		void read_text(const char* p); -> Yazýnýn son karakteri null-terminator olmasýndan dolayý zaten o yazýnýn uzunluðu dýþýna çýkýlmayacak.
	-Bir fonksiyon bir yazýnýn adresini hem okuma hem de deðiþtirme amacýyla alýyor ise o fonksiyon yazýnýn boyutunu alabilir(zorunluluk yok)
		Bazý standart fonksiyonlarý yazýda deðiþiklik yapacak olmasýna raðmen yazýnýn boyutunu parametre olarak almýyor.
			Çünkü o yazýnýn taþýp taþmayacaðý fonksiyonu çaðýran kiþinin sorumluluðunda.
				Mesela; scanf
			int main(void){
				char str[10];
				scanf("%s", &str); // cumhuriyetimizin -> bunu yazýnca dizi taþar. Çünkü str dizisi sadece 9 karakter tutabilir.
									// bu scanf'in problemi deðil, kodu yazan/fonksiyonu çaðýranýn suçu :D "Merhamet edin efendim"
			}
				puts(str) -> bu da sadece yazýnýn adresini alýyor(const) size almýyor.
	-Eðer bir diziye tutamayacaðý boyutta bir text atanýr ise bu UB oluþturur. 	
	-Bir diziyi daha küçük bir diziye kopyalamak UB oluþturur.
	-C'de sonu _s == secure anlamýna geliyor. Aldýklarý parametreleri baþka bir diziye aktararak taþma probleminin önemine geçiyor.
		Fakat bu durumun maliyete etkisi var. Sonuçta dizi bitti mi bitmedi mi diye kontrol ediyor
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
									// printf'e sadece str yazar isem Ugur Ersoy'u ekrana yazdýrýr (array decay)
										// ama str+1 yazar isem gur Ersoy yazdýrýr. bu subscript. Sadece 1 karakter tutuluyor ayný yerde
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
	-Bir kelimede/cümlede belirli karakterleri arar. Eðer aradýðý karakteri bulursa o karakterin adresini geri döndürür, bulamaz ise nullptr döndürür.
	int main(void){
		char* str[100];
		printf("yaz dostum:");
		sgets(str);

		int ch = getchar(); 
		char* p = strchr(str, c);
		if(p)
			printf("Karakter %d. sýrada bulundu. Devamý: %p ", p - str, p);
		else
			printf("Bulunamadý");
	
	}

char* my_strchr(const char* p, int ch){
	
	while(*p++)
		if(*p == ch)
			return (char*)p;

	if(ch == '\0') // eðer aranan null karakter ise p zaten o an orada olduðu için direkt p yi return edebiliriz.
		return (char*)p;

	return NULL; // eðer aranan bulamazsa nullptr döndür

}
char* my_strrchr(const char * p, int c)
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
*/












































/*
	---------------------------------------------------------------
		Mülakat Sorusu

		typedef int *IPTR;

		int x = 10;
		const IPTR ptr = &x;

		// const int * ptr = &x; 1
		// int * const ptr = &x; 2

		doðru cevap iki. top level ptr

		const keyword bir typedef ismi ile kullanýlýrsa
		her zaman kendisi const yapýyor pointerý.

		yani int * const ptr olur. ptr const olmuþ oldu yani

		*ptr = 11; ve ptr =	herhangibir adres		ile test edilebilir.
		Eðer bunu low level const yapmak istersek

		 typedef const int * CIPTR;
		 int x= 20;
		 int y = 30;
		 CIPTR ptr = &x;
		 // const int *ptr = &x; demek bu.

		 typedef globalde de function scopeta da tanýmlanabilir
		 -------------------------------
*/