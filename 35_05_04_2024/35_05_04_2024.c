/*
												NULL POINTER NED�R?

	-NULL bir makro, keyword veya identifier de�ildir.
	-NULL bir adres sabiti olarak kabul ediliyor yani adres de�i�kenlerine atanabilir, adres de�i�keni olmayan de�i�kenlere ilk de�er vermek i�in
		kullanmak do�ru de�il.
			int x = NULL; ifadesi do�ru de�ildir b�yle kullan�lmamal�d�r.
	-Telaffuz edilirken null pointer olarak edilmeli, sadece null demek do�ru de�il anlam farkl�. sadece null denir ise, null character null string gibi 
		kavramlar ile kar���kl�k ya�an�r. O y�zden null ptr demek mant�kl�.
	-NULL pointer ge�erli bir adres fakat hi�bir nesnenin adresi de�il.
	-NULL pointerin bir adres de�i�keninde kullan�lmas� onu valid pointer yapar.
	-D�KKAT! NULL pointer� dereference etmek Undefined Behaviour.
		int main(void){
			int* p = NULL;
			int z = *p; // UNDEFINED BEHAVIOUR, Derleyici derleme zaman�nda bunun kontrol�n� yapmak zorunda de�il.
			int y = p[0]; // UNDEFINED BEHAVIOUR

		}
	-iki pointer de�i�kenin ikisinin de de�eri NULL ptr ise bu pointer de�i�kenler de�erce e�ittir. 
		"==" operat�r� ile i�leme sokulursa True(1) de�eri d�nd�r�l�r.

	-C ve CPP dillerinde lojik bir ifade beklenen yerlerde bir adres(pointer) ifadesi kullan�labilir.
		-E�er pointer de�i�kenini NULL makrosunu g�steriyor ise logical FALSE(0)
		-E�er pointer de�i�keni NULL makrosunu g�sterM�YOR ise logical TRUE(1)
			int* foo();
			int main(void)
			{
				int x = 36;
				int* ptr = &x;
				int* ptr2 = NULL;
				if(ptr2 == NULL) == if(!ptr2) // Line 20
				if(ptr != NULL) == if(ptr) //Line 21
				if(foo() == NULL) == if(!foo()) // Line 20
				if(foo() != NULL) == if(foo()) // Adres d�nd�ren fonksiyonlarda da durum ayn�. Line 21
			}
	-NULL makrosunu kullanabilmek i�in NULL makrosunun tan�mland��� bir dosyay� include etmemiz gerek.
		E�er include edilmez ise derleyici NULL'� bir identifier olarak kabul edecek ve hata alaca��z.
	
	-�lk de�er verilmeyen otomatik �m�rl� pointer de�i�kenler hayata ��p de�er(garbage value/indeterminent value) olarak ba�lar.
		Ama ilk de�er verilmeyen statik �m�rl� adres de�i�kenleri hayata NULL pointer ile ba�lar. Bu garanti alt�nda.
			int sp*;
			int main(void){
				static int* msp;
				if(sp == NULL) // if'in do�ru k�sm�na girer.
				if(msp == NULL) // if'in do�ru k�sm�na girer.
			int x = 356;
			int* p = 5; // Adres de�i�keni de�il.

			p = x; // burada implicit type conversion olur ��nk� p adres de�i�keni, x ise normal tam say� de�i�keni. x int* a cast edilir.
				//B�yle bir kod yaz�lmamal�.
			int* p = 0;
			p = 0;

			}
	-Normal olarak bir pointer de�i�keni bir tam say� de�eri atanmamal�d�r(ilk de�er verme dahil). B�yle bir atama C dilinde yanl��t�r, CPP'de sentaks hatas�.
		Ancak, bu durumun bir istisnas� vard�r. Bir pointer de�i�kenine tam say� sabiti olarak 0 de�eri atanabilir. Derleyici 0 sabitini
			null pointer'a d�n���r. Bu d�n���me NULL POINTER CONVERSION denir.

			int main(void){
				int* p = 0;
				p = 0;
					// �kisinde de sorun yok 0, null pointer'a d�n��t�r�lecek. Bu olaya NULL POINTER CONVERSION denir.
				if(p == 0) == if(p == NULL)
				// Hoca p == 0 �eklinde yazmak yerine p == NULL makrosunu kullanmak kodun niyetini daha iyi a��klad���n� s�yl�yor.

				int x = 0;
				int* ptr = x; // Bu kod C'de yanl�� CPP'de sentaks hatas�.
			}
	/////////////////////////////////////////////////////////////////////////////
						NULL POINTER NE ��E YARAR?


	-Bir i� yapmaya y�nelik, i�lem sonunda adres d�nd�ren fonksiyonlarda kullan�l�r.
		a) fonksiyon i�ini yapar ve ba�ar�l� olur. ��ini yaparsa �a��ran kodun kullanaca�� bir adres d�nd�r�r.
		b) fonksiyon i�ini yapamaz ve ba�ar�s�z olur. ��ini yapamaz ise NULL pointer d�nd�r�r.
		Mesela fopen() fonksiyonu ba�ar�l� bize bir yap� nesnesinin adresini d�nd�r�yor, ba�ar�s�z olurs NULL pointer d�nd�r�yor.
			FILE* f = fopen("ugur.txt", "r");
			if (f == NULL)
				printf("TXT olusturulamad�");
			else
				printf("TXT olusturuldu");
				
		malloc() ba�ar�l� olursa dinamik olarak ayarlanan o blo�un adresini d�nd�r�yor, ba�ar�s�z olursa NULL pointer d�nd�r�yor.
	-Veri yap�lar�nda arama i�lemi yap�yor.(adres d�nd�r�r)
		a) E�er veri bulunursa(ba�ar�l�) o verinin adresini d�nd�r�r.
		b) E�er veri bulunamaz(ba�ar�s�z) ise NULL pointer d�nd�r�l�r.

		





*/
#include <stdio.h>
int* search_in_array(const int* p, int size, int key)
{
	while (size-- && p++) // burada size-- 0 oldu�unda short circuit olacak ve d�ng�den ��k�lacak.
		if (*p == key)
			return (int*)p;
	return NULL;
}
int main(void) {

	int a[4] = { 1,12321,412421,3152 };
	int ival;
	scanf("%d", &ival);
	int* p = search_in_array(a, 4, ival);
	if (p != NULL) // if(p) olarakta yaz�labilir
		printf("Aranan %d sayisi, %d. indiste bulundu.", *p, p - a);
	else
		printf("Deger bulunamadi.");
}
// Fiziksel Const: const int x = 10; // x burada fiziksel const olarak bulunuyor.

void func(const int* ptr) {
	// *ptr; Compile time a��s�ndan bak�ld���nda gelen nesnenin const olup olmamas� dikkate al�nmaks�z�n *ptr const bir ifadedir.
			// e�er yollanan nesne const ise fiziksel const, de�il ise s�zle�meye ba�l� const.
	int* p = (int*)ptr;
	*p = 987; // Burada bir s�k�nt� ya�anmaz ��nk� fonksiyona g�nderilen x de�i�keni const bir de�i�ken olmad��� i�in de�eri de�i�ir.
				// ve undefined behaviour'da olu�maz ��nk� x const bir ifade de�il.
				// Burada pointer to const oldu�u i�in derleyici ptr adres de�i�kenini atamalara kar�� derleme zaman�nda kapat�r. 
					// Buna s�zle�meye ba�l� const denir.

	return (int*)ptr;   
}

int main(void) {
	int x = 45; // E�er const int x = 45; olarak deklare edilmi� olsayd�, yukar�da anlatt�klar�m�n hepsi ge�ersiz olacakt�. Kod halen legal fakat
					// tan�ms�z davran�� VAR.
	func(&x); // yukar�da pointer to const oldu�u i�in derleyici compile time'da *ptr'i de�i�ikli�e kapatmak zorunda. -> S�zle�meye ba�l� const
}

	// D�KKAT! Baz� parametreli fonksiyonlara pointer parametrelerine NULL pointer atanabilir. Bu atama sadece fonksiyon taraf�ndan bir opsiyon
	// olarak verildi ise yap�labilir. Yani ancak fonksiyon taraf�ndan �nceden belirlendi ise NULL pointer atanabilir.
		// Fonksiyon ��yle diyor:
			// a)	ya bana bir nesne adresi g�ndereceksin
			// b)	ya da bana NULL pointer g�ndereceksin.
		// D�KKAT: Bir fonksiyonun parametresi pointer ise dok�mantasyonda kesinlikle NULL pointer al�p alamayaca��n� BEL�RT.

1:10











