/*
				-------------------------------------------------CONST KEYWORD-------------------------------------------------
En önemli 3 keywordten birisi diyor hoca.
Const'un da içinde bulunduðu bir anahtar sözcük kümesi ve buna "type qualifier(tür niteliyici)" deniyor.

CONST CORRECTNESS: const anahtar sözcüðünün doðru kullanýlmasýna const correctness deniyor.

mutate:
mutator: Deðiþtiren, özellikle fonksiyonlarý niteliyor. Nesne alýyor ve o nesneyi deðiþtiriyor
Accessor: Nesne alýyor ama sadece okumak için kullanýyor.
mutable: Deðiþtirilebilir(varlýk) anlamýna geliyor.
immutable: Deðiþtirilemez(varlýk) anlamýna geliyor.

void foo(int* a) // foo fonksiyonu bi mutator çünkü adresini aldýðý nesneyi deðiþtirebilir.
void bar(const int* a) // bar bir accessor çünkü adresini aldýðý nesneyi sadece okuyabilir, DEÐÝÞTÝREMEZ.
const keywordu olan bir deðiþkenin ilk deðerinin tam sayý olma gibi bir zorunluluðu yoktur.
--------------------------------------------------------------------------------------------------

const int x = 10; // Bu deðiþkenin deðerinin hayatý boyunca deðiþmeyeceðini ve sadece salt okuma olarak kullanýlacaðýný söylüyor.
					// const keywordünün anlamý bu. Immutable bir deðiþken oluþturmaya yarýyor.
const int x = 10; // bu ayný zamanda 'oksimoron' bir ifade. const immutable, deðiþken ise adýndan da anlaþýlabileceði için bir biri ile çeliþiyor
					// olsa da çalýþmasýnda bir sýkýntý yoktur. 
		x deðiþkeni hayata 10 deðeri ile geliyor ve programýn sonuna kadar bu deðerini koruyacak!
		++x; // bu bir sentaks hatasý. Çünkü x'in deðeri deðiþtirilemez.
		x = 20; sentaks hatasý


		// Eðer deðiþtirilmemesi gereken  bir dizi veya deðiþken var ise const kullanýlýr.
int main(void){
	const int x = 10;
	const int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
	// Burada const kullanmak derleyicye bir kontrol yükümlülüðü saðlýyor.
	// Eðer const bir nesneyi deðiþtirmeye çalýþýrsanýz dilin kurallarýna aykýrý bir durum oluyor(sentaks hatasý)
	x = 45; // SENTAKS HATASI
	primes[3]; // eriþilebilir sýkýntý yok
	printf("%d",primes[3]); // burada da sýkýntý yok
	primes[2] = 10; // hop sentaks hatasý.
}

 const anahtar sözcüðünü gerekli olan yerlerde kullanýrsak 
 	1 - const keyword kodu okuyanýnda/yazanýnda iþini kolaylaþtýrýyor.
	
	2 - int a[]; bu dizi mutable olduðunu gösterir.write edilebilir olduðunu gösterir.
		const int a[]; bu ise immutable bir dizi.elemanlarý deðiþtirilemez.write amaçlý kullanýlmayacak demek.
	
	3 - const keyword kodun optimizasyonuna faydalýdýr.
		kesinlikle daha iyi kod üretir denemez ama üretecek duruma getirir.


const int x = 5 ,y = 10; // burada y deðiþkeni de const keywordünün kapsamasýna dahil edilir. 
							y deðiþkeni üzerinde deðiþiklik yapýlamaz. READ-ONLY.

const int x = 10 ile int const x = 10 arasýnda fark yok. Ýkiside ayný anlamda.Pointerda birazcýk farklý.
									  dereferencing operatöründen önce ve sonra olmasý farklý anlamda oluyor.

const static int x; == static const int x;

-------------------------------------------------
const keywordüyle tanýmlanmýþ deðiþkenlerin deðerlerinin deðiþtirilmesi sentaks hatasý. Fakat C'de kolay bir þekilde bu yapýlabiliyor.

const int x = 20;
int* p = &x;
*p = 10; // Sentaks hatasý vermez, FAKAT UNDEFINED BEHAVIOUR.
		// printf("%d", x); ekrana 10 yazdýrýr FAKAT UB.

int main(void)
{
	const int x = 10;
	x++; // sentaks hatasý. IMMUTABLE

}
CONST VS OBJECT-LIKE MACRO
- Hangisini kullandýðýmýz fark etmez.
- Eðer bir fonksiyona adres gönderiliyorsa macro yerine const kullanýlmalý. Çünkü macrolarýn adresi yok :D
- const ile tanýmlanmýþ bir tam sayý deðiþkeni bir dizinin boyutunu belirlemek için kullanýlamaz. Macro kullanýlabilir. 
int main(void)
{
	const int arr_size = 10;
	int arr[arr_size] = { 0 }; // Bu C dilinde geçerli deðil, CPP'de sýkýntý yok.
	


}
	int x = 10;
	int y = 20;


	int * const ptr = &x; const pointer to int þeklinde ifade edilir.yada Top-Level const
	burada ptr ýn deðerinin deðiþemeyeceðini belirtiyor.Yani ptr hayatý boyunca hep
	x i gösterecek ama *ptr (yani x) i deðiþtirebilirim. *ptr = 25; iþleminde sorun yok.
	ama ptr = 0x123A... Sentaks hatasý.

	*ptr = y; sentaks hatasý deðil.
	ptr = &y; sentaks hatasý.

	int* ptr = 2400; // C'de bunda sýkýntý yok ama CPP'de sentaks hatasý.
	int* ptr = (int*)2400; // Hem C hem de CPP okey. Bu tarz deðerlere "ADRES SABÝTÝ" denir.

const keywordünün asterisk operatörüdnen önce veya sonra kullanýlmasý farklý bir anlam oluþturuyor.
	Önemli olan const keywordünün asterisk operatöründen önce veya sonra olmasý. 
1-	int * const p1 = &x;  // const pointer to int veya top-level const veya rightconst
							burada kast edilen p1'in deðerinin deðiþmeyeceði. p1'in deðeri hayatý boyunca x'in adresi olacak.
							x'in deðeri ve buna baðlý olarak *p1'in deðeri deðiþebilir ancak p1'in deðeri DEÐÝÞMEZ. IMMUTABLE
		p1 = &y; // SENTAKS HATASI
	   *p1 = 45; // Sýkýntý yok
	

2-	int const * p2 = &x; // pointer to const int veya low-level const veya left const
3-	const int * p3 = &x;	burada kast edilen eriþtiðimiz nesneyi sadece salt okuma(read only) için eriþebileceðimiz anlamýna geliyor.
							yani p2'nin deðeri deðiþtirilebilir fakat eriþtiði adresin nesnesi deðiþemez.
		p2 = &y; // SENTAKS HATASI YOK
		*p2 = 55; // SENTAKS HATASI.
		x = 33; // sentaks hatasý yok çünkü x const deðil.
		// ÖNEMLÝ:
			Bu durum bize p2'nin eriþtiði nesnenin deðeri *ptr üzerinden deðiþtirilemeyeceðini gösteriyor. x'in deðeri deðiþtirilebilir
				fakat p2'nin adresini kullanarak içerik operatörü ile deðiþtirilemeyeceði anlamýna gelir!.
	2 ve 3. durumlar ayný anlama geliyor. Önemli olan const keywordünün asteriskin hangi tarafýnda olduðu.
	
	const int* const ptr = &x; // const pointer to const int
									Burada hiçbir þey deðiþtirilemez. ptr'nin deðeri x'in adresi olacak ve ne ptr'nin deðeri 
									ne de x'in deðeri ptr üzerinden içerik operatörü kullanýlarak deðiþtirilebilecek.
	ptr = &y; // SENTAKS HATASI
	*ptr = 5; // SENTAKS HATASI


void foo(int* x) // foo bir mutator fonksiyon. x nesnesine eriþecek ve deðiþiklik yapabilecek.
void bar(const int* x) // bar bir accessor yani sadece o deðere eriþecek bir deðiþiklik yapamayacak.  burada pointer to const var ve *ptr deðiþmeyecek
EN SIK YAPILAN HATA ÞU.
	void print_array(int* p, int size); // bu fonksiyon const dizileri yazdýrmak için kullanýlamaz.
		a) yalan söylemiþ olursunuz. Parametrenin int* olduðunu görünce bunu bir mutator kabul etmek zorunda.
			fakat bu fonksiyon bir accessor, sadece dizinin elemanlarýný okuyup ekrana yazdýrýyor.
		b) 
	void print_array(const int* p, const int size); // DOÐRU HALÝ böyle. bu fonksiyon const dizileri yazdýrmak için kullanýlabilir.
	-----------------------------
	-----------------------------

	strlen() parametresi const char * , yani boyutunu alacak parametre deðiþmeyecek
	_strrev parametresi char * , çünkü yazý ters çevrilecek.
	strcmp() iki parametresi var.parametreleri const char * çünkü karþýlaþtýrma var.deðiþtime yok.

	burada const char * ve ya const int * ...
	olarak yazýlan parametre deðiþkenleri þunu belirtiyor.
	Eðer deðiþmemesi gereken bir veri varsa bunu deðiþtirmeye çalýþtýðýnda sentaks hatasý ver
	gibi bir aksiyon almýþ oluyoruz.Ve kodu okuyanda zaten const deðiþkenin deðiþmeyeceðini
	anlamasý gerekiyor.


	===================================================
	===================================================
	===================================================	

				-------------------------------------------- DÝZÝLERÝN FONKSÝYONA GÖNDERÝLMESÝ -------------------------------------------- 

	Bu dizinin adresini göndermek ile mümkün.

	//Az tercih edilen
	void print_array(cont int * ptr, int size)
	{
		for(int i = 0;i<size;i++)
		{
			printf("%d ",ptr[i]);
		}
		printf("\n--------------------------\n");
	}


	// daha çok tercih edilen
	void print_array(const int * ptr, int size)
	{
		while(size--)
		{
			printf("%d ",*ptr);
			ptr++;
		}
		printf("\n--------------------------\n");
	}

	int main()
	{
		int a[10] = { 0,1,2,3,4,5,6,7,8,9};
		print_array(a,10);

	}

	DÝKKAT!
	print_array de pointer olarak gönderilen nesne kesinlikle const keyword ü ile nitelenmeli.
	Yapýlmazsa büyük hata olur. Mülakatlarda çok dikkat ediyorlar.

	const int* p = &x;

	int* ptr = p; // bu sentaks olarak doðru olsa da sýkýntýlý bir durum.
	p nesnesi x'in adresine sadece salt okuma için eriþiyor. Fakat biz p nesnesinin gösterdiði adresi ptr'a set edersek.
		ptr üzerinden x'in deðerini deðiþtirebiliriz. Bu da sýkýntýlara yol açabilir.
	const T* ===> T* örtülü(implicit) conversion yapmayýn.
	T* ===> const T* sýkýntý yok.
	int x = 10;
	&x; // int*
	const int y = 20;
	&y; // const int*

	öyle durumlar var ki; 
	const T* ===> T* // kafa karýþýklýðýný önlemek için type conversion operatörüu kullanýlmalý
	const T* ===> (int*)T* böyle yazýlýrsa sýkýntý yok. "const cast"
*/

