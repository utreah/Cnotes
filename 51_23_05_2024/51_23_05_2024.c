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
	1:20



}
