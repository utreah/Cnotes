#include <stdio.h>
// T�R D�N��T�RME OPERAT�R� �LE YAPILAN �FADELER RVALUE EXPRESSIONDUR.
/*-------------------------------------------POINTERS(ADRES)--------------------------------------*/
/*
Adresler sadece asm, makine kodu, hardware �zerinde de�il direkt olarak yaz�l�m katman�nda da tutuluyor(C/CPP gibi dillerde).
pointer ==> address


Adresler ikiye ayr�l�yor
1-) Nesne adresleri(Object pointers) -> �u anda bunu inceleyece�iz
2-) Fonksiyon adresleri -> 1.5 ay sonra bu

-Her bir ifadenin t�r� var. ==> int x; gibi 
-Adres anlam�na gelen ifadelerin de bir t�r� var. ==> int* x;
G�sterim �ekilleri;
T* idf; => int* x;
		   double* dx; float* fx;
		   int * x; // int *x;
T�rler de�i�ti�inde adreslerinin t�r� de de�i�ir.
Her adres ayr� bir t�r.
int t�rden bir ifadenin adresi int * d�r.
	int *x -> int t�rden de�i�kenin adresi
	double *x -> double t�rden dei�ken�n adresi



SENTAKS
int t�rden bir de�i�kenin adresini tutmak i�in ==> int* ptr; ismi ptr olan bir pointer de�i�ken tan�mlad�k.
														ptr'nin t�r� [pointer to int] veya [int*] diyebiliriz

Bir de�i�keninin tan�m�nda kullan�lan tokenlara "declarator" denir.
�fadeler de kullan�lan tokenlara ise "operator" denir.

int main(void)
{
	int a[4]; ==> buradaki [] declarator
	a[3] ==> burada [] ise bir operat�r.
}


Pointerlar� initialize edebiliriz veya initialize etmeden de b�rakabiliriz.
int* ptr = 0;
int* ptr2;
int x;
ptr2 = &x;

//////////////////////////////////////////////////////////////////////////////////////////////////
-Pointerler global bir de�i�ken olabilirler(dolay�s�yla static te olabilirler)
-Otomatik �m�rl� yerel bir de�i�ken olabilirler double *dp;
-Statik �m�rl� yerel bir de�i�ken olabilirler. static int iptr;
-Bir fonksiyonun parametresi olabilirler. int func(int* p, int size);
-Globalde tan�mlanan pointer to type t�rleri ilk de�er atamas� yap�lmaz ise 'nullptr' olma garantisi vard�r.(static te ayn�)
-Localde ise garbage value ile ba�lar.

///////////////////////////////////////////////////////////////////////////////////////////////////
En �ok parametre de�i�keni olarak kullan�l�yorlar.

E�er 3 tane p1,p2,p3 isimli pointer to int t�r�nden 3 adet de�i�ken tan�mlamak isteseydik
int* p1, p2, p3; �eklinde tan�mlarsak YANLI�!
int* p1; int p2; int p3; derleyici bu �ekilde g�r�r.
Asterisk, address of, operat�rleri yaln�zca kendisinden sonra gelen de�i�keni etkiler. Bu y�zden 3 tane pointer to int tan�malamak istersek;
int* p1, *p2, *p3; �eklinde yaz�l�rsa istenilen �ekilde olur.

///////////////////////////////////////////////////////////////////////////////////////////////////
	a�a��daki adres t�rlerinin hepsi ayn� boyutta yer kaplar.
	int *
	double *
	char *
	bunlar sizeof(int *) sizeof(double *) sizeof(char *) sizeof(short *) .... hepsi ayn� boyuttad�r.

//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
	 POINTER OPERAT�RLER�
	 -& address of							adres operat�r�
	 -* dereference							i�erik operat�r�
	 -[] index/subscript operat�r			indeks operat�r�
	 -'->' member selection					ok operat�r�




*/

//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*						ADDRESS/& OPERATOR (Unary prefix)
* �ncelik'de �ncelik s�ras� 2. -> unary bir operat�r yani tek operand alan, Sa�dan sola(associativity) olan bir operat�r.
* & binary infix olursa bitsel ve anlam�ndad�r unary prefix ise adres operat�r�.
* Operand� oldu�u ifade l-value expr olmak zorunda. Ortaya ��kan de�er ise rvalue exprdir. 
* Ge�erli durumlar�;
** int x; int a[5]; 
- &x; -> ge�erli ��nk� x bir lvalue expression(t�m de�i�kenlerin adresi vard�r bu y�zden hepsi lvalue)
- &+x; -> sentaks hatas�, i�aret operat�r� ile olu�turulan ifadeler rvalue ifadelerdir.
- &(x + 3); -> aritmetik operat�rlerin olu�turdu�u ifadeler rvalue ifadelerdir.
- &x[3] ->2 adet operat�r vard�r ve legal, �ncelik s�ras�na g�re indeks operat�r� daha �nceliklidir. -> &(x[3]);
- &235 -> ge�erli de�il, 235 bir constant ifade ve rvalue exprdir.
- &x ifadesinin t�r� -> int* (line: 90)
- int z = 10; int* ptr; z'nin t�r� int, ptr'nin t�r� int*;
double dval = 3.;

T�r� pointer olan bir ifade;
a- pointer de�i�kenin olu�turdu�u ifade olabilir
b- adres operat�r� ile olu�turulmu bir ifade olabilir
// z != &z (int // int*)
// ptr == &z (int* // int*)
// &dval != ptr (double* // int*)
// &x != &dval (int* // double*)

Bir type to pointera;
a- address of operat�r� ile olu�turulmu� bir ifade ile ilk de�er  atayabilirim int* iptr = &x; // iptr'nin de�eri x'in adresi
																					iptr points to x(ptr x i g�steriyor)
b- address of operat�r� ile de�er atamas� yapabilirim. iptr = &y; // iptr'nin de�eri y'nin adresi
														iptr points to y(ptr y yi g�steriyor)

-Bir pointerin de�i�kenin bir de�i�kenin adresini tutmas� i�in o de�i�kenin adresine ihtiya� duyuyor. 

//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
int main(void)
{
	int x = 10;
	int y = 45;
	// E�er a�a��daki yap�lar CPP'de olsayd�, adres t�r�nden bir de�i�kene 
	// ilk de�er olarak adres t�r�nden bir de�er atanmad���nda SENTAKS hatas� olur.
	// C dilinde ise, derleyiciler uyar� verse de, int* ile int(veya di�er t�r / t�r*) aras�nda �rt�l� d�n���m var.
	

	// Yani a�a��daki kodlar legal olsa da pointer de�i�kenlera asla ve asla adres olmayan bir de�eri ne ilk de�er olarak
	// ne de atama olarak kullanmayaca��z.
	//int* ptr = x; 
	//ptr = 3789;
	//ptr = y;
	/*---------------------------------------------------------------------------------------------------------------*//*
	double dp;
	dp =  &x; // Farkl� adres t�rleri aras�nda �rt�l� d�n���m var. �al���r ama legal de�il.

	/*
	a-Asla ve asla adres olmayan bir ifadeyi atayamay�z.
	b-Bir pointer de�i�kene asla ve asla farkl� bir pointer t�r�nden atama veya ilk de�er verme yap�lmaz(from double* to int*)
	*//*
	int x2 = 10;
	int y2 = 25;
	int* p1 = &x2;
	int* p2 = &y2;
	p2 = p1; // burada p2 ve p1 ikisi de adresi olan bir de�erle initialize edildi�i ve ikisi de int* oldu�u i�in
			// hem p2 hem p1 x'in adresini g�steriyor.
	/*
	&x -> x'in adresi
	p1 x'in adresi (line 143'ten sonra y'de x'in adresi)
	p2 y'nin adresi
	&p1 -> p1	 de�i�keninin adresi.


}*/


/*
Pointer = i�aret eden
Pointee = i�aret edilen.

1:30:00'dan sonra izle
*/

