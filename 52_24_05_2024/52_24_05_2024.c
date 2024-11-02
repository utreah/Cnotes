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
	static const char* const pmons[] = { "Ocak", "Subat","Mart", "Nisan", "Mayis", "Haziran", "Temmuz", "Agustos", "Eyl�l", "Ekim", "Kasim", "Aralik", };
	time_t sec;
	time(&sec);
	struct tm* p = localtime(&sec);

	printf("%02d/%s/%d", p->tm_mday, pmons[p->tm_mon], (p->tm_year) + 1900);
}
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


}

1:23