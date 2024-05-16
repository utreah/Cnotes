#include <stdio.h>
// #include "nUtility.h"
#define SIZE 10
// POINTERLARDA KAR�ILA�TIRMA
/* Pointerlarda kar��la�t�rma ayn� matematikte oldu�u gibi oluyor.

a + 5 > a + 3 gibisinden.Hi�bir fark� yok.�rne�in;


int main(void)
{
	int a[5] = {10, 20, 30, 40, 50};
	int* p1 = a + 3; // burada a dizisinin 3. eleman�n� p1'e at�yoruz.
	int* p2 = a + 2;

	printf("%d\n", p1 > p2); // burada 1 de�eri ��kar ��nk� p1'in de�eri p2'den b�y�k

	int x = 10;
	int y = 20;

	if (&x < &y) // bu sentaks hatas� olmamakla beraber Undefined behaviour.
				// Bir diziye ait olmayan iki de�i�kenin adreslerinin s�ral� olma garantisi yoktur.
				// dizilerde ise s�ral� olma garantisi vard�r. 0x1234 0x1238 gibi
}

void reverseArray(int* p, int size)
{
	int* pe = p + size; // burada pe'ye p dizisinin son eleman�n�n adresi atan�yor.
	while(p < pe) // burada p ve pe adresleri kar��la�t�r�l�yor. Dizinin birinci eleman�n�n adresi de�er olarak son adresten k���k oldu�u i�in
				// p adres de�i�keninin de�eri b�y�k veya e�it olana kadar d�ng� �al���r.
		swap(p++, pe--); // burada swap fonksiyonunda iki de�er aras�nda de�i�iklik yapt�r�l�yor. nUtility'den incelenebilir.
						// bu bir diziyi tersine d�nd�rme algoritmas� oldu�u i�in dizi_boyutu/2 defa yap�l�r.
						// p'yi bir bir artt�r�rken, pe'yi bir bir azaltt���m�z i�in dizi boyutunun yar�s� kadar i�lem yap�l�r.
}
*/


//															ADRES D�ND�REN FONKS�YONLAR		
//															FUNCTION RETURNING POINTERS
/*

	-Yani fonksiyonu �a��rd���m�zda geri d�n�� de�eri olarak bir nesnenin adresini d�nd�r�yor.
	-int* func(void) fonksiyonunun geri d�n�� de�eri int* t�r�.
	Bunu geri d�n�� de�erini tutan nesne int* t�r�nden bir nesne.
	-Adres d�nd�ren bir fonksiyon asla otomatik �m�rl� bir nesne adresi d�nd�rmemelidir. (D�nd�r�rse UB olu�ur!)

*/	
int gx = 23;
int* func(void)
{
	// code
	return &gx;
}

int gy = 98;
int* foo(void)
{
	//code
	return &gy;
}
int bar(void) {
	//code
	return 0;
}
int dar(int* p);

int main(void) {
	int* ptr;
	ptr = func();


	*ptr = 99; // burada bu yap�l�rsa adresi g�nderilen nesnenin de�erini 99 yap�yor.

	int x = 10;
	int* p1 = &x;
	int a[10] = { 0 };
	int* ptr;

	ptr = &x;
	ptr = p1;
	ptr = a;
	ptr = &a[0];
	ptr = func();
	*foo() = 78; // foo'nun d�nd�rd��� adresin i�eri�ine eri�ir ve 78 de�erini set eder.  ++*foo(); -> s�k�nt� yok.
	// bunlar�n hepsi do�ru.
	dar(foo());  // foo fonksiyonu int* t�r�nden de�er d�nd�r�r ve dar fonksiyonuda int* t�r�nden de�er al�r. Bu y�zden direkt olarak
	// foo fonksiyonunu dar fonksiyonu i�erisinde �a��rabiliriz. Ek bir int* t�r�nden de�i�kene ihtiyac�m�z yok.


	int* pg = foo();
	printf("%d\n", *pg); // 98 yazd�r�r.
	*pg = 555; // pg de�i�kenine 555 set edildi. 
	printf("%d\n", *pg); // 99 yazd�r�l�r.
	//////////////////////////////
	*foo() = 444; // burda gx'in de�eri 444 yap�lm��t�. pg ile 555 yapm��t�k.
	++* foo(); // legal ama genelde kullan�lmaz.
}
/*
printf("func = %d      foo = %d\n", *func(), *foo());
swap(func(), foo());
printf("func = %d      foo = %d\n", *func(), *foo());

return de�erleriyle swap ettik.swap zaten arg�man olarak adres al�yor.
func ve foo da adres g�nderiyor.
*/


int a[4] = { 0,1,2,3 }; // globalde bir dizi

int* arr_foo(void)
{
	// code
	return a; // a dizisinin adresini yollar -> &a[0];
}
int* get_array_max(const int* p, int size)
{
	const int* pmax = p;

	while (size--) // (p++, size--) �eklinde de yaz�labilir. 
	{
		if (*pmax < *p)
			pmax = p;
		p++;
	}
	return (int*)pmax; // buradaki cast daha sonra anlat�lacakm��.
}
int main(void)
{
	int a[SIZE];
	foo()[2]++; // bu ifade legal. a[2] 3 de�erini al�r.
	get_array_max(a, SIZE); // bu fonksiyon dizinin max de�erini de�il, o max de�erinin adresini d�nd�r�r. 
	// ben bu adresi kullanarak max de�erini de�i�triebilirim.
	*get_array_max(a, SIZE) = 10; // veya bir de�i�kene atay�p de�i�tirebilirim.
	// pmax func. scope ta bitti ama g�nderdi�i
	// adres a n�n i�erisinde bir adres ve a ya��yor.
	// hi�bir hata yok.En g�zel �rneklerden biri. Bu sayede max'� bulduktan sonra onun �zerinde istedi�imiz i�i yapabiliriz.
}

int* scan_int(void) // SINAV SORUSU
{
	int x; // otomatik �m�rl� bir de�i�ken o y�zden fonksiyondan ��k�nca �mr� biter. static int x; olsa idi s�k�nt yoktu.
	printf("Bir tam say� de�erini giriniz:");
	scanf("%d", &x);

	return x; // bu fonksiyonda x'in adresini d�nd�r�yorum ama o adresteki nesnenin hayat� bitmi� oluyor ��nk� fonksiyon scopeunun d���na ��kt�k.
			// yani bu fonksiyon 'invalid pointer'(dangling pointer) olarak adland�r�l�r.
		// Undefined behavior(tan�ms�z davran��)
}

//////////////////////////////////////////////////////////

int* foo(int* a) // e�er int a olsayd� ve x'in adresi de�il de�eri yollansayd� UB olacakt�. ��nk� a'nin �mr� otomatiktir ve adresi farkl�d�r.
				// int* a ve &x'i parametre olarak yollad���m�z i�in return a yapt���m�zda asl�nda x'in adresini d�nd�rm�� olaca��z.
{
	*a += 100;
	return a;
}
int main(void)
{
	int x = 40;
	int* p = foo(&x);
	printf("%d", *p); 
	*p *= 10;			// de�i�ken olarak ptr a kopyalanm��. foo x in adresini return ediyor
	printf("%d\n", x);	// scope tan ��k�l�nca
	// ayn� adres yani x in adresi main i�erisinde devam ediyor
	// bu sebeple UB YOK.
}
// burada UB yok ��nk� a �mr�n� main'de x olarak devam etmeye devam edecek. Yani program�n sonuna kadar �al��acak. 

////////////////////////////////////
////////////////////////////////////

int a[10];

int* foo()
{
	int* p = a + 5;
	return p;
}

int main()
{
	int* ptr = foo();
	*ptr = 123213;   // TAMAMEN GE�ERL�.SIKINTI YOK.
}

////////////////////////////////////

char* get_name(void)
{
	char str[100];
	printf("ismini yaz: ");
	scanf("%s", str);

	return str;
}


int main()
{
	char* p = get_name();	// Burada da UB var.Yukar�daki str dizisinin �mr� otomatik.
	printf("isminiz %s", p);	// fonksiyondan ��kar ��kmaz art�k hayat�da bitti.
} // return edilen yeri kullanmaya �al��mak eri�mek UB.

////////////////////////////////////
									/*TANIMSIZ DAVRANI� OLMAMASI ���N ADRES D�ND�REN FOKS�YON NE D�ND�REB�L�R*/

/*
1 - static �m�rl� nesne adresi
	a - global nesne adresi
	b - static yerel nesne adresi
	c - string literalleri(string literaller static �m�rl� olan char dizilerdir.)

2 - Client koddan ald��� adresi tekrar geri d�nd�rmesi.Mesela dizi adresi isteyen bir
pointer fakat fonksiyonun geri d�n�� de�eri ayn� dizinin adresi.o adres zaten hayatta
fonksiyon �a�r�s� bitti�inde halen dizi hayatta.�rne�i yapt�k daha �nce yukar�da

3 - Dinamik �m�rl� nesne adresi d�nd�ren fonksiyonlar.Fabrika fonksiyonlar�. -> �al��ma zaman�nda elde edilen ihtiyac�m�z olan bellek alan�n�
	kullan�ma sunmas�.
NOT: Otomotik �m�rl� nesnenin adresini d�nd�r�nce fonksiyon, g�nah i�lemi� oluyor :D
*/

//�R:
//1 - c �rne�i

char* get_day_name(int dayno)
{
	switch (dayno)     // Burada tan�ms�z davran�� YOK.��nk� hepsi 
	{					//  static �m�rl� char array.
	case 1: return "pazartesi";
	case 2: return "sali";
	case 3: return "carsamba";
	case 4: return "persembe";
	case 5: return "cuma";
	case 6: return "cumartesi";
	case 7: return "pazar";

	}
	return "";
}

////////////////////////////////////
// 
// �R-   2. Maddenin �rne�i
int random_func(int* p)
{
	int* ptr = p;

	return ptr; // Burada a dizisinin adresi d�nd�r�l�yor.
}
#undef SIZE
#define SIZE 100
int main(void)
{
	int a[5] = { 0,1,2,3,4 };
	print_array(random_func(a), SIZE); // Burada random_func a dizisiinin adresini g�nderdi�i i�in print_array k�sm�nda kullan�labilir
}

int* foo_2(const int* p, int size)
{
	// code
	// return p; // bu CPP'de sentaks hatas�, C'de ��pheli ��nk� const int* t�r�nden int t�r�ne implicit d�n���m oluyor.
	// return (int*) p; // �eklinde hatas�z d�nd�r�lebilir.
	// return (int*) (p + size - 1); // dizinin son eleman�n� d�nd�r�r. E�er size �eklinde d�nd�r�l�rse dizinin d���na ��kar�z.  
}
int main(void)
{
	int a[5] = { 0 };
	*foo_2(a, 5) = 414; // e�er return (int*)(p + size - 1); olsa idi dizinin son eleman�na 414 de�eri atan�rd�. 

}

////////////////////////////////////
int* get_array_min(const int* p, int size)
{
	int* pmin = (int*)p;
	for (int i = 0; i < size; i++)
	{
		if (*pmin > *(p + i))
			pmin = (p + i); // veya pmin = &p[i];
	}

	return pmin; // bu casting daha sonra a��klanacak.
}

int* get_array_max(const int* p, int size)
{
	int* pmax = (int*)p;
	for (int i = 0; i < size; i++)
	{
		if (*pmax < *(p + i))
			pmax = (p + i); // veya pmax = &p[i];
	}

	return pmax; // bu casting daha sonra a��klanacak.
}
if (pmax > pmin) // e�er pmax indexi pminden b�y�k ise
	print_array(pmin, pmax - pmin + 1; // pmin'den itibaren pmax'a kadar yazd�r�r.
else
	pmax, pmin - pmax + 1; // pmax'tan pmin'e kadar yazd�r�r.
////////////////////////////////////



Selection Sort

K���kten b�y��e yaparsak

98 78 54  77 5 88 46 47 68
5 78 54 77 98 88 46 47 68
5 46 54 77 98 88 78 47 68
5 46 47 54 77 98 88 78  68
... devam eder.

Bunun i�in(n - 1) * (n - 1)->n - 1 eleman i�in n - 1 kere yap�l�r.O(n2)
iki eleman kald���nda son eleman� tekrar k�yaslamaya gerek kalm�yor
bu nedenle n - 1 elaman

void selection_sort(int* ptr, int size)
{
	for (int i = 0; i < size - 1; i++)
	{
		swap(ptr + i, get_array_min(ptr + i, SIZE - i));
	}

}


int a[SIZE];
set_random_array(a, SIZE);
print_array(a, SIZE);

selection_sort(a, SIZE);
print_array(a, SIZE);

////////////////////////////////////
															/*  NULL POINTER */
	/*
		-NULL bir makrodur.Yani �ni�lemci programa tan�t�lan bir isimdir.
		-NULL bir identifier de�ildir. NULL bir keyword de de�ildir.
		-NULL makrosu bir �ok standart ba�l�k dosyas�nda tan�mlanm��t�r.
			stdio.h
			stdlib.h
			stddef.h
			time.h
			string.h


		NULL macrosu bir adres sabitidir.bunu null pointer olarak telafuz etmek gerekir.
		sadece null de�il. null pointer do�rusu

		null character
		null string
		null pointer

		null derken hangisini kastediyoruz?
		yanl�� anla��lma olmas�n diye buna NULL pointer demek �ok mant�kl�.


		Pointer olmayan bir de�i�kene, �rne�in int t�rden ya da double t�rden bir de�i�kene NULL atamay�n�z.


		-Bir pointer de�i�kenin NULL pointer de�eri ge�erli bir adrestir.
		-De�eri NULL pointer olan pointer hi�bir nesneyi g�stermeyen pointer de�i�kendir.
		-NULL pointer dereference etmek UB dir.[] veya * ile i�leme sokmak mesela.
		-NULL Pointer� ++ -- + - operat�rlerinin operand� yapmak UB dir.
		-NULL pointer hi�bir nesnenin adresi de�ildir. Bir pointer de�i�keninin NULLPTR olmas� o de�i�kenin hi�bir nesneyi g�stermemesi anlam�na gelir.
	*/



