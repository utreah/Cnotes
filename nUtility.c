// code file / implementation file
#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10
// bu mod?l bir hizmet veriyor ama verirkende ayn? zamanda stdio.h tan ve windows.h tan hizmet al?yor.
// include edilme s?ras?, ilgili nesnelerin kullan?m s?ras? ile alakal?.
//nUtility.h bu dosyaya'da include edildi ??nk?
/*
1 - Burada da macro var, include edilmesiydi macro ?al??mazd?.
2 - Inclusion guard i?in.
3 - nUtility.h dosyas? i?erisinde fonksiyon bildirimleri var. E?er nUtility'i dahil etmeseydik fonksiyon ?a?r?lar?n? g?remedi?i i?in nUtility.c i?erisindeki fonksiyonlar? g?remez
ve kullanamazd?k.
*/
#define ASIZE(a) (sizeof(a) / sizeof(a[0]))
// #define RANDOMIZE() srand((unsigned)time(NULL))
#define RANDOM_DICE() (rand() % 6 + 1)
int isprime(int number)
{
	if (number < 2)
		return 0;
	if (number % 2 == 0) return number == 2;
	if (number % 3 == 0) return number == 3;
	if (number % 5 == 0) return number == 5;

	for (size_t i = 7; i * i <= number; i += 2)
	{
		if (number % i == 0)
			return 0;
	}
	return 1;
}
void randomize()
{
	srand((unsigned)time(0));
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

void put_star(void)
{
	printf("**********************************************");
}



void number(int d)
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
	for (size_t i = 0; i < x; ++i) {
		for (int k = 0; k <= i; ++k)
			printf("*");
		printf("\n");
	}
}

void set_array_random(int* p, size_t size)
{
	while (size--)
		*p++ = rand() % 1000;
}
void print_array(const int* p, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (i && i % 20 == 20)
			printf(" \n");
		printf(" %3d", p[i]);
	}
	printf("\n|-------------------------------------------|\n");
}


int* create_array(int n) // kursun ikinci yar?s?nda ??renilecek
{
	int* pd = (int*)malloc(n * sizeof(int));
	if (!pd) {
		printf("bellek yetersiz\n");
		exit(EXIT_FAILURE);
	}
	return pd;

}
void sort_array(int* p, size_t size)
{
	qsort(p, size, sizeof(*p), icmp);
}
int icmp(const void* vp1, const void* vp2)
{
	return *(const int*)vp1 - *(const int*)vp2;
}
void sgets(char* p)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		*p++ = c;

	*p = '\0';

}

void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverseArray(int* p, size_t size)
{
	int* pe = p + size;

	while (p < pe)
		swap(p++, pe--);

}
int* get_array_min(const int* p, size_t size)
{
	const int* pmin = p;
	for (size_t i = 0; i < size; i++)
	{
		if (*pmin > *(p + i))
			pmin = (p + i); // veya pmin = &p[i];
	}

	return (int*)pmin; // bu casting daha sonra a??klanacak.
}

int* get_array_max(const int* p, size_t size)
{
	const int* pmax = p;

	while (size--) // (p++, size--) ?eklinde de yaz?labilir. 
	{
		if (*pmax < *p)
			pmax = p;
		p++;
	}
	return (int*)pmax; // buradaki cast daha sonra anlat?lacakm??.
}

void selection_sort(int* p, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		swap(get_array_min(p + i, size - i), p + i);
	}
}