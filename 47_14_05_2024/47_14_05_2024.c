#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"

/*
	malloc ile ayrýlan alana HEAP denir.
	Baþka bir kodun kullanýlmasýný saðlayan kodlara 'wrapper' denir. 
	Bir fonksiyon var, fonksiyonun yaptýðý iþe ek yapmak istiyoruz. Buna 'augmentation' deniyor.
	wrapper örnek

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
		int p = (int*)checked_malloc(n * sizeof(int)); // malloc'un kontrolü burada yapýlýyor.	

		////////////////////////////////////////////

	}

	void func(int x, int y, double d);

	void sfunc(double d, int x, int y)
	{
		func(x,y,d); //bu þekilde de parametreleri istediðimiz sýrada 
						// çaðýrabiliriz.
	}

	-------------------------------------------------------------

	veya aþaðýdaki gibi parametreleri azaltarakta çaðrýlabilir.

	void func(int x, int y, int z);
	void wfunc(int x, int y)
	{
		func(x,y,0);
	}
	
*/
/////////////////////////////////////////////////////////////////////////////////////////////////


/*
	free(void* vp); // Kullanýmdan çekilecek belleðin adresini istiyor. Kaç byte edileceðini vs sormuyor.
	// 40 bytelýk bir alan allocate ettiðimizde aslýnda derleyici daha fazla bellek allocate ediyor.
		bu fazlalýk kýsýmda yapýlan malloc iþlemi ve bazý bilgiler tutuluyor. Boyutu, adý vs gibi bilgiler. Buna 'header' deniyor.

	dk 35:
*/