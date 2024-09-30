#include "C:\Users\UGUR\Documents\GitHub\Cnotes\nUtility.h"

/*
	malloc ile ayrýlan alana HEAP denir.
	Baþka bir kodun kullanýlmasýný saðlayan kodlara 'wrapper' denir. 
	Bir fonksiyon var, fonksiyonun yaptýðý iþe ek yapmak istiyoruz. Buna 'augmentation' deniyor.
	wrapper örnek

void* checked_malloc(size_t n){
		
		void* vp = malloc(n);

		if(!vp){
			fprintf(stderr, "nullptr returned!");
			exit(EXIT_FAILURE);
	}
	return vp;
}

	int main(void){
		int n;
		printf("kac adet sayi: ");
		scanf("%d", &n);
		int p = (int*)checked_malloc(n * sizeof(int)); // malloc'un kontrolü burada yapýlýyor.	

		////////////////////////////////////////////

	}

	void func(int x, int y, double d);

	void sfunc(double d, int x, int y)
	{
		func(x,y,d); //bu þekilde de parametreleri istediðimiz sýrada 
						// çaðýrabiliriz.
	}

	-------------------------------------------------------------

	veya aþaðýdaki gibi parametreleri azaltarakta çaðrýlabilir.

	void func(int x, int y, int z);
	void wfunc(int x, int y)
	{
		func(x,y,0);
	}
	
*/
/////////////////////////////////////////////////////////////////////////////////////////////////


/*
	free(void* vp); // Kullanýmdan çekilecek belleðin adresini istiyor. Kaç byte edileceðini vs sormuyor.
	// 40 bytelýk bir alan allocate ettiðimizde aslýnda derleyici daha fazla bellek allocate ediyor.
		bu fazlalýk kýsýmda yapýlan malloc iþlemi ve bazý bilgiler tutuluyor. Boyutu, adý vs gibi bilgiler. Buna 'header' deniyor.
void* checked_malloc(size_t n){
		
		void* vp = malloc(n);

		if(!vp){
			fprintf(stderr, "nullptr returned!");
			exit(EXIT_FAILURE);
	}
	return vp;
}

	int main()
	{
		size_t n;

		printf("kac adet tamsayi: ");
		(void)scanf("%zu", &n);

		int *pd = (int *)checked_malloc(n * sizeof(int)); int *pd = (int *)checked_malloc(n * sizeof *pd); sentaks hatasý yok sýkýntsýýz çalýþýr. Scope'un içerisinde kalýyor
		// sizeof operatörü için iþlem kodu üretilmez.
		set_random_array(pd, n);
		print_array(pd, n);
		free(pd);
	}
*/
///////////////////////////////////////////////////////////////

//FREE FUNCTION ÝLE ÝLGÝLÝ UNDEFINED BEHAVIOR DURUMLARI ve TÝPÝK HATALAR.

//1 - free fonksiyonuna dinamik olarak elde dedilmemiþ adres bloðu göndermek. 
	//UNDEFINED BEHAVIOR

int a[10];
free(a); // UB

/*
2 - free ile geri verilen bellek bloðunun adresi geçersiz / invalid bir adrestir.
Böyle bir pointer deðiþkeni ona yeni atama yapmadan asla kullanmamalýyýz.
Artýk buna dangling pointer deniyor.Bir nesneyi gösteriyordu ama artýk
o nesne öldü, bu sebeple bu bir dangling pointerdýr
free den sonra sonra pd geri verildi.adres ayný deðiþmedi ama artýk
geri verildi.Artýk geçersiz bir pointer.
Evde kiracýsýn ama kontrat bitmiþ.baþýna ne gelir kim bilir : D
print_array(pd, n); dereference et yada etme.Her durumda UNDEFINED BEHAVIOR.
*/

pd = (int*)checked_malloc(n * sizeof(int));
int* p = pd;

free(pd);->burada hem pd hemde p dangling pointer haline geldi.
	hem p hemde pd yi kullanmak UNDEFINED BEHAVIOR.çünkü ikiside ayný adresi
		kullanýyor.

Burada yapýlan þey free edildikten sonra
pd = NULL; yapýlýr.Dereference etmemek gerekir tabi.
	bu sayede dangling pointer olmaktan çýkarýr.
NULL hiçbiryeri göstermeyen geçerli pointer dangling ise geçersiz.
	pd = &x; yapýlabilir.Bunu telegramda hocaya sordum.

3 - Dinamik bellek bloðunun adresi free den sonra geçersiz bir adres.
	bu adresi tekrar free etmek te geçersiz.UB

	pd = (int*)checked_malloc(n * sizeof(int));
	int* p = pd;

	free(p);
//code
free(p);  // buna double deletion deniyor.


4 - malloc ile elde edilen bellek bloðunu free iþlemi ile küçültme giriþimi. 
	Bir kýsmýný geri vermek gibi bir þey yok.
		free(pd + n / 2); burasý kesinlikle UNDEFINED BEHAVIOR örneði


int main()
{
	int* pd;
	int n;

	printf("kac adet tamsayi: ");
	(void)scanf("%d", &n);

	if (!(pd = (int*)malloc(sizeof(int) * n)))
	{
		fprintf(stderr, "Yetersiz bellek alani!\n");
		return 1;
	}
	randomize();
	set_random_array(pd, n);
	print_array(pd, n);
	free(pd); // burada sorun yok ama bazýlarý 
	//free(pd + n/2); burasý kesinlikle UNDEFINED BEHAVIOR
	// print_array(pd,n/2); burasýda UNDEFINED BAHAVIOR oluyor artýk.
}


5 - malloc ile elde edilen bellek bloðunu geri vermemek yanlýþ.(memory leak)
Elde ettiðimiz dinamik bellek bloðunu programýn sonuna kadar
free etmemeniz memory leak deðildir.Çünkü memory kalmadý artýk program bitti : D

a - kodu okuyanlar için
b - test iþlemleri için
c - static kod analizi yapan programlar için
d - dinamik kod analizi yapan programlar için

Elde ettiðimiz tüm bellek bloklarýný geri vermeliyiz.
alýþkanlýk haline getirmek lazým.
zaten program bitiminde free memory boþaltýlýyor.
Sorun oluþturabilecek durumlar oluþabilir bu sebeple free ile
vermek gerekir.


NOT: free function a NULL pointer geçilmesi tanýmsýz davranýþ deðildir.
Tanýmlý davranýþtýr.Defined behavior.

pd = NULL;
free(pd); UB deðil

void my_free(void* vp)
{
	if (vp == NULL)
		return;
}

Eðer malloc fonksiyonuna 0 deðeri ile çaðrý yapýlýrsa
malloc(0)->UB DEÐÝL ama ne olacaðý UNSPECIFIED BEHAVIOR

a - Derleyici NULL döndürtebilir
b - Bir adresi döndürtebilir.

Dereference edilmemelidir.
Free ye göndermek UB deðildir.

pd = NULL;
free(pd); UB deðil

void my_free(void* vp)
{
	if (vp == NULL)
		return;
}
free(vp); //UB deðil.


NOT:	int x = 10;
int* vp = &x;

*vp; burasý hata deðil.Ýngnç bir þekilde standartlarda yazýyor.
ama etkisiz kod.normalde void* türünü dereference edip
bir operatörün operandý yapýnca sentaks hatasý.

* vp = 56; burasý hata

/////////////////////////////////////////////////////////////////////////////////////

ÖRNEKTEKÝ LOGIC HATAYA DÝKKAT.

char* get_name(void)
{
	static char name[100];
	printf("bir isim giriniz :");
	(void)scanf("%s", name);
	return name; // her seferinde adres gönderir ve adres hep ayný.
}				// en son bu adrese yazýlan isim ne ise hepsine de onu yazar.
				// fonksiyonda hata yok.çaðýranda hata var.


int main()
{
	char* pa[5];

	for (size_t i = 0; i < 5; i++)
		pa[i] = get_name();


	printf("\n\nKaydedilen isimler\n");
	for (size_t i = 0; i < 5; i++)
		printf("%s", pa[i]);
}

AÞAÐIDAKÝ GÝBÝ YAZILIRSA DAHA MANTIKLI OLABÝLÝR.

int main()
{
	char* p;

	for (int i = 0; i < 5; i++)
	{
		p = get_name();
		puts(p);
	}

}

------------------------------------------------------------

EÐER DÝNAMÝK BELLEK YÖNETÝMÝ ÝLE YAPARSAK
Tüm sorunu ortadan kaldýrmýþ oluyoruz.

cchar * get_name(void)
{
	static char name[100] = { 0 }; // malloc taki uyarýyý kaldýrmak için 0 yaptým
	printf("bir isim giriniz :");
	(void)scanf("%s", name);

	char* pd = (char*)malloc(strlen(name) + 1); // bunun sayesinde artýk tüm veriler
	if (!pd)								// malloc ile elde edilmiþ ayrý bir bellek
	{										// alanýnýn adresini tutuyor.diðeri gibi tüm elemanlar ayný adresi göstermeyecek.
		fprintf(stderr, "Bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	return strcpy(pd, name);
}

int main()
{
	char* pa[5];

	for (size_t i = 0; i < 5; i++)
		pa[i] = get_name();


	printf("\n\nKaydedilen isimler\n");
	for (size_t i = 0; i < 5; i++)
		printf("%s ", pa[i]);


	// burada da her fonksiyon çaðrýsýndan elde ettiðimiz char * türündeki
	// memory adresini free ile geri vermemiz gerekir.
	for (size_t i = 0; i < 5; i++)
		free(pa[i]); // burasý olmasaydý memory leak olacaktý.

}
// aþaðýdaki fonksiyon iki adet yazý adresini alýp bunu dinammik bir bellek
alanýnda birleþtirip adresini geri döndürecek

char* concat(const char* p1, const char* p2)
{
	char* pd = (char*)malloc(strlen(p1) + strlen(p2) + 1);
	if (!pd)
	{
		fprintf(stderr, "Bellek hatasi\n");
		exit(EXIT_FAILURE);
	}
	return strcat(strcpy(pd, p1), p2);

}


int main()
{
	char s1[100];
	char s2[100];
	char* pd;

	printf("birinci yazi \n");
	sgets(s1);
	printf("ikinci yazi \n");
	sgets(s2);

	pd = concat(s1, s2);

	printf("(%s) + (%s) = (%s)\n", s1, s2, pd);
	_strupr(pd);
	printf("(%s) + (%s) = (%s)\n", s1, s2, pd);

	free(pd); // memory leak olmasýn diye 

}

CALLOC FONKSÝYONU

void* calloc(size_t n, size_t sz);
calloc memory allocate edip bir de 0 yazýyor hepsine
birde calloc ta iki parametre deðiþkeni var.
sz->byte size bilgisi
n->adet bilgisi.

malloc(n * sizeof(int))
calloc(n, sizeof(int))  çaðrýlýrken aradaki tek fark bu.


ÖR:

int main()
{
	size_t n;
	int* pd;

	printf("Kac tamsayi \n");
	(void)scanf("%d", &n);

	randomize();
	//pd = (int*)malloc(sizeof(int)*n);
	pd = (int*)calloc(n, sizeof(int));

	if (!pd)
	{
		fprintf(stderr, "Bellek hatasi\n");
		return 1;
	}

	//memset(pd, 0, n * sizeof(int)); // malloc ile memory allocate edilip memset ile 0 yazýlabilirdi.
	print_array(pd, n);

}

----------------------------------------------------------------------------------------------

Eðer int* p[n] gibi bir diziyi dinamik olarak allocate edersek aþaðýdaki gibi yazarýz.

int** pd = (int**)malloc(n * sizeof(int*));

Eðer matris oluþturacalsak ve satýr sütun sayýsý runtime da belli olacak.

ÖNEMLÝ ÖRNEK :

int main()
{

	int row, col;
	int** pd;
	printf("matrisin satir ve sutun sayilarini girin : \n");
	(void)scanf("%d%d", &row, &col);

	pd = (int**)malloc(row * sizeof(int*)); // dizinin elemanlý bir ptr dizisi bu aslýnda
	if (!pd)
	{
		fprintf(stderr, "bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < row; i++)
	{
		pd[i] = (int*)malloc(col * sizeof(int)); // bu sefer int** deðil. zaten o dizinin içindeyiz.
		if (!pd[i])
		{
			fprintf(stderr, "bellek yetersiz\n");
			exit(EXIT_FAILURE);
		}
	}											// burada dizinin elemaný olan diziler için yer ayýrýyoruz.


	randomize();

	for (int i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
			pd[i][j] = rand() % 10;	// buradaki matris elemanlarý ardýþýk deðil.
	}								// dinamik bellek yönetiminde ardýþýk adres garantisi yok.


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			printf("%d ", pd[i][j]);
		printf("\n");
	}

	// elemanlarýn ardýþýk olmasýnýn garanti olmadýðýnýn ispatý
	int* p = pd[0];
	int n = row * col;
	while (n--)
	{
		printf("%d ", *p++);
		_getch();

	}


	for (int i = 0; i < row; i++)
	{
		free(pd[i]); // memory leak olmasýn diye ilk önce içerisindekileri free ettik.
	}
	free(pd); // sonra burayý.
}