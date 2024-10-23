/*Storage Specifiers*/

/*
	Volatile(oynak (balina)): Bu keyword ile bir point de�i�keni nitelenebiliyor. Bu keyword ile nitelenen nesnelerin program d��� kaynaklar taraf�ndan m�dahaleler ile de�i�tiribilece�inin
		bilgisi kodu okuyan ki�iye ve derleyiciye veriliyor. D�� g��lerin ma�as� haline geliyor yani.
	Niye bunu kullan�yoruz?
		Sebebi compiler'�n compile timeda �retece�i kodun do�ru olmas�n� sa�lamak. E�er, derleyici nesnenin de�erinin de�i�medi�ini koda bakarak g�r�rse
			o nesnenin bellekten de�erini okumak i�in kod �retmemesi durumu var. Diyelim ki ival adl� bir de�i�kenimiz var. Bu de�i�keni olu�turduk ama projenin hi�bir yerinde
				de�erini de�i�tirmedik. Derleyici bunu g�rd���nde optimizasyon i�in ival'in bellekten de�erini okumak i�in bir kod �retmeyecek. 

	volatile int x = 1000; // global namespace
	int main(void){
		while(x != 0){ // e�er x, volatile keyword� ile define edilmese idi derleyici bu while deyimini while(1) olarak kabul edebilirdi. ��nk� x'in de�erinin de�i�ti�i bir ihtimal yoktu.
			//.. code		// volatile kullanarak, d��ar�dan m�dahale olabilece�i bilgisini veriyoruz.
		}
	}


	int x = 10;
	int main(void){
		volatile int* p = &x; // pointer to volatile int 
		*p; // volatile olan bu. 'p;' de�il  // *p volatile oldu�u i�in pointer'�n g�sterdi�i nesnenin de�erini her seferinde bellekten gidip get etmesi anlam�na geliyor.
		int* volatile p = &x; // volatile pointer to int // p'nin de�erini her �a��rd���mda bellekten get edeceksin demek bu.
	}

	NOT: E�er volatile asterisk(*) atomunun solunda ise, *p yani Type(int mesela) volatile olur ve de�eri bellekten get edilir.
		 E�er volatile asterisk(*) atomunun sa��nda ise, p yani g�sterdi�i adres ne ise bellekten o de�er get edilir. 
			Bellekten get edilme durumu da, o nesneye her eri�im yap�ld���nda belle�e gidip de�erini sorma durumu. Optimizasyon olmad��� i�in b�yle.
---------------------------------------------------
	volatile const int x = 10; // burada ise x nesnesinin bu proje/kod i�erisinde de�i�tirilemeyece�i anlam�na geliyor. 
									//volatile ise d��ar�dan de�i�tirilebilece�ini s�yl�yor. Projenin herhangi bir yerinde eri�im sa�land���nda x'in de�eri  bellekten her seferinde get edilecek.

---------------------------------------------------
int x = 10;
int main(void){
	int* ptr = &x;
	volatile int* p = ptr; // burada d�n���m de s�k�nt� yok.
	/////////
	volatile int* volptr = &x;
	int* ptr2 = volptr; // burada �rt�l� d�n���m yok uyar� mesaj� verecek derleyici.
		const int* -> int* d�n���m� nas�l yanl��sa volatile int* -> int* d�n���m� de yanl��.


}
---------------------------------------------------
restrict (C99): restrict keyword� ile nitelenmi� pointer de�i�kenlerinin unique olmas�n� sa�l�yor. Yani ba�ka bir pointer nesnesi, restrict ile tan�mlanm�� bir pointer de�i�keninin
	g�sterdi�i adresi g�stermeyece�inin garantisini veriyor. Bu garantinin �i�nenmesi ile Undefined Behaviour olu�ur.

	Volatile, const gibi keywordlar hem pointer'� hem de g�sterdi�i nesneyi nitelerken restrict keyword� sadece pointerin kendisini niteliyor.
	
	restrict keyword� ile tan�mlanan pointerlara restrict pointer deniyor.
		En �ok kar��m�za ��kaca�� yer fonksiyonlar�n parametre de�i�kenleri.
	restrict, asterisk atomundan sonra kullan�lmak zorunda e�er �nce kullan�l�rsa sentaks hatas�.

	void func(int* restrict p); // p bir restrict pointer
	int* restrict x = &var;

	int restrict *ptr; // sentaks hatas�
	Pointerlar�n her ikisininde ayn� nesneye eri�mesine pointer-alliasing denir.
	void func(int* px, int* py, int* restrict pz)
	{
	}

	burada px ve py nin pz nin g�sterdi�i nesneyi g�sterme ihtimali yok.bunu sa�l�yor.
		bu derleyicinin daha iyi optimizasyon yapmas�n� sa�l�yor.
	e�er px = pz; yap�l�rsa bu bir UNDEFINED BAHAVIOR	

	�R:
	void func(int* px, int* py, int* restrict pz)
	{
		*px += *pz;

		// *pz ye eri� ve onu registerda tut
		// *pz ye tekrar eri�mek yerine onu registerdaki de�eri ile kullan.
		//restrict olmasayd� px, pz yi g�steriyor olabilirdi ve *px de�i�ince *pz de de�i�irdi.
		// bu de�eride get etmek i�in tekrar memory ye eri�mek gerekirdi. restrict ile bunu
		// ortadan kald�r�yoruz. sadece pz bu de�eri tutabilir ve eri�ebilir.
		//bu �ekilde compiler optimizasyon yap�yor.

		*py += *pz;

	}
	CPPREFERENCE SERGEY ZUBKOV un �rne�i

	void f(int n, int * restrict p, const int * restrict q)
	{
		while(n-- > 0)
			*p++ = *q++; // none of the objects modified through *p is the same
						 // as any of the objects read through *q
						 // compiler free to optimize, vectorize, page map, etc.
	}
	void g(void)
	{
		extern int d[100];
		f(50, d + 50, d); // OK. Kesi�miyor.birincisi d[49] da bitiyor ikinci dizi ise d[50] den ba�l�yor.
							// overlapped blocklar yok.UB DE��L.

		f(50, d + 1, d); // Undefined behavior: d[1] is accessed through both p and q in f
							//d[1] de kesi�iyorlar. UNDEFINED BEHAVIOR.
	}
	56:00
*/