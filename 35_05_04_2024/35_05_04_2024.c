/*
												NULL POINTER NEDÝR?

	-NULL bir makro, keyword veya identifier deðildir.
	-NULL bir adres sabiti olarak kabul ediliyor yani adres deðiþkenlerine atanabilir, adres deðiþkeni olmayan deðiþkenlere ilk deðer vermek için
		kullanmak doðru deðil.
			int x = NULL; ifadesi doðru deðildir böyle kullanýlmamalýdýr.
	-Telaffuz edilirken null pointer olarak edilmeli, sadece null demek doðru deðil anlam farklý. sadece null denir ise, null character null string gibi 
		kavramlar ile karýþýklýk yaþanýr. O yüzden null ptr demek mantýklý.
	-NULL pointer geçerli bir adres fakat hiçbir nesnenin adresi deðil.
	-NULL pointerin bir adres deðiþkeninde kullanýlmasý onu valid pointer yapar.
	-DÝKKAT! NULL pointerý dereference etmek Undefined Behaviour.
		int main(void){
			int* p = NULL;
			int z = *p; // UNDEFINED BEHAVIOUR, Derleyici derleme zamanýnda bunun kontrolünü yapmak zorunda deðil.
			int y = p[0]; // UNDEFINED BEHAVIOUR

		}
	-iki pointer deðiþkenin ikisinin de deðeri NULL ptr ise bu pointer deðiþkenler deðerce eþittir. 
		"==" operatörü ile iþleme sokulursa True(1) deðeri döndürülür.

	-C ve CPP dillerinde lojik bir ifade beklenen yerlerde bir adres(pointer) ifadesi kullanýlabilir.
		-Eðer pointer deðiþkenini NULL makrosunu gösteriyor ise logical FALSE(0)
		-Eðer pointer deðiþkeni NULL makrosunu gösterMÝYOR ise logical TRUE(1)
			int* foo();
			int main(void)
			{
				int x = 36;
				int* ptr = &x;
				int* ptr2 = NULL;
				if(ptr2 == NULL) == if(!ptr2) // Line 20
				if(ptr != NULL) == if(ptr) //Line 21
				if(foo() == NULL) == if(!foo()) // Line 20
				if(foo() != NULL) == if(foo()) // Adres döndüren fonksiyonlarda da durum ayný. Line 21
			}
	-NULL makrosunu kullanabilmek için NULL makrosunun tanýmlandýðý bir dosyayý include etmemiz gerek.
		Eðer include edilmez ise derleyici NULL'ý bir identifier olarak kabul edecek ve hata alacaðýz.
	
	-Ýlk deðer verilmeyen otomatik ömürlü pointer deðiþkenler hayata çöp deðer(garbage value/indeterminent value) olarak baþlar.
		Ama ilk deðer verilmeyen statik ömürlü adres deðiþkenleri hayata NULL pointer ile baþlar. Bu garanti altýnda.
			int sp*;
			int main(void){
				static int* msp;
				if(sp == NULL) // if'in doðru kýsmýna girer.
				if(msp == NULL) // if'in doðru kýsmýna girer.
			int x = 356;
			int* p = 5; // Adres deðiþkeni deðil.

			p = x; // burada implicit type conversion olur çünkü p adres deðiþkeni, x ise normal tam sayý deðiþkeni. x int* a cast edilir.
				//Böyle bir kod yazýlmamalý.
			int* p = 0;
			p = 0;

			}
	-Normal olarak bir pointer deðiþkeni bir tam sayý deðeri atanmamalýdýr(ilk deðer verme dahil). Böyle bir atama C dilinde yanlýþtýr, CPP'de sentaks hatasý.
		Ancak, bu durumun bir istisnasý vardýr. Bir pointer deðiþkenine tam sayý sabiti olarak 0 deðeri atanabilir. Derleyici 0 sabitini
			null pointer'a dönüþür. Bu dönüþüme NULL POINTER CONVERSION denir.

			int main(void){
				int* p = 0;
				p = 0;
					// Ýkisinde de sorun yok 0, null pointer'a dönüþtürülecek. Bu olaya NULL POINTER CONVERSION denir.
				if(p == 0) == if(p == NULL)
				// Hoca p == 0 þeklinde yazmak yerine p == NULL makrosunu kullanmak kodun niyetini daha iyi açýkladýðýný söylüyor.

				int x = 0;
				int* ptr = x; // Bu kod C'de yanlýþ CPP'de sentaks hatasý.
			}
	/////////////////////////////////////////////////////////////////////////////
						NULL POINTER NE ÝÞE YARAR?


	-Bir iþ yapmaya yönelik, iþlem sonunda adres döndüren fonksiyonlarda kullanýlýr.
		a) fonksiyon iþini yapar ve baþarýlý olur. Ýþini yaparsa çaðýran kodun kullanacaðý bir adres döndürür.
		b) fonksiyon iþini yapamaz ve baþarýsýz olur. Ýþini yapamaz ise NULL pointer döndürür.
		Mesela fopen() fonksiyonu baþarýlý bize bir yapý nesnesinin adresini döndürüyor, baþarýsýz olurs NULL pointer döndürüyor.
			FILE* f = fopen("ugur.txt", "r");
			if (f == NULL)
				printf("TXT olusturulamadý");
			else
				printf("TXT olusturuldu");
				
		malloc() baþarýlý olursa dinamik olarak ayarlanan o bloðun adresini döndürüyor, baþarýsýz olursa NULL pointer döndürüyor.
	-Veri yapýlarýnda arama iþlemi yapýyor.(adres döndürür)
		a) Eðer veri bulunursa(baþarýlý) o verinin adresini döndürür.
		b) Eðer veri bulunamaz(baþarýsýz) ise NULL pointer döndürülür.

		





*/
#include <stdio.h>
int* search_in_array(const int* p, int size, int key)
{
	while (size-- && p++) // burada size-- 0 olduðunda short circuit olacak ve döngüden çýkýlacak.
		if (*p == key)
			return (int*)p;
	return NULL;
}
int main(void) {

	int a[4] = { 1,12321,412421,3152 };
	int ival;
	scanf("%d", &ival);
	int* p = search_in_array(a, 4, ival);
	if (p != NULL) // if(p) olarakta yazýlabilir
		printf("Aranan %d sayisi, %d. indiste bulundu.", *p, p - a);
	else
		printf("Deger bulunamadi.");
}
// Fiziksel Const: const int x = 10; // x burada fiziksel const olarak bulunuyor.

void func(const int* ptr) {
	// *ptr; Compile time açýsýndan bakýldýðýnda gelen nesnenin const olup olmamasý dikkate alýnmaksýzýn *ptr const bir ifadedir.
			// eðer yollanan nesne const ise fiziksel const, deðil ise sözleþmeye baðlý const.
	int* p = (int*)ptr;
	*p = 987; // Burada bir sýkýntý yaþanmaz çünkü fonksiyona gönderilen x deðiþkeni const bir deðiþken olmadýðý için deðeri deðiþir.
				// ve undefined behaviour'da oluþmaz çünkü x const bir ifade deðil.
				// Burada pointer to const olduðu için derleyici ptr adres deðiþkenini atamalara karþý derleme zamanýnda kapatýr. 
					// Buna sözleþmeye baðlý const denir.

	return (int*)ptr;   
}

int main(void) {
	int x = 45; // Eðer const int x = 45; olarak deklare edilmiþ olsaydý, yukarýda anlattýklarýmýn hepsi geçersiz olacaktý. Kod halen legal fakat
					// tanýmsýz davranýþ VAR.
	func(&x); // yukarýda pointer to const olduðu için derleyici compile time'da *ptr'i deðiþikliðe kapatmak zorunda. -> Sözleþmeye baðlý const
}

	// DÝKKAT! Bazý parametreli fonksiyonlara pointer parametrelerine NULL pointer atanabilir. Bu atama sadece fonksiyon tarafýndan bir opsiyon
	// olarak verildi ise yapýlabilir. Yani ancak fonksiyon tarafýndan önceden belirlendi ise NULL pointer atanabilir.
		// Fonksiyon þöyle diyor:
			// a)	ya bana bir nesne adresi göndereceksin
			// b)	ya da bana NULL pointer göndereceksin.
		// DÝKKAT: Bir fonksiyonun parametresi pointer ise dokümantasyonda kesinlikle NULL pointer alýp alamayacaðýný BELÝRT.
			// NULL pointer alýyor ise nasýl çalýþacaðýnýn da belirtilmesi gerekir.
/*
* 		Bazý fonksiyonlarýn bildirimi

		time_t time(time_t *ptr) -> time_t bir tür eþ ismi.

		ya bir nesne adresi istiyor set etmek için
		ya da NULL pointer istiyor. bu tip örnekler var.
		NULL göndermek opsiyon ise dökümantasyonda yazar.

		fflush(FILE *)  ->  bu bir nesnenin adresini istiyor ve iliþkili 
		dosyanýn bufferýný flush ediyor.Yani bellekteki byte larý dosyaya 
		yazýyor.

		swap(&x, NULL); // swap fonksiyonunda gönderilen adreslerin içeriðine eriþildiði için NULL pointerin içeriðine eriþmek
			tanýmsýz davranýþ oluþturur.
		
		Statik deðiþkenli bir adres döndüren fonksiyondaki deðeri kullanmadan ayný fonksiyonu tekrar çaðýrmamalýyýz. Çünkü statik ömürlü
			deðiþkenler program sonuna kadar hayatta kaldýðý için durmadan ayný deðer döndürülür.

		NULL bayrak deðiþken gibide kullanýlabilir.
			int *ptr = NULL;
			if(expr)
			{
				ptr = nesne adresi  // if e girerse ptr deðeri deðiþir.
			}


			int *ptr = NULL;
			//dangling pointer -> dangling pointer gerçek bir pointer deðil.

			// ptr geçerli

			// hayatý sona erdi

			burada *ptr = ...  UB olur mesela.

			burada dangling hale gelmþ pointer a NULL deðerini atamak mesela bir kullaným
			þeklidir.
//////////////////////////////////////////////////////////////////////////////////////////////////

												TÜR EÞ ÝSÝM BÝLDÝRÝMLERÝ(TYPE-DEF DECLARATIONS)
	-Hali hazýrda bulunan bir türe o türü temsil edecek eþ bir isim vermek.
		alias -> takma ad(mahlas)
		type-alias -> tür takma adý - tür eþ ismi
	-define preprocessor komutu ile karýþtýrma.
		ön iþlemci komutlarý o kelime ile yer deðiþtirir.
			#define WORD int -> bu WORD gördüðü int yazar. Bazý durumlarda ayný iþi yapýyor olabilirler ama
				type-alias ise WORD için isim bildirimi yapar.

	-TYPE-DEF bildirim nasýl yapýlýr?
		keyword tür-ismi türe-verilen-eþ-ismi -> typedef int WORD; 
			Artýk WORD int'in eþ ismi olarak davranýlacak. 
	-typedef statik veya global deðil. Nerede/nasýl declare edildiðine göre deðiþir. Eðer statik ise her yeri, dynamic ise bulunduðu
		kod bloðunu etkiler sadece.

	-typedef int* IPTR;
		IPTR == int*; // IPTR aslýnda int*
		#define iptr int*
		int main(void){
			typedef int* IPTR;
			IPTR x, y, z; // Bu aslýnda int* x; int* y; int* z; bildirimine eþ deðer. 
			iptr p1, p2, p3; // Burada ise sadece p1 int* türündendir. iptr yerine int* yapýþtýrma iþlemi yapýlýr(define makrosu) ve sadece p1 int* olur.
		}
	- ALTIN KURAL!!!!
		1 -  O türden bir deðiþken tanýmla:
			int x; // gibi
		2 - Tanýmlamanýn baþýna typedef keywordünü getir.
			typedef int x;
		3 - Deðiþken ismini tür eþ ismi olarak deðiþtir.
			typedef int Word;
		ÖRNEK:
		int a[10];
			typedef int a[10];
				typedef int ARR[10]:
					Artýk ARR yazýldýðýnda boyutu 10 olan diziler oluþturulabilecek.
						typedef int ARR[10];
						ARR a,b,c; // bu int a[10], b[10], c[10];
	-Bir tür eþ isminin bir keyword olarak cast edilmesi, o keywordün kullanýlmasýný engellemez.
		typedef int counter;
		counter x;
		int y; // int kullanýlmaya devam edilebilir.
	-Bu kullanýmda da bir sýkýntý yok -> typedef int INT32, counter; // tamamen legal.

	-ÇOK ÖNEMLÝ!
		typedef int* IPTR;
		typedef const int* CIPTR;
		int main(void){
			int x = 5;
			int y = 10;
			const IPTR p = &x; // Bu düþünülenin aksýna pointer to const int deðil const pointer to int yani
								// const int* ptr -> buna sadece read-only eriþebilirken, const IPTR p -> bunun içeriði deðiþtirilebilir
									// gösterdiði adres deðiþtirilemez. YANÝ TAM TERSÝ. ÖNEMLÝ!
			CIPTR p2 = &x; // Bu legal
			*p2 = 31; // Deðer atamak illegal çünkü CIPTR pointer to const int yani read-only olarak iþ yapýyor.
			const CIPTR p3 = &x; // Bu const pointer to const int, Yani ne deðeri deðiþtirilebilir ne de gösterdiði adres.
									// CIPTR'den önceki const p3 identifierýný niteler. CIPTR kendisi const int* olduðu için sadece salt okunur olur
										// ilk const'ta p3'ü niteleyerek deðiþkeni const yapar. Yani p3 deðiþkenine hiçbir atama yapýlamaz, illegaldir.
			*p3 = 52; // illegal
			p3 = &y; // illegal
			typedef const int carr[6];
			carr a; // -> const int a[6];
		}

	-ÖNEMLÝ	Mülakat sorusu bu.
		typedef int Word,*Ptr;
		typedef int word; ve typedef int *Ptr; ile ayný

	-C99'da _Bool eklennee kadar bool türü olarak geleneksel olarak int kullanýlýyordu.
		#define true 1
		#define false 0
		typedef int BOOL;
		typedef int counter;
		int main(void){
			BOOL x = true;
			counter y; // diyelim ki counter(int) tutabileceði deðeri aþacaðýz. Bunun için sadece typedef'teki keywordü deðiþtirmek yeterli.
			//typedef long long int counter; -> bu sayede counter deðiþkeninin kullanýldýðý her yerde long long int kullanýlýr.

		}
*/ 











