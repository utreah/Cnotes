#include <stdio.h>
#include <string.h>
#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
/*
	idiyomlar
	-const char* pdays[] = {"", "Pazartesi", "Sal�"...}; // ilk indexi bo� b�rak�yoruz ki pazartesi 1 de�erini als�n. 
				"" -> bu NULL ptr
	-const char* pmonths[] = {"Ocak", "Subat", "Mart", "Nisan", NULL}; -> NULL karakteri dizinin boyutunu do�rudan kullanm�yoruz
		// mesela bir d�ng� var ve bu d�ng�y� NULLptr gelene kadar d�nd�rebiliriz. Bu sayede dizinin uzunlu�u de�i�ti�inde
			// de�i�iklik yapmam�za gerek kalmaz
			int i = 0;
			while(pmonths[i++] != NULL);
	-const char* pyears[5] = {"2001", "2002", "2003", "2004" "2005"}; // 2004 ile 2005 aras�nda virg�l olmad��� i�in -> s�k�a yap�lan bir hata	
		// compile time'da bu birle�tirilecek. dizinin boyutu 5 fakat dizinin sadece ilk 4 indeksine ilk de�er atamas� yap�lm��.
			// son pyears[5] -> NUrr pointer de�erini alacak. Tam say� dizisi olsayd� '0' de�eri verilecekti.

	-//designated initializator
	char* p[100] = { [5] = "Ali",[12] = "Mehmet" };
	// ilk de�er verilmeyenler null ptr olur.

	regex(regular Expression): �yle bir notasyon olsun ki yaz�n�n uymas� gereken ko�ullar� ifade etsin.
		// Girilen yaz�n�n notasyona uyumlu olup olmad���n� kontrol ediyor. �rnek olarak bu websitelerinde kay�t olurken
			// epostalar i�in 'ge�erli bir e-mail adresi de�il' yaz�s�n� �rnek verebiliriz.
				// Belirli bir notasyon istiyor ve o notasyona uygunlu�unu kontrol ediyor
		-Validity Check:
		-Search
		-replacement
	/////////////////////////////////////////////////////////////////////////////////
	POINTEr TO POINTEr
		//Ba�ka bir pointerin adresini tutan pointer.
		//G�sterici g�steren g�sterici. (m�d�r m�d�r m�d�r?)

	int main(void){
		int x = 10;
		int* p = &x; // burada int t�r�ndne bir de�i�kenin adresini tutuyoruz.
	}
	T a; // T t�r�nden a de�i�keninin adresini tutmak i�in T* t�r�ndne bir de�i�ken tan�mlamam�z gerekiyor.
	// Peki ya T* t�r�nden bir de�i�kenin adresini tutmak isteseydik?
		-> T** p;
	int x = 500;
	int* p = &x;
	int** ptp = &p; // int* p bir nesne oldu�u i�in adresi vard�r. Bu adresi tutmak i�in ise int** t�r�nden bir
		// de�i�ken tan�mlayabiliriz. 
	int* ptp2 = &p; // burada p int* t�r�ndne bir de�i�ken ptp2'de ayn� �ekilde. Bu cpp'de sentaks hatas�
						// C'de �rt�l� d�n���m var. Ondan dolay� s�k�nt� yok
	int* tt = int** // �rt�l� d�n���m yap�l�r. C'de okey ama CPP sentaks

	int* p2 = &x; // Buna pointer to int deniyor
	int** ptp3 = &p; // pointer to pointer to int
	*p; // bu x de�i�kenine eri�ir.
	*ptp; // p de�i�kenine eri�ir.
	**ptp -> *(*ptp) // x de�i�kenine eri�ir.
	printf("%d", *p); // ekrana 500 yazd�r�r

	**ptp = 340; // x de�i�kenine eri�tik ve de�erini 340 yapt�k.
	printf("%d", **ptp); // ekrana 340 yazd�r�r (2 adet derefencing operat�r� kulland�k)
	**++ptp; -> ++(*(*ptp));
	printf("%d", **ptp); // ekrana 341 yazd�r�r 

*/

/////////////////////////////////////////////////////////////////////////////////////
/*
		Expression		Data Type		Value Category
		x				int				L
		&x				int*			R
		p				int*			L
		*p				int				L
		&p				int**			R
		ptr				int**			L
		*ptr			int*			R
		**ptr			int				L
		&ptr			int***			R
		bu nereye kadar gider?
			int * her kodda g�r�l�r.
			int ** bir�ok kodda g�r�l�r.
			int *** nadiren g�r�l�r.
			int **** neredeyse hi� g�rmeyiz.1-2 defa belki
			int ***** bunu unut :D
		int x = 99;
		int *p1 = &x;
		int **p2 = &p1;
		int ***p3 = &p2;
		int ****p4 = &p3;
		int *****p5 = &p4;
		int ******p6 = &p5;
		int *******p7 = &p6;
		int ********p8 = &p7;
		int *********p9 = &p8;
		int **********p10 = &p9;
		int ***********p11 = &p10;
		int ************p12 = &p11;
		int *************p13 = &p12;
		int **************p14 = &p13;
		int ***************p15 = &p14;
		int ****************p16 = &p15;
		int *****************p17 = &p16;
		int ******************p18 = &p17;
		int *******************p19 = &p18;
		int ********************p20 = &p19;

		p20 yi dereference edip ++ n�n operand� yapal�m
		++********************p20; -> bu x i 1 art�r�r.
		x = 100 oldu
*/
////////////////////////////////////////////////////////////////////
/*
	int a[] = {1, 2, 3, 4, 5,};
	int* p = a;
	int** ptp = &p;

	++*ptp; // p'nin adresini bir artt�r�z, p, a dizisinin adresini tuttu�u i�in sonraki indise ge�er.
	++**ptp; // bir �nceki ad�mda adresi artt�rm��t�k �imdi ise o adresin tuttu�u de�erin de�erini artt�r�yoruz. 
				// Bu durumda 2 -> 3 olacak.
		
Pointer to pointer ne i�e yarar?
	-Pointer de�i�kenlerinin adreslerini de�i�tirmek i�in kullan�l�r. 
	void foo(int*);
	void bar(int**);
	int main(void){
	int x = 45;
	int y = 32;
	int* p = &x;
	int* q = &y;
	foo(p); // x'in adresini g�nderiyoruz.
	bar(&p); // p'nin adresini g�nderiyoruz.
	////////////////////////
	a�a��da x ve y swap edildi.
	int temp = x;
	x = y;
	y = temp;
	E�er ben bunu fonksiyon ile yapmak isteseydim, x ve y de�i�kenlerini call by reference ile g�ndermek zorundayd�m.
		E�er x ve y'nin adreslerini g�ndermez isem fonksiyonda de�i�im olur fakat fonksiyon bitti�inde eski haline d�nerdi.
		swap(int* p, int* q);
		swap(&x, &y);
/////////////////////////////////////////////////////////////
	Pointer kullanarak swap yapal�m;
	int * ptemp = p;
	p = q;
	q = ptemp;
	B�yle yapt���m�zda da swap yapm�� oluyoruz. Bir projede birden fazla swap yap�yorsak her seferinde bunu yazmak mant�kl� de�il.
		O y�zden fonksiyon yapabiliriz. Fonksiyonu yazarken de parametrelerini pointer to pointer to data type �eklinde yazmak
			gerekli.
		pswap(int** p, int** q);
		pswap(&p, &q);

	}

*/
/*
	Pointer to Pointer �rnek.
		Diyelim ki 1 fonksiyon i�erisinde bir dizinin hem min ve hem max de�erleri bulunuyor ve bu iki de�erin adresleri d�nd�r�lmeli.
			return ile sadece 1 de�er d�nd�rebildi�imiz i�in pointer to pointer to data type kullanarak min ve max de�erlerinin
				adreslerini yaz�yoruz.
	#define SIZE 100
	void get_arr_min_max(const int* pa, size_t arr_size, int** pmax, int** pmin){
	*pmin = *pmax = (int *)pa;
		for(size_t i = 1; i < arr_size; i++)
			if(pa[i] > **pmax) // pmax'�n g�sterdi�i adresin g�sterdi�i adresinin de�eriyle kar��la�t�raca��m�z i�in ** kullan�yoruz.
				*pmax = (int*)&pa[i]; // pa[i]'nin adresini *pmax pointer�na at�yoruz. ��lem sonunda pmax, dizinin en b�y�k eleman�n� g�sterecek
			else if(pa[i] < **pmin)	// pmin'in g�sterdi�i adresin g�sterdi�i adresinin de�eriyle kar��la�t�raca��m�z i�in ** kullan�yoruz.
				*pmin = (int*)&pa[i]; // pa[i]'nin adresini *pmin pointer�na at�yoruz. ��lem sonunda pmin, dizinin en k���k eleman�n� g�sterecek
	} // i�lem sounnda ptr_max ve ptr_min de�i�kenleri max ve min de�erlerinin ADRESLER�N� tutacak.
	int main(void){
		int arr[SIZE] = {123,124215,26731,1232153,26132632,31};
		int* ptr_max = NULL;
		int* ptr_min = NULL;
		get_arr_min_max(arr, SIZE, &ptr_max, &ptr_min);
		printf("%d    %d", *ptr_min, *ptr_max); // min ve max de�erlerini ekrana yazd�rd�k.
		swap(ptr_min, ptr_max); // burada ptrlerin adreslerini g�ndermeye gerek yok. ��nk� takas i�lemini pointerlar �zerinde yapm�yoruz.
									// i�eriklerinin yerlerini de�i�tiriyoruz. E�er adreslerini g�nderseydik ptr_min 

	}
	
		#include <stdio.h>

		void func(int **p1, int **p2)
		{
		int ptemp = **p1; 
		**p1 = **p2;	
		**p2 = ptemp; 
		}

		int main()
		{
		int a = 34;
		int b = 67;
		int *pa = &a;
		int *pb = &b;
		printf("pa = %p          pb = %p\n", pa, pb);
		func(&pa,&pb); // a ve b'nin de�erlerini swap ettik. a->b, b->a;
		printf("pa = %p          pb = %p", pa, pb);
		}
	
*/
int x = 50;
int y = 75;
int z = 100;
int foo(int** param, int size) {
	for (int i = 0; i < size; i++)
		// param[i]; == a[0] == &x; Yani param[i] asl�nda int* t�r�nden bir nesneyi g�steriyor �u anda.
		printf("%d", *param[i]); // burada ise int* dereference edilerek x, y ve z nesnelerinin de�erlerine eri�iyoruz.
}
void bar(int*** x) {
	//x =  burada atama ptr, p veya x(main)'e olmuyor. int*** t�r�nden olan x'e atama yap�yoruz. Yani bu atamadan sonra
		// main g�vdesinde bulunan hi�bir nesnenin de�erinde de�i�iklik olmaz.
	*x; // ptr nesnesine eri�ir.
	**x; // p nesnesine eri�ir
	**x; // x nesnesine eri�ir
}
int main(void) {

	int* a[] = { &x, &y, &z }; // Normalde bir dizinin adresini bir fonksiyon parametresine g�nderdi�imizde fonksiyonun
								// T* t�r�nden olmas� yetiyor fakat burada a'n�n 0. eleman�n� int* t�r�nden bir de�er oldu�undan dolay�
									// fonksiyondan parametresi T** t�r�nden olmak zorunda
	foo(a, 3); // -> foo(&a[0], 3);
	int x = 10;
	int* p = &x;
	int** ptr = &p;
	bar(&ptr);

}

void print_names1(char* const* p, size_t size) //aradaki const a��klanacak.
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%s ", *(p + i));
	}

}



void print_names2(char* const* p, size_t size) //aradaki const a��klanacak. *p de�i�mez(const) demek bu
{
	while (size--)
	{
		printf("%s ", *p++);// *p++ -> burada �ncelik s�ras� sa�dan sola. p + 1 yap�l�p dereference yap�l�yor
	}						// kural ihlali yok. ++*p; yaz�lsayd�, tan�mda *p de�i�mez diyor.sentaks hatas�.

}
void sort_names(char** p, size_t size) // klasik bubble sort
{
	for (size_t i = 0; i < size - 1; i++)
		for (size_t k = 0; k < size - 1 - i; k++)
			if (strcmp(p[k], p[k + 1]) > 0)
			{
				char* ptemp = p[k];
				p[k] = p[k + 1];
				p[k + 1] = ptemp;
			}
}

int main(void) {

	char* pdays[] = { "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar" }; // bu isimleri yazd�rmak i�in bir
								// fonksiyon yaz�caz print_names1 ve 2.
		//pdays char* t�r�nden bir nesne oldu�u i�in fonksiyonun parametreleri T** t�r�ndne olmak zorunda. ��nk�
			//pdays'in ilk eleman�n�n adresini fonksiyona g�ndericez.
	print_names1(pdays, 7);
	int x = 10;
	// const'un yerini unutursak �una dikkat etmek gerekiyormu�.
		// const neyden �nce geliyorsa const olan nesne o'dur
	const int* p = &x; // burada const int*'dan �nce geliyor bu durumda const olan de�er x'tir. *p �zerinde de�i�iklik yapamay�z.
	int* const p = &x; // burada ise const p'den �nce geliyor bu durumda p'nin de�eri const olan de�erdir. 
							// *p ile burada x'in de�eri de�i�tirilebilir fakat p = &y; gibi ibr �ey yaparsak bu sentaks hatas�.

}
int b = 123;
int access(const int* const* p, int size) {
	// �imdi e�er access fonksiyonu parametre t�r� olarak int* const* p olarak al�rsa
		// const *p'yi niteler. Bu sayede dizinin elemanlar� (&x, &y, &z) de�i�tirilemezken, **p yap�larak adreslerini tuttuklar�
			// nesnenin de�erini de�i�tirebilir. Bunun �n�ne ge�mek i�in const int* const* p; �eklinde yap�yoruz
		// int*'dan �nce gelen const int*'� niteleyerek adresi g�nderilen T* t�r�nden dizinin de�erinin i�eriklerinin de�i�mesini
			// engelliyor.
	p[2] = &b; // sentaks hatas� ��nk� const *p'yi niteliyor ve tuttu�u adreslerin de�i�mesini engelliyor.(2. bir i�erik operat�r� ile
					// o adreslerin g�sterdi�i de�erde oynama yap�labiliyor)
	*p[2] = 5; // e�er const int* const* p �eklinde olursa parametre bu da sentaks hatas�. Bu durumda sadece okumak istedi�imiz i�in
					// const int* const* p �eklinde tan�ml�.
}
int main(void)
{
	// int* const* ��rendiklerimizden �ook farkl� fakat �ok basit.
		// e�er consttan sonra y�ld�z geliyorsa eri�emedi�imiz yer *idf'tir. �rne�in;
	int x = 10;
	int* p = &x;
	int* const *ptr = &p; // burada p'nin de�erinin de�i�tirilmesini engelliyoruz. ��nk� const *ptr'yi niteliyor.
	int** const ptr = &p; // burada const ptr'yi niteliyor ve ptr'nin &p d���nda bir de�er almas�n� engelliyor. p'nin i�eri�i de�i�tirilebilir.
	int const** ptr = &p; // burada ise ptr'nin ve p'nin de�erleri de�i�tirilebilir. Fakat x'in de�erinde de�i�iklik yap�lamaz.
	int y = 40;
	int z = 20;
	int* a[] = { &x, &y, &z }; // �imdi �yle bir fonksiyon yazal�m ki a'y� sadece okuma ama�l� kullanabilsin hi�bir de�erini
									// de�i�tiremesin.
	access_arr(a, 3);
}