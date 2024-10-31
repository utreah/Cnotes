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
	1:20



}
