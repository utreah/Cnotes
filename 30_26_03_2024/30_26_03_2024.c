#include <stdio.h>
// TÜR DÖNÜÞTÜRME OPERATÖRÜ ÝLE YAPILAN ÝFADELER RVALUE EXPRESSIONDUR.
/*-------------------------------------------POINTERS(ADRES)--------------------------------------*/
/*
Adresler sadece asm, makine kodu, hardware üzerinde deðil direkt olarak yazýlým katmanýnda da tutuluyor(C/CPP gibi dillerde).
pointer ==> address


Adresler ikiye ayrýlýyor
1-) Nesne adresleri(Object pointers) -> þu anda bunu inceleyeceðiz
2-) Fonksiyon adresleri -> 1.5 ay sonra bu

-Her bir ifadenin türü var. ==> int x; gibi 
-Adres anlamýna gelen ifadelerin de bir türü var. ==> int* x;
Gösterim þekilleri;
T* idf; => int* x;
		   double* dx; float* fx;
		   int * x; // int *x;
Türler deðiþtiðinde adreslerinin türü de deðiþir.
Her adres ayrý bir tür.
int türden bir ifadenin adresi int * dýr.
	int *x -> int türden deðiþkenin adresi
	double *x -> double türden deiþkenþn adresi



SENTAKS
int türden bir deðiþkenin adresini tutmak için ==> int* ptr; ismi ptr olan bir pointer deðiþken tanýmladýk.
														ptr'nin türü [pointer to int] veya [int*] diyebiliriz

Bir deðiþkeninin tanýmýnda kullanýlan tokenlara "declarator" denir.
Ýfadeler de kullanýlan tokenlara ise "operator" denir.

int main(void)
{
	int a[4]; ==> buradaki [] declarator
	a[3] ==> burada [] ise bir operatör.
}


Pointerlarý initialize edebiliriz veya initialize etmeden de býrakabiliriz.
int* ptr = 0;
int* ptr2;
int x;
ptr2 = &x;

//////////////////////////////////////////////////////////////////////////////////////////////////
-Pointerler global bir deðiþken olabilirler(dolayýsýyla static te olabilirler)
-Otomatik ömürlü yerel bir deðiþken olabilirler double *dp;
-Statik ömürlü yerel bir deðiþken olabilirler. static int iptr;
-Bir fonksiyonun parametresi olabilirler. int func(int* p, int size);
-Globalde tanýmlanan pointer to type türleri ilk deðer atamasý yapýlmaz ise 'nullptr' olma garantisi vardýr.(static te ayný)
-Localde ise garbage value ile baþlar.

///////////////////////////////////////////////////////////////////////////////////////////////////
En çok parametre deðiþkeni olarak kullanýlýyorlar.

Eðer 3 tane p1,p2,p3 isimli pointer to int türünden 3 adet deðiþken tanýmlamak isteseydik
int* p1, p2, p3; þeklinde tanýmlarsak YANLIÞ!
int* p1; int p2; int p3; derleyici bu þekilde görür.
Asterisk, address of, operatörleri yalnýzca kendisinden sonra gelen deðiþkeni etkiler. Bu yüzden 3 tane pointer to int tanýmalamak istersek;
int* p1, *p2, *p3; þeklinde yazýlýrsa istenilen þekilde olur.

///////////////////////////////////////////////////////////////////////////////////////////////////
	aþaðýdaki adres türlerinin hepsi ayný boyutta yer kaplar.
	int *
	double *
	char *
	bunlar sizeof(int *) sizeof(double *) sizeof(char *) sizeof(short *) .... hepsi ayný boyuttadýr.

//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
	 POINTER OPERATÖRLERÝ
	 -& address of							adres operatörü
	 -* dereference							içerik operatörü
	 -[] index/subscript operatör			indeks operatörü
	 -'->' member selection					ok operatörü




*/

//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*						ADDRESS/& OPERATOR (Unary prefix)
* Öncelik'de öncelik sýrasý 2. -> unary bir operatör yani tek operand alan, Saðdan sola(associativity) olan bir operatör.
* & binary infix olursa bitsel ve anlamýndadýr unary prefix ise adres operatörü.
* Operandý olduðu ifade l-value expr olmak zorunda. Ortaya çýkan deðer ise rvalue exprdir. 
* Geçerli durumlarý;
** int x; int a[5]; 
- &x; -> geçerli çünkü x bir lvalue expression(tüm deðiþkenlerin adresi vardýr bu yüzden hepsi lvalue)
- &+x; -> sentaks hatasý, iþaret operatörü ile oluþturulan ifadeler rvalue ifadelerdir.
- &(x + 3); -> aritmetik operatörlerin oluþturduðu ifadeler rvalue ifadelerdir.
- &x[3] ->2 adet operatör vardýr ve legal, öncelik sýrasýna göre indeks operatörü daha önceliklidir. -> &(x[3]);
- &235 -> geçerli deðil, 235 bir constant ifade ve rvalue exprdir.
- &x ifadesinin türü -> int* (line: 90)
- int z = 10; int* ptr; z'nin türü int, ptr'nin türü int*;
double dval = 3.;

Türü pointer olan bir ifade;
a- pointer deðiþkenin oluþturduðu ifade olabilir
b- adres operatörü ile oluþturulmu bir ifade olabilir
// z != &z (int // int*)
// ptr == &z (int* // int*)
// &dval != ptr (double* // int*)
// &x != &dval (int* // double*)

Bir type to pointera;
a- address of operatörü ile oluþturulmuþ bir ifade ile ilk deðer  atayabilirim int* iptr = &x; // iptr'nin deðeri x'in adresi
																					iptr points to x(ptr x i gösteriyor)
b- address of operatörü ile deðer atamasý yapabilirim. iptr = &y; // iptr'nin deðeri y'nin adresi
														iptr points to y(ptr y yi gösteriyor)

-Bir pointerin deðiþkenin bir deðiþkenin adresini tutmasý için o deðiþkenin adresine ihtiyaç duyuyor. 

//////////////////////////////////////////////////////////////////////////////////////////////////*/
/*
int main(void)
{
	int x = 10;
	int y = 45;
	// Eðer aþaðýdaki yapýlar CPP'de olsaydý, adres türünden bir deðiþkene 
	// ilk deðer olarak adres türünden bir deðer atanmadýðýnda SENTAKS hatasý olur.
	// C dilinde ise, derleyiciler uyarý verse de, int* ile int(veya diðer tür / tür*) arasýnda örtülü dönüþüm var.
	

	// Yani aþaðýdaki kodlar legal olsa da pointer deðiþkenlera asla ve asla adres olmayan bir deðeri ne ilk deðer olarak
	// ne de atama olarak kullanmayacaðýz.
	//int* ptr = x; 
	//ptr = 3789;
	//ptr = y;
	/*---------------------------------------------------------------------------------------------------------------*//*
	double dp;
	dp =  &x; // Farklý adres türleri arasýnda örtülü dönüþüm var. Çalýþýr ama legal deðil.

	/*
	a-Asla ve asla adres olmayan bir ifadeyi atayamayýz.
	b-Bir pointer deðiþkene asla ve asla farklý bir pointer türünden atama veya ilk deðer verme yapýlmaz(from double* to int*)
	*//*
	int x2 = 10;
	int y2 = 25;
	int* p1 = &x2;
	int* p2 = &y2;
	p2 = p1; // burada p2 ve p1 ikisi de adresi olan bir deðerle initialize edildiði ve ikisi de int* olduðu için
			// hem p2 hem p1 x'in adresini gösteriyor.
	/*
	&x -> x'in adresi
	p1 x'in adresi (line 143'ten sonra y'de x'in adresi)
	p2 y'nin adresi
	&p1 -> p1	 deðiþkeninin adresi.


}*/


/*
Pointer = iþaret eden
Pointee = iþaret edilen.

1:30:00'dan sonra izle
*/

