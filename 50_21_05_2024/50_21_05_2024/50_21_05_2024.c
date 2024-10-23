/*Storage Specifiers*/

/*
	Volatile(oynak (balina)): Bu keyword ile bir point de�i�keni nitelenebiliyor. Bu keyword ile nitelenen nesnelerin program d��� kaynaklar taraf�ndan m�dahaleler ile de�i�tiribilece�inin
		bilgisi kodu okuyan ki�iye ve derleyiciye veriliyor. D�� g��lerin ma�as� haline geliyor yani.
	Niye bunu kullan�yoruz?
		Sebebi compiler'�n compile timeda �retece�i kodun do�ru olmas�n� sa�lamak. E�er, derleyici nesnenin de�erinin de�i�medi�ini koda bakarak g�r�rse
			o nesnenin bellekten de�erini okumak i�in kod �retmemesi durumu var. Diyelim ki ival adl� bir de�i�kenimiz var. Bu de�i�keni olu�turduk ama projenin hi�bir yerinde
				de�erini de�i�tirmedik. Derleyici bunu g�rd���nde optimizasyon i�in ival'in bellekten de�erini okumak i�in bir kod �retmeyecek. 

	volatile int x = 1000; // global namespace
	int main(void){
		while(x != 0){ // e�er x, volatile keyword� ile define edilmese idi derleyici bu while deyimini while(1) olarak kabul edebilirdi. ��nk� x'in de�erinin de�i�ti�i bir ihtimal yoktu.
			//.. code		// volatile kullanarak, d��ar�dan m�dahale olabilece�i bilgisini veriyoruz.
		}
	}


	int x = 10;
	int main(void){
		volatile int* p = &x; // pointer to volatile int 
		*p; // volatile olan bu. 'p;' de�il  // *p volatile oldu�u i�in pointer'�n g�sterdi�i nesnenin de�erini her seferinde bellekten gidip get etmesi anlam�na geliyor.
		int* volatile p = &x; // volatile pointer to int // p'nin de�erini her �a��rd���mda bellekten get edeceksin demek bu.
	}

	NOT: E�er volatile asterisk(*) atomunun solunda ise, *p yani Type(int mesela) volatile olur ve de�eri bellekten get edilir.
		 E�er volatile asterisk(*) atomunun sa��nda ise, p yani g�sterdi�i adres ne ise bellekten o de�er get edilir. 
			Bellekten get edilme durumu da, o nesneye her eri�im yap�ld���nda belle�e gidip de�erini sorma durumu. Optimizasyon olmad��� i�in b�yle.
---------------------------------------------------
	volatile const int x = 10; // burada ise x nesnesinin bu proje/kod i�erisinde de�i�tirilemeyece�i anlam�na geliyor. 
									//volatile ise d��ar�dan de�i�tirilebilece�ini s�yl�yor. Projenin herhangi bir yerinde eri�im sa�land���nda x'in de�eri  bellekten her seferinde get edilecek.

---------------------------------------------------
int x = 10;
int main(void){
	int* ptr = &x;
	volatile int* p = ptr; // burada d�n���m de s�k�nt� yok.
	/////////
	volatile int* volptr = &x;
	int* ptr2 = volptr; // burada �rt�l� d�n���m yok uyar� mesaj� verecek derleyici.
		const int* -> int* d�n���m� nas�l yanl��sa volatile int* -> int* d�n���m� de yanl��.


}
---------------------------------------------------
restrict (C99): restrict keyword� ile nitelenmi� pointer de�i�kenlerinin unique olmas�n� sa�l�yor. Yani ba�ka bir pointer nesnesi, restrict ile tan�mlanm�� bir pointer de�i�keninin
	g�sterdi�i adresi g�stermeyece�inin garantisini veriyor. Bu garantinin �i�nenmesi ile Undefined Behaviour olu�ur.

	Volatile, const gibi keywordlar hem pointer'� hem de g�sterdi�i nesneyi nitelerken restrict keyword� sadece pointerin kendisini niteliyor.
	
	restrict keyword� ile tan�mlanan pointerlara restrict pointer deniyor.
		En �ok kar��m�za ��kaca�� yer fonksiyonlar�n parametre de�i�kenleri.
	restrict, asterisk atomundan sonra kullan�lmak zorunda e�er �nce kullan�l�rsa sentaks hatas�.

	void func(int* restrict p); // p bir restrict pointer
	int* restrict x = &var;

	int restrict *ptr; // sentaks hatas�
	Pointerlar�n her ikisininde ayn� nesneye eri�mesine pointer-alliasing denir.
	void func(int* px, int* py, int* restrict pz)
	{
	}

	burada px ve py nin pz nin g�sterdi�i nesneyi g�sterme ihtimali yok.bunu sa�l�yor.
		bu derleyicinin daha iyi optimizasyon yapmas�n� sa�l�yor.
	e�er px = pz; yap�l�rsa bu bir UNDEFINED BAHAVIOR	

	�R:
	void func(int* px, int* py, int* restrict pz)
	{
		*px += *pz;

		// *pz ye eri� ve onu registerda tut
		// *pz ye tekrar eri�mek yerine onu registerdaki de�eri ile kullan.
		//restrict olmasayd� px, pz yi g�steriyor olabilirdi ve *px de�i�ince *pz de de�i�irdi.
		// bu de�eride get etmek i�in tekrar memory ye eri�mek gerekirdi. restrict ile bunu
		// ortadan kald�r�yoruz. sadece pz bu de�eri tutabilir ve eri�ebilir.
		//bu �ekilde compiler optimizasyon yap�yor.

		*py += *pz;

	}
	CPPREFERENCE SERGEY ZUBKOV un �rne�i

	void f(int n, int * restrict p, const int * restrict q)
	{
		while(n-- > 0)
			*p++ = *q++; // none of the objects modified through *p is the same
						 // as any of the objects read through *q
						 // compiler free to optimize, vectorize, page map, etc.
	}
	void g(void)
	{
		extern int d[100];
		f(50, d + 50, d); // OK. Kesi�miyor.birincisi d[49] da bitiyor ikinci dizi ise d[50] den ba�l�yor.
							// overlapped blocklar yok.UB DE��L.

		f(50, d + 1, d); // Undefined behavior: d[1] is accessed through both p and q in f
							//d[1] de kesi�iyorlar. UNDEFINED BEHAVIOR.
	}
---------------------------------------------------
	C99 ile memcpy fonksiyonunun parametreleri de�i�ti.
	C99 �ncesi
		void* memcpy(void* vpdest, const void* vsrc, size_t size)
	C99 sonras�
		void* memcpy(void* restrict vpdest, const void* restrict vsrc, size_t size)

	C99 sonras� restrict ile beraber memcpy fonksiyonunda kaynak ve hedefin ayn� olma ihtimali kalmad�.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*															USER-DEFINED TYPES
	Teknik bir anlam olarak kabul et UDT'yi. Tam kar��l���n� d���nme.
	User-Defined Types ile kullan�c� kendi t�r�n� olu�turuyor. T�r sisteminde olmayan yeni bir t�r� ekliyoruz

	Bu arac�, problem domaininde kar��m�za ��kacak olan problemleri ��zebilmek i�in kullan�yoruz.
		��nk�, bir yerden sonra tam, ger�ek say�lar ve char gibi verileri tutabilen veri t�rleri i�e yaram�yor ya da yetersiz kal�yor.
	- Kodun daha okunabilir, anla��labilir olmas� i�in kullan�labiliyor. Mesela, aylara denk gelen bir type yok fakat biz bunu olu�turabiliriz.
	

	C dilinde 3 farkl� ara� var User Defined Types olu�turmak i�in. Bunlar� a�a��daki s�ra ile ��renece�iz
		- structures(yap�(lar))
		- unions(birlik(ler))
		- enumarations	(numaraland�rma(lar))


	Structure Type:Problem domainindeki bir varl��� ��z�m domaininde tan�mlamak i�in olu�turulan bir t�r.
		

	Sentaks�

	keyword		structure_tag 
	struct		Data{ // Bu �ekilde i�erisi bo� olursa CPP'de ge�erli fakat C'de ge�ersiz. 
	
	}; -> struct'�n bitti�ini g�stermek i�in terminator koymak zorunday�z.
		// Struct i�erisindeki bildirimlere membr deniyor ve C en az 1 tane member istiyor struct i�erisinde.
	---------------------------------------------

	struct Data{
		int x, y;
		double dval;
	};
	int main(void){
		struct Data mydata; // struct data t�r�nden bir de�i�ken yarat�ld�.
								// CPP'de Data y�  bir T�r olarak direkt kullanabiliyoruz. C'de struct Data �eklinde yazmak zorunday�z.
	}
	// her definitionda struct kullanmak vergozite(kod kalabal���) sebep olabilir. Bunun �n�ne ge�mek i�in typedef kullan�yoruz

	
	int main(void){
		struct Data mydata2; // derleyici bu tan�mdan sonra bellekte struct'�n memberlar� kadar yer ay�r�yor. Struct tan�m� yap�ld���nda de�il!
								// burada sadece derleyiciye Struct hakk�nda bilgi veriyoruz.
	}
//	Derleyici bu nesne i�in memberlar�n�n toplam� kadar byte yer ay�r�yor fakat bunu struct bildiriminde de�il struct Data
		kullan�larak yap�lan tan�mda yer ay�r�yor. Ama padding hizalama konusunda g�r�lecek daha fazla yer ay�rd���da g�r�lebilir.
			�leride g�r�lecek.

	- Nesnelerin bellekteki s�ralamas� struct i�erisindeki tan�m s�ralar� ile ayn� olacak. Yani struct memberlar� contiogous.
	- mydata nesnesinin kendi adresi ile mydatan�n ilk eleman�n�n adresi ayn�
	- struct data t�r�nden bir nesnenin adresini t�r d�n���m� ile struct data t�r�n�n ilk eleman�n�n adresine d�n��t�rebiliriz.
	- struct'�n bellekte kaplayaca�� yer sizeof(member_type) + sizeof(member_type) �eklinde. E�er bir structta 2 int 1 double var ise
		(sizeof(int) * 2) + sizeof(double) �eklinde teorik olarak do�ru kabul edebiliriz. �leride g�rece�imiz alignment konusu ile daha detayl�
			g�rece�iz. Daha fazla yerde ay�rabiliyor.

	- User defined types;
		*Global de�i�ken olabilirler
		*Yerel de�i�ken olabilirler
			-Statik
			-Dinamik �m�rl� olabilirler
		*Fonksiyonun parametre de�i�keni olabilir.
*/
struct Data {
	int x, y;
	double d;

};
struct Data gdata; // struct Data t�r�nden global bir de�i�ken oldu
						// �u anki hali ile di�er dosyalar taraf�ndan eri�ilebilir. Sadece bulundu�u kaynak dosyas�na ba�l� yapmak istiyor
							// isek static keyword� ile tan�mlanmal�.
static struct Data sgdata; // global and static, sadece 50_21_05_2024.c dosyas� i�erisinde eri�ilebilir.

void foo(void) {
	struct Data foo1;
}
void bar(void) {
	static struct Data bar1;
}
void foobar(struct Data param) { ; }
//////////////////////////////////////////////////

/*
			�NEML� NOT
	struct t�r� ile olu�turdu�umuz nesne, struct'�n i�erisinde bulunan memberlar�n�n t�r�nden birine atanmaz.
		Memberlar�n�n birle�erek/ortak olu�turdu�u yap�y� kullan�r. Yani i�erisinde 2int 1double var diye type deduction gibi bir �ey olmaz.
			int ve double'lar�n birle�imi ile olu�an yap�y� kullan�yoruz.	
*/

/*
	Neler struct member olabilir?
		-Ger�ek, tam say�lar olabilir
		-Pointer de�i�ken olabilir(object pointer, function pointer vs)
		-Dizi olabilir
		-Multidimensional array olabilir.
		-Struct'�n elemanlar� gene struct t�rlerinden olabilir.
		-const, static gibi keywordleri alabilirler.

	-E�er statik ve global struct t�r�nden nesnelere ilk de�er verilmez ise 0 de�eri ile hayata gelecekler. Primitive t�rlerin statik veya
		global define edilmesiyle ayn� �ekil.
	-Yap�lar�n elemanlar� fonksiyon OLAMAZ. CPP'de fonksiyonda olabiliyor, bunlara member function deniyor.

*/
struct Point {
	double x, y;

};
struct struct_members {
	int x, y; // tam say� olabilir
	int* xptr, yptr; // pointer t�r�nden olabilir
	int (*fp)(int); // function pointer t�r�nden olabilir
	int arr[10]; // dizi olabilir
	int mdarr[10][20]; // �ok boyutlu dizi olabilir
	struct Point mypoint; // struct t�r�nden elemana sahip olabilir.
	struct Point mypointarr[5]; // struct Point t�r�nden, i�erisinde 5 adet o t�rden tutabilen bir array
};
int main(void) {
	struct Point arr[10]; // elemanlar�n�n t�r� struct Point t�r�nden olan bir dizi olabilir
	const struct Point point[5] = { 1., 2., }; // const ile tan�mland�, readonly art�k.
	struct Point px;
	// sizeof de�eri nas�l bulunabilir?

	sizeof(px); // bu �ekilde de yaz�labilir
	sizeof px; // bu �ekilde de yaz�labilir
	sizeof(struct Point); // bu �ekilde de yaz�labilir
	sizeof struct Point; // bu �ekilde yaz�lamaz. Hat�rlatma: Veri t�rleri parantez i�erisinde yaz�lmak zorunda.
	//////////
	struct Point point;

	point; // bu  bir expression statement ve t�r� struct Point.
	&point;		// lvalue expression bundan dolay� addressof operat�r�n�n operand� olabilir.
}
/*-------------------------------------------------------------------------------*/
/*
	struct'�n memberlar�na eri�mek i�in 2 adet operat�r�m�z var. Bu operat�rlere dilin standart� taraf�ndan 
		'member selection operators' deniyor. Necati hocan�n olu�turdu�u operat�r �ncelik tablosunda ilk s�rada yer al�yor.
	�ki operat�rde infix, binary. Bu operat�rler dot operator(.) ve arrow operator(->)
	Bu operat�rler yap� nesnesinin(struct) elemanlar�na eri�mek i�in kullan�l�yor.
		-Dot operator, yap� nesnesinin eleman�na kendisi yoluyla eri�ir
		-Arrow operator, yap� nesnesinin eleman�na adresi yoluyla eri�ir.


	---------------
1	()	[]	.	->	Soldan sa�a 
	---------------
*/
/*
* 	-----------------DOT OPERATOR-----------------	*
		1-a)Binary infix bir operat�rd�r.
		2-a)Dot operat�r�n�n kullan�m� �u �ekilde. lvalue_olan_bir_yap�_t�r�nden_nesne.lvalue_olan_nesnenin_yap�s�nda_bulunan_member
*/
struct Eng {
	int x, y;
	int a[6];
	double d;
	struct Kend kendarli;
};
struct Kend {
	int a, b, c;
};
int main(void) {
	struct Eng ex;
	ex.x; // 2-a k�sm� i�in buras� ve 1-a. 'ex' struct Eng t�r�nden bir lvalue nesne. x ise struct Eng i�erisinde bulunan memberlardan birisi.
	ex.p; // sentaks hatas� ��nk� p adl� bir member yok.
	ex.d; // bu bir expression statement ve t�r� double. ��nk� eng yap�s�n�n i�erisindeki d eleman�n�n t�r� double ve d'ye eri�iyoruz b�yle yazarak.
	// lvalue expression 
	++ex.x; //l value expression oldu�u i�in legal.
	&ex.x;
	ex.a; // array to pointer conversion (array decay) ge�erli burada.
	int* pa = ex.a; // pa pointer de�i�keni, struct Eng i�erisinde bulunan a'n�n ilk eleman�n�n adresini tutuyor �u anda.

	/* arrow operat�r� i�in k���k �rnekler. �leride g�r�cez arrow operat�r�n� */
	int x = 10;
	int* p = &x; //pointer to int t�r�nden bir de�i�ken kullan�yoruz x'in adresini tutmak i�in
	// yap� t�r�nden nesnelerinde adresini tutmak i�in pointer de�i�kenlerine ihtiyac�m�z var
	struct Eng myEng;
	struct Eng* p = &myEng;

	// p �zerinden yap� t�r�n�n i�eri�ine nas�l eri�ebiliriz?
	*p; // bu �ekilde yazarsam p'nin g�sterdi�i myEng de�i�keninin adresine/kendisine eri�irim. Peki myEng'in yap� t�r�n�n sahip
			// oldu�u memberlara nas�l eri�ilir?
	*p.x; // bu �ekilde yaz�l�rsa operat�r �nceli�inden dolay� derleyici bunu *(p.x) �eklinde okur bu da yanl��.
	(*p).x; // bu �ekilde yaz�labilir fakat b�yle yaz�nca da 3 tane operat�r kullanm�� olduk.s
	p->x; // (*p).x; yazmak ile ayn� �ey. Burada ise 1 tane operat�r kullan�yoruz.
	/*------------------------------------------*/
	// Bir yap� nesnesi anlam�na gelen bir ifade C dilinde sadece 4 operat�r�n operand� olabilir.
	myEng.a; // nokta operat�r�
	sizeof(myEng); // sizeof operator�
	&myEng; // addressof operator�
	myEng =; // atama operat�r�
	/*
		1- Dot operat�r�n�n operand�
		2- sizeof operat�r�n�n operand�
		3- addressof operat�r�n�n operand�
		4- atama operat�r�n�n operand�
			bu operat�rler d���nda operat�r kullan�lamaz.
	*/
	// ayn� ifadede birden fazla nokta operat�r� kullan�labilir

	myEng.kendarli.a; // Daha �nce dedi�imiz gibi yap�lar�n memberlar� yap� t�r�nden olabilir. 
						// kendarli struct Kend yap� t�r�ne ait bir eleman. Kend yap� t�r�n�n elemanlar�na eri�mek i�in birden fazla dot operat�r kullan�labilir
	
	// size_t t�r�nden bir ifade constant expression
	char buf[sizeof(struct Eng)];
}

