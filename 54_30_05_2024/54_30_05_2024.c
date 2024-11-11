
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
/*
#include "Student.h"
int wcmpstudent(const void* vp1, const void* vp2) { // callback fonksiyonumuz. Ýþlevi þu. qsort fonksiyonuna bir compare fonksiyonun adresini geçmemiz gerkeiyor.
		// fakat cmp_student'ýn parametre deðiþkenlerinin türü Student* olduðundan onu kapsayabilmesi için bu fonksiyonu oluþturduk. BUna da callback fonksiyon deniyor.

	/*	Bir fonksiyon çalýþmasýný tamamladýktan sonra baþka bir 
	fonksiyonun çalýþmasýný saðlayan fonksiyonlara callback fonksiyon denir. 
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
// Incomplete type kullanmanýn bir yöntemi daha var.
	// Bir struct içerisindeki memberlardan bir tanesi baþka bir yapý türüne ait nesne olabilir. Bunu zaten öðrendik.
		// nested struct diye bir biçim var. Baþka bir yapý türünden tanýmladýðýmýz o memberýn structýný direkt memberý olduðu structýn içinde tanýmlayabiliriz.
			// çok kafa karýþtýrýcý 
/*
struct Nec {
	int x, y, z;
};

struct Erg {
	int a, b, c;
	struct Nec enec;
};
// struct Nec ve Erg türünden iki nesnemiz var. Struct erg'in içinde struct Nec türünden bir nesne tanýmlanmýþ. Bu þekilde tanýmlayabildiðimiz gibi baþka bir yöntem daha var.
	
struct Erg {
	int a, b, c;
	struct Nec {
		int x, y, z;
	}enec;
};
// Buna 'nested struct' deniyor. Eriþim þekli gene ayný. bErg'in Erg türünden bir nesne olduðunu kabul edelim.
	// bErg.enec.x; bu þekilde bir fark yok yani.

	// struct Nec'in scope'u struct Erg'in scope'u ile ayný. Erg'in görüldüðü, kullanýldýðý her yerde Eng'te kullanýlabilir. Nested olmasý farklýlýk oluþturmaz.
		// bu özellik C de geçerli CPP'de geçersiz.
	// nested structýn kullanýlma sebebi, member olarak tanýmlanan structýn sadece tanýmlandýðý struct tarafýndan kullanýlacaðý anlamýna geldiðini vurgulamak için yapýlýyor.
	// Ýçeride tanýmlanan yapýnýn ismi olmak zorunda deðil. Ýsimsiz de tanýmlanabilir. (struct Nec yerine sadece struct)

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
// Erg struct'ýnýn sizeof deðeri 24. x y z = 12 byte, a b c = 12 byte toplamda 24byte


struct Erg {
	int x, y, z;
	struct {
		int a, b, c;
	}; // bu kýsýmda nesne tanýmýný yapmaz isek bu struct'ýn içerisindeki memberlara direkt eriþilebilir.
};

int main(void) {
	struct Erg myerg;
	myerg.a;
	myerg.b;
	myerg.c;
} // hepsine direkt olarak eriþebiliyorum artýk bunun sebebini ileride öðrenicez
*/

/*------------------------------------------------------------*/
// Bir yapý türünün memberý kendi türünden bir pointer nesnesi olabilir.

struct Nec {
	//..
	struct Nec* ptr; // bu tarz yapýlara self referencial structures deniyor.
};

/*
	Ne iþe yarýyor bu?
	- Baþka bir struct Nec nesnesinin adresini tutabilirler.
		Diziler contigous olduðu için ek bir iþlem yapmadan sadece bellekte + sizeof(type) þeklinde ilerleyerek eriþebiliyorduk. Burada da o devamlýlýðý
			saðlamak için ayný yapý türü nesnelerinin adresleri tutulup bir dizi iþlemde rol aldýrýlabilir. -> Linked list bu þekilde implemente ediliyor.
				


	LINKED LIST(BAÐLI DÝZÝLER)
		Veri yapýsýnda tutulan yapýyla bir ya da iki tane pointerý bir arada tutan yapýya node(düðüm) denir. 
			Diyelim ki bir tane dinamik olarak allocate edilmiþ dizi var. Node'un içerisinde bir nesne o dinamik dizinin ilk elemananýn deðerini tutarken
				içerisindeki diðer pointer türünden olan nesne sonraki dizinin elemanýnýn bulunduðu node'un adresini tutuyor. Bu þekilde oluþturulan yapýlara Linked List denir.
	
	Dinamik dizi vs Linked List
	- Eðer belirli bir indexteki elemana eriþmek istiyorsak; Dinamik dizi O(1) karmaþýklýðýna sahip.
		Linked List ise O(n) karmaþýklýðna sahip. Çünkü Linked Listte eriþmek istediðimiz list'e gidene kadar o yoldaki her node'a girmeliyiz.
	- Deðer ararken ikisi de ayný karmaþýklýða sahip(eðer bir düzenleme vs söz konusu deðil ise)
	- Dinamik ömürlü bir nesneden deðer eklenmesi ve çýkarýlmasý durumunun constant time sadece sondan olduðunda söz konusu.
		Fakat, baðlý listede eklenecek/çýkarýlacak konuma iliþkin pointerler var ise nereden ekleme/çýkarma yaparsak yapalým Constant Time. Sadece pointerin deðerini deðiþtirerek 
			bu deðiþimi yapabiliriz.
	- Linked list alan konusunda tam bir felaket. Bellek kullanýmý aþýrý fazla. Her veriyi tutmak için bir düðüm olmasý gerekiyor her düðümün içerisinde de 1 tane pointer var.
		8 elemanlý bir char dizisi için 8 byte alan gerekirken Linked listte bu deðer 8 * sizeof(char*) + 8 * sizeof(char) oluyor. Benim derleyicimde bu 72Byte'a tekabül ediyor.
			8 byte nere 72 byte nere.

		Singly Linked List
			- Eðer düðümün içerisinde 1 adet pointer nesnesi var ise ve sonraki düðüme iþaret ediyor ise sadece tek yönlü hareket edebilirsiniz demek bu. 
				Soldan -> Saða gibi. Gidiyorsun ama gelemiyorsun.
		Doubly Linked List
			- Yani singly bir ise doubly 2 pointer nesnesi olduðu anlamýna geliyor. Ýçerisin de iki pointer nesnesi tutuyor. Bu sayede iki yönde de hareket edebilir. Bir pointer
				sonraki düðümü, diðeri de önceki düðümü gösterebilir. Maaliyet iyiyce arttý çünkü artýk 2 * sizeof(T*) + sizeof(T) aboooo
	- Her ne kadar linked listte constant time ile ekleme çýkarma yapabiliyor olsakta belirli bir eleman sayýsýna kadar dinamik bellek daha avantajlý. Ýki sebebi var bunun
		1 - Ön bellek mekanizmasý (sýk eriþilen bellek bloklarýnýn ön belleðe alýnmasý) Linked listte birbirine baðlý olan düðümler ardýþýk olsa da ayný bellek üzerinde
			bulunmuyor. Bundan dolayý Cache hit olayý çoook düþük. 
		2 - vektorizasyon komutlarý


	Baðlý listenin avantajlarý;
		1 - Fragmentation: Daha önce görmüþtük bunu kýsacasý kullanýlan her belleðin contigous olmasý deðilde parça parça þeklinde olmasý durumu.
			Biz memory allocation yaparken n * sizeof(T) kadarlýk bir bellek bloðu arýyoruz ve contigous olma garantisi var. Küçük bellek allocationlarý için bu durum ok olabilir
				ama 40000Byte'lýk bir dinamik bellek alaný allocate ederken 40k Byte'lýk contgious boþ bir bellek alaný bulmak biraz zor. Linked List'in contigous olma zorunluluðu olmadýðý için
					bir node'u allocate edebildiði sürece "dewamke" modunda gidiyor. Ýsterse birisi New York'ta tanýmlý olsun diðeri Dubai de. Adresi sahip olduðumuz sürece sýkýntý yok.
		2 - Boyutu büyük olan veri yapýlarýnda swap iþleminde avantaj saðlar. 120Byte'lýk bir student struct'ý olduðunu düþünelim. 2 struct Student türünden nesneyi takas ederken 3 kere
			kopyalama iþlemi yapýlacak bu ada 120 * 3 = 360 bytelýk kopyalama iþlemi demek. Bunu yapmak yerine nodelarýn gösterdiði pointerlar swaplanýrsa maaliyet çok daha fazla düþük
				olur. 
		3 - 2 dinamik dizi ve 2 linked list olduðunu düþünelim. Bir diziden aldýðým deðeri silip ikinci diziye aktarmak istediðim de lineer karmaþýklýkta bir algoritma
			çalýþtýrmam gerek 2 kez. Fakat, linked listte silmek istediðim düðümü tamamen silmek yerine sadece o linked list ile iliþkisini kesmem ve diðer list'e baðlamam yeterli.
		


	- Linked list'in ilk düðümünün adresi bir yerde tutulmalý yoksa diðer nodelara eriþemeyiz.
*/

#include "Student.h"
// Singly linked list
	// typedef keywordü ile bildirilse bile içerisindeki SNode* nesnesinin baþýnad struct bulunmasý zorunda.
typedef struct SNode {
	Student data;
	struct SNode* pnext;
}SNode;

// Doubly Linked List
	// typedef keywordü ile bildirilse bile içerisindeki SNode* nesnesinin baþýnad struct bulunmasý zorunda.
typedef struct DNode {
	Student data;
	struct DNode* pprev;
	struct DNode* pnext;
}DNode;

// Son düðüme geldiðimizi nasýl anlayacaðýz.
	//Eðer singly linked list ise pointer deðiþkeni NULL pointer olmalý.
	//Eðer doubly linked list ise sonraki düðümü gösteren pointer deðiþkeni NULL pointer olmalý.
// Ýlk düðümün adresini tutan deðiþkene ANCHOR denir.
// Doubly Linked Listte ilk ve son düðümün adresleri tutulur.
	// Son düðümün adresini sona constant time'da düðüm eklemek için yapýyoruz.



/*
	Öðrencilerin bir veri yapýsý olsun.
	Ekleme ve silme iþlemleri baþtan yapýlýyor
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