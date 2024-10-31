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