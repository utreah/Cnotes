#include "nUtility.h"
#include <stdio.h>
// Zaman geçtikçe bu modül dosyasýna yeni makrolar, yeni fonksiyon eklemeleri yapýlacak.


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