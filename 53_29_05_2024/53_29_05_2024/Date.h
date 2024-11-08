#pragma once
#ifndef DATE_H // DATE_H adl� bir makro tan�ml�yoruz. Buna multiple-inclusion guard deniyor. Birden fazla kez include edilmesini engelliyoruz
#define DATE_H // E�er DATE_H define edilmediyse buraya geliyor ve DATE_H'� define ediyor.

typedef struct Date {
	int d_;
	int m_;
	int y_;
}Date;

/*
	Client kodlara, hizmet verecek fonksiyonlar� bir ka� kategoriye ay�rabiliriz.
	1- Set functions: Yap� nesnesinin de�erini veren, de�er kazand�ran veya de�erini de�i�tiren fonksiyonlara denir.
		Nesnenin adresini de�i�tirece�i i�in parametre de�eri olarak adres almak ZORUNDA -> Date* t�r�nden olmal�.
		Geri d�n�� de�erleri; 
			De�i�iklik yapt�klar� nesnenin adresi olabilir. -> Bu konvensiyonel, en �ok kullan�lanlardan biri yani.
			Yap�lan de�i�ikli�in ba�ar�l� ya da ba�ar�s�z oldu�unu belirten bir de�er d�nd�rebilir.
	2-	Input-output functions

	3- Accessor Functions: Bu fonksiyonlar yap�n�n gerekli elemanlar�na eri�erek istenen bilgiyi elde ediyor. De�i�iklik, atama vs
		yapamad�klar� i�in 
*/
// Set functions
Date* set_date(Date*, int d, int m, int y); // adresini ald��� Date* t�r�nden yap� t�r�ne Day, Month ve Year atamalar�n� yap�yor.
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