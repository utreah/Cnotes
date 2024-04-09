SWITCH CONTROL STATEMENT
switch (int_expr), bir tam sayý ifadesinin farklý deðerlerine göre program akýþýný farklý noktalara yönlendiren bir kontrol deyimidir.
/*
- Switch deyimi if - else if merdiveni yerine kullanýlabilir.Tamamlayýcý bir yapý.
- Daha iyi okunabilirliðe sahip olmasý.
- Derleyici tarafýndan daha iyi optimize edilebiliyor.
********************************************************************/

if (x == 1)
	fa();
else if (x == 2)
	fb();
else if (x == 3)
	fc();

// Bu kodun switch case karþýlýðý þu;

switch (x) {
case 1:
	fa();
case 2:
	fb();
case 3:
	fc();
}
/* 1 - 2 - 3 - 4 - 5 - 6 þeklinde gitmesi zorunluluðu yok. case 1 case 5 case 9 gibi de gidebilir.
Switch-case bodysinde '{}' sentaks açýsýndan bulunmasý zorunlu deðil ama lojik olarak ZORUNLU.
statementlardan sonra break koymazsak koþulu saðladýktan sonraki tüm etiketlere girer.
case 10 / 2  - 1:   buda geçerli.
if-else if'ler için switch case yazýlabilir ama her zaman deðil.
switch'in içerisindeki ifade tam sayý ifadesi olmak zorunda. Reel sayý olursa çalýþmaz.
if(x > 2.1) if içerisindeki ifade if'te çalýþýrken switchte tam sayý olma zorunluluðu var.

*******************************************************************/
x = 2;
switch (x)
	case 1:
		...
	case 2:  break; // break olmasaydý önce case 2 deki kodlarý çalýþtýracak ve daha sonra 3 ve 4. kýsýmlardaki kodlarý da yürütecek.
		...
	case 3:
		...
	case 4:
		...
// break statement zorunlu deðil, break statement olmadan da switch case yapýsý sorunsuz çalýþýr. FAKAT
// break statement koyulmadýðý takdirde bulunduðu case label'ý çalýþtýrýr ve altýnda kalan diðer caseler de çalýþýr.
/* Makrolar ile #define case int_expr'lara isim verilebilir.
 #define FIRST 1 
 #define SECOND 2 gibi.
 */
 switch (x) {
case FIRST:
	fa();
case SECOND:
	fb();
}
/* 
case(keyword)expr: -> case label olarak adlandýrýlýr.
Kaynak kodda bir noktayý belirttikleri için 'label' (etiket) deniyor.

*******************************************************************/

#include <stdio.h>
int main(void)
{
	int n;
	printf("Haftanin kacinci gunu: ");
	scanf("%d", &n);
	switch (n) {
		case 1:
			printf("Pazartesi"); break;
		case 2:
			printf("Sali"); break;
		case 3:
			printf("Carsamba"); break;
		case 6:
			printf("Cumartesi"); break;
		case 4:
			printf("Persembe"); break;
		case 5:
			printf("Cuma"); break;
		case 7:
			printf("Pazar"); break;
	}

}
// Belirli bir sýrada yazýlmalarý için bir kural yok.
// Ýlk ve en çok kullanýlacak olanýn yukarýlarda olmasý, if-else if'te olduðu gibi, tercih edilmeli.

/*******************************************************************/

switch (expr)
{
case 1: foo(); break;
case 2: bar(); break;
case 1: baz(); break;
}
/*
-case labellarý unique(eþsiz) olmak zorunda! 
-Ayný deðeri karþýlayan birden fazla case label olamaz. (compile time'da kontrol edilir)

/*******************************************************************/

// Bazý geçerli case expr: yazým sekilleri

case 'A': statement1; break; // Geçerli, çünkü 'A' nýn deðeri 65'tir.
case 2 + 3 + 5: statement2; break; // Geçerli, constant olduðu için. Fakat case 7+3 gibi baþka bir deðer olursa sentaks hatasý
case '\x1a': statement3; break; // Geçerli, karakter literali de tamsayý sabitidir.

// Bazýlarý ise duruma baðlý.

case SIZE:
case FIRST:
case SECOND:
// Bu case labellarý kullanabilmek için #define makrosu ile SIZE,FIRST ve SECOND isimlerine deðer atayarak kullanýlabilir.

// Geçersiz olanlar
int x = 5;
const int y = 10;
case x: // geçersiz,
case "Ali" // geçersiz, char array olduðu için
case y: // geçersiz, const keyword'ün kullanýlmasý durumu deðiþtirmiyor.
case 4.5: // geçersiz, reel sayýlar olmaz

/*******************************************************************/

// - Her case'ten sonra bir deyim bulunmak zorunda.
	int main(void)
	{
		int n = 5;
		switch (n) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			printf("Pazar"); break;
		}

	}
// Yukarýdaki kod, her case'ten sonra bir deyim bulundurduðu için geçerli bir koddur.
	int main(void)
	{
		int n = 5;
		switch (n) {
		case 1:
		case 2:
			printf("Pazar"); break;
		case 3:
		}
	}
// Yukarýdaki kod, case3'ten sonra herhangi bir deyim bulundurmadýðý için geçersizdir.
	int main(void)
	{
		int n = 5;
		switch (n) {
		case 1:
		case 2:
			printf("Pazar"); break;
		case 3:;
		}
	}
// Yukarýdaki kod, case3'te null statement(;) bulundurduðu için geçerlidir.

/*******************************************************************/
/*
-	default etiketi. default bir keyword.
-	default else if teki else ifadesi ile aynýdýr.
-	default sonda deðil herhangi bir yerde olabilir.

/*******************************************************************/
#include <stdio.h>
	int main(void)
	{
		int n;
		printf("Haftanin kacinci gunu: ");
		scanf("%d", &n);
		switch (n) {
		case 1:
			printf("Pazartesi"); break;
		case 2:
			printf("Sali"); break;
		case 3:
			printf("Carsamba"); break;
		case 6:
			printf("Cumartesi"); break;
		case 4:
			printf("Persembe"); break;
		case 5:
			printf("Cuma"); break;
		case 7:
			printf("Pazar"); break;
		default:
			printf("Gecerli bir gun degil"); break;
		}

	}

/*******************************************************************/
	int x = 1;
switch (x) {
	case 1: case 3: case 4: case 5: case 12321: printf("AYNI SEY"); break;
}
/* caselerin yan yana yazýlmasý ile ayrý yazýlmasý arasýnda bir fark yok.Kodun anlamý deðiþmez

/*******************************************************************/

#include <stdio.h>
int main(void)
{
	int n;
	printf("Haftanin kacinci gunu: ");
	scanf("%d", &n);
	switch (n) {
	case 1:
		printf("Pazartesi"); { break;
	case 2:
		printf("Sali"); break;
	case 3:
		printf("Carsamba"); break;
	case 6:
	}
		printf("Cumartesi"); break;
	case 4:
		printf("Persembe"); break;
	case 5:
		printf("Cuma"); break;
	case 7:
		printf("Pazar"); break;
	default:
		printf("Gecerli bir gun degil"); break;
	}

}
// case'ler sadece belirli bir noktayý belirttiði için aralarýna (sentaksý bozmayacak þekilde) süslü parentez koyulmasý
// hiçibr fark oluþturmaz. Kod çalýþmasý gerektiði þekilde çalýþýr

/*******************************************************************/

// switch deyimlerinin çoðunda case etiketlerinde bulunan sabitler
//	ya birer macro ya da birer enumaration constant olur.
// bazý switch deyimlerinde break statement özellikle kullanýlmaz. Bu duruma popüler olarak fall through denir.


switch (expr)
{
case 1: foo(); //fallthrough:  Eðer switch-case'te normalde break yazýlan yere break deyimi yazýlmadýysa ve bu kasýtlý yapýldýysa "fallthrough" yazarak bunun kasýtlý yapýldýðý bilgisi verilir.
case 2: bar(); break; // fallthrough yazma alýþkanlýðý kazanmak önemli.
case 3: //..		  // buradaki anlamý eðer expr 1 ise foo() ve bar() fonksiyonlarý çalýþtýrýlýyor, eðer 2 ise sadece bar()
case 4: //..
}

switch (expr)
{
case 1: // burada herhangi bir iþ yapýlmadýðý için fallthrough yazmaya gerek yok. Buradaki anlamý daha çok eðer expr 1 veya 2 ise ayný sonuca çýkýyor.
case 2: bar(); break; 
case 3: //..
case 4: //..
}

/*******************************************************************/

switch (x)
{				//dikkat: herhangibir case e girdikten sonra, sonrasýndaki tüm caseler çalýþtýrýlýr.
case 1:		// 1 e girerse 1,11,21 çalýþýr ve break. zaten sadece 21 de yazý var.
case 11:	//	11 e girerse 11 ve 21 çalýþýr ve break, yine printf çalýþýr.
case 21:	// 21 e girerse sadece 21 çalýþýr orda da printf çalýþýr ve break.
	printf("st"); break;
case 2:
case 12:
case 22:
	printf("nd"); break;
case 3:
case 13:
case 23:
	printf("rd"); break;

}

breaklar zorunlu deðil istenirse break hiç yazýlmadanda olur.

Compiler Explorer önemli.https://godbolt.org/
Static kod analizi programlarý

/*******************************************************************/
int isleap(int y)
{
	return (y) % 4 == 0 && ((y) % 400 == 0 || (y) % 100 != 0);
}
int sum = day;

switch (month - 1) {
case 11: sum += 30; //fallthrough   //bilerek yapýldýðý için bu ifade yazýlmýþ
case 10: sum += 31;  //fallthrough	//yani girdiði yerden aþaðý kadar devam edecek çünkü break yok.
case 9: sum += 30;  //fallthrough cpp'ta attribute denen bir sentaks var -> [[fallthrough]]
case 8: sum += 31;  //fallthrough
case 7: sum += 31;  //fallthrough
case 6: sum += 30;  //fallthrough
case 5: sum += 31;  //fallthrough
case 4: sum += 30;  //fallthrough
case 3: sum += 31;  //fallthrough
case 2: sum += 28 + isleap(year); //fallthrough
case 1: sum += 31;

/*******************************************************************/

#include <stdio.h>
int main()
{
	switch (1) {
	printf("bu deyim gecerli ama yurutulmez\n");
	case 1: printf("bir\n"); break;
	case 2: printf("iki\n"); break;
}

/*******************************************************************/

// case labellarýndan önce deðiþken bildirimi yapýlabilir.

	switch (expr) {
		int x = 5; // geçerli
	case 1: break; 
	case 2: break;
	}

/*******************************************************************/
	int a = 1;
	switch (a) {
	case 1:
		int x;		//C’de geçersiz C++ ta geçerli.Bir sonraki case de block tan çýktýðý için garbage value.
		x = 10;		// undefined behavior.
		//
		break;
	case 2: ++x; break;
		///
	}

/*******************************************************************/

ÖNEMLÝ!!!!!!!!!!!!
case ler sýralý bir þekilde yapýldýðýnda(büyükten küçüðe ya da küçükten büyüðe)
daha low levelda C bir jump table oluþturuyor ve istenen hedefe direkt gidiyor.
bu durum else if merdiveninde karþýlýðýný oluþturamayabiliyor.

/*******************************************************************/
int main(void) { // MÜLAKAT: mülakatta bu tarz sorulabiliyormuþ.
	int i, k;
	for (i = 0; i < 5; i++)
		for (k = 0; k < 5; ++k)
			; // buradaki null statementin etkisi yok

printf("%d %d", i, k); // çýktý 5 ve 5 olacak
}