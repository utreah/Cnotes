#include "C:\Users\Liver\Documents\GitHub\Cnotes\|nUtility.h"
/*
bir fonksiyonun parametresi pointer ise biz buna dizinin adresini g�nderebiliriz.

pointer daki veriye p[i] veya *(p+i) ile eri�ilir.

dizi de�i�meyecekse const int * ptr �eklinde parametre tan�mlamak mant�kl�.

fonksiyon parametrelerini ba�ka bir fonksiyona arg�man olarak g�nderebilirim.

void func(int x); ile
void func(const int x); aras�nda hi�bir fark yok. Bu function redeclaration olarak kabul ediliyor. Bildirim anlam�nda hi�bir fark yok.
							hi�bir avantajda sunmuyor. Bu durum CPP'de de ayn�. Derleyici kodu g�rd���nde e�er parametre de�i�kenin de�eri
								de�i�medi�ini g�rd���nde optimizasyonunu ona g�re yap�yor.


*/

int sum_array(const int* p, int size)
{

	int sum = 0;
	while (size--)
		sum += *p++;

	return sum;
}

double get_array_mean(const int* p, int size)
{
	return (double)sum_array(p, size) / size;
}

double get_std_dev(const int* p, int size)
{
	double mean = get_array_mean(p, size);
	double sum_square = 0;

	for (int i = 0; i < size; i++)
		sum_square += (p[i] - mean) * (p[i] - mean);

	return sqrt(sum_square / size);
}
//Elemanlar� reverse etme kodu. nutility ye eklendi
void reverse_array(int* p, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		swap(p + i, p + size - 1 - i);
	}
}

//Bu da nutility ye eklendi.
void get_min_max(const int* p, int size, int* max, int* min)
{
	*max = *min = *p;
	for (int i = 1; i < size; i++)
	{
		if (*min > *(p + i))
			*min = *(p + i);
		if (*max < *(p + i))
			*max = *(p + i);
	}
}


void bsort(int* p, int size)
{
	for (int i = 0; i < size - 1; i++)
		for(int j = 0; j < size - 1 - i; j++)
			if (p[j] > p[j + 1])
			{
				//swap(&p[j],&p[j+1]); buda �al���r fakat alttakini tercih ettik
				swap(p + j > p + j + 1);
			}
}



void copy_array(int* pdest, const int* psource, int n)
{
	while (n--)
		*pdest++ = *psource++;

}
int copy_array_main()
{
	int a[20];
	int b[20] = { 0 };
	int idx_a, idx_b, n;
	printf("a'da indeks: ");
	scanf("%d", &idx_a);
	printf("b'de indeks: ");
	scanf("%d", &idx_b);
	printf("Ka� adet kopyalans�n: ");
	scanf("%d", &n);

	// E�er kaynak dizinin belirli yerinden belirli adetine kadar de�erleri hedef diziye yazd�rmak i�in g�ndermemiz gereken parametreler �unlar;
	copy_array(a + idx_a, b + idx_b, n);
	// Kaynak olarak kullan�lan dizi(bu durumda b) e�er de�erleri initialize edilmediyse yani garbage value tutuyor ise bu de�erleri kullanmak UB.
		// int b[20]; �eklinde olursa buradan gelecek de�erleri kullanmak UB, int b[20] = { 0 }; olur ise SIKINTI YOK.

}
// NOT: E�er bir fonksiyonun bir yerden okuma bir yere yazma i�lemi yapacak ise std. lib'in kulland��� konvensiyonel
//		parametre s�ralamas� her zaman: �nce hedef ->  sonra kaynak adres
int ptr_main()
{
	// �ki pointerin fark� i�aretli tam say� t�r�ndendir.
		int a[10];
		printf("%d", (p + 5) - (p + 4)); // ekrana 1 yazd�r�r. 
		printf("%d", &p[5] - &p[4]); // ekrana 1 yazd�r�r. 
}



int main()
{
	int x = 5;
	int y = 4;
	int diff = &x - &y; // 1 yazdr�r�r fakat kullan�m alan� yok. Derleyicye ba�l� bu y�zden Unspecified Behaviour. 


	// Bir fonksiyonun parametre de�i�keni bir pointer ise iki farkl� �ekilde g�sterilebilir;
	//	1 - int func(int* p); veya, 
	//  2 - int func(int p[]); fakat
			// int func(int p[10]); standart burada bulunan tam say�y� discard eder. Dizinin boyutunun 10 oldu�u anlam�na gelmez.

	int x = 10;
	int* py = &x;
	int py[] = &x; // YANLI�, b�yle yap�lamaz. Bu durum sadece fonksiyonun parametre de�i�kenleri i�in ge�erli.

	///////////////////////////////////////////////////////////////////////////////////////////////
	// POINTER IDIOMLARI(IDIOMATIC POINTER EXPRESSIONS)
	
	// &x++ -> illegal, ��nk� x++ bir rvalue ve &(addressof) operat�r� ancak bir lvalue operand alabilir.
	// ++&x ->  illegal, ayn� durum ++ prefix increment operat�r� lvalue operand alabilir.	
	int a[3] = { 5,4,3 };
	int* p = a; // array decayden dolay� &a[0] oldu ve a'n�n ilk eleman�n�n adresi var.
					// dizilerin memoryde arka arkaya bulunma garantisi var.
	//*p++; -> tamamen legal hi�bir s�k�nt� yok dizinin 1 indis numaral� eleman�na ge�er.
	/*
			�OOOK �NEML�
	int x = 10;

	&x++;  ->	x++ rvalue exp. dur, & operat�r�de lvalue exp a etki eder.Sentaks hatas�.
	&++x;  ->	Ayn� �ekilde sentaks hatas�.illegal
	++&x;  ->	&x in degeri rvalue exp. dir. ama ++ operat�r� lvalue exp. e ihtiya� duyar.
				sentaks hatas�
	
	int a[10] = {0};
	int *p = a;
	*p++   ->	++ i�in, p bir lvalue exp dir.* operat�r� ise adrese ihtiya� duyar.Ge�erli.
				bu ifade lvalue exp. * operat�r� varsa lvalue exp �retir.
	*a++   -> Ge�ersiz. a bir dizi ve (a++) a burada array decayden dolay� rvalue olmaktan ��kar ve bu sentaks hatas�d�r.
	
	int a[5] = {0,10,20,30,40};
	int p = *a;

	// *++p; Ge�erli ve ifade sol taraf de�eri
	// *++p = -1; ikinci elemana yap�ld� atama
		---------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------

	Dizi Pointer farkl�l���.

	Dizi contiguous olarak bellekte n tane nesnenin birlikte tutuldu�u nesneler toplulu�u.
	Pointer ise sadece adres tutar.

	Mesela
	int *p;

	p[5] = 12;  TANIMSIZ DAVRANI�(UB)

	Array decay den dolay� kar��t�r�labilir.
	Array decay dizi ismini dizinin ilk eleman�n�n adresine d�n��t�r�yor.
	
	*/

}
void reverse_array(int* pdest, const int* psource, int size)
{
	psource += size;
	while (size--)
	{
		*pdest++ = *--psource;
	}
}
#define SIZE 5
void reverseArray(int* p, int size)
{
	int* pe = p + SIZE; // SIZE bir makro
	while (p < pe)
	{					// M�LAKAT SORUSU
		swap(p++, --pe);	// pe nin bir k�����n� p ile yer de�i�tir.P yi bir art�r.
	}					// pe zaten azaltl�yor i�lemden �nce.
}

void reverse_copy(int* pdest, const int* psource, int size)
{
	while (size--)
		*pdest++ = *(psource + size);
}
///////////////////////////////////////////////////////////////////
/*
											VALID VE INVALID POINTERLAR
Invalid Pointer: Kullan�lamaz olmas�, kendisine ge�erli bir adres atamadan asla kullan�lmamal�
Valid Pointer: Kullan�labilir olabilir, baz� i�lemlerde kullan�lmas� legal ve do�ru olabilir.
				D�KKAT: Bizler invalid pointerlar� asla kullanmamal�y�z.
	1 - Otomatik �m�rl�, ilk de�er verilmemi� adres de�i�kenleri:
		int* p; -> �u anda ge�ersiz, hi�bir de�er atamas� yap�lmam��.
			*p; -> sentaks hatas� ��nk� de�ere eri�meye �al���yoruz
	
		Dangling Pointer: Pointer de�i�ken hayatta olan bir nesneyi tutuyor. Bu nesne �mr�n� tamamlad���nda pointer ge�ersiz hale geliyor. Buna 'dangling pointer' denir.00
			Dynamic Memory Management k�sm�nda a��r� �nemli olacak.
	GE�ERL� PO�NTER:
		Ge�erli bir pointer demek o pointerin dereference edilebilece�i anlam�na gelmiyor(dereferencable de�il)
	int main(void)
	{
		int x = 10;
		int* p = &x; // ge�erli bir pointer, dereferencede edilebilir.

		int a[4] = {1, 2, 3, 4}
		int* p1 = &a[4]; // bu dizinin son indisi 3(a+3), dizi boyutunun d���na ��k�p bunu kullanmak UB olu�turur.
			Bir dizinin d���nda kalan adresini kullanmak 'valid' fakat dereferencable de�il. Ve bu dizinin d���nda kalan adresteki de�er
				kullan�l�rsa(dereference edilip) bu UB. (line 224) 
			Bu a+4 yani dizinin bitti�i eleman�n� dizinin ilk eleman�ndan ��kar�rsak dizinin boyutunu buluruz.
			a+4 - a = 4 // dizinin 4 elemanl� anlam�na gelir.
				Line 183teki psource += size; -> asl�nda bunu yapt���m�zda dizinin son eleman�n� de�il dizinin bitti�i elemana ula��r�z. 
					Bu de�i�keni kullanmakta sak�nca yok fakat dereference edilip de�eri kullan�l�rsa bu UB(Line 225)
						Bu �zellik sadece kar��la�t�rma i�lemleri i�in kullan�lacak!
		

		�NEML�!! Tekil nesnelerde adeta tek elemanl� dizilermi� gibi ele al�n�yor.
			int x = 10;
			int* p = &x + 1; // Bu GE�ERL�(VALID) bir pointer.
			printf("%d", *p); // bunu b�yle kullanmak UB ��nk� �u anda p adres de�i�keni x'ten sonraki adresi g�steriyor ve bu adres garbage value tutuyor.
			printf("%d", *--p); // Burada ise ekrana 10 de�erini yazd�r�r.
		Bu yukar�da anlat�lanlar sadece ve sadece dizinin bitti�i yer i�in ge�erli. Mesela 4 b�y�kl���nde bir dizinin 5. eleman� bitti�i yer olur.
			E�er 6. elemana eri�meye �al���rsam bu bir invalid pointer. �RNEK;
				int a[4] = { 0 };
				int* p = a + 5; // veya &a[5); // bundan yana s�k�nt� yok bu ge�erli
				int* p = a + 6; // veya &a[6); // INVALID pointer GE�ERS�Z.
				int* p = a - 1; // bu da ge�ersiz bir durum.
			Bu sadece dizinin bitti�ini g�steren eleman i�in �zel bir durum. CPP'de de ayn�.
		Bir pointerin ge�erli olabilmesi i�in �u �� senaryodan biri olmal�;
			-Ya hayat� devam etmekte olan bir nesnenin adresini
			-Ya dizinin bitti�i yerin adresi
			-Ya da null pointer denilen �zel bir adres // ileride i�leyecez.



	}

*/





/*											POINTERLAR VE KAR�ILA�TIRMA ��LEMLER�
int main(void)
{
	int a[5] = {0, 1, 2, 3, 4);
	int x = 10;
	int y = 30;
	int* p1;
	int* p2;
	
	p1 == p2;
		a) Ayn� nesnenin adresini tutuyorlar ise -> p1 = &x; p2 = &x;
			if (p1 == p2)
				printf("EKRANA DOGRU YAZDIRIR");

		b) Ayn� dizinin bitti�i yerin adresini tutuyorlar ise -> p1 = a + 5; p2 = a + 5;
			if (p1 == p2)
				printf("EKRANA DOGRU YAZDIRIR ��NK� �K�S�DE AYNI D�Z�N�N B�TT��� YERDEK� ELEMANIN ADRES�N� G�STER�YOR");

		c) �kisinin de�eri de null pointer ise. p1 = &x; p2 = NULL; -> NULL bir makro
			if(p1 == p2)
				// Yanl�� oldu�u i�in else k�sm�na girer.

	p1 != p2;

	p1 > p2;
	p1 >= p2;

	p1 < p2;
	p1 <= p2;

}





*/