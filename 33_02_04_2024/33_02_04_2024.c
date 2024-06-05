#include "C:\Users\Liver\Documents\GitHub\Cnotes\|nUtility.h"
/*
bir fonksiyonun parametresi pointer ise biz buna dizinin adresini gönderebiliriz.

pointer daki veriye p[i] veya *(p+i) ile eriþilir.

dizi deðiþmeyecekse const int * ptr þeklinde parametre tanýmlamak mantýklý.

fonksiyon parametrelerini baþka bir fonksiyona argüman olarak gönderebilirim.

void func(int x); ile
void func(const int x); arasýnda hiçbir fark yok. Bu function redeclaration olarak kabul ediliyor. Bildirim anlamýnda hiçbir fark yok.
							hiçbir avantajda sunmuyor. Bu durum CPP'de de ayný. Derleyici kodu gördüðünde eðer parametre deðiþkenin deðeri
								deðiþmediðini gördüðünde optimizasyonunu ona göre yapýyor.


*/

int sum_array(const int* p, int size)
{

	int sum = 0;
	while (size--)
		sum += *p++;

	return sum;
}

double get_array_mean(const int* p, int size)
{
	return (double)sum_array(p, size) / size;
}

double get_std_dev(const int* p, int size)
{
	double mean = get_array_mean(p, size);
	double sum_square = 0;

	for (int i = 0; i < size; i++)
		sum_square += (p[i] - mean) * (p[i] - mean);

	return sqrt(sum_square / size);
}
//Elemanlarý reverse etme kodu. nutility ye eklendi
void reverse_array(int* p, int size)
{
	for (int i = 0; i < size / 2; i++)
	{
		swap(p + i, p + size - 1 - i);
	}
}

//Bu da nutility ye eklendi.
void get_min_max(const int* p, int size, int* max, int* min)
{
	*max = *min = *p;
	for (int i = 1; i < size; i++)
	{
		if (*min > *(p + i))
			*min = *(p + i);
		if (*max < *(p + i))
			*max = *(p + i);
	}
}


void bsort(int* p, int size)
{
	for (int i = 0; i < size - 1; i++)
		for(int j = 0; j < size - 1 - i; j++)
			if (p[j] > p[j + 1])
			{
				//swap(&p[j],&p[j+1]); buda çalýþýr fakat alttakini tercih ettik
				swap(p + j > p + j + 1);
			}
}



void copy_array(int* pdest, const int* psource, int n)
{
	while (n--)
		*pdest++ = *psource++;

}
int copy_array_main()
{
	int a[20];
	int b[20] = { 0 };
	int idx_a, idx_b, n;
	printf("a'da indeks: ");
	scanf("%d", &idx_a);
	printf("b'de indeks: ");
	scanf("%d", &idx_b);
	printf("Kaç adet kopyalansýn: ");
	scanf("%d", &n);

	// Eðer kaynak dizinin belirli yerinden belirli adetine kadar deðerleri hedef diziye yazdýrmak için göndermemiz gereken parametreler þunlar;
	copy_array(a + idx_a, b + idx_b, n);
	// Kaynak olarak kullanýlan dizi(bu durumda b) eðer deðerleri initialize edilmediyse yani garbage value tutuyor ise bu deðerleri kullanmak UB.
		// int b[20]; þeklinde olursa buradan gelecek deðerleri kullanmak UB, int b[20] = { 0 }; olur ise SIKINTI YOK.

}
// NOT: Eðer bir fonksiyonun bir yerden okuma bir yere yazma iþlemi yapacak ise std. lib'in kullandýðý konvensiyonel
//		parametre sýralamasý her zaman: önce hedef ->  sonra kaynak adres
int ptr_main()
{
	// Ýki pointerin farký iþaretli tam sayý türündendir.
		int a[10];
		printf("%d", (p + 5) - (p + 4)); // ekrana 1 yazdýrýr. 
		printf("%d", &p[5] - &p[4]); // ekrana 1 yazdýrýr. 
}



int main()
{
	int x = 5;
	int y = 4;
	int diff = &x - &y; // 1 yazdrýrýr fakat kullaným alaný yok. Derleyicye baðlý bu yüzden Unspecified Behaviour. 


	// Bir fonksiyonun parametre deðiþkeni bir pointer ise iki farklý þekilde gösterilebilir;
	//	1 - int func(int* p); veya, 
	//  2 - int func(int p[]); fakat
			// int func(int p[10]); standart burada bulunan tam sayýyý discard eder. Dizinin boyutunun 10 olduðu anlamýna gelmez.

	int x = 10;
	int* py = &x;
	int py[] = &x; // YANLIÞ, böyle yapýlamaz. Bu durum sadece fonksiyonun parametre deðiþkenleri için geçerli.

	///////////////////////////////////////////////////////////////////////////////////////////////
	// POINTER IDIOMLARI(IDIOMATIC POINTER EXPRESSIONS)
	
	// &x++ -> illegal, çünkü x++ bir rvalue ve &(addressof) operatörü ancak bir lvalue operand alabilir.
	// ++&x ->  illegal, ayný durum ++ prefix increment operatörü lvalue operand alabilir.	
	int a[3] = { 5,4,3 };
	int* p = a; // array decayden dolayý &a[0] oldu ve a'nýn ilk elemanýnýn adresi var.
					// dizilerin memoryde arka arkaya bulunma garantisi var.
	//*p++; -> tamamen legal hiçbir sýkýntý yok dizinin 1 indis numaralý elemanýna geçer.
	/*
			ÇOOOK ÖNEMLÝ
	int x = 10;

	&x++;  ->	x++ rvalue exp. dur, & operatörüde lvalue exp a etki eder.Sentaks hatasý.
	&++x;  ->	Ayný þekilde sentaks hatasý.illegal
	++&x;  ->	&x in degeri rvalue exp. dir. ama ++ operatörü lvalue exp. e ihtiyaç duyar.
				sentaks hatasý
	
	int a[10] = {0};
	int *p = a;
	*p++   ->	++ için, p bir lvalue exp dir.* operatörü ise adrese ihtiyaç duyar.Geçerli.
				bu ifade lvalue exp. * operatörü varsa lvalue exp üretir.
	*a++   -> Geçersiz. a bir dizi ve (a++) a burada array decayden dolayý rvalue olmaktan çýkar ve bu sentaks hatasýdýr.
	
	int a[5] = {0,10,20,30,40};
	int p = *a;

	// *++p; Geçerli ve ifade sol taraf deðeri
	// *++p = -1; ikinci elemana yapýldý atama
		---------------------------------------------------------
	---------------------------------------------------------
	---------------------------------------------------------

	Dizi Pointer farklýlýðý.

	Dizi contiguous olarak bellekte n tane nesnenin birlikte tutulduðu nesneler topluluðu.
	Pointer ise sadece adres tutar.

	Mesela
	int *p;

	p[5] = 12;  TANIMSIZ DAVRANIÞ(UB)

	Array decay den dolayý karýþtýrýlabilir.
	Array decay dizi ismini dizinin ilk elemanýnýn adresine dönüþtürüyor.
	
	*/

}
void reverse_array(int* pdest, const int* psource, int size)
{
	psource += size;
	while (size--)
	{
		*pdest++ = *--psource;
	}
}
#define SIZE 5
void reverseArray(int* p, int size)
{
	int* pe = p + SIZE; // SIZE bir makro
	while (p < pe)
	{					// MÜLAKAT SORUSU
		swap(p++, --pe);	// pe nin bir küçüðünü p ile yer deðiþtir.P yi bir artýr.
	}					// pe zaten azaltlýyor iþlemden önce.
}

void reverse_copy(int* pdest, const int* psource, int size)
{
	while (size--)
		*pdest++ = *(psource + size);
}
///////////////////////////////////////////////////////////////////
/*
											VALID VE INVALID POINTERLAR
Invalid Pointer: Kullanýlamaz olmasý, kendisine geçerli bir adres atamadan asla kullanýlmamalý
Valid Pointer: Kullanýlabilir olabilir, bazý iþlemlerde kullanýlmasý legal ve doðru olabilir.
				DÝKKAT: Bizler invalid pointerlarý asla kullanmamalýyýz.
	1 - Otomatik ömürlü, ilk deðer verilmemiþ adres deðiþkenleri:
		int* p; -> þu anda geçersiz, hiçbir deðer atamasý yapýlmamýþ.
			*p; -> sentaks hatasý çünkü deðere eriþmeye çalýþýyoruz
	
		Dangling Pointer: Pointer deðiþken hayatta olan bir nesneyi tutuyor. Bu nesne ömrünü tamamladýðýnda pointer geçersiz hale geliyor. Buna 'dangling pointer' denir.00
			Dynamic Memory Management kýsmýnda aþýrý önemli olacak.
	GEÇERLÝ POÝNTER:
		Geçerli bir pointer demek o pointerin dereference edilebileceði anlamýna gelmiyor(dereferencable deðil)
	int main(void)
	{
		int x = 10;
		int* p = &x; // geçerli bir pointer, dereferencede edilebilir.

		int a[4] = {1, 2, 3, 4}
		int* p1 = &a[4]; // bu dizinin son indisi 3(a+3), dizi boyutunun dýþýna çýkýp bunu kullanmak UB oluþturur.
			Bir dizinin dýþýnda kalan adresini kullanmak 'valid' fakat dereferencable deðil. Ve bu dizinin dýþýnda kalan adresteki deðer
				kullanýlýrsa(dereference edilip) bu UB. (line 224) 
			Bu a+4 yani dizinin bittiði elemanýný dizinin ilk elemanýndan çýkarýrsak dizinin boyutunu buluruz.
			a+4 - a = 4 // dizinin 4 elemanlý anlamýna gelir.
				Line 183teki psource += size; -> aslýnda bunu yaptýðýmýzda dizinin son elemanýný deðil dizinin bittiði elemana ulaþýrýz. 
					Bu deðiþkeni kullanmakta sakýnca yok fakat dereference edilip deðeri kullanýlýrsa bu UB(Line 225)
						Bu özellik sadece karþýlaþtýrma iþlemleri için kullanýlacak!
		

		ÖNEMLÝ!! Tekil nesnelerde adeta tek elemanlý dizilermiþ gibi ele alýnýyor.
			int x = 10;
			int* p = &x + 1; // Bu GEÇERLÝ(VALID) bir pointer.
			printf("%d", *p); // bunu böyle kullanmak UB çünkü þu anda p adres deðiþkeni x'ten sonraki adresi gösteriyor ve bu adres garbage value tutuyor.
			printf("%d", *--p); // Burada ise ekrana 10 deðerini yazdýrýr.
		Bu yukarýda anlatýlanlar sadece ve sadece dizinin bittiði yer için geçerli. Mesela 4 büyüklüðünde bir dizinin 5. elemaný bittiði yer olur.
			Eðer 6. elemana eriþmeye çalýþýrsam bu bir invalid pointer. ÖRNEK;
				int a[4] = { 0 };
				int* p = a + 5; // veya &a[5); // bundan yana sýkýntý yok bu geçerli
				int* p = a + 6; // veya &a[6); // INVALID pointer GEÇERSÝZ.
				int* p = a - 1; // bu da geçersiz bir durum.
			Bu sadece dizinin bittiðini gösteren eleman için özel bir durum. CPP'de de ayný.
		Bir pointerin geçerli olabilmesi için þu üç senaryodan biri olmalý;
			-Ya hayatý devam etmekte olan bir nesnenin adresini
			-Ya dizinin bittiði yerin adresi
			-Ya da null pointer denilen özel bir adres // ileride iþleyecez.



	}

*/





/*											POINTERLAR VE KARÞILAÞTIRMA ÝÞLEMLERÝ
int main(void)
{
	int a[5] = {0, 1, 2, 3, 4);
	int x = 10;
	int y = 30;
	int* p1;
	int* p2;
	
	p1 == p2;
		a) Ayný nesnenin adresini tutuyorlar ise -> p1 = &x; p2 = &x;
			if (p1 == p2)
				printf("EKRANA DOGRU YAZDIRIR");

		b) Ayný dizinin bittiði yerin adresini tutuyorlar ise -> p1 = a + 5; p2 = a + 5;
			if (p1 == p2)
				printf("EKRANA DOGRU YAZDIRIR ÇÜNKÜ ÝKÝSÝDE AYNI DÝZÝNÝN BÝTTÝÐÝ YERDEKÝ ELEMANIN ADRESÝNÝ GÖSTERÝYOR");

		c) Ýkisinin deðeri de null pointer ise. p1 = &x; p2 = NULL; -> NULL bir makro
			if(p1 == p2)
				// Yanlýþ olduðu için else kýsmýna girer.

	p1 != p2;

	p1 > p2;
	p1 >= p2;

	p1 < p2;
	p1 <= p2;

}





*/