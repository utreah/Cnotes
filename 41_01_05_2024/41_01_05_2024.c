#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdio.h>
#include <stddef.h>
//    VOID POINTERS
int main(void) {
	  void bir t�r.
		int, double nas�l birer t�r ise void'te �yle bir t�r.
			Fakat, void baz� k�s�tlamalara sahip;
		- Bir de�i�kenin t�r� void olamaz.
			void x = 10; // sentaks hatas�. Incomplete type'larla de�i�ken tan�mlanam�yor. �leride ��renicez incomplete type'�.
				void x[10]; // bu da sentaks hatas�.
		- Bir ifadenin t�r� void olabilir. 
			void foo(int a); // bir fonksiyonun geri d�n�� de�eri yok ise void olabilir.
		- T�r d�n��t�rme operat�r� olarak kullan�labilir.
			Mesela bir fonksiyondan gelen geri d�n�� de�erini discard etmek i�in kullan�labilir.
				(void)scanf("%d",&x); // atama yap�l�r fakat geri d�n�� de�eri kullan�lmaz. 'discard' edilir.
		-void t�r�nden ifadeler bir lojik ifadeye sahip olmad�klar� i�in bir de�er beklenilen yerlerde kullan�lamazlar.
			void func(int);
			if(func(45)) // burada kullan�lamazlar ��nk� if'in do�ru ya da yanl�� yere gidece�ini belirlemek i�in lojik ifadeye
				ihtiyac�m�z var.
			int b = func(23); // bu da sentaks hatas�.
		-Parametre parantezinin i�ine e�er parametre alm�yor ise void yaz�lmal�.
			int foo(void);
			int bar(); // fonksiyonun parametre de�i�kenleri hakk�nda bilgi verilmemi�. 
		

		VOID POINTERS
			-void* bir adres t�r�d�r ve de�i�kenin t�r� void* t�r�nden olabilir.
			-void ile void* ba�ka bir t�rd�r.
			-void* t�r� ile bir de�i�ken tan�mlayabiliriz, void ile bir de�i�ken tan�mlayamay�z.
			-void* bir object-pointer yani bir nesnenin adresini atayabiliriz.
				void* t�r�nden bir de�i�kene herhangi bir t�rden bir nesnenin adresini atayabiliriz.
					Mesela, int* t�r�nden bir pointera sadece int t�r�nden bir nesnenin adresi atanabilir.
						int ival = 10;
						double dval = 4.;
						char str[100] = "UGUR";
						void* vptr;
						vptr = &ival;
						vptr = &dval;
						vptr = str;
							Sentaks
			-Di�er adres t�rleri gibi 4 byte yer kaplar.
			-void* NULL pointer'da olabilir. 
				void* vptr = NULL;

			Yani
			void func(void * ptr); // Generic function
			bu fonksiyona istedi�imiz t�rden arg�man g�nderebiliriz.
			int *, double *.... hepsini �a�rabiliriz demek. Buna Generic function denir

			-void* t�r�nden tan�mlanm�� bir t�r �u �ekilde dereference edilemez.
				*vptr = -> bu hata verir.
				vptr[2];->
			-void* t�r�nde pointer aritmeti�inden yararlan�lamaz.
				int a[10] = { 0 };
				int* iptr = a;
				void* vptr = a;
				iptr + 2; // bu olur
				vptr + 2; // olmaz, sentaks hatas�.
				vptr - 2; // olmaz, sentaks hatas�.
				vptr++; vptr--; vptr - vptr1; bunlar�n hepsi sentaks hatas�
					Uzun laf�n k�sasi void* t�r� dereference edilemez, pointer aritmeti�inde kullan�lamaz.

			VOID* ile neler yap�labilir?

			int x = 10;
			-void* vptr = &x; // bu yap�labilir.
			-void* vptr = NULL; // bu yap�labilir.
				if(!p) // b�yle yap�larak NULL pointer� s�nayabiliriz.
			-if(vptr == &x) // yap�labilir.

			C ve CPP aras�nda void* kullan�m� konusunda inan�lmaz  bir fark var.
				1-)	
					int x = 10;
					int* iptr;
					void* vptr = &x; 
					// C'de T* t�r�nden void* t�r�ne �rt�l�(implicit) d�n���m var.
						// void* t�r�n�n var olma nedeni herhangi bir adres t�r�n� tutabilmeleri	
					iptr = vptr; // void* t�r�nden int* t�r�ne d�n���m var. Bu C'de ge�erli
						// CPP'de void* t�r�nden T* t�r�ne �rt�l� d�n���m yok. Bu y�zden bu kod CPP'de sentaks hatas�.
					iptr = (int*)vptr; // Buras� cpp'de legal. Sentaks hatas� yok. Ancak bu �ekilde void* t�r�nden T* 
						// t�r�ne d�n���m yapabiliriz.
				2-)2 farkl� yakla��m var bu yukar�daki kod i�in.
					a) Ya implicit conversion'a izin veriliyor
					b) Ya da anla��lmas� daha kolay olmas� ve CPP'de de ge�erli olmas� i�in explicit conversion yap�l�yor.
						iptr = (int*)vptr; // gibi
			-void* t�r�ne her de�eri atayamay�z.
				int x = 10;
				void* vptr = x; // bu hatal�. void* olmas� 'her' nesnenin atanabilece�i anlam�na gelmiyor. // t�r uyu�mazl��� var
					// sadece herhangi t�rden bir 'ADRES' atanabilir.


			Generic Programming: Generic burada t�rden ba��ms�z anlam�na geliyor.
				T�rden ba��ms�z kodlama: Mesela iki de�erin swap edilece�i bir fonksiyon yazaca��z. C CPP gibi dillerde
					bunlar�n t�rleri oluyor. 2 tane int nesneyi takas etmek i�in parametresi int* olan 2 tane parametre de�i�keni
						yaz�lmal�. Bu fonksiyonu double* t�rden bir nesne i�in kullanmay�z onlar i�in ayr� fonksiyon yapmam�z gerekir.
					Generic function burada devreye giriyor. Birden fazla farkl� t�rde nesneye hizmet veriyor.
				C'de generic programming yapmak i�in �yle bir fonksiyon yazmal�y�z ki parametre de�i�keni 
						herhangi bir nesne adresi alabilecek olan void* t�r�nden olmal�.
				Template: Bu CPP'de var. CPP'de 2 yol var kod yazd�rmak i�in. Biri C ile ayn� di�eri ise derleyiciye kod yazd�rma.
					CPP kursunda detayl� g�recez.
				
				Parametresi void* t�r�nden bir fonksiyon g�rd���m�zde;
					a) D�k�mantasyon olmasa bile o fonksiyonun herhangi bir t�re kar��l�k gelebilece�ini buna binayen
						bunun generic bir kodlama oldu�unu
					b) Birden fazla t�re hizmet verebilece�ini, anl�yoruz.
					//////////////////////////////////

						// *vp; -> bunun sentaks hatas� oldu�unu ��renmi�tik zaten.
						// void* parametreli fonksiyonlar
						//-Gelen adresteki nesnenin t�r�n� bilmiyor
						//-Parametreye gelen de�i�keni bytelardan olu�an bir dizi gibi ele al�r.
						//-Fonksiyon t�r� bilmeyecke ama fonksiyonu �a��ran ki�i bilecek. �a��ran�n sorumlulu�unda
						//-Generic fonksiyonlar byte byte i�lem yapt���ndan dolay� parametre olarak adres de�i�kenleri
							// haricinde birde o g�nderilen adresin sizeof de�erini parametre de�i�kenine al�r.
								// ��nk� boyutunu bilmedi�imiz bir �eyde byte-byte takas yapamay�z.

						// Bytelar� kar��l�kl� olarak takas etmek i�in byte seviyesinde i�lem yapmam�z gerek.
							/* bunun i�inde vp1 ve vp2'yi char* t�r�ne cast etmeliyiz. (char 1 byte boyutunda oldu�undan
								de�eri 1 artt�rd���m�zda dizinin di�er byte'�n� g�sterir, bu y�zden char/char* kullan�yoruz)*/
						//-C'de herhangi bir diziyi char veya unsigned char'm�� gibi kullanabiliriz.
						//-Herhangi bir nesne t�r�nden char* t�r�ne UB olmadan sentaks hatas� olmadan s�k�nt�s�z d�n���m yap�labilir.
							// ama mesela float* t�r�nden int* t�r�ne yapmak sentaks hatas� olmasa da UB.

					void gswap(void* vp1, void* vp2, size_t size){
						char* p1 = (char*)vp1;
						char* p2 = vp2;
						// Yukar�daki iki atama i�leminde de C dilinde s�k�nt� yok. Line 122'deki ifade de implicit
							// type conversion oldu�u i�in �al���r. Ama okuyan ki�inin i�ini kolayla�t�rmak i�in
								// C dilinde char* t�r�ne cast edebiliriz. CPP'de zorunluyuz di�er t�rl� sentaks hatas�.
						//char t�r�n� se�tik ��nk� char'da 1 byte olma garantisi var. float* int* gibi bir �ey olsayd�
							// takas kullan�lan t�r�n derleyicideki byte de�erine g�re iki�er veya d�rder d�rder olurdu bu da do�ru de�il. UB.
							// tek do�ru davran�� char* kullanmak.
						while(size--){
							char temp = *p1;
							*p1++ = *p2;
							*p2++ = temp;
						}
						
					}
					int main(void){
						int i1 = 345, i2 = 567;
						double d1 = 5.6 , d2 = 6.25;
						int a[5] = {1, 2, 3, 4, 5};
						int b[5] = {-10, -20, -30, -40, -50};
						gswap(&i1, &i2, sizeof(int)); // ya da sizeof(i1);
						gswap(&d1, &d2, sizeof(double)); // ya da sizeof(d1);
						gswap(a, b, sizeof(int[5])); // ya da sizeof(a);

					}

///////////////////////////////////////////////////////////////////////////////////////////
#define SIZE 100
					void greverse(void* vp, size_t size, size_t sz)
					{
						char* p = (char*)vp;
						for (size_t i = 0; i < size / 2; i++) {
							// p + i * sz; -> �OK �NEML�! Diyelim ki burada tersine �evirdi�imiz dizinin t�r� int 4 byte yer kapl�yor olsun
								// i�lem char* t�r�nde yap�ld��� i�in 1 byte 1 byte yap�lacak bu da s�k�nt� ��nk� t�r�m�z int oldu�u i�in
									// 4 byte atlayarak yap�lmal�. Bizde i * sz yaparak her seferinde o t�r�n bellekte kaplad��� yer kadar
									// ilerliyoruz. yani int bir dizi i�in her seferinde bellekte 4byte ilerliyoruz.
									//bellekte ne kadar ileri gidilece�ine fonksiyona parametre olarak ald���m�z size_t sz(sizeof) de�erinden
									// anl�yoruz.
							// p + (size - 1 - i) * sz -> buras� da son elemana eri�mek i�in. 
							gswap(p + i * sz, p + (size - i - 1) * sz, sz); // daha �nce yazd���m�z gswap fonksiyonunu �a��r�yoruz.
								// gswapte t�rden ba��ms�z olarak d�nd�r�r.
						}
					}
					int main(void) {
						int a[SIZE];
						randomize();
						set_array_random();
						print_array();
						greverse(a, SIZE, sizeof(int));
					}

			// Generic programlama da �ok s�k kullan�lan standart k�t�phanenin fonksiyonlar�. Bu fonksiyonlar t�rden ba��ms�z
					// Bu fonksiyonlar string.h k�t�phanesinde bulunuyor ve sistem programlamada �ok�a kullan�l�yor.
						// Her ne kadar string.h k�t�phanesinde olsalar da yaz�lar(NTBS) �zerinde i�lem yapan fonksiyonlar de�il
				-memset() -> bellek blo�una tam say� yazar.
				- memcpy() ->  bir bellek blo�unu bir yerden bir yere kopyal�yor.
				- memmove() -> bir bellek blo�unu bir yerden bir yere kopyal�yor.
				- memchr() ->  bir bellek blo�u i�erisinde byte ar�yor.
				- memcmp() ->  bir bellek blo�u i�erisinde k�yaslama yapar.
				- Bu fonksiyonlar�n en az 1 parametresi void* ve  bir tanesi de size_t size;
			str ile ba�layan standart fonksiyonlar yaz�n�n adresini parametre olarak al�yor ve yaz�n�n sonunda '\0' oldu�unu kabul
					ederek i�lem yap�yor.
			mem -> bunlar void* parametreli fonksiyonlar. NTBS vs ile i�leri yok. 
		
}

void* my_memset(void* vp, int val, size_t size) {
	// void* vp = i�lem yap�lacak nesnenin adresi
	// int val = yaz�lacak de�er
	// size_t size = ka� bytel�k belle�e set edilecek
	// geri d�n�� de�eri fonksiyona g�nderilen adres
	char* p = (char*)vp;
	while (size--)
		*p++ = val;

	return vp;
}

int main(void)
{
	int x = 10013412;
	printf("%d\n", x);

	memset(&x, 0, sizeof(int)); // burada x'in adresini, x nesnesinin bytelar�na yaz�lacak de�er, ve x'in t�r�n�n bellekte kaplad��� boyut.
		// nesnenin her bir bellek bloklar�na 0 de�erini yazacak. 

	int arr[100];
	randomize();
	set_array_random(arr, 100);
	print_array(arr, 100);
	memset(arr, 0, sizeof(arr)); // dizinin b�t�n elemanlar�na 0 de�erini yazd�rd�k. sizeof'a operand olarak arr yaz�yoruz.
									// dizinin boyutunu atmak i�in. E�er *arr yazarsak 4 olur bize t�m dizinin boyutu laz�m.
	memset(arr + 20, 0, 20 * sizeof(*arr)); // burada ise dizinin 20. eleman�ndan ba�layarak, 20 elemana 0 yazd�r�yoruz.

	char str[] = "AAAABBBBCCCCDDDD";
	puts(str); 
	memset(str + 4, 'X', 4); // B'nin ba�lad��� yerden ba�layarak her bir byte X yaz�l�yor.
	puts(str); // output : AAAAXXXXBBBBCCCCDDDD
	///////////////////
	int x;
	memset(&x, 255, 4); // memset i�aretli char 1 byte olarak yapt��� ve 255'te i�aretli char t�r�n�n s�n�rlar� i�erisinde
							// olmad���ndan dolay� 1000 0001 -> x -1 de�erini al�r.
						// 111 1111 1111 1111 1111 1111 1111 1111 -> -1
	memset(&x, 1, 4); // bu da her byte'�n ilk bitine 1 yazar(��nk� o 1 de�erini yazd�r�yoruz 0000 0001)
						// i�lem sonunda ��yle bir g�r�nt� ortaya ��kar;
						// 0000 0001 0000 0001 0000 0001 0000 0001 -> sonu� : 16843009 olur;
	// Bir belle�in b�t�n bytelar�n� 0'a set etmek o belle�i 'clear' etti�imiz anlam�na geliyor.

	// E�er bir de�i�kenin belirli byte'�n� s�f�rlamak istiyorsak o de�i�keni �nce char*'a cast ediyoruz pointer aritmeti�inden faydalanmak
		// i�in.
	memset((char*)&x + 3, 0, 1); // burada x nesnesinin 3. byte�n� s�f�rl�yoruz. veya �u �ekilde de yazabiliriz
	*((char*)&x + 3) = 0; //yukar�daki expr statement� ile bu ayn� anlama geliyor. x'� char* olarak cast ediyoruz. 3. byte'�n adresini 
		// dereference edip 0 de�erini at�yoruz.

	/////////////////////////////////////////////////////////////////////

	// Endiannes
	// E�er d���k anlaml� byte d���k de�erli adreste, y�ksek anlaml� byte y�ksek adreste ise buna
		// little endian denir.
	4800	0000 0001
	4801	0000 0000
	4802	0000 0000
	4803	0000 0000
	// E�er d���k anlaml� byte b�y�k de�erli adreste, b�y�k anlaml� byte d���k adreste ise buna
		// big endian denir.
	4800	0000 0000
	4801	0000 0000
	4802	0000 0000
	4803	0000 0001
;
	// Say�lar�n bellekte nas�l tutuldu�u i�lemciye ba�l�. Mesela intel tarz� mimari little endian, motorola ise big endian.
		// ARM'ler ise little veya big olarak konfig�re edilebiliyor.
	/*
		int x = 1;
		char* p = (char*)&x;

		if(*p) // de�eri ekrana yazd�rsayd�k 1 yazard�
			printf("little endian");
		else
		
		///////////////////// -> hoca yukar�daki kodda s�k�nt� yok dedi ama daha iyi bir yolu varm��(yaz�m a��s�ndan)
		if(*(char*)&x)
			printf("little endian");
		else
			printf("big endian");
	
		x = 2048;
		char* p = (char*)&x;
		if(*p) // e�er *p �eklinde derefence eder isem ekrana 0 yazd�r�r. ��nk� 2048 de�eri i�in �u anda 2. bytetay�z.
		if(*(p+1)) // ekrana 2048 de�il, 8 yazd�r�r sebebi ise 0000 1000 olmas�ndan dolay�.
						// sonu�ta ele byte byte al�yoruz ve 2. byte olsa bile 1 bytem�� gibi g�r�yor ve 8 yazd�r�yor ekrana.
		
	*/
	/////////////////////////////////////////////
	// void* memcpy(void* pdest, const void* psrc, size_t size); // bir kaynak belle�in blo�unu hedef belle�e yappppppp��t�r�yor.

	void* my_memcpy(void* vpdest, const void* psrc, size_t size){
		char* pdest = (char*)vpdest;
		const char* psrc = (const char*)vpsrc;
		while (size--)
			pdest++ = psrc++;

		return vpdest;
	}

	int main(void) {
		int x, y;
		printf("bir tam sayi giriniz:");
		scanf("%d", &x);

		y = x; // x'in de�erini y nesnesine atad�k.
		memcpy(&y, &x, sizeof(int)); // x'in de�erini y nesnesine kopyalad�k ama memcpy ile
		printf("%d", y);
		///////////////////////////////
		int a[SIZE];
		int b[SIZE];
		randomize();
		set_array_random(a, SIZE);
		print_array(a, SIZE);
		print_array(b, SIZE);
		for (int i = 0; i < SIZE; i++)
			b[i] = a[i]; // b�yle yaparak b'ye a'y� kopyal�yoruz.
		
		memcpy(b, a, sizeof(a)); // b�yle yaparakta a'y� b'ye kopyalayabiliriz
		//////////////////////////////////

		int idx_a, idx_b, n;
		printf("a indeks? : ");
		scanf("%d", &idx_a);
		printf("b indeks? : ");
		scanf("%d", &idx_b);
		printf("Ka� eleman kopyalanacak? : ");
		scanf("%d", &n);
		memcpy(b + idx_b, a + idx_a, sizeof(*a) * n);
	}

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

}