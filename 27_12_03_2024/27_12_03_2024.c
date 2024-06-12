#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdlib.h>
#include <stdio.h>

/*reverse i�in->��e say�s�n�n yar�s� kadar d�nen d�ng�.ba�tan birinci sondan birinci, ikinciye ikinci, ���nc�ye ���nc�...
//------------------------------------------------SORTING ALGORITHM(S)--------------------------------------------------//
S�ralama kriteri : S�ralama sonucu olu�mas� istenen d�zeni belirtir.
S�ralama Algoritmas� : S�ralaman�n yap�lmas� i�in hangi s�rayla hangi basamaklar�n ger�ekle�tirilece�ini a��klar.


Dikkat : S�ralama kriteri ve s�ralama algoritmas�ndan ba��ms�zd�r.
// s�ralama algoritmas� i�in nas�l yap�laca��n� tarif ediyor.
// s�ralama kriteri hangi ko�ullar alt�nda yapaca��n� s�yl�yor.

// baz� algoritmalar� ezbere bilmek mant�kl�.

// bubble sort,quick sort, insertion sort, selection sort, merge sort, shell sort...
//quick sort �ok kullan�l�yor.
//radix sort, index sort... �ok var.

S�ralama algoritmalar�n farkl� farkl� dezavantajlar� ve avantajlar� olabiliyor;
- Computational Complexity(��lem Karma��kl���) -> Best Case, Worst Case, Avg Case durumlar� var. 
- Memory Complexity(Bellek Alan� karma��kl���) -> �lave alana ihtiya� duyuyor mu duymuyor mu? (baz� algoritmalar duyuyor)

S�ralama algoritmas� Stable m� yoksa Unstable m�?


	a�a��daki elemanlar� s�ralarsak s�ralama kriterimiz -> isim
	isim    ya�
	ahmet	12
	hasan	24
	mehmet	55
	naci	47
	huseyin	34
	mehmet	30
	mehmet	21

	E�er key kendi aras�nda s�ralamas� de�i�irse bu unstable olur. mehmetlerin s�ralamalar� isme g�re olmas� gerekirken hem isim hem ya�a g�re olmu�.
	ahmet	12
	hasan	24
	huseyin	34
	mehmet	21
	mehmet	30
	mehmet	55
	naci	47

	E�er key(s�ralama kriteri) kendi aras�ndaki s�ralamalar� ayn� kal�rsa stable olur. Mehmetler bir araya gelse de s�ralama �ncesi s�ralamalar� ayn�.
	ahmet	12
	hasan	24
	huseyin	34
	mehmet	55
	mehmet	30
	mehmet	21
	naci	47



Kursun sonuna kadar bubble sort kullan�lacak. Anlat�m� ve yaz�m� kolay oldu�u i�in.*/
/*
#define SIZE 10
int main(void)
{
	int a[SIZE];
	randomize();
	set_array_random(a, SIZE);
	print_array(a, SIZE);

	for(int i = 0; i < SIZE - 1; ++i)
		for (int k = 0; k < SIZE - i - 1; k++) {
			if (a[k] < a[k + 1]) { // a[k] < a[k+1] olursa b�y�kten k����e -> a[k] > a[k+1] olur ise k���kten b�y��e olur.
								 // s�ralama kriterini if'in i�erisindeki expression sa�l�yor.
				int temp = a[k];
				a[k] = a[k + 1];
				a[k + 1] = temp;
			}
		}
	print_array(a, SIZE);

		
}*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//#define SIZE 100
/*int main(void)
{
	int a[SIZE];
	randomize();
	set_array_random(a, SIZE);
	print_array(a, SIZE);

	for (int i = 0; i < SIZE - 1; ++i)
		for (int k = 0; k < SIZE - i - 1; k++) {
			if (i) { // burada i yerine �yle bir �ey yaz�lmal� ki tekler en ba�ta kendi i�erisinde, �iftiler ise en sonda kendi i�erisinde
					// k���kten b�y��e s�ralanmal�.
				int temp = a[k];
				a[k] = a[k + 1];
				a[k + 1] = temp;
			}
		}
	print_array(a, SIZE);
	CEVAP
	* a[k] a[k+1]
	* 24	91 ->  Burada a[k] �ift k+1 ise tek. 
	* 24	11 -> burada sol �ift sa� tek fakat tek olan say� daha k���k oldu�u i�in de�i�meli
	* 45	13 -> tek ve tek ama sa�daki de�er daha d���k
	* 94	22 -> �ift ve �ift ama sa�daki de�er daha k���k	
	// a[k] �ift ve a[k+1] tek ise mutlaka takas yap�lmal�.
	// a[k] % 2 != 0 && a[k+1] % 2 == 0 . bu tekleri ba�a �iftleri sona al�r.��nk� her teki �ift ile yer de�i�tirir bu ifade.
	// sonraki ad�mda kendi i�lerinde de s�ral� olmas�n� sa�lamak gerekiyor.
	// a[k] % 2 != 0 && a[k+1] % 2 == 0 || (a[k] % 2 == a[k+1]%2) && a[k] > a[k+1]) 
	// || den sonr ayaz�lan ise hem bak�lan hemde bir sonraki eleman tek veya �ift ise ve bak�lan, bir sonrakinden b�y�kse demek.
	if ( a[k] % 2 == 0 && a[k + 1] % 2 != 0 || ( a[k] % 2 == a[k+1] % 2 ) && a[k] > a[k+1],   

	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1 - i; j++)
		{
			if (a[j] % 2 != 0 && a[j + 1] % 2 == 0 || (a[j] % 2 == a[j + 1] % 2) && (a[j] > a[j + 1]))
			{		// ilk ciftler, sonra da tekler s�ral� �ekilde yaz�ls�n. 
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	printf("tekler ve ciftler siralamasi\n");
	print_array(a, SIZE);
 }*/

// Bubble sort ile Quick sort kar��la�t�r�l�yor.

//bunlar sonra g�r�lecek

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/*#ifdef SIZE
#undef SIZE
#define SIZE 100000
#endif */


/*int icmp(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2;
}
int main(void)
{
	randomize();
	int* a = create_array(SIZE);
	set_array_random(a, SIZE);
	clock_t qsort_start = clock();
	qsort(a, SIZE, sizeof(int), &icmp); 	// bu fonksiyon leride g�r�lecek. stdlib.h d ge�en qsort .
	clock_t qsort_end = clock();

	clock_t start = clock();
	for(int i = 0; i < SIZE - 1; i++)
		for (int k = 0; k < SIZE - i - 1; k++) {
			if (a[k] < a[k + 1])
			{
				int temp = a[k];
				a[k] = a[k + 1];
				a[k + 1] = temp;
			}
		}
	clock_t end = clock();
	printf("Time elapsed Bubble Sort: %f\nTime Elapsed Q sort: %f", (double)(end - start) / CLOCKS_PER_SEC, (double)(qsort_end - qsort_start) / CLOCKS_PER_SEC);
	(void)getchar();
	//print_array(a, SIZE);
	free(a);	
}
*/
// Bubble sort algoritmas� y�ksek veri say�lar� i�in uygun bir algoritma de�il. 1 Milyon adet verinin bulundu�u bir diziyi sort etmek istersek
// sort edilme s�resi 16 dakika'ya yak�n s�recek.
// O(nlogn) karma��kl���nda y�ksek veride bubble sort(n^2) algoritmas�ndan daha etkilidir. qsort (standart k�t�phanede var) 
// 100k uzunlu�undaki bir dizideki s�ralama da qsort ve bubblesort aras�ndaki fark 
/* Time elapsed Bubble Sort: 3.507000
   Time Elapsed Q sort: 0.008000 */

 /////////////////////////////////////////////////////////////////////////////////////////////////////////

/* void t�r� baz� k�s�tlamalara ba�l� bir t�r;
- Bir de�i�kenin t�r� void olamaz. ( de�i�kenlerde kullan�lamayan t�rlere incomplete type denir)
- Bir dizinin t�r� void olamaz.
- Bir ifadenin t�r� void olabilir. -> ya void fonksiyona bir �a�r� yap�lacak ya da bir ifadeyi t�r d�n��t�rme operat�r�n�n operand� yap�p hedef t�r�
	void yapabiliriz. double dVal = 5.4; -> (void)dVal;
Neden VOID t�r�ne cast edeyim?
-  Baz� fonksiyonlar�n geri d�n�� de�eri olmas�na kar�� belirli bir nedenle fonksiyonu �a��r�p geri d�n�� de�erini discard etti�imiz durumlarda kullan�l�r.
- Derleyicilerin "warning(uyar�)" switchlerine ya da statik kod analizi yapan programlara ba�l� olarak geri d�n�� de�erini discard etti�imiz durumlarda
	ifadeyi void'e cast ediyoruz.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////

//�DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV
// maximum subsequence problem: Bir dizinin ard���k n tane ��esinin olu�turdu�u birim.
/*
	// a�a��daki dizi i�in max-subsequence de�erini hesaplayan bir kod yaz�n�z.
		-Olu�turdu�unuz algoritman�n karma��kl��� ne?, o(n2) ise nas�l o(n) olabilir onu d���n
	// seed degeri 14012021. Algoritma karma��kl��� best case O(n)
	// O(n2) de kabul.
	
	test kodu:
	#include <nUtility.h>
	#include <stdio.h>
	int main(void){
		int a[SIZE] = {-477, 550, -747, 759, 96, -322, 380, -238, 909, 134, -355, -500, 707, 131, 626, -81, 661, 877, -767, -902, 267,
		325, 10, 403, -174, -901, 928, 639, 560, 207, -507, -380, -217, 63, 407, 304, 747, 20, -535, 613, -447, -515, 262, 418, -390,
		731, -582, -688, 273, -178, -133, 685, 617, 207, 467, -877, -416, -390, -805, 324, -454, 928, -733, -93, -77, -912, 375, 230,
		845, -231, -517, -130, -657, 952, -740, 237, -359, 29, -806, -611, 764, -264, 70, -282, 214, -979, -903, 236, -865, -473,
		-525, -966, -371, -810, 385, -955, -56, 243, -194, -650,};
	}

//�DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV �DEV
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef SIZE
#define SIZE 100
#endif
int main(void)
{
	int a[100];
	randomize();
	set_array_random(a, SIZE);
	sort_array(a, SIZE);
	print_array(a, SIZE);
	int key;
	printf("Aranacak deger giriniz: ");
	(void)scanf("%d", &key);
	
	int index_first = 0;
	int index_last = SIZE - 1;
	int index_mid;
	int counter = 0;
	while (index_first < index_last)
	{
		++counter;
		index_mid = (index_first + index_last)/2;
		if (a[index_mid] == key)
			break;
		if (a[index_mid] > key)
			index_last = index_mid - 1;
		else
			index_first = index_mid + 1; 
	}
	if (index_first < index_last) // idx first, last� ge�erse olmad��� anla��l�r.
		printf("Aranan deger bulundu, dizinin %d indisli elemani\n", index_mid);
	else
		printf("Bulunamadi... Sorgulama Sayisi : %d", counter);
}
/* BINARY SEARCH ALGORITMASI;
- �lk �nce dizinin en ortadaki de�erine gidilir ve arad���m�z de�erden b�y�k veya k���k m� diye bak�l�r bu i�lem istenilen de�eri bulana kadar devam eder.
Binary search algoritmas� i�in dizi hali haz�rda sort edilmi� olmas� gerek.
BINARY SEARCH COMPLEXITY -> O(nlogn)


Partial Sort: Dizinin tamam� de�il ilk N tane eleman�n s�ralanmas�na verilen isim.

Partition(O(n)): Partisyon algoritmas�n� kodlay�n�z. �DEV �DEV �DEV �DEV �DEV �DEV -> Bir dizideki tek say�lar� dizinin ba��na, �iftleri sona al�n

nth element algoritmas� : n'inci eleman s�ralanm�� gibi yerinde duracak ondan �nceki elemanlar ondan k���k, ondan sonrakiler b�y�k olacak.



n. eleman 12 olsun.
1 2 3 5 6 7 12 45 11 10 39 55 41

1 2 3 5 6 7 10 11 12 39 41 45 55 -> bu �ekilde olur

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////


/*---------------------------------------------------C D�L�NDE YAZILAR----------------------------------------------*/
/*

Yaz� karakterlerden olu�an bir k�me. �rne�in u g u r  e r s o y
Her harfin bir tam say� kar��l��� var.
 B	A  B  A
66 65 66 65
Yaz�y� tutmak i�in bir bellek ad�na ihtiyac�mz� var fakat bu dizinin boyutu ne olacak?
Bir char dizisinde tutmak gerek fakat bu seferde uzunlu�u bilme sorunumuz var.
Bunun i�inde dizinin uzunlu�u ayr� bir de�i�kende tutabiliriz.
int len = 10;
char[len] = "UGUR ERSOY";

NTBS = Null Terminated Byte Stream
'\0' -> yaz�n�n bitti�ini belirten �zel karakter. NULL CHARACTER denir.
Tam say� de�eri 0 olan karakterdir.
'\0' ile 0 aras�nda bir fark yok. '\0' �eklinde yazarsak karakterle ilgili bir i� yapt���m�z� anlayabiliriz.

'0' != '\0' -> '0' 0 rakam�n�n karakter kodu iken '\0' null karakterinin kodudur ve AYNI DE��LD�R.
*/

#define SIZE 100

int main(void)
{
	char str[SIZE] = "UGUR"; // Bu yaz�n�n uzunlu�u en k���k 0, en fazla ise SIZE - 1 olur.
					// ilk karakter str[0] = '\0'; olur ise uzunlu�u 0 olur. SIZE olmaz ��nk� son element '\0' olaca��ndan dolay� maks uzunluk SIZE - 1 olur.
	int i = 0;
	while (str[i] != '\0') {
		i++;
		printf("%c", str[i]);
		// veya putchar(str[i]) kullan�labilir.
	}
	// while (str[i] != '\0') bunun ile while (str[i] != 0) aras�nda fark yok. Fark while (str[i] != '\0') ile str[i] != '0' aras�nda.
		
	// sadece while(str[i])'de yaz�labilir. Lojik yorumlamadan dolay�. Ne zaman str[i] null karakterine gelir o zaman d�ng� ifadesi 0 olaca��
	// i�in d�ng�den hi�bir UB veya hata olmadan ��k�l�r. LEGAL!
	for (int i = 0; str[i]; i++); // LEGAL!
	while (str[i] != 0); // LEGAL, for ile de olur.
	while (str[i] != '0'); // LEGAL DE��L, 
	
	puts(str); // �DEV �DEV �DEV ARRAY DECAYI TAM OLARAK �ALI� 

	// Yaz�n�n sonunda '\0' karakteri oldu�una g�venilerek i�lemler yap�l�r.
	// Yaz�n�n sonunda null karakteri olmayan ve UB olu�turan durumlar;
	char str2[10];
	str2[0] = 'A';
	str2[1] = 'L';
	str2[3] = 'P';
	for (int i = 0; str2[i] != '\0'; i++) // diziye null karakterini eklemedi�imiz i�in UB var burada.
		printf("%s", str2[i]);
	// E�er str2'yi global veya statik olarak tan�mlar isek ilk de�er vermedi�imiz zaman otomatik olarak 0 atand��� i�in UB olu�maz.

}






