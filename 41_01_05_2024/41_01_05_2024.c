#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdio.h>
#include <stddef.h>
//    VOID POINTERS
int main(void) {
	  void bir tür.
		int, double nasýl birer tür ise void'te öyle bir tür.
			Fakat, void bazý kýsýtlamalara sahip;
		- Bir deðiþkenin türü void olamaz.
			void x = 10; // sentaks hatasý. Incomplete type'larla deðiþken tanýmlanamýyor. Ýleride öðrenicez incomplete type'ý.
				void x[10]; // bu da sentaks hatasý.
		- Bir ifadenin türü void olabilir. 
			void foo(int a); // bir fonksiyonun geri dönüþ deðeri yok ise void olabilir.
		- Tür dönüþtürme operatörü olarak kullanýlabilir.
			Mesela bir fonksiyondan gelen geri dönüþ deðerini discard etmek için kullanýlabilir.
				(void)scanf("%d",&x); // atama yapýlýr fakat geri dönüþ deðeri kullanýlmaz. 'discard' edilir.
		-void türünden ifadeler bir lojik ifadeye sahip olmadýklarý için bir deðer beklenilen yerlerde kullanýlamazlar.
			void func(int);
			if(func(45)) // burada kullanýlamazlar çünkü if'in doðru ya da yanlýþ yere gideceðini belirlemek için lojik ifadeye
				ihtiyacýmýz var.
			int b = func(23); // bu da sentaks hatasý.
		-Parametre parantezinin içine eðer parametre almýyor ise void yazýlmalý.
			int foo(void);
			int bar(); // fonksiyonun parametre deðiþkenleri hakkýnda bilgi verilmemiþ. 
		

		VOID POINTERS
			-void* bir adres türüdür ve deðiþkenin türü void* türünden olabilir.
			-void ile void* baþka bir türdür.
			-void* türü ile bir deðiþken tanýmlayabiliriz, void ile bir deðiþken tanýmlayamayýz.
			-void* bir object-pointer yani bir nesnenin adresini atayabiliriz.
				void* türünden bir deðiþkene herhangi bir türden bir nesnenin adresini atayabiliriz.
					Mesela, int* türünden bir pointera sadece int türünden bir nesnenin adresi atanabilir.
						int ival = 10;
						double dval = 4.;
						char str[100] = "UGUR";
						void* vptr;
						vptr = &ival;
						vptr = &dval;
						vptr = str;
							Sentaks
			-Diðer adres türleri gibi 4 byte yer kaplar.
			-void* NULL pointer'da olabilir. 
				void* vptr = NULL;

			Yani
			void func(void * ptr); // Generic function
			bu fonksiyona istediðimiz türden argüman gönderebiliriz.
			int *, double *.... hepsini çaýrabiliriz demek. Buna Generic function denir

			-void* türünden tanýmlanmýþ bir tür þu þekilde dereference edilemez.
				*vptr = -> bu hata verir.
				vptr[2];->
			-void* türünde pointer aritmetiðinden yararlanýlamaz.
				int a[10] = { 0 };
				int* iptr = a;
				void* vptr = a;
				iptr + 2; // bu olur
				vptr + 2; // olmaz, sentaks hatasý.
				vptr - 2; // olmaz, sentaks hatasý.
				vptr++; vptr--; vptr - vptr1; bunlarýn hepsi sentaks hatasý
					Uzun lafýn kýsasi void* türü dereference edilemez, pointer aritmetiðinde kullanýlamaz.

			VOID* ile neler yapýlabilir?

			int x = 10;
			-void* vptr = &x; // bu yapýlabilir.
			-void* vptr = NULL; // bu yapýlabilir.
				if(!p) // böyle yapýlarak NULL pointerý sýnayabiliriz.
			-if(vptr == &x) // yapýlabilir.

			C ve CPP arasýnda void* kullanýmý konusunda inanýlmaz  bir fark var.
				1-)	
					int x = 10;
					int* iptr;
					void* vptr = &x; 
					// C'de T* türünden void* türüne örtülü(implicit) dönüþüm var.
						// void* türünün var olma nedeni herhangi bir adres türünü tutabilmeleri	
					iptr = vptr; // void* türünden int* türüne dönüþüm var. Bu C'de geçerli
						// CPP'de void* türünden T* türüne örtülü dönüþüm yok. Bu yüzden bu kod CPP'de sentaks hatasý.
					iptr = (int*)vptr; // Burasý cpp'de legal. Sentaks hatasý yok. Ancak bu þekilde void* türünden T* 
						// türüne dönüþüm yapabiliriz.
				2-)2 farklý yaklaþým var bu yukarýdaki kod için.
					a) Ya implicit conversion'a izin veriliyor
					b) Ya da anlaþýlmasý daha kolay olmasý ve CPP'de de geçerli olmasý için explicit conversion yapýlýyor.
						iptr = (int*)vptr; // gibi
			-void* türüne her deðeri atayamayýz.
				int x = 10;
				void* vptr = x; // bu hatalý. void* olmasý 'her' nesnenin atanabileceði anlamýna gelmiyor. // tür uyuþmazlýðý var
					// sadece herhangi türden bir 'ADRES' atanabilir.


			Generic Programming: Generic burada türden baðýmsýz anlamýna geliyor.
				Türden baðýmsýz kodlama: Mesela iki deðerin swap edileceði bir fonksiyon yazacaðýz. C CPP gibi dillerde
					bunlarýn türleri oluyor. 2 tane int nesneyi takas etmek için parametresi int* olan 2 tane parametre deðiþkeni
						yazýlmalý. Bu fonksiyonu double* türden bir nesne için kullanmayýz onlar için ayrý fonksiyon yapmamýz gerekir.
					Generic function burada devreye giriyor. Birden fazla farklý türde nesneye hizmet veriyor.
				C'de generic programming yapmak için öyle bir fonksiyon yazmalýyýz ki parametre deðiþkeni 
						herhangi bir nesne adresi alabilecek olan void* türünden olmalý.
				Template: Bu CPP'de var. CPP'de 2 yol var kod yazdýrmak için. Biri C ile ayný diðeri ise derleyiciye kod yazdýrma.
					CPP kursunda detaylý görecez.
				
				Parametresi void* türünden bir fonksiyon gördüðümüzde;
					a) Dökümantasyon olmasa bile o fonksiyonun herhangi bir türe karþýlýk gelebileceðini buna binayen
						bunun generic bir kodlama olduðunu
					b) Birden fazla türe hizmet verebileceðini, anlýyoruz.
					//////////////////////////////////

						// *vp; -> bunun sentaks hatasý olduðunu öðrenmiþtik zaten.
						// void* parametreli fonksiyonlar
						//-Gelen adresteki nesnenin türünü bilmiyor
						//-Parametreye gelen deðiþkeni bytelardan oluþan bir dizi gibi ele alýr.
						//-Fonksiyon türü bilmeyecke ama fonksiyonu çaðýran kiþi bilecek. Çaðýranýn sorumluluðunda
						//-Generic fonksiyonlar byte byte iþlem yaptýðýndan dolayý parametre olarak adres deðiþkenleri
							// haricinde birde o gönderilen adresin sizeof deðerini parametre deðiþkenine alýr.
								// Çünkü boyutunu bilmediðimiz bir þeyde byte-byte takas yapamayýz.

						// Bytelarý karþýlýklý olarak takas etmek için byte seviyesinde iþlem yapmamýz gerek.
							/* bunun içinde vp1 ve vp2'yi char* türüne cast etmeliyiz. (char 1 byte boyutunda olduðundan
								deðeri 1 arttýrdýðýmýzda dizinin diðer byte'ýný gösterir, bu yüzden char/char* kullanýyoruz)*/
						//-C'de herhangi bir diziyi char veya unsigned char'mýþ gibi kullanabiliriz.
						//-Herhangi bir nesne türünden char* türüne UB olmadan sentaks hatasý olmadan sýkýntýsýz dönüþüm yapýlabilir.
							// ama mesela float* türünden int* türüne yapmak sentaks hatasý olmasa da UB.

					void gswap(void* vp1, void* vp2, size_t size){
						char* p1 = (char*)vp1;
						char* p2 = vp2;
						// Yukarýdaki iki atama iþleminde de C dilinde sýkýntý yok. Line 122'deki ifade de implicit
							// type conversion olduðu için çalýþýr. Ama okuyan kiþinin iþini kolaylaþtýrmak için
								// C dilinde char* türüne cast edebiliriz. CPP'de zorunluyuz diðer türlü sentaks hatasý.
						//char türünü seçtik çünkü char'da 1 byte olma garantisi var. float* int* gibi bir þey olsaydý
							// takas kullanýlan türün derleyicideki byte deðerine göre ikiþer veya dörder dörder olurdu bu da doðru deðil. UB.
							// tek doðru davranýþ char* kullanmak.
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
							// p + i * sz; -> ÇOK ÖNEMLÝ! Diyelim ki burada tersine çevirdiðimiz dizinin türü int 4 byte yer kaplýyor olsun
								// iþlem char* türünde yapýldýðý için 1 byte 1 byte yapýlacak bu da sýkýntý çünkü türümüz int olduðu için
									// 4 byte atlayarak yapýlmalý. Bizde i * sz yaparak her seferinde o türün bellekte kapladýðý yer kadar
									// ilerliyoruz. yani int bir dizi için her seferinde bellekte 4byte ilerliyoruz.
									//bellekte ne kadar ileri gidileceðine fonksiyona parametre olarak aldýðýmýz size_t sz(sizeof) deðerinden
									// anlýyoruz.
							// p + (size - 1 - i) * sz -> burasý da son elemana eriþmek için. 
							gswap(p + i * sz, p + (size - i - 1) * sz, sz); // daha önce yazdýðýmýz gswap fonksiyonunu çaðýrýyoruz.
								// gswapte türden baðýmsýz olarak döndürür.
						}
					}
					int main(void) {
						int a[SIZE];
						randomize();
						set_array_random();
						print_array();
						greverse(a, SIZE, sizeof(int));
					}

			// Generic programlama da çok sýk kullanýlan standart kütüphanenin fonksiyonlarý. Bu fonksiyonlar türden baðýmsýz
					// Bu fonksiyonlar string.h kütüphanesinde bulunuyor ve sistem programlamada çokça kullanýlýyor.
						// Her ne kadar string.h kütüphanesinde olsalar da yazýlar(NTBS) üzerinde iþlem yapan fonksiyonlar deðil
				-memset() -> bellek bloðuna tam sayý yazar.
				- memcpy() ->  bir bellek bloðunu bir yerden bir yere kopyalýyor.
				- memmove() -> bir bellek bloðunu bir yerden bir yere kopyalýyor.
				- memchr() ->  bir bellek bloðu içerisinde byte arýyor.
				- memcmp() ->  bir bellek bloðu içerisinde kýyaslama yapar.
				- Bu fonksiyonlarýn en az 1 parametresi void* ve  bir tanesi de size_t size;
			str ile baþlayan standart fonksiyonlar yazýnýn adresini parametre olarak alýyor ve yazýnýn sonunda '\0' olduðunu kabul
					ederek iþlem yapýyor.
			mem -> bunlar void* parametreli fonksiyonlar. NTBS vs ile iþleri yok. 
		
}

void* my_memset(void* vp, int val, size_t size) {
	// void* vp = iþlem yapýlacak nesnenin adresi
	// int val = yazýlacak deðer
	// size_t size = kaç bytelýk belleðe set edilecek
	// geri dönüþ deðeri fonksiyona gönderilen adres
	char* p = (char*)vp;
	while (size--)
		*p++ = val;

	return vp;
}

int main(void)
{
	int x = 10013412;
	printf("%d\n", x);

	memset(&x, 0, sizeof(int)); // burada x'in adresini, x nesnesinin bytelarýna yazýlacak deðer, ve x'in türünün bellekte kapladýðý boyut.
		// nesnenin her bir bellek bloklarýna 0 deðerini yazacak. 

	int arr[100];
	randomize();
	set_array_random(arr, 100);
	print_array(arr, 100);
	memset(arr, 0, sizeof(arr)); // dizinin bütün elemanlarýna 0 deðerini yazdýrdýk. sizeof'a operand olarak arr yazýyoruz.
									// dizinin boyutunu atmak için. Eðer *arr yazarsak 4 olur bize tüm dizinin boyutu lazým.
	memset(arr + 20, 0, 20 * sizeof(*arr)); // burada ise dizinin 20. elemanýndan baþlayarak, 20 elemana 0 yazdýrýyoruz.

	char str[] = "AAAABBBBCCCCDDDD";
	puts(str); 
	memset(str + 4, 'X', 4); // B'nin baþladýðý yerden baþlayarak her bir byte X yazýlýyor.
	puts(str); // output : AAAAXXXXBBBBCCCCDDDD
	///////////////////
	int x;
	memset(&x, 255, 4); // memset iþaretli char 1 byte olarak yaptýðý ve 255'te iþaretli char türünün sýnýrlarý içerisinde
							// olmadýðýndan dolayý 1000 0001 -> x -1 deðerini alýr.
						// 111 1111 1111 1111 1111 1111 1111 1111 -> -1
	memset(&x, 1, 4); // bu da her byte'ýn ilk bitine 1 yazar(çünkü o 1 deðerini yazdýrýyoruz 0000 0001)
						// iþlem sonunda þöyle bir görüntü ortaya çýkar;
						// 0000 0001 0000 0001 0000 0001 0000 0001 -> sonuç : 16843009 olur;
	// Bir belleðin bütün bytelarýný 0'a set etmek o belleði 'clear' ettiðimiz anlamýna geliyor.

	// Eðer bir deðiþkenin belirli byte'ýný sýfýrlamak istiyorsak o deðiþkeni önce char*'a cast ediyoruz pointer aritmetiðinden faydalanmak
		// için.
	memset((char*)&x + 3, 0, 1); // burada x nesnesinin 3. byteýný sýfýrlýyoruz. veya þu þekilde de yazabiliriz
	*((char*)&x + 3) = 0; //yukarýdaki expr statementý ile bu ayný anlama geliyor. x'ý char* olarak cast ediyoruz. 3. byte'ýn adresini 
		// dereference edip 0 deðerini atýyoruz.

	/////////////////////////////////////////////////////////////////////

	// Endiannes
	// Eðer düþük anlamlý byte düþük deðerli adreste, yüksek anlamlý byte yüksek adreste ise buna
		// little endian denir.
	4800	0000 0001
	4801	0000 0000
	4802	0000 0000
	4803	0000 0000
	// Eðer düþük anlamlý byte büyük deðerli adreste, büyük anlamlý byte düþük adreste ise buna
		// big endian denir.
	4800	0000 0000
	4801	0000 0000
	4802	0000 0000
	4803	0000 0001
;
	// Sayýlarýn bellekte nasýl tutulduðu iþlemciye baðlý. Mesela intel tarzý mimari little endian, motorola ise big endian.
		// ARM'ler ise little veya big olarak konfigüre edilebiliyor.
	/*
		int x = 1;
		char* p = (char*)&x;

		if(*p) // deðeri ekrana yazdýrsaydýk 1 yazardý
			printf("little endian");
		else
		
		///////////////////// -> hoca yukarýdaki kodda sýkýntý yok dedi ama daha iyi bir yolu varmýþ(yazým açýsýndan)
		if(*(char*)&x)
			printf("little endian");
		else
			printf("big endian");
	
		x = 2048;
		char* p = (char*)&x;
		if(*p) // eðer *p þeklinde derefence eder isem ekrana 0 yazdýrýr. Çünkü 2048 deðeri için þu anda 2. bytetayýz.
		if(*(p+1)) // ekrana 2048 deðil, 8 yazdýrýr sebebi ise 0000 1000 olmasýndan dolayý.
						// sonuçta ele byte byte alýyoruz ve 2. byte olsa bile 1 bytemýþ gibi görüyor ve 8 yazdýrýyor ekrana.
		
	*/
	/////////////////////////////////////////////
	// void* memcpy(void* pdest, const void* psrc, size_t size); // bir kaynak belleðin bloðunu hedef belleðe yapppppppýþtýrýyor.

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

		y = x; // x'in deðerini y nesnesine atadýk.
		memcpy(&y, &x, sizeof(int)); // x'in deðerini y nesnesine kopyaladýk ama memcpy ile
		printf("%d", y);
		///////////////////////////////
		int a[SIZE];
		int b[SIZE];
		randomize();
		set_array_random(a, SIZE);
		print_array(a, SIZE);
		print_array(b, SIZE);
		for (int i = 0; i < SIZE; i++)
			b[i] = a[i]; // böyle yaparak b'ye a'yý kopyalýyoruz.
		
		memcpy(b, a, sizeof(a)); // böyle yaparakta a'yý b'ye kopyalayabiliriz
		//////////////////////////////////

		int idx_a, idx_b, n;
		printf("a indeks? : ");
		scanf("%d", &idx_a);
		printf("b indeks? : ");
		scanf("%d", &idx_b);
		printf("Kaç eleman kopyalanacak? : ");
		scanf("%d", &n);
		memcpy(b + idx_b, a + idx_a, sizeof(*a) * n);
	}

	void* memmove(void* vpdest, const void* vpsrc, size_t size) {
		//memmove ve memcpy semantik olarak ayný ve ayný iþlemi yapýyorlar.
		// overlapped blocks(kesiþen bellekler): Eðer iki bellek bloðunun yapýlan iþlem açýsýndan ortak bir alaný varsa
			// o zaman o ortak alana sahip bellek bloklarýna overlapped blocks deniyor.
		// strcpy'nin overlapped bloklarý üzerinde davranýþý UB, ayný þekilde memcpy'de overlapped bloklarda UB. 
		// C99 standartlarý ile beraber restrict diye bir keyword eklendi.
			// restrict keywordu asterisk(*)'dan sonra geliyor ve T* türünden bir deðiþkenin gösterdiði adresin
			// baþka bir deðiþekn tarafýndan gösterilmediðinin garantisini veriyor.
				// Bu sayede overlapped blocktan dolayý olan UB'nin önüne geçiyor. 
			// Eðer buna uyulmaz ise UB oluþur. Mesela strcpy(p+3, p); burada restrict keywordü ile tanýmlanmýþ olmasýna raðmen
				// kullanýlmýþ burasý UB çünkü tanýmda restrict var. restrict varsa overlapped block varsa UB'de vardýr.
				// 	strcpy (a+3, a); // UB
				// memcpy(a + 3, a, 3 * sizeof(int)); // UB 
			// void func(int* restrict p1, int* restrict p2) // burada p1'in gösterdiði nesne ile p2'nin gösterdiði nesne ayný olamaz
				// ikisi de farklý olmak zorunda. Buna baðlý olarakta derleyiciler temel optimizasyonu farklý yapacak. Sonuçta
					// UB olmama garantisi var.

	
	}

}