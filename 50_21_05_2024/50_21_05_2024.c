/*Storage Specifiers*/

/*
	Volatile(oynak (balina)): Bu keyword ile bir point deðiþkeni nitelenebiliyor. Bu keyword ile nitelenen nesnelerin program dýþý kaynaklar tarafýndan müdahaleler ile deðiþtiribileceðinin
		bilgisi kodu okuyan kiþiye ve derleyiciye veriliyor. Dýþ güçlerin maþasý haline geliyor yani.
	Niye bunu kullanýyoruz?
		Sebebi compiler'ýn compile timeda üreteceði kodun doðru olmasýný saðlamak. Eðer, derleyici nesnenin deðerinin deðiþmediðini koda bakarak görürse
			o nesnenin bellekten deðerini okumak için kod üretmemesi durumu var. Diyelim ki ival adlý bir deðiþkenimiz var. Bu deðiþkeni oluþturduk ama projenin hiçbir yerinde
				deðerini deðiþtirmedik. Derleyici bunu gördüðünde optimizasyon için ival'in bellekten deðerini okumak için bir kod üretmeyecek. 

	volatile int x = 1000; // global namespace
	int main(void){
		while(x != 0){ // eðer x, volatile keywordü ile define edilmese idi derleyici bu while deyimini while(1) olarak kabul edebilirdi. Çünkü x'in deðerinin deðiþtiði bir ihtimal yoktu.
			//.. code		// volatile kullanarak, dýþarýdan müdahale olabileceði bilgisini veriyoruz.
		}
	}


	int x = 10;
	int main(void){
		volatile int* p = &x; // pointer to volatile int 
		*p; // volatile olan bu. 'p;' deðil  // *p volatile olduðu için pointer'ýn gösterdiði nesnenin deðerini her seferinde bellekten gidip get etmesi anlamýna geliyor.
		int* volatile p = &x; // volatile pointer to int // p'nin deðerini her çaðýrdýðýmda bellekten get edeceksin demek bu.
	}

	NOT: Eðer volatile asterisk(*) atomunun solunda ise, *p yani Type(int mesela) volatile olur ve deðeri bellekten get edilir.
		 Eðer volatile asterisk(*) atomunun saðýnda ise, p yani gösterdiði adres ne ise bellekten o deðer get edilir. 
			Bellekten get edilme durumu da, o nesneye her eriþim yapýldýðýnda belleðe gidip deðerini sorma durumu. Optimizasyon olmadýðý için böyle.
---------------------------------------------------
	volatile const int x = 10; // burada ise x nesnesinin bu proje/kod içerisinde deðiþtirilemeyeceði anlamýna geliyor. 
									//volatile ise dýþarýdan deðiþtirilebileceðini söylüyor. Projenin herhangi bir yerinde eriþim saðlandýðýnda x'in deðeri  bellekten her seferinde get edilecek.

---------------------------------------------------
int x = 10;
int main(void){
	int* ptr = &x;
	volatile int* p = ptr; // burada dönüþüm de sýkýntý yok.
	/////////
	volatile int* volptr = &x;
	int* ptr2 = volptr; // burada örtülü dönüþüm yok uyarý mesajý verecek derleyici.
		const int* -> int* dönüþümü nasýl yanlýþsa volatile int* -> int* dönüþümü de yanlýþ.


}
---------------------------------------------------
restrict (C99): restrict keywordü ile nitelenmiþ pointer deðiþkenlerinin unique olmasýný saðlýyor. Yani baþka bir pointer nesnesi, restrict ile tanýmlanmýþ bir pointer deðiþkeninin
	gösterdiði adresi göstermeyeceðinin garantisini veriyor. Bu garantinin çiðnenmesi ile Undefined Behaviour oluþur.

	Volatile, const gibi keywordlar hem pointer'ý hem de gösterdiði nesneyi nitelerken restrict keywordü sadece pointerin kendisini niteliyor.
	
	restrict keywordü ile tanýmlanan pointerlara restrict pointer deniyor.
		En çok karþýmýza çýkacaðý yer fonksiyonlarýn parametre deðiþkenleri.
	restrict, asterisk atomundan sonra kullanýlmak zorunda eðer önce kullanýlýrsa sentaks hatasý.

	void func(int* restrict p); // p bir restrict pointer
	int* restrict x = &var;

	int restrict *ptr; // sentaks hatasý
	Pointerlarýn her ikisininde ayný nesneye eriþmesine pointer-alliasing denir.
	void func(int* px, int* py, int* restrict pz)
	{
	}

	burada px ve py nin pz nin gösterdiði nesneyi gösterme ihtimali yok.bunu saðlýyor.
		bu derleyicinin daha iyi optimizasyon yapmasýný saðlýyor.
	eðer px = pz; yapýlýrsa bu bir UNDEFINED BAHAVIOR	

	ÖR:
	void func(int* px, int* py, int* restrict pz)
	{
		*px += *pz;

		// *pz ye eriþ ve onu registerda tut
		// *pz ye tekrar eriþmek yerine onu registerdaki deðeri ile kullan.
		//restrict olmasaydý px, pz yi gösteriyor olabilirdi ve *px deðiþince *pz de deðiþirdi.
		// bu deðeride get etmek için tekrar memory ye eriþmek gerekirdi. restrict ile bunu
		// ortadan kaldýrýyoruz. sadece pz bu deðeri tutabilir ve eriþebilir.
		//bu þekilde compiler optimizasyon yapýyor.

		*py += *pz;

	}
	CPPREFERENCE SERGEY ZUBKOV un örneði

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
		f(50, d + 50, d); // OK. Kesiþmiyor.birincisi d[49] da bitiyor ikinci dizi ise d[50] den baþlýyor.
							// overlapped blocklar yok.UB DEÐÝL.

		f(50, d + 1, d); // Undefined behavior: d[1] is accessed through both p and q in f
							//d[1] de kesiþiyorlar. UNDEFINED BEHAVIOR.
	}
---------------------------------------------------
	C99 ile memcpy fonksiyonunun parametreleri deðiþti.
	C99 öncesi
		void* memcpy(void* vpdest, const void* vsrc, size_t size)
	C99 sonrasý
		void* memcpy(void* restrict vpdest, const void* restrict vsrc, size_t size)

	C99 sonrasý restrict ile beraber memcpy fonksiyonunda kaynak ve hedefin ayný olma ihtimali kalmadý.
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*															USER-DEFINED TYPES
	Teknik bir anlam olarak kabul et UDT'yi. Tam karþýlýðýný düþünme.
	User-Defined Types ile kullanýcý kendi türünü oluþturuyor. Tür sisteminde olmayan yeni bir türü ekliyoruz

	Bu aracý, problem domaininde karþýmýza çýkacak olan problemleri çözebilmek için kullanýyoruz.
		Çünkü, bir yerden sonra tam, gerçek sayýlar ve char gibi verileri tutabilen veri türleri iþe yaramýyor ya da yetersiz kalýyor.
	- Kodun daha okunabilir, anlaþýlabilir olmasý için kullanýlabiliyor. Mesela, aylara denk gelen bir type yok fakat biz bunu oluþturabiliriz.
	

	C dilinde 3 farklý araç var User Defined Types oluþturmak için. Bunlarý aþaðýdaki sýra ile öðreneceðiz
		- structures(yapý(lar))
		- unions(birlik(ler))
		- enumarations	(numaralandýrma(lar))


	Structure Type:Problem domainindeki bir varlýðý çözüm domaininde tanýmlamak için oluþturulan bir tür.
		

	Sentaksý

	keyword		structure_tag 
	struct		Data{ // Bu þekilde içerisi boþ olursa CPP'de geçerli fakat C'de geçersiz. 
	
	}; -> struct'ýn bittiðini göstermek için terminator koymak zorundayýz.
		// Struct içerisindeki bildirimlere membr deniyor ve C en az 1 tane member istiyor struct içerisinde.
	---------------------------------------------

	struct Data{
		int x, y;
		double dval;
	};
	int main(void){
		struct Data mydata; // struct data türünden bir deðiþken yaratýldý.
								// CPP'de Data yý  bir Tür olarak direkt kullanabiliyoruz. C'de struct Data þeklinde yazmak zorundayýz.
	}
	// her definitionda struct kullanmak vergozite(kod kalabalýðý) sebep olabilir. Bunun önüne geçmek için typedef kullanýyoruz

	
	int main(void){
		struct Data mydata2; // derleyici bu tanýmdan sonra bellekte struct'ýn memberlarý kadar yer ayýrýyor. Struct tanýmý yapýldýðýnda deðil!
								// burada sadece derleyiciye Struct hakkýnda bilgi veriyoruz.
	}
//	Derleyici bu nesne için memberlarýnýn toplamý kadar byte yer ayýrýyor fakat bunu struct bildiriminde deðil struct Data
		kullanýlarak yapýlan tanýmda yer ayýrýyor. Ama padding hizalama konusunda görülecek daha fazla yer ayýrdýðýda görülebilir.
			Ýleride görülecek.

	- Nesnelerin bellekteki sýralamasý struct içerisindeki taným sýralarý ile ayný olacak. Yani struct memberlarý contiogous.
	- mydata nesnesinin kendi adresi ile mydatanýn ilk elemanýnýn adresi ayný
	- struct data türünden bir nesnenin adresini tür dönüþümü ile struct data türünün ilk elemanýnýn adresine dönüþtürebiliriz.
	- struct'ýn bellekte kaplayacaðý yer sizeof(member_type) + sizeof(member_type) þeklinde. Eðer bir structta 2 int 1 double var ise
		(sizeof(int) * 2) + sizeof(double) þeklinde teorik olarak doðru kabul edebiliriz. Ýleride göreceðimiz alignment konusu ile daha detaylý
			göreceðiz. Daha fazla yerde ayýrabiliyor.

	- User defined types;
		*Global deðiþken olabilirler
		*Yerel deðiþken olabilirler
			-Statik
			-Dinamik ömürlü olabilirler
		*Fonksiyonun parametre deðiþkeni olabilir.
*/
struct Data {
	int x, y;
	double d;

};
struct Data gdata; // struct Data türünden global bir deðiþken oldu
						// þu anki hali ile diðer dosyalar tarafýndan eriþilebilir. Sadece bulunduðu kaynak dosyasýna baðlý yapmak istiyor
							// isek static keywordü ile tanýmlanmalý.
static struct Data sgdata; // global and static, sadece 50_21_05_2024.c dosyasý içerisinde eriþilebilir.

void foo(void) {
	struct Data foo1;
}
void bar(void) {
	static struct Data bar1;
}
void foobar(struct Data param) { ; }
//////////////////////////////////////////////////

/*
			ÖNEMLÝ NOT
	struct türü ile oluþturduðumuz nesne, struct'ýn içerisinde bulunan memberlarýnýn türünden birine atanmaz.
		Memberlarýnýn birleþerek/ortak oluþturduðu yapýyý kullanýr. Yani içerisinde 2int 1double var diye type deduction gibi bir þey olmaz.
			int ve double'larýn birleþimi ile oluþan yapýyý kullanýyoruz.	
*/

/*
	Neler struct member olabilir?
		-Gerçek, tam sayýlar olabilir
		-Pointer deðiþken olabilir(object pointer, function pointer vs)
		-Dizi olabilir
		-Multidimensional array olabilir.
		-Struct'ýn elemanlarý gene struct türlerinden olabilir.
		-const, static gibi keywordleri alabilirler.

	-Eðer statik ve global struct türünden nesnelere ilk deðer verilmez ise 0 deðeri ile hayata gelecekler. Primitive türlerin statik veya
		global define edilmesiyle ayný þekil.
	-Yapýlarýn elemanlarý fonksiyon OLAMAZ. CPP'de fonksiyonda olabiliyor, bunlara member function deniyor.

*/
struct Point {
	double x, y;

};
struct struct_members {
	int x, y; // tam sayý olabilir
	int* xptr, yptr; // pointer türünden olabilir
	int (*fp)(int); // function pointer türünden olabilir
	int arr[10]; // dizi olabilir
	int mdarr[10][20]; // çok boyutlu dizi olabilir
	struct Point mypoint; // struct türünden elemana sahip olabilir.
	struct Point mypointarr[5]; // struct Point türünden, içerisinde 5 adet o türden tutabilen bir array
};
int main(void) {
	struct Point arr[10]; // elemanlarýnýn türü struct Point türünden olan bir dizi olabilir
	const struct Point point[5] = { 1., 2., }; // const ile tanýmlandý, readonly artýk.
	struct Point px;
	// sizeof deðeri nasýl bulunabilir?

	sizeof(px); // bu þekilde de yazýlabilir
	sizeof px; // bu þekilde de yazýlabilir
	sizeof(struct Point); // bu þekilde de yazýlabilir
	sizeof struct Point; // bu þekilde yazýlamaz. Hatýrlatma: Veri türleri parantez içerisinde yazýlmak zorunda.
	//////////
	struct Point point;

	point; // bu  bir expression statement ve türü struct Point.
	&point;		// lvalue expression bundan dolayý addressof operatörünün operandý olabilir.
}
/*-------------------------------------------------------------------------------*/
/*
	struct'ýn memberlarýna eriþmek için 2 adet operatörümüz var. Bu operatörlere dilin standartý tarafýndan 
		'member selection operators' deniyor. Necati hocanýn oluþturduðu operatör öncelik tablosunda ilk sýrada yer alýyor.
	Ýki operatörde infix, binary. Bu operatörler dot operator(.) ve arrow operator(->)
	Bu operatörler yapý nesnesinin(struct) elemanlarýna eriþmek için kullanýlýyor.
		-Dot operator, yapý nesnesinin elemanýna kendisi yoluyla eriþir
		-Arrow operator, yapý nesnesinin elemanýna adresi yoluyla eriþir.


	---------------
1	()	[]	.	->	Soldan saða 
	---------------
*/
/*
* 	-----------------DOT OPERATOR-----------------	*
		1-a)Binary infix bir operatördür.
		2-a)Dot operatörünün kullanýmý þu þekilde. lvalue_olan_bir_yapý_türünden_nesne.lvalue_olan_nesnenin_yapýsýnda_bulunan_member
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
	ex.x; // 2-a kýsmý için burasý ve 1-a. 'ex' struct Eng türünden bir lvalue nesne. x ise struct Eng içerisinde bulunan memberlardan birisi.
	ex.p; // sentaks hatasý çünkü p adlý bir member yok.
	ex.d; // bu bir expression statement ve türü double. Çünkü eng yapýsýnýn içerisindeki d elemanýnýn türü double ve d'ye eriþiyoruz böyle yazarak.
	// lvalue expression 
	++ex.x; //l value expression olduðu için legal.
	&ex.x;
	ex.a; // array to pointer conversion (array decay) geçerli burada.
	int* pa = ex.a; // pa pointer deðiþkeni, struct Eng içerisinde bulunan a'nýn ilk elemanýnýn adresini tutuyor þu anda.

	/* arrow operatörü için küçük örnekler. Ýleride görücez arrow operatörünü */
	int x = 10;
	int* p = &x; //pointer to int türünden bir deðiþken kullanýyoruz x'in adresini tutmak için
	// yapý türünden nesnelerinde adresini tutmak için pointer deðiþkenlerine ihtiyacýmýz var
	struct Eng myEng;
	struct Eng* p = &myEng;

	// p üzerinden yapý türünün içeriðine nasýl eriþebiliriz?
	*p; // bu þekilde yazarsam p'nin gösterdiði myEng deðiþkeninin adresine/kendisine eriþirim. Peki myEng'in yapý türünün sahip
			// olduðu memberlara nasýl eriþilir?
	*p.x; // bu þekilde yazýlýrsa operatör önceliðinden dolayý derleyici bunu *(p.x) þeklinde okur bu da yanlýþ.
	(*p).x; // bu þekilde yazýlabilir fakat böyle yazýnca da 3 tane operatör kullanmýþ olduk.s
	p->x; // (*p).x; yazmak ile ayný þey. Burada ise 1 tane operatör kullanýyoruz.
	/*------------------------------------------*/
	// Bir yapý nesnesi anlamýna gelen bir ifade C dilinde sadece 4 operatörün operandý olabilir.
	myEng.a; // nokta operatörü
	sizeof(myEng); // sizeof operatorü
	&myEng; // addressof operatorü
	myEng =; // atama operatörü
	/*
		1- Dot operatörünün operandý
		2- sizeof operatörünün operandý
		3- addressof operatörünün operandý
		4- atama operatörünün operandý
			bu operatörler dýþýnda operatör kullanýlamaz.
	*/
	// ayný ifadede birden fazla nokta operatörü kullanýlabilir

	myEng.kendarli.a; // Daha önce dediðimiz gibi yapýlarýn memberlarý yapý türünden olabilir. 
						// kendarli struct Kend yapý türüne ait bir eleman. Kend yapý türünün elemanlarýna eriþmek için birden fazla dot operatör kullanýlabilir
	
	// size_t türünden bir ifade constant expression
	char buf[sizeof(struct Eng)];
}

