#include <stdio.h>
// #include "nUtility.h"
#define SIZE 10
// POINTERLARDA KARÞILAÞTIRMA
/* Pointerlarda karþýlaþtýrma ayný matematikte olduðu gibi oluyor.

a + 5 > a + 3 gibisinden.Hiçbir farký yok.Örneðin;


int main(void)
{
	int a[5] = {10, 20, 30, 40, 50};
	int* p1 = a + 3; // burada a dizisinin 3. elemanýný p1'e atýyoruz.
	int* p2 = a + 2;

	printf("%d\n", p1 > p2); // burada 1 deðeri çýkar çünkü p1'in deðeri p2'den büyük

	int x = 10;
	int y = 20;

	if (&x < &y) // bu sentaks hatasý olmamakla beraber Undefined behaviour.
				// Bir diziye ait olmayan iki deðiþkenin adreslerinin sýralý olma garantisi yoktur.
				// dizilerde ise sýralý olma garantisi vardýr. 0x1234 0x1238 gibi
}

void reverseArray(int* p, int size)
{
	int* pe = p + size; // burada pe'ye p dizisinin son elemanýnýn adresi atanýyor.
	while(p < pe) // burada p ve pe adresleri karþýlaþtýrýlýyor. Dizinin birinci elemanýnýn adresi deðer olarak son adresten küçük olduðu için
				// p adres deðiþkeninin deðeri büyük veya eþit olana kadar döngü çalýþýr.
		swap(p++, pe--); // burada swap fonksiyonunda iki deðer arasýnda deðiþiklik yaptýrýlýyor. nUtility'den incelenebilir.
						// bu bir diziyi tersine döndürme algoritmasý olduðu için dizi_boyutu/2 defa yapýlýr.
						// p'yi bir bir arttýrýrken, pe'yi bir bir azalttýðýmýz için dizi boyutunun yarýsý kadar iþlem yapýlýr.
}
*/


//															ADRES DÖNDÜREN FONKSÝYONLAR		
//															FUNCTION RETURNING POINTERS
/*

	-Yani fonksiyonu çaðýrdýðýmýzda geri dönüþ deðeri olarak bir nesnenin adresini döndürüyor.
	-int* func(void) fonksiyonunun geri dönüþ deðeri int* türü.
	Bunu geri dönüþ deðerini tutan nesne int* türünden bir nesne.
	-Adres döndüren bir fonksiyon asla otomatik ömürlü bir nesne adresi döndürmemelidir. (Döndürürse UB oluþur!)

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


	*ptr = 99; // burada bu yapýlýrsa adresi gönderilen nesnenin deðerini 99 yapýyor.

	int x = 10;
	int* p1 = &x;
	int a[10] = { 0 };
	int* ptr;

	ptr = &x;
	ptr = p1;
	ptr = a;
	ptr = &a[0];
	ptr = func();
	*foo() = 78; // foo'nun döndürdüðü adresin içeriðine eriþir ve 78 deðerini set eder.  ++*foo(); -> sýkýntý yok.
	// bunlarýn hepsi doðru.
	dar(foo());  // foo fonksiyonu int* türünden deðer döndürür ve dar fonksiyonuda int* türünden deðer alýr. Bu yüzden direkt olarak
	// foo fonksiyonunu dar fonksiyonu içerisinde çaðýrabiliriz. Ek bir int* türünden deðiþkene ihtiyacýmýz yok.


	int* pg = foo();
	printf("%d\n", *pg); // 98 yazdýrýr.
	*pg = 555; // pg deðiþkenine 555 set edildi. 
	printf("%d\n", *pg); // 99 yazdýrýlýr.
	//////////////////////////////
	*foo() = 444; // burda gx'in deðeri 444 yapýlmýþtý. pg ile 555 yapmýþtýk.
	++* foo(); // legal ama genelde kullanýlmaz.
}
/*
printf("func = %d      foo = %d\n", *func(), *foo());
swap(func(), foo());
printf("func = %d      foo = %d\n", *func(), *foo());

return deðerleriyle swap ettik.swap zaten argüman olarak adres alýyor.
func ve foo da adres gönderiyor.
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

	while (size--) // (p++, size--) þeklinde de yazýlabilir. 
	{
		if (*pmax < *p)
			pmax = p;
		p++;
	}
	return (int*)pmax; // buradaki cast daha sonra anlatýlacakmýþ.
}
int main(void)
{
	int a[SIZE];
	foo()[2]++; // bu ifade legal. a[2] 3 deðerini alýr.
	get_array_max(a, SIZE); // bu fonksiyon dizinin max deðerini deðil, o max deðerinin adresini döndürür. 
	// ben bu adresi kullanarak max deðerini deðiþtriebilirim.
	*get_array_max(a, SIZE) = 10; // veya bir deðiþkene atayýp deðiþtirebilirim.
	// pmax func. scope ta bitti ama gönderdiði
	// adres a nýn içerisinde bir adres ve a yaþýyor.
	// hiçbir hata yok.En güzel örneklerden biri. Bu sayede max'ý bulduktan sonra onun üzerinde istediðimiz iþi yapabiliriz.
}

int* scan_int(void) // SINAV SORUSU
{
	int x; // otomatik ömürlü bir deðiþken o yüzden fonksiyondan çýkýnca ömrü biter. static int x; olsa idi sýkýnt yoktu.
	printf("Bir tam sayý deðerini giriniz:");
	scanf("%d", &x);

	return x; // bu fonksiyonda x'in adresini döndürüyorum ama o adresteki nesnenin hayatý bitmiþ oluyor çünkü fonksiyon scopeunun dýþýna çýktýk.
			// yani bu fonksiyon 'invalid pointer'(dangling pointer) olarak adlandýrýlýr.
		// Undefined behavior(tanýmsýz davranýþ)
}

//////////////////////////////////////////////////////////

int* foo(int* a) // eðer int a olsaydý ve x'in adresi deðil deðeri yollansaydý UB olacaktý. Çünkü a'nin ömrü otomatiktir ve adresi farklýdýr.
				// int* a ve &x'i parametre olarak yolladýðýmýz için return a yaptýðýmýzda aslýnda x'in adresini döndürmüþ olacaðýz.
{
	*a += 100;
	return a;
}
int main(void)
{
	int x = 40;
	int* p = foo(&x);
	printf("%d", *p); 
	*p *= 10;			// deðiþken olarak ptr a kopyalanmýþ. foo x in adresini return ediyor
	printf("%d\n", x);	// scope tan çýkýlýnca
	// ayný adres yani x in adresi main içerisinde devam ediyor
	// bu sebeple UB YOK.
}
// burada UB yok çünkü a ömrünü main'de x olarak devam etmeye devam edecek. Yani programýn sonuna kadar çalýþacak. 

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
	*ptr = 123213;   // TAMAMEN GEÇERLÝ.SIKINTI YOK.
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
	char* p = get_name();	// Burada da UB var.Yukarýdaki str dizisinin ömrü otomatik.
	printf("isminiz %s", p);	// fonksiyondan çýkar çýkmaz artýk hayatýda bitti.
} // return edilen yeri kullanmaya çalýþmak eriþmek UB.

////////////////////////////////////
									/*TANIMSIZ DAVRANIÞ OLMAMASI ÝÇÝN ADRES DÖNDÜREN FOKSÝYON NE DÖNDÜREBÝLÝR*/

/*
1 - static ömürlü nesne adresi
	a - global nesne adresi
	b - static yerel nesne adresi
	c - string literalleri(string literaller static ömürlü olan char dizilerdir.)

2 - Client koddan aldýðý adresi tekrar geri döndürmesi.Mesela dizi adresi isteyen bir
pointer fakat fonksiyonun geri dönüþ deðeri ayný dizinin adresi.o adres zaten hayatta
fonksiyon çaðrýsý bittiðinde halen dizi hayatta.Örneði yaptýk daha önce yukarýda

3 - Dinamik ömürlü nesne adresi döndüren fonksiyonlar.Fabrika fonksiyonlarý. -> Çalýþma zamanýnda elde edilen ihtiyacýmýz olan bellek alanýný
	kullanýma sunmasý.
NOT: Otomotik ömürlü nesnenin adresini döndürünce fonksiyon, günah iþlemiþ oluyor :D
*/

//ÖR:
//1 - c örneði

char* get_day_name(int dayno)
{
	switch (dayno)     // Burada tanýmsýz davranýþ YOK.Çünkü hepsi 
	{					//  static ömürlü char array.
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
// ÖR-   2. Maddenin örneði
int random_func(int* p)
{
	int* ptr = p;

	return ptr; // Burada a dizisinin adresi döndürülüyor.
}
#undef SIZE
#define SIZE 100
int main(void)
{
	int a[5] = { 0,1,2,3,4 };
	print_array(random_func(a), SIZE); // Burada random_func a dizisiinin adresini gönderdiði için print_array kýsmýnda kullanýlabilir
}

int* foo_2(const int* p, int size)
{
	// code
	// return p; // bu CPP'de sentaks hatasý, C'de þüpheli çünkü const int* türünden int türüne implicit dönüþüm oluyor.
	// return (int*) p; // þeklinde hatasýz döndürülebilir.
	// return (int*) (p + size - 1); // dizinin son elemanýný döndürür. Eðer size þeklinde döndürülürse dizinin dýþýna çýkarýz.  
}
int main(void)
{
	int a[5] = { 0 };
	*foo_2(a, 5) = 414; // eðer return (int*)(p + size - 1); olsa idi dizinin son elemanýna 414 deðeri atanýrdý. 

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

	return pmin; // bu casting daha sonra açýklanacak.
}

int* get_array_max(const int* p, int size)
{
	int* pmax = (int*)p;
	for (int i = 0; i < size; i++)
	{
		if (*pmax < *(p + i))
			pmax = (p + i); // veya pmax = &p[i];
	}

	return pmax; // bu casting daha sonra açýklanacak.
}
if (pmax > pmin) // eðer pmax indexi pminden büyük ise
	print_array(pmin, pmax - pmin + 1; // pmin'den itibaren pmax'a kadar yazdýrýr.
else
	pmax, pmin - pmax + 1; // pmax'tan pmin'e kadar yazdýrýr.
////////////////////////////////////



Selection Sort

Küçükten büyüðe yaparsak

98 78 54  77 5 88 46 47 68
5 78 54 77 98 88 46 47 68
5 46 54 77 98 88 78 47 68
5 46 47 54 77 98 88 78  68
... devam eder.

Bunun için(n - 1) * (n - 1)->n - 1 eleman için n - 1 kere yapýlýr.O(n2)
iki eleman kaldýðýnda son elemaný tekrar kýyaslamaya gerek kalmýyor
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
		-NULL bir makrodur.Yani öniþlemci programa tanýtýlan bir isimdir.
		-NULL bir identifier deðildir. NULL bir keyword de deðildir.
		-NULL makrosu bir çok standart baþlýk dosyasýnda tanýmlanmýþtýr.
			stdio.h
			stdlib.h
			stddef.h
			time.h
			string.h


		NULL macrosu bir adres sabitidir.bunu null pointer olarak telafuz etmek gerekir.
		sadece null deðil. null pointer doðrusu

		null character
		null string
		null pointer

		null derken hangisini kastediyoruz?
		yanlýþ anlaþýlma olmasýn diye buna NULL pointer demek çok mantýklý.


		Pointer olmayan bir deðiþkene, örneðin int türden ya da double türden bir deðiþkene NULL atamayýnýz.


		-Bir pointer deðiþkenin NULL pointer deðeri geçerli bir adrestir.
		-Deðeri NULL pointer olan pointer hiçbir nesneyi göstermeyen pointer deðiþkendir.
		-NULL pointer dereference etmek UB dir.[] veya * ile iþleme sokmak mesela.
		-NULL Pointerý ++ -- + - operatörlerinin operandý yapmak UB dir.
		-NULL pointer hiçbir nesnenin adresi deðildir. Bir pointer deðiþkeninin NULLPTR olmasý o deðiþkenin hiçbir nesneyi göstermemesi anlamýna gelir.
	*/



