�NEML�
SIZEOF operat�r� UNSIGNED INT T�R�NDEND�R. E�er i�aretli bir t�rden de�i�ken ile i�leme sokulacak ise D�KKAT ED�LMEL�.
int a[10];
a[15] = 30; ->bu sentaks hatas� de�il.compile time hatas� de�il runtime hatas� ve tan�ms�z davran��.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


sizeof operat�r�n�n operand� bir expr(ifade) olabilir.
Bu durumda derleyici sizeof operat�r�n�n operand� olan ifadenin t�r�ne bakar.
ve sizeof operat�r� o t�r�n storage de�erini �retir.

D�KKAT!
sizeof operat�r�n�n b�yle kullan�m�nda parantez kullan�lmaz. Kullan�l�rsa �ncelik parantezi haline gelir.

int main(void)
{
	int x = 10;
	sizeof x; // burada paranteze gerek yok. 
	printf("%zu", sizeof x); // ekrana 4 yazd�r�r ��nk� benim derleyicimde integer tam say� t�r�n�n storage i�in gerekli alan� 4.
}

#include <stdio.h>

int main()
{
	char c = 5;
	printf("%zu", sizeof(c)); // 1 ��kar
	printf("%zu", sizeof(c + c)); // 4 ��kar sebebi ise integral promotiondan dolay�. �ki char i�leme girdi�inde integral promotiondan dolay� int olur ve ekrana 4 ��kar.
	printf("%zu", sizeof(c > 4 ? 1 : 1.)); // 8 yazar, her ne kadar kar��la�t�rma do�ru olsa da derleyici t�r�ne bakarken 2. ve 3. operand�n t�r�ne bakar ve b�y�k olan t�r� ele al�r.
}

#include <stdio.h>

int main()
{
	int c = 5;
	printf("%zu\n", sizeof(++c)); // �OK �NEML�! : sizeof operat�r�n�n operand� i�in derleyici taraf�ndan bir i�lem kodu �retilmez. operand�n yan etkisi olsa dahi i�lem kodu olmad��� i�in
	printf("%d", c); // burada 6 de�il 5 ekrana yazd�r�l�r. 
}

unevaluated context : i�lem kodu �retilmeyen ifadelere unevaluated context denir(CPP'de') necati hoca C i�inde kullan�yor.C i�in sadece sizeof operat�r�.
- e�er ifade yan etki i�eriyor ise yan etki ger�ekle�mez.
- sizeof operandlar� i�lem kodu �retmedi�i i�in UB i�in endi�elenmeye gerek yoktur.x / y(y = 0) bu durumda UB var iken sizeof(x / y) bunda UB yoktur.

sizeof operat�r�n�n operand� bir dizi oldu�unda ARRAY DECAY(array to pointer conversion) UYGULANMAZ.Do�rudan dizinin t�r� ne ise o kabul edilir.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

printf("%zu", sizeof(int a[10])); // burada ekrana yazacak de�er 40, ��nk� dizinin her indisi int t�r�nde bir eleman tutaca��ndan ve 10 ayr� int t�r�nden eleman oldu�undan dolay� 40 olur.
printf("%zu", sizeof(double a[100])); // burada ekrana yazacak de�er 800, ��nk� dizinin her indisi double t�r�nde bir eleman tutaca��ndan ve 100 ayr� double t�r�nden eleman oldu�undan dolay� 800 olur.
// bu sizeof ile kullan�lan t�m t�rler i�in ge�erli. �retilen bir i�lem kodu yoksa array decay de yok.

#include <stdio.h>
int main(void)
{
	int a[20] = { 0 };
	// #define ASIZE(a) (sizeof(a) / sizeof(a[0])) -> fonksiyonel makro hali.
	printf("%d", sizeof a / sizeof a[0]); // bu idiyomatik yap� bize dizinin boyutunu s�yler. 80 / 4 -> 20
										// bu idiyomatik yap� e�er a dizisinin boyutu verilmeseydi a[] = {1, 2, 3, 4, 5, 6,} ve bu dizinin boyutunu constant bir ifade olarak kullanmak
										// isteseydik bu y�ntemle kullanabilirdik.
	int b[sizeof a / sizeof(a[0])]; // ge�erli bir dizi tan�m�.
	unsigned int sz = sizeof(a[21]); // UB veya ba�ka bir hata yok ��nk� i�lem kodu �retilmiyor. Normalde pointer hatas�(UB)
	return 0;
}
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, };
	for (int i = -3; i < sizeof(a) / sizeof(a[0] - 3); ++i) // ekrana hi�bir �ey yazd�r�lmaz, sizeof keyword�n�n t�r� benim derleyicimde unsigned int. 
		printf("%d", a[i + 3]); // int i = -3 ise signed oldu�u i�in implicit conversiondan dolay� -3 unsigned oldu�unda �ok b�y�k bir pozitif say� olacak ve
	// �artlar sa�lanmad���ndan dolay� ekrana hi�bir �ey yazd�r�lmaz. sizeof(a)'dan �nce (int) eklenir ise dizinin b�t�n elemanlar�n� ekrana yazdr�r.
}

//////////////////////////////////////////////////////////////////////////D�Z�LER///////////////////////////////////////////////////////////


a[i] yazmak ile i[a] yazmak aras�nda hi�bir fark yok. Derlenir ve �al���r. C/CPP'de' s�k�nt� yok. Nedenini pointer k�sm�nda ��renece�iz.

//////////////////////////////////////////////////////////////////////////D�Z�LER///////////////////////////////////////////////////////////
#include "nUtility.h"
#include <stdio.h>
#define SIZE 100
int main(void) // bir dizinin de�erlerinin toplam�n� veren kod. Karma��kl��� (complexity) -> O(n) dizinin boyutu artt�k�a s�re artar, Linear
{			// Algoritman�n karma��kl���, en karma��k k�sm� ele al�narak belirlenir.
	int a[SIZE];
	RANDOMIZE();
	set_array_random(a, SIZE);
	print_array(a, SIZE);

	int sum = 0;

	for (int i = 0; i < sizeof(a) - sizeof(a[0]), ++i)
		sum += a[i];
	printf("sum = %d", sum);
	printf("Avg = %f", sum / SIZE); // Tan�ms�z davran�� var, %f yazarak UB yap�yoruz ��nk� %f format� double i�in. %d olmal�! veya t�r d�n��t�rme
									// operat�r� kullan�lmal� (double) sum / SIZE;
} // bu kodda UB ihtimali var. E�er sum int t�r�n�n ta��yabilece�i de�erlerin �st�ne ��karsa overflowdan dolay� tan�ms�z davran�� olabilir. 


#include <stdio.h>
int main(void)
{
	int a[SIZE];
	RANDOMIZE();
	set_array_random(a, SIZE);
	print_array(a, SIZE);

	int oddsum = 0;
	int odd_counter = 0; // e�er hi� tek say yok ise UB olu�ur! o y�zden ya if kontrol� ya da counter 1 olacak

	for (int i = 0; i < sizeof(a) - sizeof(a[0]), ++i)
		if(a[i] % 2 != 0)
			oddsum += a[i];
	if (odd_counter)
		printf("%d", oddsum);
	int  max = a[0];
	for (int i = 1; i < SIZE; i++)
		if (a[i] > max)
			max = a[i];
	printf("MAX: %d", max);
}


#undef	 SIZE
#define		SIZE	 10

	a[SIZE];
	int b[SIZE];
	int merged[2 * SIZE];

	// randomize �al��t�r�ld� en yukar�da zaten.gerek yok.
	set_random_array(a, SIZE);
	set_random_array(b, SIZE);
	sort_array(a, SIZE);
	sort_array(b, SIZE);

	print_array(a, SIZE);
	print_array(b, SIZE);

	
	// iki arrayi C arrayinde s�ral� bir �ekilde birle�tirmek istiyoruz.
	int idx_a = 0;
	int idx_b = 0;

	for (int i = 0; i < 2 * SIZE; i++)
	{
		if (idx_a == SIZE)
			merged[i] = b[idx_b++];

		else if (idx_b == SIZE)
			merged[i] = a[idx_a++];

		else if (a[idx_a] < b[idx_b])
			merged[i] = a[idx_a++];

		else
			merged[i] = b[idx_b++];
	}

	print_array(merged, 2 * SIZE);


	//------------------------------------
	//------------------------------------

	printf("\n");
	
	int r[10] = { 5,3,2,5,6,7,1,9,7,8 };

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", i[a]);  // bu legal.Pointerlarda g�r�lecek.a[i] ile i[a] aras�nda fark yok.
	}

	return 0;
}


// �OK �NEML�
	int c[] = { 4,6,2,6,1,5,9,7,8 };

	/*
	for (int i = -2; i < asize(c) - 2; i++) // burada asize unsigned int. kar��la�t�r�lm��. i de type casting i�lemine sokulur.
		printf("%d ", c[i+2]);				// -2 oldu�u i�in unsigned int e �evrilince de�eri 4.2 milyar k�s�r olur.d�ng�ye girmez.
	*/									

	int c1[asize(c) * 2] = {0};  // di�er dizinin boyutuna g�re yap�land�r�labilir.
	int c2[asize(c) * 3 / 2] = {0};

	x = 5;
	int y = 5;
	printf("%d", sizeof ++x + ++y); // int oldu�u i�in 4. i�leme sokulmad� ++. ikincideise sokulur. 4+6 = 10

	putline();
	printf("\n");

	//============================================================
	//============================================================
	//============================================================

// odev adli resime baq
// reverse algorithm