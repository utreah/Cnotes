E�er bir t�r d�n���m� yap�lmak isteniyorsa ve bu d�n���m derleyici taraf�ndan otomatik yap�l�yorsa bu;
	implicit yani �rt�l� d�n���md�r.
E�er bir t�r d�n�m��� isteniyor fakat derleyici taraf�ndan otomatik bir d�n���m yap�lm�yor ise;
	type - cast(t�r d�n��t�rme operat�r�) operator ile yap�l�r.;


Operat�r tablosunda 2. s�rada bulunur.


---------------------------------------------------------
2- (type) + - ++ -- & sizeof ! sa�dan sola �ncelik y�n�
---------------------------------------------------------

parantez i�erisine d�n��t�rmesini istedi�i "hedef t�r�" yaz�yoruz. -> (d�n��t�r�lecek t�r) -> (double)expr (int)expr
///////////////////////////////////////////////////////////////////////////////////////////////////



int main(void)
{
		int ival = 4;
		int dval = 46.4;
		(double)ival; // ival'in t�r� burada double ve (double)ival bir expressiondur. De�eri double t�r�nden 4t�r.
					// value kategorisi rValue'dur.
					// t�r d�n���m� operat�r� ile olu�turulan de�erler C dili i�in her zaman rvalue dur.
					// C ve CPP'de statik t�r kavram� oldu�undan dolay�, bir t�r�n asla ve asla de�i�mez.
					// t�r d�n���mleri ge�ici nesne olu�turularak ger�ekle�tiriliyor. (dynamic-type)

}
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
int main()
{
	int sum = 34543;
	int n = 76;
//	double avg = sum / n; // bu �ekilde sum ve n int oldu�u i�in avg de�i�keni double olsa bile sonu� int olacakt�r. �ki �ekilde yap�labilir ->
	double avg = (double)sum / n; // (type) type-cast operat�r� sayesinde sum'�n de�eri ge�ici bir double nesneye aktar�l�r. ve n implicit type conversiondan dolay� double olur.(veri kayb� yok)
	double avg = 1. * sum / n; // burada i�lem �arpma/b�lme operat�r�n�n i�lem �nceli�i soldan sa�a olmas�ndan dolay� sum'�n de�eri double olan 1. ile �arp�l�r ve sum bu noktada double t�r�nde i�lem g�r�r
										// ve b�lmenin sol taraf� double oldu�u i�in sa� taraf�da double t�r�ne d�n��tr�l�rek i�lem yap�l�r -> implicit type conversion.
	printf("%f", avg); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// a�a��daki kod int t�r�n�n 4, long long t�r�n�n 8 byte oldu�u bir sistemde derlenmekte
int main(void)
{
	int x, y;
	scanf("%d%d", &x, &y);
	x * y; // 2 147 483 647 (i�aretli int s�n�r�) e�er buradan elde edilecek de�er bu s�n�r� a�ar ise Undefined Behavior'dur.
		// E�er bu i�lem long long'ta yap�lm�� olsayd� ta�ma s�n�r� 9 kentilyona b�y�yecekti ve tan�ms�z davran�� ihtimali azalacakt�. 

	x * (long long)y; // e�er bir fark yaratm�yor ise type-cast operat�r� sol operanda yaz�l�r. Sa�a yaz�ld���nda bir anlam veya run timeda fark yaratmayacak.

}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	int x = 54124;
	double mean = x / 142; // burada x int ve 142 ifadesi sabit oldu�u i�in veri kayb� olur. �ki �ekilde yap�labilir.
	double mean = (double)x / 142; // type-cast operat�r� kullan�larak veya
	double mean = x / 142.; // sabit ifadesi double yap�larak(sabitlerde tercih edilen y�ntem bu) -> sabitin yan�na . (nokta) koyarak yap�labilir.

}


// �rt�l� d�n���m�n derleyici taraf�ndan yap�ld��� durumlar.
void func(float);
int main(void)
{
	double dval = 123123.5566;
	int ival = dval; // Yapmak istedi�imiz bu olsa da burada hem warning verir hem de okuyan�n kafas� kar��abilir.
	int ival = (int)dval; // B�yle yaz�l�rsa ne warning al�n�r ne de okuyan�n akl� kar���r.
	func(dval); // possible loss of data conversion float to double warning verir.
	func((float)dval); // s�k�nt� yok, veri kayb�da yok. 
	int ival = (int)dval; // e�er dval'in de�eri int s�n�rlar� i�erisinde de�ilse tan�ms�z davran�� olu�ur(i�aretli intte ge�erli bu durum, i�aretsizde 0 olur
}

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	srand(); // srand'�n parametresi unsigned int
	time(); // time ise long long bundan dolay� srand(time()) kullan�l�rken unsigned diye yaz�l�r.
	srand((unsigned)time(0)); // bu normal
}

///////////////////////////////////////////////////////////////////////////////////////////////////


Rastgelelik �ng�r�lemezlilik ile alakal�.�ng�r�lemezlik ne kadar y�ksek ise rastgelelik o kadar y�ksektir.

7 7 7 7 7 7 ?
7 gelmesi beklenir.�ng�r�lemezlik �ok �ok d���k.

1 2 3 1 2 3 1 2 ?
3 gelmesi beklenir.Rastgelelik d���k, �ng�r�lebilirlik y�ksek.

bir�ok programda rasgelelik �ok y�ksek olmal�.

random number generation;
1 - True(ly) random generation : do�adaki olaylardan faydalan�yor.atmosferic noise, zaman.Bir cihaza ihtiya� var.

2 - Pseudo random generation : S�zde rastgele say�l� �retimi.matematiksel s�re�.herhangibir rasgelelik yok.sadece �yle bir izlenim veriyor.

1 - true->avantaj� ger�ekten �ng�r�lmez olmas�
- External(bir cihaz yard�m� gerekiyor.
	- Tekrar edilebilir de�il.
	- Non - deterministic(ger�ekten �ng�r�lemez, sadece cenab - � allah bilir - necati ergin)

	2 - pseudo->avantaj� h�zl� olmas� ve ayn� say� zincirini istenildi�i kadar tekrarlayabilir olmas�.
	dezavantaj� �ng�r�lebilir oluyor.bir seed value gerekiyor.
	- Tekrar edilebilir(sat�r 117)
	- Deterministic(ayn� input ==> ayn� outputu vermek zorunda)

	///////////////////////////////////////////////////////////////////////////////////////////////////

	Mersenne twister(en �ok kullan�lan random num gen) C dilinde yok!
	Programlamada da �ok fazla yerde rastgele say� �retimine ihtiya� duyuyoruz.
	Mesela;
-Test kodlar�n�n yaz�lmas�nda.
- Sim�lasyon kodlar�nda
- Kriptoloji.
- Genetik algoritma kategorisinde.
- Oyun programlar�nda.

///////////////////////////////////////////////////////////////////////////////////////////////////
Ba�lang�� de�erlerine seed value denir.
C dilinde rastgele say� �retimi i�in bir destek yok. (kendi standart d�k�mantasyonunda bile e�er rastgelelik �nemliyse kullanmay�n diye uyar�yor)
CPP'de ise bir s�r� farkl� random say� �retmek i�in fonksiyonu bulunuyor. 
C standart k�t�phanesi da��l�m i�in hi�bir �ey sunmuyor.

int rand(void)  0 - RAND_MAX(stdlib.h'ta 'tan�ml� bir object - like makro) aras�nda say�lar d�nd�r�r.macronun de�eri compilerlar�n �o�unda 32767 oluyor. (default seed val = > 1)
void srand(unsigned seed); srand fonksiyonu seed set ediyor.Rastgele say� �retmiyor.
Bilgisayar ger�ek anlamda rasgele say� �retmez.Deterministik bir alet ��nk�.

bir seed / tohum de�eri gerekiyor bunun i�in.
Seed de�erini set eden fonksiyon srand dir

ayn� seed de�eri i�in hep ayn� say�lar� �retir.

///////////////////////////////////////////////////////////////////////////////////////////////////

rastgele say� �retimi ile bu say�lar�n matematiksel da��l�m� ayn� �ey de�ildir.

uniform distribution : K�medeki b�t�n de�erlerin olas�l��� ayn�. (tavla oyunu i�in i�e yarayabilir : D) her zaman optimal olmaz.

<stdlib.h> mod�l� di�er mod�llerden baya�� farkl�.Birden fazl� farkl� alanda genel destek veren fonksiyonlar�n da bildirimi oldu�u bir ba�l�k dosyas�.
// exit, abort, rand, srand, malloc, calloc, realloc, free, atoi, atof, atol gibi fonksiyonlar var. 


D�KKAT!
Daha �nce, g�rd���m�z kod �rneklerinde belirli aral�kta uniform da��lm�� rastgele say�lar i�in mod operat�r�n�n kullan�ld���n� g�rm�� olabilirisiniz ama
bu matematiksel olarak do�ru de�il.E�er �nemli de�ilse kullan�labilir.

E�er program her �al��t�r�ld���nda seed farkl� olacak �ekilde rastgele say� �retmek istiyorsak 2 y�ntem var;

1- (E�er m�mk�nse) say� ger�ek rastgele say� �retiminden alabilir.
2- Tohum de�eri i�in zamanla de�i�en bir de�er kullanmak. Onun i�idne <time.h> dosyas� include edilmeli 
		// srand((unsigned)timme(0))

///////////////////////////////////////////////////////////////////////////////////////////////////

rastgele say�lar �retmekte m�mk�n.Bunun i�in hava durumu, klavyeye bas�lma s�releri fark�, OS api
varsa ki genelde oluyor, yap�yorlar bunu.

srand i�erisine time(0) arg�man�n� g�nderirsek.bu sefer 01 01 1970 ten sonra ge�en zaman� g�steriyor
bu da s�rekli de�i�iyor.bunu almak mant�kl�.

printf("%ld", time(0));->bu 1970 ten bu yana olan zaman� saniye cinsinden verir.

srand(time(0))->bu her seferinde zaman ge�ece�i i�in srand e verilen seed de�eri de�i�ecek
yani her seferinde farkl� say� zinciri olu�acak.burada uyar� mesaj� verir compiler.
time() fonksiyonu long long veya unsigned long olablir.ama srand in parametresi unsigned int
bu y�zden srand fonksiyonunu �a��r�rken time() fonksiyonunu parametre atarken
explicit olarak t�r�n� de�i�tirmeliyiz. ->srand((unsigned)timme(0))

///////////////////////////////////////////////////////////////////////////////////////////////////

Herhangi bir de�i�kene set etmek istemiyorsak NULL keyword�n� kullanabiliriz.
srand((unsigned)NULL) -> geri d�n�� de�eri ayn� EPOCHtan ge�en saniye say�s�. ama de�er bir de�i�kene set edilmiyor. Set etmek istersekte
call by reference yaparak yapabiliriz. Ayn� zamanda "randomize" idiyomu olarakta biliniyor.
srand((unsigned)&expr)
#define RANDOMIZE() srand((unsigned)time(NULL))
// RANDOMIZE() e�er ba�ka bir fonksiyonun i�inde ise ve o fonksiyon bir saniye i�erisinde birden fazla kez(d�ng�) �a��r�l�rsa
// RANDOMIZE()'dan gelen de�er birden fazla kez kullan�l�r. 
/*
void print_random_psw(void)
{
	int len = rand() % 8 + 5;
	//randomize(); // burada �a�r�lsayd� her bir saniyede �retilen t�m rand de�erler ayn� olacak.��nk� 1sn i�in seed de�eri
	while (len--)	// ayn� kal�yor ve her seferinde tekrardan randomize fonksiyonu �al��t�r�ld���nda o zincirin en ba��na at�yor.
	{
		putchar(rand() % 26 + 'a' );
	}
	putchar('\n');

}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define HEADS 1
#define NTOSS 1000000
#define RANDOMIZE() srand((unsigned)time(NULL))

int main(void)
{
	RANDOMIZE();
	int heads_count = 0;
	for (int i = 0; i < NTOSS; i++)
		if (rand() % 2 == 0)
			heads_count++;
	printf("Olas�l�k %f", (double)heads_count / NTOSS);
}

///////////////////////////////////////////////////////////////////////////////////////////////////


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "nutility.h"
#include <ctype.h>

#define HEADS 0
#define NTOSS 10'000'000 

int roll_dice(void)
{
	int dice1 = rand() % 6 + 1;
	int dice2 = rand() % 6 + 1;

	return dice1 + dice2;
}

int game_(int dice_new)
{
	for (;;)
	{
		int new_roll_dice = roll_dice();
		if (new_roll_dice == dice_new)
		{
			return 1;
		}
		if (new_roll_dice == 7)
			return 0;
	}


}


// 1 -> win
// 0 -> lose
int game(void)
{
	int dice = roll_dice();
	switch (dice)
	{
	case 7:
	case 11:
		return 1;
	case 2:
	case 3:
	case 12:
		return 0;
	default:
		return game_(dice);
	}

}


	



