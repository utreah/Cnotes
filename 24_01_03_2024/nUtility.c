// code file / implementation file
#include "nutility.h"
#include <Windows.h>
#include <stdio.h>
#define RANDOMIZE() srand((unsigned)time(NULL))
#define RANDOM_DICE() (rand() % 6 + 1)
// bu modül bir hizmet veriyor ama verirkende ayný zamanda stdio.h tan ve windows.h tan hizmet alýyor.
// include edilme sýrasý, ilgili nesnelerin kullaným sýrasý ile alakalý.
//nUtility.h bu dosyaya'da include edildi çünkü
/*
1 - Burada da macro var, include edilmesiydi macro çalýþmazdý.
2 - Inclusion guard için.
3 - nUtility.h dosyasý içerisinde fonksiyon bildirimleri var. Eðer nUtility'i dahil etmeseydik fonksiyon çaðrýlarýný göremediði için nUtility.c içerisindeki fonksiyonlarý göremez
ve kullanamazdýk.
*/


int isprime(int number)
{
	if (number < 2)
		return 0;
	if (number % 2 == 0) return number == 2;
	if (number % 3 == 0) return number == 3;
	if (number % 5 == 0) return number == 5;

	for (int i = 7; i * i <= number; i += 2)
	{
		if (number % i == 0)
			return 0;
	}
	return 1;
}

int ndigit(int number)
{
	int digit_count = 0;

	if (number == 0)
		return 1;

	while (number)
	{
		number /= 10;
		digit_count++;
	}
	return digit_count;
}

void clear_input_buffer(void)
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void put_start(void)
{
	printf("**********************************************");
}



void main(int d)
{
	int n;
	printf("Sayi giriniz: ");
	while ((scanf("%d", &n)) != 0) {
		if (n >= 10 && n <= 20)
			;
		else
			n %= 10;
		switch (n) {
		case 1: printf("st\n"); break;
		case 2: printf("nd\n"); break;
		case 3: printf("rd\n"); break;
		default: printf("th\n"); break;
		}
	}

}

int isleap(int y)
{
	return (y) % 4 == 0 && ((y) % 400 == 0 || (y) % 100 != 0);
}

void print_triangle(int x)
{
	for (int i = 0; i < x; ++i) {
		for (int k = 0; k <= i; ++k)
			printf("*");
		printf("\n");
	}
}