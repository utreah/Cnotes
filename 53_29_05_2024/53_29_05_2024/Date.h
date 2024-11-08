#pragma once
#ifndef DATE_H // DATE_H adlý bir makro tanýmlýyoruz. Buna multiple-inclusion guard deniyor. Birden fazla kez include edilmesini engelliyoruz
#define DATE_H // Eðer DATE_H define edilmediyse buraya geliyor ve DATE_H'ý define ediyor.

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
		yapamadýklarý için 
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

//accessors - get functions
int month_day(const Date*);
int month(const Date*);
int year(const Date*);
int weak_day(const Date*);
int year_day(const Date*);


// input - output functions
void print_date(const Date*);
Date* scan_date(Date*);

#endif
33:00