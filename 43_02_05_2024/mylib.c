#include "mylib.h"
#include <stdio.h>

static void foo(void)
{
	printf("foo cagrildi\n");
}

FPTR gfp = &foo;

void func(void)  // burada func çaðrýldýðýnda gfp() yani foo() yani foo çaðrýsý yapýlýr.
{
	gfp();
}


FPTR setfunc(FPTR f) // davranýþ deðiþtiren fonksiyonlarýn geri dönüþ deðeri de FPTR(function pointer oluyor)
{
	FPTR fp = gfp;
	gfp = f;

	return fp;
}