#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"

/*
	malloc ile ayr�lan alana HEAP denir.
	Ba�ka bir kodun kullan�lmas�n� sa�layan kodlara 'wrapper' denir. 
	Bir fonksiyon var, fonksiyonun yapt��� i�e ek yapmak istiyoruz. Buna 'augmentation' deniyor.
	wrapper �rnek

	void* checked_malloc(size_t n){
		
		void* vp = malloc(n);

		if(!vp){
			fprintf(stderr, "nullptr returned!");
			exit(EXIT_FAILURE);
	}
	return vp;
}

	int main(void){
		int n;
		printf("kac adet sayi: ");
		scanf("%d", &n);
		int p = (int*)checked_malloc(n * sizeof(int)); // malloc'un kontrol� burada yap�l�yor.	

		////////////////////////////////////////////

	}

	void func(int x, int y, double d);

	void sfunc(double d, int x, int y)
	{
		func(x,y,d); //bu �ekilde de parametreleri istedi�imiz s�rada 
						// �a��rabiliriz.
	}

	-------------------------------------------------------------

	veya a�a��daki gibi parametreleri azaltarakta �a�r�labilir.

	void func(int x, int y, int z);
	void wfunc(int x, int y)
	{
		func(x,y,0);
	}
	
*/
/////////////////////////////////////////////////////////////////////////////////////////////////


/*
	free(void* vp); // Kullan�mdan �ekilecek belle�in adresini istiyor. Ka� byte edilece�ini vs sormuyor.
	// 40 bytel�k bir alan allocate etti�imizde asl�nda derleyici daha fazla bellek allocate ediyor.
		bu fazlal�k k�s�mda yap�lan malloc i�lemi ve baz� bilgiler tutuluyor. Boyutu, ad� vs gibi bilgiler. Buna 'header' deniyor.

	dk 35:
*/