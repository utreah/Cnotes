ÖNEMLÝ
SIZEOF operatörü UNSIGNED INT TÜRÜNDENDÝR. Eðer iþaretli bir türden deðiþken ile iþleme sokulacak ise DÝKKAT EDÝLMELÝ.
int a[10];
a[15] = 30; ->bu sentaks hatasý deðil.compile time hatasý deðil runtime hatasý ve tanýmsýz davranýþ.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


sizeof operatörünün operandý bir expr(ifade) olabilir.
Bu durumda derleyici sizeof operatörünün operandý olan ifadenin türüne bakar.
ve sizeof operatörü o türün storage deðerini üretir.

DÝKKAT!
sizeof operatörünün böyle kullanýmýnda parantez kullanýlmaz. Kullanýlýrsa öncelik parantezi haline gelir.

int main(void)
{
	int x = 10;
	sizeof x; // burada paranteze gerek yok. 
	printf("%zu", sizeof x); // ekrana 4 yazdýrýr çünkü benim derleyicimde integer tam sayý türünün storage için gerekli alaný 4.
}

#include <stdio.h>

int main()
{
	char c = 5;
	printf("%zu", sizeof(c)); // 1 çýkar
	printf("%zu", sizeof(c + c)); // 4 çýkar sebebi ise integral promotiondan dolayý. Ýki char iþleme girdiðinde integral promotiondan dolayý int olur ve ekrana 4 çýkar.
	printf("%zu", sizeof(c > 4 ? 1 : 1.)); // 8 yazar, her ne kadar karþýlaþtýrma doðru olsa da derleyici türüne bakarken 2. ve 3. operandýn türüne bakar ve büyük olan türü ele alýr.
}

#include <stdio.h>

int main()
{
	int c = 5;
	printf("%zu\n", sizeof(++c)); // ÇOK ÖNEMLÝ! : sizeof operatörünün operandý için derleyici tarafýndan bir iþlem kodu üretilmez. operandýn yan etkisi olsa dahi iþlem kodu olmadýðý için
	printf("%d", c); // burada 6 deðil 5 ekrana yazdýrýlýr. 
}

unevaluated context : iþlem kodu üretilmeyen ifadelere unevaluated context denir(CPP'de') necati hoca C içinde kullanýyor.C için sadece sizeof operatörü.
- eðer ifade yan etki içeriyor ise yan etki gerçekleþmez.
- sizeof operandlarý iþlem kodu üretmediði için UB için endiþelenmeye gerek yoktur.x / y(y = 0) bu durumda UB var iken sizeof(x / y) bunda UB yoktur.

sizeof operatörünün operandý bir dizi olduðunda ARRAY DECAY(array to pointer conversion) UYGULANMAZ.Doðrudan dizinin türü ne ise o kabul edilir.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

printf("%zu", sizeof(int a[10])); // burada ekrana yazacak deðer 40, çünkü dizinin her indisi int türünde bir eleman tutacaðýndan ve 10 ayrý int türünden eleman olduðundan dolayý 40 olur.
printf("%zu", sizeof(double a[100])); // burada ekrana yazacak deðer 800, çünkü dizinin her indisi double türünde bir eleman tutacaðýndan ve 100 ayrý double türünden eleman olduðundan dolayý 800 olur.
// bu sizeof ile kullanýlan tüm türler için geçerli. Üretilen bir iþlem kodu yoksa array decay de yok.

#include <stdio.h>
int main(void)
{
	int a[20] = { 0 };
	// #define ASIZE(a) (sizeof(a) / sizeof(a[0])) -> fonksiyonel makro hali.
	printf("%d", sizeof a / sizeof a[0]); // bu idiyomatik yapý bize dizinin boyutunu söyler. 80 / 4 -> 20
										// bu idiyomatik yapý eðer a dizisinin boyutu verilmeseydi a[] = {1, 2, 3, 4, 5, 6,} ve bu dizinin boyutunu constant bir ifade olarak kullanmak
										// isteseydik bu yöntemle kullanabilirdik.
	int b[sizeof a / sizeof(a[0])]; // geçerli bir dizi tanýmý.
	unsigned int sz = sizeof(a[21]); // UB veya baþka bir hata yok çünkü iþlem kodu üretilmiyor. Normalde pointer hatasý(UB)
	return 0;
}
#include <stdio.h>

int main()
{
	int a[] = { 1, 2, 3, 4, 5, };
	for (int i = -3; i < sizeof(a) / sizeof(a[0] - 3); ++i) // ekrana hiçbir þey yazdýrýlmaz, sizeof keywordünün türü benim derleyicimde unsigned int. 
		printf("%d", a[i + 3]); // int i = -3 ise signed olduðu için implicit conversiondan dolayý -3 unsigned olduðunda çok büyük bir pozitif sayý olacak ve
	// þartlar saðlanmadýðýndan dolayý ekrana hiçbir þey yazdýrýlmaz. sizeof(a)'dan önce (int) eklenir ise dizinin bütün elemanlarýný ekrana yazdrýr.
}

//////////////////////////////////////////////////////////////////////////DÝZÝLER///////////////////////////////////////////////////////////


a[i] yazmak ile i[a] yazmak arasýnda hiçbir fark yok. Derlenir ve çalýþýr. C/CPP'de' sýkýntý yok. Nedenini pointer kýsmýnda öðreneceðiz.

//////////////////////////////////////////////////////////////////////////DÝZÝLER///////////////////////////////////////////////////////////
#include "nUtility.h"
#include <stdio.h>
#define SIZE 100
int main(void) // bir dizinin deðerlerinin toplamýný veren kod. Karmaþýklýðý (complexity) -> O(n) dizinin boyutu arttýkça süre artar, Linear
{			// Algoritmanýn karmaþýklýðý, en karmaþýk kýsmý ele alýnarak belirlenir.
	int a[SIZE];
	RANDOMIZE();
	set_array_random(a, SIZE);
	print_array(a, SIZE);

	int sum = 0;

	for (int i = 0; i < sizeof(a) - sizeof(a[0]), ++i)
		sum += a[i];
	printf("sum = %d", sum);
	printf("Avg = %f", sum / SIZE); // Tanýmsýz davranýþ var, %f yazarak UB yapýyoruz çünkü %f formatý double için. %d olmalý! veya tür dönüþtürme
									// operatörü kullanýlmalý (double) sum / SIZE;
} // bu kodda UB ihtimali var. Eðer sum int türünün taþýyabileceði deðerlerin üstüne çýkarsa overflowdan dolayý tanýmsýz davranýþ olabilir. 


#include <stdio.h>
int main(void)
{
	int a[SIZE];
	RANDOMIZE();
	set_array_random(a, SIZE);
	print_array(a, SIZE);

	int oddsum = 0;
	int odd_counter = 0; // eðer hiç tek say yok ise UB oluþur! o yüzden ya if kontrolü ya da counter 1 olacak

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

	// randomize çalýþtýrýldý en yukarýda zaten.gerek yok.
	set_random_array(a, SIZE);
	set_random_array(b, SIZE);
	sort_array(a, SIZE);
	sort_array(b, SIZE);

	print_array(a, SIZE);
	print_array(b, SIZE);

	
	// iki arrayi C arrayinde sýralý bir þekilde birleþtirmek istiyoruz.
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
		printf("%d ", i[a]);  // bu legal.Pointerlarda görülecek.a[i] ile i[a] arasýnda fark yok.
	}

	return 0;
}


// ÇOK ÖNEMLÝ
	int c[] = { 4,6,2,6,1,5,9,7,8 };

	/*
	for (int i = -2; i < asize(c) - 2; i++) // burada asize unsigned int. karþýlaþtýrýlmýþ. i de type casting iþlemine sokulur.
		printf("%d ", c[i+2]);				// -2 olduðu için unsigned int e çevrilince deðeri 4.2 milyar küsür olur.döngüye girmez.
	*/									

	int c1[asize(c) * 2] = {0};  // diðer dizinin boyutuna göre yapýlandýrýlabilir.
	int c2[asize(c) * 3 / 2] = {0};

	x = 5;
	int y = 5;
	printf("%d", sizeof ++x + ++y); // int olduðu için 4. iþleme sokulmadý ++. ikincideise sokulur. 4+6 = 10

	putline();
	printf("\n");

	//============================================================
	//============================================================
	//============================================================

// odev adli resime baq
// reverse algorithm