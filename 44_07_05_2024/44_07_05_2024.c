#include <stdio.h>
// foo �a�r�ld���n daha �nce kaydedilen fonksiyonlar� �a��racak
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
	// burada yap�lan i�lemler implementasyona g�re de�i�ebilir. 
}
// void (*fp)() -> parametre k�sm� bo� b�rak�l�rsa, C dilinde, parametre hakk�nda bilgi verilmiyor demek. Daha �nce g�rm��t�k zaten
void baz(double);
void bar(int);
void foo2(int, double);
int main(void) {

	void (*fp)(int) = &baz; // derleyici hata verecek. ��nk� fp fonksiyon pointeri geri d�n�� de�eri void olan, 
								// parametre de�i�kenleri int t�r�nden olan bir fonksiyon istiyor. bar'�n parametresi double.

	void (*fp2)() = &baz;
	void (*fp2)() = &bar;
	void (*fp2)() = &foo2;
		// yukar�daki �� �rnekte ise hi�bir s�k�nt� yok. ��nk� fp2 fonksiyon pointer�nda parametre de�i�keni hakk�nda bilgi vermedi�imiz
			// i�in s�k�nt�s�z derlenir.
}
///////////////////////////////////////////////////////


//													MULTI DIMENSIONAL ARRAYS
//														�OK BOYUTLU DIZILER
int main(void) {
	// C'de �ok boyutlu diziler yoktur.
	
	int a[10][20]; // bu �ekilde bir tan�mlama yap�labiliyor ama bunun anlam�
		// a bir dizi elemanlar� int[20]
	int x[20]; // a'n�n elemanlar� int, farklar� bu asl�nda.
		// Yani a'n�n i�erisinde x gibi olan 10 adet eleman var. -> a = {x[20], x[20], x[20], x[20], x[20], x[20], x[20], x[20], x[20], x[20]}
			// anlamam i�in o �ekilde, g�rsel olsun diye, yazd�m.	

	// Daha �nce ��rendi�imiz bir bilgi. a[10][20] bir bellek blo�udur hepsi ayn� yerdedir. S�ral� olma garantisi vard�r.
		// ��renmi�tik daha �nce bunu "B�T�N D�Z�LER BELLEKTE TEK B�R BLOK OLMAK ZORUNDA."

	sizeof(int); // 4 Byte
	sizeof(a); // a'n�n boyutu 800byte. ��nk� int 4 byte, 4 * 10 = 40, bu �ekilde 20 adet dizi var bu da 4 * 10 * 20 = 800 BYTE.
	sizeof(a[0]); // 80 Byte,
	sizeof(a[0][0]); // 4 Byte,
/*
	a[5][10][15];
	a n�n elemanlar� b[10][15] gibi diziler
	b nin elemanlar� c[15] gibi diziler
	c nin elemanlar� int x; gibi de�i�kenler.
*/

	int b[5][4];
	int arr[10]
	
	int* p = b[2]; // Legal, ��nk� b[2] dedi�imizde array decaye u�rar. b[2] asl�nda b dizisinin 3. eleman� olan diziyi g�steriyor.
						// bundan dolay� da &b[2][0]; �eklini al�r. E�er '�ok boyutlu dizi' olmasayd� array decay olmaz
							// hata verirdi.
	//  int* p = b[2] -> int* p = &b[2][0

	int* p = b; // YANLI�! ��nk� ben p'yi bir artt�rd���mda 'p++' dizinin bir sonraki eleman�na ge�mesi i�in 16byte ilerlemesi gerek
					// fakat int d�rder d�rder ilerledi�i i�in bu olmaz, derleyici hata verir.
				// a tek boyutlu olsayd� array decay ilk eleman�n adresini �eviriyor.
					// ilk eleman int t�rden.adreside int* t�rden.bu y�zden array decay sorun ��karmaz.

	int* p = arr; // burada s�k�nt� yok ��nk� arr dizisi �ok boyutlu dizi de�il. Dizinin sonraki eleman�na s�k�nt�s�z ge�er

	// PEK� NASIL �OK BOYUTLU D�Z�'Y� B�R POINTER DE���KEN�NE ATAYAB�L�R�Z?
		// de�i�kenin t�r� (*idf)[] �eklinde tan�mlayabiliriz.
	int(*ptr)[4] = b; // Art�k bu legal ve �al���r. BU AYRI BIR POINTER T�R�
	///////////////////////////////////////////////////////////////
	int a[5] = { 1, 2, 3, 4, 5 };
	// �imdi �yle bir pointer de�i�keni yazal�m ki derefence edildi�inde 'a' de�i�keni olsun.

	int (*ptr)[5] = a; // BU YANLI�!!!!  
	int (*ptr)[5] = &a; //  Bu �ekilde olmas� gerekiyor, bize a'n�n adresi gerekli, ilk eleman�n�n adresi de�il.

	////////////////////////////////////////////////////

	// �ok boyutlu dizide nas�l ilk de�er verilir?
	int ARR[2] = { 1, 2 }; // Bu 2 elemanl� bir diziye ilk de�er verme
	int mdARR[2][4] = { {1,2,3,4}, {5,6,7,8} }; // Bu elemanlar� 4 elemanl� dizi olan bir diziye ilk de�er verme
	int mdARR[2][4] = { 1,2,3,4, 5,6,7,8 }; // bu da bir �stteki dizi gibi LEGAL. Derleyici s�ras�yla dizilere da��tacak tek tek
	
	// designated initiliazor
	int mdARR2[5][4] = {
		[1] = { [2] = 31},
		[2] = {1, 2, 3, 4},
		[4] = {2, 4, 6, 8} };

	////////////////////////////////////////////////////

//	M�LAKAT SORUSU
	int a[][] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int b[3][] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int c[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	// a ve b illegal, c legal.
		// Bir dizinin elemanlar�n�n t�r�n� yazmak zorundas�n.
			// a dizisinde ne dizinin boyutu ne de elemanlar�n�n t�r� belli de�il.
			// b dizisinde dizinin boyutu belli ama elemanlar�n�n t�r� belli de�il
			// c dizisinde dizinin boyutu belli de�il, �nemli de de�il, ELEMANLARININ T�R� BELL�.
	// Yukar�da ��renmi�tik nas�l da��t�ld���n�. K�sa bir mant�kla, a dizisinde bir dizinin ka� eleman alaca��n� kestiremeyiz,
		// b dizisinde 3 adet eleman oldu�u s�yleniyor fakat elemanlar�n t�r� belli de�il. Diyelim ki, b[0] t�m diziyi ald�
			// eleman dizinin boyutu belli olmad��� i�in daha ne kadar de�er alablece�i belli de�il.
		// c dizisinde ise dizinin boyutu ne kadar b�y�rse b�y�s�n, eleman dizinin boyutu her zaman 3 olarak kalacak. En fazla 3 eleman
			// tutabilecek.

int mdARR2[5][4] = {
	[1] = { [2] = 31},
	[2] = {1, 2, 3, 4},
	[4] = {2, 4, 6, 8} };

	int* ptr = a[0];
	int* ptr = &a[0][0];
	int* ptr = (int*)a; // normalde uyar� mesaj� veriyor ama (int*)'a cast ederek yap�yoruz.
	// Bu �� g�sterim de DO�RU
	int a[5][10];
	randomize();

	set_random_array((int*)a, 5 * 10); // a n�n adresi ile s�ral� olarak atama yap�labiliyor.Yukar�da yazm��t�k.
	// 5 * 10 da eleman say�s�.
	// iki boyutlu diziler tek boyutlu gibi atama yap�labiliyor.
	void set_matrix_5(int(*a)[5], int size){
		for (int i = 0; i < size; i++) {
			for (int k = 0; k < 5; k++)
				a[i][k] = rand() % 10;
			printf("\n");
		}
	}
	/////////////////////////////////////////////////////
	//�OK �NEML�
	void f1(int(*ptr1)[10], int size);	// a dizisinin g�nderilebilece�i dizi
	void f2(int(*ptr1)[8], int size);	// b dizisinin g�nderilebilece�i dizi
	void f3(int(*ptr1)[40], int size); // c dizisinin g�nderilebilece�i dizi
	//	A�a��daki dizilerin t�rleri ayn� m� farkl� m� ?
	int a[5][10];
	int b[4][8];
	int c[6][40];
	int d[3][10];
	f1(a, 5);
	f2(b, 4);
	f3(c, 6);
	f1(d, 3); // d'nin  boyutu 3, elemanlar�n�n t�r� a ile ayn�.
	/*
	FARKLI.
		��nk� elemanlar�n t�rleri farkl�.
		a nin elemanlar�, elemanlar� 10 elemanl� int dizi olan diziler
		b nin elemanlar�, elemanlar� 8 elemanl� int dizi olan diziler
		c nin elemanlar�, elemanlar� 40 elemanl� int dizi olan diziler

		int a[5][10]; ve int c[3][10]; olsayd� ayn� t�rden olacakt�.

		MATR�S D�YE GENEL B�R T�R YOK.
	*/
	///////////////////////////////////////////////////////////////////////////////
	
	void set_matrix(int* p, int row, int col) {
		for (int i = 0; i < row; ++i) {
			for (int k = 0; k < col; k++) {
				p[i * col + k] = rand % 10; // burada neden p[i][k] kullanmad�k??
			}									// Sebebi �ok basit, set_matrix parametrelerinden int* p sadece p[] ile g�sterilebilir.
											// set_matrixe g�nderirken int* t�r�ne cast etti�imiz i�in bu �ekilde.
											// ki zaten dizilerin s�ral� olma garantisi ve pointer aritmeti�i kullanarak matrixe s�ras� ile
		}									//atama yapabiliyoruz. Derleyici bunu (row * col) b�y�kl���nde bir dizi olarak yorumlayacak.
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

		set_matrix(a, 4, 8); // Bu yanl��. Do�ru �ekli a�a��daki gibi olmal�.
		set_matrix((int*)a, 4, 8); // bunun sebebi t�r uyu�mazl���ndan dolay�
		set_matrix(a[0], 4, 8); // Do�ru
		set_matrix(&a[0][0], 4, 8); // Do�ru
		
	}
	/*
	int a[5]; bunun t�r� int*;
	int* ptr = a;

	&a n�n t�r� int(*)[5] tir
		int(*p)[5] = &a;  do�ru kullan�md�r.
	*/
}

///////////
FONKS�YONLARI HER SEFER�NDE KEND�M�Z YAZAB�L�R�Z AMA DAHA KISA B�R YOLUDA VAR.
MACRO KONUSUNDA FUNCTION YAZDIRMI�TIK.BENZER �EY� BURADA DA YAPACA�IZ.

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
	int d[5][6];// bu yukar�daki ile ayn� t�rden.yani ayn� fonksiyona g�nderilebilir.

	grsa_20(a, 10);
	grsa_8(a, 5);
	grsa_6(a, 4);
}
HEM SET EDEN HEMDE YAZDIRAN KOD A�A�IDA.

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
print etmenin birs�r� yolu var.

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



/* Bu alttaki g�sterimlerin hepsi do�ru
void foo(int* p, int size) == void foo(int p[], int size)
void bar(int** p, int size) == void bar(int* p[], int size)
void baz(int (*p)[10], int size) == void baz(int p[][10], int size)
*/
/*
typedef ile kullan�m�

typedef int INTA10[10];

typedef int INTA10[10];

INTA10 a[5]; // BU tan�m a[5][10] demek.


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
t�m illerdeki ve t�m aylardaki ve g�nlerdeki s�cak de�erlerini tutan dizi
double grades[81][12][30];
t�r� double(*)[12][30];
////////////////////

