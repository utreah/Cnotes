#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "C:\Users\UGUR\Documents\GitHub\Cnotes\nUtility.h"
int secondary_main(void);
// buradaki senaryo �u.
	// x ��rencinin y dersini tutacak bir dizi olu�turmam�z gerekiyor. Fakat ka� ��renci ve ders oldu�unu bilmedi�imiz i�in dinamik olarak olu�turuyoruz.
int main(void) {
	int row;
	int col;
	printf("Ogrenci sayisini giriniz: ");
	(void)scanf("%d%d", &row,&col);
	int** pd = (int**)malloc(row * sizeof(int**)); // burada int** t�r�nde olu�turmam�z�n sebebi ise pointer to pointer to int bir de�i�ken olu�turmak.
																	// �ok boyutlu dizilerdeki mant�kla ayn�. O adresde ��rencilerin derslerinin notlar�n�n oldu�u y adet diziler
																		// olu�turulacak. int studentArr[number_of_students][number_of_classes] <- g�r�n�m� b�yle olacak asl�nda
	if (!pd)
	{
		return 0;
	}
	// �nce x kadar ��renci say�s�na sahip bir 'pointer dizisi' allocate ettik. �imdi ise o pointer dizilerini derefence edip int dizimizi olu�turaca��z.
	
	for (int i = 0; i < row; i++)
	{
		pd[i] = (int*)malloc(col * sizeof(int)); // number of students * int b�y�kl���nde int dizileri olu�turulacak ve pd[i] ile pointer dizisine atanacak.
		if (!pd[i])
			return 0;
	}
	// �ok boyutlu diziyi olu�tururken �nce pointer dizisi sonra int dizisini allocate ettik.
		// Free ederken tam tersi olacak. �nce int dizileri sonra pointer dizileri free edece�iz. Bunun sebebi ise dangling pointer durumuyla kar��la�mamak i�in.
			// E�er, �nce pointer dizileri free edersek int dizilerin adres(ler)ine eri�imimiz olmayaca�� i�in onlar� asla free edemeyece�iz. 
				// Bu da 'memory leak' asl�na bakt���m�z zaman. Program�n sonuna kadar hayatta kalacak bu dizi(ler)
	randomize();
	for (size_t i = 0; i < row; i++)
		for (size_t k = 0; k < col; k++)
			pd[i][k] = rand() % 10;
	for (int i = 0; i < row; i++)
		for (int k = 0; k < col; k++)
			printf("number_of_students[%d][%d] = %d\n", i, k+1, pd[i][k]);

/*
	// NOT olu�turdu�umuz iki dizinin ard���k olma garantisi yok.
		// statik olarak olu�turulmu� dizilerde evet b�yle bir garanti var fakat, pointer dizisinin i�erisine adresini verdi�imiz int dizilerinin ard���k olma garantisi yok.
			// �ok anlams�z bir not oldu ��yle a��klayay�m.

		// pd++ yapt���m�zda s�ral� olma garantisi var. Bundan yana s�k�nt� yok.
		// *pd++ as�l s�k�nt� burada. Normalde ayn� bellek �zerinde olu�turuldu�unda contigous oldu�undan dolay� ard���k olma garantisi var FAKAT
			// burada olu�turulan diziler pointer dizisinin i�erisinde olu�turuldu�u i�in, son elemana geldikten sonra devam edersek bu tan�ms�z davran��.

	int t = row * col;

	while (t--) {
		printf("%2d", *pd++); // Burada g�r�lece�i �zere pd[i] dizisinin g�sterdi�i int dizisinin son eleman�na gelindi�inde sa�malamaya ba�layacak.
		getch();
	}
*/


	// olu�turdu�umuz �ok boyutlu dizi ile i�imiz bitti �imdi free() zaman�


	for (size_t i = 0; i < row; i++)
	{
		free(pd[i]); // �nce pd pointer dizisinin i�eri�indeki adresleri deallocate ediyoruz.
	}
	free(pd); // en son pointer dizisini deallocate ediyoruz.

	// Yukar�da yapt�klar�m�z�n ayn�s� tek bir dizi ile yapaca��z �imdi. Yani row * col * sizeof(int) boyutlu
		// tek bir bellek blo�unu allocate edicez. Ve bu sayede contigous(s�ral�) olma garantisi var art�k dizimizin.

	int* pd2 = (int*)malloc(row * col * sizeof(int));

	if (!pd2) {
		return 0;
	}
	for (size_t i = 0; i < row; i++)
		for (size_t k = 0; k < col; k++)
			pd2[i * col + k] = rand() % 10;
	for (int i = 0; i < row; i++)
		for (int k = 0; k < col; k++)
			printf("number_of_students2[%d][%d] = %d\n", i, k, pd2[i * col + k]);

	free(pd2);

	////////////////////////////////////////////////
	/*
	 Farklar�
	 -�lk dizinin maliyeti daha �ok. Fonksiyonlar� birden fazla kullanmam�z haricinde de, her allocate edilen bellek blo�u 'header' k�sm�nda 
		allocate bilgilerini vs saklar. Bu da ekstra alan demek. �lkinde 2 adet bellek blo�u allocate etti�imiz i�inde bu miktar normal x2
	 -�lk dizi contigous de�il iken ikinci dizi contigous.
	 -Birinci arr[i][k] notasyonuna uyuyor, ikinci �ekilde bu kullan�lamaz.
	 -Birincinin di�er avantaj� ise, fragmentation(fragmentasyon-par�alanma) kavram� var. �ok kavrayamad�m ama anlad���m kadar�yla
		programlar HEAP'te bellek bloklar�nda farkl� yerlerde olabiliyor. Kimisinin erkenden free edilmesinden dolay�.
		Diyelim ki 20KB'lik bir bellek alan�m�z var ve bunun 14 kbsi kullan�mda. Ben 5KB'lik bir alan allocate etmeye �al��t���mda garanti yok. ��nk� dizinin
			s�ral� olma garantisinden dolay�. HEAP'te par�a par�a bulundu�u i�inde b�yle bir zorluk ��k�yor kar��m�za.
		Birincinin avantaj� burada geliyor asl�nda. Allocate ederken row i�in x * sizeof(int), col i�in y * sizeof(int) boyutunda iki farkl� allocation yap�l�yor. 
		�kincisin de ise row * col * sizeof(int) tek 1 adet ard���k dizi allocate edilmeye �al���l�yor. �rne�in, 1000 row 1000 col olan bir dizi i�in 4 milyon byte'l�k
			contigous �ekilde allocate edebilece�imiz alana ihtiyac�m�z var. Bu da s�k�nt�l� bir durum ba� a�r�tabilir.
	*/
	// Yukar�da yapt���m�z ilk �rnek contigous de�ildi. �imdi ise ayn� �rne�i contigous yap�cam

	int** pp = (int**)malloc(row * sizeof(int*));
	if (!pp)
		return 0;

	int* intd = (int*)malloc(col * sizeof(int));
	if (!intd)
		return 0;

	for (int i = 0; i < row; ++i) {
		pp[i] = intd + i * col; // �ok g�zel, �iir gibi. Bir diziyi parampar�a ediyoruz ve her par�an�n adresini pointer dizimize at�yoruz. 
	}
	free(intd);
	free(pp);

}


/*
Heap Alan�n�n Fragmantation Durumu
	Heap ten �ok fazla alan al�nd���nda, ard���k olarak 50.000 byte olmayabilir
	ama 50.000 byte toplamda yer olabilir.burada alan fragmante oluyor.

	Sisteme yer verilene kadar, o alan� ba�ka birinin kullanmas� m�mk�n de�il.
	bu geri verme i�lemine free ya da deallocate deniyor.

	free edilmezse memory, memory leak olu�uyor.Yani bellek s�z�nt�s�.
	bu olu�ursa memory de i�i yapabilmek i�in yer kalm�yor art�k.

	Program�n i�i bitti kapand� ama al�nm�� alanlar� free etmedik diyelim.
	Program tekrar �al���rsa o bellek alanlar� sanki hi� al�nmam�� gibi 0 km olarak
	bize ait ve kullan�labilir.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void* realloc(void* vp, size_t newsize) fonksiyonun bildirimi
/*
-Hem b�y�tme hem k���ltme amac� ile kullan�labiliyor.
-Geri d�n�� de�eri void*
-Parametreleri;
	void* vp -> daha �nceden allocate edilmi� bellek blo�unun adresi
	size_t newsize -> ��lem sonras� elde edilmek istenilen belle�in BYTE boyutu. Diyelim ki 5000 Bytel�k bir bellek blo�umuz var ve onu 6000 yapmak istiyoruz.
		newsize parametresine 1000 de�il 6000 g�ndermemiz gerek. 2000e d���rmek isteseydikte 3000 de�il 2000 yazacakt�k.

-realloc i�in 3 senaryo var;
	-G�nderdi�imiz bellek blo�unu b�y�t�r, ayn� adresi geri d�nd�r�r.
	-G�nderdi�imiz bellek blo�unu b�y�temez ya da hi� kontrol bile etmez, istenilen boyutta bir bellek blo�u allocate eder ve onun adresini d�nd�r�r(i�eri�i kopyalar)
		E�er, bunun i�in bir �nlem al�nmad�ysa eski bellek blo�u dangling pointer olaca�� i�in probleme yol a�m�� olur.
	-B�y�tme i�lemi ba�ar�s�z olabilir. Fakat, bu g�nderdi�imiz bellek blo�unu da kaybedece�imiz anlam�na gelmiyor. Sadece artt�rma/azaltma i�leminde sorun oldu�u anlam�na geliyor.

*/

int secondary_main(void) {
	int num;
	printf("kac tam sayi: ");	
	(void)scanf("%d", &num);

	int* pd = (int*)malloc(num * sizeof(int));

	if (!pd)
		return 0;
	printf("malloc ile elde edilen adres : %p\n", pd);
	randomize();
	set_array_random(pd, num);
	print_array(pd, num);

	// �imdi yeni bir bellek blo�u allocate edecez
	int numplus;
	printf("kac tam sayi eklenecek: ");
	(void)scanf("%d", &numplus);
	
	pd = (int*) realloc(pd, (num + numplus) * sizeof(int)); // byte olarak istedi�i i�in sizeof(type) ile �arp�yoruz. num+numplus olma sebebi ise istenilen YEN� boyutu yaz�yoruz.
	// C6308 Uyar�s�n� d�zeltmek etmek i�in, direkt pd'ye atamak yerine �nce ge�ici bir de�i�kene atay�p NULL kontrol� yap�p �yle pdye atarak ��z�lebilir.
	/*
		int* pdTemp = (int*)realloc(pd, (num + numplus) * sizeof(int));
		if(pdTemp)
			pd = pdTemp;
	*/

	printf("realloc ile elde edilen adres : %p\n", pd);
	if (!pd)
		return 0;
	// Peki, yeni allocate etti�imiz bu bellek blo�una veri yazma i�ini nas�l yap�caz?
		// Tabiiki de, dizimizin bitti�i yerden ba�layarak. Bunu da pd + num ile yap�caz.

	set_array_random(pd + num, numplus); // pd + num yazarak, ilk bellek blo�unun bitti�i yerden ba�layarak numplus kadar de�er yazd�k.
	print_array(pd, num + numplus);
	free(pd);
	return 1;
}


/*
- Reallocation TAKES TIME! -> Realloc zaman alan ve maliyetli bir fonksiyon. O y�zden kullanma zorunlulu�umuz olmayan, boyutunu �nceden bildi�imiz i�lemlerde ka��nmal�y�z.
	int ch;
	int val;
	int counter = 1;
	int* pd = NULL;
	randomize();
	// E�er realloc'a NULL adres olarak g�nderilir ise, realloc malloc gibi i� yap�yor.
	for(;;){
		printf("tam sayi girecek misiniz? (e / h) : ");
		while((ch = getch()) != 'e' && ch != 'h');
		printf("\n%c\n", ch);
		if(ch == h)
			break;
		val = rand() % 100;
		printf("%d\n", val);
		pd = (int*)realloc(pd, counter * sizeof(int);
		if(!pd)
			return 0;

		pd[cnt] = val;
		counter++;
	}
	free(pd);

- Reallocation invalidates pointers! -> invalid hale gelen pointer dangling pointer olacak, ya da dangling pointer olma �ans� var.

*/
///////////////////////////////////////////////////////////////////////////////////////

/*                                                                   Dynamic Array             */
/*
Mant�ksal ili�kideki veriler, herzaman memoryde tutuluyorlar.
Bu verilerin memory de nas�l tutulaca�� bilgisine data structure deniyor.

dynamic array
linked list
- singly linked list
- doubly linked list
- rotating linked list
trees
binary search tree
hash tables
hash - maps
hash - set

yurtd��� m�lakatlarda �ok �nemli.

Bunlardan en �nemlisi halen daha dynamic array.��nk� % 70 bu kullan�l�yor.
C++ ta bunu y�neten s�n�fa vector deniyor.

Avantaj� index bilgisiyle verilere eri�ebiliyoruz.

Bu t�r dizilere sondan eleman eklemek constant time O(1) karma��kl���nda.
Araya eleman ekleme ise O(n) karma��kl���nda ��nk� kayd�rma yapmak gerekiyor.

bizim �nceki kodda constant time de�il �nk� her d�ng�de realloc �a�r�l�yor.
habire bellek kopyalan�yor biryerden ba�ka bir yere.

dinamik dizide bunun O(1) karma��kl���nda olabilmesinin sebebi birer birer allocate etmiyor.
bir seferde % 50 fazlas�n� allocate edip ona g�re i�lem yap�yor.
eleman yaz�ld���nda ise tekrar b�y�tmeye ihtiya� kalm�yor.

Yani
dizi boyutu Capacity
dizideki eleman say�s� Size

capacity s�rekli size dan �ok daha b�y�k tutuluyor.size, capacity ye e�it olana kadar realloc yok.

size = 19 capacity = 20
size = 20 capacity = 20
reallocation
size 21 capacity 40
...

bu �ekilde gider.Olay� s�rekli realloc yapmamak.fazla art�r�yorki habire yapmas�n diye.
reallocta baya maliyetli ��nk�.dinamik dizi veri yap�s�nda amortised constant time diye ge�iyor.

KEND� DYNAMIC ARRAY KODUNU YAZDI HOCA, BEN YAZMIYORUM. 1.30

Caching de programlamada �ok �nemli bir mekanizma.cpu cache memory ye g�re �ok daha h�zl�.
eri�ilmek istenen nesne cache de ise buna cache hit deniyor.Cache hit oran� dinamik dizide
daha y�ksek olmas� sebebiyle de tercih ediliyor.

cache hitin tersi cache miss.

c++ ta cache mekanizmas� haz�r.C de yok : D
kendimiz yazaca��z.

*/

