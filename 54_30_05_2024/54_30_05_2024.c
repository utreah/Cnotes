
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
/*
#include "Student.h"
int wcmpstudent(const void* vp1, const void* vp2) { // callback fonksiyonumuz. ��levi �u. qsort fonksiyonuna bir compare fonksiyonun adresini ge�memiz gerkeiyor.
		// fakat cmp_student'�n parametre de�i�kenlerinin t�r� Student* oldu�undan onu kapsayabilmesi i�in bu fonksiyonu olu�turduk. BUna da callback fonksiyon deniyor.

	/*	Bir fonksiyon �al��mas�n� tamamlad�ktan sonra ba�ka bir 
	fonksiyonun �al��mas�n� sa�layan fonksiyonlara callback fonksiyon denir. 
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
*/
// Incomplete type kullanman�n bir y�ntemi daha var.
	// Bir struct i�erisindeki memberlardan bir tanesi ba�ka bir yap� t�r�ne ait nesne olabilir. Bunu zaten ��rendik.
		// nested struct diye bir bi�im var. Ba�ka bir yap� t�r�nden tan�mlad���m�z o member�n struct�n� direkt member� oldu�u struct�n i�inde tan�mlayabiliriz.
			// �ok kafa kar��t�r�c� 
/*
struct Nec {
	int x, y, z;
};

struct Erg {
	int a, b, c;
	struct Nec enec;
};
// struct Nec ve Erg t�r�nden iki nesnemiz var. Struct erg'in i�inde struct Nec t�r�nden bir nesne tan�mlanm��. Bu �ekilde tan�mlayabildi�imiz gibi ba�ka bir y�ntem daha var.
	
struct Erg {
	int a, b, c;
	struct Nec {
		int x, y, z;
	}enec;
};
// Buna 'nested struct' deniyor. Eri�im �ekli gene ayn�. bErg'in Erg t�r�nden bir nesne oldu�unu kabul edelim.
	// bErg.enec.x; bu �ekilde bir fark yok yani.

	// struct Nec'in scope'u struct Erg'in scope'u ile ayn�. Erg'in g�r�ld���, kullan�ld��� her yerde Eng'te kullan�labilir. Nested olmas� farkl�l�k olu�turmaz.
		// bu �zellik C de ge�erli CPP'de ge�ersiz.
	// nested struct�n kullan�lma sebebi, member olarak tan�mlanan struct�n sadece tan�mland��� struct taraf�ndan kullan�laca�� anlam�na geldi�ini vurgulamak i�in yap�l�yor.
	// ��eride tan�mlanan yap�n�n ismi olmak zorunda de�il. �simsiz de tan�mlanabilir. (struct Nec yerine sadece struct)

struct Erg {
	int x, y, z;
	struct {
		int a, b, c;
	}enec;
};

int main(void) {
	struct Erg myerg;
	myerg.enec.a; 
}
// Erg struct'�n�n sizeof de�eri 24. x y z = 12 byte, a b c = 12 byte toplamda 24byte


struct Erg {
	int x, y, z;
	struct {
		int a, b, c;
	}; // bu k�s�mda nesne tan�m�n� yapmaz isek bu struct'�n i�erisindeki memberlara direkt eri�ilebilir.
};

int main(void) {
	struct Erg myerg;
	myerg.a;
	myerg.b;
	myerg.c;
} // hepsine direkt olarak eri�ebiliyorum art�k bunun sebebini ileride ��renicez
*/

/*------------------------------------------------------------*/
// Bir yap� t�r�n�n member� kendi t�r�nden bir pointer nesnesi olabilir.

struct Nec {
	//..
	struct Nec* ptr; // bu tarz yap�lara self referencial structures deniyor.
};

/*
	Ne i�e yar�yor bu?
	- Ba�ka bir struct Nec nesnesinin adresini tutabilirler.
		Diziler contigous oldu�u i�in ek bir i�lem yapmadan sadece bellekte + sizeof(type) �eklinde ilerleyerek eri�ebiliyorduk. Burada da o devaml�l���
			sa�lamak i�in ayn� yap� t�r� nesnelerinin adresleri tutulup bir dizi i�lemde rol ald�r�labilir. -> Linked list bu �ekilde implemente ediliyor.
				


	LINKED LIST(BA�LI D�Z�LER)
		Veri yap�s�nda tutulan yap�yla bir ya da iki tane pointer� bir arada tutan yap�ya node(d���m) denir. 
			Diyelim ki bir tane dinamik olarak allocate edilmi� dizi var. Node'un i�erisinde bir nesne o dinamik dizinin ilk elemanan�n de�erini tutarken
				i�erisindeki di�er pointer t�r�nden olan nesne sonraki dizinin eleman�n�n bulundu�u node'un adresini tutuyor. Bu �ekilde olu�turulan yap�lara Linked List denir.
	
	Dinamik dizi vs Linked List
	- E�er belirli bir indexteki elemana eri�mek istiyorsak; Dinamik dizi O(1) karma��kl���na sahip.
		Linked List ise O(n) karma��kl��na sahip. ��nk� Linked Listte eri�mek istedi�imiz list'e gidene kadar o yoldaki her node'a girmeliyiz.
	- De�er ararken ikisi de ayn� karma��kl��a sahip(e�er bir d�zenleme vs s�z konusu de�il ise)
	- Dinamik �m�rl� bir nesneden de�er eklenmesi ve ��kar�lmas� durumunun constant time sadece sondan oldu�unda s�z konusu.
		Fakat, ba�l� listede eklenecek/��kar�lacak konuma ili�kin pointerler var ise nereden ekleme/��karma yaparsak yapal�m Constant Time. Sadece pointerin de�erini de�i�tirerek 
			bu de�i�imi yapabiliriz.
	- Linked list alan konusunda tam bir felaket. Bellek kullan�m� a��r� fazla. Her veriyi tutmak i�in bir d���m olmas� gerekiyor her d���m�n i�erisinde de 1 tane pointer var.
		8 elemanl� bir char dizisi i�in 8 byte alan gerekirken Linked listte bu de�er 8 * sizeof(char*) + 8 * sizeof(char) oluyor. Benim derleyicimde bu 72Byte'a tekab�l ediyor.
			8 byte nere 72 byte nere.

		Singly Linked List
			- E�er d���m�n i�erisinde 1 adet pointer nesnesi var ise ve sonraki d���me i�aret ediyor ise sadece tek y�nl� hareket edebilirsiniz demek bu. 
				Soldan -> Sa�a gibi. Gidiyorsun ama gelemiyorsun.
		Doubly Linked List
			- Yani singly bir ise doubly 2 pointer nesnesi oldu�u anlam�na geliyor. ��erisin de iki pointer nesnesi tutuyor. Bu sayede iki y�nde de hareket edebilir. Bir pointer
				sonraki d���m�, di�eri de �nceki d���m� g�sterebilir. Maaliyet iyiyce artt� ��nk� art�k 2 * sizeof(T*) + sizeof(T) aboooo
	- Her ne kadar linked listte constant time ile ekleme ��karma yapabiliyor olsakta belirli bir eleman say�s�na kadar dinamik bellek daha avantajl�. �ki sebebi var bunun
		1 - �n bellek mekanizmas� (s�k eri�ilen bellek bloklar�n�n �n belle�e al�nmas�) Linked listte birbirine ba�l� olan d���mler ard���k olsa da ayn� bellek �zerinde
			bulunmuyor. Bundan dolay� Cache hit olay� �oook d���k. 
		2 - vektorizasyon komutlar�


	Ba�l� listenin avantajlar�;
		1 - Fragmentation: Daha �nce g�rm��t�k bunu k�sacas� kullan�lan her belle�in contigous olmas� de�ilde par�a par�a �eklinde olmas� durumu.
			Biz memory allocation yaparken n * sizeof(T) kadarl�k bir bellek blo�u ar�yoruz ve contigous olma garantisi var. K���k bellek allocationlar� i�in bu durum ok olabilir
				ama 40000Byte'l�k bir dinamik bellek alan� allocate ederken 40k Byte'l�k contgious bo� bir bellek alan� bulmak biraz zor. Linked List'in contigous olma zorunlulu�u olmad��� i�in
					bir node'u allocate edebildi�i s�rece "dewamke" modunda gidiyor. �sterse birisi New York'ta tan�ml� olsun di�eri Dubai de. Adresi sahip oldu�umuz s�rece s�k�nt� yok.
		2 - Boyutu b�y�k olan veri yap�lar�nda swap i�leminde avantaj sa�lar. 120Byte'l�k bir student struct'� oldu�unu d���nelim. 2 struct Student t�r�nden nesneyi takas ederken 3 kere
			kopyalama i�lemi yap�lacak bu ada 120 * 3 = 360 bytel�k kopyalama i�lemi demek. Bunu yapmak yerine nodelar�n g�sterdi�i pointerlar swaplan�rsa maaliyet �ok daha fazla d���k
				olur. 
		3 - 2 dinamik dizi ve 2 linked list oldu�unu d���nelim. Bir diziden ald���m de�eri silip ikinci diziye aktarmak istedi�im de lineer karma��kl�kta bir algoritma
			�al��t�rmam gerek 2 kez. Fakat, linked listte silmek istedi�im d���m� tamamen silmek yerine sadece o linked list ile ili�kisini kesmem ve di�er list'e ba�lamam yeterli.
		


	- Linked list'in ilk d���m�n�n adresi bir yerde tutulmal� yoksa di�er nodelara eri�emeyiz.
*/

#include "Student.h"
// Singly linked list
	// typedef keyword� ile bildirilse bile i�erisindeki SNode* nesnesinin ba��nad struct bulunmas� zorunda.
typedef struct SNode {
	Student data;
	struct SNode* pnext;
}SNode;

// Doubly Linked List
	// typedef keyword� ile bildirilse bile i�erisindeki SNode* nesnesinin ba��nad struct bulunmas� zorunda.
typedef struct DNode {
	Student data;
	struct DNode* pprev;
	struct DNode* pnext;
}DNode;

// Son d���me geldi�imizi nas�l anlayaca��z.
	//E�er singly linked list ise pointer de�i�keni NULL pointer olmal�.
	//E�er doubly linked list ise sonraki d���m� g�steren pointer de�i�keni NULL pointer olmal�.
// �lk d���m�n adresini tutan de�i�kene ANCHOR denir.
// Doubly Linked Listte ilk ve son d���m�n adresleri tutulur.
	// Son d���m�n adresini sona constant time'da d���m eklemek i�in yap�yoruz.



/*
	��rencilerin bir veri yap�s� olsun.
	Ekleme ve silme i�lemleri ba�tan yap�l�yor
*/
#include "stdio.h"
#include "StudentList.h"
#include "Student.h"
#include "nUtility.h"
int main(void) {

	randomize();
	int n = rand() % 10 + 10;

	Student s;

	for (int i = 0; i < n; i++) {
		set_random_student(&s);
		push_front(&s);
	}
	Student* p = &s;
	while (!is_empty()) {
	printf("Listede %zu ogrenci var\n", get_size());
		printf("Listedeki ilk ogrenci :\n");
		print_list();
		pop_front();
		(void)getchar();
		system("cls");
	}
}