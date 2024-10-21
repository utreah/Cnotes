/*Storage class modifiers - Type Modifiers*/
/*
	auto, register, extern, static, const, volatile, restrict bu keywordler.
	typedef -> standart bunu da modifier olarak al�yor fakat necati hoca uygun bulmuyormu� burada olmas�n�.

	auto: C'de kullan�mdan d��m�� bir keyword. Hoca, bunu hi� kullanmayacaks�n�z dedi.
	register: auto ile ayn�, derleyicilerin ve teknolojinin geli�mesi ile buna da gerek kalmam��.
	

	Storage Class Specifiers:
	- auto -> C'de kullan�mdan d��se de Modern CPP ile anlam� de�i�ti bunun. C auto != CPP auto 
		- Gelen anlam de�i�ikli�i ile beraber C'de kullan�mdan d��m�� olmas�na ra�men CPP'de en �ok kullan�lan
			keywordlerde ilk ��.
		- Type Deduction: C statik dil kavram�na sahip oldu�u i�in her bir de�i�kenin bir t�r� olmak zorunda.
			De�i�kenin sahip oldu�u de�ere bak�larak hangi t�r oldu�unun anla��lmas�na 'Type Deduction'
				yani 'T�r ��kar�m�' deniyor. E�er CPP'de auto'yu kullan�yor olsayd�k.
					auto x = 10; // burada auto yerine int olurdu, double t�r�nden olsayd� double olacakt�.
		- C'de kullan�m amac� ise de�i�kenin �mr�n�n otomatik oldu�unu s�ylemek.
			int x = 10; // x burada otomatik �m�rl�
			static int y = 12; // y burada statik �m�rl�
			auto int z = 10; // z burada da otomatik �m�rl�.
			�u �rne�e bak�larak neden kullan�mdan d��t��� anla��labilir.
		- auto global de�i�kenlerin ba��na gelemez. Sentaks hatas�.
		- Fonksiyonlar�n parametreleri otomatik �m�rl� olmak zorunda oldu�u i�in fonksiyon parametrelerinde kullan�lmas�
			sentaks hatas�.
------------------------------------------------------
	- register: Register, eski zamanlarda(15-20 y�l �nce) bir de�i�kenin �zerinde bir i�lemin yap�labilmesi i�in
		�rne�in, fiilen de�erini de�i�tirmek i�in de�i�kenin bir i�lemcinin 'register'inde tutulmas� gerekiyor.
			register, i�lemlerin fiilen yap�ld��� bir bellek alan�.
		- Bir de�i�kenin register keyword� ile tan�mlanmas�yla derleyiciye "bu de�i�keni registerda tutar m�s�n l�tfen?"
			diyoruz. Rica ediyoruz, emir vermiyoruz - ba�lay�c� de�il bu.
		- register ile tan�mlanm�� bir de�i�kene bellekten, i�lemcinin register k�sm�na yap�lacak kopyalama i�leminin
			maaliyetini kald�r�yor. Normalde bellekte olsayd� kopyalama i�lemi(yeni de�er atama vs) yap�l�rken bir
				maliyet olacak(instructionlar �al��acakt�) ama register olunca bu maliyet yok.
		- �ok s�k kullan�lan, �zerinde �ok i�lem yap�lan de�i�kenlerde kullan�l�rd�. Mesela d�ng� i�erisindeki de�i�kenler.
		- Kullan�mdan d��me sebebi;
			Bu bir rica oldu�u i�in derleyicinin bunu ger�ekle�tirme garantisi yok.
			�kinci olarakta, teknolojinin ve derleyicilerin geli�mesi ile derleyiciler bu i�lemlerin optimizasyonunu
				�ok iyi yaptu�u i�in register keywordu kullan�mdan d��t�(standartta var ama kullan�mda yok)
		- statik �m�rl� de�i�kenlerin register keyword� ile tan�mlanmas� sentaks hatas�.
		- Parametre de�i�kenleri ve yerel de�i�kenlerinde kullan�labilir.
			int square(register int x){
				return x * x;
			}
		- CPP'nin son standart� ile beraber dilden kald�r�ld�, ba�ka bir anlam y�klemek �zere rezerve edildi.
		- register keyword� ile tan�mlanm�� bir de�i�ken addressof(&) operat�r�n�n operand� olamaz.
			register int x = 10;
			int* p = &x; // bu sentaks hatas�
------------------------------------------------------

	- static: keyword�n kullan�ld��� yere g�re iki farkl� anlam� var.
		- Yerel de�i�kenlerle kullan�lan 'static ' keyword� de�i�kenin �mr�n� statik yapar.
		- Global bir de�i�ken ile static keyword� ile tan�mlanm�� bir de�i�ken aras�nda �m�r a��s�ndan bir fark yok.
		- Global - static yerel de�i�kenler aras�nda Scope fark� var.
			Bir de�i�kene birden fazla kaynak-ba�l�k dosyas�n�n eri�mesini istiyor isek o de�i�keni global
				yapmak zorunday�z. E�er sadece belirli bir fonksiyonu alakadar ediyor ise static local variable yap�yoruz.

		Static keyword�n�n kullan�ld��� temalar:
			- Diyelim ki bir fonksiyon de�er d�nd�recek. Fonksiyon bu i�lemi yapmak i�in bir statik �m�rl�
				bir de�i�ken olu�turuyor ve bu de�i�kenin adresini d�nd�r�yor. Fonksiyonu �a��ran kodta bu de�i�keni
					kullanarak yap�yor i�lemlerini. 
					char* random_psy(void){
						static char str[100];
						int len = rand() % 5 + 4;
						for (int i = 0; i < size; i++)
							str[i] = rand() % 26 + 'A';
						return str;
					} // mesela bu fonksiyon random bir �ifre olu�turup, statik char dizisine kaydedip adresini d�nd�r�yor.

			- Bir fonksiyonun daha �nceki �a�r�lardan eldi etti�i de�erleri sonraki �a�r�larda kullanmas�.
				Daha �nceki de�erler ile gelecekte kullan�lacak de�erler aras�nda bir benzerlik oluyor.
				Mesela fonksiyon i�erisinde kullan�lacak bir flag de�i�keni buna �rnek verilebilir.

					void func(void){
						static int flag = 1;
						if(flag){
							printf("Fonksiyon ilk kez cagrildi");
							flag = 0;
						}
						// bu fonksiyon 2. kez �a�r�ld���nda if blo�una girmeyecek. E�er flag de�i�keni statil olmasayd�
							// her �a�r�ld���nda tekrar tan�mlanaca�� i�in her seferinde if blo�una girecekti.
						// Global de�i�ken niye yapmad�k? Kafalar kar��mas�n diye. Kodu okuyan, global namespacedeki
							// o statik de�i�keni g�r�p de�i�iklik yapmas�n diye. Globalde olunca her yerden eri�ilebiliyor
								// bu da kafa kar���kl��� yapabilir.
					}
------------------------------------------------------ 
#define	URAND_MAX 20
int urand(void){
	static int flags[URAND_MAX] = { 0 };
	static int cnt = 0;
	if (cnt == URAND_MAX)
		return -1;
		int	val;
	while(1){
		val = = rand() % URAND_MAX;
		if(flags[i] == 0)
			break;
	}
	flags[val] = 1;
	++cnt;
	return val;
}
------------------------------------------------------
			- ���nc� bir kullan�m yeri ise diziler. Baz� dizileri lookup table olarak kullan�yoruz. 
				void foo(int n){
					static const int primes[100] = {2, 3, 5, 7, 11, 13, 17, 19, 23}; // ilk 100 asal say� varm�� gibi
					 // burada ama� �u. Fonksiyona verilen n de�erinin asal say�s�n� hesaplamak yerine n'in denk geldi�i asal say�y� dizinin i�erisinde bulup kullanma
						// olay�na lookup table deniyor. Maaliyeti yok bunun ondan dolay�. Fakat, bu int primes dizisinin Immutable olmas� gerek. ��nk� i�erisindeki herhangi bir
							// de�er de�i�ir ise bu tablo tamamen yanl�� hale gelir. Bundan dolay� const keyword�n� ekliyorum.
					// Bir di�er problem ise, bu dizi otomatik �m�rl� oldu�u i�in her �al��t�r�ld���nda primes dizisi bellekte tekrardan 100 eleman� ile beraber hayata getirilecek.
						// bu da b�y�k bir problem bak�ld��� zaman. Bunun �n�ne ge�mek i�inde static keyword�n� ekliyorum.

					// namelookup tablelar genellikle static const oluyor anlad���m kadar�yla. const keyword�, tablonun de�i�mesini �nlemek i�in, static ise tablonun elemanlar�n�n,
						// her �a�r�ld��� seferde tekrar tekrar olu�turulma maaliyetini kesmek i�in.

				}

------------------------------------------------------
Linkage(ba�lant�) 
	Bir C program� birden fazla kaynak dosyas�ndan olu�uyor. E�er farkl� kaynak dosyalar�nda kullan�lan ayn� isimler, �al��ma zaman�nda
		ayn� varl��a i�aret ediyor ise buna external linkage deniyor. Linkage, scope'un birden fazla kaynak dosyas�n� i�ine alm�� olmas� gibi.
			Scope sadece bulundu�u kaynak dosyas�n� ilgilendirirken, linkage projedeki t�m kaynak dosyalar�n� ilgilendiriyor.

		Bu ba�lant�lar ��e ayr�l�yor;
		- External	linkage ( d�� ba�lant� ):	Ayn� de�i�keni birden fazla farkl� kaynak dosyas�nda kullan�yorum fakat run-time'da hepsi ayn� nesneyi g�steriyor.
		- Internal	linkage ( i� ba�lant� )	:	Bir isim internal linkage'a ait ise o nesne belirli bir kaynak dosyas�na ait, ba�ka bir kaynak dosyas�nda ba�ka bir nesneye ait olaB�L�R.
		- No		linkage ( ba�lant�s�z )	:	Kendi kaynak dosyamda bile her yerde eri�emedi�im nesneler ise 'no linkage' kategorisine giriyor

// engin.c
	int g = 10; // e�er bu de�i�keni projenin di�er kaynak dosyalar�nda da kullanmak istiyorsam external linkage'a ait yapmal�y�m.
					// E�er ayn� nesne birden fazla kaynak dosyas�nda tan�mlan�r ve external linkage'a ait ise, LINKER(LNK) a�amas�nda en iyi ihtimalle hata al�r�z.
				// ba�ka projeler taraf�ndan kullan�lmas�n, nesne ad�n�n birden fazla kullan�m�n� engellemek, sadece ait oldu�u kaynak dosyas�nda kullan�lmas� i�in ise internal linkage'a ait olmal�.
	// E�er tan�mlamada keyword kullanmaz isek otomatik olarak de�i�kenler/fonksiyonlar external linkage'a ait say�l�yor.
// kendarli.c
	int k = 20; // external linkage'a ait bu
	void foo(void){
		/- code -/
	}
// engin.c
	static int c = 10; // global namespacedeki nesneler static keyword� ile tan�mlan�rsa, tan�mlanan bu de�i�kenler internal linkage'a ait olur.
	static void bar(void){
		/- code -/
	
	}
	// burada c ve bar'�n di�er mod�llere kapat�ld���n�, ba�ka mod�llerde kullan�lamayaca��n� s�yl�yor.
------------------------------------------------------
	
	- extern: Bu keyword e�er bir nesnenin tan�m�nda kullan�l�rsa, derleyiciye kullan�lan nesnenin ba�ka bir mod�lden al�nd���n� s�yl�yor.
		Mesela, ali.c i�erisinde tan�mlanm�� int x = 10; nesnesini kullanabilmek i�in engin.c dosyas�nda
			extern int x; �eklinde bildirim yapmam gerekiyor. Bu yap�lan bildirimi non-defining declaration deniyor.
				
	//engin.h
		extern int g;
	//engin.c
		int g = 10;

	//Di�er mod�ller engin.h'y� include etmeleri halinde, di�er mod�llerde g �zerinde yap�lan t�m de�i�iklikler engin.c i�erisinde bulunan
		g nesnesi �zerinde yap�lacak.

	// diziler i�in extern bildirimi yap�l�rken dizi boyutu k�sm� bo� b�rak�labilir.
		// kendarli.h
			extern int arr[];
		// kendarli.c
			int arr[100] = { 0 };

	E�er bulundu�u mod�le ait olmas�n� istiyorsan�z nesnenin tan�m�n� static keyword� ile yapacaks�n ve ba�l�k dosyas�na tan�m�n� koymayacaks�n

	B�t�n kurallar fonksiyonlar i�inde ge�erli ve ayn�.
		Tek fark, fonksiyonlar�n, ba�l�k dosyalar�ndaki, bildirimlerinde extern keyword�n�n bulunmas�na gerek yok. (bulunabilir ama gerek yok)
		
	External Linkage'a ait bir nesne birden fazla kez tan�mlan�rsa bu hata linker taraf�ndan yakalan�r. Kodlar derlenir ama link a�amas�nda cort.
		// Varl�klar�n bir tane tan�m� olabilir. CPP'de bunun i�in bir kural var One Definition Rule(ODR)

		engin.c
		int x = 10; // bu de�i�ken engin.c i�erisinde hi� kullan�lmamas� durumunda lojik hata olu�turmaz. ��nk�, external linkage'a ba�l�
						// oldu�u i�in di�er mod�llerden eri�im olabilir.
		static int c = 20; // e�er bunu engin.c i�erisinde hi� kullanmaz isem bu lojik hata.
------------------------------------------------------
Global namespace pollution problem(Global isim alan�n�n kirlilik/kalabal�k problemi): D��ar� a��lm��(ext linkage) nesnelerin tek olmas� gerekiyor.
	�ak��ma olas�l��� y�ksek olan isimleri kullan�rsak, kodu yazan ki�i o nesnenin ismini ba�ka bir mod�lde kullanamaz. �sim �ak��mas� do�rudan link a�amas�nda problem olur.

	Bunun �n�ne ge�mek i�in nesnelerin isimleri �zelle�tiriliyor. Mesela, encryption alan�nda  bir k�t�phane deste�i veriyoruz.
	k�t�phanead�_isleminadi_fonksiyonad�(void) -> tabii bu ba�ka �ekillerde de yap�labilir bu sadece bir �rnek.
	CPP'de b�yle bir problem yok. CPP'de namespace denen bir �zellik var. Nesneler direkt olarak global isimalan�na bo�alt�lmak yerine 
		namespaceler i�erisinde enjekte ediliyor. Bu sayede �ak��ma problemleri olmuyor ��nk� her isim kendi namespace'inde.

------------------------------------------------------
	Type modifier(Type qualifiers): De�i�kenin t�rleri �zerinde etkiyi sahipler
	const - volatile - restrict - typedef

	- Type modifiers implicit int kural�n� uygularlar. E�er bir nesnenin t�r� belirtilmediyse int kabul edilir.

	Const: Nesnenin de�erinin de�i�tirilemeyece�ini vurguluyor. Immutable yap�yor yani nesneyi.
		Const bir nesnenin de�eri de�i�tirilemez sentaks hatas� verir. const olmas� gereken ama const olmayan bir nesnede de�i�iklik yaparsak
			bu sentaks hatas� de�il ama lojik bir hata.


*/

/*
	NOT: extern k�sm�nda bulunan extern int x; bir definition de�il declaration. E�er bir de�i�ken define ediliyor ise 
		bu, derleyicinin o nesne i�in bellekte bir yer ay�raca�� anlam�na geliyor. extern int x ile yeni bir de�i�ken tan�m� de�il
			hali haz�rda ba�ka bir mod�lde bulunan bir nesnenin bildirimi yap�l�yor. Tan�mlama olmayan bildirimlere non-defining declaration denir.


*/