/*
				-------------------------------------------------CONST KEYWORD-------------------------------------------------
En �nemli 3 keywordten birisi diyor hoca.
Const'un da i�inde bulundu�u bir anahtar s�zc�k k�mesi ve buna "type qualifier(t�r niteliyici)" deniyor.

CONST CORRECTNESS: const anahtar s�zc���n�n do�ru kullan�lmas�na const correctness deniyor.

mutate:
mutator: De�i�tiren, �zellikle fonksiyonlar� niteliyor. Nesne al�yor ve o nesneyi de�i�tiriyor
Accessor: Nesne al�yor ama sadece okumak i�in kullan�yor.
mutable: De�i�tirilebilir(varl�k) anlam�na geliyor.
immutable: De�i�tirilemez(varl�k) anlam�na geliyor.

void foo(int* a) // foo fonksiyonu bi mutator ��nk� adresini ald��� nesneyi de�i�tirebilir.
void bar(const int* a) // bar bir accessor ��nk� adresini ald��� nesneyi sadece okuyabilir, DE���T�REMEZ.
const keywordu olan bir de�i�kenin ilk de�erinin tam say� olma gibi bir zorunlulu�u yoktur.
--------------------------------------------------------------------------------------------------

const int x = 10; // Bu de�i�kenin de�erinin hayat� boyunca de�i�meyece�ini ve sadece salt okuma olarak kullan�laca��n� s�yl�yor.
					// const keyword�n�n anlam� bu. Immutable bir de�i�ken olu�turmaya yar�yor.
const int x = 10; // bu ayn� zamanda 'oksimoron' bir ifade. const immutable, de�i�ken ise ad�ndan da anla��labilece�i i�in bir biri ile �eli�iyor
					// olsa da �al��mas�nda bir s�k�nt� yoktur. 
		x de�i�keni hayata 10 de�eri ile geliyor ve program�n sonuna kadar bu de�erini koruyacak!
		++x; // bu bir sentaks hatas�. ��nk� x'in de�eri de�i�tirilemez.
		x = 20; sentaks hatas�


		// E�er de�i�tirilmemesi gereken  bir dizi veya de�i�ken var ise const kullan�l�r.
int main(void){
	const int x = 10;
	const int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}
	// Burada const kullanmak derleyicye bir kontrol y�k�ml�l��� sa�l�yor.
	// E�er const bir nesneyi de�i�tirmeye �al���rsan�z dilin kurallar�na ayk�r� bir durum oluyor(sentaks hatas�)
	x = 45; // SENTAKS HATASI
	primes[3]; // eri�ilebilir s�k�nt� yok
	printf("%d",primes[3]); // burada da s�k�nt� yok
	primes[2] = 10; // hop sentaks hatas�.
}

 const anahtar s�zc���n� gerekli olan yerlerde kullan�rsak 
 	1 - const keyword kodu okuyan�nda/yazan�nda i�ini kolayla�t�r�yor.
	
	2 - int a[]; bu dizi mutable oldu�unu g�sterir.write edilebilir oldu�unu g�sterir.
		const int a[]; bu ise immutable bir dizi.elemanlar� de�i�tirilemez.write ama�l� kullan�lmayacak demek.
	
	3 - const keyword kodun optimizasyonuna faydal�d�r.
		kesinlikle daha iyi kod �retir denemez ama �retecek duruma getirir.


const int x = 5 ,y = 10; // burada y de�i�keni de const keyword�n�n kapsamas�na dahil edilir. 
							y de�i�keni �zerinde de�i�iklik yap�lamaz. READ-ONLY.

const int x = 10 ile int const x = 10 aras�nda fark yok. �kiside ayn� anlamda.Pointerda birazc�k farkl�.
									  dereferencing operat�r�nden �nce ve sonra olmas� farkl� anlamda oluyor.

const static int x; == static const int x;

-------------------------------------------------
const keyword�yle tan�mlanm�� de�i�kenlerin de�erlerinin de�i�tirilmesi sentaks hatas�. Fakat C'de kolay bir �ekilde bu yap�labiliyor.

const int x = 20;
int* p = &x;
*p = 10; // Sentaks hatas� vermez, FAKAT UNDEFINED BEHAVIOUR.
		// printf("%d", x); ekrana 10 yazd�r�r FAKAT UB.

int main(void)
{
	const int x = 10;
	x++; // sentaks hatas�. IMMUTABLE

}
CONST VS OBJECT-LIKE MACRO
- Hangisini kulland���m�z fark etmez.
- E�er bir fonksiyona adres g�nderiliyorsa macro yerine const kullan�lmal�. ��nk� macrolar�n adresi yok :D
- const ile tan�mlanm�� bir tam say� de�i�keni bir dizinin boyutunu belirlemek i�in kullan�lamaz. Macro kullan�labilir. 
int main(void)
{
	const int arr_size = 10;
	int arr[arr_size] = { 0 }; // Bu C dilinde ge�erli de�il, CPP'de s�k�nt� yok.
	


}
	int x = 10;
	int y = 20;


	int * const ptr = &x; const pointer to int �eklinde ifade edilir.yada Top-Level const
	burada ptr �n de�erinin de�i�emeyece�ini belirtiyor.Yani ptr hayat� boyunca hep
	x i g�sterecek ama *ptr (yani x) i de�i�tirebilirim. *ptr = 25; i�leminde sorun yok.
	ama ptr = 0x123A... Sentaks hatas�.

	*ptr = y; sentaks hatas� de�il.
	ptr = &y; sentaks hatas�.

	int* ptr = 2400; // C'de bunda s�k�nt� yok ama CPP'de sentaks hatas�.
	int* ptr = (int*)2400; // Hem C hem de CPP okey. Bu tarz de�erlere "ADRES SAB�T�" denir.

const keyword�n�n asterisk operat�r�dnen �nce veya sonra kullan�lmas� farkl� bir anlam olu�turuyor.
	�nemli olan const keyword�n�n asterisk operat�r�nden �nce veya sonra olmas�. 
1-	int * const p1 = &x;  // const pointer to int veya top-level const veya rightconst
							burada kast edilen p1'in de�erinin de�i�meyece�i. p1'in de�eri hayat� boyunca x'in adresi olacak.
							x'in de�eri ve buna ba�l� olarak *p1'in de�eri de�i�ebilir ancak p1'in de�eri DE���MEZ. IMMUTABLE
		p1 = &y; // SENTAKS HATASI
	   *p1 = 45; // S�k�nt� yok
	

2-	int const * p2 = &x; // pointer to const int veya low-level const veya left const
3-	const int * p3 = &x;	burada kast edilen eri�ti�imiz nesneyi sadece salt okuma(read only) i�in eri�ebilece�imiz anlam�na geliyor.
							yani p2'nin de�eri de�i�tirilebilir fakat eri�ti�i adresin nesnesi de�i�emez.
		p2 = &y; // SENTAKS HATASI YOK
		*p2 = 55; // SENTAKS HATASI.
		x = 33; // sentaks hatas� yok ��nk� x const de�il.
		// �NEML�:
			Bu durum bize p2'nin eri�ti�i nesnenin de�eri *ptr �zerinden de�i�tirilemeyece�ini g�steriyor. x'in de�eri de�i�tirilebilir
				fakat p2'nin adresini kullanarak i�erik operat�r� ile de�i�tirilemeyece�i anlam�na gelir!.
	2 ve 3. durumlar ayn� anlama geliyor. �nemli olan const keyword�n�n asteriskin hangi taraf�nda oldu�u.
	
	const int* const ptr = &x; // const pointer to const int
									Burada hi�bir �ey de�i�tirilemez. ptr'nin de�eri x'in adresi olacak ve ne ptr'nin de�eri 
									ne de x'in de�eri ptr �zerinden i�erik operat�r� kullan�larak de�i�tirilebilecek.
	ptr = &y; // SENTAKS HATASI
	*ptr = 5; // SENTAKS HATASI


void foo(int* x) // foo bir mutator fonksiyon. x nesnesine eri�ecek ve de�i�iklik yapabilecek.
void bar(const int* x) // bar bir accessor yani sadece o de�ere eri�ecek bir de�i�iklik yapamayacak.  burada pointer to const var ve *ptr de�i�meyecek
EN SIK YAPILAN HATA �U.
	void print_array(int* p, int size); // bu fonksiyon const dizileri yazd�rmak i�in kullan�lamaz.
		a) yalan s�ylemi� olursunuz. Parametrenin int* oldu�unu g�r�nce bunu bir mutator kabul etmek zorunda.
			fakat bu fonksiyon bir accessor, sadece dizinin elemanlar�n� okuyup ekrana yazd�r�yor.
		b) 
	void print_array(const int* p, const int size); // DO�RU HAL� b�yle. bu fonksiyon const dizileri yazd�rmak i�in kullan�labilir.
	-----------------------------
	-----------------------------

	strlen() parametresi const char * , yani boyutunu alacak parametre de�i�meyecek
	_strrev parametresi char * , ��nk� yaz� ters �evrilecek.
	strcmp() iki parametresi var.parametreleri const char * ��nk� kar��la�t�rma var.de�i�time yok.

	burada const char * ve ya const int * ...
	olarak yaz�lan parametre de�i�kenleri �unu belirtiyor.
	E�er de�i�memesi gereken bir veri varsa bunu de�i�tirmeye �al��t���nda sentaks hatas� ver
	gibi bir aksiyon alm�� oluyoruz.Ve kodu okuyanda zaten const de�i�kenin de�i�meyece�ini
	anlamas� gerekiyor.


	===================================================
	===================================================
	===================================================	

				-------------------------------------------- D�Z�LER�N FONKS�YONA G�NDER�LMES� -------------------------------------------- 

	Bu dizinin adresini g�ndermek ile m�mk�n.

	//Az tercih edilen
	void print_array(cont int * ptr, int size)
	{
		for(int i = 0;i<size;i++)
		{
			printf("%d ",ptr[i]);
		}
		printf("\n--------------------------\n");
	}


	// daha �ok tercih edilen
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

	D�KKAT!
	print_array de pointer olarak g�nderilen nesne kesinlikle const keyword � ile nitelenmeli.
	Yap�lmazsa b�y�k hata olur. M�lakatlarda �ok dikkat ediyorlar.

	const int* p = &x;

	int* ptr = p; // bu sentaks olarak do�ru olsa da s�k�nt�l� bir durum.
	p nesnesi x'in adresine sadece salt okuma i�in eri�iyor. Fakat biz p nesnesinin g�sterdi�i adresi ptr'a set edersek.
		ptr �zerinden x'in de�erini de�i�tirebiliriz. Bu da s�k�nt�lara yol a�abilir.
	const T* ===> T* �rt�l�(implicit) conversion yapmay�n.
	T* ===> const T* s�k�nt� yok.
	int x = 10;
	&x; // int*
	const int y = 20;
	&y; // const int*

	�yle durumlar var ki; 
	const T* ===> T* // kafa kar���kl���n� �nlemek i�in type conversion operat�r�u kullan�lmal�
	const T* ===> (int*)T* b�yle yaz�l�rsa s�k�nt� yok. "const cast"
*/

