#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <string.h>
#include <stdio.h>
#define SIZE 100
typedef unsigned char BYTE;
void* memmove(void* vpdest, const void* vpsrc, size_t size) {
	//memmove ve memcpy semantik olarak ayn� ve ayn� i�lemi yap�yorlar.
	// overlapped blocks(kesi�en bellekler): E�er iki bellek blo�unun yap�lan i�lem a��s�ndan ortak bir alan� varsa
		// o zaman o ortak alana sahip bellek bloklar�na overlapped blocks deniyor.
	// strcpy'nin overlapped bloklar� �zerinde davran��� UB, ayn� �ekilde memcpy'de overlapped bloklarda UB. 
	// C99 standartlar� ile beraber restrict diye bir keyword eklendi.
		// restrict keywordu asterisk(*)'dan sonra geliyor ve T* t�r�nden bir de�i�kenin g�sterdi�i adresin
		// ba�ka bir de�i�ekn taraf�ndan g�sterilmedi�inin garantisini veriyor.
			// Bu sayede overlapped blocktan dolay� olan UB'nin �n�ne ge�iyor. 
		// E�er buna uyulmaz ise UB olu�ur. Mesela strcpy(p+3, p); burada restrict keyword� ile tan�mlanm�� olmas�na ra�men
			// kullan�lm�� buras� UB ��nk� tan�mda restrict var. restrict varsa overlapped block varsa UB'de vard�r.
			// 	strcpy (a+3, a); // UB
			// memcpy(a + 3, a, 3 * sizeof(int)); // UB 
		// void func(int* restrict p1, int* restrict p2) // burada p1'in g�sterdi�i nesne ile p2'nin g�sterdi�i nesne ayn� olamaz
			// ikisi de farkl� olmak zorunda. Buna ba�l� olarakta derleyiciler temel optimizasyonu farkl� yapacak. Sonu�ta
				// UB olmama garantisi var.
	
}
/*
memchr(const void* vptr, int val, size_t size) // adresini ve b�y�kl���n� ald��� bir bellek blo�unda tam say� de�eri ar�yor.
	-Blo�un i�eri�ini bilmez. Yani arad��� blo�un yaz�y� tutan bir bellek blo�umu yoksa say� tutan bir bellek blo�u mu bilmez.
	-2. parametre int olmas�n�n sebebi integral promotion. Aranan karakter char t�r�nden olsa da integral promotiondan dolay�
		int oluyor.
	-strchr() sondaki null karakterine g�venirken memchr parametresindeki SIZE'a g�venir.
*/
void* my_memchr(const void* vptr, int val, size_t size) {
	const char* p = (const char*)vptr;
	while (size--)
		if (*p == val)
			return (char*)p; // void* t�r�ne �rt�l� olarak d�n��t�r�l�yor. char*'a cast etmek yerine void* cast etsekte s�k�nt�s�z �al���rd�.
	return NULL;
}
/*
int memcmp(const void* vptr, const void* vptr2, size_t size);
	-E�er geri d�n�� de�eri 0 ise iki bellek blo�u birbirine e�it.
	-E�er geri d�n�� de�eri pozitif ise vp1 vp2'den b�y�k.
	-E�er geri d�n�� de�eri negatif ise vp1 vp2'den k���k.
		Buraya kadar strcmp ile ayn� zaten.
	-�ki bellek blo�unu kar��la�t�r�yor.
	-Bu bloklar�n i�eri�inde ne oldu�u memcmp'yi ba�lam�yor. Umrum d���s�n diyor resmen.
	-Kar��la�t�rma yap�l�rken unsigned t�rden yap�l�yor. Bytelar i�aretsiz tam say� olarak de�erlendirilecek.

	0001 0001					0001 0001
	0000 0000					0000 0000
	1111 1111					1111 1111
	0101 0101					0101 0101
	E�er birebir e�itse ayn� olarak g�r�yor.
	�imdi 3. byte'taki LSB'i 0 yapal�m
		vp1							vp2
	0001 0001					0001 0001
	0000 0000					0000 0000
	1111 1111					1111 1110 -> bunu 0 yapt�k
	0101 0101					0101 0101
	
	��aretsiz binaryde 1111 1111 de�er olarak 1111 1110'dan b�y�k oldu�u i�in burada vp1 belle�i > vp2 belle�i, s�z konusu

*/
int my_memcmp(const void* vp1, const void* vp2, size_t n)
{
	const unsigned char* p1 = (const unsigned char*)vp1; // unsigned olarak k�yaslad���n� s�ylemi�tik.
	const unsigned char* p2 = (const unsigned char*)vp2; // unsigned olarak k�yaslad���n� s�ylemi�tik.

	while (n--)
	{
		if (*p1 != *p2)
		{
			return *p1 > *p2 ? 1 : -1; // buradaki b�y�kl�k, de�erlerin b�y�kl��� de�il,
		}								// bytelar�n k�yaslamas� sonucu olu�an b�y�kl�k.
		++p1, ++p2;						// Notlarda a�a��da yani var a��klamas�.
	}

	return 0;

}
int main(void) {
	char str[SIZE] = "gulden";
	strcpy(str + 3, str); // bu undefined behaviour -> overlapped blocks
	memcpy(str + 3, str, 7); // bu undefined behaviour -> overlapped blocks
	memmove(str + 3, str, strlen(str) + 1); // bunda s�k�nt� yok 
	///////////////////////////////// memchr() �RNEK

	BYTE ar[SIZE] = { 0 };
	srand((unsigned)time(0));
	for (int i = 0; i < SIZE; i++)
		ar[rand() % SIZE] = 1;

	for (int i = 0; i < SIZE; i++)
		printf("%d", ar[i]);

	printf("\n");
	BYTE* p = (BYTE*)memchr(ar, 0, sizeof(ar));
	if (p)
		printf("Bulundu! %lld nolu indiste", p - ar); // format specifier derleyiciye ba�l�. E�er long long veya unsigned long long olursa specifer farkl� olur.
	else
		printf("BULUNAMADI");
	/// /////////////////////////////////////
	char str[SIZE] = "Mustafa Mete C dersini izliyor, degil mi";
	memchr(str, 'e', 8); // e karakterini 8 bytel�k alanda arayacak. Yani Mustafa_ k�sm�na kadar ve bulamayacak.
							// strchr'den en b�y�k fark� bu. STRCHR null karakterine kadar b�t�n diziyi ararken
								// memchr bir bellek blo�unda belirlenen byte kadar arama yapabiliyor.
	/////////////////////////////////// memcmp() �RNEK
	int a[SIZE];
	int b[SIZE];
	randomize();
	set_array_random(a, SIZE);
	memcpy(b, a, sizeof a);

	if (!memcmp(b, a, sizeof a))
		printf("Diziler birbirine e�it"); // diziler line 111'den dolay� birbirine e�it.
	else
	++a[rand() % SIZE];

	if (!memcmp(b, a, sizeof a))
		printf("Diziler birbirine e�it");
	else
		printf("Diziler birbirine e�it de�il"); // art�k e�it de�il
	
	return 0;
}
 /* VOID* 2. KISIM
 
	T�rden ba��ms�z bir arama fonksiyonu yaz�labilir mi? Evet,

	void* gsearch(const void* vpa, size_t size, size_t szof, const void* vpkey);
		vpa = ��erisinde arama yap�lacak dizinin adresi
		size = dizinin boyutu
		szof = dizinin 1 eleman�n�n sizeof de�eri
		vpkey = aranacak de�er
 */
void* myf_gsearch(const void* vpa, size_t size, size_t szof, const void* vpkey) {
	const char* p = (const char*)vpa;
	for (size_t i = 0; i < size; i++) {

		if (!memcmp(p+i*szof, vpkey, szof)) // p + i * szof; szof burada kulland���m�z de�i�kenin t�r�n�n bellekte kaplad��� yer.
			return (char*)(p + i * szof);	// memcmp i�erisinde, yollanan bellek blo�u tamamen kar��la�t�r�l�yor(1 byte)
											// sonraki bellek blo�una ge�ebilmek i�in p + i'yi sz ile �arp�yoruz.
	}
	return NULL;
}
void* myw_gsearch(const void* vpa, size_t size, size_t sz, const void* vpkey) {
	const char* p = (const char*)vpa;
	while (size--) {
		if (!memcmp(p, vpkey, sz))
			return (char*)p;
		p += sz; // p'nin elemanlar� int t�r�nden ise sizeof de�eri 4 olaca��ndan dolay� p'nin de�eri d�rder d�rder artt�r�l�r.
					// p++ char* t�r�nde bir byte bir byte ilerlemek demek. Biz zaten p ve vpkey parametre de�i�kenlerini memcmp'ye att���m�zda
						// o bellek blo�u(1 byte) tamamen kar��la�t�r�l�yor. Sonraki bellek blo�una ge�ebilmemiz i�in o veri t�r�n�n 
						//	bellekte kaplad��� kadar p'ye eklememiz gerekiyor. sz'de burada o veri t�r�n��n sizeof de�erini tutuyor.s
						//	E�er i�inde arama yapt���m�z dizinin t�r� int ise +4, double ise 8 olurdu sz i�in.
	}
	return NULL;
}
int main(void) {
	int a[SIZE];
	randomize();
	set_random_array(a, SIZE);
	print_array(a, SIZE);
	int sval;

	printf("aranacak degeri girin ");
	(void)scanf("%d", &sval);
	int* p = (int*)gsearch(a, SIZE, sizeof(*a), &sval);
	// int *p = dizinin bir int dizi oldu�unu biliyoruz. D�nen de�erde void * olacak.
	// bizde zaten cast ettik
	// a = array
	// SIZE = Dizi uzunlu�u
	// sizeof(*a) -> bir eleman�n sizeof de�eri
	// &sval -> aranan deger adresi. HEr�ey adresler �zerinden yap�l�yor. memcmp de kullan�lacak
	// bu de�i�ken ve memcmp de adres ile i�lem yap�yor.t�rden ba��ms�z ��nk�.

	if (p)
		printf("bulundu dizinin %d indisli elemani\n", p - a);
	else
		printf("bulunamadi\n");
}
////////////////////////////////////////
 /*
	-Yazaca��m�z bir �ok fonksiyon hala t�re ba�l� olacak.
	-Gerekmedi�i s�rece hem bak�m hem de kodun anlaman�n daha kolay olmas� i�in void* kullan�lmayacak.(zorunlu de�ilse)
	-
 */
///////////////////////////////////////
///////////////////////////////////////  
/*
	void* vptr = NULL; // void* t�r�nden bir de�i�ken herhangi bir nesnenin adresini tutabilir.
		vptr = &vptr; // kendi adresini tutabilir.
	void** vp2; // void* t�r�nden bir de�i�ken herhangi bir nesnenin adresini tutabilirken, void** t�r�nden bir de�i�ekn
					// herhangi T* t�r�nden bir nesnenin adresini tutabilir diye bir analoji kurulamaz.
				//void** t�r� de di�er T** t�rleri gibi �al���r. void* veri t�r� ile bildirilmi� nesnenin adresini tutabilir.
					// void** t�r� generic bir t�r de�il.
	int x = 10;
	int* y = &x;
	vp2 = &vptr; // s�k�nt� yok
	vp2 = &y; // hatal� y int* t�r�nden bir nesne ve void**'a atanamaz.
	*vptr = 10; // Bu derefence edilemez ��n� vptr NULL pointer� g�steriyor. Bu t�rden
					// ba��ms�z, bir kural. Ek olarakta, void* t�r�nden nesneler dereference edilemez. 
	*vp2 = &y; // vptr'ye y'nin adresini cast edebiliriz ��nk� vp2 derefence edilebilir ve edildi�inde vptr nesnesinin de�erine eri�ir.

	int main(void){
		int x = 10;
		double dval = 45.56;

		void* vp = &x; 
		*vp; // sentaks hatas�, derefence edilemez.
		void** vptr = &vp; // t�rsel a��dan hi�bir s�k�nt� yok.
		*vptr = &dval; // vp'ye dval'i at�yorum. *vptr == vp;
		 
	}
		�yle durumlarla kar��la��caz ki 3. parti k�t�phaneler bizden void* t�r�ndeki nesnenin adresini isteyecek.
	int g;
	void foo(void** vptr){
		*vptr = &g;
	}
	int main(void){
		void* vp1;
		foo(&vp1); // void* t�r�nden  bir nesnenin adresini g�nderdik. foo fonksiyonunun parametresi void** t�r�nden
		int* p = NULL;
		void* x = &p; // void* t�r�nden bir de�i�kene herhangi bir nesnenin adresini atayabilirim
		void **y = &p; // fakat void** t�r�nden bir de�i�kene sadece void* t�r�nden bir nesnenin adresini atayabilirim.
							// bundan dolay� burada t�r uyu�mazl��� var
	}	
	Bir fonksiyonun geri d�n�� de�eri T* t�rden olabilece�i gibi T** t�r�nden de olabilir.
*/
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
/*												FUNCTION POINTERS
	-Bir fonksiyonun, ba�ka bir fonksiyona fonksiyon g�ndermesi. Buna Callback deniyor.
	Pointerlar ikiye ayr�l�yor;
		-object pointers -> De�i�kenlerin(nesnelerin) adresleri.
		-function pointers -> Fonksiyonlar�n adresleri.
	-Fonksiyonlar�n da adresi vard�r ayn� nesnelerin adresinin olmas� gibi.
	-Nesnelerin memoryde adresleri vard�. Bu adresler s�z konusu oldu�unda pointer kullan�r�z. Fonksiyonlar�n da makine kodlar� var.
		Bu makine kodlar�n�n �al��abilmesi i�in memory'e y�klenmesi gerekiyor. Bu makine kodlar�n�n y�klendi�i bellek blo�unun da adresi var.
			Adresi biliyor isek fonksiyonu �a��rabiliriz.
				�zet= Makine komutlar� bellekte tutuldu�u adres.
	-Fonksiyonlar�n ve fonksiyon adreslerinin de t�r� var.
		Bir fonksiyon adresinin t�r�, fonksiyonun geri d�n�� t�r� ve parametrelerinin t�r�nden elde ediliyor.
	-Fonksiyon t�r� ile fonksiyon adresinin t�r� ayn� �ey de�ildir.
		Fonksiyon t�r�: Fonksiyonun geri d�n�� de�eri(parametrelerinin t�r�)
	Bildirim							 Fonksiyon T�r�					Fonksiyon Adresi T�r�(geri d�n�� de�eri (*)(parametre de�i�kenleri))
	int foo(int); 						 int(int)						int (*)(int)
	int bar(int, int)					 int(int, int)					int (*)(int, int)
	double baz(double)					 double(double)					double (*)(double)
	size_t strlen(const char*)			 size_t(const char*)			size_t (*)(const char*) // (*) bir pointer oldu�unu g�stermek i�in yaz�l�yor.
	int strcmp(const char*, const char*) int(const char*, const char*)	int (*)(const char*, const char*)
	char* strcpy(char*, const char*)	 char*(char*, const char*)		char* (*)(char*, const char*)

	-Bir fonksiyonun adresini nas�l elde ediyoruz?
		Bir fonksiyonun adresini elde etmek i�in ayn� de�i�kenlerde oldu�u gibi addressof(&) operat�r�n�n operand� yap�yoruz.
			int foo(int);
			&foo; // -> int(*)(int, int)
			&strcat; // -> char* (*)(char*, const char*)
			 
	-Fonksiyonlarda da ayn� dizilerde ��rendi�imiz gibi 'array decay' ya da pointer to int conversion oluyor. Tabii fonksiyonlar i�in biz buna
		function to pointer conversion diyoruz.
		Mesela int arr[10]; dizisinin adresini &ar[0] yazmak ile sadece 'ar' yazmak aras�nda hi�bir fark yok.
		Ayn� durum fonksiyonlarda da ge�erli.
			int foo(void);
			foo(); // b�yle yazarak foo fonksiyonunu �a��r�yoruz. Asl�nda foo burada function to pointer conversion'a u�rayarak �u hali al�r.
			(&foo)(); -> bu foo() ile ayn� anlama geliyor. 
				Parantez(�ncelik operat�r�) i�ersine koyuyoruz e�er koymazsak () -> function call operat�r� �ncelik kazan�r.
					Bunun �n�ne ge�mek i�in �ncelik parantezine al�yoruz.

	-Fonksiyon �a�r� operat�r�n�n operand� ya bir fonksiyon olacak ya da bir fonksiyon adresi olmal�.
		( standart buna function designator diyor) () -> fonksiyon �a��rma operat�r�n�n operand� solunda kalan fonksiyonun ad�d�r.
			// o adreste bulunan fonksiyonun �a��r�lmas�n� sa�l�yor.

	int foo(int x){
		printf("int foo(int x) �a�r�ld� x = %d\n", x);
		return x * x
	}
	int baz(int);
	int bar(int);
	int main(void){
		int val = foo(12);
		int val2 = (&foo)(31); // addresof operat�r�n�n �nceli�i () fonksiyon �a�r� operat�r�nden d���k oldu�u i�in
								// �ncelik operat�r�n�n i�ine al�yoruz
		
		int (*fp)(int); // bu bir fonksiyon adresi tutan de�i�kenin tan�m�
		fp = &foo; // fp = foo;
		fp = &bar; // fp = bar;
		fp = &baz; // fp = baz; // Burada function to pointer conversion oluyor.
		// geri d�n�� de�eri (*de�i�ken ad�)(parametre t�r�); 

		size_t (*sp)(const char*) = strlen; // burada da strlen fonksiyonun adresini tutuyoruz.

	}
	// Neden bir fonksiyonun ad�n� function pointer variable dedi�imiz de�i�kenlerde tutal�m?
		-Fonksiyonun  adresini ba�ka bir de�i�kende tutarak, fonksiyonun adresini kullanarak o de�i�ekn vas�tas� ile fonksiyonu �a��rabiliriz.
		-
	void foo(void){
		printf("foo cagrildi");
	}
	void bar(void);
	void baz(void);
	void func(void (*fp)(void)){
		fp(); // burada mainden foo fonksiyonunun adresi g�nderildi�i i�in foo fonksiyonu �a��r�lacak.
	}
		// -Burada foo fonksiyonunun parametresi, geri d�n�� de�eri olmayan, parametre de�i�keni olmayan bir fonksiyonun adresi olmal�. 

	int main(void){
		void (*fp)(void) = &foo;

		fp(); // bu foo fonksiyonunu �a��r�r ve ekrana "foo cagrildi" yazd�r�r.
		//////////

		fp = &baz;
		fp(); // bu baz fonksiyonunu �a��r�r

		fp = &bar;
		fp(); // bu bar fonksiyonunu �a��r�r
		func(&foo); // foo fonksiyonunun adresini func fonksiyonuna parametre olarak g�nderdik.

	}
	- Bu neden bu kadar �nemli?
		Bir fonksiyonun i�levinin daha da esnek hale gelmesini sa�l�yoruz. ��inin bir k�sm�n� veya tamam�n�n nas�l yap�laca��n�
			fonksiyon de�il onu �a��ran fonksiyon karar veriyor.
		Bir fonksiyona ba�ka bir fonksiyonun adresini g�nderip, o fonksiyonu g�nderdi�imiz fonksiyonda �a��rd���m�zda asl�nda
			o fonksiyonu �A�IRTMI� oluyoruz. Bizim i�in fonksiyon adresini ald��� fonksiyonu �a��r�yor.

	////////////////////

	void func(int ch){
		if(isupper(ch)); // burada func fonksiyonu i�erisinde ne yap�laca��na kendi karar veriyor.
	}
	void func(int ch, void (*fptest)(int)){
		if(fptest(ch)); // burada ise func fonksiyonun i�erisinde nas�l bir fonksiyon �a��r�l�p nas�l bir i�lem yap�laca��na
							// fonksiyonu �a��ran ki�i karar veriyor
	}
	void print_chars(int (*fp)(int)){
		for(int i = 0; i < 128; i++)
			if(fp(i))
				printf("%c", i);
	}
	int main(void){
		print_chars(&isupper);
		print_chars(&islower);
		print_chars(&isalpha);
		print_chars(&ispunct);

		// g�r�ld��� �zere 1 fonksiyon yazd�k ve parametresini function pointer t�r�nden yapt�k.
			// bu sayede 1 fonksiyon yazarak birden fazla fonksiyonla o fonksiyona �a�r� yapabildik.
	}
	

*/
/*
bir function pointer� ile nesne pointer�n�n sizeof u ayn� olmayabilir,
ama t�m function ptr sizeoflar� kendi i�inde ayn�.
T�m obje pointerlarda kendi i�inde ayn� size de�erine sahip.*/
/*
	
	�DEV MEMMOVE KODUNU YAZ?


*/