#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdio.h>
// strtok bildirimi
/*
char* strtok(char* str, const char* delimiter);
int main(void) {
	char str[] = "Ahmet, Mehmet, gelmis...niye gelmis.? dehlenmis mi, niye. dehlenmiþ ";
	
	char* p = strtok(str, "?., "); // strtok açýlýþý string tokenizing olan bir standart fonksiyon. Delimiter parametresine gelen
										// argümanlarý ayýraç olarak kullanýr. Bu; bir rakam, harf veya noktalama iþareti olabilir.
									// strtok'ta fonksiyonu kaçýncý kez çaðýrdýðýmýza dair statik ömürlü yerel bir deðiþken bulunuyor.
	while (p) {
		printf("[%s]", p);
		p = strtok(NULL, "?., "); // fonksiyon ikinci kez çaðýrýlmasýna raðmen buraya parametre olarak str'nin adresi deðil nullptr yollandý.
									// strtok fonksiyonu, üzerinde çalýþtýðý yazý dizisinde deðiþiklik yaparak çalýþýr.
								// delimiter parametresine gelen argüman(lar) ile karþýlaþtýðýnda oraya >'\0'< null karakterini koyar.
									// bunu hoca açýklamadý ama NULL'ýn kullanýlma sebebi strtok içerisinde str parametresinde nerede
										// olduðunun adresini tutan bir deðiþiklik olabilir. NULL yollarak fonksiyona ayný yazý dizisi
											// üzerinde çalýþtýðýmýzý haber veriyor olabiliriz. -> yorumum/tahminim bu yönde
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														DINAMIK BELLEK YONETIMI
														DYNAMIC MEMORY MANAGEMENT


	Programýn çalýþmakta olan haline 'process' denir. Diskteki haline 'program' denir.
		Ýþletim sistemi altýnda koþuyor ise iþletim sistemi processlerin kontrolünü saðlýyor -> hosted environment
		Ýþletim sistemi olmadan çalýþýyor ise -> free-standing/standalone denir.

	Dinamik bellek yönetime baþlamadan önce, exit - atexit - abort göreceðiz.
		Hepsi programý sonlandýran fonksiyonlar.

	normal termination: Process sonlandýrýlmadan önce bazý iþlemlerin yapýlma garantisinde olduðu duruma.
		mesela dosyalarýnýn bufferýnýn flush edilmesi. Geçici dosyalarýn silinmesi. atexit ile çaðýrýlan fonksiyonlarýn ters sýra ile
			çaðrýlmasý gibi. Normal termination için exit() fonksiyonu çaðýrýlacak.
	abnormal termination: Process sonlandýrýlmadan önce bazý iþlerin yapýlma garantisi yok.
		Abnormal termination için abort() fonksiyonu çaðýrýlacak.



		atexit, exit ile kullanýlan yardýmcý bir fonksiyon.

		void exit(int); -> programýn hangi sebeple sonlandýrýldýðýný ifade ediyor.
		int yerine 0 verilirse program baþarýlý.Ýþini yaptý
		nonzero bir deðer ise baþarýsýz.yapamadý demektir.
		main fonksiyonundaki return deyimi de bu þekilde yorumlanýyordu zaten.

		MAÝN ÝÇÝNDE RETURN STATEMENT DERLEYÝCÝ TARAFINDAN EXÝT ÇAÐRISINA DÖNÜÞTÜRÜLÜYOR.

		exit(0) -> program iþini yapmýþ baþarýlý þekilde sonlanmýþ.kullanacak kiþiye bunun bilgisini veriyor
		exit(1) -> program baþarýsýz.kullanacak olan kiþiye bu bilgiyi verir

		0 ve 1 yerine macro kullanýlýyor.
		stdlib.h de var bunlar

		#define		EXIT_SUCCESS		0
		#define		EXIT_FAILURE		1

		exit(0) -> exit(EXIT_SUCCESS)  ayný anlamda
		exit(1) -> exit(EXIT_FAILURE)  ayný anlamda


		void f3(void)
		{
			printf("f3 cagrildi\n");
			exit(EXIT_FAILURE); // bu þekilde yapýlýnca buradan sonra process/program sonlandýrýlýr.
					// bunu yapmanýn 1-2 sebebi var.
					// 1. iþini bitirmiþtir ve bu yüzden sonlandýrýlýr.EXIT_SUCCESS ile yapýlýr.
					// 2. baþarýsýzlýk durumunda çaðrýlýr.
			printf("f3 Sona erdi\n");
		}

		void f2(void)
		{
			printf("f2 cagrildi\n");
			f3();
			printf("f2 Sona erdi\n");
		}

		void f1(void)
		{
			printf("f1 cagrildi\n");
			f2();
			printf("f1 Sona erdi\n");
		}


		int main()
		{
			printf("main cagrildi\n");
			f1();
			printf("main sona erdi\n");
		}
		exitin aborttan farký, abort hemen sonlandýrýyor.
		exit ise programý sonlandýrmadan önce bazý iþlemlerin yapýlmasýný garanti altýna alýyor.
		mesela, yazma amaçlý kullanýlan dosyalarýn bufferlarýnýn flush edilmesi.
		dosya iþlemlerinde dosyaya yazma iþlemi yapan fonksiyon aslýnda dosyaya yazmýyor, bu dosya için memoryde ayrýlmýþ
		bir buffera yazýyor. Belirli eventler oluþunca, bellek bloðundaki byte larýn hepsi dosyaya yazýlýyor.
		buna da bufferýn flush edilmesi deniyor.


		int atexit(void (*fp)(void)); geri dönüþ deðeri olmayan parametresi olmayan fonksiyon adresi alýyor.
		atexit bunu global bir fonksiyon pointerý dizisine yazýyor.
		geri dönüþ deðeri baþarý bilgisi.

		exit çaðrýldýðýnda, atexit ile kaydedilmiþ fonksiyonlar ters sýrada çaðrýlacak.
		void handler1(void)
		{
			printf("handler1 cagrildi\n");
		}

		void handler2(void)
		{
			printf("handler2 cagrildi\n");
		}

		void handler3(void)
		{
			printf("handler3 cagrildi\n");
		}


		int main()
		{
			printf("main basladi\n");
			atexit(handler1);
			atexit(handler2);
			atexit(handler3);

			exit(EXIT_FAILURE);  //ters sýrada çaðýrýyor,handler 3, 2, 1 þeklinde çaðrýlýyor.
			printf("main sona erdi\n");
		}


			aþaðýdaki gibi de biz yapabiliriz.

			void handler1(void)
			{
				printf("handler1 cagrildi\n");
			}

			void handler2(void)
			{
				printf("handler2 cagrildi\n");
			}

			void handler3(void)
			{
				printf("handler3 cagrildi\n");
			}


			int main()
			{
				printf("main basladi\n");
				fregister(handler1);
				fregister(handler2);
				fregister(handler3);


				func();
				printf("main sona erdi\n");
			}

			mylib.h içeriði
			------------
			typedef void (*FPTR)(void);

			void func(void);

			void fregister(FPTR F);


			mylib.c içeriði
			---------------
			#include <stdio.h>
			#include "mylib.h"

			#define		MAX_REGISTER_NO		10

			FPTR gfa[MAX_REGISTER_NO];
			int idx = 0;

			void fregister(FPTR f)
			{
				gfa[idx++] = f;
			}

			void func(void)
			{
				printf("func cagrildi ve kayit edilmis functionlari cagiracak\n");

				for (int i = idx-1; 0 <= i; i--) // tersten çaðýrýyor atexit gibi.
					gfa[i]();
			}

			BUnlarýn yapýlmasýnýn sebebi veri kaybýný engellemek.

			db baðlantýsý kapatýlmasý, file larýn flush edilmesi, hataya iliþkin loglarýn yazýlmasý.
			bunlarý unutabiliriz ya da ihmal edebilriiz.bunlar için kullanýlýyor.

			bunlara cleanup iþlemleri deniyor.

			exit çaðrýlmasada atexit ile kaydedilen fonksiyonlar çaðrýldý.
			derleyici c99 dan sonra main içine return 0 koyuyor. bu da exit(0) gibi deðerlendiriliyor.
			veya return 1 de exit(1) çaðýrýr.
			main içinde return olduðunda exite yapýlan çaðrý söz konusudur.

			mesela powershell ile bir exe çalýþtýrdým ve outputunu kullanacaðým, burada iþe yarýyor.
///////////////////////////////////////////////////////////////////////////

			ABORT

			void abort(void)
			abnormal termination.

			abort eðer programý sonlandýrýrsa kendisi uyarý mesajý veriyor.
			Abort olduðu belli oluyor.

			exit(EXIT_FAILURE) ; örneðini abort içinde yapabiliriz.

			void asd(const int *p)
			{
				if(p == NULL) // bu þekilde yazýlan kodlara assertion denir. runtime de olunca bu kontrol dynamic assertion denir
				{				// çünkü NULL ptr dereference etmek UB oluþturur.bu hatayý alýr almaz abort ile pat diye sonlandýrmasý için.
					printf("hata\n"); // ileride görülecek assert macrosu kullanýlacak. zaten geri planda o da abort u çaðýrýyor.
					abort();			// assert(p != NULL) ile kullanýlýr    1:01
				}

				while(*p)
				{
					++p;
				}

			}
///////////////////////////////////////////////////////////////////////////

																DÝNAMÝC BELLEK YÖNETÝMÝ
																DYNAMÝC MEMORY MANAGEMENT
	STATIC -> BU ÇEVÝRÝ SÜRECÝNE AÝT DEMEKTÝR.
	DYNAMIC -> BU KAVRAM ÝSE PROGRAMIN ÇALIÞMA ZAMANINA AÝT DEMEK.

	STATIC ASSERTÝON -> DOÐRULAMANIN COMPÝLE TÝME DA
	DYNAMIC ASSERTÝON -> DOÐRULAMANIN RUNTÝME DA YAPILDIÐINI GÖSTERÝR.

	Derleyici koda bakarak bir deðiþkenin statik, dinamik veya otomatik ömürlü olup olmadýðýný anlýyor.
	Statik bellek yönetimi, deðiþkenlerinin storagelarýný derleyicinin çevirici sürecinde ayarlýyor.
	Dinamik bellek yönetimi, programýn çalýþma zamanýnda belirli bir belleðin kullanýma sunulmasý ve o bellek alanýna duyulan ihtiyacýn
		ortadan kalkmasýyla baþka amaçlarla kullanýlmak için geri verilmesi anlamýna geliyor. -> runtime'da oluyor bunlar
	Dinamik bellek yönetimi sadece ve sadece mecburiyet durumlarýnda kullanýlmalý. Eðer ihtiyaç yokken kullanýlýrsa
		inanýlmaz bir maliyet ekliyoruz kodumuza. Belirli temalar dýþýnda kullanýlmamalý.

	dinamik ömür, hayata istenildiði zaman getirilip, istenildiði zaman silinebilen nesnelerdir.
		bunlarýnda yerlerinin runtime da elde edilmesi gerekiyor.Dinamik bellek yönetimi de bu bellek
			bloðunun elde edilmesi ve yönetilmesi iþlemlerini yapýyor

	C# JAVA GÝBÝ DÝLLERDE TÜM NESNELER DÝNAMÝK ÖMÜRLÜ.HEPSÝ DÝNAMÝK BELLEK YÖNETÝMÝ ÝLE ELDE EDÝLÝYOR.
	Program, dinamik ömürlü nesnelerin kaynaklarýný eski haline getirmeden sonlanýyor ise kalýcý zarar/problem oluþturabilir.
	Çalýþma zamanýnda bellek ayýrma iþlemine 'memory allocation' denir. Ayrýlan belleðin geri verilmemesine ve 
			bundan dolayý dinamik ömürlü ürünlere ayrýlacak yerin kalmamasýna 'memory leak' denir.
	
	
	HEAP
	Process'in kullandýðý bellek alanýndan bahsederken C' dilinde 'HEAP' denir.
	Dinamic memory management ile ayrýlan alanlar memory alanlarý bu segmentte yer alýr.
		C++ ta buraya free store da denilebiliyor.
	///////////////////////////////////////////////////////////
	C dilinin dinamik bellek yönetimi fonksiyonlarý(4 adet)
		<stdlib.h> baþlýk dosyasýnda
	malloc() -> memory allocation
	calloc() -> clear allocation (hocaya göre, c'nin ne anlama geldiði dökümante edilmemiþ)
		calloc ile malloc ayný iþi yapýyor. Ýkisi de bir bellek edinimi saðlýyor. Fakat, malloc ayýrdýðý bellek bloðunu
			garbage value ile teslim ederken, calloc bu bellek bloðunu '0' ile dolduruyor. statik vs dinamik ömürlü deðiþken gibi düþünebiliriz.
	realloc() -> realloc yeniden allocate et anlamýna geliyor. Daha önce allocate ettiðimiz bir bellek bloðunun arttýrýlmasý/azaltýlmasý için
					kullanýlýyor. 1000 bytelýk bir bellek bloðu yetersiz/fazla gelmeye baþladýðýnda byte ta deðiþiklik yapmak için kullanýlýr.
						
	free() -> deallocation, kullanýlan bellek bloðunun kullanýmdan çekilmesi için. 

	Bir bellek alanýna ihtiyacýmýz var fakat ihtiyacýmýz olan bellek alaný run-time'da belirleniyor. Dinamik bellek yönetimini de 
		bunun gibi senaryolarda kullanýyoruz. Tek senaryo bu deðil.
	void* malloc(size_t n); // parametre deðeri olarak açýlmasýný istediðimiz miktarý yazýyoruz(byte olarak açýyor)
	malloc baþarý garantisi olan bir fonksiyon deðil.	
		Baþarýlý olup olmadýðý kontrol edilmeli. Eðer baþarýlý olduysa allocate ettiði bellek bloðunun adresini döndürüyor
			baþarýsýz oldu ise nullptr döndürüyor.
		malloc baþarýlý olduysa geri döndürülen dizi contigous yani ardýþýk olmak zorunda. Ayný arrays de olduðu gibi.
*/
// malloc örneði
#include <stdlib.h>
#include <stdio.h>

int main_malloc_example(void) {
	int n;

	printf("Kac tamsayi istiyorsunuz?: ");
	(void)scanf("%d", &n);
	int* ip = (int*)malloc(n * sizeof(int));
	int* iptr;
	// if (iptr = (int*)malloc(n * sizeof(int)) == NULL) -> bu þekilde de yazýlabiliyormuþ. Özellikle sistem programlamada
	if (!ip){
		printf("malloc returned nullptr\nexiting.");
		exit(EXIT_FAILURE);
	} 
}
// ikinci yapýlan malloc çaðrýsýnýn, ilk yapýlan malloc çaðrýsýnýn boyutunu büyütme garantisi yok. Böyle bir ihtiyacýmýz var ise
	// realloc çaðýrarak yapmalýyýz.

int get_median(const int* p, size_t size) {
	int* pd = (int*)malloc(size * sizeof(int));
	if (!pd) {
		exit(EXIT_FAILURE);
	}
	memcpy(pd, p, size * sizeof(int));
	sort_array(pd, size);
	int ret_val = pd[size / 2];
	free(pd);
	return ret_val;
}
// yukarýdaki örnekte malloc'u kullanma sebebimiz, get_median fonksiyonundaki ilk parametre const int* türünden.
	// medyan ise küçükten - büyüðe(ya da diðer türlü) sýralanmýþ bir dizinin ortasýndaki elemana denir.
	// asýl dizideki elemanlarý kopyalamak için bir bellek bloðu allocate ediyoruz. memcpy ile const diziden, üzerinde  deðiþiklik
		// yapabileceðimiz diziye aktarýyoruz. Ortanca deðeri bulduktan sonra ise 'memory leak' problemi ile karþýlaþmamak için
			// free(idf) ile allocate ettiðimiz bellek bloðunu serbest býrakýyoruz.