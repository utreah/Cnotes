#include "C:\Users\UGUR\Documents\GitHub\Cnotes\nUtility.h"

/*
	malloc ile ayr�lan alana HEAP denir.
	Ba�ka bir kodun kullan�lmas�n� sa�layan kodlara 'wrapper' denir. 
	Bir fonksiyon var, fonksiyonun yapt��� i�e ek yapmak istiyoruz. Buna 'augmentation' deniyor.
	wrapper �rnek

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
		int p = (int*)checked_malloc(n * sizeof(int)); // malloc'un kontrol� burada yap�l�yor.	

		////////////////////////////////////////////

	}

	void func(int x, int y, double d);

	void sfunc(double d, int x, int y)
	{
		func(x,y,d); //bu �ekilde de parametreleri istedi�imiz s�rada 
						// �a��rabiliriz.
	}

	-------------------------------------------------------------

	veya a�a��daki gibi parametreleri azaltarakta �a�r�labilir.

	void func(int x, int y, int z);
	void wfunc(int x, int y)
	{
		func(x,y,0);
	}
	
*/
/////////////////////////////////////////////////////////////////////////////////////////////////


/*
	free(void* vp); // Kullan�mdan �ekilecek belle�in adresini istiyor. Ka� byte edilece�ini vs sormuyor.
	// 40 bytel�k bir alan allocate etti�imizde asl�nda derleyici daha fazla bellek allocate ediyor.
		bu fazlal�k k�s�mda yap�lan malloc i�lemi ve baz� bilgiler tutuluyor. Boyutu, ad� vs gibi bilgiler. Buna 'header' deniyor.
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

		int *pd = (int *)checked_malloc(n * sizeof(int)); int *pd = (int *)checked_malloc(n * sizeof *pd); sentaks hatas� yok s�k�nts��z �al���r. Scope'un i�erisinde kal�yor
		// sizeof operat�r� i�in i�lem kodu �retilmez.
		set_random_array(pd, n);
		print_array(pd, n);
		free(pd);
	}
*/
///////////////////////////////////////////////////////////////

//FREE FUNCTION �LE �LG�L� UNDEFINED BEHAVIOR DURUMLARI ve T�P�K HATALAR.

//1 - free fonksiyonuna dinamik olarak elde dedilmemi� adres blo�u g�ndermek. 
	//UNDEFINED BEHAVIOR

int a[10];
free(a); // UB

/*
2 - free ile geri verilen bellek blo�unun adresi ge�ersiz / invalid bir adrestir.
B�yle bir pointer de�i�keni ona yeni atama yapmadan asla kullanmamal�y�z.
Art�k buna dangling pointer deniyor.Bir nesneyi g�steriyordu ama art�k
o nesne �ld�, bu sebeple bu bir dangling pointerd�r
free den sonra sonra pd geri verildi.adres ayn� de�i�medi ama art�k
geri verildi.Art�k ge�ersiz bir pointer.
Evde kirac�s�n ama kontrat bitmi�.ba��na ne gelir kim bilir : D
print_array(pd, n); dereference et yada etme.Her durumda UNDEFINED BEHAVIOR.
*/

pd = (int*)checked_malloc(n * sizeof(int));
int* p = pd;

free(pd);->burada hem pd hemde p dangling pointer haline geldi.
	hem p hemde pd yi kullanmak UNDEFINED BEHAVIOR.��nk� ikiside ayn� adresi
		kullan�yor.

Burada yap�lan �ey free edildikten sonra
pd = NULL; yap�l�r.Dereference etmemek gerekir tabi.
	bu sayede dangling pointer olmaktan ��kar�r.
NULL hi�biryeri g�stermeyen ge�erli pointer dangling ise ge�ersiz.
	pd = &x; yap�labilir.Bunu telegramda hocaya sordum.

3 - Dinamik bellek blo�unun adresi free den sonra ge�ersiz bir adres.
	bu adresi tekrar free etmek te ge�ersiz.UB

	pd = (int*)checked_malloc(n * sizeof(int));
	int* p = pd;

	free(p);
//code
free(p);  // buna double deletion deniyor.


4 - malloc ile elde edilen bellek blo�unu free i�lemi ile k���ltme giri�imi. 
	Bir k�sm�n� geri vermek gibi bir �ey yok.
		free(pd + n / 2); buras� kesinlikle UNDEFINED BEHAVIOR �rne�i


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
	free(pd); // burada sorun yok ama baz�lar� 
	//free(pd + n/2); buras� kesinlikle UNDEFINED BEHAVIOR
	// print_array(pd,n/2); buras�da UNDEFINED BAHAVIOR oluyor art�k.
}


5 - malloc ile elde edilen bellek blo�unu geri vermemek yanl��.(memory leak)
Elde etti�imiz dinamik bellek blo�unu program�n sonuna kadar
free etmemeniz memory leak de�ildir.��nk� memory kalmad� art�k program bitti : D

a - kodu okuyanlar i�in
b - test i�lemleri i�in
c - static kod analizi yapan programlar i�in
d - dinamik kod analizi yapan programlar i�in

Elde etti�imiz t�m bellek bloklar�n� geri vermeliyiz.
al��kanl�k haline getirmek laz�m.
zaten program bitiminde free memory bo�alt�l�yor.
Sorun olu�turabilecek durumlar olu�abilir bu sebeple free ile
vermek gerekir.


NOT: free function a NULL pointer ge�ilmesi tan�ms�z davran�� de�ildir.
Tan�ml� davran��t�r.Defined behavior.

pd = NULL;
free(pd); UB de�il

void my_free(void* vp)
{
	if (vp == NULL)
		return;
}

E�er malloc fonksiyonuna 0 de�eri ile �a�r� yap�l�rsa
malloc(0)->UB DE��L ama ne olaca�� UNSPECIFIED BEHAVIOR

a - Derleyici NULL d�nd�rtebilir
b - Bir adresi d�nd�rtebilir.

Dereference edilmemelidir.
Free ye g�ndermek UB de�ildir.

pd = NULL;
free(pd); UB de�il

void my_free(void* vp)
{
	if (vp == NULL)
		return;
}
free(vp); //UB de�il.


NOT:	int x = 10;
int* vp = &x;

*vp; buras� hata de�il.�ngn� bir �ekilde standartlarda yaz�yor.
ama etkisiz kod.normalde void* t�r�n� dereference edip
bir operat�r�n operand� yap�nca sentaks hatas�.

* vp = 56; buras� hata

/////////////////////////////////////////////////////////////////////////////////////

�RNEKTEK� LOGIC HATAYA D�KKAT.

char* get_name(void)
{
	static char name[100];
	printf("bir isim giriniz :");
	(void)scanf("%s", name);
	return name; // her seferinde adres g�nderir ve adres hep ayn�.
}				// en son bu adrese yaz�lan isim ne ise hepsine de onu yazar.
				// fonksiyonda hata yok.�a��randa hata var.


int main()
{
	char* pa[5];

	for (size_t i = 0; i < 5; i++)
		pa[i] = get_name();


	printf("\n\nKaydedilen isimler\n");
	for (size_t i = 0; i < 5; i++)
		printf("%s", pa[i]);
}

A�A�IDAK� G�B� YAZILIRSA DAHA MANTIKLI OLAB�L�R.

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

E�ER D�NAM�K BELLEK Y�NET�M� �LE YAPARSAK
T�m sorunu ortadan kald�rm�� oluyoruz.

cchar * get_name(void)
{
	static char name[100] = { 0 }; // malloc taki uyar�y� kald�rmak i�in 0 yapt�m
	printf("bir isim giriniz :");
	(void)scanf("%s", name);

	char* pd = (char*)malloc(strlen(name) + 1); // bunun sayesinde art�k t�m veriler
	if (!pd)								// malloc ile elde edilmi� ayr� bir bellek
	{										// alan�n�n adresini tutuyor.di�eri gibi t�m elemanlar ayn� adresi g�stermeyecek.
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


	// burada da her fonksiyon �a�r�s�ndan elde etti�imiz char * t�r�ndeki
	// memory adresini free ile geri vermemiz gerekir.
	for (size_t i = 0; i < 5; i++)
		free(pa[i]); // buras� olmasayd� memory leak olacakt�.

}
// a�a��daki fonksiyon iki adet yaz� adresini al�p bunu dinammik bir bellek
alan�nda birle�tirip adresini geri d�nd�recek

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

	free(pd); // memory leak olmas�n diye 

}

CALLOC FONKS�YONU

void* calloc(size_t n, size_t sz);
calloc memory allocate edip bir de 0 yaz�yor hepsine
birde calloc ta iki parametre de�i�keni var.
sz->byte size bilgisi
n->adet bilgisi.

malloc(n * sizeof(int))
calloc(n, sizeof(int))  �a�r�l�rken aradaki tek fark bu.


�R:

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

	//memset(pd, 0, n * sizeof(int)); // malloc ile memory allocate edilip memset ile 0 yaz�labilirdi.
	print_array(pd, n);

}

----------------------------------------------------------------------------------------------

E�er int* p[n] gibi bir diziyi dinamik olarak allocate edersek a�a��daki gibi yazar�z.

int** pd = (int**)malloc(n * sizeof(int*));

E�er matris olu�turacalsak ve sat�r s�tun say�s� runtime da belli olacak.

�NEML� �RNEK :

int main()
{

	int row, col;
	int** pd;
	printf("matrisin satir ve sutun sayilarini girin : \n");
	(void)scanf("%d%d", &row, &col);

	pd = (int**)malloc(row * sizeof(int*)); // dizinin elemanl� bir ptr dizisi bu asl�nda
	if (!pd)
	{
		fprintf(stderr, "bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < row; i++)
	{
		pd[i] = (int*)malloc(col * sizeof(int)); // bu sefer int** de�il. zaten o dizinin i�indeyiz.
		if (!pd[i])
		{
			fprintf(stderr, "bellek yetersiz\n");
			exit(EXIT_FAILURE);
		}
	}											// burada dizinin eleman� olan diziler i�in yer ay�r�yoruz.


	randomize();

	for (int i = 0; i < row; i++)
	{
		for (size_t j = 0; j < col; j++)
			pd[i][j] = rand() % 10;	// buradaki matris elemanlar� ard���k de�il.
	}								// dinamik bellek y�netiminde ard���k adres garantisi yok.


	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
			printf("%d ", pd[i][j]);
		printf("\n");
	}

	// elemanlar�n ard���k olmas�n�n garanti olmad���n�n ispat�
	int* p = pd[0];
	int n = row * col;
	while (n--)
	{
		printf("%d ", *p++);
		_getch();

	}


	for (int i = 0; i < row; i++)
	{
		free(pd[i]); // memory leak olmas�n diye ilk �nce i�erisindekileri free ettik.
	}
	free(pd); // sonra buray�.
}