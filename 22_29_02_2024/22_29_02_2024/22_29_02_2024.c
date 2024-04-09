SWITCH CONTROL STATEMENT
switch (int_expr), bir tam say� ifadesinin farkl� de�erlerine g�re program ak���n� farkl� noktalara y�nlendiren bir kontrol deyimidir.
/*
- Switch deyimi if - else if merdiveni yerine kullan�labilir.Tamamlay�c� bir yap�.
- Daha iyi okunabilirli�e sahip olmas�.
- Derleyici taraf�ndan daha iyi optimize edilebiliyor.
********************************************************************/

if (x == 1)
	fa();
else if (x == 2)
	fb();
else if (x == 3)
	fc();

// Bu kodun switch case kar��l��� �u;

switch (x) {
case 1:
	fa();
case 2:
	fb();
case 3:
	fc();
}
/* 1 - 2 - 3 - 4 - 5 - 6 �eklinde gitmesi zorunlulu�u yok. case 1 case 5 case 9 gibi de gidebilir.
Switch-case bodysinde '{}' sentaks a��s�ndan bulunmas� zorunlu de�il ama lojik olarak ZORUNLU.
statementlardan sonra break koymazsak ko�ulu sa�lad�ktan sonraki t�m etiketlere girer.
case 10 / 2  - 1:   buda ge�erli.
if-else if'ler i�in switch case yaz�labilir ama her zaman de�il.
switch'in i�erisindeki ifade tam say� ifadesi olmak zorunda. Reel say� olursa �al��maz.
if(x > 2.1) if i�erisindeki ifade if'te �al���rken switchte tam say� olma zorunlulu�u var.

*******************************************************************/
x = 2;
switch (x)
	case 1:
		...
	case 2:  break; // break olmasayd� �nce case 2 deki kodlar� �al��t�racak ve daha sonra 3 ve 4. k�s�mlardaki kodlar� da y�r�tecek.
		...
	case 3:
		...
	case 4:
		...
// break statement zorunlu de�il, break statement olmadan da switch case yap�s� sorunsuz �al���r. FAKAT
// break statement koyulmad��� takdirde bulundu�u case label'� �al��t�r�r ve alt�nda kalan di�er caseler de �al���r.
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
case(keyword)expr: -> case label olarak adland�r�l�r.
Kaynak kodda bir noktay� belirttikleri i�in 'label' (etiket) deniyor.

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
// Belirli bir s�rada yaz�lmalar� i�in bir kural yok.
// �lk ve en �ok kullan�lacak olan�n yukar�larda olmas�, if-else if'te oldu�u gibi, tercih edilmeli.

/*******************************************************************/

switch (expr)
{
case 1: foo(); break;
case 2: bar(); break;
case 1: baz(); break;
}
/*
-case labellar� unique(e�siz) olmak zorunda! 
-Ayn� de�eri kar��layan birden fazla case label olamaz. (compile time'da kontrol edilir)

/*******************************************************************/

// Baz� ge�erli case expr: yaz�m sekilleri

case 'A': statement1; break; // Ge�erli, ��nk� 'A' n�n de�eri 65'tir.
case 2 + 3 + 5: statement2; break; // Ge�erli, constant oldu�u i�in. Fakat case 7+3 gibi ba�ka bir de�er olursa sentaks hatas�
case '\x1a': statement3; break; // Ge�erli, karakter literali de tamsay� sabitidir.

// Baz�lar� ise duruma ba�l�.

case SIZE:
case FIRST:
case SECOND:
// Bu case labellar� kullanabilmek i�in #define makrosu ile SIZE,FIRST ve SECOND isimlerine de�er atayarak kullan�labilir.

// Ge�ersiz olanlar
int x = 5;
const int y = 10;
case x: // ge�ersiz,
case "Ali" // ge�ersiz, char array oldu�u i�in
case y: // ge�ersiz, const keyword'�n kullan�lmas� durumu de�i�tirmiyor.
case 4.5: // ge�ersiz, reel say�lar olmaz

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
// Yukar�daki kod, her case'ten sonra bir deyim bulundurdu�u i�in ge�erli bir koddur.
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
// Yukar�daki kod, case3'ten sonra herhangi bir deyim bulundurmad��� i�in ge�ersizdir.
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
// Yukar�daki kod, case3'te null statement(;) bulundurdu�u i�in ge�erlidir.

/*******************************************************************/
/*
-	default etiketi. default bir keyword.
-	default else if teki else ifadesi ile ayn�d�r.
-	default sonda de�il herhangi bir yerde olabilir.

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
/* caselerin yan yana yaz�lmas� ile ayr� yaz�lmas� aras�nda bir fark yok.Kodun anlam� de�i�mez

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
// case'ler sadece belirli bir noktay� belirtti�i i�in aralar�na (sentaks� bozmayacak �ekilde) s�sl� parentez koyulmas�
// hi�ibr fark olu�turmaz. Kod �al��mas� gerekti�i �ekilde �al���r

/*******************************************************************/

// switch deyimlerinin �o�unda case etiketlerinde bulunan sabitler
//	ya birer macro ya da birer enumaration constant olur.
// baz� switch deyimlerinde break statement �zellikle kullan�lmaz. Bu duruma pop�ler olarak fall through denir.


switch (expr)
{
case 1: foo(); //fallthrough:  E�er switch-case'te normalde break yaz�lan yere break deyimi yaz�lmad�ysa ve bu kas�tl� yap�ld�ysa "fallthrough" yazarak bunun kas�tl� yap�ld��� bilgisi verilir.
case 2: bar(); break; // fallthrough yazma al��kanl��� kazanmak �nemli.
case 3: //..		  // buradaki anlam� e�er expr 1 ise foo() ve bar() fonksiyonlar� �al��t�r�l�yor, e�er 2 ise sadece bar()
case 4: //..
}

switch (expr)
{
case 1: // burada herhangi bir i� yap�lmad��� i�in fallthrough yazmaya gerek yok. Buradaki anlam� daha �ok e�er expr 1 veya 2 ise ayn� sonuca ��k�yor.
case 2: bar(); break; 
case 3: //..
case 4: //..
}

/*******************************************************************/

switch (x)
{				//dikkat: herhangibir case e girdikten sonra, sonras�ndaki t�m caseler �al��t�r�l�r.
case 1:		// 1 e girerse 1,11,21 �al���r ve break. zaten sadece 21 de yaz� var.
case 11:	//	11 e girerse 11 ve 21 �al���r ve break, yine printf �al���r.
case 21:	// 21 e girerse sadece 21 �al���r orda da printf �al���r ve break.
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

breaklar zorunlu de�il istenirse break hi� yaz�lmadanda olur.

Compiler Explorer �nemli.https://godbolt.org/
Static kod analizi programlar�

/*******************************************************************/
int isleap(int y)
{
	return (y) % 4 == 0 && ((y) % 400 == 0 || (y) % 100 != 0);
}
int sum = day;

switch (month - 1) {
case 11: sum += 30; //fallthrough   //bilerek yap�ld��� i�in bu ifade yaz�lm��
case 10: sum += 31;  //fallthrough	//yani girdi�i yerden a�a�� kadar devam edecek ��nk� break yok.
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

// case labellar�ndan �nce de�i�ken bildirimi yap�labilir.

	switch (expr) {
		int x = 5; // ge�erli
	case 1: break; 
	case 2: break;
	}

/*******************************************************************/
	int a = 1;
	switch (a) {
	case 1:
		int x;		//C�de ge�ersiz C++ ta ge�erli.Bir sonraki case de block tan ��kt��� i�in garbage value.
		x = 10;		// undefined behavior.
		//
		break;
	case 2: ++x; break;
		///
	}

/*******************************************************************/

�NEML�!!!!!!!!!!!!
case ler s�ral� bir �ekilde yap�ld���nda(b�y�kten k����e ya da k���kten b�y��e)
daha low levelda C bir jump table olu�turuyor ve istenen hedefe direkt gidiyor.
bu durum else if merdiveninde kar��l���n� olu�turamayabiliyor.

/*******************************************************************/
int main(void) { // M�LAKAT: m�lakatta bu tarz sorulabiliyormu�.
	int i, k;
	for (i = 0; i < 5; i++)
		for (k = 0; k < 5; ++k)
			; // buradaki null statementin etkisi yok

printf("%d %d", i, k); // ��kt� 5 ve 5 olacak
}