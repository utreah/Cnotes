/*
   Ortak kodlar� bir yerde toplamak daha iyi. Mesela set fonksiyonlar�. Hepsini tek tek yazmak hem kod tekrar�na hem de test ederken zorluklara sebebiyet verir.
	   Bir tane fonksiyon yaz�caz, ortak kodu bir yerde toplayaca��z bu sayede, ve di�er fonksiyonlar bunu �a��racak. OOP jargonuna benzetmek i�in bir trick kullanacak hoca.

   Trick dedi�imiz �ey static keyword�n�n kullan�lmas�. OOP dillerinde public, private, protected gibi keywordler var. private,  client kodun erimesi yasak olan yerler.
	   bizde PRIVATE ad�nda bir macro tan�mlayaca��z. Bu sayede PRIVATE ifadesine sahip olan fonksiyonlar o ba�l�k/kaynak dosyas�na ait olacak ve d��ar�dan eri�ilemeyecek.
	   #define PRIVATE static
	Ayn� zamanda bir de PUBLIC tan�mlayaca��z fakat PUBLIC hi�bir �eyin yerini almayacak. Bu sayede derleyici PUBLIC g�rd��� yerde onu silecek. Asl�nda public kullan�m� tamamen
		kendimize "bu fonksiyona d��ar�dan eri�ilebilir" diye hat�rlatmak.
*/
#include "Date.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma 
#define PRIVATE			static
#define PUBLIC
#define YEARBASE			1900
#define RANDOM_YEAR_MIN		1950
#define RANDOM_YEAR_MAX		2024

#define ISLEAP(y)	((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
#define MDAYS(y, m) (daytabs[ISLEAP(y)][m])
PRIVATE int is_valid_date(int, int, int); //tarihin ge�erli olup olmad���n� sorgulayacak. return val -> boolean int
PRIVATE Date* set(Date*, int, int, int); // b�t�n set fonksiyonlar� bu fonksiyonu �a��racak
PRIVATE int totaldays(const Date*);
PRIVATE Date* to_date(Date*, int);

PUBLIC Date* set_date_from_str(Date*, const char*);
PUBLIC Date* set_random_date(Date*);
PUBLIC Date* set_month_day(Date*, int);
PUBLIC Date* set_month(Date*, int);
PUBLIC Date* set_year(Date*, int);
PUBLIC void print_date(const Date*);
PUBLIC Date* scan_date(Date*);
PUBLIC int cmp_date(const Date*, const Date*);
PUBLIC int date_diff(const Date*, const Date*);
PUBLIC Date* ndays_after(Date*, const Date*, int);
PUBLIC Date* ndays_before(Date*, const Date*, int);
PUBLIC Date* date_increment(Date*, int);
PUBLIC Date* date_decrement(Date*, int);

PRIVATE const daytabs[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

PUBLIC Date* date_increment(Date* p, int day) {
	return to_date(p ,totaldays(p) + day);
}

PUBLIC Date* date_decrement(Date* p, int day) {
	return to_date(p, totaldays(p) - day);
}

PUBLIC int cmp_date(const Date* p1, const Date* p2) {
	if (year(p1) != year(p2))
		return year(p1) > year(p2) ? 1 : -1;
	if (month(p1) != month(p2))
		return month(p1) > month(p2) ? 1 : -1;
	return month_day(p1) > month_day(p2) ? 1 : -1;
}

PUBLIC void print_date(const Date* p) {
	static const char* const pmons[] = { "", "Ocak", "Subat", "Mart", "Nisan", "Mayis", "Haziran", 
										"Temmuz", "Agustos", "Eylul", "Ekim", "Kasim", "Aralik" , };

	static const char* const pdays[] = { "", "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar" };

	printf("%02d %s %d %s\n", month_day(p), pmons[month(p)], year(p), pdays[week_day(p)]);
}

PUBLIC int date_diff(const Date* p1, const Date* p2) {
	return totaldays(p1) - totaldays(p2);
}

PUBLIC Date* scan_date(Date* p) {
	int d, m, y;
	(void)scanf("%d%d%d", &d, &m, &y);

	return set(p, d, m, y);
}

PUBLIC int year_day(const Date* p) {
	int y = year(p);
	int m = month(p);

	int sum = month_day(p);
	for (int i = 1; i < m; i++) {
		sum += MDAYS(y, i);
	}
	return sum;
}

PUBLIC int month_day(const Date* p) {
	return p->d_;
}
PUBLIC int month(const Date* p) {
	return p->m_;
}
PUBLIC int year(const Date* p) {
	return p->y_;
}
PUBLIC int week_day(const Date* p) {
	// week day i�in sakamoto algoritmas�n� kullan�caz. Biraz �st�nde de�i�iklik yap�lacak
	static const int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int y = year(p);
	int m = month(p);
	int d = month_day(p);
	if (m < 3)
		y -= 1;
	return ((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
}
PUBLIC int year_day(const Date* p);


PUBLIC Date* set_month_day(Date* p, int mday) {
	return set(p, mday, month(p), year(p));
}
PUBLIC Date* set_month(Date* p, int month) {
	return set(p, month_day(p), month, year(p));
}
PUBLIC Date* set_year(Date* p, int year) {
	return set(p, month_day(p), month(p), year);
}


PUBLIC Date* set_date(Date* p, int d, int m, int y) {
	return set(p, d, m, y);
}
PUBLIC Date* set_today(Date* p) {
	time_t sec;
	time(&sec);
	struct tm* tptr = localtime(&sec);
	return set(p, tptr->tm_mday, tptr->tm_mon + 1, tptr->tm_year + 1900);
}
PUBLIC Date* set_date_from_str(Date* p, const char* str) {
	int d = atoi(str);
	int m = atoi(str + 3);
	int y = atoi(str + 6);
	return set(p, d, m, y);
}
PUBLIC Date* set_random_date(Date* p) {
	int y = rand() % (RANDOM_YEAR_MAX - RANDOM_YEAR_MIN + 1) + RANDOM_YEAR_MIN;
	int m = rand() % 12 + 1;
	int d = rand() % MDAYS(y, m) + 1;
	return set(p, d, m, y);
}
PUBLIC Date* ndays_after(Date* presult, const Date* psource, int ndays) {
	return to_date(presult, totaldays(psource) + ndays);
}
PUBLIC Date* ndays_before(Date* presult, const Date* psource, int ndays) {
	return to_date(presult, totaldays(psource) - ndays);
}

PRIVATE Date* to_date(Date* p, int tdays) {
	int y = YEARBASE;
	while (tdays > (ISLEAP(y) ? 366 : 365)) {
		tdays -= (ISLEAP(y) ? 366 : 365);
		y++;
	}
	int m = 1;
	while (tdays > MDAYS(y, m)) {
		tdays -= MDAYS(y, m);
		m++;
	}
	int d = tdays;
	return set(p, d, m, y);
}


PRIVATE Date* set(Date* p, int d, int m, int y)
{
	if (!is_valid_date(d, m, y)) {
		fprintf(stderr, "gecersiz tarih olustu!\n");
		exit(EXIT_FAILURE);
	}
	p->d_ = d;
	p->m_ = m;
	p->y_ = y;
	return p;
}

PRIVATE int is_valid_date(int d, int m, int y) 
{
	return y >= YEARBASE && m > 0 && m <= 12 && d > 0 && d <= MDAYS(y, m);
		// YEARBASE kendimiz belirliyoruz 1900 tarihini ele ald�k biz. Ge�erli olmas� i�in 1900 ve �zerinde bir y�l olmas� gerek.
		// Ay 1 ve 12 aras�nda olmal�. 
		// g�n ise 1 ile MDAYS hesaplamas�n�n aras�nda olmal�. E�er o y�l art�k y�l ve ay �ubat ise <= 29, e�er art�k y�l de�il ve �ubat ise <= 28 olacak.
		// Art�k y�l hesaplamas�n� MDAYS ad�nda makro ile yap�yoruz. O da ISLEAP makrosunu kullan�yor ve lookup tabledan bak�yoruz art�k y�la.
}

PRIVATE int totaldays(const Date* p) {
	int sum = year_day(p);
	for (int i = YEARBASE; i < year(p); ++i) {
		sum += ISLEAP(i) ? 366 : 365;
	}
	return sum;
}