/* 21_27_02_2023 */
// undef, conditional compiling, pragma, Multiple inclusion guard


// Conditional Compiling nedir?
// C ba�l�k dosyalar� �o�unlukla derleyicinin g�rd��� ve g�rece�i kodtan daha fazla bildirim i�eriyor.
// Fakat �n i�lemci program� �al��t�r�ld��� zaman kodlar�n bir k�sm�n� derleyiciye veriyor bir k�sm�n� da vermiyor.
// Ko�ullu derlenme derken kast edilen asl�nda �n i�lemci program s�recinde de�erlendirilen ko�ullara ba�l� olarak �n i�lemci program�n baz� kod bloklar�n i�ine girip ordaki bildirimleri vermesi/vermemesi.

/*
#if
#endif
#else
#elif
#ifdef
#ifndef
#undef
*/

//////////////////////////////////////////////////////////////////////////

/*
Neden Conditional Compiling?
-Donan�ma ba�l�. Farkl� bildirim/kodlar�n kullan�lmas� gerekiyor olabilir.
-��letim sistemi ile alakal� olabilir. (Baz� kodlar ortak olabilir/olmayabilir buna ba�l� olarak farkl� �ekilde yaz�labilir)
-Kullan�lan programlama diline ba�l� olabilir. (C ve CPP ortak noktalar� olsa da bire bir de�il. Derlenen programlama diline g�re farkl� kodlar�nn derleyici taraf�ndan g�r�lmesi i�in kullan�labilir)
-Versiyona ba�l� olabilir.
-Lokalizasyon, o �lkelere g�re belirli kodlar�n farkl� se�ilmesi gerekebilir.
-Fiyata ba�l� olabilir.
-Farkl� diller i�in derleyicinin g�rmesi i�in de�i�tirilebilir

*/
//////////////////////////////////////////////////////////////////////////

// Assertion(assert) runtime da bir kodlama hatas� varsa assertion koduna tak�l�p ekrana bir �eyler yazd�r�r.

#include <stdio.h>
void func(int x)
{
    if (x == 0) // x'in de�eri 0 ise
    {
        printf("%s kaynak dosyas�n�n %d. sat�r�nda %s fonksiyonu i�inde x'in degeri 0", __FILE__, __LINE__, __func__); // x'in de�erinin hangi sat�rdaki hangi fonksiyon
        abort();                                                                                                        // ve hangi kaynak dosyas�nda oldu�u bilgisini ekrana yazd�r�r
    }
    int y = 5;
    y /= x;
}

int main()
{
    func(0);
}
//////////////////////////////////////////////////////////////////////////

// assert() bir fonksiyonel makrodur. #include <assert.h> ba�l�k dosyas�ndan gelir.
// 2 ayr� dosya olur. Birisi debug file, di�eri de m��teriye giden. Debug file'da assert() gibi makrolar/fonksiyonlar kullanarak problemler ��z�l�r ve m��teri s�r�m�nde bu kodlar bulunmaz.

//////////////////////////////////////////////////////////////////////////

Ko�ullu derleme komutlar� nas�l kullan�l�r?
Bir kod blo�u(derleyicinin ve bizim bildi�imiz kod blo�undan(scope kavram� olan) bahsetmiyoruz) olu�turulur ve bir ko�ula ba�lan�r.
�n i�lemci program� bu ko�ulu do�ru ya da yanl�� olarak processing time'da evaluate eder.
if deyiminin 3 farkl� bi�imi oldu�u gibi (if, else if, else) conditional makrolar�nda da benzer mant�k kullan�l�yor diyebiliriz.
*/
//////////////////////////////////////////////////////////////////////////
/* Girse ne olur girmezse ne olur?
1-)E�er ko�ul do�ru ise derleyiciye do�ru k�sm�ndaki kodlar verilecek. */

// ko�ul(true kabul edelim)
void func(int);
//

/*
2-)Bu blo�un i�erisinde �n i�lemci komutlar�da olabilir */

// ko�ul(true kabul edelim)
#include "ali.h"
//
//////////////////////////////////////////////////////////////////////////

// #if ile if() ayn� de�il kar��t�rma!

#if preprocessing expression

#endif
/* Hangi operat�rleri kullanabiliriz?
-Aritmetik operat�rler
-Bitsel operat�rler
-Ternary operat�r�
-Logical operator

-Ger�ek say� operat�r� KULLANILAMAZ.
- ++ -- gibi operat�rler KULLANILAMAZ.
- nonzero true, zero false kabul edilir.
*/
#if 1 // E�er 0 olsa idi main'de �a�r� yap�lamazd�.
void foo(int);
#endif
int main(void)
{
    foo(12);
}

//////////////////////////////////////////////////////////////////////////

#define UGUR 100
#if UGUR > 50
int a = 5;
#endif

int main(void)
{
    a = 10; // UGUR 50den b�y�k oldu�u i�in a de�i�kenine eri�ebiliyoruz.
}
//////////////////////////////////////////////////////////////////////////
#define UGUR 100
#define OYKU 50
#if UGUR == 100 && OYKU == 50 // preprocessing expression denir buna.
int a;
#endif

int main(void)
{
    a = 10; // UGUR 50den b�y�k oldu�u i�in a de�i�kenine eri�ebiliyoruz.
}
//////////////////////////////////////////////////////////////////////////

#define UGUR 6
#if UGUR == 5
int x;
#else
int b;
#endif
int main(void)
{
    x = 5; // sentaks hatas� ��nk� yanl�� k�sma girdi�i i�in x'in bildirimi yok.
    b = 10; // s�k�nt� yok
}
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#define UGUR 10
#if UGUR > 19
int x = 1;
#else
#if UGUR == 10
int x = 2;
#endif // her bir if i�in #endif makrosu kullan�l�yor. E�er kullan�lmaz ise "unterminated else" hatas�n� veriyor.
#endif

int main()
{
    printf("%d", x);

    return 0;
}

//////////////////////////////////////////////////////////////////////////

// #elif makrosu kullan�ld��� zaman her if i�in #endif kullanmaya gerek yok 1 tane yeterli.

#include <stdio.h>
#define UGUR 10
#if UGUR > 10
int x = 1;
#elif UGUR == 10
int x = 2;
#elif UGUR < 10
int x = 3;
#endif

int main()
{
    printf("%d", x); // 2 yazd�r�r
    return 0;
}

//////////////////////////////////////////////////////////////////////////

/* KURALLAR */
//-Tan�mlanmam�� macro identifierlar� 0 de�erinde kabul edilir.(statik �m�rl� de�i�kenler gibi)
#if UGUR > -5 // burada hata yok. UGUR'un de�eri 0 oldu�u i�in
int x = 5; // buraya eri�ir ve x'in de�eri 5 olarak set edilir.
#endif

// Bir ko�ulun define edilmi� olup olmamas�na bakmak.
// #ifdef identifier -> e�er tan�ml� ise do�ru kabul edilecek
// #ifndef identifier -> e�er tan�ml� de�il ise do�ru kabul edilecek.
#ifdef pp_expr
#endif

//////////////////////////////////////////////////////////////////////////

/* 3 Adet preprocessor operat�r� vard�r.Bunlar;
1-#(stringification)
2-##(token pasting)
3-defined 
*/

#if defined NEC // bu ifdef NEC ile ayn� anlama geliyor.
    int x = 5;
#endif

#if !defined NEC // bu ifned NEC ile ayn� anlama geliyor
    int x = 5;
#endif

// �nce #ifdef vard� daha sonra defined eklendi
// birden fazla identifier'�n tan�ml� olup olmad���n� daha rahat anlamak/g�rmek i�in "defined" eklenmi�tir.

#ifdef UGR

#else
#ifdef OYK
#endif
#endif
// �ok karma��k ve g�ze korkutucu geliyor.

#if defined UGR && !defined OYK
#endif
// daha kolay ve g�ze sade geliyor.

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// conditional compiling'e derleyici taraf�ndan optimizasyon yap�lmaz

//////////////////////////////////////////////////////////////////////////

#define PRC 3.1234    // burada sorun yok.
#if PRC > 4.23123    // buras� hata verir .��nk� tamsay� olmak zorunda bu kar��la�t�rma.
#endif

//////////////////////////////////////////////////////////////////////////     

// PREDEFINED MACRO / PREDEFINED SYMBOLIC CONSTANTS (�N TANIMLI MAKROLAR)
// Baz� makrolar, define ile tan�mlanm�� olmasa bile dilin kurallar� gere�i �n i�lemci program� bunlar� yer de�i�tirmeye tabii tutuyor.
/* Baz�lar� �unlard�r
__LINE__ , bulundu�u sat�r�n numaras� ile de�i�tiriyor. Tamsay� kullan�r. 
__FILE__ , Dosyanin ad�n� kullan�r, string kullan�r. ORN: bu ders notlar�n�n bulundu�u .c dosyas� i�in kullan�r isek "21_27_02_2023.c" olur.
__DATE__ , Tarihi al�r, string "12 05 1987"
__TIME__ , Saat, "12:45:54", string
__STDC__ ,
-C89 ile gelen ilk predefined makrolar bunlar. 
-Kesinlikle bilinmesi gerekiyor.
*/

//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
int main(void)
{
    printf("%s dosyas�n�n %d. satiri ", __FILE__, __LINE__);
    printf("Compilation Date: %s", __DATE__);
    printf("Compilation Time: %s", __TIME__);
}

// __STDC__ derleyicinin C derleyicisi olup olmad��� i�in kullan�labilir.

#ifdef __STDC__ // c derleyicisi ise i�eri girecek, de�il ise girmeyecek.
    int x = 1;
#elif __cplusplus // CPP derleyicisi ise buraya
    int x = 2;
#else
    int x = 3;
#endif

//////////////////////////////////////////////////////////////////////////

#error -> program�n derlenmesini �ni�lemci a�amas�nda durduruyor.
#error "hata mesaj�"

#ifndef __STDC__ // e�er __STDC__ predefined makrosu yok ise program compile time'� sonland�r�yor. Yani sadece C derleyecisinde �al���r.
#error Sadece C derleyicisinde �al���r.  
    // "Sadece C derleyicisinde �al���r." yaz�s� hata olarak yazd�r�l�r.
#endif
    
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
// #line bu makro __LINE__ ve __FILE__ predefined makrolar�n�n de�erini de�i�tiriyor
#line 6676 "ugur.c"
printf("%s dosyasinin %d. satiri", __FILE__, __LINE__);
// Baz� c kodlar�n�n varl�k nedeni code generate yapmak. �ok kullan�lan bir �ey de�il. (binde bir belki)

//////////////////////////////////////////////////////////////////////////

Multiple inclusion guard

    �n i�lemci program�n bir ba�l�k dosyas� i�indeki koda bir kere de�il birden fazla girmesi baz� sak�ncalar olu�turur.
    Multiple inc. guard, Ayn� dosyan�n birden fazla kez include edilmesini engeller.
#include "ugur.h"
#include "ugur.h" // bu ba�l�k dosyas� 2. kez include edilmez. 
    // ugur.h i�erisinde alttaki struct'�n bulundu�unu varsayal�m.

    struct Date {
    int d, m, y;
};
// Dosyan�n i�inde e�er fonksiyon var ise birden fazla yaz�ld���nda "function re-declaration" olur iken, struct'ta sentaks hatas�na sebep olur.
#ifndef UGUR_H
#define UGUR_H
    struct Date {
    int d, m, y;
};
#endif


//////////////////////////////////////////////////////////////////////////

#pragma

    Ne yapaca�� derleyicilerin implementasyonuna ba�l�. Farkl� derleyicilerde farkl� anlamlar� olabilir. 

#pragma once -> multip inc. guard sa�l�yor. Birden fazla kullan�lmas�n� engelliyor. #ifndef #endif kullanmak yerine #pragma once daha kolay, kullan�m pratikli�i sa�l�yor.
#pragma pack(1) -> alignment sa�l�yor.
#pragma warning (disable: 4706)   4706 nolu uyar� mesaj�n� verme demek bu.

