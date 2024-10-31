/*
	-Yapý nesneleri sadece 4 operatörün operandý olabilir
		* sizeof Operator
		* Assignment Operator
		* Arrow Operator 
		* Dot Operator

*/

struct Eng {
	int x, y;
	double dval;
	int a[5];
};
int main(void) {
	struct Eng myeng;
	//sizeof(myeng) ve sizeof myeng  þeklinde yazýlabilir. myeng burada bir deðiþken
		// struct Eng ise parantez içerisinde olmak zorunda. Çünkü bir tür. sizeof(int) ile ayný olay. size_t türünden bir deðer üretir.

	&myeng; // myeng bir lvalue expression olduðu için addressof operatörünün sol operandý olabilir. 
				//Bu ifadenin türü struct Eng* türünden.

	// addressof operatörü ile oluþturulmuþ ifadenin deðerini tutmak istersek;
	struct Eng* myEngptr = &myeng; 
	// Dizi de oluþturulabilir.
	struct Eng myEngArr[10] = { 0 };
	myEngArr + 1; // dizinin bir sonraki elemanýný gösteriri. (indisi numarasý 1) Pointer aritmatiði burada da geçerli.
					// ileride görülecek bu konular detaylýca

	/* þimdi detaylýca atama operatörünü anlatýlacak*/
}
struct Data {
	int x, y;
	double dval;
};
struct Token {
	int x, y;
	double dval;
};

int main(void) {
	struct Data mydata = { 2, 5, 6.7 }; // ilk deðer verme sentaksý bu þekilde. Daha görmedik öðrenicez.
	struct Data b;
	// bir yapý türünden nesneye atama yapýlýrken ayný türden bir nesne olmak zorunda. 
	b = mydata; // legal, çünkü mydata struct Data türünden bir nesne.
	
	//a- Diðer türlerden implicit/explicit type conversion yok.
	b = 10; // sentaks hatasý
	b = (struct Data)10; // sentaks hatasý
	
	struct Token myToken;
	//b- farklý yapý türleri arasýnda da sentaks dönüþümü yok.
	b = myToken; // Ýki yapý türünün de elemanlarý ayný olsa dahi atama yapýlamaz. Tür dönüþtürme operatörü de iþe yaramýyor
	b = (struct Data)myToken; // sentaks hatasý

	//c- Atama yaparken deðerleri sýralý olarak alacak. Yani b = mydata yaptýðýmýzda x, y ve dval deðiþkenleri sýrasý ile 2, 5, 6.7 deðerlerini alacak.
	b = mydata; // b.x = 2; b.y = 5; b.dval = 6.7; deðerlerini aldý.
		/*
			b.x = mydata.x;
			b.y = mydata.y;
			b.dval = mydata.dval;
			yukarýdaki þekilde oluyormuþ gibi düþün 

			b = mydata; yaptýðýmýzda memcpy çalýþýyormuþ gibi düþünebiliriz.
			memcpy(&b, &mydata, sizeof(mydata)); struct memberlarý contigous olduðu için çat çat çat hepsine atama yapacak.
		*/
	printf("b.x = %d", b.x); // 2
	printf("b.y = %d", b.y); // 5
	printf("b.dval = %d", b.dval); // 6.7

	/*
		Üretimde yapýlarýn birbirine kopyaladýðýný görücez illaki. Fakat, structlarýn bellekteki boyutu büyüdükçe kopyalama iþleminin maliyeti de büyüyor.
			Çok ihtiyaç olmadýkça büyük yapý nesnelerini kopyalamaktan kaçýnmalýyýz özellikle verimin kritik olduðu uygulamalar/iþlemlerde.
	*/
	// yapýlara ilk deðer verme sentaksý dizilerin ilk deðer verme sentaksýna benziyor. (Agregate deniyor buna)
		// Köþeli parantez içerisine sýrasý ile deðerleri veriyoruz.

	struct Data initData = { 1, 2, 4.2, }; // sýrasý ile int, int ve double deðiþkenlere deðer verdik. 
	/*
		* Eðer yapý nesnelerine ilk deðer verilmez ise 0 deðeri ile hayata baþlarlar. -> Bu durum diðer memberlarý deðer alýrsa geçerli.
			Hiçbir member init edilmez ise, garbage value tutarlar.
		* Pointer türünden bir yapý nesnesi ise NULL pointer ile hayata baþlarlar.
		* trailing comma olabilir. initData nesnesinde olduðu gibi.
		struct içerisindeki dizilere nasýl ilk deðer verilebilir?
			struct initData{
				int x, y;
				int ar[4];
				double d;
			};
			struct initData myData = {1, 2, {1, 2,}, 4.2}; // Dizinin elemanlarýna deðer vermeye baþlayacaðýmýz yerde bir tane daha köþeli
				// parantez açýyoruz ve ilk deðeri öyle veriyoruz. Ýlk deðer verilmeyen elemanlar 0 deðeri ile hayata baþlar.
			struct initData myData2 = {10, 23, 40, 50, 60, 70, 4.2}; bu þekilde de tanýmlanabilir. Bir sakýncasý yok
				// bu þekilde süslü parantez olmadan tanýmlama yapmakta bir sakýnca var. Eðer dizinin son elemanýný yazmaz isek derleyici bunu ne olduðunu anlamaz ve sonraki deðeri
					// diziye yapýþtýrýr.
			struct initData myData3 = {10, 3, 5, 7, 4.2}; // burada derleyici "4.2 double türünden bir deðer o zaman 4. atama d deðiþkeni için" demez, dizinin son elemanýna 4.2
				// deðerini atar (int olduðu için 4 olur) ve d deðiþkeni hayata 0 olarak baþlar.
					// Dizi var ise süslü parantez kullanmak daha mantýklý ve güvenli gibi duruyor.
	*/
/*--------------------------------------------*/
	/* Designated Initializer */
	// Diziler için görmüþtük, bir tekrar edelim.
	int a[10] = { [3] = 5,[4] = 3, [1] = 2};
		// Sýralý olma zorunluluklarý yok.
		// Eðer dizinin boyutu belirtilmez ise dizi içerisindeki en büyük indisin deðeri ile gerekli bellek alaný allocate edilecek compiler tarafýndan.
	// Yapý türünden nesneler için ise dot operatöründen sonra member'ýn adýný yazýyoruz.

	struct Data designatedInitData = { .dval = 2.4, .x = 5, }; // ilk deðer verilmeyenler 0 olarak baþlayacak.
		// deðer vermenin sýrasýnýn bir önemi yok(designated init ile)
		// designated init ile hatalý deðer verme riski gidiyor. 
		// Maliyet açýsýndan hiçbir fark yok.
} 
/*--------------------------------------------*/
struct Student {
	int no;
	int age;
	char name[20];
	char surname[20];
	int grades[5];
};
int main(void) {
	struct Student s = { 23, 26, "Engin", "Kendarli"}; // þimdi buradaki 23 no mu yaþ mý? Belki sýrasý yanlýþ yazýldý. Bu hatanýn önüne geçmek için designated init
	struct Student myStudent = { .no = 31, .age = 25, .name = "Engin", .surname = "Kend" };
	struct Student myStud = { .no = 12, .age = 23, .name = "Kagan", .surname = "Kultigin", .grades = { [0] = 100,[2] = 25} }; // diziler içinde designated init kullanýlabilir. 
}
/*--------------------------------------------*/


struct Ar {
	int a[5];
};
int main(void) {
	int a[5] = { 1, 2, 3, 4, 5 };
	int b[5];
	// b = a; bu YANLIÞ SENTAKS HATASI. Array decay, b burada rvalue expression	
	
	// yapý nesneleri birbirine atanabilir.

	struct Ar a2 = { 1, 2, 3, 4, 5, };
	struct Ar b2;

	b2 = a2; // bu legal çünkü struct türünden nesneler birbirine atanabilir. Daha önce demiþtir strcpy fonksiyonunu çaðýrmýþýz gibi.
}
/*--------------------------------------------*/
#include <stdlib.h>
#include <C:\Users\xxxx\Documents\GitHub\Cnotes\nUtility.h>
struct Data {
	int x, y;
	int* iptr;
	char* cptr;
};

int main(void) {
	// Eðer yapý türünden nesneler dinamik olarak allocate edilmiþ bir bellek alanýný tutuyor ise ve bu deðeri baþka ayný türden bir yapý nesnesine kopyalanýr ise
		// T* türünden deðiþkenlerin tuttuðu adreslerde yeni yapý türünden nesneye geçmiþ olur.
	struct Data mydata;
	size_t n = 40;
	mydata.iptr = (int*)malloc(n * sizeof(int));
	set_array_random(mydata.iptr, n);
	mydata.cptr = (char*)malloc(n * sizeof(char));

	struct Data another_data;
	another_data = mydata; // sadece pointerlar gönderilmiþ olacak. 
	/*
		Þurada þöyle bir problem var. mydata.iptr ve mydata.cptr nesneleri dinamik olarak allocate edilmiþ bir belleðin adresini tutuyor. 
			Eðer ben another_data üzerinden bu belleklerden birini free() eder isem, mydata.iptr ve cptr artýk dangling pointer haline gelir.
				Ve bunu farkýnda olmasan yaparsak inanýlmaz baþ aðrýtýr. 
	*/
}

struct Number {
	int x, y;
	double d;
};
struct Number g; // global bir struct  Number türünden bir nesne.
	// Bunu bu þekilde define etmenin bir baþka yolu daha var


struct Number2 {
	int x, y;
	double d;
}g1, g2, *ptr = &g1 ,g3 = { 2, 4, 6.2 }; // böyle yaparak g1, g2, g3 adýnda struct Number2 türünde 3 adet global deðiþken tanýmlamýþ olduk.
// burada ilk deðer atamasý yapabilir, poiter deðiþkenlerde olabiliyor burada.
// *ptr = &g1; *ptr, yapý türünden bir nesnenin adresini tutuyor.

// Structure tag olmadan da struct kullanabiliriz.

struct {
	int x, y, z;
	double d;
}a, b, c = { 1, 2, 3, .5 }; // sentaks hatasý yok böyle tanýmlama yapabiliriz. Böyle yapýnca tür ismi olmayan, ayný yapý türünden nesneler oluyorlar.
/*
	Kullanýmý;
	* Belirli sayýda yapý türünden nesne tutmak istiyoruz. Bu sayede baþka, yapý türünden nesne oluþturulamýyor.
	* Kodlara ayný türden baþka nesne oluþturma imkaný vermiyoruz bu sayede.
*/

int main(void) {
	a = c; // legal
	printf("%d", a.x);
	/*
		
	*/
}

struct {
	int x, y, z;
	double d;
}q1;

struct {
	int x, y, z;
	double d;
}q2;
struct Point {
	int x, y;
}ar[4];
int main(void) {
	q1 = q2; // bu bir sentaks hatasý. Ýkisinin de struct_tag'i olmamasý, memberlarýnýn ayný olmasý ayný türden olduklarý anlamýna gelmiyor
				// ikisi de farklý tür. Farklý türler arasýnda implicit/explicit dönüþüm YOK.
	struct Point a[5] = { {1, 2}, {3, 4}, {7,8}, {23, 43},[4] = {33, 231} };

}
/*--------------------------------------------*/
struct Data {
	int x, y;
	double d;
};

int main(void) {
	struct Data mydata = { 3, 4, 5.2 };

	&mydata; //geçerli bunun adresini tutmak için struct Data* türünden bir deðiþkene ihtiyacým var
	struct Data* p = &mydata;
	*p; // atama yapmak istersem gene struct Data türünden bir nesne olmalý

	//*p.x; -> nokta operatörü içerik operatöründen daha öncellikli sýkýntý var. -> *(p.x) anlamýna gelir böyle ki yanlýþ bu. p bir adres
	(*p).x; // doðru kullanýmý bu þekilde Öncelik parantezine alýnmasý gerek. Ayný anlama gelen, görünüþü daha kolay olan bir gösterim var. Arrow operator

														/*					ARROW OPERATOR					*/
	/*
		arrow operatörü binary infix bir operatördür.
		Sol operandý yapý türüyle oluþturulmuþ nesnenin adý, sað operandý ise o yapý türünün içerisinde bulunan member.
		Dot operator, struct içerisinde bulunan memberlara isimleri üzerinden ulaþýyordu.
		Arrow operator ise memberlara adresleri üzerinden ulaþýyor. 
		Arrow operatörlerinin oluþturduðu ifadeler lvalue expressiondur.
	*/
	(*p).x; p->x; // bu ikisi ayný anlamda.
	struct Data a[5] = { 0 };
	a->x = 5; // array decaydan faydalanarak struct data türünden a dizisinin sýfýr numaralý indisine 5 deðerini kopyalayacak.
	a[0].x = 5; // 

	(a + 3)->y = 15; // 3 indisli elemanýna eriþip 15 deðerini atayacak.
	a[3].y = 15;

	(&mydata)->x = 5; // legal

	// const keywordü pointerlarda olduðu gibi burada da ayný anlam ve amaçla kullanýlabilir.

	struct Data Eng = { 1, 2, 3.4 };
	struct Data Ken = { 5, 7, .4 };
	// struct Data* ePtr = &Eng; Eðer const keywordü * tokenýndan önce olursa, read-only. 
									// Saðýnda olur ise içerik deðiþebilir, gösterdiði nesne deðiþtirilemez.
	const struct Data* cEng = &Eng;
	*Eng = 5; // sentaks hatasý
	Eng->x = 50; // sentaks hatasý
	cEng = &Ken; // yeni bir nesnenin adresi atanabilir

	struct Data* const coPtr = &Eng;

	coPtr->d = 5; // memberlarýnýn deðerleri deðiþtirilebilir.
	coPTR = &Ken; // sentaks hatasý

	cEng = NULL; // pointer nesnelerine null pointer atanabilir.
	// pointerlarýn sizeof deðerleri diðer pointerlarda da olduðu gibi 4 BYTE.

	printf("%zu\n1", sizeof(struct Data)); // Bunun sizeof deðeri 2 * int + double;
	printf("%zu\n1", sizeof(cEng)); // bunun sizeof deðeri 4 byte
}
#include <stdio.h>
#include <stdlib.h>

struct Data {
	int x, y;
	double d;
};

int main(void) {
	// pointerlarda öðrendiðimiz her þey struct* içinde geçerli
	struct Data d;
	struct Data* dp = &d;
	struct Data** dpp = &dp; // pointer to pointer to struct Data

}
struct Student {
	int no;
	char name[20];
	char surname[20];
	int grades[5];
};

struct Student* make_random_student(void) {
	struct Student* p = (struct Data*)malloc(sizeof(*p));

	if (!p)
		printf("Memory allocation failed");
	p->no = rand();
	strcpy(p->name, "Engin");
	strcpy(p->surname, "Kendarli");
	set_array_random(p->grades, 5); // nutility.h içerisinde bu.

	return p;
}

int main(void) {
	struct Student* p = make_random_student();

	free(p);
}
// CPP'de bir struct'ýn structure tag'ý direkt olarak kullanýlabiliyor. struct Struct_tag þeklinde yazýlmasýna gerek yok.
	// C'de ise struct keywordü kullanýlmak zorunda. Bundan kurtulmanýn bir yolu var o da typedef bildirimi yapmak.


														/*		Struct Type-Alias Bildirimleri		*/
struct Student {
	int no;
	char name[20];
	char surname[20];
	int grades[5];
};
int main(void) {

	// typedef "tür eþ oluþturulacak isim" "eþ isim"
	typedef struct Student Student; // struct tagi tekrar kullanmakta bir sakýnca yok

	/*
		a- Bir struct'ýn struct tag'i ile bir elemanýnýn adý ayný olabilir -> struct nec{int nec;};
		b- Bir yapý türü ile tanýmlanan nesnenin adý struct tag ile ayný olabilir -> struct nec nec; (nec.nec; burada nec elemanýna eriþiyoruz)
		c- typedef bildiriminde de tür ismi ile eþ ismi ayný olabilir. typedef struct nec nec;
	*/
	typedef struct Student* StudentPTR;
	typedef struct Student Student, *StudentPTR; // burada struct Student -> Student
												// struct Student* StudentPTR; Çok kullanýlmýyormuþ ama bu da bir tanýmlama þekli.

	// Kafa karýþtýrýcý bir özellik var. Onu anlatmadan önce þunun tekrarýný yapalým.
	/*
		Nasýl typedef bildirimi yapýyorduk?
		- Hedef türden bir deðiþken tanýmla.
			int x;
		- Daha sonra baþýna typedef keywordunu getir. 
			typedef int x;
		- Son olarak deðiþken adýný ilgili tür-eþ ismine deðiþtir.
			typedef int zort; 
		Artýk zort int türünün yerini aldý.
		Daha önce yapý türünden nesne tanýmlarken bir yöntem daha öðrenmiþtik. 

		struct Data{
			int x, y;
			double d;
		}test; // test artýk struct Data türünden bir deðiþken oldu. Ekstradan 'struct Data test;' yazmama gerek kalmadan.

		Þimdi bunu üstteki typedef bildirimi ile birleþtirelim.
	*/
	// Hedef türden bir tanýmlama yap.
		struct Data {
			int x, y;
			double d;
		}x;
	// Baþýna typedef getir.
		typedef struct Data {
			int x, y;
			double d;
		}x;
	// Deðiþken adýný yerini almasýný istediðin tür-eþ ismine çevir.
		struct Data {
			int x, y;
			double d;
		}Data; // struct tag ile struct Data türünden nesnenin adlarý ayný olabilir
		// Artýk Data, struct Data'nýn tür-eþ ismi oldu.
		Data d1; // -> struct Data d1; ayný anlam.
}


typedef struct Student {
	int student_no;
	char student_name[20];
	char student_surname[20];
	int grades[5];
}Student, *StudentPTR; // *StudentPTR  pointerlar için eþ ismi olacaktý.

int main(void) {
	Student s1 = { 1071, "Engin", "Kendarli", {100, 20, 60, 86, 0} };
	struct Student s2 = { 1071, "Engin", "Kendarli", {100, 20, 60, 86, 0} };
	// bazý kütüphaneler/kiþiler type-alias ve structure_tag'i ayýrmak için structure tagin sonuna _tag ekliyorlar.
	/*
		typedef struct student_tag { // böyle yaparak struct keywordü ile tanýmlanmak istediðinde struct student_tag kullanýlmak zorunda.
		int student_no;
		char student_name[20];
		char student_surname[20];
		int grades[5];
		}Student;
	*/
}
/*----------------------------------------------------------------------------*/

// structure tag'i olmayan yapýlarda da type-alias kullanýlabilir. 
typedef struct {
	int x, y;
	double d;
}Data;

int main(void) {
	Data d1 = { 13, 15, .4 };
	// Fakat tür-eþ ismi struct keywordü ile kullanýlamaz.
	struct Data d2 = d1; // bu yanlýþ. struct keywordü ile kullanýlamaz.
}
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	double d;
}*DataPTR;
// DataPTR burada, yapý ismi olmayan bu yapýnýn struct* türünden tür-eþ ismi
//Yukarýdaki isimsiz struct yapýsý ile statik veya otomatik ömürlü bir deðiþken tanýmlayamayýz. Neden?
	// çünkü structure tag'i yok ve tür-eþ ismi tanýmlarken de oluþturmak için bir yol býrakmadýk.
// Yukarýdaki DataPTR sayesinde bu yapý türünün dinamik ömürlü nesnelerin adresini tutabileceðini biliyoruz. Bunu kullanarak
	// bu structure'ý kullanabiliriz.
int main(void) {
	DataPTR pd = (DataPTR)malloc(sizeof(*pd)); // DataPTR yapý türünden pd adlý bir deðiþken tanýmladýk ve bu deðiþkene bir bellek bloðunun
	pd->d = 4.;											// adresini ilk deðer olarak atadýk. malloc geri dönüþ deðeri void* olduðu için DataPTR'ye explicit
													// type conversion ile dönüþtürdük. *pd ile yaparakta bellekte kapladýðý alaný öðrendik.
														// bunu structure_tag ile yapabilirdik ama structure_tag yok. Çakal yöntem bu
	// yukarýdaki definition için not
	/*
		Atama operatörü sequence point oluþturur. Bu sayede atama operatörünün solundaki ifade, operatörün sað operandýnda da kullanýlabilir.
			pd hayata geldiðinde garbage value sahibi. Çünkü hiçbir adresin deðerini tutmuyor o anda. sizeof keywordü
				iþlem kodu üretmiyor bunu hatýrlýyoruz. Eðer sizeof, *pd için bir iþlem kodu üretiyor olsaydý bu undefined behaviour olacaktý.
					Garbage value tutan bir pointerýn derefence edilmesi UB.
	*/
	/*
		Mülakat sorusu
		-bir structta statik ve otomatik ömürlü deðiþken tanýmýný engellemek ve sadece dinamik ömürlü nesne kullanmak için ne yapabiliriz?
			Yukarýda ne yaptýysak aynýsý. struct_tag'i olmayan, tür eþ ismi o yapý türünden olan bir struct tanýmlayarak
				yapabiliriz.
	*/
}

	// Bir fonksiyonun içersinide struct tanýmý yapýlabilir. Fakat, fonksiyon içinde tanýmlanan struct'ýn ömrü fonskiyonda tanýmlandýðý yerden
		// fonksiyonun sonuna kadardýr. Ýleride görücez bunu
void foo(void) {

	struct Data {
		int x, y;
	}; // hayata geldi
} // hayata veda etti :'(((
/*----------------------------------------------------------------------------*/
												/*		C ve CPP arasýndaki struct farklarý		*/	
// C'de yapý türünden bir nesne tanýmlarken struct keywordü de kullanýlýrken CPP'de gerek yok.
struct Data mydata; // C'de böyle
Data mydata; // CPP'de böyle
// C dilinde elemaný olmayan bir yapý türü olamaz.
struct Dataa {

}; // C'de bu olamaz, CPP'de olabilir hatta baya sýk karþýlaþýlabiliyormuþ.
// CPP'de yapýnýn elemanlarý fonksiyon olabiliyor.

struct DataFunc {
	void foo();
	void bar();
	void baz();

	void (*foo)(void); // C'de function pointer olabilir.
};// C'de yapýnýn elemanlarý fonksiyon olamýyor, CPP'de legal. Bunlara member function deniyor
	//C'de yapýnýn elemanlarý function pointer olabiliyor. Bunlar function pointer member.

// Yapýnýn elemanlarýna yapý içerisinde deðer verilemez.
struct Data {
	int x = 5; // bu C'de illegal.

	int y{ 6 }; int z = 10; // bunlar ise CPP'de legal. Birisi uniform init 
};
// Yapý türleri, kütüphanelerde, genellike problem/çözüm domainindeki bir türü temsil ediyor. Hizmet vermeye yönelik bir bileþen structlar.
/*
	Yapý türleri bizim problemleri/çözümleri daha da yüksek seviyede soyutlamamýza yardýmcý oluyor.
		Diyelim ki gün/ay/yýl tutan bir nesne(ler)e ihtiyacýmýz var. int day,mon,year; diye deðiþken tanýmlayabilirdik.
		Fakat kodu okuyan kiþi bunlarýn bir tarihi temsil ettiðini ancak bir araya geldiklerinde anlayabilirdi. 
			Yeni bir tarih içinde yeniden bu üç deðiþken gibi deðiþkenler tanýmlamak gerekiyor. Ýþte tam bu noktada structures bize
				problemi daha üst seviyede soyutlamak için yardýmcý oluyor.
*/
/*----------------------------------------------------------------------------*/
													/*		Fonksiyonlar ve Yapýlar arasýndaki iliþki		*/	
// Bazý kütüphaneler oluþturduklarý yapýlarýn memberlarýný konvensiyonel þekilde isimlendirebiliyor.
	// bazýlarý deðiþken adýnýn baþýna "m_" ekliyor. -> m_no; gibi
	// bazýlarý deðiþkenin sonuna "_" ekliyor. int no_; gibi
typedef struct Student {
	int no;
	char name[20];
	char surname[20];
	double mean;
}Student;
// Fonksiyonlarýn parametre deðiþkenleri yapý türünden nesneler olabilir. Fakat, bu tercih edilen bir kullaným þekli deðil.
	// Çünkü, argüman olarak gönderilen yapý türünden nesnenin içeriði, yapý türünden olan parametre deðiþkenine KOPYALANIYOR.
		// Kopyalama iþleminin maaliyeti çok olacaðý için çok fazla kullanýlmýyor. Belki, sizeof deðeri çok küçük yapý türü için
			// geçerli olabilir. Kopyalama iþlemi bir yapý türünden nesnenin ayný türden baþka bir nesneye kopyalanmasý gibi.
void foo(Student s) {
	printf("Student No : %d\n", s.no);
	printf("Student No : %s\n", s.name);
	printf("Student No : %s\n", s.surname);
	printf("Student No : %.2f\n", s.mean);
}

// Bu tarz iþlemler için daha çok pointer kullanýlýyor. Pointerlarýn tüm türlerinin sizeof deðeri 4 (derleyiciye göre deðiþebilir)
	// Pointer kullanmak maaliyet açýsýndan daha ucuz
void bar(Student* x) { // Student* olarak yazdýk çünkü yukarýda type-alias var. Olmasaydý struct Student* þeklinde olacaktý. Call by reference
	printf("Student No : %d\n", x->no); // Burada eriþim, isim üzerinden deðil de adres üzerinden olduðu için arrow operator kullanýyoruz.
	printf("Student No : %s\n", x->name);
	printf("Student No : %s\n", x->surname);
	printf("Student No : %.2f\n", x->mean);
	printf("--------------------------------");
} // bar bir mutator fonksiyon. Çünkü parametresi const deðil. Deðer deðiþtirebilir.
void baz(const Student* x) {

} // baz bir accessor. Parametre const olduðu için sadece okuma yapýlabilir deðiþiklik yapýlamaz.	
int main(void) {
	Student s1 = { .no = 6236, .name = "Engin", .surname = "Kendarli", .mean = 98.72 };
	foo(s1);
	Student* s1ptr = &s1;
	bar(s1ptr); // veya bar(&s1);
}
2:23