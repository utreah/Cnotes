
#include <stdio.h>
/*
	Bir t�r�n tamamlanm�� olmas� demek, derleyicinin o t�r�n bilgilerine eri�mi� olmas� demek. 
struct Nec { // mesela bu bir complete type. Tan�m� belli, elemanlar� belli her �eyi belli.
	int x, y, z;
};

struct Eng; // Burada derleyiciye nesnenin varl���n�n haberini veriyor fakat bildirmi hakk�nda bir bilgi yok. -> Incomplete type.
	CPP'de buna forward declaration deniyor. C'de Incomplete declaration

													/-				Incomplete Type ile neler yap�labilir?				 -\
	1-) Bir fonksiyonun parametre de�i�keninin t�r�, geri d�n�� de�erinin t�r� incomplete type olabilir. Bu sadece bildirim i�in ge�erli tan�mlamada(definition) bu ge�erli de�il.
		struct Eng;
		struct Erg;

		struct Nec	foo(struct Eng); // hata yok.
		struct Nec* bar(struct Eng*); // hata yok.

	2-) typedef bildirimlerinde de kullan�labilirler.
		typedef struct Eng Eng;
		typedef struct Eng* EngPTR;

	3-) Bu t�rden bir pointer de�i�ken tan�mlanabilir.
		struct Data;
		struct Data* foo(void);
		struct Data* bar(struct Data* ptr);
		int main(void){
			struct Data* mydataptr;  NULL pointerda atanabilir.	
			 neden sentaks hatas� de�il? Asl�nda sebebi �ok basit. Pointerlar i�in sizeof de�eri belli benim derleyicimde bir object pointer 8 byte yer kapl�yor.
				 e�er mydataptr'� derefence eder isem bu sentaks hatas� olur hatta derleyici "tan�ms�z 'Data' t�r� kullan�ld�." diye hata verir.

			mydataptr = foo();  sentaks hatas� yok. 
			bar(mydataptr);  sentaks hatas� yok.

			 derefencing s�z konusu olmad��� s�rece sentaks hatas� almay�z.
		}

	4-) extern bildirim yap�labilir. -> Bunlara non-defining declaration deniyor.
		struct Nec;
		extern struct Nec x;  derleyici extern i�in compile time'da yer ay�rmayacak. extern keyword� bildirilen de�i�kenin ba�ka bir mod�lde
				global olarak tan�mland���n� s�yl�yor bize.
		 x nesnesine ne kadar yer ay�r�laca��n� bilmedi�i i�in, gerekte duymuyor, ondan dolay� incomplete type olmas�na ve pointer nesnesi olmamas�na ra�men
			hi�bir sentaks hatas�yla kar��la�mayaca��z.


													/-				Incomplete type nerede kullan�lmaz?				-\
	1 - Incomplete type t�rden nesne tan�mlanamaz.
		struct Nec;
		int main(void){
			struct Nec x; // Bu nesne tan�mlanamaz. ��nk�, derleyici struct Nec'in elemanlar�n� g�remedi�i i�in bellekte ne kadar alan ay�raca��n� bilemeyecek. 
		}
	2 - sizeof operat�r�n�n operand� olamaz.
		struct Eng;
		struct Nec{
			int x, y, z;
		};
		int main(void){
			 
			printf("%zu" , sizeof(struct Eng)); // bu hatal� �nk� Eng bir incomplete  type var sizeof'un operand� olamaz.
			printf("%zu" , sizeof(struct Nec)); // bu da derleyiciye ba�l� bir de�er d�nd�r�r ben de 12
		}
	3 - Pointer'�n derefence edildi�i ifade de kullan�lamaz. (subscript, i�erik)
		extern struct Nec gnec; // hata yok
		int main(void){
			struct Nec* p = &gnec; // buraya kadar bir s�k�nt� yok legal.
			*p; // burada sentaks hatas� var incomplete type nesneler derefence edilemez. A�a��dakilerde de ayn� durum ge�erli.
			*p[2]; 
			p->x;
			(*p).x;
		}
	4 - Ba�ka bir struct'�n eleman� olamazlar.
		struct Nec;

		struct Eng{
			struct Nec nec; // error, pointer olmad��� s�rece bu sentaks hatas� ��nk� allocate edilmesi gerekilen memory boyutu bilinmiyor.
		};


	5 - Bir yap�n�n eleman� kendi t�r�nden olamaz.!!
		struct Nec{
			struct Nec nec; // O LA MAZ https://www.youtube.com/watch?v=xvFZjo5PgG0
				// Burada struct Nec hala incomplete durumunda. Sentaks hatas�
		};
	6 - Bir yap�n�n eleman� kendi t�r�nden POINTER olabilir.
		// �ok kullan�lan bir kullan�m �ekliymi� bu. Linked List, Trees, Graph gibi bir �ok veri yap�s�nda implementasyon taraf�nda b�yle bir birim kullan�l�yor.
			// bunlara 'node' deniyor. 
		struct Eng{
			int data;
			struct Eng* myeng; // bu olabilir i�te legal. ��nk� myeng'in byte de�eri belli -> bu bir node(d���m)
		}; // bunlara ayn� zamanda 'self-referential structure' deniyor.
	
*/

// Student.h ba�l�k dosyas� olu�turuldu.
#include "Student.h"
int wcmpstudent(const void* vp1, const void* vp2) { // callback fonksiyonumuz. ��levi �u. qsort fonksiyonuna bir compare fonksiyonun adresini ge�memiz gerkeiyor.
		// fakat cmp_student'�n parametre de�i�kenlerinin t�r� Student* oldu�undan onu kapsayabilmesi i�in bu fonksiyonu olu�turduk. BUna da callback fonksiyon deniyor.

	/*	Bir fonksiyon �al��mas�n� tamamlad�ktan sonra ba�ka bir 
	fonksiyonun �al��mas�n� sa�layan fonksiyonlara callback fonksiyon denir. */
	return cmp_student((const Student*)vp1, (const Student*)vp2);
}
int main(void) {
	size_t n;
	printf("Kac Ogrenci? :");
	(void)scanf("%zu", &n);

	Student* studentmalloc = (Student*)malloc(sizeof(Student) * n);
	if (!studentmalloc) {
		fprintf(stderr, "Bellek alani yetersiz!");
		return 1;
	}
	for (size_t i = 0; i < n; i++)
		set_random_student(studentmalloc + i);
	clock_t clStart = clock();
	printf("Siralama Basladi\n");
	qsort(studentmalloc, n, sizeof(Student), wcmpstudent);
	clock_t clEnd = clock();
	printf("Siralama Bitti! Gecen Sure: %f", (double)(clEnd - clStart) / CLOCKS_PER_SEC);
	clear_input_buffer();
	(void)getchar();

	for (size_t i = 0; i < n; i++) {
		print_student(studentmalloc + i);
	}
	free(studentmalloc);
} 
// 1:10