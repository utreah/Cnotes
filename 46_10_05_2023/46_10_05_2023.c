#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdio.h>
// strtok bildirimi
/*
char* strtok(char* str, const char* delimiter);
int main(void) {
	char str[] = "Ahmet, Mehmet, gelmis...niye gelmis.? dehlenmis mi, niye. dehlenmi� ";
	
	char* p = strtok(str, "?., "); // strtok a��l��� string tokenizing olan bir standart fonksiyon. Delimiter parametresine gelen
										// arg�manlar� ay�ra� olarak kullan�r. Bu; bir rakam, harf veya noktalama i�areti olabilir.
									// strtok'ta fonksiyonu ka��nc� kez �a��rd���m�za dair statik �m�rl� yerel bir de�i�ken bulunuyor.
	while (p) {
		printf("[%s]", p);
		p = strtok(NULL, "?., "); // fonksiyon ikinci kez �a��r�lmas�na ra�men buraya parametre olarak str'nin adresi de�il nullptr yolland�.
									// strtok fonksiyonu, �zerinde �al��t��� yaz� dizisinde de�i�iklik yaparak �al���r.
								// delimiter parametresine gelen arg�man(lar) ile kar��la�t���nda oraya >'\0'< null karakterini koyar.
									// bunu hoca a��klamad� ama NULL'�n kullan�lma sebebi strtok i�erisinde str parametresinde nerede
										// oldu�unun adresini tutan bir de�i�iklik olabilir. NULL yollarak fonksiyona ayn� yaz� dizisi
											// �zerinde �al��t���m�z� haber veriyor olabiliriz. -> yorumum/tahminim bu y�nde
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
														DINAMIK BELLEK YONETIMI
														DYNAMIC MEMORY MANAGEMENT


	Program�n �al��makta olan haline 'process' denir. Diskteki haline 'program' denir.
		��letim sistemi alt�nda ko�uyor ise i�letim sistemi processlerin kontrol�n� sa�l�yor -> hosted environment
		��letim sistemi olmadan �al���yor ise -> free-standing/standalone denir.

	Dinamik bellek y�netime ba�lamadan �nce, exit - atexit - abort g�rece�iz.
		Hepsi program� sonland�ran fonksiyonlar.

	normal termination: Process sonland�r�lmadan �nce baz� i�lemlerin yap�lma garantisinde oldu�u duruma.
		mesela dosyalar�n�n buffer�n�n flush edilmesi. Ge�ici dosyalar�n silinmesi. atexit ile �a��r�lan fonksiyonlar�n ters s�ra ile
			�a�r�lmas� gibi. Normal termination i�in exit() fonksiyonu �a��r�lacak.
	abnormal termination: Process sonland�r�lmadan �nce baz� i�lerin yap�lma garantisi yok.
		Abnormal termination i�in abort() fonksiyonu �a��r�lacak.



		atexit, exit ile kullan�lan yard�mc� bir fonksiyon.

		void exit(int); -> program�n hangi sebeple sonland�r�ld���n� ifade ediyor.
		int yerine 0 verilirse program ba�ar�l�.��ini yapt�
		nonzero bir de�er ise ba�ar�s�z.yapamad� demektir.
		main fonksiyonundaki return deyimi de bu �ekilde yorumlan�yordu zaten.

		MA�N ���NDE RETURN STATEMENT DERLEY�C� TARAFINDAN EX�T �A�RISINA D�N��T�R�L�YOR.

		exit(0) -> program i�ini yapm�� ba�ar�l� �ekilde sonlanm��.kullanacak ki�iye bunun bilgisini veriyor
		exit(1) -> program ba�ar�s�z.kullanacak olan ki�iye bu bilgiyi verir

		0 ve 1 yerine macro kullan�l�yor.
		stdlib.h de var bunlar

		#define		EXIT_SUCCESS		0
		#define		EXIT_FAILURE		1

		exit(0) -> exit(EXIT_SUCCESS)  ayn� anlamda
		exit(1) -> exit(EXIT_FAILURE)  ayn� anlamda


		void f3(void)
		{
			printf("f3 cagrildi\n");
			exit(EXIT_FAILURE); // bu �ekilde yap�l�nca buradan sonra process/program sonland�r�l�r.
					// bunu yapman�n 1-2 sebebi var.
					// 1. i�ini bitirmi�tir ve bu y�zden sonland�r�l�r.EXIT_SUCCESS ile yap�l�r.
					// 2. ba�ar�s�zl�k durumunda �a�r�l�r.
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
		exitin aborttan fark�, abort hemen sonland�r�yor.
		exit ise program� sonland�rmadan �nce baz� i�lemlerin yap�lmas�n� garanti alt�na al�yor.
		mesela, yazma ama�l� kullan�lan dosyalar�n bufferlar�n�n flush edilmesi.
		dosya i�lemlerinde dosyaya yazma i�lemi yapan fonksiyon asl�nda dosyaya yazm�yor, bu dosya i�in memoryde ayr�lm��
		bir buffera yaz�yor. Belirli eventler olu�unca, bellek blo�undaki byte lar�n hepsi dosyaya yaz�l�yor.
		buna da buffer�n flush edilmesi deniyor.


		int atexit(void (*fp)(void)); geri d�n�� de�eri olmayan parametresi olmayan fonksiyon adresi al�yor.
		atexit bunu global bir fonksiyon pointer� dizisine yaz�yor.
		geri d�n�� de�eri ba�ar� bilgisi.

		exit �a�r�ld���nda, atexit ile kaydedilmi� fonksiyonlar ters s�rada �a�r�lacak.
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

			exit(EXIT_FAILURE);  //ters s�rada �a��r�yor,handler 3, 2, 1 �eklinde �a�r�l�yor.
			printf("main sona erdi\n");
		}


			a�a��daki gibi de biz yapabiliriz.

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

			mylib.h i�eri�i
			------------
			typedef void (*FPTR)(void);

			void func(void);

			void fregister(FPTR F);


			mylib.c i�eri�i
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

				for (int i = idx-1; 0 <= i; i--) // tersten �a��r�yor atexit gibi.
					gfa[i]();
			}

			BUnlar�n yap�lmas�n�n sebebi veri kayb�n� engellemek.

			db ba�lant�s� kapat�lmas�, file lar�n flush edilmesi, hataya ili�kin loglar�n yaz�lmas�.
			bunlar� unutabiliriz ya da ihmal edebilriiz.bunlar i�in kullan�l�yor.

			bunlara cleanup i�lemleri deniyor.

			exit �a�r�lmasada atexit ile kaydedilen fonksiyonlar �a�r�ld�.
			derleyici c99 dan sonra main i�ine return 0 koyuyor. bu da exit(0) gibi de�erlendiriliyor.
			veya return 1 de exit(1) �a��r�r.
			main i�inde return oldu�unda exite yap�lan �a�r� s�z konusudur.

			mesela powershell ile bir exe �al��t�rd�m ve outputunu kullanaca��m, burada i�e yar�yor.
///////////////////////////////////////////////////////////////////////////

			ABORT

			void abort(void)
			abnormal termination.

			abort e�er program� sonland�r�rsa kendisi uyar� mesaj� veriyor.
			Abort oldu�u belli oluyor.

			exit(EXIT_FAILURE) ; �rne�ini abort i�inde yapabiliriz.

			void asd(const int *p)
			{
				if(p == NULL) // bu �ekilde yaz�lan kodlara assertion denir. runtime de olunca bu kontrol dynamic assertion denir
				{				// ��nk� NULL ptr dereference etmek UB olu�turur.bu hatay� al�r almaz abort ile pat diye sonland�rmas� i�in.
					printf("hata\n"); // ileride g�r�lecek assert macrosu kullan�lacak. zaten geri planda o da abort u �a��r�yor.
					abort();			// assert(p != NULL) ile kullan�l�r    1:01
				}

				while(*p)
				{
					++p;
				}

			}
///////////////////////////////////////////////////////////////////////////

																D�NAM�C BELLEK Y�NET�M�
																DYNAM�C MEMORY MANAGEMENT
	STATIC -> BU �EV�R� S�REC�NE A�T DEMEKT�R.
	DYNAMIC -> BU KAVRAM �SE PROGRAMIN �ALI�MA ZAMANINA A�T DEMEK.

	STATIC ASSERT�ON -> DO�RULAMANIN COMP�LE T�ME DA
	DYNAMIC ASSERT�ON -> DO�RULAMANIN RUNT�ME DA YAPILDI�INI G�STER�R.

	Derleyici koda bakarak bir de�i�kenin statik, dinamik veya otomatik �m�rl� olup olmad���n� anl�yor.
	Statik bellek y�netimi, de�i�kenlerinin storagelar�n� derleyicinin �evirici s�recinde ayarl�yor.
	Dinamik bellek y�netimi, program�n �al��ma zaman�nda belirli bir belle�in kullan�ma sunulmas� ve o bellek alan�na duyulan ihtiyac�n
		ortadan kalkmas�yla ba�ka ama�larla kullan�lmak i�in geri verilmesi anlam�na geliyor. -> runtime'da oluyor bunlar
	Dinamik bellek y�netimi sadece ve sadece mecburiyet durumlar�nda kullan�lmal�. E�er ihtiya� yokken kullan�l�rsa
		inan�lmaz bir maliyet ekliyoruz kodumuza. Belirli temalar d���nda kullan�lmamal�.

	dinamik �m�r, hayata istenildi�i zaman getirilip, istenildi�i zaman silinebilen nesnelerdir.
		bunlar�nda yerlerinin runtime da elde edilmesi gerekiyor.Dinamik bellek y�netimi de bu bellek
			blo�unun elde edilmesi ve y�netilmesi i�lemlerini yap�yor

	C# JAVA G�B� D�LLERDE T�M NESNELER D�NAM�K �M�RL�.HEPS� D�NAM�K BELLEK Y�NET�M� �LE ELDE ED�L�YOR.
	Program, dinamik �m�rl� nesnelerin kaynaklar�n� eski haline getirmeden sonlan�yor ise kal�c� zarar/problem olu�turabilir.
	�al��ma zaman�nda bellek ay�rma i�lemine 'memory allocation' denir. Ayr�lan belle�in geri verilmemesine ve 
			bundan dolay� dinamik �m�rl� �r�nlere ayr�lacak yerin kalmamas�na 'memory leak' denir.
	
	
	HEAP
	Process'in kulland��� bellek alan�ndan bahsederken C' dilinde 'HEAP' denir.
	Dinamic memory management ile ayr�lan alanlar memory alanlar� bu segmentte yer al�r.
		C++ ta buraya free store da denilebiliyor.
	///////////////////////////////////////////////////////////
	C dilinin dinamik bellek y�netimi fonksiyonlar�(4 adet)
		<stdlib.h> ba�l�k dosyas�nda
	malloc() -> memory allocation
	calloc() -> clear allocation (hocaya g�re, c'nin ne anlama geldi�i d�k�mante edilmemi�)
		calloc ile malloc ayn� i�i yap�yor. �kisi de bir bellek edinimi sa�l�yor. Fakat, malloc ay�rd��� bellek blo�unu
			garbage value ile teslim ederken, calloc bu bellek blo�unu '0' ile dolduruyor. statik vs dinamik �m�rl� de�i�ken gibi d���nebiliriz.
	realloc() -> realloc yeniden allocate et anlam�na geliyor. Daha �nce allocate etti�imiz bir bellek blo�unun artt�r�lmas�/azalt�lmas� i�in
					kullan�l�yor. 1000 bytel�k bir bellek blo�u yetersiz/fazla gelmeye ba�lad���nda byte ta de�i�iklik yapmak i�in kullan�l�r.
						
	free() -> deallocation, kullan�lan bellek blo�unun kullan�mdan �ekilmesi i�in. 

	Bir bellek alan�na ihtiyac�m�z var fakat ihtiyac�m�z olan bellek alan� run-time'da belirleniyor. Dinamik bellek y�netimini de 
		bunun gibi senaryolarda kullan�yoruz. Tek senaryo bu de�il.
	void* malloc(size_t n); // parametre de�eri olarak a��lmas�n� istedi�imiz miktar� yaz�yoruz(byte olarak a��yor)
	malloc ba�ar� garantisi olan bir fonksiyon de�il.	
		Ba�ar�l� olup olmad��� kontrol edilmeli. E�er ba�ar�l� olduysa allocate etti�i bellek blo�unun adresini d�nd�r�yor
			ba�ar�s�z oldu ise nullptr d�nd�r�yor.
		malloc ba�ar�l� olduysa geri d�nd�r�len dizi contigous yani ard���k olmak zorunda. Ayn� arrays de oldu�u gibi.
*/
// malloc �rne�i
#include <stdlib.h>
#include <stdio.h>

int main_malloc_example(void) {
	int n;

	printf("Kac tamsayi istiyorsunuz?: ");
	(void)scanf("%d", &n);
	int* ip = (int*)malloc(n * sizeof(int));
	int* iptr;
	// if (iptr = (int*)malloc(n * sizeof(int)) == NULL) -> bu �ekilde de yaz�labiliyormu�. �zellikle sistem programlamada
	if (!ip){
		printf("malloc returned nullptr\nexiting.");
		exit(EXIT_FAILURE);
	} 
}
// ikinci yap�lan malloc �a�r�s�n�n, ilk yap�lan malloc �a�r�s�n�n boyutunu b�y�tme garantisi yok. B�yle bir ihtiyac�m�z var ise
	// realloc �a��rarak yapmal�y�z.

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
// yukar�daki �rnekte malloc'u kullanma sebebimiz, get_median fonksiyonundaki ilk parametre const int* t�r�nden.
	// medyan ise k���kten - b�y��e(ya da di�er t�rl�) s�ralanm�� bir dizinin ortas�ndaki elemana denir.
	// as�l dizideki elemanlar� kopyalamak i�in bir bellek blo�u allocate ediyoruz. memcpy ile const diziden, �zerinde  de�i�iklik
		// yapabilece�imiz diziye aktar�yoruz. Ortanca de�eri bulduktan sonra ise 'memory leak' problemi ile kar��la�mamak i�in
			// free(idf) ile allocate etti�imiz bellek blo�unu serbest b�rak�yoruz.