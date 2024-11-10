#pragma once
#ifndef DATE_H // DATE_H adlý bir makro tanýmlýyoruz. Buna multiple-inclusion guard deniyor. Birden fazla kez include edilmesini engelliyoruz
#define DATE_H // Eðer DATE_H define edilmediyse buraya geliyor ve DATE_H'ý define ediyor.
#pragma warning(disable:4996)
typedef struct Date {
	int d_;
	int m_;
	int y_;
}Date;

/*
	Client kodlara, hizmet verecek fonksiyonlarý bir kaç kategoriye ayýrabiliriz.
	1- Set functions: Yapý nesnesinin deðerini veren, deðer kazandýran veya deðerini deðiþtiren fonksiyonlara denir.
		Nesnenin adresini deðiþtireceði için parametre deðeri olarak adres almak ZORUNDA -> Date* türünden olmalý.
		Geri dönüþ deðerleri; 
			Deðiþiklik yaptýklarý nesnenin adresi olabilir. -> Bu konvensiyonel, en çok kullanýlanlardan biri yani.
			Yapýlan deðiþikliðin baþarýlý ya da baþarýsýz olduðunu belirten bir deðer döndürebilir.
	2-	Input-output functions

	3- Accessor Functions: Bu fonksiyonlar yapýnýn gerekli elemanlarýna eriþerek istenen bilgiyi elde ediyor. Deðiþiklik, atama vs
		yapamadýklarý için const keywordü ile read-only olarak eriþiyorlar.
*/
// Set functions
	Date* set_date(Date*, int d, int m, int y); // adresini aldýðý Date* türünden yapý türüne Day, Month ve Year atamalarýný yapýyor.
	Date* set_today(Date* p);
	Date* set_date_from_str(Date* p, const char* str); 
	Date* set_random_date(Date* p);
	Date* set_month_day(Date* p, int mday);
	Date* set_month(Date* p, int month);
	Date* set_year(Date* p, int year);
	Date* date_increment(Date* ptr, int day);
	Date* date_decrement(Date* ptr, int day);

	// accessors - get functions
	int month_day(const Date*);
	int month(const Date*);
	int year(const Date*);
	int week_day(const Date*);
	int year_day(const Date*);


	// input - output functions
	void print_date(const Date*);
	Date* scan_date(Date*);


	// utility functions -> Genel hizmet veren fonksiyonlar
	int cmp_date(const Date*, const Date*);
	int date_diff(const Date*, const Date*);
	Date* ndays_after(Date* presult, const Date* psource, int ndays);
	Date* ndays_before(Date* presult, const Date* psource, int ndays);
	Date* to_date(Date*, int);
#endif

 /*
	Ortak kodlarý bir yerde toplamak daha iyi. Mesela set fonksiyonlarý. Hepsini tek tek yazmak hem kod tekrarýna hem de test ederken zorluklara sebebiyet verir.
		Bir tane fonksiyon yazýcaz, ortak kodu bir yerde toplayacaðýz bu sayede, ve diðer fonksiyonlar bunu çaðýracak. OOP jargonuna benzetmek için bir trick kullanacak hoca.

	Trick dediðimiz þey static keywordünün kullanýlmasý. OOP dillerinde public, private, protected gibi keywordler var. private,  client kodun erimesi yasak olan yerler.
		bizde PRIVATE adýnda bir macro tanýmlayacaðýz. Bu sayede PRIVATE ifadesine sahip olan fonksiyonlar o baþlýk/kaynak dosyasýna ait olacak ve dýþarýdan eriþilemeyecek.
		#define PRIVATE static

	Normalde kodlarda hata mesajý vs döndürmek olmamasý gereken bir þey(debug durumlarý dahil deðil) bunun için ayrý bir yöntem var. Kursun sonunda göreceðiz.
		set fonksiyonlarý adres döndürdüðü için baþarýsýz olduðu durumda NULL döndürmeli normalde. Biz iþimiz kolaylaþsýn diye þimdilik hata mesajý veriyoruz.
 */