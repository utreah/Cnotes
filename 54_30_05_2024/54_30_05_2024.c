
#include <stdio.h>
/*
	Bir türün tamamlanmýþ olmasý demek, derleyicinin o türün bilgilerine eriþmiþ olmasý demek. 
struct Nec { // mesela bu bir complete type. Tanýmý belli, elemanlarý belli her þeyi belli.
	int x, y, z;
};

struct Eng; // Burada derleyiciye nesnenin varlýðýnýn haberini veriyor fakat bildirmi hakkýnda bir bilgi yok. -> Incomplete type.
	CPP'de buna forward declaration deniyor. C'de Incomplete declaration

													/-				Incomplete Type ile neler yapýlabilir?				 -\
	1-) Bir fonksiyonun parametre deðiþkeninin türü, geri dönüþ deðerinin türü incomplete type olabilir. Bu sadece bildirim için geçerli tanýmlamada(definition) bu geçerli deðil.
		struct Eng;
		struct Erg;

		struct Nec	foo(struct Eng); // hata yok.
		struct Nec* bar(struct Eng*); // hata yok.

	2-) typedef bildirimlerinde de kullanýlabilirler.
		typedef struct Eng Eng;
		typedef struct Eng* EngPTR;

	3-) Bu türden bir pointer deðiþken tanýmlanabilir.
		struct Data;
		struct Data* foo(void);
		struct Data* bar(struct Data* ptr);
		int main(void){
			struct Data* mydataptr;  NULL pointerda atanabilir.	
			 neden sentaks hatasý deðil? Aslýnda sebebi çok basit. Pointerlar için sizeof deðeri belli benim derleyicimde bir object pointer 8 byte yer kaplýyor.
				 eðer mydataptr'ý derefence eder isem bu sentaks hatasý olur hatta derleyici "tanýmsýz 'Data' türü kullanýldý." diye hata verir.

			mydataptr = foo();  sentaks hatasý yok. 
			bar(mydataptr);  sentaks hatasý yok.

			 derefencing söz konusu olmadýðý sürece sentaks hatasý almayýz.
		}

	4-) extern bildirim yapýlabilir. -> Bunlara non-defining declaration deniyor.
		struct Nec;
		extern struct Nec x;  derleyici extern için compile time'da yer ayýrmayacak. extern keywordü bildirilen deðiþkenin baþka bir modülde
				global olarak tanýmlandýðýný söylüyor bize.
		 x nesnesine ne kadar yer ayýrýlacaðýný bilmediði için, gerekte duymuyor, ondan dolayý incomplete type olmasýna ve pointer nesnesi olmamasýna raðmen
			hiçbir sentaks hatasýyla karþýlaþmayacaðýz.


													/-				Incomplete type nerede kullanýlmaz?				-\
	1 - Incomplete type türden nesne tanýmlanamaz.
		struct Nec;
		int main(void){
			struct Nec x; // Bu nesne tanýmlanamaz. Çünkü, derleyici struct Nec'in elemanlarýný göremediði için bellekte ne kadar alan ayýracaðýný bilemeyecek. 
		}
	2 - sizeof operatörünün operandý olamaz.
		struct Eng;
		struct Nec{
			int x, y, z;
		};
		int main(void){
			 
			printf("%zu" , sizeof(struct Eng)); // bu hatalý çnkü Eng bir incomplete  type var sizeof'un operandý olamaz.
			printf("%zu" , sizeof(struct Nec)); // bu da derleyiciye baðlý bir deðer döndürür ben de 12
		}
	3 - Pointer'ýn derefence edildiði ifade de kullanýlamaz. (subscript, içerik)
		extern struct Nec gnec; // hata yok
		int main(void){
			struct Nec* p = &gnec; // buraya kadar bir sýkýntý yok legal.
			*p; // burada sentaks hatasý var incomplete type nesneler derefence edilemez. Aþaðýdakilerde de ayný durum geçerli.
			*p[2]; 
			p->x;
			(*p).x;
		}
	4 - Baþka bir struct'ýn elemaný olamazlar.
		struct Nec;

		struct Eng{
			struct Nec nec; // error, pointer olmadýðý sürece bu sentaks hatasý çünkü allocate edilmesi gerekilen memory boyutu bilinmiyor.
		};


	5 - Bir yapýnýn elemaný kendi türünden olamaz.!!
		struct Nec{
			struct Nec nec; // O LA MAZ https://www.youtube.com/watch?v=xvFZjo5PgG0
				// Burada struct Nec hala incomplete durumunda. Sentaks hatasý
		};
	6 - Bir yapýnýn elemaný kendi türünden POINTER olabilir.
		// Çok kullanýlan bir kullaným þekliymiþ bu. Linked List, Trees, Graph gibi bir çok veri yapýsýnda implementasyon tarafýnda böyle bir birim kullanýlýyor.
			// bunlara 'node' deniyor. 
		struct Eng{
			int data;
			struct Eng* myeng; // bu olabilir iþte legal. Çünkü myeng'in byte deðeri belli -> bu bir node(düðüm)
		}; // bunlara ayný zamanda 'self-referential structure' deniyor.
	
*/

// Student.h baþlýk dosyasý oluþturuldu.
#include "Student.h"
int wcmpstudent(const void* vp1, const void* vp2) { // callback fonksiyonumuz. Ýþlevi þu. qsort fonksiyonuna bir compare fonksiyonun adresini geçmemiz gerkeiyor.
		// fakat cmp_student'ýn parametre deðiþkenlerinin türü Student* olduðundan onu kapsayabilmesi için bu fonksiyonu oluþturduk. BUna da callback fonksiyon deniyor.

	/*	Bir fonksiyon çalýþmasýný tamamladýktan sonra baþka bir 
	fonksiyonun çalýþmasýný saðlayan fonksiyonlara callback fonksiyon denir. */
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