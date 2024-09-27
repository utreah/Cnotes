#include <stdio.h>
// foo çaðrýldýðýn daha önce kaydedilen fonksiyonlarý çaðýracak
#define max_number_of_functions 10
typedef void (*FPTR)(void);
static FPTR gfa[max_number_of_functions] = {0};
static gcount = 0;
void reg_func(FPTR f) {
	if (gcount == max_number_of_functions)
		return;
	gfa[gcount++] = f;
}

void foo(void) {
	for (int i = 0; i < gcount; i++)
		gfa[i]();
}

void f1(void) { printf("F1 CAGRILDI\n"); }
void f2(void) { printf("F2 CAGRILDI\n"); }
int main(void) {
	printf("1. foo cagrisi\n");
	foo();
	reg_func(&f1);
	reg_func(&f2);
	printf("2. foo cagrisi\n");
	foo();
	// burada yapýlan iþlemler implementasyona göre deðiþebilir. 
}
// void (*fp)() -> parametre kýsmý boþ býrakýlýrsa, C dilinde, parametre hakkýnda bilgi verilmiyor demek. Daha önce görmüþtük zaten
void baz(double);
void bar(int);
void foo2(int, double);
int main(void) {

	void (*fp)(int) = &baz; // derleyici hata verecek. Çünkü fp fonksiyon pointeri geri dönüþ deðeri void olan, 
								// parametre deðiþkenleri int türünden olan bir fonksiyon istiyor. bar'ýn parametresi double.

	void (*fp2)() = &baz;
	void (*fp2)() = &bar;
	void (*fp2)() = &foo2;
		// yukarýdaki üç örnekte ise hiçbir sýkýntý yok. Çünkü fp2 fonksiyon pointerýnda parametre deðiþkeni hakkýnda bilgi vermediðimiz
			// için sýkýntýsýz derlenir.
}
///////////////////////////////////////////////////////


//													MULTI DIMENSIONAL ARRAYS
//														ÇOK BOYUTLU DIZILER
int main(void) {
	// C'de Çok boyutlu diziler yoktur.
	
	int a[10][20]; // bu þekilde bir tanýmlama yapýlabiliyor ama bunun anlamý
		// a bir dizi elemanlarý int[20]
	int x[20]; // a'nýn elemanlarý int, farklarý bu aslýnda.
		// Yani a'nýn içerisinde x gibi olan 10 adet eleman var. -> a = {x[20], x[20], x[20], x[20], x[20], x[20], x[20], x[20], x[20], x[20]}
			// anlamam için o þekilde, görsel olsun diye, yazdým.	

	// Daha önce öðrendiðimiz bir bilgi. a[10][20] bir bellek bloðudur hepsi ayný yerdedir. Sýralý olma garantisi vardýr.
		// öðrenmiþtik daha önce bunu "BÜTÜN DÝZÝLER BELLEKTE TEK BÝR BLOK OLMAK ZORUNDA."

	sizeof(int); // 4 Byte
	sizeof(a); // a'nýn boyutu 800byte. Çünkü int 4 byte, 4 * 10 = 40, bu þekilde 20 adet dizi var bu da 4 * 10 * 20 = 800 BYTE.
	sizeof(a[0]); // 80 Byte,
	sizeof(a[0][0]); // 4 Byte,
/*
	a[5][10][15];
	a nýn elemanlarý b[10][15] gibi diziler
	b nin elemanlarý c[15] gibi diziler
	c nin elemanlarý int x; gibi deðiþkenler.
*/

	int b[5][4];
	int arr[10]
	
	int* p = b[2]; // Legal, çünkü b[2] dediðimizde array decaye uðrar. b[2] aslýnda b dizisinin 3. elemaný olan diziyi gösteriyor.
						// bundan dolayý da &b[2][0]; þeklini alýr. Eðer 'çok boyutlu dizi' olmasaydý array decay olmaz
							// hata verirdi.
	//  int* p = b[2] -> int* p = &b[2][0

	int* p = b; // YANLIÞ! çünkü ben p'yi bir arttýrdýðýmda 'p++' dizinin bir sonraki elemanýna geçmesi için 16byte ilerlemesi gerek
					// fakat int dörder dörder ilerlediði için bu olmaz, derleyici hata verir.
				// a tek boyutlu olsaydý array decay ilk elemanýn adresini çeviriyor.
					// ilk eleman int türden.adreside int* türden.bu yüzden array decay sorun çýkarmaz.

	int* p = arr; // burada sýkýntý yok çünkü arr dizisi çok boyutlu dizi deðil. Dizinin sonraki elemanýna sýkýntýsýz geçer

	// PEKÝ NASIL ÇOK BOYUTLU DÝZÝ'YÝ BÝR POINTER DEÐÝÞKENÝNE ATAYABÝLÝRÝZ?
		// deðiþkenin türü (*idf)[] þeklinde tanýmlayabiliriz.
	int(*ptr)[4] = b; // Artýk bu legal ve çalýþýr. BU AYRI BIR POINTER TÜRÜ
	///////////////////////////////////////////////////////////////
	int a[5] = { 1, 2, 3, 4, 5 };
	// Þimdi öyle bir pointer deðiþkeni yazalým ki derefence edildiðinde 'a' deðiþkeni olsun.

	int (*ptr)[5] = a; // BU YANLIÞ!!!!  
	int (*ptr)[5] = &a; //  Bu þekilde olmasý gerekiyor, bize a'nýn adresi gerekli, ilk elemanýnýn adresi deðil.

	////////////////////////////////////////////////////

	// Çok boyutlu dizide nasýl ilk deðer verilir?
	int ARR[2] = { 1, 2 }; // Bu 2 elemanlý bir diziye ilk deðer verme
	int mdARR[2][4] = { {1,2,3,4}, {5,6,7,8} }; // Bu elemanlarý 4 elemanlý dizi olan bir diziye ilk deðer verme
	int mdARR[2][4] = { 1,2,3,4, 5,6,7,8 }; // bu da bir üstteki dizi gibi LEGAL. Derleyici sýrasýyla dizilere daðýtacak tek tek
	
	// designated initiliazor
	int mdARR2[5][4] = {
		[1] = { [2] = 31},
		[2] = {1, 2, 3, 4},
		[4] = {2, 4, 6, 8} };

	////////////////////////////////////////////////////

//	MÜLAKAT SORUSU
	int a[][] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int b[3][] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int c[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// a ve b illegal, c legal.
		// Bir dizinin elemanlarýnýn türünü yazmak zorundasýn.
			// a dizisinde ne dizinin boyutu ne de elemanlarýnýn türü belli deðil.
			// b dizisinde dizinin boyutu belli ama elemanlarýnýn türü belli deðil
			// c dizisinde dizinin boyutu belli deðil, önemli de deðil, ELEMANLARININ TÜRÜ BELLÝ.
	// Yukarýda öðrenmiþtik nasýl daðýtýldýðýný. Kýsa bir mantýkla, a dizisinde bir dizinin kaç eleman alacaðýný kestiremeyiz,
		// b dizisinde 3 adet eleman olduðu söyleniyor fakat elemanlarýn türü belli deðil. Diyelim ki, b[0] tüm diziyi aldý
			// eleman dizinin boyutu belli olmadýðý için daha ne kadar deðer alableceði belli deðil.
		// c dizisinde ise dizinin boyutu ne kadar büyürse büyüsün, eleman dizinin boyutu her zaman 3 olarak kalacak. En fazla 3 eleman
			// tutabilecek.

int mdARR2[5][4] = {
	[1] = { [2] = 31},
	[2] = {1, 2, 3, 4},
	[4] = {2, 4, 6, 8} };

	int* ptr = a[0];
	int* ptr = &a[0][0];
	int* ptr = (int*)a; // normalde uyarý mesajý veriyor ama (int*)'a cast ederek yapýyoruz.
	// Bu üç gösterim de DOÐRU
	int a[5][10];
	randomize();

	set_random_array((int*)a, 5 * 10); // a nýn adresi ile sýralý olarak atama yapýlabiliyor.Yukarýda yazmýþtýk.
	// 5 * 10 da eleman sayýsý.
	// iki boyutlu diziler tek boyutlu gibi atama yapýlabiliyor.
	void set_matrix_5(int(*a)[5], int size){
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < 5; k++)
				a[i][k] = rand() % 10;
			printf("\n");
		}
	}
	/////////////////////////////////////////////////////
	//ÇOK ÖNEMLÝ
	void f1(int(*ptr1)[10], int size);	// a dizisinin gönderilebileceði dizi
	void f2(int(*ptr1)[8], int size);	// b dizisinin gönderilebileceði dizi
	void f3(int(*ptr1)[40], int size); // c dizisinin gönderilebileceði dizi
	//	Aþaðýdaki dizilerin türleri ayný mý farklý mý ?
	int a[5][10];
	int b[4][8];
	int c[6][40];
	int d[3][10];
	f1(a, 5);
	f2(b, 4);
	f3(c, 6);
	f1(d, 3); // d'nin  boyutu 3, elemanlarýnýn türü a ile ayný.
	/*
	FARKLI.
		çünkü elemanlarýn türleri farklý.
		a nin elemanlarý, elemanlarý 10 elemanlý int dizi olan diziler
		b nin elemanlarý, elemanlarý 8 elemanlý int dizi olan diziler
		c nin elemanlarý, elemanlarý 40 elemanlý int dizi olan diziler

		int a[5][10]; ve int c[3][10]; olsaydý ayný türden olacaktý.

		MATRÝS DÝYE GENEL BÝR TÜR YOK.
	*/
	///////////////////////////////////////////////////////////////////////////////
	
	void set_matrix(int* p, int row, int col) {
		for (int i = 0; i < row; ++i) {
			for (int k = 0; k < col; k++) {
				p[i * col + k] = rand % 10; // burada neden p[i][k] kullanmadýk??
			}									// Sebebi çok basit, set_matrix parametrelerinden int* p sadece p[] ile gösterilebilir.
											// set_matrixe gönderirken int* türüne cast ettiðimiz için bu þekilde.
											// ki zaten dizilerin sýralý olma garantisi ve pointer aritmetiði kullanarak matrixe sýrasý ile
		}									//atama yapabiliyoruz. Derleyici bunu (row * col) büyüklüðünde bir dizi olarak yorumlayacak.
	}
	;
	void print_matrix(const int* p, int row, int col) {
		for (int i = 0; i < row; i++) {
			for (int k = 0; k < col; k++)n	
				printf("%d ", p[i * col + k]);
		}
		printf("\n\n");
	}
	int main(void) {
		randomize();
		int a[4][8];
		int b[5][7];
		int c[3][40];

		set_matrix(a, 4, 8); // Bu yanlýþ. Doðru þekli aþaðýdaki gibi olmalý.
		set_matrix((int*)a, 4, 8); // bunun sebebi tür uyuþmazlýðýndan dolayý
		set_matrix(a[0], 4, 8); // Doðru
		set_matrix(&a[0][0], 4, 8); // Doðru
		
	}
	/*
	int a[5]; bunun türü int*;
	int* ptr = a;

	&a nýn türü int(*)[5] tir
		int(*p)[5] = &a;  doðru kullanýmdýr.
	*/
}

///////////
FONKSÝYONLARI HER SEFERÝNDE KENDÝMÝZ YAZABÝLÝRÝZ AMA DAHA KISA BÝR YOLUDA VAR.
MACRO KONUSUNDA FUNCTION YAZDIRMIÞTIK.BENZER ÞEYÝ BURADA DA YAPACAÐIZ.

#define		grsa(a)		void func_##a(int (*p)[a], size_t size) { \
										for(int i = 0; i < size;i++) { \
											for(int j = 0; j < a; j++) { \
												p[i][j] = rand() % 100; \
											} } }

#define		print


	func_array(20)
	func_array(8)
	func_array(6)

	int main()
{

	int a[10][20];
	int b[5][8];
	int c[4][6];
	int d[5][6];// bu yukarýdaki ile ayný türden.yani ayný fonksiyona gönderilebilir.

	grsa_20(a, 10);
	grsa_8(a, 5);
	grsa_6(a, 4);
}
HEM SET EDEN HEMDE YAZDIRAN KOD AÞAÐIDA.

#define		grsa(a)		void set_matrix_##a(int (*p)[a], size_t size) { \
										for(int i = 0; i < size;i++) { \
											for(int j = 0; j < a; j++) { \
												p[i][j] = rand() % 100; \
											} } }



#define		gpm(s)		void print_matrix_##s(int (*p)[s], size_t size) { \
											for(int i = 0; i < size; i++) { \
												for(int j = 0; j < s ; j++) { \
													printf("%3d ",p[i][j]);\
												} printf("\n"); } printf("\n\n\n");}
/////////////////////////////////////////////////////////////////////////////////////////////
print etmenin birsürü yolu var.

void print_matrix(int(*p)[4], size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			printf("%3d ", p[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void print_matrix2(int(*p)[4], size_t size)
{
	while (size--)
	{
		for (size_t j = 0; j < 4; j++)
		{
			printf("%3d ", (*p)[j]);
		}
		p++;
		printf("\n");
	}
	printf("\n\n");
}

void print_matrix3(int(*p)[4], size_t size)
{
	while (size--)
		print_array(*p++, 4);

	printf("\n\n");
}


int main()
{
	int b[5][4] = { {1,1,1,1},
					{2,2,2,2},
					{3,3,3,3},
					{4,4,4,4},
					{5,5,5,5} };

	print_matrix(b, 5);
	print_matrix2(b, 5);
	print_matrix3(b, 5);
}

////////////////////////////////////////////////////



/* Bu alttaki gösterimlerin hepsi doðru
void foo(int* p, int size) == void foo(int p[], int size)
void bar(int** p, int size) == void bar(int* p[], int size)
void baz(int (*p)[10], int size) == void baz(int p[][10], int size)
*/
/*
typedef ile kullanýmý

typedef int INTA10[10];

typedef int INTA10[10];

INTA10 a[5]; // BU taným a[5][10] demek.


*/
/*
int main()
{
    int a[5][5] = {0};
    int* ptr;
    
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++){
			ptr = &a[i][j];
			printf("a[%d][%d] = %p\n", i, j, ptr);
        }
}

*/
///////////////////
tüm illerdeki ve tüm aylardaki ve günlerdeki sýcak deðerlerini tutan dizi
double grades[81][12][30];
türü double(*)[12][30];
////////////////////

