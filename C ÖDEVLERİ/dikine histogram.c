#include <iostream>
#define SIZE 20
int find_max(int* a)
{
	int max = a[0];
	for (int i = 0; i < SIZE; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}
int main()
{
	int a[SIZE] = { 5,15,12,10,19,17,18,3,1,4,6,14,7,12,7,10,11,18,19,6};
	int max = find_max(a);

	for (int i = 0; i < SIZE; i++) {
		for (int k = 0; k < SIZE; k++)
		{
			if (a[k] == max && max > 0) {
				printf("*");
				a[k] -= 1;
			}
			else
				printf(" ");
			printf(" ");
		}
		max -= 1;
		printf("\n");

	}
	return 0;
}
;
