Bir fonksiyonun davranýþýný o fonksiyona çaðrý yapan kodun deðiþtirebilmesini saðlýyor.

Örneðin, bir function pointer deðiþkeni alan fonksiyon olsun.

void print_char(int (*fp)(int))
{
	for (int i = 0; i < 128; i++)
		if (fp(i))
			printf("%c", i;);
}
print_char adlý fonksiyona yolladýðýmýz bir fonksiyonun adresi ile for döngüsü içerisinde
	yapýlan iþlemi deðiþtirebiliyoruz.;
print_char(&isupper);
print_char(&isdigit);
print_char(&islower);

Bu fonksiyonlarýn adreslerini yollayarak istediðimiz iþlemi yaptýrabiliyoruz.

//////////////////////////////////
int foo(int x) {
	printf("Foo cagrildi, x = %d", x);
	return x * x;
}
int main(void) {

	int (*fp)(int) = foo;
	int retval = fp(45); // array decay gibi, fp'yi fonksiyon çaðrý operatörünün operandý yaparak kullanýyorum..
							// fp(45) == (*fp)(45), fp'yi içerik operatörünün operandý yaparak fp'nin gösterdiði fonksiyonu görebiliriz
								// içerik operatörünün önceliði function call operatoründen daha düþük olduðundan dolayý öncelik parantezi
									// içerisine alýyoruz

	// retval = fp(45)
	// retval = (*fp)(45) bu þekilde kullanýlmasýnýn hiçbir avantajý yok. Kullanýlmasýnýn sebebi function pointer olduðunu vurgulamak için.

	/////////////////////
	int (*fp2)(int) = &foo;
	(&foo)(12); // Legal
	(*foo)(12); // Legal
	fp2(15); // Legal
	(*fp2)(15); // Legal
	(&fp2)(15); // Illegal -> çünkü fp2 bir pointer ve biz bunun adresini aldýðýmýzda aslýnda ** þeklinde oluyor. 
	


}

/////////////////////////////////////////////

// foo ve bar herhangi bir kodda iki farklý fonksiyon olsun

//Alttaki örnekler ayný fonksiyon deðil, örnek için
foo(bar()); // Burada bar adlý fonksiyon çaðrýlýyor ve geri dönüþ deðeri foo fonksiyonunda parametre deðeri olarak kullanýlýyor
foo(bar); // Burada ise bar adlý fonksiyonun ADRESÝ foo'ya parametre deðeri olarak kullanýlýyor. Ýkisi FARKLI
foo(&bar); // Üstteki ile ayný


/////////////////////////////////////////////

			// Function pointerla TYPEDEF kullanmak
#include <string.h>
#include <stdio.h>
#include <ctype.h>
int foo(const char*, const char*);
int bar(const char*, const char*);
int baz(const char*, const char*);
void f1(int (*fp)(const char*, const char*)); // f1, parametre deðiþkeni function pointer olan, geri dönüþ deðeri olmayan bir fonksiyon
void f2(int (*fp)(const char*, const char*), int (*fp2)(const char*, const char*)); // f2, parametre deðiþkenleri function pointer olan, geri dönüþ deðeri olmayan bir fonksiyon
int	(*f3(int (*fp)(const char*, const char*, int (*fp2)(const char*, const char*)))(const char*, const char*);
typedef int (*FPTR)(const char*, const char*);
int main(void) {
	int (*fp)(const char*, const char*) = &strcmp; // bu  pointer to function pointer
	int (**fpp)(const char*, const char*) = &fp; // bu ise pointer to function pointer to function pointer

	///////////////////////
	int (*fp)(const char*, const char*) = foo;

	// Fonksiyonlarýn adresini tutan bir function pointer array yazmak için þu adýmlarý izliyoruz.
		// ayný dizi oluþturur gibi fonksiyonlarýn adreslerini yazýyoruz.
			// {&bar, &foo, &baz} daha sonra ise fonksiyonlarýn parametre deðiþkenlerini tutabilen function pointerý yazýyoruz
				// int (*fpar)(const char*, const char*) son olarakta tutacaðý eleman sayýsýný index operatörü ile beraber
					// function pointerýn yanýna yazýyoruz
	int (*fpar[3])(const char*, const char*) = { &bar, &foo, &baz }; // bu 3 fonksiyonun adresini tutan bir function pointer array oluþturduk

	/*
	Geri dönüþ deðeri function pointer olan, parametreleri function pointer olan bir fonksiyon nasýl yazýlýr?
		Önce fonksiyonun adý yazýlýr
			-func
		Daha sonra fonksiyon adýnýn baþýna asterisk atomu koyulur
			-*func
		Fonksiyon adýnýn yaýna fonksiyonun iliþkili olduðu parametreler yazýlýr
			-*func(int, double)
		Bir daha paranteze alýnýr
			-(*func(int, double))
		Fonksiyonun iliþkili olduðu geri dönüþ deðeri yazýlýr
			-int (*func(int, double))
		Function pointerin iliþkili olduðu parametreler yazýlýr
			-int (*func(int, double))(const char*, const char*)
	*/
	int ergo(const char*, const char*); // ->bu bir fonksiyon;
	int (*func(void))(const char*, const char*) {
		return ergo; // veya return &ergo. 
				// func fonksiyonu ergo'yu return edebilir.
	}
	// Yukarýda yaptýðýmýz tüm örnekler aþýrý karmaþýk ve anlamasý zor.
		// Kodlama hatasý riskini azaltmak, anlamayý kolaylaþtýrmak için tür-eþ(typedef alias) kullanýyoruz
	/*	typedef nasýl kullanýyoruz ?
		-Eþ-tür ismi kullanýlacak türden bir deðiþken tanýmla
			int (*f)(const char*, const char*);
		-Baþýna typedef getir
			typedef int (*f)(const char*, const char*);
		-Deðiþkenin adýný yapmak istediðin eþ-tür ismi ile deðiþtir	
			typedef int (*FPTR)(const char*, const char*);
	*/ 

	FPTR fp = foo;
	FPTR* fpp = &fp;
	FPTR fpar[] = { foo, bar, baz };
	// FPTR typedef kullanraak f1,f2 ve f3 fonksiyonlarýný nasýl yazabiliriz?
	void f1(FPTR fp);
	void f2(FPTR fp1, FPTR fp2);
	FPTR f3(FPTR fp1, FPTR fp2);
}	
////////////////////////////////////////////////////////////
// Üretimde kullanýlabilecek bazý örnekler - QSORT
/*Callback, bir fonksiyona bir fonksiyonu argüman olarak olarak gönderiyoruz, çaðýrdýðým
fonksiyonun benim gönderdiðim fonksiyonu çaðýrmasýný isteyeceðiz.

yani fonksiyonu baþka bir fonksiyona çaðýrtacaðýz.

bir fonksiyona argüman olarak fonksiyon göndererek yapýyor bu iþi.
Çaðýrdýðým fonksiyon benim gönderdiðimi çaðýrýyor.*/

// q sort türden baðýmsýz çalýþýyor (void*)


void qsort(void* vpa, size_t size, size_t sz, int (*fcomp)(const void*, const void*)) {
	// vpa = Sýralama iþleminin yapýlacaðý dizinin adresý
	// size = dizinin boyutu
	// sz = sýralama yapýlan elemanýn boyutu (int, double 4byte gibi düþün)
	// fcomp = Bu ise fonksiyon pointer. Adresini aldýðý fonksiyonu kullanarak karþýlaþtýrma yapacak. Yani bu parametreye strcmp'nin
		// adresini gönderebilirim.

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
	return *(const int*)vp1 - *(const int*)vp2; // Bu yazým þekli hem doðru hem de yanlýþ. Yapýlan iþlem tam sayý olduðu sürece
		// doðru sonuç elde ederiz fakat TAÞMA riski var. Eðer sýralamasýný yaptýðýmýz dizinin elemanlarýnýn deðerinin taþma riski
			// oluþturmayacaðý garantisi var ise bu þekilde de yazýlabilir.
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
// ÖDEV - Bubblesort algoritmasýný "GENERIC" olarak implemente eden ismi gbsort fonksiyonu tanýmlayýnýz.


void gbsort(void* vpa, size_t size, size_t sz, int (*fp)(const void*, const void*))
{
	char* p = (char*)vpa;
	for (int i = 0; i < size - 1; i++)
		for (int k = 0; k < size - 1 - i; k++) 
			// Eðer dizinin k indisli elemaný dizinin k + 1 indisli elemanýndan büyük ise
				// dizinin k indisli elemaný ile k + 1 i indisli elemaný ile takasla
			if (fp(p + k * sz, p + (k + 1) * sz) > 0) 
				gswap(p + k * sz, p + (k + 1) * sz, sz); // bunun kodunu daha önce yazmýþtýk. Tekrar yazmanýn anlamý yok
}
int main(void) { // ÖDEV
	char* names[] = {
	"Ali, Yýlmaz",
	"Ayþe, Demir",
	"Mehmet, Kaya",
	"Fatma, Çelik",
	"Ahmet, Yurt",
	"Elif, Arslan",
	"Mustafa, Öztürk",
	"Zeynep, Polat",
	"Hasan, Aydýn",
	"Emine, Kara",
	"Hüseyin, Güneþ",
	"Meryem, Arý",
	"Osman, Koç",
	"Seda, Erkan",
	"Ýsmail, Çetin",
	"Hülya, Tekin",
	"Cemal, Görkem",
	"Büþra, Çakýr",
	"Yusuf, Karaaslan",
	"Derya, Yurt"
	};
	// bu isimleri büyükten küçüðe gbsort kullanarak sýralayacaðýz. strcmp kullanarak.
		// gbsort'taki fonksiyona callback olarak yazýlarýn tutulduðu dizinin adresi gönderilecek. Bunu düþünerek yaz kodu 
	
}

//////////////////////////////////////////////////////////////////
// bsearch  yani binary search. Standart kütüphanenin fonksiyonu.Sýralý dizide arama yapýyor.Kodunu yazmýþtýk.
void* (const void* pkey, const void vpa, size_t size, size_t sz, int(*fp)(const void*, const void*));
/*
	-pkey = aranacak deðerin adresi
	-vpa = aranacak dizinin adresi
	-size = arama yapýlacak dizinin boyutu
	-sz = arama yapýlan dizinin bir elemanýnýn boyutu
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
fonksiyon pointerlarýna NULL pointer atanabilir.
////////////////////////////////////////////

FUNCTION POINTER ARRAYS

---------------------- -

int* p[10] demek int* ptr den 10 tane var demek.

Bunu uyarlarsak

int (*fptr[10])(int);  typedef ile de tanýmlanabilir bu daha kýsa olur hatta.

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

	int (*fpa[3])(int) = { &f1,&f2,&f3 }; // {f1,f2,f3}; þeklinde de yazýlabilir.

	for (int i = 0; i < 3; i++)
	{
		int val = fpa[i](i); // fpa[i] aslýnda bu þekilde operasyon çaðrý operatörünün operandý halinde.
								// fpa[i](i) -> burada (i) ise fonksiyon çaðrý operatörü.  i ise burada argüman olarak gönderiliyor.
									// bir tane 1 var çünkü function pointer arrayimiz sadece 1 tane argüman alýyor.
		printf("val = %d\n", val);
	}

}
// Typedef ile yaparsak proddan örnek verirsek
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
ÇOK GÜZEL ÖRNEK

#include "mylib.h"
#include "mylib.c"
void g(void)
{
	printf("g cagrildi\n");
}
int main()
{
	// bu örnekte mylib .h ve .c yi create etti. -> mylib.h mylib.c
	func();//default davranýþý foo fonksiyonunu çaðýrmak -> bu fonksiyon mylib'te

	FPTR f = setfunc(g); // setfunc a hangi fonksiyonun adresini geçersek func artýk o fonkisyonu çaðýracak.
	// geri dönüþ deðeri ilk fonksiyonun adresi yani g nin adresi.

	func(); // artýk g yi çaðýracak.

	setfunc(f);// artýk func eski davranýþýna geri döndü.

	func(); // tekrar f yi çaðýracak
}


*/

