// Süre ölçme iþlemleri için clock adý verilen bir fonksiyon kullanýlýyor.

/*
	Bildirimi þu þekilde.
		clock_t clock(void); // geri dönüþ deðeri derleyiciye baðlý olan clock_t adýnda bir typedef bildirimi. Benim derleyicimde long.

	clock fonksiyonu çaðýrýldýðýnda geri dönüþ deðeri 'tick count'(tick miktarý/sayýsý) denilen bir þey.
		tick count denilen donanýmsa veya yazýlýmsal olarak main fonksiyonun çaðrýlmasýndan, clock fonksiyonunun çaðýrýlmasýna kadar geçen
			tick sayýsýna deniyor. Bu standart bir deðer deðil derleyiciden derleyiciye deðiþebilir.
	Bu tick sayýsýný saniyeye dönüþtürmek için bir makro var. Bu makronun adý CLOCK_PER_SEC -> bu makro tik sayýlarýný saniye
		cinsinden karþýlýk geldiði deðeri yazýyor.
		Saniye cinsinden türünü almak içinde clock() ile geri döndürülen deðeri CLOCK_PER_SEC makrosu ile bölüyoruz.
	CLOCK_PER_SEC 'te tam sayý bir deðer olduðu için, veri kaybýný önlemek için bölme iþleminin sol operandýný double(sað operandý da yapabiliriz) yapýyoruz.

	Ýki iþlem arasýndaki geçen süreyi/tick count'ý hesaplamak için kullanýyoruz bu fonksiyonu.

	CLK_TCK makrosu ise direkt olarak saniyeyi veriyor. Fakat bu standart bir makro deðil ama neredeyse tüm derleyiciler veriyor bu makroyu.

*/
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"

/*
int main(void) {

	printf("kac tam sayi? :");
	size_t n;
	(void)scanf("%zu", &n);

	int* p = (int*)malloc(n * sizeof(int));
	if (!p)
		fprintf(stderr, "bellek yetersiz\n");
	set_array_random(p, n);
	sort_array(p, n);
	print_array(p, n);
	printf("Siralama bitti\n");
	// printf("clock tick = %ld", clock()); Bu þekilde yazdýrýnca tick sayýsýný gösteriyor. Bunu sniye cinsine döndürelim
	printf("Gecen Sure : %lf", (double)clock() / CLOCKS_PER_SEC); // clock_per_sec tam sayý olduðu için veri kaybýný önlemek adýna
											// iþlemi bir gerçek sayý türünde yapýyoruz ve böylece veri kaybý olmuyor.
	free(p);
}
*/
// Eðer spesifik bir iþlemin ne kadar zaman aldýðýný görmek istiyor isek o iþlemden önce baþlatmamýz gerek.

int main(void) {
	clock_t start = clock();

	printf("kac tam sayi? :");
	size_t n;
	(void)scanf("%zu", &n);

	int* p = (int*)malloc(n * sizeof(int));
	if (!p)
		fprintf(stderr, "bellek yetersiz\n");
	set_array_random(p, n);
	sort_array(p, n);
	print_array(p, n);
	printf("Siralama bitti\n");
	clock_t end = clock();
	printf("Gecen sure %lf", (double)(end - start) / CLOCKS_PER_SEC); // hoca 2:28de bir þey diyor ama anlaþýlmýyor sor kendisine

}