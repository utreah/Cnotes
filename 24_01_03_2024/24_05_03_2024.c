Eðer bir tür dönüþümü yapýlmak isteniyorsa ve bu dönüþüm derleyici tarafýndan otomatik yapýlýyorsa bu;
	implicit yani örtülü dönüþümdür.
Eðer bir tür dönümüþü isteniyor fakat derleyici tarafýndan otomatik bir dönüþüm yapýlmýyor ise;
	type - cast(tür dönüþtürme operatörü) operator ile yapýlýr.;


Operatör tablosunda 2. sýrada bulunur.


---------------------------------------------------------
2- (type) + - ++ -- & sizeof ! saðdan sola öncelik yönü
---------------------------------------------------------

parantez içerisine dönüþtürmesini istediði "hedef türü" yazýyoruz. -> (dönüþtürülecek tür) -> (double)expr (int)expr
///////////////////////////////////////////////////////////////////////////////////////////////////



int main(void)
{
		int ival = 4;
		int dval = 46.4;
		(double)ival; // ival'in türü burada double ve (double)ival bir expressiondur. Deðeri double türünden 4tür.
					// value kategorisi rValue'dur.
					// tür dönüþümü operatörü ile oluþturulan deðerler C dili için her zaman rvalue dur.
					// C ve CPP'de statik tür kavramý olduðundan dolayý, bir türün asla ve asla deðiþmez.
					// tür dönüþümleri geçici nesne oluþturularak gerçekleþtiriliyor. (dynamic-type)

}
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
int main()
{
	int sum = 34543;
	int n = 76;
//	double avg = sum / n; // bu þekilde sum ve n int olduðu için avg deðiþkeni double olsa bile sonuç int olacaktýr. Ýki þekilde yapýlabilir ->
	double avg = (double)sum / n; // (type) type-cast operatörü sayesinde sum'ýn deðeri geçici bir double nesneye aktarýlýr. ve n implicit type conversiondan dolayý double olur.(veri kaybý yok)
	double avg = 1. * sum / n; // burada iþlem çarpma/bölme operatörünün iþlem önceliði soldan saða olmasýndan dolayý sum'ýn deðeri double olan 1. ile çarpýlýr ve sum bu noktada double türünde iþlem görür
										// ve bölmenin sol tarafý double olduðu için sað tarafýda double türüne dönüþtrülürek iþlem yapýlýr -> implicit type conversion.
	printf("%f", avg); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// aþaðýdaki kod int türünün 4, long long türünün 8 byte olduðu bir sistemde derlenmekte
int main(void)
{
	int x, y;
	scanf("%d%d", &x, &y);
	x * y; // 2 147 483 647 (iþaretli int sýnýrý) eðer buradan elde edilecek deðer bu sýnýrý aþar ise Undefined Behavior'dur.
		// Eðer bu iþlem long long'ta yapýlmýþ olsaydý taþma sýnýrý 9 kentilyona büyüyecekti ve tanýmsýz davranýþ ihtimali azalacaktý. 

	x * (long long)y; // eðer bir fark yaratmýyor ise type-cast operatörü sol operanda yazýlýr. Saða yazýldýðýnda bir anlam veya run timeda fark yaratmayacak.

}

///////////////////////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	int x = 54124;
	double mean = x / 142; // burada x int ve 142 ifadesi sabit olduðu için veri kaybý olur. Ýki þekilde yapýlabilir.
	double mean = (double)x / 142; // type-cast operatörü kullanýlarak veya
	double mean = x / 142.; // sabit ifadesi double yapýlarak(sabitlerde tercih edilen yöntem bu) -> sabitin yanýna . (nokta) koyarak yapýlabilir.

}


// Örtülü dönüþümün derleyici tarafýndan yapýldýðý durumlar.
void func(float);
int main(void)
{
	double dval = 123123.5566;
	int ival = dval; // Yapmak istediðimiz bu olsa da burada hem warning verir hem de okuyanýn kafasý karýþabilir.
	int ival = (int)dval; // Böyle yazýlýrsa ne warning alýnýr ne de okuyanýn aklý karýþýr.
	func(dval); // possible loss of data conversion float to double warning verir.
	func((float)dval); // sýkýntý yok, veri kaybýda yok. 
	int ival = (int)dval; // eðer dval'in deðeri int sýnýrlarý içerisinde deðilse tanýmsýz davranýþ oluþur(iþaretli intte geçerli bu durum, iþaretsizde 0 olur
}

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	srand(); // srand'ýn parametresi unsigned int
	time(); // time ise long long bundan dolayý srand(time()) kullanýlýrken unsigned diye yazýlýr.
	srand((unsigned)time(0)); // bu normal
}

///////////////////////////////////////////////////////////////////////////////////////////////////


Rastgelelik öngörülemezlilik ile alakalý.Öngörülemezlik ne kadar yüksek ise rastgelelik o kadar yüksektir.

7 7 7 7 7 7 ?
7 gelmesi beklenir.Öngörülemezlik çok çok düþük.

1 2 3 1 2 3 1 2 ?
3 gelmesi beklenir.Rastgelelik düþük, öngörülebilirlik yüksek.

birçok programda rasgelelik çok yüksek olmalý.

random number generation;
1 - True(ly) random generation : doðadaki olaylardan faydalanýyor.atmosferic noise, zaman.Bir cihaza ihtiyaç var.

2 - Pseudo random generation : Sözde rastgele sayýlý üretimi.matematiksel süreç.herhangibir rasgelelik yok.sadece öyle bir izlenim veriyor.

1 - true->avantajý gerçekten öngörülmez olmasý
- External(bir cihaz yardýmý gerekiyor.
	- Tekrar edilebilir deðil.
	- Non - deterministic(gerçekten öngörülemez, sadece cenab - ý allah bilir - necati ergin)

	2 - pseudo->avantajý hýzlý olmasý ve ayný sayý zincirini istenildiði kadar tekrarlayabilir olmasý.
	dezavantajý öngörülebilir oluyor.bir seed value gerekiyor.
	- Tekrar edilebilir(satýr 117)
	- Deterministic(ayný input ==> ayný outputu vermek zorunda)

	///////////////////////////////////////////////////////////////////////////////////////////////////

	Mersenne twister(en çok kullanýlan random num gen) C dilinde yok!
	Programlamada da çok fazla yerde rastgele sayý üretimine ihtiyaç duyuyoruz.
	Mesela;
-Test kodlarýnýn yazýlmasýnda.
- Simülasyon kodlarýnda
- Kriptoloji.
- Genetik algoritma kategorisinde.
- Oyun programlarýnda.

///////////////////////////////////////////////////////////////////////////////////////////////////
Baþlangýç deðerlerine seed value denir.
C dilinde rastgele sayý üretimi için bir destek yok. (kendi standart dökümantasyonunda bile eðer rastgelelik önemliyse kullanmayýn diye uyarýyor)
CPP'de ise bir sürü farklý random sayý üretmek için fonksiyonu bulunuyor. 
C standart kütüphanesi daðýlým için hiçbir þey sunmuyor.

int rand(void)  0 - RAND_MAX(stdlib.h'ta 'tanýmlý bir object - like makro) arasýnda sayýlar döndürür.macronun deðeri compilerlarýn çoðunda 32767 oluyor. (default seed val = > 1)
void srand(unsigned seed); srand fonksiyonu seed set ediyor.Rastgele sayý üretmiyor.
Bilgisayar gerçek anlamda rasgele sayý üretmez.Deterministik bir alet çünkü.

bir seed / tohum deðeri gerekiyor bunun için.
Seed deðerini set eden fonksiyon srand dir

ayný seed deðeri için hep ayný sayýlarý üretir.

///////////////////////////////////////////////////////////////////////////////////////////////////

rastgele sayý üretimi ile bu sayýlarýn matematiksel daðýlýmý ayný þey deðildir.

uniform distribution : Kümedeki bütün deðerlerin olasýlýðý ayný. (tavla oyunu için iþe yarayabilir : D) her zaman optimal olmaz.

<stdlib.h> modülü diðer modüllerden bayaðý farklý.Birden fazlý farklý alanda genel destek veren fonksiyonlarýn da bildirimi olduðu bir baþlýk dosyasý.
// exit, abort, rand, srand, malloc, calloc, realloc, free, atoi, atof, atol gibi fonksiyonlar var. 


DÝKKAT!
Daha önce, gördüðümüz kod örneklerinde belirli aralýkta uniform daðýlmýþ rastgele sayýlar için mod operatörünün kullanýldýðýný görmüþ olabilirisiniz ama
bu matematiksel olarak doðru deðil.Eðer önemli deðilse kullanýlabilir.

Eðer program her çalýþtýrýldýðýnda seed farklý olacak þekilde rastgele sayý üretmek istiyorsak 2 yöntem var;

1- (Eðer mümkünse) sayý gerçek rastgele sayý üretiminden alabilir.
2- Tohum deðeri için zamanla deðiþen bir deðer kullanmak. Onun içidne <time.h> dosyasý include edilmeli 
		// srand((unsigned)timme(0))

///////////////////////////////////////////////////////////////////////////////////////////////////

rastgele sayýlar üretmekte mümkün.Bunun için hava durumu, klavyeye basýlma süreleri farký, OS api
varsa ki genelde oluyor, yapýyorlar bunu.

srand içerisine time(0) argümanýný gönderirsek.bu sefer 01 01 1970 ten sonra geçen zamaný gösteriyor
bu da sürekli deðiþiyor.bunu almak mantýklý.

printf("%ld", time(0));->bu 1970 ten bu yana olan zamaný saniye cinsinden verir.

srand(time(0))->bu her seferinde zaman geçeceði için srand e verilen seed deðeri deðiþecek
yani her seferinde farklý sayý zinciri oluþacak.burada uyarý mesajý verir compiler.
time() fonksiyonu long long veya unsigned long olablir.ama srand in parametresi unsigned int
bu yüzden srand fonksiyonunu çaðýrýrken time() fonksiyonunu parametre atarken
explicit olarak türünü deðiþtirmeliyiz. ->srand((unsigned)timme(0))

///////////////////////////////////////////////////////////////////////////////////////////////////

Herhangi bir deðiþkene set etmek istemiyorsak NULL keywordünü kullanabiliriz.
srand((unsigned)NULL) -> geri dönüþ deðeri ayný EPOCHtan geçen saniye sayýsý. ama deðer bir deðiþkene set edilmiyor. Set etmek istersekte
call by reference yaparak yapabiliriz. Ayný zamanda "randomize" idiyomu olarakta biliniyor.
srand((unsigned)&expr)
#define RANDOMIZE() srand((unsigned)time(NULL))
// RANDOMIZE() eðer baþka bir fonksiyonun içinde ise ve o fonksiyon bir saniye içerisinde birden fazla kez(döngü) çaðýrýlýrsa
// RANDOMIZE()'dan gelen deðer birden fazla kez kullanýlýr. 
/*
void print_random_psw(void)
{
	int len = rand() % 8 + 5;
	//randomize(); // burada çaðrýlsaydý her bir saniyede üretilen tüm rand deðerler ayný olacak.çünkü 1sn için seed deðeri
	while (len--)	// ayný kalýyor ve her seferinde tekrardan randomize fonksiyonu çalýþtýrýldýðýnda o zincirin en baþýna atýyor.
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
	printf("Olasýlýk %f", (double)heads_count / NTOSS);
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


	



