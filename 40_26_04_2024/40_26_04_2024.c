#include <stdio.h>
#include <string.h>
#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
/*
	idiyomlar
	-const char* pdays[] = {"", "Pazartesi", "Salý"...}; // ilk indexi boþ býrakýyoruz ki pazartesi 1 deðerini alsýn. 
				"" -> bu NULL ptr
	-const char* pmonths[] = {"Ocak", "Subat", "Mart", "Nisan", NULL}; -> NULL karakteri dizinin boyutunu doðrudan kullanmýyoruz
		// mesela bir döngü var ve bu döngüyü NULLptr gelene kadar döndürebiliriz. Bu sayede dizinin uzunluðu deðiþtiðinde
			// deðiþiklik yapmamýza gerek kalmaz
			int i = 0;
			while(pmonths[i++] != NULL);
	-const char* pyears[5] = {"2001", "2002", "2003", "2004" "2005"}; // 2004 ile 2005 arasýnda virgül olmadýðý için -> sýkça yapýlan bir hata	
		// compile time'da bu birleþtirilecek. dizinin boyutu 5 fakat dizinin sadece ilk 4 indeksine ilk deðer atamasý yapýlmýþ.
			// son pyears[5] -> NUrr pointer deðerini alacak. Tam sayý dizisi olsaydý '0' deðeri verilecekti.

	-//designated initializator
	char* p[100] = { [5] = "Ali",[12] = "Mehmet" };
	// ilk deðer verilmeyenler null ptr olur.

	regex(regular Expression): Öyle bir notasyon olsun ki yazýnýn uymasý gereken koþullarý ifade etsin.
		// Girilen yazýnýn notasyona uyumlu olup olmadýðýný kontrol ediyor. Örnek olarak bu websitelerinde kayýt olurken
			// epostalar için 'geçerli bir e-mail adresi deðil' yazýsýný örnek verebiliriz.
				// Belirli bir notasyon istiyor ve o notasyona uygunluðunu kontrol ediyor
		-Validity Check:
		-Search
		-replacement
	/////////////////////////////////////////////////////////////////////////////////
	POINTEr TO POINTEr
		//Baþka bir pointerin adresini tutan pointer.
		//Gösterici gösteren gösterici. (müdür müdür müdür?)

	int main(void){
		int x = 10;
		int* p = &x; // burada int türündne bir deðiþkenin adresini tutuyoruz.
	}
	T a; // T türünden a deðiþkeninin adresini tutmak için T* türündne bir deðiþken tanýmlamamýz gerekiyor.
	// Peki ya T* türünden bir deðiþkenin adresini tutmak isteseydik?
		-> T** p;
	int x = 500;
	int* p = &x;
	int** ptp = &p; // int* p bir nesne olduðu için adresi vardýr. Bu adresi tutmak için ise int** türünden bir
		// deðiþken tanýmlayabiliriz. 
	int* ptp2 = &p; // burada p int* türündne bir deðiþken ptp2'de ayný þekilde. Bu cpp'de sentaks hatasý
						// C'de örtülü dönüþüm var. Ondan dolayý sýkýntý yok
	int* tt = int** // örtülü dönüþüm yapýlýr. C'de okey ama CPP sentaks

	int* p2 = &x; // Buna pointer to int deniyor
	int** ptp3 = &p; // pointer to pointer to int
	*p; // bu x deðiþkenine eriþir.
	*ptp; // p deðiþkenine eriþir.
	**ptp -> *(*ptp) // x deðiþkenine eriþir.
	printf("%d", *p); // ekrana 500 yazdýrýr

	**ptp = 340; // x deðiþkenine eriþtik ve deðerini 340 yaptýk.
	printf("%d", **ptp); // ekrana 340 yazdýrýr (2 adet derefencing operatörü kullandýk)
	**++ptp; -> ++(*(*ptp));
	printf("%d", **ptp); // ekrana 341 yazdýrýr 

*/

/////////////////////////////////////////////////////////////////////////////////////
/*
		Expression		Data Type		Value Category
		x				int				L
		&x				int*			R
		p				int*			L
		*p				int				L
		&p				int**			R
		ptr				int**			L
		*ptr			int*			R
		**ptr			int				L
		&ptr			int***			R
		bu nereye kadar gider?
			int * her kodda görülür.
			int ** birçok kodda görülür.
			int *** nadiren görülür.
			int **** neredeyse hiç görmeyiz.1-2 defa belki
			int ***** bunu unut :D
		int x = 99;
		int *p1 = &x;
		int **p2 = &p1;
		int ***p3 = &p2;
		int ****p4 = &p3;
		int *****p5 = &p4;
		int ******p6 = &p5;
		int *******p7 = &p6;
		int ********p8 = &p7;
		int *********p9 = &p8;
		int **********p10 = &p9;
		int ***********p11 = &p10;
		int ************p12 = &p11;
		int *************p13 = &p12;
		int **************p14 = &p13;
		int ***************p15 = &p14;
		int ****************p16 = &p15;
		int *****************p17 = &p16;
		int ******************p18 = &p17;
		int *******************p19 = &p18;
		int ********************p20 = &p19;

		p20 yi dereference edip ++ nýn operandý yapalým
		++********************p20; -> bu x i 1 artýrýr.
		x = 100 oldu
*/
////////////////////////////////////////////////////////////////////
/*
	int a[] = {1, 2, 3, 4, 5,};
	int* p = a;
	int** ptp = &p;

	++*ptp; // p'nin adresini bir arttýrýz, p, a dizisinin adresini tuttuðu için sonraki indise geçer.
	++**ptp; // bir önceki adýmda adresi arttýrmýþtýk þimdi ise o adresin tuttuðu deðerin deðerini arttýrýyoruz. 
				// Bu durumda 2 -> 3 olacak.
		
Pointer to pointer ne iþe yarar?
	-Pointer deðiþkenlerinin adreslerini deðiþtirmek için kullanýlýr. 
	void foo(int*);
	void bar(int**);
	int main(void){
	int x = 45;
	int y = 32;
	int* p = &x;
	int* q = &y;
	foo(p); // x'in adresini gönderiyoruz.
	bar(&p); // p'nin adresini gönderiyoruz.
	////////////////////////
	aþaðýda x ve y swap edildi.
	int temp = x;
	x = y;
	y = temp;
	Eðer ben bunu fonksiyon ile yapmak isteseydim, x ve y deðiþkenlerini call by reference ile göndermek zorundaydým.
		Eðer x ve y'nin adreslerini göndermez isem fonksiyonda deðiþim olur fakat fonksiyon bittiðinde eski haline dönerdi.
		swap(int* p, int* q);
		swap(&x, &y);
/////////////////////////////////////////////////////////////
	Pointer kullanarak swap yapalým;
	int * ptemp = p;
	p = q;
	q = ptemp;
	Böyle yaptýðýmýzda da swap yapmýþ oluyoruz. Bir projede birden fazla swap yapýyorsak her seferinde bunu yazmak mantýklý deðil.
		O yüzden fonksiyon yapabiliriz. Fonksiyonu yazarken de parametrelerini pointer to pointer to data type þeklinde yazmak
			gerekli.
		pswap(int** p, int** q);
		pswap(&p, &q);

	}

*/
/*
	Pointer to Pointer örnek.
		Diyelim ki 1 fonksiyon içerisinde bir dizinin hem min ve hem max deðerleri bulunuyor ve bu iki deðerin adresleri döndürülmeli.
			return ile sadece 1 deðer döndürebildiðimiz için pointer to pointer to data type kullanarak min ve max deðerlerinin
				adreslerini yazýyoruz.
	#define SIZE 100
	void get_arr_min_max(const int* pa, size_t arr_size, int** pmax, int** pmin){
	*pmin = *pmax = (int *)pa;
		for(size_t i = 1; i < arr_size; i++)
			if(pa[i] > **pmax) // pmax'ýn gösterdiði adresin gösterdiði adresinin deðeriyle karþýlaþtýracaðýmýz için ** kullanýyoruz.
				*pmax = (int*)&pa[i]; // pa[i]'nin adresini *pmax pointerýna atýyoruz. Ýþlem sonunda pmax, dizinin en büyük elemanýný gösterecek
			else if(pa[i] < **pmin)	// pmin'in gösterdiði adresin gösterdiði adresinin deðeriyle karþýlaþtýracaðýmýz için ** kullanýyoruz.
				*pmin = (int*)&pa[i]; // pa[i]'nin adresini *pmin pointerýna atýyoruz. Ýþlem sonunda pmin, dizinin en küçük elemanýný gösterecek
	} // iþlem sounnda ptr_max ve ptr_min deðiþkenleri max ve min deðerlerinin ADRESLERÝNÝ tutacak.
	int main(void){
		int arr[SIZE] = {123,124215,26731,1232153,26132632,31};
		int* ptr_max = NULL;
		int* ptr_min = NULL;
		get_arr_min_max(arr, SIZE, &ptr_max, &ptr_min);
		printf("%d    %d", *ptr_min, *ptr_max); // min ve max deðerlerini ekrana yazdýrdýk.
		swap(ptr_min, ptr_max); // burada ptrlerin adreslerini göndermeye gerek yok. Çünkü takas iþlemini pointerlar üzerinde yapmýyoruz.
									// içeriklerinin yerlerini deðiþtiriyoruz. Eðer adreslerini gönderseydik ptr_min 

	}
	
		#include <stdio.h>

		void func(int **p1, int **p2)
		{
		int ptemp = **p1; 
		**p1 = **p2;	
		**p2 = ptemp; 
		}

		int main()
		{
		int a = 34;
		int b = 67;
		int *pa = &a;
		int *pb = &b;
		printf("pa = %p          pb = %p\n", pa, pb);
		func(&pa,&pb); // a ve b'nin deðerlerini swap ettik. a->b, b->a;
		printf("pa = %p          pb = %p", pa, pb);
		}
	
*/
int x = 50;
int y = 75;
int z = 100;
int foo(int** param, int size) {
	for (int i = 0; i < size; i++)
		// param[i]; == a[0] == &x; Yani param[i] aslýnda int* türünden bir nesneyi gösteriyor þu anda.
		printf("%d", *param[i]); // burada ise int* dereference edilerek x, y ve z nesnelerinin deðerlerine eriþiyoruz.
}
void bar(int*** x) {
	//x =  burada atama ptr, p veya x(main)'e olmuyor. int*** türünden olan x'e atama yapýyoruz. Yani bu atamadan sonra
		// main gövdesinde bulunan hiçbir nesnenin deðerinde deðiþiklik olmaz.
	*x; // ptr nesnesine eriþir.
	**x; // p nesnesine eriþir
	**x; // x nesnesine eriþir
}
int main(void) {

	int* a[] = { &x, &y, &z }; // Normalde bir dizinin adresini bir fonksiyon parametresine gönderdiðimizde fonksiyonun
								// T* türünden olmasý yetiyor fakat burada a'nýn 0. elemanýný int* türünden bir deðer olduðundan dolayý
									// fonksiyondan parametresi T** türünden olmak zorunda
	foo(a, 3); // -> foo(&a[0], 3);
	int x = 10;
	int* p = &x;
	int** ptr = &p;
	bar(&ptr);

}

void print_names1(char* const* p, size_t size) //aradaki const açýklanacak.
{
	for (size_t i = 0; i < size; i++)
	{
		printf("%s ", *(p + i));
	}

}



void print_names2(char* const* p, size_t size) //aradaki const açýklanacak. *p deðiþmez(const) demek bu
{
	while (size--)
	{
		printf("%s ", *p++);// *p++ -> burada öncelik sýrasý saðdan sola. p + 1 yapýlýp dereference yapýlýyor
	}						// kural ihlali yok. ++*p; yazýlsaydý, tanýmda *p deðiþmez diyor.sentaks hatasý.

}
void sort_names(char** p, size_t size) // klasik bubble sort
{
	for (size_t i = 0; i < size - 1; i++)
		for (size_t k = 0; k < size - 1 - i; k++)
			if (strcmp(p[k], p[k + 1]) > 0)
			{
				char* ptemp = p[k];
				p[k] = p[k + 1];
				p[k + 1] = ptemp;
			}
}

int main(void) {

	char* pdays[] = { "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar" }; // bu isimleri yazdýrmak için bir
								// fonksiyon yazýcaz print_names1 ve 2.
		//pdays char* türünden bir nesne olduðu için fonksiyonun parametreleri T** türündne olmak zorunda. Çünkü
			//pdays'in ilk elemanýnýn adresini fonksiyona göndericez.
	print_names1(pdays, 7);
	int x = 10;
	// const'un yerini unutursak þuna dikkat etmek gerekiyormuþ.
		// const neyden önce geliyorsa const olan nesne o'dur
	const int* p = &x; // burada const int*'dan önce geliyor bu durumda const olan deðer x'tir. *p üzerinde deðiþiklik yapamayýz.
	int* const p = &x; // burada ise const p'den önce geliyor bu durumda p'nin deðeri const olan deðerdir. 
							// *p ile burada x'in deðeri deðiþtirilebilir fakat p = &y; gibi ibr þey yaparsak bu sentaks hatasý.

}
int b = 123;
int access(const int* const* p, int size) {
	// Þimdi eðer access fonksiyonu parametre türü olarak int* const* p olarak alýrsa
		// const *p'yi niteler. Bu sayede dizinin elemanlarý (&x, &y, &z) deðiþtirilemezken, **p yapýlarak adreslerini tuttuklarý
			// nesnenin deðerini deðiþtirebilir. Bunun önüne geçmek için const int* const* p; þeklinde yapýyoruz
		// int*'dan önce gelen const int*'ý niteleyerek adresi gönderilen T* türünden dizinin deðerinin içeriklerinin deðiþmesini
			// engelliyor.
	p[2] = &b; // sentaks hatasý çünkü const *p'yi niteliyor ve tuttuðu adreslerin deðiþmesini engelliyor.(2. bir içerik operatörü ile
					// o adreslerin gösterdiði deðerde oynama yapýlabiliyor)
	*p[2] = 5; // eðer const int* const* p þeklinde olursa parametre bu da sentaks hatasý. Bu durumda sadece okumak istediðimiz için
					// const int* const* p þeklinde tanýmlý.
}
int main(void)
{
	// int* const* öðrendiklerimizden çook farklý fakat çok basit.
		// eðer consttan sonra yýldýz geliyorsa eriþemediðimiz yer *idf'tir. Örneðin;
	int x = 10;
	int* p = &x;
	int* const *ptr = &p; // burada p'nin deðerinin deðiþtirilmesini engelliyoruz. Çünkü const *ptr'yi niteliyor.
	int** const ptr = &p; // burada const ptr'yi niteliyor ve ptr'nin &p dýþýnda bir deðer almasýný engelliyor. p'nin içeriði deðiþtirilebilir.
	int const** ptr = &p; // burada ise ptr'nin ve p'nin deðerleri deðiþtirilebilir. Fakat x'in deðerinde deðiþiklik yapýlamaz.
	int y = 40;
	int z = 20;
	int* a[] = { &x, &y, &z }; // þimdi öyle bir fonksiyon yazalým ki a'yý sadece okuma amaçlý kullanabilsin hiçbir deðerini
									// deðiþtiremesin.
	access_arr(a, 3);
}