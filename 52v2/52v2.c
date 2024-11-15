// S�re �l�me i�lemleri i�in clock ad� verilen bir fonksiyon kullan�l�yor.

/*
	Bildirimi �u �ekilde.
		clock_t clock(void); // geri d�n�� de�eri derleyiciye ba�l� olan clock_t ad�nda bir typedef bildirimi. Benim derleyicimde long.

	clock fonksiyonu �a��r�ld���nda geri d�n�� de�eri 'tick count'(tick miktar�/say�s�) denilen bir �ey.
		tick count denilen donan�msa veya yaz�l�msal olarak main fonksiyonun �a�r�lmas�ndan, clock fonksiyonunun �a��r�lmas�na kadar ge�en
			tick say�s�na deniyor. Bu standart bir de�er de�il derleyiciden derleyiciye de�i�ebilir.
	Bu tick say�s�n� saniyeye d�n��t�rmek i�in bir makro var. Bu makronun ad� CLOCK_PER_SEC -> bu makro tik say�lar�n� saniye
		cinsinden kar��l�k geldi�i de�eri yaz�yor.
		Saniye cinsinden t�r�n� almak i�inde clock() ile geri d�nd�r�len de�eri CLOCK_PER_SEC makrosu ile b�l�yoruz.
	CLOCK_PER_SEC 'te tam say� bir de�er oldu�u i�in, veri kayb�n� �nlemek i�in b�lme i�leminin sol operand�n� double(sa� operand� da yapabiliriz) yap�yoruz.

	�ki i�lem aras�ndaki ge�en s�reyi/tick count'� hesaplamak i�in kullan�yoruz bu fonksiyonu.

	CLK_TCK makrosu ise direkt olarak saniyeyi veriyor. Fakat bu standart bir makro de�il ama neredeyse t�m derleyiciler veriyor bu makroyu.

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
	// printf("clock tick = %ld", clock()); Bu �ekilde yazd�r�nca tick say�s�n� g�steriyor. Bunu sniye cinsine d�nd�relim
	printf("Gecen Sure : %lf", (double)clock() / CLOCKS_PER_SEC); // clock_per_sec tam say� oldu�u i�in veri kayb�n� �nlemek ad�na
											// i�lemi bir ger�ek say� t�r�nde yap�yoruz ve b�ylece veri kayb� olmuyor.
	free(p);
}
*/
// E�er spesifik bir i�lemin ne kadar zaman ald���n� g�rmek istiyor isek o i�lemden �nce ba�latmam�z gerek.

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
	printf("Gecen sure %lf", (double)(end - start) / CLOCKS_PER_SEC); // hoca 2:28de bir �ey diyor ama anla��lm�yor sor kendisine

}