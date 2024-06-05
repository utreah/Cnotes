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

1:10











