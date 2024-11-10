// Bir fonksiyonun geri d�n�� de�eri yap� t�r�nden olabilir.
	// fakat �ok fazla tercih edilmez. De�eri geri d�nd�r�rken de bir kopyalama i�lemi yap�l�yor sonu�ta.
		// struct ne kadar b�y�k ise o kadar fazla maliyet. K���k yap� t�rleri i�in tercih edilebilir.
typedef struct Data {
	int x, y;
	double d;
}Data;

Data f1(void);

void ff(void) {
	// Data x = f1(); // kopyalama i�lemi 2 kere oluyor. 
							// 1- x de�i�kenine yap�l�rken
							// 2- return edilirken. Yani maliyet x2 oldu.
	// return x; // fonksiyonun geri d�n�� de�erinin void olmas�na tak�lma derleme i�lemi i�in yapt�m void.
}

// Geri d�n�� de�eri yap� nnesnesi t�r�nden pointer olabilir. 
	/*
		1- Otomatik �m�rl� nesne d�nd�remez.
		2- Statik �m�rl� nesne adresi d�nd�rmesi
		3- Dinamik �m�rl� nesne adresi d�nd�rmesi
		4- �a��ran kodtan ald��� adresi yine �a��ran adrese d�nd�rmesi.
	*/

Data* foo(void) {
	Data px; 
	// code
	//code

	return &px; // bu yanl��! PX otomatik �m�rl� bir de�i�ken ve d�nd�r�ld���nde dangling pointer olacak. Kullan�lmas� UB
}

Data* bar(void) {
	Data* px = (Data*)malloc(sizeof(Data));
	//..code
	return px; // dinamik �m�rl� bir nesnenin adresini d�nd�rd�. �� bitince free edilmesi gerek.
}

const Data* baz(void); // Data t�r�nden bir nesnenin adresini 'salt-okunur' olarak d�nd�r�yor. 

/*----------------------------------------------------------------------------------*/

/*
STRUCTLARI / YAPILARI KULLANARAK H�ZMET VEREN K�T�PHANELER.
------------------------------------------------
2 tarz k�t�phane var �z�nde.
Ne gibi ?

a - C tarz� k�t�phane
b - OOP tarz� k�t�pane

Mesela ��yle olacak
k�t�phane diyecek ki ben sana struct image t�rden yap� veriyorum.
bunlar�n elemanlar� �unlard�r

struct Image {
	size_t width;
	size_t height;
	//..
};

a - 20 elemanl� diyelim. 20 sinide bilmek gerekiyor.B�yle k�t�phaneleri kullanmak
maliyetli.��renmi y�k� art�yor.��nk� her bir eleman�n�n nas�l kullan�ld���n�
ne i�e yarad���n� bilmek gerekiyor.

b - Hata yapma riski art�yor.
	yap�n�n elemanlar�n� yanl�� de�erler verilebilir.
	yap�n�n elemanlar�n� aral�k d��� de�erler verilebilir.


c - Yap�n�n elemanlar�n�n birbirleriyle logic ili�kisi var.
	mesela birini de�i�tirince, di�erleride de�i�ebilir.

	OOP TARZI K�T�PHANELER �SE

	Benim yap�m�n elemanlar� seni ilgilendirmeiyor.
		- yap�n�n elemanlar�na ula�am�yoruz.
		- her i� i�in k�t�phane fonksiyon veriyor.
		- elemanlar� de�i�tirmek i�in bile fonksiyon veriyor.
		- yap�n�n elemanlar�n� client coddan tamamen gizler.

	Yap�n�n elemanlar�n� gizlemenin yolu
	eleman� void * ile tutmak.

	struct Data {
		void *vp; // bunun ne oldu�u implementasyonda belli oluyor.��nk� buna member of
	};				// ile eri�ince hi�bir �ey yapamay�z. T�r� belirsiz.


		//
		// K�t�phanenin yap� t�r�n� "INCOMPLETE TYPE" olarak vermesi
		// yap� t�r�n�n sadece eksik bildirimi var ama yap�n�n elemanlar�n� g�steren bir
		// bildirim yok.


*/

/*
	Calendar Time(takvim zaman�): 
		Tarihte bir zamandaki noktaya 'timepoint' denir. -> 15 May�s 1987 12:45 gibi.
	Programlamada ��yle tan�mlan�yor. Buna "EPOCHE" deniyor. Timepointler, Epoche'tan ge�en s�re olarak ifade ediliyor. 
	01.01.1970 00:00 -> bu her sistemde ayn� de�il, farkl� olabilir. C'de bu �ekilde.

	�ki timepoint'�n birbirinden ��karmas�yla "duration(s�re)" ortaya ��k�yor. �ki tarih aras�nda ge�en s�re.
	�ki timepoint'�n toplanmas� ile ise yeni bir timepoint elde ediyoruz. ��kart�ld���n da ise "s�re" pointer aritmeti�i gibi

	Calender Time ise epochtan, timepoint'e ge�en zaman� ifade eder. Bir tam say� t�r�d�r. 
		K�t�phane bu tam say� t�r�ne direkt bir t�r vermek yerine bunun i�in bir t�r e� ismi olu�turmu�.
			Bu t�r-e� ismi 'time_t' ve benim derleyicimde 8 byte ve t�r� 'unsigned long long'.
	time_t g�rd���m�zde;
		a- Bir tam say� de�eri
		b- Bir calendar time ifade etti�ini
			Epochtan ge�en saniye say�s� olarak betimledi�ini anlamal�y�z.
	
	Broken-down time(ayr��t�r�lm�� zaman bilgisi):	BDT asl�nda calendar-time'�n insan g�z�ne ve akl�nda daha uygun hale getirilmi� �ekli.
		Epochtan 1.250.312.214 ge�mi� demek yerine bunu g�n/ay/y�l �eklinde yazmak. Bu, insanlar�n saati anlamas� i�in �nemli fakat
			hesaplamalar i�in uygun de�il. Calendar time bilgisayarlar i�in daha �nemli.

	<time.h> k�t�phanesi ayr��t�r�lm�� zaman bilgisini bir yap� t�r� ile temsil ediyor.

	- typedef bildirimi yok. Direkt safkan C struct'�
	- 9 tane int eleman� var. B�t�n elemanlar� int
		9 * sizeof(struct tm) = 36 byte // benim derleyicimde int 4 byte
	-
	struct tm {
		int tm_year;	// Y�l de�erini tutuyor. Fakat bu tuttu�u de�er bizim istedi�imiz olan de�er gibi de�il. Yani 2024 y�l� i�in, 2024 de�erini tutmaz. 2024 - 1900 de�erini tutar.
							// yani tm_year eleman� 124 de�erini tutar. Bu y�zden 1900 ile toplamam�z gerek.
		int tm_mon;		// Aylar 0dan ba�l�yor. 0 -> Ocak, 1 -> Subat, 2 -> Mart vs.
		int tm_mday;	//	1 - 31. Burada de�i�iklik yok :scream:
		int tm_wday;	// Haftan�n g�n�. 0-> Pazar, 1-> Pazartesi, 2-> Sal�. Indexleme pazar ile ba�l�yor.
		int tm_yday;	// Y�l�n g�n�n� temsil ediyor. Indexleme 1 Ocak ile ba�l�yor. 0 -> 1 Ocak, 1 -> 2 Ocak. Art�k y�llar i�in son g�n 364.g�n olacak, Art�k y�llar i�in 365
		int tm_hour;	// 0 - 23 aral���
		int tm_min;		// 0 - 59
		int tm_sec;		// 0 - 59
		int tm_isdst;	// Bayrak(flag) de�i�ken, daylight saving time anlam�nda.  
	/-*
	tm_ isdst < 0 ise
		sistemde g�n ����� tasaruf modu verisi tutulmuyor demek.
	tm_isdst == 0 ise
		sistemde g�n ����� tasaruf modu verisi var ama bu modda de�iliz.
	tm_isdst > 0 ise
		sistemde g�n ����� tasaruf modu verisi var ve bu modda bulunuyoruz.

	};
	*-/
	
*/
#include <time.h>
#include <stdio.h>
#pragma warning(disable:4996)
/*
	time_ time(time_t *p){ // set fonksiyon - mutator.
		// �a�r�ld��� noktada epochtan ge�en zaman� calendar time olarak veriyor.
			// �ki �ekilde veriyor bu de�eri.
				// 1- Bizim g�nderdi�imiz adrese set ediyor
				// 2- De�eri return ediyor.
		// Bu fonksiyona NULL g�ndermek UB de�il. NULL pointer g�nderdi�imiz de fonksiyona "hi�bir nesneye set etmeyeceksin" diyoruz. 
	}
*/
void print_current_time(void) {
	static const char* const pmons[] = { "Ocak", "Subat","Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eyl�l", "Ekim", "Kasim", "Aralik", }; // lookup table.
	static const char* const pdays[] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };
	time_t sec;
	time(&sec);
	struct tm* p = localtime(&sec); // yerel saat

	printf("%02d/%s/%d %s  %02d:%02d:%02d\n", p->tm_mday, pmons[p->tm_mon], (p->tm_year) + 1900, pdays[p->tm_wday], 
			p->tm_hour, p->tm_min, p->tm_sec);
	///////////////
	if (p->tm_isdst < 0)
		printf("sistemde g�n isigi tasarruf bayragi tutulmuyor\n");
	else if(p->tm_isdst)
		printf("sistemde g�n isigi tasarruf bayragi tutuluyor\n");
	else
		printf("gun isigi tasarruf modunda degiliz\n");

}
void print_current_time2(void) {
	static const char* const pmons[] = { "Ocak", "Subat","Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eyl�l", "Ekim", "Kasim", "Aralik", }; // lookup table.
	static const char* const pdays[] = { "Pazar", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi" };
	time_t sec;
	time(&sec);
	struct tm* p = gmtime(&sec); // GMT ben zaten �ngiltere'deyim. Ondan dolay� local ile gmt ayn� ��kt� aq

	printf("%02d/%s/%d %s  %02d:%02d:%02d\n", p->tm_mday, pmons[p->tm_mon], (p->tm_year) + 1900, pdays[p->tm_wday],
		p->tm_hour, p->tm_min, p->tm_sec);
	///////////////

}
/*
int main(void) {
	struct tm x;
	time_t sec;
	time(&sec);
	printf("%lld\n", sec); // Epochtan g�n�m�ze ge�en s�re (saniye cinsinden) -> calendar time yani

	time_t sec_null = time(NULL);
	printf("%lld\n", sec_null); // Burada da parametre de�eri olarak nullptr yolluyoruz.

	// Peki bunu BDT'ye nas�l �eviricez?
		// struct tm* localtime(const time_t* p); -> varl�k nedeni calendar time'� broken time'a d�n��t�rmek. 
	// time() fonksiyonundan ald���m�z saniye cinsinden de�eri struct tm t�r�ne d�n��t�rmeye yar�yor. Geri d�n�� t�r� struct tm*
		// geri d�n�� t�r�n�n �mr�, statik �m�rl�

	time_t timer = 17500000000;
	for (int i = 0; i < 10; i++) {
		printf("%p\n", localtime(&timer)); // yukar�daki statik �m�rl� kavram�n� kan�tlamak i�in yazd�k bunu.
												// 10 defa adresini �a��rd�k adres hep ayn� statik �m�rl� oldu�unu b�yle anl�yoruz.
	}
	print_current_time();
	print_current_time2();
}
*/

/*
	ctime ve asctime

	char* ctime(const time_t* p)	
	char* asctime(struct tm* p)		
		Bu fonksiyonlar�n ikisi de ayn� adresi d�nd�r�yor. �kisi de statik �m�rl� bir diziyi d�nd�r�yor. �rne�i a�a��da var.
	Bunlar�n d�nd�rd��� yaz�n�n i�erisinde newline (\n) karakteri de dahil. 


	int main(void){
		time_t sec;
		time(&sec);

		char *p = ctime(&sec);
		printf("%senginkendarli\n", p); // newline karakterini g�stermek i�in %s'den sonra yazi var.

		sec -= 100000;

		p = ctime(&sec);
		printf("100.000 Saniye oncesi : %s", p); // sec-=100000 ile 100k saniye ��karm�� olduk.
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
	locale dedi�imiz �ey ki�ilerin bulundu�u konuma vs g�re yap�lacak ve g�sterilecek �eylerin de�i�tirilmesi.
		Mesela T�rkiye'de ya�ayan birisi i�in TRY fiyat g�stermek, nokta ve virg�l�n say�lardaki/saatlerdeki g�sterimini de�i�tirmek gibi.
			Mesela T�rkiye ve avrupa �lkelerinde tarih -> G�n/Ay/Y�l olarak yaz�l�rken Amerika -> Ay/G�n/Y�l �eklinde yaz�yor. Bu tarz i�lemlerin
				de�i�ikliklerin yap�ld���, tan�mland��� k�meye locale diyoruz.


	Locale'i de�i�tirmedi�imiz s�rece bulundu�umuz lokale "C" local deniyor. 
		De�i�tirme i�lemini setlocale(int cat, const char* pname) fonksiyonu ile yap�yoruz. -> geri d�n�� de�eri char*, cat -> category
	Baz� fonksiyonlar direkt olarak setlocaleden etkileniyor.
		Yani mant�k olarak baz�lar� da ba�l� de�il. Mesela printf - scanf - strcoll locale ba�l�. strcmp ba�l� de�il

	Neden ��reniyoruz bunu?
		strftime diye bir timepoint'i stringe d�nd�ren bir fonksiyon var ve bu fonksiyon locale ba�l�.
	
	setlocale(int cat, const char* pname) -> ilk parametresi enum t�r�nden, ikinci parametresi de ismini al�yor.
		enum t�r�nden olan parametrede object-like macrolar tan�mlanm�� onlar� kullan�yoruz.
			LC_ALL = locale'in t�m �zelliklerini kullanmak anlam�na geliyor. B�t�n kategorileri de�i�tirmek istiyoruz demek
				E�er spesifik bir kategori �zerinde de�i�iklik yapmak istiyorsak o kategoriye uygun object-like makroyu �a��rmal�y�z. LC_COLLAT LC_NUMERIC gibi gibi

		geri d�n�� de�eri e�er ba�ar�l� ise char*, e�er ba�ar�s�z olur ise nullptr.

	
#include <locale.h>
int main(void) {
	double dval = 45.923123; // localeden �nce nokta ile ayr�l�yor
	printf("Before locale: %f\n", dval);
	char *p = setlocale(LC_ALL, "turkish");
	if (!*p)
		printf("Locale degisikligi basarisiz\n");
	else
		printf("Locale degisikligi basarili\n");
	printf("After locale: %f\n", dval); // setlocaleden sonra virg�l ile ayr�l�yor.
	/*
		double d;
		scanf("%f", &d);
		// locale �ncesi nokta veya virg�l ile ayr�l�rsa bir de�er ekrana nokta kullanarak yazd�r�r.
		// locale sonras� nokta veya virg�l ile ayr�l�rsa o locale'de nas�l kullan�l�yor ise �yle. T�rkiye i�in bu virg�l.
	
}
*/
/*
#include <locale.h>
int main(void) {
		strftime(char* _buffer, size_t _sizeinbytes, const char* _Format, const struct tm*), ald��� timepoint'i yaz� haline getiriyor.
		
		strftime'�n parametreleri �u �ekilde.
		char* _buffer = yaz�n�n olu�turulaca�� yerin adresi.
		size_t _sizeinbytes = dizinin boyutu. Yaz�lacak olan saatin diziyi ta��r�p ta��rmad���na bak�lacak. size - 1
		const char* _Format = Kendine ait format specifieri var. printf'deki %f vs vs
		const struct tm* _Tm = salt okuma ama�l� kullan�yor. time'�n yap�s�n� istiyor bizden.
		
		Geri d�n�� de�eri verilen adrese ka� karakter yaz�ld���n� d�nd�r�yor.
	time_t timer;
	time(&timer);
	struct tm* p = localtime(&timer);
	char buffer[100];
	char buffer2[100];
	size_t n = strftime(buffer, sizeof(buffer), "%a", p);
		// %a haftan�n g�n�n�n k�salt�lm�� halini yazar. -> Friday - Fri // %A yaz�l�r ise tam halini yaz�yor.
		// %D dd/mm/yyyy �eklinde yazd�r�r.
		// %d %B %A %Y -> Bunlar bir arada format k�sm�na yazd�r�labilir. %d -> day(24), %B -> Ay(May), %A -> Friday(tam hali), %Y -> Y�l(2024)
	printf("(%s)\n", buffer);
	printf("%lld", n);
	*/
	/*-----------------------------------------------*/
	/*
	char* llp = setlocale(LC_ALL, "turkish"); // setlocale ile locale'� Turkish yapt���m�z i�in ekrana T�rk�e isimleriyle yazacak. Normalde 3 October Sunday yazaca��na
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
/* ZAMAN TUTMA ��LEMLER� time.h*/
// clock_t clock(void); -> clock ile tutuyoruz zaman i�lemlerini.
#include <time.h>
int main(void) {
	
}
2:19