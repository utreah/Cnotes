#include "mylib.h"
#include <stdio.h>

static void foo(void)
{
	printf("foo cagrildi\n");
}

FPTR gfp = &foo;

void func(void)  // burada func �a�r�ld���nda gfp() yani foo() yani foo �a�r�s� yap�l�r.
{
	gfp();
}


FPTR setfunc(FPTR f) // davran�� de�i�tiren fonksiyonlar�n geri d�n�� de�eri de FPTR(function pointer oluyor)
{
	FPTR fp = gfp;
	gfp = f;

	return fp;
}