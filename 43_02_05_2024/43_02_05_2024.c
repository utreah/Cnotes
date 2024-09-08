Bir fonksiyonun davran���n� o fonksiyona �a�r� yapan kodun de�i�tirebilmesini sa�l�yor.

�rne�in, bir function pointer de�i�keni alan fonksiyon olsun.

void print_char(int (*fp)(int))
{
	for (int i = 0; i < 128; i++)
		if (fp(i))
			printf("%c", i;);
}
print_char adl� fonksiyona yollad���m�z bir fonksiyonun adresi ile for d�ng�s� i�erisinde
	yap�lan i�lemi de�i�tirebiliyoruz.;
print_char(&isupper);
print_char(&isdigit);
print_char(&islower);

Bu fonksiyonlar�n adreslerini yollayarak istedi�imiz i�lemi yapt�rabiliyoruz.

//////////////////////////////////
int foo(int x) {
	printf("Foo cagrildi, x = %d", x);
	return x * x;
}
int main(void) {

	int (*fp)(int) = foo;
	int retval = fp(45); // array decay gibi, fp'yi fonksiyon �a�r� operat�r�n�n operand� yaparak kullan�yorum..
							// fp(45) == (*fp)(45), fp'yi i�erik operat�r�n�n operand� yaparak fp'nin g�sterdi�i fonksiyonu g�rebiliriz
								// i�erik operat�r�n�n �nceli�i function call operator�nden daha d���k oldu�undan dolay� �ncelik parantezi
									// i�erisine al�yoruz

	// retval = fp(45)
	// retval = (*fp)(45) bu �ekilde kullan�lmas�n�n hi�bir avantaj� yok. Kullan�lmas�n�n sebebi function pointer oldu�unu vurgulamak i�in.

	/////////////////////
	int (*fp2)(int) = &foo;
	(&foo)(12); // Legal
	(*foo)(12); // Legal
	fp2(15); // Legal
	(*fp2)(15); // Legal
	(&fp2)(15); // Illegal -> ��nk� fp2 bir pointer ve biz bunun adresini ald���m�zda asl�nda ** �eklinde oluyor. 
	


}

/////////////////////////////////////////////

// foo ve bar herhangi bir kodda iki farkl� fonksiyon olsun

//Alttaki �rnekler ayn� fonksiyon de�il, �rnek i�in
foo(bar()); // Burada bar adl� fonksiyon �a�r�l�yor ve geri d�n�� de�eri foo fonksiyonunda parametre de�eri olarak kullan�l�yor
foo(bar); // Burada ise bar adl� fonksiyonun ADRES� foo'ya parametre de�eri olarak kullan�l�yor. �kisi FARKLI
foo(&bar); // �stteki ile ayn�


/////////////////////////////////////////////

			// Function pointerla TYPEDEF kullanmak
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int foo(const char*, const char*);
int bar(const char*, const char*);
int baz(const char*, const char*);
void f1(int (*fp)(const char*, const char*)); // f1, parametre de�i�keni function pointer olan, geri d�n�� de�eri olmayan bir fonksiyon
void f2(int (*fp)(const char*, const char*), int (*fp2)(const char*, const char*)); // f2, parametre de�i�kenleri function pointer olan, geri d�n�� de�eri olmayan bir fonksiyon
int	(*f3(int (*fp)(const char*, const char*, int (*fp2)(const char*, const char*)))(const char*, const char*);
typedef int (*FPTR)(const char*, const char*);
int main(void) {
	int (*fp)(const char*, const char*) = &strcmp; // bu  pointer to function pointer
	int (**fpp)(const char*, const char*) = &fp; // bu ise pointer to function pointer to function pointer

	///////////////////////
	int (*fp)(const char*, const char*) = foo;

	// Fonksiyonlar�n adresini tutan bir function pointer array yazmak i�in �u ad�mlar� izliyoruz.
		// ayn� dizi olu�turur gibi fonksiyonlar�n adreslerini yaz�yoruz.
			// {&bar, &foo, &baz} daha sonra ise fonksiyonlar�n parametre de�i�kenlerini tutabilen function pointer� yaz�yoruz
				// int (*fpar)(const char*, const char*) son olarakta tutaca�� eleman say�s�n� index operat�r� ile beraber
					// function pointer�n yan�na yaz�yoruz
	int (*fpar[3])(const char*, const char*) = { &bar, &foo, &baz }; // bu 3 fonksiyonun adresini tutan bir function pointer array olu�turduk

	/*
	Geri d�n�� de�eri function pointer olan, parametreleri function pointer olan bir fonksiyon nas�l yaz�l�r?
		�nce fonksiyonun ad� yaz�l�r
			-func
		Daha sonra fonksiyon ad�n�n ba��na asterisk atomu koyulur
			-*func
		Fonksiyon ad�n�n ya�na fonksiyonun ili�kili oldu�u parametreler yaz�l�r
			-*func(int, double)
		Bir daha paranteze al�n�r
			-(*func(int, double))
		Fonksiyonun ili�kili oldu�u geri d�n�� de�eri yaz�l�r
			-int (*func(int, double))
		Function pointerin ili�kili oldu�u parametreler yaz�l�r
			-int (*func(int, double))(const char*, const char*)
	*/
	int ergo(const char*, const char*); // ->bu bir fonksiyon;
	int (*func(void))(const char*, const char*) {
		return ergo; // veya return &ergo. 
				// func fonksiyonu ergo'yu return edebilir.
	}
	// Yukar�da yapt���m�z t�m �rnekler a��r� karma��k ve anlamas� zor.
		// Kodlama hatas� riskini azaltmak, anlamay� kolayla�t�rmak i�in t�r-e�(typedef alias) kullan�yoruz
	/*	typedef nas�l kullan�yoruz ?
		-E�-t�r ismi kullan�lacak t�rden bir de�i�ken tan�mla
			int (*f)(const char*, const char*);
		-Ba��na typedef getir
			typedef int (*f)(const char*, const char*);
		-De�i�kenin ad�n� yapmak istedi�in e�-t�r ismi ile de�i�tir	
			typedef int (*FPTR)(const char*, const char*);
	*/ 

	FPTR fp = foo;
	FPTR* fpp = &fp;
	FPTR fpar[] = { foo, bar, baz };
	// FPTR typedef kullanraak f1,f2 ve f3 fonksiyonlar�n� nas�l yazabiliriz?
	void f1(FPTR fp);
	void f2(FPTR fp1, FPTR fp2);
	FPTR f3(FPTR fp1, FPTR fp2);
}	
////////////////////////////////////////////////////////////
// �retimde kullan�labilecek baz� �rnekler - QSORT
/*Callback, bir fonksiyona bir fonksiyonu arg�man olarak olarak g�nderiyoruz, �a��rd���m
fonksiyonun benim g�nderdi�im fonksiyonu �a��rmas�n� isteyece�iz.

yani fonksiyonu ba�ka bir fonksiyona �a��rtaca��z.

bir fonksiyona arg�man olarak fonksiyon g�ndererek yap�yor bu i�i.
�a��rd���m fonksiyon benim g�nderdi�imi �a��r�yor.*/

// q sort t�rden ba��ms�z �al���yor (void*)


void qsort(void* vpa, size_t size, size_t sz, int (*fcomp)(const void*, const void*)) {
	// vpa = S�ralama i�leminin yap�laca�� dizinin adres�
	// size = dizinin boyutu
	// sz = s�ralama yap�lan eleman�n boyutu (int, double 4byte gibi d���n)
	// fcomp = Bu ise fonksiyon pointer. Adresini ald��� fonksiyonu kullanarak kar��la�t�rma yapacak. Yani bu parametreye strcmp'nin
		// adresini g�nderebilirim.

}
//////////////////////////////////////////////////
#include <stdlib.h>
#include <C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h>
#include <stdio.h>
#define SIZE 100
int icmp(const void* vp1, const void* vp2) {
	if (*(const int*)vp1 > *(const int*)vp2)
		return 1;
	else if (*(const int*)vp1 < *(const int*)vp2)
		return -1;
	return 0;
}

int icmp2(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2; // Bu yaz�m �ekli hem do�ru hem de yanl��. Yap�lan i�lem tam say� oldu�u s�rece
		// do�ru sonu� elde ederiz fakat TA�MA riski var. E�er s�ralamas�n� yapt���m�z dizinin elemanlar�n�n de�erinin ta�ma riski
			// olu�turmayaca�� garantisi var ise bu �ekilde de yaz�labilir.
}
int main(void) {
	int ar[SIZE];
	randomize();
	set_array_random(ar, SIZE);
	print_array(ar, SIZE);

	qsort(ar, SIZE, sizeof(*ar), &icmp);
	print_array(ar, SIZE);

}
double dcmp(const void* vp1, const void vp2) {
	if (*(const double*)vp1 > *(const double*)vp2)
		return 1;
	else if (*(const double*)vp1 > *(const double*)vp2)
		return -1;
	return 0;
	// return (*(const double*)vp1 > *(const double*)vp2) ? 1 : (*(const double*)vp1 < *(const double*)vp2) ? -1 : 0;
}
int main(void) {
	int dAr[SIZE];
	randomize();
	for (int i = 0; i < SIZE; i++)
		dAr[i] = (double)rand() * 1.76;

	qsort(dAr, SIZE, sizeof(*dAr), dcmp); // sizeof(*dAr) yerine sizeof(dAr[0]) veya sizeof(double) yazabilirim.

}
// �DEV - Bubblesort algoritmas�n� "GENERIC" olarak implemente eden ismi gbsort fonksiyonu tan�mlay�n�z.


void gbsort(void* vpa, size_t size, size_t sz, int (*fp)(const void*, const void*))
{
	char* p = (char*)vpa;
	for (int i = 0; i < size - 1; i++)
		for (int k = 0; k < size - 1 - i; k++) 
			// E�er dizinin k indisli eleman� dizinin k + 1 indisli eleman�ndan b�y�k ise
				// dizinin k indisli eleman� ile k + 1 i indisli eleman� ile takasla
			if (fp(p + k * sz, p + (k + 1) * sz) > 0) 
				gswap(p + k * sz, p + (k + 1) * sz, sz); // bunun kodunu daha �nce yazm��t�k. Tekrar yazman�n anlam� yok
}
int main(void) { // �DEV
	char* names[] = {
	"Ali, Y�lmaz",
	"Ay�e, Demir",
	"Mehmet, Kaya",
	"Fatma, �elik",
	"Ahmet, Yurt",
	"Elif, Arslan",
	"Mustafa, �zt�rk",
	"Zeynep, Polat",
	"Hasan, Ayd�n",
	"Emine, Kara",
	"H�seyin, G�ne�",
	"Meryem, Ar�",
	"Osman, Ko�",
	"Seda, Erkan",
	"�smail, �etin",
	"H�lya, Tekin",
	"Cemal, G�rkem",
	"B��ra, �ak�r",
	"Yusuf, Karaaslan",
	"Derya, Yurt"
	};
	// bu isimleri b�y�kten k����e gbsort kullanarak s�ralayaca��z. strcmp kullanarak.
		// gbsort'taki fonksiyona callback olarak yaz�lar�n tutuldu�u dizinin adresi g�nderilecek. Bunu d���nerek yaz kodu 
	
}

//////////////////////////////////////////////////////////////////
// bsearch  yani binary search. Standart k�t�phanenin fonksiyonu.S�ral� dizide arama yap�yor.Kodunu yazm��t�k.
void* (const void* pkey, const void vpa, size_t size, size_t sz, int(*fp)(const void*, const void*));
/*
	-pkey = aranacak de�erin adresi
	-vpa = aranacak dizinin adresi
	-size = arama yap�lacak dizinin boyutu
	-sz = arama yap�lan dizinin bir eleman�n�n boyutu
	-(*fp) = arama fonksiyonunun adresi
	*/
int main()
{
	int a[SIZE];
	int ival;

	randomize();
	set_random_array(a, SIZE);
	qsort(a, SIZE, sizeof(*a), &icmp);
	print_array(a, SIZE);
	printf("aranacak degeri girin\n");
	(void)scanf("%d", &ival);

	int* ptr = (int*)bsearch(&ival, a, SIZE, sizeof(int), &icmp);

	if (ptr)
		printf("Bulundu. Dizinin %d indisli elemani\n", ptr - a);
	else
		printf("Bulunamadi\n");
}

////////////////////////////////////////////
int (*fp)(int) == NULL;
fonksiyon pointerlar�na NULL pointer atanabilir.
////////////////////////////////////////////

FUNCTION POINTER ARRAYS

---------------------- -

int* p[10] demek int* ptr den 10 tane var demek.

Bunu uyarlarsak

int (*fptr[10])(int);  typedef ile de tan�mlanabilir bu daha k�sa olur hatta.

#define		SIZE		100


int f1(int x)
{
	printf("f1 cagrildi x = %d\n", x);
	return x * x;
}

int f2(int x)
{
	printf("f1 cagrildi x = %d\n", x);
	return x * x;
}

int f3(int x)
{
	printf("f1 cagrildi x = %d\n", x);
	return x * x;
}


int main()
{

	int (*fpa[3])(int) = { &f1,&f2,&f3 }; // {f1,f2,f3}; �eklinde de yaz�labilir.

	for (int i = 0; i < 3; i++)
	{
		int val = fpa[i](i); // fpa[i] asl�nda bu �ekilde operasyon �a�r� operat�r�n�n operand� halinde.
								// fpa[i](i) -> burada (i) ise fonksiyon �a�r� operat�r�.  i ise burada arg�man olarak g�nderiliyor.
									// bir tane 1 var ��nk� function pointer arrayimiz sadece 1 tane arg�man al�yor.
		printf("val = %d\n", val);
	}

}
// Typedef ile yaparsak proddan �rnek verirsek
typedef int (*FPTEST)(int);
int main()
{
	FPTEST fa[] = { &isupper,&islower,&isalpha,&isalnum,&isdigit,&isxdigit,&ispunct,&isspace,&isblank,&isprint,
	&isgraph,&iscntrl };

	const char* p[] = { "isupper","islower","isalpha","isalnum","isdigit","isxdigit","ispunct",
		"isspace","isblank","isprint","isgraph","iscntrl" };
	typedef size_t unsigned int;	
	int ch;
	printf("bir karakter girin :");
	ch = getchar();

	for (size_t i = 0; i < asize(fa); i++)
	{
		if (fa[i](ch))
			printf("%s	OK\n", p[i]);
		else
			printf("%s  Not Ok\n", p[i]);
	}


}
�OK G�ZEL �RNEK

#include "mylib.h"
#include "mylib.c"
void g(void)
{
	printf("g cagrildi\n");
}
int main()
{
	// bu �rnekte mylib .h ve .c yi create etti. -> mylib.h mylib.c
	func();//default davran��� foo fonksiyonunu �a��rmak -> bu fonksiyon mylib'te

	FPTR f = setfunc(g); // setfunc a hangi fonksiyonun adresini ge�ersek func art�k o fonkisyonu �a��racak.
	// geri d�n�� de�eri ilk fonksiyonun adresi yani g nin adresi.

	func(); // art�k g yi �a��racak.

	setfunc(f);// art�k func eski davran���na geri d�nd�.

	func(); // tekrar f yi �a��racak
}


*/

