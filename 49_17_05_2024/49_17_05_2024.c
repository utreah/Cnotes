/*Storage class modifiers - Type Modifiers*/
/*
	auto, register, extern, static, const, volatile, restrict bu keywordler.
	typedef -> standart bunu da modifier olarak alýyor fakat necati hoca uygun bulmuyormuþ burada olmasýný.

	auto: C'de kullanýmdan düþmüþ bir keyword. Hoca, bunu hiç kullanmayacaksýnýz dedi.
	register: auto ile ayný, derleyicilerin ve teknolojinin geliþmesi ile buna da gerek kalmamýþ.
	

	Storage Class Specifiers:
	- auto -> C'de kullanýmdan düþse de Modern CPP ile anlamý deðiþti bunun. C auto != CPP auto 
		- Gelen anlam deðiþikliði ile beraber C'de kullanýmdan düþmüþ olmasýna raðmen CPP'de en çok kullanýlan
			keywordlerde ilk üç.
		- Type Deduction: C statik dil kavramýna sahip olduðu için her bir deðiþkenin bir türü olmak zorunda.
			Deðiþkenin sahip olduðu deðere bakýlarak hangi tür olduðunun anlaþýlmasýna 'Type Deduction'
				yani 'Tür Çýkarýmý' deniyor. Eðer CPP'de auto'yu kullanýyor olsaydýk.
					auto x = 10; // burada auto yerine int olurdu, double türünden olsaydý double olacaktý.
		- C'de kullaným amacý ise deðiþkenin ömrünün otomatik olduðunu söylemek.
			int x = 10; // x burada otomatik ömürlü
			static int y = 12; // y burada statik ömürlü
			auto int z = 10; // z burada da otomatik ömürlü.
			Þu örneðe bakýlarak neden kullanýmdan düþtüðü anlaþýlabilir.
		- auto global deðiþkenlerin baþýna gelemez. Sentaks hatasý.
		- Fonksiyonlarýn parametreleri otomatik ömürlü olmak zorunda olduðu için fonksiyon parametrelerinde kullanýlmasý
			sentaks hatasý.
------------------------------------------------------
	- register: Register, eski zamanlarda(15-20 yýl önce) bir deðiþkenin üzerinde bir iþlemin yapýlabilmesi için
		örneðin, fiilen deðerini deðiþtirmek için deðiþkenin bir iþlemcinin 'register'inde tutulmasý gerekiyor.
			register, iþlemlerin fiilen yapýldýðý bir bellek alaný.
		- Bir deðiþkenin register keywordü ile tanýmlanmasýyla derleyiciye "bu deðiþkeni registerda tutar mýsýn lütfen?"
			diyoruz. Rica ediyoruz, emir vermiyoruz - baðlayýcý deðil bu.
		- register ile tanýmlanmýþ bir deðiþkene bellekten, iþlemcinin register kýsmýna yapýlacak kopyalama iþleminin
			maaliyetini kaldýrýyor. Normalde bellekte olsaydý kopyalama iþlemi(yeni deðer atama vs) yapýlýrken bir
				maliyet olacak(instructionlar çalýþacaktý) ama register olunca bu maliyet yok.
		- Çok sýk kullanýlan, üzerinde çok iþlem yapýlan deðiþkenlerde kullanýlýrdý. Mesela döngü içerisindeki deðiþkenler.
		- Kullanýmdan düþme sebebi;
			Bu bir rica olduðu için derleyicinin bunu gerçekleþtirme garantisi yok.
			Ýkinci olarakta, teknolojinin ve derleyicilerin geliþmesi ile derleyiciler bu iþlemlerin optimizasyonunu
				çok iyi yaptuðu için register keywordu kullanýmdan düþtü(standartta var ama kullanýmda yok)
		- statik ömürlü deðiþkenlerin register keywordü ile tanýmlanmasý sentaks hatasý.
		- Parametre deðiþkenleri ve yerel deðiþkenlerinde kullanýlabilir.
			int square(register int x){
				return x * x;
			}
		- CPP'nin son standartý ile beraber dilden kaldýrýldý, baþka bir anlam yüklemek üzere rezerve edildi.
		- register keywordü ile tanýmlanmýþ bir deðiþken addressof(&) operatörünün operandý olamaz.
			register int x = 10;
			int* p = &x; // bu sentaks hatasý
------------------------------------------------------

	- static: keywordün kullanýldýðý yere göre iki farklý anlamý var.
		- Yerel deðiþkenlerle kullanýlan 'static ' keywordü deðiþkenin ömrünü statik yapar.
		- Global bir deðiþken ile static keywordü ile tanýmlanmýþ bir deðiþken arasýnda ömür açýsýndan bir fark yok.
		- Global - static yerel deðiþkenler arasýnda Scope farký var.
			Bir deðiþkene birden fazla kaynak-baþlýk dosyasýnýn eriþmesini istiyor isek o deðiþkeni global
				yapmak zorundayýz. Eðer sadece belirli bir fonksiyonu alakadar ediyor ise static local variable yapýyoruz.

		Static keywordünün kullanýldýðý temalar:
			- Diyelim ki bir fonksiyon deðer döndürecek. Fonksiyon bu iþlemi yapmak için bir statik ömürlü
				bir deðiþken oluþturuyor ve bu deðiþkenin adresini döndürüyor. Fonksiyonu çaðýran kodta bu deðiþkeni
					kullanarak yapýyor iþlemlerini. 
					char* random_psy(void){
						static char str[100];
						int len = rand() % 5 + 4;
						for (int i = 0; i < size; i++)
							str[i] = rand() % 26 + 'A';
						return str;
					} // mesela bu fonksiyon random bir þifre oluþturup, statik char dizisine kaydedip adresini döndürüyor.

			- Bir fonksiyonun daha önceki çaðrýlardan eldi ettiði deðerleri sonraki çaðrýlarda kullanmasý.
				Daha önceki deðerler ile gelecekte kullanýlacak deðerler arasýnda bir benzerlik oluyor.
				Mesela fonksiyon içerisinde kullanýlacak bir flag deðiþkeni buna örnek verilebilir.

					void func(void){
						static int flag = 1;
						if(flag){
							printf("Fonksiyon ilk kez cagrildi");
							flag = 0;
						}
						// bu fonksiyon 2. kez çaðrýldýðýnda if bloðuna girmeyecek. Eðer flag deðiþkeni statil olmasaydý
							// her çaðrýldýðýnda tekrar tanýmlanacaðý için her seferinde if bloðuna girecekti.
						// Global deðiþken niye yapmadýk? Kafalar karýþmasýn diye. Kodu okuyan, global namespacedeki
							// o statik deðiþkeni görüp deðiþiklik yapmasýn diye. Globalde olunca her yerden eriþilebiliyor
								// bu da kafa karýþýklýðý yapabilir.
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
			- Üçüncü bir kullaným yeri ise diziler. Bazý dizileri lookup table olarak kullanýyoruz. 
				void foo(int n){
					static const int primes[100] = {2, 3, 5, 7, 11, 13, 17, 19, 23}; // ilk 100 asal sayý varmýþ gibi
					 // burada amaç þu. Fonksiyona verilen n deðerinin asal sayýsýný hesaplamak yerine n'in denk geldiði asal sayýyý dizinin içerisinde bulup kullanma
						// olayýna lookup table deniyor. Maaliyeti yok bunun ondan dolayý. Fakat, bu int primes dizisinin Immutable olmasý gerek. Çünkü içerisindeki herhangi bir
							// deðer deðiþir ise bu tablo tamamen yanlýþ hale gelir. Bundan dolayý const keywordünü ekliyorum.
					// Bir diðer problem ise, bu dizi otomatik ömürlü olduðu için her çalýþtýrýldýðýnda primes dizisi bellekte tekrardan 100 elemaný ile beraber hayata getirilecek.
						// bu da büyük bir problem bakýldýðý zaman. Bunun önüne geçmek içinde static keywordünü ekliyorum.

					// namelookup tablelar genellikle static const oluyor anladýðým kadarýyla. const keywordü, tablonun deðiþmesini önlemek için, static ise tablonun elemanlarýnýn,
						// her çaðrýldýðý seferde tekrar tekrar oluþturulma maaliyetini kesmek için.

				}

------------------------------------------------------
Linkage(baðlantý) 
	Bir C programý birden fazla kaynak dosyasýndan oluþuyor. Eðer farklý kaynak dosyalarýnda kullanýlan ayný isimler, çalýþma zamanýnda
		ayný varlýða iþaret ediyor ise buna external linkage deniyor. Linkage, scope'un birden fazla kaynak dosyasýný içine almýþ olmasý gibi.
			Scope sadece bulunduðu kaynak dosyasýný ilgilendirirken, linkage projedeki tüm kaynak dosyalarýný ilgilendiriyor.

		Bu baðlantýlar üçe ayrýlýyor;
		- External	linkage ( dýþ baðlantý ):	Ayný deðiþkeni birden fazla farklý kaynak dosyasýnda kullanýyorum fakat run-time'da hepsi ayný nesneyi gösteriyor.
		- Internal	linkage ( iç baðlantý )	:	Bir isim internal linkage'a ait ise o nesne belirli bir kaynak dosyasýna ait, baþka bir kaynak dosyasýnda baþka bir nesneye ait olaBÝLÝR.
		- No		linkage ( baðlantýsýz )	:	Kendi kaynak dosyamda bile her yerde eriþemediðim nesneler ise 'no linkage' kategorisine giriyor

// engin.c
	int g = 10; // eðer bu deðiþkeni projenin diðer kaynak dosyalarýnda da kullanmak istiyorsam external linkage'a ait yapmalýyým.
					// Eðer ayný nesne birden fazla kaynak dosyasýnda tanýmlanýr ve external linkage'a ait ise, LINKER(LNK) aþamasýnda en iyi ihtimalle hata alýrýz.
				// baþka projeler tarafýndan kullanýlmasýn, nesne adýnýn birden fazla kullanýmýný engellemek, sadece ait olduðu kaynak dosyasýnda kullanýlmasý için ise internal linkage'a ait olmalý.
	// Eðer tanýmlamada keyword kullanmaz isek otomatik olarak deðiþkenler/fonksiyonlar external linkage'a ait sayýlýyor.
// kendarli.c
	int k = 20; // external linkage'a ait bu
	void foo(void){
		/- code -/
	}
// engin.c
	static int c = 10; // global namespacedeki nesneler static keywordü ile tanýmlanýrsa, tanýmlanan bu deðiþkenler internal linkage'a ait olur.
	static void bar(void){
		/- code -/
	
	}
	// burada c ve bar'ýn diðer modüllere kapatýldýðýný, baþka modüllerde kullanýlamayacaðýný söylüyor.
------------------------------------------------------
	
	- extern: Bu keyword eðer bir nesnenin tanýmýnda kullanýlýrsa, derleyiciye kullanýlan nesnenin baþka bir modülden alýndýðýný söylüyor.
		Mesela, ali.c içerisinde tanýmlanmýþ int x = 10; nesnesini kullanabilmek için engin.c dosyasýnda
			extern int x; þeklinde bildirim yapmam gerekiyor. Bu yapýlan bildirimi non-defining declaration deniyor.
				
	//engin.h
		extern int g;
	//engin.c
		int g = 10;

	//Diðer modüller engin.h'yý include etmeleri halinde, diðer modüllerde g üzerinde yapýlan tüm deðiþiklikler engin.c içerisinde bulunan
		g nesnesi üzerinde yapýlacak.

	// diziler için extern bildirimi yapýlýrken dizi boyutu kýsmý boþ býrakýlabilir.
		// kendarli.h
			extern int arr[];
		// kendarli.c
			int arr[100] = { 0 };

	Eðer bulunduðu modüle ait olmasýný istiyorsanýz nesnenin tanýmýný static keywordü ile yapacaksýn ve baþlýk dosyasýna tanýmýný koymayacaksýn

	Bütün kurallar fonksiyonlar içinde geçerli ve ayný.
		Tek fark, fonksiyonlarýn, baþlýk dosyalarýndaki, bildirimlerinde extern keywordünün bulunmasýna gerek yok. (bulunabilir ama gerek yok)
		
	External Linkage'a ait bir nesne birden fazla kez tanýmlanýrsa bu hata linker tarafýndan yakalanýr. Kodlar derlenir ama link aþamasýnda cort.
		// Varlýklarýn bir tane tanýmý olabilir. CPP'de bunun için bir kural var One Definition Rule(ODR)

		engin.c
		int x = 10; // bu deðiþken engin.c içerisinde hiç kullanýlmamasý durumunda lojik hata oluþturmaz. Çünkü, external linkage'a baðlý
						// olduðu için diðer modüllerden eriþim olabilir.
		static int c = 20; // eðer bunu engin.c içerisinde hiç kullanmaz isem bu lojik hata.
------------------------------------------------------
Global namespace pollution problem(Global isim alanýnýn kirlilik/kalabalýk problemi): Dýþarý açýlmýþ(ext linkage) nesnelerin tek olmasý gerekiyor.
	Çakýþma olasýlýðý yüksek olan isimleri kullanýrsak, kodu yazan kiþi o nesnenin ismini baþka bir modülde kullanamaz. Ýsim çakýþmasý doðrudan link aþamasýnda problem olur.

	Bunun önüne geçmek için nesnelerin isimleri özelleþtiriliyor. Mesela, encryption alanýnda  bir kütüphane desteði veriyoruz.
	kütüphaneadý_isleminadi_fonksiyonadý(void) -> tabii bu baþka þekillerde de yapýlabilir bu sadece bir örnek.
	CPP'de böyle bir problem yok. CPP'de namespace denen bir özellik var. Nesneler direkt olarak global isimalanýna boþaltýlmak yerine 
		namespaceler içerisinde enjekte ediliyor. Bu sayede çakýþma problemleri olmuyor çünkü her isim kendi namespace'inde.

------------------------------------------------------
	Type modifier(Type qualifiers): Deðiþkenin türleri üzerinde etkiyi sahipler
	const - volatile - restrict - typedef

	- Type modifiers implicit int kuralýný uygularlar. Eðer bir nesnenin türü belirtilmediyse int kabul edilir.

	Const: Nesnenin deðerinin deðiþtirilemeyeceðini vurguluyor. Immutable yapýyor yani nesneyi.
		Const bir nesnenin deðeri deðiþtirilemez sentaks hatasý verir. const olmasý gereken ama const olmayan bir nesnede deðiþiklik yaparsak
			bu sentaks hatasý deðil ama lojik bir hata.


*/

/*
	NOT: extern kýsmýnda bulunan extern int x; bir definition deðil declaration. Eðer bir deðiþken define ediliyor ise 
		bu, derleyicinin o nesne için bellekte bir yer ayýracaðý anlamýna geliyor. extern int x ile yeni bir deðiþken tanýmý deðil
			hali hazýrda baþka bir modülde bulunan bir nesnenin bildirimi yapýlýyor. Tanýmlama olmayan bildirimlere non-defining declaration denir.


*/