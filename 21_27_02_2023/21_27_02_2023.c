/* 21_27_02_2023 */
// undef, conditional compiling, pragma, Multiple inclusion guard


// Conditional Compiling nedir?
// C baþlýk dosyalarý çoðunlukla derleyicinin gördüðü ve göreceði kodtan daha fazla bildirim içeriyor.
// Fakat ön iþlemci programý çalýþtýrýldýðý zaman kodlarýn bir kýsmýný derleyiciye veriyor bir kýsmýný da vermiyor.
// Koþullu derlenme derken kast edilen aslýnda ön iþlemci program sürecinde deðerlendirilen koþullara baðlý olarak ön iþlemci programýn bazý kod bloklarýn içine girip ordaki bildirimleri vermesi/vermemesi.

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
-Donanýma baðlý. Farklý bildirim/kodlarýn kullanýlmasý gerekiyor olabilir.
-Ýþletim sistemi ile alakalý olabilir. (Bazý kodlar ortak olabilir/olmayabilir buna baðlý olarak farklý þekilde yazýlabilir)
-Kullanýlan programlama diline baðlý olabilir. (C ve CPP ortak noktalarý olsa da bire bir deðil. Derlenen programlama diline göre farklý kodlarýnn derleyici tarafýndan görülmesi için kullanýlabilir)
-Versiyona baðlý olabilir.
-Lokalizasyon, o ülkelere göre belirli kodlarýn farklý seçilmesi gerekebilir.
-Fiyata baðlý olabilir.
-Farklý diller için derleyicinin görmesi için deðiþtirilebilir

*/
//////////////////////////////////////////////////////////////////////////

// Assertion(assert) runtime da bir kodlama hatasý varsa assertion koduna takýlýp ekrana bir þeyler yazdýrýr.

#include <stdio.h>
void func(int x)
{
    if (x == 0) // x'in deðeri 0 ise
    {
        printf("%s kaynak dosyasýnýn %d. satýrýnda %s fonksiyonu içinde x'in degeri 0", __FILE__, __LINE__, __func__); // x'in deðerinin hangi satýrdaki hangi fonksiyon
        abort();                                                                                                        // ve hangi kaynak dosyasýnda olduðu bilgisini ekrana yazdýrýr
    }
    int y = 5;
    y /= x;
}

int main()
{
    func(0);
}
//////////////////////////////////////////////////////////////////////////

// assert() bir fonksiyonel makrodur. #include <assert.h> baþlýk dosyasýndan gelir.
// 2 ayrý dosya olur. Birisi debug file, diðeri de müþteriye giden. Debug file'da assert() gibi makrolar/fonksiyonlar kullanarak problemler çözülür ve müþteri sürümünde bu kodlar bulunmaz.

//////////////////////////////////////////////////////////////////////////

Koþullu derleme komutlarý nasýl kullanýlýr?
Bir kod bloðu(derleyicinin ve bizim bildiðimiz kod bloðundan(scope kavramý olan) bahsetmiyoruz) oluþturulur ve bir koþula baðlanýr.
Ön iþlemci programý bu koþulu doðru ya da yanlýþ olarak processing time'da evaluate eder.
if deyiminin 3 farklý biçimi olduðu gibi (if, else if, else) conditional makrolarýnda da benzer mantýk kullanýlýyor diyebiliriz.
*/
//////////////////////////////////////////////////////////////////////////
/* Girse ne olur girmezse ne olur?
1-)Eðer koþul doðru ise derleyiciye doðru kýsmýndaki kodlar verilecek. */

// koþul(true kabul edelim)
void func(int);
//

/*
2-)Bu bloðun içerisinde ön iþlemci komutlarýda olabilir */

// koþul(true kabul edelim)
#include "ali.h"
//
//////////////////////////////////////////////////////////////////////////

// #if ile if() ayný deðil karýþtýrma!

#if preprocessing expression

#endif
/* Hangi operatörleri kullanabiliriz?
-Aritmetik operatörler
-Bitsel operatörler
-Ternary operatörü
-Logical operator

-Gerçek sayý operatörü KULLANILAMAZ.
- ++ -- gibi operatörler KULLANILAMAZ.
- nonzero true, zero false kabul edilir.
*/
#if 1 // Eðer 0 olsa idi main'de çaðrý yapýlamazdý.
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
    a = 10; // UGUR 50den büyük olduðu için a deðiþkenine eriþebiliyoruz.
}
//////////////////////////////////////////////////////////////////////////
#define UGUR 100
#define OYKU 50
#if UGUR == 100 && OYKU == 50 // preprocessing expression denir buna.
int a;
#endif

int main(void)
{
    a = 10; // UGUR 50den büyük olduðu için a deðiþkenine eriþebiliyoruz.
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
    x = 5; // sentaks hatasý çünkü yanlýþ kýsma girdiði için x'in bildirimi yok.
    b = 10; // sýkýntý yok
}
//////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#define UGUR 10
#if UGUR > 19
int x = 1;
#else
#if UGUR == 10
int x = 2;
#endif // her bir if için #endif makrosu kullanýlýyor. Eðer kullanýlmaz ise "unterminated else" hatasýný veriyor.
#endif

int main()
{
    printf("%d", x);

    return 0;
}

//////////////////////////////////////////////////////////////////////////

// #elif makrosu kullanýldýðý zaman her if için #endif kullanmaya gerek yok 1 tane yeterli.

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
    printf("%d", x); // 2 yazdýrýr
    return 0;
}

//////////////////////////////////////////////////////////////////////////

/* KURALLAR */
//-Tanýmlanmamýþ macro identifierlarý 0 deðerinde kabul edilir.(statik ömürlü deðiþkenler gibi)
#if UGUR > -5 // burada hata yok. UGUR'un deðeri 0 olduðu için
int x = 5; // buraya eriþir ve x'in deðeri 5 olarak set edilir.
#endif

// Bir koþulun define edilmiþ olup olmamasýna bakmak.
// #ifdef identifier -> eðer tanýmlý ise doðru kabul edilecek
// #ifndef identifier -> eðer tanýmlý deðil ise doðru kabul edilecek.
#ifdef pp_expr
#endif

//////////////////////////////////////////////////////////////////////////

/* 3 Adet preprocessor operatörü vardýr.Bunlar;
1-#(stringification)
2-##(token pasting)
3-defined 
*/

#if defined NEC // bu ifdef NEC ile ayný anlama geliyor.
    int x = 5;
#endif

#if !defined NEC // bu ifned NEC ile ayný anlama geliyor
    int x = 5;
#endif

// önce #ifdef vardý daha sonra defined eklendi
// birden fazla identifier'ýn tanýmlý olup olmadýðýný daha rahat anlamak/görmek için "defined" eklenmiþtir.

#ifdef UGR

#else
#ifdef OYK
#endif
#endif
// çok karmaþýk ve göze korkutucu geliyor.

#if defined UGR && !defined OYK
#endif
// daha kolay ve göze sade geliyor.

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// conditional compiling'e derleyici tarafýndan optimizasyon yapýlmaz

//////////////////////////////////////////////////////////////////////////

#define PRC 3.1234    // burada sorun yok.
#if PRC > 4.23123    // burasý hata verir .Çünkü tamsayý olmak zorunda bu karþýlaþtýrma.
#endif

//////////////////////////////////////////////////////////////////////////     

// PREDEFINED MACRO / PREDEFINED SYMBOLIC CONSTANTS (ÖN TANIMLI MAKROLAR)
// Bazý makrolar, define ile tanýmlanmýþ olmasa bile dilin kurallarý gereði ön iþlemci programý bunlarý yer deðiþtirmeye tabii tutuyor.
/* Bazýlarý þunlardýr
__LINE__ , bulunduðu satýrýn numarasý ile deðiþtiriyor. Tamsayý kullanýr. 
__FILE__ , Dosyanin adýný kullanýr, string kullanýr. ORN: bu ders notlarýnýn bulunduðu .c dosyasý için kullanýr isek "21_27_02_2023.c" olur.
__DATE__ , Tarihi alýr, string "12 05 1987"
__TIME__ , Saat, "12:45:54", string
__STDC__ ,
-C89 ile gelen ilk predefined makrolar bunlar. 
-Kesinlikle bilinmesi gerekiyor.
*/

//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
int main(void)
{
    printf("%s dosyasýnýn %d. satiri ", __FILE__, __LINE__);
    printf("Compilation Date: %s", __DATE__);
    printf("Compilation Time: %s", __TIME__);
}

// __STDC__ derleyicinin C derleyicisi olup olmadýðý için kullanýlabilir.

#ifdef __STDC__ // c derleyicisi ise içeri girecek, deðil ise girmeyecek.
    int x = 1;
#elif __cplusplus // CPP derleyicisi ise buraya
    int x = 2;
#else
    int x = 3;
#endif

//////////////////////////////////////////////////////////////////////////

#error -> programýn derlenmesini öniþlemci aþamasýnda durduruyor.
#error "hata mesajý"

#ifndef __STDC__ // eðer __STDC__ predefined makrosu yok ise program compile time'ý sonlandýrýyor. Yani sadece C derleyecisinde çalýþýr.
#error Sadece C derleyicisinde çalýþýr.  
    // "Sadece C derleyicisinde çalýþýr." yazýsý hata olarak yazdýrýlýr.
#endif
    
//////////////////////////////////////////////////////////////////////////
#include <stdio.h>
// #line bu makro __LINE__ ve __FILE__ predefined makrolarýnýn deðerini deðiþtiriyor
#line 6676 "ugur.c"
printf("%s dosyasinin %d. satiri", __FILE__, __LINE__);
// Bazý c kodlarýnýn varlýk nedeni code generate yapmak. Çok kullanýlan bir þey deðil. (binde bir belki)

//////////////////////////////////////////////////////////////////////////

Multiple inclusion guard

    Ön iþlemci programýn bir baþlýk dosyasý içindeki koda bir kere deðil birden fazla girmesi bazý sakýncalar oluþturur.
    Multiple inc. guard, Ayný dosyanýn birden fazla kez include edilmesini engeller.
#include "ugur.h"
#include "ugur.h" // bu baþlýk dosyasý 2. kez include edilmez. 
    // ugur.h içerisinde alttaki struct'ýn bulunduðunu varsayalým.

    struct Date {
    int d, m, y;
};
// Dosyanýn içinde eðer fonksiyon var ise birden fazla yazýldýðýnda "function re-declaration" olur iken, struct'ta sentaks hatasýna sebep olur.
#ifndef UGUR_H
#define UGUR_H
    struct Date {
    int d, m, y;
};
#endif


//////////////////////////////////////////////////////////////////////////

#pragma

    Ne yapacaðý derleyicilerin implementasyonuna baðlý. Farklý derleyicilerde farklý anlamlarý olabilir. 

#pragma once -> multip inc. guard saðlýyor. Birden fazla kullanýlmasýný engelliyor. #ifndef #endif kullanmak yerine #pragma once daha kolay, kullaným pratikliði saðlýyor.
#pragma pack(1) -> alignment saðlýyor.
#pragma warning (disable: 4706)   4706 nolu uyarý mesajýný verme demek bu.

