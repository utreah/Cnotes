#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <string.h>
#include <stdio.h>
#define SIZE 100
typedef unsigned char BYTE;
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
/*
memchr(const void* vptr, int val, size_t size) // adresini ve büyüklüðünü aldýðý bir bellek bloðunda tam sayý deðeri arýyor.
	-Bloðun içeriðini bilmez. Yani aradýðý bloðun yazýyý tutan bir bellek bloðumu yoksa sayý tutan bir bellek bloðu mu bilmez.
	-2. parametre int olmasýnýn sebebi integral promotion. Aranan karakter char türünden olsa da integral promotiondan dolayý
		int oluyor.
	-strchr() sondaki null karakterine güvenirken memchr parametresindeki SIZE'a güvenir.
*/
void* my_memchr(const void* vptr, int val, size_t size) {
	const char* p = (const char*)vptr;
	while (size--)
		if (*p == val)
			return (char*)p; // void* türüne örtülü olarak dönüþtürülüyor. char*'a cast etmek yerine void* cast etsekte sýkýntýsýz çalýþýrdý.
	return NULL;
}
/*
int memcmp(const void* vptr, const void* vptr2, size_t size);
	-Eðer geri dönüþ deðeri 0 ise iki bellek bloðu birbirine eþit.
	-Eðer geri dönüþ deðeri pozitif ise vp1 vp2'den büyük.
	-Eðer geri dönüþ deðeri negatif ise vp1 vp2'den küçük.
		Buraya kadar strcmp ile ayný zaten.
	-Ýki bellek bloðunu karþýlaþtýrýyor.
	-Bu bloklarýn içeriðinde ne olduðu memcmp'yi baðlamýyor. Umrum dýþýsýn diyor resmen.
	-Karþýlaþtýrma yapýlýrken unsigned türden yapýlýyor. Bytelar iþaretsiz tam sayý olarak deðerlendirilecek.

	0001 0001					0001 0001
	0000 0000					0000 0000
	1111 1111					1111 1111
	0101 0101					0101 0101
	Eðer birebir eþitse ayný olarak görüyor.
	Þimdi 3. byte'taki LSB'i 0 yapalým
		vp1							vp2
	0001 0001					0001 0001
	0000 0000					0000 0000
	1111 1111					1111 1110 -> bunu 0 yaptýk
	0101 0101					0101 0101
	
	Ýþaretsiz binaryde 1111 1111 deðer olarak 1111 1110'dan büyük olduðu için burada vp1 belleði > vp2 belleði, söz konusu

*/
int my_memcmp(const void* vp1, const void* vp2, size_t n)
{
	const unsigned char* p1 = (const unsigned char*)vp1; // unsigned olarak kýyasladýðýný söylemiþtik.
	const unsigned char* p2 = (const unsigned char*)vp2; // unsigned olarak kýyasladýðýný söylemiþtik.

	while (n--)
	{
		if (*p1 != *p2)
		{
			return *p1 > *p2 ? 1 : -1; // buradaki büyüklük, deðerlerin büyüklüðü deðil,
		}								// bytelarýn kýyaslamasý sonucu oluþan büyüklük.
		++p1, ++p2;						// Notlarda aþaðýda yani var açýklamasý.
	}

	return 0;

}
int main(void) {
	char str[SIZE] = "gulden";
	strcpy(str + 3, str); // bu undefined behaviour -> overlapped blocks
	memcpy(str + 3, str, 7); // bu undefined behaviour -> overlapped blocks
	memmove(str + 3, str, strlen(str) + 1); // bunda sýkýntý yok 
	///////////////////////////////// memchr() ÖRNEK

	BYTE ar[SIZE] = { 0 };
	srand((unsigned)time(0));
	for (int i = 0; i < SIZE; i++)
		ar[rand() % SIZE] = 1;

	for (int i = 0; i < SIZE; i++)
		printf("%d", ar[i]);

	printf("\n");
	BYTE* p = (BYTE*)memchr(ar, 0, sizeof(ar));
	if (p)
		printf("Bulundu! %lld nolu indiste", p - ar); // format specifier derleyiciye baðlý. Eðer long long veya unsigned long long olursa specifer farklý olur.
	else
		printf("BULUNAMADI");
	/// /////////////////////////////////////
	char str[SIZE] = "Mustafa Mete C dersini izliyor, degil mi";
	memchr(str, 'e', 8); // e karakterini 8 bytelýk alanda arayacak. Yani Mustafa_ kýsmýna kadar ve bulamayacak.
							// strchr'den en büyük farký bu. STRCHR null karakterine kadar bütün diziyi ararken
								// memchr bir bellek bloðunda belirlenen byte kadar arama yapabiliyor.
	/////////////////////////////////// memcmp() ÖRNEK
	int a[SIZE];
	int b[SIZE];
	randomize();
	set_array_random(a, SIZE);
	memcpy(b, a, sizeof a);

	if (!memcmp(b, a, sizeof a))
		printf("Diziler birbirine eþit"); // diziler line 111'den dolayý birbirine eþit.
	else
	++a[rand() % SIZE];

	if (!memcmp(b, a, sizeof a))
		printf("Diziler birbirine eþit");
	else
		printf("Diziler birbirine eþit deðil"); // artýk eþit deðil
	
	return 0;
}
 /* VOID* 2. KISIM
 
	Türden baðýmsýz bir arama fonksiyonu yazýlabilir mi? Evet,

	void* gsearch(const void* vpa, size_t size, size_t szof, const void* vpkey);
		vpa = Ýçerisinde arama yapýlacak dizinin adresi
		size = dizinin boyutu
		szof = dizinin 1 elemanýnýn sizeof deðeri
		vpkey = aranacak deðer
 */
void* myf_gsearch(const void* vpa, size_t size, size_t szof, const void* vpkey) {
	const char* p = (const char*)vpa;
	for (size_t i = 0; i < size; i++) {

		if (!memcmp(p+i*szof, vpkey, szof)) // p + i * szof; szof burada kullandýðýmýz deðiþkenin türünün bellekte kapladýðý yer.
			return (char*)(p + i * szof);	// memcmp içerisinde, yollanan bellek bloðu tamamen karþýlaþtýrýlýyor(1 byte)
											// sonraki bellek bloðuna geçebilmek için p + i'yi sz ile çarpýyoruz.
	}
	return NULL;
}
void* myw_gsearch(const void* vpa, size_t size, size_t sz, const void* vpkey) {
	const char* p = (const char*)vpa;
	while (size--) {
		if (!memcmp(p, vpkey, sz))
			return (char*)p;
		p += sz; // p'nin elemanlarý int türünden ise sizeof deðeri 4 olacaðýndan dolayý p'nin deðeri dörder dörder arttýrýlýr.
					// p++ char* türünde bir byte bir byte ilerlemek demek. Biz zaten p ve vpkey parametre deðiþkenlerini memcmp'ye attýðýmýzda
						// o bellek bloðu(1 byte) tamamen karþýlaþtýrýlýyor. Sonraki bellek bloðuna geçebilmemiz için o veri türünün 
						//	bellekte kapladýðý kadar p'ye eklememiz gerekiyor. sz'de burada o veri türünüün sizeof deðerini tutuyor.s
						//	Eðer içinde arama yaptýðýmýz dizinin türü int ise +4, double ise 8 olurdu sz için.
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
	// int *p = dizinin bir int dizi olduðunu biliyoruz. Dönen deðerde void * olacak.
	// bizde zaten cast ettik
	// a = array
	// SIZE = Dizi uzunluðu
	// sizeof(*a) -> bir elemanýn sizeof deðeri
	// &sval -> aranan deger adresi. HErþey adresler üzerinden yapýlýyor. memcmp de kullanýlacak
	// bu deðiþken ve memcmp de adres ile iþlem yapýyor.türden baðýmsýz çünkü.

	if (p)
		printf("bulundu dizinin %d indisli elemani\n", p - a);
	else
		printf("bulunamadi\n");
}
////////////////////////////////////////
 /*
	-Yazacaðýmýz bir çok fonksiyon hala türe baðlý olacak.
	-Gerekmediði sürece hem bakým hem de kodun anlamanýn daha kolay olmasý için void* kullanýlmayacak.(zorunlu deðilse)
	-
 */
///////////////////////////////////////
///////////////////////////////////////  
/*
	void* vptr = NULL; // void* türünden bir deðiþken herhangi bir nesnenin adresini tutabilir.
		vptr = &vptr; // kendi adresini tutabilir.
	void** vp2; // void* türünden bir deðiþken herhangi bir nesnenin adresini tutabilirken, void** türünden bir deðiþekn
					// herhangi T* türünden bir nesnenin adresini tutabilir diye bir analoji kurulamaz.
				//void** türü de diðer T** türleri gibi çalýþýr. void* veri türü ile bildirilmiþ nesnenin adresini tutabilir.
					// void** türü generic bir tür deðil.
	int x = 10;
	int* y = &x;
	vp2 = &vptr; // sýkýntý yok
	vp2 = &y; // hatalý y int* türünden bir nesne ve void**'a atanamaz.
	*vptr = 10; // Bu derefence edilemez çünü vptr NULL pointerý gösteriyor. Bu türden
					// baðýmsýz, bir kural. Ek olarakta, void* türünden nesneler dereference edilemez. 
	*vp2 = &y; // vptr'ye y'nin adresini cast edebiliriz çünkü vp2 derefence edilebilir ve edildiðinde vptr nesnesinin deðerine eriþir.

	int main(void){
		int x = 10;
		double dval = 45.56;

		void* vp = &x; 
		*vp; // sentaks hatasý, derefence edilemez.
		void** vptr = &vp; // türsel açýdan hiçbir sýkýntý yok.
		*vptr = &dval; // vp'ye dval'i atýyorum. *vptr == vp;
		 
	}
		Öyle durumlarla karþýlaþýcaz ki 3. parti kütüphaneler bizden void* türündeki nesnenin adresini isteyecek.
	int g;
	void foo(void** vptr){
		*vptr = &g;
	}
	int main(void){
		void* vp1;
		foo(&vp1); // void* türünden  bir nesnenin adresini gönderdik. foo fonksiyonunun parametresi void** türünden
		int* p = NULL;
		void* x = &p; // void* türünden bir deðiþkene herhangi bir nesnenin adresini atayabilirim
		void **y = &p; // fakat void** türünden bir deðiþkene sadece void* türünden bir nesnenin adresini atayabilirim.
							// bundan dolayý burada tür uyuþmazlýðý var
	}	
	Bir fonksiyonun geri dönüþ deðeri T* türden olabileceði gibi T** türünden de olabilir.
*/
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
////////////////////////////////////////////
/*												FUNCTION POINTERS
	-Bir fonksiyonun, baþka bir fonksiyona fonksiyon göndermesi. Buna Callback deniyor.
	Pointerlar ikiye ayrýlýyor;
		-object pointers -> Deðiþkenlerin(nesnelerin) adresleri.
		-function pointers -> Fonksiyonlarýn adresleri.
	-Fonksiyonlarýn da adresi vardýr ayný nesnelerin adresinin olmasý gibi.
	-Nesnelerin memoryde adresleri vardý. Bu adresler söz konusu olduðunda pointer kullanýrýz. Fonksiyonlarýn da makine kodlarý var.
		Bu makine kodlarýnýn çalýþabilmesi için memory'e yüklenmesi gerekiyor. Bu makine kodlarýnýn yüklendiði bellek bloðunun da adresi var.
			Adresi biliyor isek fonksiyonu çaðýrabiliriz.
				Özet= Makine komutlarý bellekte tutulduðu adres.
	-Fonksiyonlarýn ve fonksiyon adreslerinin de türü var.
		Bir fonksiyon adresinin türü, fonksiyonun geri dönüþ türü ve parametrelerinin türünden elde ediliyor.
	-Fonksiyon türü ile fonksiyon adresinin türü ayný þey deðildir.
		Fonksiyon türü: Fonksiyonun geri dönüþ deðeri(parametrelerinin türü)
	Bildirim							 Fonksiyon Türü					Fonksiyon Adresi Türü(geri dönüþ deðeri (*)(parametre deðiþkenleri))
	int foo(int); 						 int(int)						int (*)(int)
	int bar(int, int)					 int(int, int)					int (*)(int, int)
	double baz(double)					 double(double)					double (*)(double)
	size_t strlen(const char*)			 size_t(const char*)			size_t (*)(const char*) // (*) bir pointer olduðunu göstermek için yazýlýyor.
	int strcmp(const char*, const char*) int(const char*, const char*)	int (*)(const char*, const char*)
	char* strcpy(char*, const char*)	 char*(char*, const char*)		char* (*)(char*, const char*)

	-Bir fonksiyonun adresini nasýl elde ediyoruz?
		Bir fonksiyonun adresini elde etmek için ayný deðiþkenlerde olduðu gibi addressof(&) operatörünün operandý yapýyoruz.
			int foo(int);
			&foo; // -> int(*)(int, int)
			&strcat; // -> char* (*)(char*, const char*)
			 
	-Fonksiyonlarda da ayný dizilerde öðrendiðimiz gibi 'array decay' ya da pointer to int conversion oluyor. Tabii fonksiyonlar için biz buna
		function to pointer conversion diyoruz.
		Mesela int arr[10]; dizisinin adresini &ar[0] yazmak ile sadece 'ar' yazmak arasýnda hiçbir fark yok.
		Ayný durum fonksiyonlarda da geçerli.
			int foo(void);
			foo(); // böyle yazarak foo fonksiyonunu çaðýrýyoruz. Aslýnda foo burada function to pointer conversion'a uðrayarak þu hali alýr.
			(&foo)(); -> bu foo() ile ayný anlama geliyor. 
				Parantez(öncelik operatörü) içersine koyuyoruz eðer koymazsak () -> function call operatörü öncelik kazanýr.
					Bunun önüne geçmek için öncelik parantezine alýyoruz.

	-Fonksiyon çaðrý operatörünün operandý ya bir fonksiyon olacak ya da bir fonksiyon adresi olmalý.
		( standart buna function designator diyor) () -> fonksiyon çaðýrma operatörünün operandý solunda kalan fonksiyonun adýdýr.
			// o adreste bulunan fonksiyonun çaðýrýlmasýný saðlýyor.

	int foo(int x){
		printf("int foo(int x) çaðrýldý x = %d\n", x);
		return x * x
	}
	int baz(int);
	int bar(int);
	int main(void){
		int val = foo(12);
		int val2 = (&foo)(31); // addresof operatörünün önceliði () fonksiyon çaðrý operatöründen düþük olduðu için
								// öncelik operatörünün içine alýyoruz
		
		int (*fp)(int); // bu bir fonksiyon adresi tutan deðiþkenin tanýmý
		fp = &foo; // fp = foo;
		fp = &bar; // fp = bar;
		fp = &baz; // fp = baz; // Burada function to pointer conversion oluyor.
		// geri dönüþ deðeri (*deðiþken adý)(parametre türü); 

		size_t (*sp)(const char*) = strlen; // burada da strlen fonksiyonun adresini tutuyoruz.

	}
	// Neden bir fonksiyonun adýný function pointer variable dediðimiz deðiþkenlerde tutalým?
		-Fonksiyonun  adresini baþka bir deðiþkende tutarak, fonksiyonun adresini kullanarak o deðiþekn vasýtasý ile fonksiyonu çaðýrabiliriz.
		-
	void foo(void){
		printf("foo cagrildi");
	}
	void bar(void);
	void baz(void);
	void func(void (*fp)(void)){
		fp(); // burada mainden foo fonksiyonunun adresi gönderildiði için foo fonksiyonu çaðýrýlacak.
	}
		// -Burada foo fonksiyonunun parametresi, geri dönüþ deðeri olmayan, parametre deðiþkeni olmayan bir fonksiyonun adresi olmalý. 

	int main(void){
		void (*fp)(void) = &foo;

		fp(); // bu foo fonksiyonunu çaðýrýr ve ekrana "foo cagrildi" yazdýrýr.
		//////////

		fp = &baz;
		fp(); // bu baz fonksiyonunu çaðýrýr

		fp = &bar;
		fp(); // bu bar fonksiyonunu çaðýrýr
		func(&foo); // foo fonksiyonunun adresini func fonksiyonuna parametre olarak gönderdik.

	}
	- Bu neden bu kadar önemli?
		Bir fonksiyonun iþlevinin daha da esnek hale gelmesini saðlýyoruz. Ýþinin bir kýsmýný veya tamamýnýn nasýl yapýlacaðýný
			fonksiyon deðil onu çaðýran fonksiyon karar veriyor.
		Bir fonksiyona baþka bir fonksiyonun adresini gönderip, o fonksiyonu gönderdiðimiz fonksiyonda çaðýrdýðýmýzda aslýnda
			o fonksiyonu ÇAÐIRTMIÞ oluyoruz. Bizim için fonksiyon adresini aldýðý fonksiyonu çaðýrýyor.

	////////////////////

	void func(int ch){
		if(isupper(ch)); // burada func fonksiyonu içerisinde ne yapýlacaðýna kendi karar veriyor.
	}
	void func(int ch, void (*fptest)(int)){
		if(fptest(ch)); // burada ise func fonksiyonun içerisinde nasýl bir fonksiyon çaðýrýlýp nasýl bir iþlem yapýlacaðýna
							// fonksiyonu çaðýran kiþi karar veriyor
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

		// görüldüðü üzere 1 fonksiyon yazdýk ve parametresini function pointer türünden yaptýk.
			// bu sayede 1 fonksiyon yazarak birden fazla fonksiyonla o fonksiyona çaðrý yapabildik.
	}
	

*/
/*
bir function pointerý ile nesne pointerýnýn sizeof u ayný olmayabilir,
ama tüm function ptr sizeoflarý kendi içinde ayný.
Tüm obje pointerlarda kendi içinde ayný size deðerine sahip.*/
/*
	
	ÖDEV MEMMOVE KODUNU YAZ?


*/