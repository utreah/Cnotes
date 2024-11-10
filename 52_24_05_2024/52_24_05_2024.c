// Bir fonksiyonun geri dönüþ deðeri yapý türünden olabilir.
	// fakat çok fazla tercih edilmez. Deðeri geri döndürürken de bir kopyalama iþlemi yapýlýyor sonuçta.
		// struct ne kadar büyük ise o kadar fazla maliyet. Küçük yapý türleri için tercih edilebilir.
typedef struct Data {
	int x, y;
	double d;
}Data;

Data f1(void);

void ff(void) {
	// Data x = f1(); // kopyalama iþlemi 2 kere oluyor. 
							// 1- x deðiþkenine yapýlýrken
							// 2- return edilirken. Yani maliyet x2 oldu.
	// return x; // fonksiyonun geri dönüþ deðerinin void olmasýna takýlma derleme iþlemi için yaptým void.
}

// Geri dönüþ deðeri yapý nnesnesi türünden pointer olabilir. 
	/*
		1- Otomatik ömürlü nesne döndüremez.
		2- Statik ömürlü nesne adresi döndürmesi
		3- Dinamik ömürlü nesne adresi döndürmesi
		4- Çaðýran kodtan aldýðý adresi yine çaðýran adrese döndürmesi.
	*/

Data* foo(void) {
	Data px; 
	// code
	//code

	return &px; // bu yanlýþ! PX otomatik ömürlü bir deðiþken ve döndürüldüðünde dangling pointer olacak. Kullanýlmasý UB
}

Data* bar(void) {
	Data* px = (Data*)malloc(sizeof(Data));
	//..code
	return px; // dinamik ömürlü bir nesnenin adresini döndürdü. Ýþ bitince free edilmesi gerek.
}

const Data* baz(void); // Data türünden bir nesnenin adresini 'salt-okunur' olarak döndürüyor. 

/*----------------------------------------------------------------------------------*/

/*
STRUCTLARI / YAPILARI KULLANARAK HÝZMET VEREN KÜTÜPHANELER.
------------------------------------------------
2 tarz kütüphane var özünde.
Ne gibi ?

a - C tarzý kütüphane
b - OOP tarzý kütüpane

Mesela þöyle olacak
kütüphane diyecek ki ben sana struct image türden yapý veriyorum.
bunlarýn elemanlarý þunlardýr

struct Image {
	size_t width;
	size_t height;
	//..
};

a - 20 elemanlý diyelim. 20 sinide bilmek gerekiyor.Böyle kütüphaneleri kullanmak
maliyetli.Öðrenmi yükü artýyor.Çünkü her bir elemanýnýn nasýl kullanýldýðýný
ne iþe yaradýðýný bilmek gerekiyor.

b - Hata yapma riski artýyor.
	yapýnýn elemanlarýný yanlýþ deðerler verilebilir.
	yapýnýn elemanlarýný aralýk dýþý deðerler verilebilir.


c - Yapýnýn elemanlarýnýn birbirleriyle logic iliþkisi var.
	mesela birini deðiþtirince, diðerleride deðiþebilir.

	OOP TARZI KÜTÜPHANELER ÝSE

	Benim yapýmýn elemanlarý seni ilgilendirmeiyor.
		- yapýnýn elemanlarýna ulaþamýyoruz.
		- her iþ için kütüphane fonksiyon veriyor.
		- elemanlarý deðiþtirmek için bile fonksiyon veriyor.
		- yapýnýn elemanlarýný client coddan tamamen gizler.

	Yapýnýn elemanlarýný gizlemenin yolu
	elemaný void * ile tutmak.

	struct Data {
		void *vp; // bunun ne olduðu implementasyonda belli oluyor.Çünkü buna member of
	};				// ile eriþince hiçbir þey yapamayýz. Türü belirsiz.


		//
		// Kütüphanenin yapý türünü "INCOMPLETE TYPE" olarak vermesi
		// yapý türünün sadece eksik bildirimi var ama yapýnýn elemanlarýný gösteren bir
		// bildirim yok.


*/

/*
	Calendar Time(takvim zamaný): 
		Tarihte bir zamandaki noktaya 'timepoint' denir. -> 15 Mayýs 1987 12:45 gibi.
	Programlamada þöyle tanýmlanýyor. Buna "EPOCHE" deniyor. Timepointler, Epoche'tan geçen süre olarak ifade ediliyor. 
	01.01.1970 00:00 -> bu her sistemde ayný deðil, farklý olabilir. C'de bu þekilde.

	Ýki timepoint'ýn birbirinden çýkarmasýyla "duration(süre)" ortaya çýkýyor. Ýki tarih arasýnda geçen süre.
	Ýki timepoint'ýn toplanmasý ile ise yeni bir timepoint elde ediyoruz. Çýkartýldýðýn da ise "süre" pointer aritmetiði gibi

	Calender Time ise epochtan, timepoint'e geçen zamaný ifade eder. Bir tam sayý türüdür. 
		Kütüphane bu tam sayý türüne direkt bir tür vermek yerine bunun için bir tür eþ ismi oluþturmuþ.
			Bu tür-eþ ismi 'time_t' ve benim derleyicimde 8 byte ve türü 'unsigned long long'.
	time_t gördüðümüzde;
		a- Bir tam sayý deðeri
		b- Bir calendar time ifade ettiðini
			Epochtan geçen saniye sayýsý olarak betimlediðini anlamalýyýz.
	
	Broken-down time(ayrýþtýrýlmýþ zaman bilgisi):	BDT aslýnda calendar-time'ýn insan gözüne ve aklýnda daha uygun hale getirilmiþ þekli.
		Epochtan 1.250.312.214 geçmiþ demek yerine bunu gün/ay/yýl þeklinde yazmak. Bu, insanlarýn saati anlamasý için önemli fakat
			hesaplamalar için uygun deðil. Calendar time bilgisayarlar için daha önemli.

	<time.h> kütüphanesi ayrýþtýrýlmýþ zaman bilgisini bir yapý türü ile temsil ediyor.

	- typedef bildirimi yok. Direkt safkan C struct'ý
	- 9 tane int elemaný var. Bütün elemanlarý int
		9 * sizeof(struct tm) = 36 byte // benim derleyicimde int 4 byte
	-
	struct tm {
		int tm_year;	// Yýl deðerini tutuyor. Fakat bu tuttuðu deðer bizim istediðimiz olan deðer gibi deðil. Yani 2024 yýlý için, 2024 deðerini tutmaz. 2024 - 1900 deðerini tutar.
							// yani tm_year elemaný 124 deðerini tutar. Bu yüzden 1900 ile toplamamýz gerek.
		int tm_mon;		// Aylar 0dan baþlýyor. 0 -> Ocak, 1 -> Subat, 2 -> Mart vs.
		int tm_mday;	//	1 - 31. Burada deðiþiklik yok :scream:
		int tm_wday;	// Haftanýn günü. 0-> Pazar, 1-> Pazartesi, 2-> Salý. Indexleme pazar ile baþlýyor.
		int tm_yday;	// Yýlýn gününü temsil ediyor. Indexleme 1 Ocak ile baþlýyor. 0 -> 1 Ocak, 1 -> 2 Ocak. Artýk yýllar için son gün 364.gün olacak, Artýk yýllar için 365
		int tm_hour;	// 0 - 23 aralýðý
		int tm_min;		// 0 - 59
		int tm_sec;		// 0 - 59
		int tm_isdst;	// Bayrak(flag) deðiþken, daylight saving time anlamýnda.  
	/-*
	tm_ isdst < 0 ise
		sistemde gün ýþýðý tasaruf modu verisi tutulmuyor demek.
	tm_isdst == 0 ise
		sistemde gün ýþýðý tasaruf modu verisi var ama bu modda deðiliz.
	tm_isdst > 0 ise
		sistemde gün ýþýðý tasaruf modu verisi var ve bu modda bulunuyoruz.

	};
	*-/
	
*/
#include <time.h>
#include <stdio.h>
#pragma warning(disable:4996)
/*
	time_ time(time_t *p){ // set fonksiyon - mutator.
		// Çaðrýldýðý noktada epochtan geçen zamaný calendar time olarak veriyor.
			// Ýki þekilde veriyor bu deðeri.
				// 1- Bizim gönderdiðimiz adrese set ediyor
				// 2- Deðeri return ediyor.
		// Bu fonksiyona NULL göndermek UB deðil. NULL pointer gönderdiðimiz de fonksiyona "hiçbir nesneye set etmeyeceksin" diyoruz. 
	}
*/
void print_current_time(void) {
	static const char* const pmons[] = { "Ocak", "Subat","Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eylül", "Ekim", "Kasim", "Aralik", }; // lookup table.
	static const char* const pdays[] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };
	time_t sec;
	time(&sec);
	struct tm* p = localtime(&sec); // yerel saat

	printf("%02d/%s/%d %s  %02d:%02d:%02d\n", p->tm_mday, pmons[p->tm_mon], (p->tm_year) + 1900, pdays[p->tm_wday], 
			p->tm_hour, p->tm_min, p->tm_sec);
	///////////////
	if (p->tm_isdst < 0)
		printf("sistemde gün isigi tasarruf bayragi tutulmuyor\n");
	else if(p->tm_isdst)
		printf("sistemde gün isigi tasarruf bayragi tutuluyor\n");
	else
		printf("gun isigi tasarruf modunda degiliz\n");

}
void print_current_time2(void) {
	static const char* const pmons[] = { "Ocak", "Subat","Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eylül", "Ekim", "Kasim", "Aralik", }; // lookup table.
	static const char* const pdays[] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };
	time_t sec;
	time(&sec);
	struct tm* p = gmtime(&sec); // GMT ben zaten Ýngiltere'deyim. Ondan dolayý local ile gmt ayný çýktý aq

	printf("%02d/%s/%d %s  %02d:%02d:%02d\n", p->tm_mday, pmons[p->tm_mon], (p->tm_year) + 1900, pdays[p->tm_wday],
		p->tm_hour, p->tm_min, p->tm_sec);
	///////////////

}
/*
int main(void) {
	struct tm x;
	time_t sec;
	time(&sec);
	printf("%lld\n", sec); // Epochtan günümüze geçen süre (saniye cinsinden) -> calendar time yani

	time_t sec_null = time(NULL);
	printf("%lld\n", sec_null); // Burada da parametre deðeri olarak nullptr yolluyoruz.

	// Peki bunu BDT'ye nasýl çeviricez?
		// struct tm* localtime(const time_t* p); -> varlýk nedeni calendar time'ý broken time'a dönüþtürmek. 
	// time() fonksiyonundan aldýðýmýz saniye cinsinden deðeri struct tm türüne dönüþtürmeye yarýyor. Geri dönüþ türü struct tm*
		// geri dönüþ türünün ömrü, statik ömürlü

	time_t timer = 17500000000;
	for (int i = 0; i < 10; i++) {
		printf("%p\n", localtime(&timer)); // yukarýdaki statik ömürlü kavramýný kanýtlamak için yazdýk bunu.
												// 10 defa adresini çaðýrdýk adres hep ayný statik ömürlü olduðunu böyle anlýyoruz.
	}
	print_current_time();
	print_current_time2();
}
*/

/*
	ctime ve asctime

	char* ctime(const time_t* p)	
	char* asctime(struct tm* p)		
		Bu fonksiyonlarýn ikisi de ayný adresi döndürüyor. Ýkisi de statik ömürlü bir diziyi döndürüyor. Örneði aþaðýda var.
	Bunlarýn döndürdüðü yazýnýn içerisinde newline (\n) karakteri de dahil. 


	int main(void){
		time_t sec;
		time(&sec);

		char *p = ctime(&sec);
		printf("%senginkendarli\n", p); // newline karakterini göstermek için %s'den sonra yazi var.

		sec -= 100000;

		p = ctime(&sec);
		printf("100.000 Saniye oncesi : %s", p); // sec-=100000 ile 100k saniye çýkarmýþ olduk.
		////////////////////////////////////////////////////////////////
		time_t sec2;
		time(&sec2);
		struct tm* tp = localtime(&sec2);

		char* p1 = ctime(&sec2);
		char* p2 = asctime(tp);
		printf("%p %p", p1, p2);
}
*/


	/* LOCALE <locale.h>
	locale dediðimiz þey kiþilerin bulunduðu konuma vs göre yapýlacak ve gösterilecek þeylerin deðiþtirilmesi.
		Mesela Türkiye'de yaþayan birisi için TRY fiyat göstermek, nokta ve virgülün sayýlardaki/saatlerdeki gösterimini deðiþtirmek gibi.
			Mesela Türkiye ve avrupa ülkelerinde tarih -> Gün/Ay/Yýl olarak yazýlýrken Amerika -> Ay/Gün/Yýl þeklinde yazýyor. Bu tarz iþlemlerin
				deðiþikliklerin yapýldýðý, tanýmlandýðý kümeye locale diyoruz.


	Locale'i deðiþtirmediðimiz sürece bulunduðumuz lokale "C" local deniyor. 
		Deðiþtirme iþlemini setlocale(int cat, const char* pname) fonksiyonu ile yapýyoruz. -> geri dönüþ deðeri char*, cat -> category
	Bazý fonksiyonlar direkt olarak setlocaleden etkileniyor.
		Yani mantýk olarak bazýlarý da baðlý deðil. Mesela printf - scanf - strcoll locale baðlý. strcmp baðlý deðil

	Neden öðreniyoruz bunu?
		strftime diye bir timepoint'i stringe döndüren bir fonksiyon var ve bu fonksiyon locale baðlý.
	
	setlocale(int cat, const char* pname) -> ilk parametresi enum türünden, ikinci parametresi de ismini alýyor.
		enum türünden olan parametrede object-like macrolar tanýmlanmýþ onlarý kullanýyoruz.
			LC_ALL = locale'in tüm özelliklerini kullanmak anlamýna geliyor. Bütün kategorileri deðiþtirmek istiyoruz demek
				Eðer spesifik bir kategori üzerinde deðiþiklik yapmak istiyorsak o kategoriye uygun object-like makroyu çaðýrmalýyýz. LC_COLLAT LC_NUMERIC gibi gibi

		geri dönüþ deðeri eðer baþarýlý ise char*, eðer baþarýsýz olur ise nullptr.

	
#include <locale.h>
int main(void) {
	double dval = 45.923123; // localeden önce nokta ile ayrýlýyor
	printf("Before locale: %f\n", dval);
	char *p = setlocale(LC_ALL, "turkish");
	if (!*p)
		printf("Locale degisikligi basarisiz\n");
	else
		printf("Locale degisikligi basarili\n");
	printf("After locale: %f\n", dval); // setlocaleden sonra virgül ile ayrýlýyor.
	/*
		double d;
		scanf("%f", &d);
		// locale öncesi nokta veya virgül ile ayrýlýrsa bir deðer ekrana nokta kullanarak yazdýrýr.
		// locale sonrasý nokta veya virgül ile ayrýlýrsa o locale'de nasýl kullanýlýyor ise öyle. Türkiye için bu virgül.
	
}
*/
/*
#include <locale.h>
int main(void) {
		strftime(char* _buffer, size_t _sizeinbytes, const char* _Format, const struct tm*), aldýðý timepoint'i yazý haline getiriyor.
		
		strftime'ýn parametreleri þu þekilde.
		char* _buffer = yazýnýn oluþturulacaðý yerin adresi.
		size_t _sizeinbytes = dizinin boyutu. Yazýlacak olan saatin diziyi taþýrýp taþýrmadýðýna bakýlacak. size - 1
		const char* _Format = Kendine ait format specifieri var. printf'deki %f vs vs
		const struct tm* _Tm = salt okuma amaçlý kullanýyor. time'ýn yapýsýný istiyor bizden.
		
		Geri dönüþ deðeri verilen adrese kaç karakter yazýldýðýný döndürüyor.
	time_t timer;
	time(&timer);
	struct tm* p = localtime(&timer);
	char buffer[100];
	char buffer2[100];
	size_t n = strftime(buffer, sizeof(buffer), "%a", p);
		// %a haftanýn gününün kýsaltýlmýþ halini yazar. -> Friday - Fri // %A yazýlýr ise tam halini yazýyor.
		// %D dd/mm/yyyy þeklinde yazdýrýr.
		// %d %B %A %Y -> Bunlar bir arada format kýsmýna yazdýrýlabilir. %d -> day(24), %B -> Ay(May), %A -> Friday(tam hali), %Y -> Yýl(2024)
	printf("(%s)\n", buffer);
	printf("%lld", n);
	*/
	/*-----------------------------------------------*/
	/*
	char* llp = setlocale(LC_ALL, "turkish"); // setlocale ile locale'ý Turkish yaptýðýmýz için ekrana Türkçe isimleriyle yazacak. Normalde 3 October Sunday yazacaðýna
												// 3 Ekim Pazar yazacak.
	 
	if (!*llp)
		printf("locale failed");
	time_t tim;
	time(&tim);
	struct tm* timp = localtime(&tim);

	char buf[100];

	size_t retval = strftime(buf, sizeof(buf), "Date = %d %B %A %Y %j", timp);
	printf("(%s)", buf);


}
	*/
/* ZAMAN TUTMA ÝÞLEMLERÝ time.h*/
// clock_t clock(void); -> clock ile tutuyoruz zaman iþlemlerini.
#include <time.h>
int main(void) {
	
}
2:19