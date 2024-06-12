#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdlib.h>
#include <stdio.h>

/*reverse için->öðe sayýsýnýn yarýsý kadar dönen döngü.baþtan birinci sondan birinci, ikinciye ikinci, üçüncüye üçüncü...
//------------------------------------------------SORTING ALGORITHM(S)--------------------------------------------------//
Sýralama kriteri : Sýralama sonucu oluþmasý istenen düzeni belirtir.
Sýralama Algoritmasý : Sýralamanýn yapýlmasý için hangi sýrayla hangi basamaklarýn gerçekleþtirileceðini açýklar.


Dikkat : Sýralama kriteri ve sýralama algoritmasýndan baðýmsýzdýr.
// sýralama algoritmasý iþin nasýl yapýlacaðýný tarif ediyor.
// sýralama kriteri hangi koþullar altýnda yapacaðýný söylüyor.

// bazý algoritmalarý ezbere bilmek mantýklý.

// bubble sort,quick sort, insertion sort, selection sort, merge sort, shell sort...
//quick sort çok kullanýlýyor.
//radix sort, index sort... çok var.

Sýralama algoritmalarýn farklý farklý dezavantajlarý ve avantajlarý olabiliyor;
- Computational Complexity(Ýþlem Karmaþýklýðý) -> Best Case, Worst Case, Avg Case durumlarý var. 
- Memory Complexity(Bellek Alaný karmaþýklýðý) -> Ýlave alana ihtiyaç duyuyor mu duymuyor mu? (bazý algoritmalar duyuyor)

Sýralama algoritmasý Stable mý yoksa Unstable mý?


	aþaðýdaki elemanlarý sýralarsak sýralama kriterimiz -> isim
	isim    yaþ
	ahmet	12
	hasan	24
	mehmet	55
	naci	47
	huseyin	34
	mehmet	30
	mehmet	21

	Eðer key kendi arasýnda sýralamasý deðiþirse bu unstable olur. mehmetlerin sýralamalarý isme göre olmasý gerekirken hem isim hem yaþa göre olmuþ.
	ahmet	12
	hasan	24
	huseyin	34
	mehmet	21
	mehmet	30
	mehmet	55
	naci	47

	Eðer key(sýralama kriteri) kendi arasýndaki sýralamalarý ayný kalýrsa stable olur. Mehmetler bir araya gelse de sýralama öncesi sýralamalarý ayný.
	ahmet	12
	hasan	24
	huseyin	34
	mehmet	55
	mehmet	30
	mehmet	21
	naci	47



Kursun sonuna kadar bubble sort kullanýlacak. Anlatýmý ve yazýmý kolay olduðu için.*/
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
			if (a[k] < a[k + 1]) { // a[k] < a[k+1] olursa büyükten küçüðe -> a[k] > a[k+1] olur ise küçükten büyüðe olur.
								 // sýralama kriterini if'in içerisindeki expression saðlýyor.
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
			if (i) { // burada i yerine öyle bir þey yazýlmalý ki tekler en baþta kendi içerisinde, çiftiler ise en sonda kendi içerisinde
					// küçükten büyüðe sýralanmalý.
				int temp = a[k];
				a[k] = a[k + 1];
				a[k + 1] = temp;
			}
		}
	print_array(a, SIZE);
	CEVAP
	* a[k] a[k+1]
	* 24	91 ->  Burada a[k] çift k+1 ise tek. 
	* 24	11 -> burada sol çift sað tek fakat tek olan sayý daha küçük olduðu için deðiþmeli
	* 45	13 -> tek ve tek ama saðdaki deðer daha düþük
	* 94	22 -> çift ve çift ama saðdaki deðer daha küçük	
	// a[k] çift ve a[k+1] tek ise mutlaka takas yapýlmalý.
	// a[k] % 2 != 0 && a[k+1] % 2 == 0 . bu tekleri baþa çiftleri sona alýr.çünkü her teki çift ile yer deðiþtirir bu ifade.
	// sonraki adýmda kendi içlerinde de sýralý olmasýný saðlamak gerekiyor.
	// a[k] % 2 != 0 && a[k+1] % 2 == 0 || (a[k] % 2 == a[k+1]%2) && a[k] > a[k+1]) 
	// || den sonr ayazýlan ise hem bakýlan hemde bir sonraki eleman tek veya çift ise ve bakýlan, bir sonrakinden büyükse demek.
	if ( a[k] % 2 == 0 && a[k + 1] % 2 != 0 || ( a[k] % 2 == a[k+1] % 2 ) && a[k] > a[k+1],   

	for (int i = 0; i < SIZE - 1; i++)
	{
		for (int j = 0; j < SIZE - 1 - i; j++)
		{
			if (a[j] % 2 != 0 && a[j + 1] % 2 == 0 || (a[j] % 2 == a[j + 1] % 2) && (a[j] > a[j + 1]))
			{		// ilk ciftler, sonra da tekler sýralý þekilde yazýlsýn. 
				int temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
	printf("tekler ve ciftler siralamasi\n");
	print_array(a, SIZE);
 }*/

// Bubble sort ile Quick sort karþýlaþtýrýlýyor.

//bunlar sonra görülecek

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
	qsort(a, SIZE, sizeof(int), &icmp); 	// bu fonksiyon leride görülecek. stdlib.h d geçen qsort .
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
// Bubble sort algoritmasý yüksek veri sayýlarý için uygun bir algoritma deðil. 1 Milyon adet verinin bulunduðu bir diziyi sort etmek istersek
// sort edilme süresi 16 dakika'ya yakýn sürecek.
// O(nlogn) karmaþýklýðýnda yüksek veride bubble sort(n^2) algoritmasýndan daha etkilidir. qsort (standart kütüphanede var) 
// 100k uzunluðundaki bir dizideki sýralama da qsort ve bubblesort arasýndaki fark 
/* Time elapsed Bubble Sort: 3.507000
   Time Elapsed Q sort: 0.008000 */

 /////////////////////////////////////////////////////////////////////////////////////////////////////////

/* void türü bazý kýsýtlamalara baðlý bir tür;
- Bir deðiþkenin türü void olamaz. ( deðiþkenlerde kullanýlamayan türlere incomplete type denir)
- Bir dizinin türü void olamaz.
- Bir ifadenin türü void olabilir. -> ya void fonksiyona bir çaðrý yapýlacak ya da bir ifadeyi tür dönüþtürme operatörünün operandý yapýp hedef türü
	void yapabiliriz. double dVal = 5.4; -> (void)dVal;
Neden VOID türüne cast edeyim?
-  Bazý fonksiyonlarýn geri dönüþ deðeri olmasýna karþý belirli bir nedenle fonksiyonu çaðýrýp geri dönüþ deðerini discard ettiðimiz durumlarda kullanýlýr.
- Derleyicilerin "warning(uyarý)" switchlerine ya da statik kod analizi yapan programlara baðlý olarak geri dönüþ deðerini discard ettiðimiz durumlarda
	ifadeyi void'e cast ediyoruz.
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////

//ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV
// maximum subsequence problem: Bir dizinin ardýþýk n tane öðesinin oluþturduðu birim.
/*
	// aþaðýdaki dizi için max-subsequence deðerini hesaplayan bir kod yazýnýz.
		-Oluþturduðunuz algoritmanýn karmaþýklýðý ne?, o(n2) ise nasýl o(n) olabilir onu düþün
	// seed degeri 14012021. Algoritma karmaþýklýðý best case O(n)
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

//ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV
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
	if (index_first < index_last) // idx first, lastý geçerse olmadýðý anlaþýlýr.
		printf("Aranan deger bulundu, dizinin %d indisli elemani\n", index_mid);
	else
		printf("Bulunamadi... Sorgulama Sayisi : %d", counter);
}
/* BINARY SEARCH ALGORITMASI;
- Ýlk önce dizinin en ortadaki deðerine gidilir ve aradýðýmýz deðerden büyük veya küçük mü diye bakýlýr bu iþlem istenilen deðeri bulana kadar devam eder.
Binary search algoritmasý için dizi hali hazýrda sort edilmiþ olmasý gerek.
BINARY SEARCH COMPLEXITY -> O(nlogn)


Partial Sort: Dizinin tamamý deðil ilk N tane elemanýn sýralanmasýna verilen isim.

Partition(O(n)): Partisyon algoritmasýný kodlayýnýz. ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV ÖDEV -> Bir dizideki tek sayýlarý dizinin baþýna, çiftleri sona alýn

nth element algoritmasý : n'inci eleman sýralanmýþ gibi yerinde duracak ondan önceki elemanlar ondan küçük, ondan sonrakiler büyük olacak.



n. eleman 12 olsun.
1 2 3 5 6 7 12 45 11 10 39 55 41

1 2 3 5 6 7 10 11 12 39 41 45 55 -> bu þekilde olur

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////


/*---------------------------------------------------C DÝLÝNDE YAZILAR----------------------------------------------*/
/*

Yazý karakterlerden oluþan bir küme. Örneðin u g u r  e r s o y
Her harfin bir tam sayý karþýlýðý var.
 B	A  B  A
66 65 66 65
Yazýyý tutmak için bir bellek adýna ihtiyacýmzý var fakat bu dizinin boyutu ne olacak?
Bir char dizisinde tutmak gerek fakat bu seferde uzunluðu bilme sorunumuz var.
Bunun içinde dizinin uzunluðu ayrý bir deðiþkende tutabiliriz.
int len = 10;
char[len] = "UGUR ERSOY";

NTBS = Null Terminated Byte Stream
'\0' -> yazýnýn bittiðini belirten özel karakter. NULL CHARACTER denir.
Tam sayý deðeri 0 olan karakterdir.
'\0' ile 0 arasýnda bir fark yok. '\0' þeklinde yazarsak karakterle ilgili bir iþ yaptýðýmýzý anlayabiliriz.

'0' != '\0' -> '0' 0 rakamýnýn karakter kodu iken '\0' null karakterinin kodudur ve AYNI DEÐÝLDÝR.
*/

#define SIZE 100

int main(void)
{
	char str[SIZE] = "UGUR"; // Bu yazýnýn uzunluðu en küçük 0, en fazla ise SIZE - 1 olur.
					// ilk karakter str[0] = '\0'; olur ise uzunluðu 0 olur. SIZE olmaz çünkü son element '\0' olacaðýndan dolayý maks uzunluk SIZE - 1 olur.
	int i = 0;
	while (str[i] != '\0') {
		i++;
		printf("%c", str[i]);
		// veya putchar(str[i]) kullanýlabilir.
	}
	// while (str[i] != '\0') bunun ile while (str[i] != 0) arasýnda fark yok. Fark while (str[i] != '\0') ile str[i] != '0' arasýnda.
		
	// sadece while(str[i])'de yazýlabilir. Lojik yorumlamadan dolayý. Ne zaman str[i] null karakterine gelir o zaman döngü ifadesi 0 olacaðý
	// için döngüden hiçbir UB veya hata olmadan çýkýlýr. LEGAL!
	for (int i = 0; str[i]; i++); // LEGAL!
	while (str[i] != 0); // LEGAL, for ile de olur.
	while (str[i] != '0'); // LEGAL DEÐÝL, 
	
	puts(str); // ÖDEV ÖDEV ÖDEV ARRAY DECAYI TAM OLARAK ÇALIÞ 

	// Yazýnýn sonunda '\0' karakteri olduðuna güvenilerek iþlemler yapýlýr.
	// Yazýnýn sonunda null karakteri olmayan ve UB oluþturan durumlar;
	char str2[10];
	str2[0] = 'A';
	str2[1] = 'L';
	str2[3] = 'P';
	for (int i = 0; str2[i] != '\0'; i++) // diziye null karakterini eklemediðimiz için UB var burada.
		printf("%s", str2[i]);
	// Eðer str2'yi global veya statik olarak tanýmlar isek ilk deðer vermediðimiz zaman otomatik olarak 0 atandýðý için UB oluþmaz.

}






