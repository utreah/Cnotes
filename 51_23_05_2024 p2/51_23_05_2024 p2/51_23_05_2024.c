#include <stdio.h>
#include <stdlib.h>

struct Data {
	int x, y;
	double d;
};

int main(void) {
	// pointerlarda ��rendi�imiz her �ey struct* i�inde ge�erli
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
	set_array_random(p->grades, 5); // nutility.h i�erisinde bu.

	return p;
}

int main(void) {
	struct Student* p = make_random_student();

	free(p);
}
// CPP'de bir struct'�n structure tag'� direkt olarak kullan�labiliyor. struct Struct_tag �eklinde yaz�lmas�na gerek yok.
	// C'de ise struct keyword� kullan�lmak zorunda. Bundan kurtulman�n bir yolu var o da typedef bildirimi yapmak.


														/*		Struct Type-Alias Bildirimleri		*/
struct Student {
	int no;
	char name[20];
	char surname[20];
	int grades[5];
};
int main(void) {

	// typedef "t�r e� olu�turulacak isim" "e� isim"
	typedef struct Student Student; // struct tagi tekrar kullanmakta bir sak�nca yok

	/*
		a- Bir struct'�n struct tag'i ile bir eleman�n�n ad� ayn� olabilir -> struct nec{int nec;};
		b- Bir yap� t�r� ile tan�mlanan nesnenin ad� struct tag ile ayn� olabilir -> struct nec nec; (nec.nec; burada nec eleman�na eri�iyoruz)
		c- typedef bildiriminde de t�r ismi ile e� ismi ayn� olabilir. typedef struct nec nec;
	*/
	typedef struct Student* StudentPTR;
	typedef struct Student Student, *StudentPTR; // burada struct Student -> Student
												// struct Student* StudentPTR; �ok kullan�lm�yormu� ama bu da bir tan�mlama �ekli.

	// Kafa kar��t�r�c� bir �zellik var. Onu anlatmadan �nce �unun tekrar�n� yapal�m.
	/*
		Nas�l typedef bildirimi yap�yorduk?
		- Hedef t�rden bir de�i�ken tan�mla.
			int x;
		- Daha sonra ba��na typedef keywordunu getir. 
			typedef int x;
		- Son olarak de�i�ken ad�n� ilgili t�r-e� ismine de�i�tir.
			typedef int zort; 
		Art�k zort int t�r�n�n yerini ald�.
		Daha �nce yap� t�r�nden nesne tan�mlarken bir y�ntem daha ��renmi�tik. 

		struct Data{
			int x, y;
			double d;
		}test; // test art�k struct Data t�r�nden bir de�i�ken oldu. Ekstradan 'struct Data test;' yazmama gerek kalmadan.

		�imdi bunu �stteki typedef bildirimi ile birle�tirelim.
	*/
	// Hedef t�rden bir tan�mlama yap.
		struct Data {
			int x, y;
			double d;
		}x;
	// Ba��na typedef getir.
		typedef struct Data {
			int x, y;
			double d;
		}x;
	// De�i�ken ad�n� yerini almas�n� istedi�in t�r-e� ismine �evir.
		struct Data {
			int x, y;
			double d;
		}Data; // struct tag ile struct Data t�r�nden nesnenin adlar� ayn� olabilir
		// Art�k Data, struct Data'n�n t�r-e� ismi oldu.
		Data d1; // -> struct Data d1; ayn� anlam.
}


typedef struct Student {
	int student_no;
	char student_name[20];
	char student_surname[20];
	int grades[5];
}Student, *StudentPTR; // *StudentPTR  pointerlar i�in e� ismi olacakt�.

int main(void) {
	Student s1 = { 1071, "Engin", "Kendarli", {100, 20, 60, 86, 0} };
	struct Student s2 = { 1071, "Engin", "Kendarli", {100, 20, 60, 86, 0} };
	// baz� k�t�phaneler/ki�iler type-alias ve structure_tag'i ay�rmak i�in structure tagin sonuna _tag ekliyorlar.
	/*
		typedef struct student_tag { // b�yle yaparak struct keyword� ile tan�mlanmak istedi�inde struct student_tag kullan�lmak zorunda.
		int student_no;
		char student_name[20];
		char student_surname[20];
		int grades[5];
		}Student;
	*/
}
/*----------------------------------------------------------------------------*/

// structure tag'i olmayan yap�larda da type-alias kullan�labilir. 
typedef struct {
	int x, y;
	double d;
}Data;

int main(void) {
	Data d1 = { 13, 15, .4 };
	// Fakat t�r-e� ismi struct keyword� ile kullan�lamaz.
	struct Data d2 = d1; // bu yanl��. struct keyword� ile kullan�lamaz.
}
/*----------------------------------------------------------------------------*/
typedef struct {
	int x, y;
	double d;
}*DataPTR;
// DataPTR burada, yap� ismi olmayan bu yap�n�n struct* t�r�nden t�r-e� ismi
//Yukar�daki isimsiz struct yap�s� ile statik veya otomatik �m�rl� bir de�i�ken tan�mlayamay�z. Neden?
	// ��nk� structure tag'i yok ve t�r-e� ismi tan�mlarken de olu�turmak i�in bir yol b�rakmad�k.
// Yukar�daki DataPTR sayesinde bu yap� t�r�n�n dinamik �m�rl� nesnelerin adresini tutabilece�ini biliyoruz. Bunu kullanarak
	// bu structure'� kullanabiliriz.
int main(void) {
	DataPTR pd = (DataPTR)malloc(sizeof(*pd)); // DataPTR yap� t�r�nden pd adl� bir de�i�ken tan�mlad�k ve bu de�i�kene bir bellek blo�unun
	pd->d = 4.;											// adresini ilk de�er olarak atad�k. malloc geri d�n�� de�eri void* oldu�u i�in DataPTR'ye explicit
													// type conversion ile d�n��t�rd�k. *pd ile yaparakta bellekte kaplad��� alan� ��rendik.
														// bunu structure_tag ile yapabilirdik ama structure_tag yok. �akal y�ntem bu
	// yukar�daki definition i�in not
	/*
		Atama operat�r� sequence point olu�turur. Bu sayede atama operat�r�n�n solundaki ifade, operat�r�n sa� operand�nda da kullan�labilir.
			pd hayata geldi�inde garbage value sahibi. ��nk� hi�bir adresin de�erini tutmuyor o anda. sizeof keyword�
				i�lem kodu �retmiyor bunu hat�rl�yoruz. E�er sizeof, *pd i�in bir i�lem kodu �retiyor olsayd� bu undefined behaviour olacakt�.
					Garbage value tutan bir pointer�n derefence edilmesi UB.
	*/
	/*
		M�lakat sorusu
		-bir structta statik ve otomatik �m�rl� de�i�ken tan�m�n� engellemek ve sadece dinamik �m�rl� nesne kullanmak i�in ne yapabiliriz?
			Yukar�da ne yapt�ysak ayn�s�. struct_tag'i olmayan, t�r e� ismi o yap� t�r�nden olan bir struct tan�mlayarak
				yapabiliriz.
	*/
}

	// Bir fonksiyonun i�ersinide struct tan�m� yap�labilir. Fakat, fonksiyon i�inde tan�mlanan struct'�n �mr� fonskiyonda tan�mland��� yerden
		// fonksiyonun sonuna kadard�r. �leride g�r�cez bunu
void foo(void) {

	struct Data {
		int x, y;
	}; // hayata geldi
} // hayata veda etti :'(((
/*----------------------------------------------------------------------------*/
												/*		C ve CPP aras�ndaki struct farklar�		*/	
// C'de yap� t�r�nden bir nesne tan�mlarken struct keyword� de kullan�l�rken CPP'de gerek yok.
struct Data mydata; // C'de b�yle
Data mydata; // CPP'de b�yle
// C dilinde eleman� olmayan bir yap� t�r� olamaz.
struct Dataa {

}; // C'de bu olamaz, CPP'de olabilir hatta baya s�k kar��la��labiliyormu�.
// CPP'de yap�n�n elemanlar� fonksiyon olabiliyor.

struct DataFunc {
	void foo();
	void bar();
	void baz();

	void (*foo)(void); // C'de function pointer olabilir.
};// C'de yap�n�n elemanlar� fonksiyon olam�yor, CPP'de legal. Bunlara member function deniyor
	//C'de yap�n�n elemanlar� function pointer olabiliyor. Bunlar function pointer member.

// Yap�n�n elemanlar�na yap� i�erisinde de�er verilemez.
struct Data {
	int x = 5; // bu C'de illegal.

	int y{ 6 }; int z = 10; // bunlar ise CPP'de legal. Birisi uniform init 
};
// Yap� t�rleri, k�t�phanelerde, genellike problem/��z�m domainindeki bir t�r� temsil ediyor. Hizmet vermeye y�nelik bir bile�en structlar.
/*
	Yap� t�rleri bizim problemleri/��z�mleri daha da y�ksek seviyede soyutlamam�za yard�mc� oluyor.
		Diyelim ki g�n/ay/y�l tutan bir nesne(ler)e ihtiyac�m�z var. int day,mon,year; diye de�i�ken tan�mlayabilirdik.
		Fakat kodu okuyan ki�i bunlar�n bir tarihi temsil etti�ini ancak bir araya geldiklerinde anlayabilirdi. 
			Yeni bir tarih i�inde yeniden bu �� de�i�ken gibi de�i�kenler tan�mlamak gerekiyor. ��te tam bu noktada structures bize
				problemi daha �st seviyede soyutlamak i�in yard�mc� oluyor.
*/
/*----------------------------------------------------------------------------*/
													/*		Fonksiyonlar ve Yap�lar aras�ndaki ili�ki		*/	
// Baz� k�t�phaneler olu�turduklar� yap�lar�n memberlar�n� konvensiyonel �ekilde isimlendirebiliyor.
	// baz�lar� de�i�ken ad�n�n ba��na "m_" ekliyor. -> m_no; gibi
	// baz�lar� de�i�kenin sonuna "_" ekliyor. int no_; gibi
typedef struct Student {
	int no;
	char name[20];
	char surname[20];
	double mean;
}Student;
// Fonksiyonlar�n parametre de�i�kenleri yap� t�r�nden nesneler olabilir. Fakat, bu tercih edilen bir kullan�m �ekli de�il.
	// ��nk�, arg�man olarak g�nderilen yap� t�r�nden nesnenin i�eri�i, yap� t�r�nden olan parametre de�i�kenine KOPYALANIYOR.
		// Kopyalama i�leminin maaliyeti �ok olaca�� i�in �ok fazla kullan�lm�yor. Belki, sizeof de�eri �ok k���k yap� t�r� i�in
			// ge�erli olabilir. Kopyalama i�lemi bir yap� t�r�nden nesnenin ayn� t�rden ba�ka bir nesneye kopyalanmas� gibi.
void foo(Student s) {
	printf("Student No : %d\n", s.no);
	printf("Student No : %s\n", s.name);
	printf("Student No : %s\n", s.surname);
	printf("Student No : %.2f\n", s.mean);
}

// Bu tarz i�lemler i�in daha �ok pointer kullan�l�yor. Pointerlar�n t�m t�rlerinin sizeof de�eri 4 (derleyiciye g�re de�i�ebilir)
	// Pointer kullanmak maaliyet a��s�ndan daha ucuz
void bar(Student* x) { // Student* olarak yazd�k ��nk� yukar�da type-alias var. Olmasayd� struct Student* �eklinde olacakt�. Call by reference
	printf("Student No : %d\n", x->no); // Burada eri�im, isim �zerinden de�il de adres �zerinden oldu�u i�in arrow operator kullan�yoruz.
	printf("Student No : %s\n", x->name);
	printf("Student No : %s\n", x->surname);
	printf("Student No : %.2f\n", x->mean);
	printf("--------------------------------");
} // bar bir mutator fonksiyon. ��nk� parametresi const de�il. De�er de�i�tirebilir.
void baz(const Student* x) {

} // baz bir accessor. Parametre const oldu�u i�in sadece okuma yap�labilir de�i�iklik yap�lamaz.	
int main(void) {
	Student s1 = { .no = 6236, .name = "Engin", .surname = "Kendarli", .mean = 98.72 };
	foo(s1);
	Student* s1ptr = &s1;
	bar(s1ptr); // veya bar(&s1);
}
2:23