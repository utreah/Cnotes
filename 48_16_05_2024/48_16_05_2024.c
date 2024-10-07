#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "C:\Users\UGUR\Documents\GitHub\Cnotes\nUtility.h"
int secondary_main(void);
// buradaki senaryo þu.
	// x öðrencinin y dersini tutacak bir dizi oluþturmamýz gerekiyor. Fakat kaç öðrenci ve ders olduðunu bilmediðimiz için dinamik olarak oluþturuyoruz.
int main(void) {
	int row;
	int col;
	printf("Ogrenci sayisini giriniz: ");
	(void)scanf("%d%d", &row,&col);
	int** pd = (int**)malloc(row * sizeof(int**)); // burada int** türünde oluþturmamýzýn sebebi ise pointer to pointer to int bir deðiþken oluþturmak.
																	// çok boyutlu dizilerdeki mantýkla ayný. O adresde öðrencilerin derslerinin notlarýnýn olduðu y adet diziler
																		// oluþturulacak. int studentArr[number_of_students][number_of_classes] <- görünümü böyle olacak aslýnda
	if (!pd)
	{
		return 0;
	}
	// önce x kadar öðrenci sayýsýna sahip bir 'pointer dizisi' allocate ettik. Þimdi ise o pointer dizilerini derefence edip int dizimizi oluþturacaðýz.
	
	for (int i = 0; i < row; i++)
	{
		pd[i] = (int*)malloc(col * sizeof(int)); // number of students * int büyüklüðünde int dizileri oluþturulacak ve pd[i] ile pointer dizisine atanacak.
		if (!pd[i])
			return 0;
	}
	// Çok boyutlu diziyi oluþtururken önce pointer dizisi sonra int dizisini allocate ettik.
		// Free ederken tam tersi olacak. Önce int dizileri sonra pointer dizileri free edeceðiz. Bunun sebebi ise dangling pointer durumuyla karþýlaþmamak için.
			// Eðer, önce pointer dizileri free edersek int dizilerin adres(ler)ine eriþimimiz olmayacaðý için onlarý asla free edemeyeceðiz. 
				// Bu da 'memory leak' aslýna baktýðýmýz zaman. Programýn sonuna kadar hayatta kalacak bu dizi(ler)
	randomize();
	for (size_t i = 0; i < row; i++)
		for (size_t k = 0; k < col; k++)
			pd[i][k] = rand() % 10;
	for (int i = 0; i < row; i++)
		for (int k = 0; k < col; k++)
			printf("number_of_students[%d][%d] = %d\n", i, k+1, pd[i][k]);

/*
	// NOT oluþturduðumuz iki dizinin ardýþýk olma garantisi yok.
		// statik olarak oluþturulmuþ dizilerde evet böyle bir garanti var fakat, pointer dizisinin içerisine adresini verdiðimiz int dizilerinin ardýþýk olma garantisi yok.
			// çok anlamsýz bir not oldu þöyle açýklayayým.

		// pd++ yaptýðýmýzda sýralý olma garantisi var. Bundan yana sýkýntý yok.
		// *pd++ asýl sýkýntý burada. Normalde ayný bellek üzerinde oluþturulduðunda contigous olduðundan dolayý ardýþýk olma garantisi var FAKAT
			// burada oluþturulan diziler pointer dizisinin içerisinde oluþturulduðu için, son elemana geldikten sonra devam edersek bu tanýmsýz davranýþ.

	int t = row * col;

	while (t--) {
		printf("%2d", *pd++); // Burada görüleceði üzere pd[i] dizisinin gösterdiði int dizisinin son elemanýna gelindiðinde saçmalamaya baþlayacak.
		getch();
	}
*/


	// oluþturduðumuz çok boyutlu dizi ile iþimiz bitti þimdi free() zamaný


	for (size_t i = 0; i < row; i++)
	{
		free(pd[i]); // önce pd pointer dizisinin içeriðindeki adresleri deallocate ediyoruz.
	}
	free(pd); // en son pointer dizisini deallocate ediyoruz.

	// Yukarýda yaptýklarýmýzýn aynýsý tek bir dizi ile yapacaðýz þimdi. Yani row * col * sizeof(int) boyutlu
		// tek bir bellek bloðunu allocate edicez. Ve bu sayede contigous(sýralý) olma garantisi var artýk dizimizin.

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
	 Farklarý
	 -Ýlk dizinin maliyeti daha çok. Fonksiyonlarý birden fazla kullanmamýz haricinde de, her allocate edilen bellek bloðu 'header' kýsmýnda 
		allocate bilgilerini vs saklar. Bu da ekstra alan demek. Ýlkinde 2 adet bellek bloðu allocate ettiðimiz içinde bu miktar normal x2
	 -Ýlk dizi contigous deðil iken ikinci dizi contigous.
	 -Birinci arr[i][k] notasyonuna uyuyor, ikinci þekilde bu kullanýlamaz.
	 -Birincinin diðer avantajý ise, fragmentation(fragmentasyon-parçalanma) kavramý var. Çok kavrayamadým ama anladýðým kadarýyla
		programlar HEAP'te bellek bloklarýnda farklý yerlerde olabiliyor. Kimisinin erkenden free edilmesinden dolayý.
		Diyelim ki 20KB'lik bir bellek alanýmýz var ve bunun 14 kbsi kullanýmda. Ben 5KB'lik bir alan allocate etmeye çalýþtýðýmda garanti yok. Çünkü dizinin
			sýralý olma garantisinden dolayý. HEAP'te parça parça bulunduðu içinde böyle bir zorluk çýkýyor karþýmýza.
		Birincinin avantajý burada geliyor aslýnda. Allocate ederken row için x * sizeof(int), col için y * sizeof(int) boyutunda iki farklý allocation yapýlýyor. 
		Ýkincisin de ise row * col * sizeof(int) tek 1 adet ardýþýk dizi allocate edilmeye çalýþýlýyor. Örneðin, 1000 row 1000 col olan bir dizi için 4 milyon byte'lýk
			contigous þekilde allocate edebileceðimiz alana ihtiyacýmýz var. Bu da sýkýntýlý bir durum baþ aðrýtabilir.
	*/
	// Yukarýda yaptýðýmýz ilk örnek contigous deðildi. Þimdi ise ayný örneði contigous yapýcam

	int** pp = (int**)malloc(row * sizeof(int*));
	if (!pp)
		return 0;

	int* intd = (int*)malloc(col * sizeof(int));
	if (!intd)
		return 0;

	for (int i = 0; i < row; ++i) {
		pp[i] = intd + i * col; // çok güzel, þiir gibi. Bir diziyi paramparça ediyoruz ve her parçanýn adresini pointer dizimize atýyoruz. 
	}
	free(intd);
	free(pp);

}


/*
Heap Alanýnýn Fragmantation Durumu
	Heap ten çok fazla alan alýndýðýnda, ardýþýk olarak 50.000 byte olmayabilir
	ama 50.000 byte toplamda yer olabilir.burada alan fragmante oluyor.

	Sisteme yer verilene kadar, o alaný baþka birinin kullanmasý mümkün deðil.
	bu geri verme iþlemine free ya da deallocate deniyor.

	free edilmezse memory, memory leak oluþuyor.Yani bellek sýzýntýsý.
	bu oluþursa memory de iþi yapabilmek için yer kalmýyor artýk.

	Programýn iþi bitti kapandý ama alýnmýþ alanlarý free etmedik diyelim.
	Program tekrar çalýþýrsa o bellek alanlarý sanki hiç alýnmamýþ gibi 0 km olarak
	bize ait ve kullanýlabilir.
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// void* realloc(void* vp, size_t newsize) fonksiyonun bildirimi
/*
-Hem büyütme hem küçültme amacý ile kullanýlabiliyor.
-Geri dönüþ deðeri void*
-Parametreleri;
	void* vp -> daha önceden allocate edilmiþ bellek bloðunun adresi
	size_t newsize -> Ýþlem sonrasý elde edilmek istenilen belleðin BYTE boyutu. Diyelim ki 5000 Bytelýk bir bellek bloðumuz var ve onu 6000 yapmak istiyoruz.
		newsize parametresine 1000 deðil 6000 göndermemiz gerek. 2000e düþürmek isteseydikte 3000 deðil 2000 yazacaktýk.

-realloc için 3 senaryo var;
	-Gönderdiðimiz bellek bloðunu büyütür, ayný adresi geri döndürür.
	-Gönderdiðimiz bellek bloðunu büyütemez ya da hiç kontrol bile etmez, istenilen boyutta bir bellek bloðu allocate eder ve onun adresini döndürür(içeriði kopyalar)
		Eðer, bunun için bir önlem alýnmadýysa eski bellek bloðu dangling pointer olacaðý için probleme yol açmýþ olur.
	-Büyütme iþlemi baþarýsýz olabilir. Fakat, bu gönderdiðimiz bellek bloðunu da kaybedeceðimiz anlamýna gelmiyor. Sadece arttýrma/azaltma iþleminde sorun olduðu anlamýna geliyor.

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

	// þimdi yeni bir bellek bloðu allocate edecez
	int numplus;
	printf("kac tam sayi eklenecek: ");
	(void)scanf("%d", &numplus);
	
	pd = (int*) realloc(pd, (num + numplus) * sizeof(int)); // byte olarak istediði için sizeof(type) ile çarpýyoruz. num+numplus olma sebebi ise istenilen YENÝ boyutu yazýyoruz.
	// C6308 Uyarýsýný düzeltmek etmek için, direkt pd'ye atamak yerine önce geçici bir deðiþkene atayýp NULL kontrolü yapýp öyle pdye atarak çözülebilir.
	/*
		int* pdTemp = (int*)realloc(pd, (num + numplus) * sizeof(int));
		if(pdTemp)
			pd = pdTemp;
	*/

	printf("realloc ile elde edilen adres : %p\n", pd);
	if (!pd)
		return 0;
	// Peki, yeni allocate ettiðimiz bu bellek bloðuna veri yazma iþini nasýl yapýcaz?
		// Tabiiki de, dizimizin bittiði yerden baþlayarak. Bunu da pd + num ile yapýcaz.

	set_array_random(pd + num, numplus); // pd + num yazarak, ilk bellek bloðunun bittiði yerden baþlayarak numplus kadar deðer yazdýk.
	print_array(pd, num + numplus);
	free(pd);
	return 1;
}


/*
- Reallocation TAKES TIME! -> Realloc zaman alan ve maliyetli bir fonksiyon. O yüzden kullanma zorunluluðumuz olmayan, boyutunu önceden bildiðimiz iþlemlerde kaçýnmalýyýz.
	int ch;
	int val;
	int counter = 1;
	int* pd = NULL;
	randomize();
	// Eðer realloc'a NULL adres olarak gönderilir ise, realloc malloc gibi iþ yapýyor.
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

- Reallocation invalidates pointers! -> invalid hale gelen pointer dangling pointer olacak, ya da dangling pointer olma þansý var.

*/
///////////////////////////////////////////////////////////////////////////////////////

/*                                                                   Dynamic Array             */
/*
Mantýksal iliþkideki veriler, herzaman memoryde tutuluyorlar.
Bu verilerin memory de nasýl tutulacaðý bilgisine data structure deniyor.

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

yurtdýþý mülakatlarda çok önemli.

Bunlardan en önemlisi halen daha dynamic array.Çünkü % 70 bu kullanýlýyor.
C++ ta bunu yöneten sýnýfa vector deniyor.

Avantajý index bilgisiyle verilere eriþebiliyoruz.

Bu tür dizilere sondan eleman eklemek constant time O(1) karmaþýklýðýnda.
Araya eleman ekleme ise O(n) karmaþýklýðýnda çünkü kaydýrma yapmak gerekiyor.

bizim önceki kodda constant time deðil çnkü her döngüde realloc çaðrýlýyor.
habire bellek kopyalanýyor biryerden baþka bir yere.

dinamik dizide bunun O(1) karmaþýklýðýnda olabilmesinin sebebi birer birer allocate etmiyor.
bir seferde % 50 fazlasýný allocate edip ona göre iþlem yapýyor.
eleman yazýldýðýnda ise tekrar büyütmeye ihtiyaç kalmýyor.

Yani
dizi boyutu Capacity
dizideki eleman sayýsý Size

capacity sürekli size dan çok daha büyük tutuluyor.size, capacity ye eþit olana kadar realloc yok.

size = 19 capacity = 20
size = 20 capacity = 20
reallocation
size 21 capacity 40
...

bu þekilde gider.Olayý sürekli realloc yapmamak.fazla artýrýyorki habire yapmasýn diye.
reallocta baya maliyetli çünkü.dinamik dizi veri yapýsýnda amortised constant time diye geçiyor.

KENDÝ DYNAMIC ARRAY KODUNU YAZDI HOCA, BEN YAZMIYORUM. 1.30

Caching de programlamada çok önemli bir mekanizma.cpu cache memory ye göre çok daha hýzlý.
eriþilmek istenen nesne cache de ise buna cache hit deniyor.Cache hit oraný dinamik dizide
daha yüksek olmasý sebebiyle de tercih ediliyor.

cache hitin tersi cache miss.

c++ ta cache mekanizmasý hazýr.C de yok : D
kendimiz yazacaðýz.

*/

