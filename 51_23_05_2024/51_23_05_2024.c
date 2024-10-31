/*
	-Yap� nesneleri sadece 4 operat�r�n operand� olabilir
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
	//sizeof(myeng) ve sizeof myeng  �eklinde yaz�labilir. myeng burada bir de�i�ken
		// struct Eng ise parantez i�erisinde olmak zorunda. ��nk� bir t�r. sizeof(int) ile ayn� olay. size_t t�r�nden bir de�er �retir.

	&myeng; // myeng bir lvalue expression oldu�u i�in addressof operat�r�n�n sol operand� olabilir. 
				//Bu ifadenin t�r� struct Eng* t�r�nden.

	// addressof operat�r� ile olu�turulmu� ifadenin de�erini tutmak istersek;
	struct Eng* myEngptr = &myeng; 
	// Dizi de olu�turulabilir.
	struct Eng myEngArr[10] = { 0 };
	myEngArr + 1; // dizinin bir sonraki eleman�n� g�steriri. (indisi numaras� 1) Pointer aritmati�i burada da ge�erli.
					// ileride g�r�lecek bu konular detayl�ca

	/* �imdi detayl�ca atama operat�r�n� anlat�lacak*/
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
	struct Data mydata = { 2, 5, 6.7 }; // ilk de�er verme sentaks� bu �ekilde. Daha g�rmedik ��renicez.
	struct Data b;
	// bir yap� t�r�nden nesneye atama yap�l�rken ayn� t�rden bir nesne olmak zorunda. 
	b = mydata; // legal, ��nk� mydata struct Data t�r�nden bir nesne.
	
	//a- Di�er t�rlerden implicit/explicit type conversion yok.
	b = 10; // sentaks hatas�
	b = (struct Data)10; // sentaks hatas�
	
	struct Token myToken;
	//b- farkl� yap� t�rleri aras�nda da sentaks d�n���m� yok.
	b = myToken; // �ki yap� t�r�n�n de elemanlar� ayn� olsa dahi atama yap�lamaz. T�r d�n��t�rme operat�r� de i�e yaram�yor
	b = (struct Data)myToken; // sentaks hatas�

	//c- Atama yaparken de�erleri s�ral� olarak alacak. Yani b = mydata yapt���m�zda x, y ve dval de�i�kenleri s�ras� ile 2, 5, 6.7 de�erlerini alacak.
	b = mydata; // b.x = 2; b.y = 5; b.dval = 6.7; de�erlerini ald�.
		/*
			b.x = mydata.x;
			b.y = mydata.y;
			b.dval = mydata.dval;
			yukar�daki �ekilde oluyormu� gibi d���n 

			b = mydata; yapt���m�zda memcpy �al���yormu� gibi d���nebiliriz.
			memcpy(&b, &mydata, sizeof(mydata)); struct memberlar� contigous oldu�u i�in �at �at �at hepsine atama yapacak.
		*/
	printf("b.x = %d", b.x); // 2
	printf("b.y = %d", b.y); // 5
	printf("b.dval = %d", b.dval); // 6.7

	/*
		�retimde yap�lar�n birbirine kopyalad���n� g�r�cez illaki. Fakat, structlar�n bellekteki boyutu b�y�d�k�e kopyalama i�leminin maliyeti de b�y�yor.
			�ok ihtiya� olmad�k�a b�y�k yap� nesnelerini kopyalamaktan ka��nmal�y�z �zellikle verimin kritik oldu�u uygulamalar/i�lemlerde.
	*/
	// yap�lara ilk de�er verme sentaks� dizilerin ilk de�er verme sentaks�na benziyor. (Agregate deniyor buna)
		// K��eli parantez i�erisine s�ras� ile de�erleri veriyoruz.

	struct Data initData = { 1, 2, 4.2, }; // s�ras� ile int, int ve double de�i�kenlere de�er verdik. 
	/*
		* E�er yap� nesnelerine ilk de�er verilmez ise 0 de�eri ile hayata ba�larlar. -> Bu durum di�er memberlar� de�er al�rsa ge�erli.
			Hi�bir member init edilmez ise, garbage value tutarlar.
		* Pointer t�r�nden bir yap� nesnesi ise NULL pointer ile hayata ba�larlar.
		* trailing comma olabilir. initData nesnesinde oldu�u gibi.
		struct i�erisindeki dizilere nas�l ilk de�er verilebilir?
			struct initData{
				int x, y;
				int ar[4];
				double d;
			};
			struct initData myData = {1, 2, {1, 2,}, 4.2}; // Dizinin elemanlar�na de�er vermeye ba�layaca��m�z yerde bir tane daha k��eli
				// parantez a��yoruz ve ilk de�eri �yle veriyoruz. �lk de�er verilmeyen elemanlar 0 de�eri ile hayata ba�lar.
			struct initData myData2 = {10, 23, 40, 50, 60, 70, 4.2}; bu �ekilde de tan�mlanabilir. Bir sak�ncas� yok
				// bu �ekilde s�sl� parantez olmadan tan�mlama yapmakta bir sak�nca var. E�er dizinin son eleman�n� yazmaz isek derleyici bunu ne oldu�unu anlamaz ve sonraki de�eri
					// diziye yap��t�r�r.
			struct initData myData3 = {10, 3, 5, 7, 4.2}; // burada derleyici "4.2 double t�r�nden bir de�er o zaman 4. atama d de�i�keni i�in" demez, dizinin son eleman�na 4.2
				// de�erini atar (int oldu�u i�in 4 olur) ve d de�i�keni hayata 0 olarak ba�lar.
					// Dizi var ise s�sl� parantez kullanmak daha mant�kl� ve g�venli gibi duruyor.
	*/
/*--------------------------------------------*/
	/* Designated Initializer */
	// Diziler i�in g�rm��t�k, bir tekrar edelim.
	int a[10] = { [3] = 5,[4] = 3, [1] = 2};
		// S�ral� olma zorunluluklar� yok.
		// E�er dizinin boyutu belirtilmez ise dizi i�erisindeki en b�y�k indisin de�eri ile gerekli bellek alan� allocate edilecek compiler taraf�ndan.
	// Yap� t�r�nden nesneler i�in ise dot operat�r�nden sonra member'�n ad�n� yaz�yoruz.

	struct Data designatedInitData = { .dval = 2.4, .x = 5, }; // ilk de�er verilmeyenler 0 olarak ba�layacak.
		// de�er vermenin s�ras�n�n bir �nemi yok(designated init ile)
		// designated init ile hatal� de�er verme riski gidiyor. 
		// Maliyet a��s�ndan hi�bir fark yok.
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
	struct Student s = { 23, 26, "Engin", "Kendarli"}; // �imdi buradaki 23 no mu ya� m�? Belki s�ras� yanl�� yaz�ld�. Bu hatan�n �n�ne ge�mek i�in designated init
	struct Student myStudent = { .no = 31, .age = 25, .name = "Engin", .surname = "Kend" };
	struct Student myStud = { .no = 12, .age = 23, .name = "Kagan", .surname = "Kultigin", .grades = { [0] = 100,[2] = 25} }; // diziler i�inde designated init kullan�labilir. 
}
/*--------------------------------------------*/


struct Ar {
	int a[5];
};
int main(void) {
	int a[5] = { 1, 2, 3, 4, 5 };
	int b[5];
	// b = a; bu YANLI� SENTAKS HATASI. Array decay, b burada rvalue expression	
	
	// yap� nesneleri birbirine atanabilir.

	struct Ar a2 = { 1, 2, 3, 4, 5, };
	struct Ar b2;

	b2 = a2; // bu legal ��nk� struct t�r�nden nesneler birbirine atanabilir. Daha �nce demi�tir strcpy fonksiyonunu �a��rm���z gibi.
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
	// E�er yap� t�r�nden nesneler dinamik olarak allocate edilmi� bir bellek alan�n� tutuyor ise ve bu de�eri ba�ka ayn� t�rden bir yap� nesnesine kopyalan�r ise
		// T* t�r�nden de�i�kenlerin tuttu�u adreslerde yeni yap� t�r�nden nesneye ge�mi� olur.
	struct Data mydata;
	size_t n = 40;
	mydata.iptr = (int*)malloc(n * sizeof(int));
	set_array_random(mydata.iptr, n);
	mydata.cptr = (char*)malloc(n * sizeof(char));

	struct Data another_data;
	another_data = mydata; // sadece pointerlar g�nderilmi� olacak. 
	/*
		�urada ��yle bir problem var. mydata.iptr ve mydata.cptr nesneleri dinamik olarak allocate edilmi� bir belle�in adresini tutuyor. 
			E�er ben another_data �zerinden bu belleklerden birini free() eder isem, mydata.iptr ve cptr art�k dangling pointer haline gelir.
				Ve bunu fark�nda olmasan yaparsak inan�lmaz ba� a�r�t�r. 
	*/
}

struct Number {
	int x, y;
	double d;
};
struct Number g; // global bir struct  Number t�r�nden bir nesne.
	// Bunu bu �ekilde define etmenin bir ba�ka yolu daha var


struct Number2 {
	int x, y;
	double d;
}g1, g2, *ptr = &g1 ,g3 = { 2, 4, 6.2 }; // b�yle yaparak g1, g2, g3 ad�nda struct Number2 t�r�nde 3 adet global de�i�ken tan�mlam�� olduk.
// burada ilk de�er atamas� yapabilir, poiter de�i�kenlerde olabiliyor burada.
// *ptr = &g1; *ptr, yap� t�r�nden bir nesnenin adresini tutuyor.

// Structure tag olmadan da struct kullanabiliriz.

struct {
	int x, y, z;
	double d;
}a, b, c = { 1, 2, 3, .5 }; // sentaks hatas� yok b�yle tan�mlama yapabiliriz. B�yle yap�nca t�r ismi olmayan, ayn� yap� t�r�nden nesneler oluyorlar.
/*
	Kullan�m�;
	* Belirli say�da yap� t�r�nden nesne tutmak istiyoruz. Bu sayede ba�ka, yap� t�r�nden nesne olu�turulam�yor.
	* Kodlara ayn� t�rden ba�ka nesne olu�turma imkan� vermiyoruz bu sayede.
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
	q1 = q2; // bu bir sentaks hatas�. �kisinin de struct_tag'i olmamas�, memberlar�n�n ayn� olmas� ayn� t�rden olduklar� anlam�na gelmiyor
				// ikisi de farkl� t�r. Farkl� t�rler aras�nda implicit/explicit d�n���m YOK.
	struct Point a[5] = { {1, 2}, {3, 4}, {7,8}, {23, 43},[4] = {33, 231} };

}
/*--------------------------------------------*/
struct Data {
	int x, y;
	double d;
};

int main(void) {
	struct Data mydata = { 3, 4, 5.2 };

	&mydata; //ge�erli bunun adresini tutmak i�in struct Data* t�r�nden bir de�i�kene ihtiyac�m var
	struct Data* p = &mydata;
	*p; // atama yapmak istersem gene struct Data t�r�nden bir nesne olmal�

	//*p.x; -> nokta operat�r� i�erik operat�r�nden daha �ncellikli s�k�nt� var. -> *(p.x) anlam�na gelir b�yle ki yanl�� bu. p bir adres
	(*p).x; // do�ru kullan�m� bu �ekilde �ncelik parantezine al�nmas� gerek. Ayn� anlama gelen, g�r�n��� daha kolay olan bir g�sterim var. Arrow operator

														/*					ARROW OPERATOR					*/
	/*
		arrow operat�r� binary infix bir operat�rd�r.
		Sol operand� yap� t�r�yle olu�turulmu� nesnenin ad�, sa� operand� ise o yap� t�r�n�n i�erisinde bulunan member.
		Dot operator, struct i�erisinde bulunan memberlara isimleri �zerinden ula��yordu.
		Arrow operator ise memberlara adresleri �zerinden ula��yor. 
		Arrow operat�rlerinin olu�turdu�u ifadeler lvalue expressiondur.
	*/
	(*p).x; p->x; // bu ikisi ayn� anlamda.
	struct Data a[5] = { 0 };
	a->x = 5; // array decaydan faydalanarak struct data t�r�nden a dizisinin s�f�r numaral� indisine 5 de�erini kopyalayacak.
	a[0].x = 5; // 

	(a + 3)->y = 15; // 3 indisli eleman�na eri�ip 15 de�erini atayacak.
	a[3].y = 15;

	(&mydata)->x = 5; // legal

	// const keyword� pointerlarda oldu�u gibi burada da ayn� anlam ve ama�la kullan�labilir.

	struct Data Eng = { 1, 2, 3.4 };
	struct Data Ken = { 5, 7, .4 };
	// struct Data* ePtr = &Eng; E�er const keyword� * token�ndan �nce olursa, read-only. 
									// Sa��nda olur ise i�erik de�i�ebilir, g�sterdi�i nesne de�i�tirilemez.
	const struct Data* cEng = &Eng;
	*Eng = 5; // sentaks hatas�
	Eng->x = 50; // sentaks hatas�
	cEng = &Ken; // yeni bir nesnenin adresi atanabilir

	struct Data* const coPtr = &Eng;

	coPtr->d = 5; // memberlar�n�n de�erleri de�i�tirilebilir.
	coPTR = &Ken; // sentaks hatas�

	cEng = NULL; // pointer nesnelerine null pointer atanabilir.
	// pointerlar�n sizeof de�erleri di�er pointerlarda da oldu�u gibi 4 BYTE.

	printf("%zu\n1", sizeof(struct Data)); // Bunun sizeof de�eri 2 * int + double;
	printf("%zu\n1", sizeof(cEng)); // bunun sizeof de�eri 4 byte
}
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