													/* HANDLE TEKNÝÐÝ */
/*
	Handle Tekniði Linked List'e baðlý bir yöntem deðil. Bir kütüphane oluþturma tekniði
	HANDLE LAR SADECE BAÐLI LÝSTELERDE YOK.HERYERDE KULLANILABÝLÝYOR.
	Örnekler bir önceki StudentList üzerinden yapýlýyor. Oradaki kaynak ve baþlýk dosyalarýný da kullanýn.

	StudentList kullanarak 2 ayrý liste oluþturabilir miyiz? Mesela, sýnýftan geçenler ve kalanlar. Hayýr Linked List ile bu mümkün deðil.
		Linked List kullanýrken 2. listeyi oluþturmak için önce ilk liste tamamen boþaltýlmalý ve baþka bir kod tarafýndan tekrar tekrar çaðýrýlarak doldurulmalý.

	StudentList örneðini yaparken fonksiyonlar iþlemlerini yapabilmek için 2 adet internal-linkage'a ait(client kod göremiyor bu nesneleri) global nesne kullanýyordu.
		Bunlar gpfirst ve gsize. Bir liste için 2 tane bu deðiþkenden gerekmiþti. 2. liste için, fonksiyonlar iþlemlerini yapabilmesi için, 2 tane daha ayný nesneye ihtiyaç duyacaktý. 
			Handle tekniði bize bunu saðlýyor. Her list için gereken deðiþkenleri saðlýyor. Bunu da, ortak kullanýlan nesneleri bir yapýnýn elemaný yaparak saðlýyor.


		Bu sayede her yeni link için yeni bir deðiþken tanýmlamak yerine yapý türünden bir nesne kullanarak yapabiliyoruz bu iþlemi.
	struct NewLink{
		int data1, data2;
	}; // Bu þekilde her seferinde fonksiyona o nesnelerin adresini tek tek yollamak yerine struct NewLink türünden bir nesnenin adresini yolluyoruz.
	
		Bu yapý nesnelerinin oluþturulmasýnýn da kolay bir yolu var. StudentList'i düzenlerken daha detaylý þekilde ya burada ya da kaynak dosyasýnda not alýrým.
			Bu yapýlana Open/Create iþlemi denir. Bu fonksiyon oluþturulan yeni struct'ýn adresini geri döndürecek.

			struct NewLink* create_newlink(???);
		
		Eðer client kod yeni bir link oluþturmak isterse create_newlink fonksiyonunu çaðýracak ve bu fonksiyonun döndürdüðü adresi tutacak.
			Ýþlem yapan fonksiyonlarda bu geri döndürülen pointerý isteyecek client koddan. Bu tarz pointerlara da 'Handle' deniyor.

		Döndürülen adresle iþlemler yapýlýp o þekilde býrakýlýrsa, yani nodelar free edilmezse 'kaynak sýzýntýsý' olur. 
			Bunu yapmak içinde yardýmcý bir fonksiyon daha kullanýcaz. Bu yapýlana destroy/close iþlemi denir.

		CPP'de bu tarz iþlemlere gerek yok.	
			OOP dillerindeki constructor destructor gibi fonksiyonlar bu iþe yarýyor. 

		struct List { 
			Node* gpfirst;
			size_t gsize;
			// void* -> veri elemanlarýný direkt eriþimi engellemek, daha fazla gizlemek için void* kullanýlabiliyor.
		};


int main(void) {
	// student_list_test.txt 
}
*/



													/*						Alignment(Hizalama)						*/
/*
	Ýþlemciler belirli iþlemleri yapmak için belleklere eriþiyorlar.
		Ýþlemciler eriþtikleri bu nesnelerde get,set vs gibi iþlemler yapýlabilmeleri için, bu nesnelerin 2-4-8'in katlarý olan adreslere yerleþtirilmesi gerekiyor.
			Daha rahat eriþmeleri için yapýlýyor bu 'hizalama' ve iþlemciden iþlemciye deðiþebilir. Buna alignment requirement deniyor. Sisteme baðlý.
				Mesela int nesnelere daha rahat eriþmek için(benim sistemimde) 4'ün katlarý kullanýlýyor.
	 Eðer iþlemcinin belirlediði alignment requirement'a uygun sýralanmaz ise;
		- (iþlemcinin türüne baðlý) Ekstra maliyet ile eriþir o yerlere
		- Öyle bir eriþim Donanýmsal ya da yazýlýmsal bir hata olur.




int main(void) {

	int x = 10, y = 20;

	double d1 = .4, d2 = 3.2;

	printf("%p\n", &x); // 4'ün katý olacak
	printf("%p\n", &y); // 4'ün katý olacak
	printf("%p\n", &d1); // 8in katý olacak
	printf("%p\n", &d2); // 8in katý olacak 
		// Ýþte buna alignment requirement
}
*/
/*
	C11 ile eklenen bir keyword ile bunu elde edebiliyoruz.
	_Alignof(T) // compile time operatörü
		Bu keyword/operatör operand olarak aldýðý türün alignment requirement deðerini gösteriyor. 
	struct nesnelerinin de alignment requirementý vardýr. sizeof deðeri ile karýþtýrma.

	define makrosu ile yapýlan taným ile alignof þeklinde de kullanýlabilir. Bir farký yok ayný iþlem yapýlýyor. 
		bu makro baþlýk dosyasý içerisinde yapýlmýþ halde. (#include <stdalign.h>)
#include <stdalign.h>
#include <stdio.h>
struct Eng {
	int x, y, z;
	double d1, d2;
};
int main(void) {
	printf("%lld\n", _Alignof(char));
	printf("%lld\n", _Alignof(int));
	printf("%lld\n", _Alignof(double));
	printf("%lld\n", _Alignof(struct Eng ));

}
*/

/*
	Bazý sebeplerden dolayý, performans ya da baþka bir þey, bu alignment requirement'ý deðiþtirebiliyoruz.
		Bunu yapmamýzý saðlayan keyword ise _Alignas(kat). Bunu kullanarak int için 4'ün katlarý yerine 8in katlarý þeklinde yerleþtirebiliriz.
			Kat yerine kaçýn katýn olmasýný istiyor isek onu yazýyoruz.


	Her struct'ýn alignment requirement'ý olduðu gibi memberlarýnýnda var. Örneðin.

		struct Eng{
			char c1;
			int x;
			char c2;
		};
	Nesne		Adres
	c1			1000 // c1 nesnesi 1000. adreste 
	x			1001 // bu hem olabilir hem de yanlýþ. Ekstra maliyet ile x'e eriþilebilir(iþlemciye baðlý) ya da bu hata(yukarýda bahsettim)
	

	Padding byte denilen bir þey var. Padding byte, alignment requirement için uyulmasý gereken kurallara uygun þekilde kullanýlmayan bytelerý dolduruyor.
		int için 4'ün katlarý olmasý gerekiyor. char için 1'in katlarý(XD)

	Nesne		Adres
	c1			1000 // Þimdi bundan sonraki 3 byte padding bytelar ile doldurulacak. Bu sayede int nesnesi 4ün katý olan bir byteta olabilecek.
	pdbyte		1001 // bu padding bytelar bir nesneye baðlý deðil.
	pdbyte		1002
	pdbyte	1	1003
	x			1004
	x			1005
	x			1007
	x			1008
	c2			1009
	pdbyte		1010
	pdbyte		1011
	Özet olarak, padding byteler 2 þekilde kullanýlýyor.
		- Nesnenin alignment gereksinimlerini karþýlamak için kullanýlmayan ve/veya kullanýlamayacak olan nesneleri padding byteler ile dolduruyor.
			int nesnesi 4'ün katlarý olmasý gerektiði için 2 veya 3'ün katlarýnda kullanýlamaz. Bunlarý padding byte ile dolduracak ve 4'ün katlarýnda saklanacak.
		- Bir yapý nesnesinin sonunu, kullanýlmayan veya orada bir nesne olmayan, padding byte kullanýlmamasý için kapatýr.

	Yapýnýn içerisindeki memberlarýn yazým sýrasý sizeof deðerinin deðiþmesine sebep olabilir.
	Yapý nesnesinin sonunda padding byte olabilir fakat baþýnda padding byte olamaz. 

#include <stdio.h>
#include <stdalign.h>
struct Eng {
	int x, y, z;
};
typedef struct Agr {
	char c1;
	int x;
	char c2;
}Agr;

struct Agr2 {
	int x;
	char c1;
	char c2;
};

int main(void) {
	printf("%zu\n", sizeof(struct Eng));// sizeof deðeri 12, çünkü bütün elemanlar padding byte'a gerek duymadan alignment gereksinimini karþýlýyor.
	printf("%zu\n", sizeof(struct Agr));// sizeof deðeri 12, (normalde olmasý gereken 6) fakat 6 bytelýk padding byte var.
	printf("%zu\n", sizeof(struct Agr2));// sizeof deðeri 8, çünkü elemanlarýnýn taným sýrasý farklý olduðu için padding byte kullanýmý da farklý.
											// char c1 1001, char c2 1002 adresleriin tutuyor. int alignment requirement 4 ve katý olduðu için 1003 ve 1004 adreslerine
												// birer adet byte ekleniyor(toplam 2 byte) birde struct'ýn elemanlarýnýn bittiði yere 2 padding byte daha ekleniyor bu sayede 8 oluyor.
	Agr myagr;
	// &myagr = &myagr.c1; Yapý nesnesinin baþýnda padding byte olmaz. Bu bilgiye göre, yapý türünden oluþturulan bir nesnenin adresi ile o yapý türünün ilk elemanýnýn adresi ayný
		// olmak zorunda.
	printf("%02p %02p ", &myagr, &myagr.c1); // burada ikisinin de adresi ayný.
}
*/
/*
	Padding byte " " 

	- Ýþlemlerin daha küçük maliyetle yapýlmasýný saðlýyor.
	- Yapý nesnelerinin dizimine göre yapý nesnesinin ihtiyacý olduðu bellek alanýnýn miktarý artabilir veya azalabilir.
		padding byte'a baðlý bu.
	- Yapý nesnesinin elemanlarýný pointer aritmetiði kullanarak eriþmemeliyiz. Çünkü pointer aritmetiði padding bytelarý dikkate almaz. 
		Padding byteler, garbage value olacaðý için bu adreslerin dereference edilmesi UB.
		Padding bytelarý dikkate alarak istenen nesnenin adresini alan bir fonksiyonel makro var. stddef.h içerisinde tanýmlanmýþ olan bi fonksiyonel makroya
			offsetof(s, m) deniyor.


	#include <stddef.h>
	#include <stdio.h>
	#include <stdalign.h>
	typedef struct Data {
		char c1;
		int x;
		char c2;
	}Data;
	int main(void) {
		Data mydata = { 1, 213120, 10 };
		char* p = &mydata.c1;
		printf("%d\n", *(int*)(p + 2)); // bu undefined behaviour çünkü pointer aritmetiði padding bytelarý dikkate almayacaðýndan dolayý çöp deðere eriþiriz bu da UB.

		//	Padding bytelarý dikkate alarak istenen nesnenin adresini alan bir fonksiyonel makro var. stddef.h içerisinde tanýmlanmýþ olan bi fonksiyonel makroya
		//		offsetof deniyor.

		printf("%zu\n", offsetof(Data, c1));
		printf("%zu\n", offsetof(Data, x));
		printf("%zu\n", offsetof(Data, c2));

	}	
*/ 

/*
	offsetof makrosunu nasýl implemete edilir
		1-Öncellikle struct türünü ve member türünü alan 2 adet fonksiyonel makro operandý tanýmlýyoruz.
			#define Offsetof(s, memberT)
		2-Daha sonra s'i kullanarak 0'ýn adresini alýyoruz.
			#define Offsetof(s, memberT)		(s*)0
		3-Struct'ýn aldýðýmýz 0'ýn adresi üstünden member'a eriþiyoruz. Bunu yapmadan önce (s*)0'ý öncelik parantezine alýyoruz.
			#define Offsetof(s, memberT)		((s*)0)->m // (
		4-Daha sonra bu eriþtiðimiz member'ýn adresini alýyoruz.
			#define Offsetof(s, memberT)		&(((s*)0)->m) // adresini almadan önce tüm þeyi kapsamasý için tüm iþlemi parantez içine alýp ve öyle adresini aldýk.
		5-Þu an elimizde olan deðer bir adres. Bunu size_t türüne cast ederek 0, 1 ,2, 4, 8 vs vs gibi deðerler elde ediyoruz.
			#define Offsetof(s, memberT)		(size_t)(&(((s*)0)->m)) 
			
*/
/*
	offsetof makrosu mülakatlarda soruluyormuþ.
		Sen nasýl tanýmlardýn gibisinden.

#include <stddef.h>
#include <stdio.h>
#include <stdalign.h>
#include <string.h>
#define clear_struct(x) (memset(&x, 0, sizeof(x)))
typedef struct Data {
	char c1;	//0
	int x;		//4
	char c2;	//8
}Data;
int main(void) {
	Data mydata = { 1, 2, 3 };
	Data* dataptr = &mydata;
	// data üzerinden x'in adresini almak istiyorum.
	int* x3 = (int*)((char*)dataptr + offsetof(Data, x)); //char* a cast ediyoruz ki yapýlan iþlem byte byte yapýlsýn int* veya bþaka bir pointer deðiþkenine yapsaydýk iþlem doðru olmazdý
	int* x2 = (int*)((int*)dataptr + offsetof(Data, x));
	int* x1 = ((int*)dataptr + offsetof(Data, x));
	//////////////////////////

	Data d1 = { 12, 129, 45 };
	Data d2 = { 12,	129, 45 };
	// bu yapý türünden nesnelerin eþitliðini kontrol etmek için her iki yapý nesnesinde de karþýlýk gelen nesnelerin karþýlaþtýrýlmasý gerekiyor.
	if (d1.c1 == d2.c1 && d1.x == d2.x && d1.c2 == d2.c2); // bu ok ama 10 tane eleman olduðunu düþün. O zaman ne olacak?

	// string.h içerisinde bulunan memcpy ile bellek bloklarýnýn karþýlaþtýrmasýný yapabiliyorduk.
	if (!memcmp(&d1, &d2, sizeof(Data))) // eðer eþit ise 0 deðeri döneceði için ! kullanýyoruz
		printf("Yapilar ayni\n");
	else
		printf("Esit degil\n");

	// yukarýdaki kod doðru gözüküyor fakat eþit deðil kýsmýna girecek. Bunun sebebi ise padding bytes. strcmp fonksiyonu paddingbytesý dikkate almýyor.
		// eðer iki yapý nesnesini karþýlaþtýrmak istiyor ise padding bytelarý 0 yapmamýz gerekiyor. Bunu da memseti bir fonksiyonel makroya çevirerek yapýyoruz -> clear_struct

	//memset(&d1, 0, sizeof(d1));
	//memset(&d2, 0, sizeof(d2)); bu þekilde yazmak yerine
	Data data1;
	Data data2;
	clear_struct(data1);
	clear_struct(data2);
	// þimdi ise struct'ýn memberlarýna deðerleri veriyoruz.
	data1.c1 = 32;		data1.x = 12521; 	data1.c2 = 43;
	data2.c1 = 32;		data2.x = 12521;	data2.c2 = 43;
	if (!memcmp(&data1, &data2, sizeof(Data)))
		printf("Yapilar ayni\n");
	else
		printf("Esit degil");
	// Artýk yapilar ayný kýsmýna girecek çünkü paddingbyteler çöp deðer yerine 0 deðerinde
	// Eðer yapýlar karþýlaþtýrma iþlemi için dýþarýdan geliyor ise temizlenmiþ halde bize gönderilmesi gerek. Eðer temizlenmediyse tek tek tüm elemanlarý karþýlaþtýrmamýz gerekli. Baþka yolu yok.
}
*/
/*
	Eðer önceliðimiz bellek/alan kullanýmý ise, eriþim maliyetinin düþüklüðü gibi durumlar önemli deðil ise 
		derleyicinin padding byte kullanmasýný belirli makro/fonksiyonlarla engelleyebiliriz. (derleyici de izin vermeli) 
	Bunlardan bir tanesi
		#pragma pack(1) bunu yazdýktan sonra padding bytelar kullanýlmayacak bir deðiþkenin bittikten sonraki byteýndan sonra diðer deðiþken baþlayacak.
			Alignment requirements göz ardý edilecek.



#include <stdio.h>
typedef struct Data {
	double dval;
	int a, b, c;

}Data;
int main(void) {
	float f = 4.12421f;
	// printf("%d",*(int*)f); // tanýmsýz davranýþ.
	// standartýn belirttiði durumlar dýþýnda(compatible types), bir nesnenin deðerini okumak/deðiþtirmek/kopyalamak için baþka bir türden adrese dönüþtürüp derefence etmemeliyiz.
		// sizeof deðerlerinin ayný olmasý yapýlabileceði anlamýna gelmez! Standartýn belirlediði bazý senaryolarda ayný olur. Bunlara compatible types denir.

	// ayný tam sayýlarýn iþaretli/iþaretsiz arasýnda hallerinin arasýndaki deðiþim
	unsigned int x = 874353987;
	int y = *(int*)&x; // bunlar compatible type. Çünkü ayný sayý türünün signed/unsigned tür dönüþümü.

	//char türlerine yapýlan dönüþümlerde de undefined behaviour yok. Çünkü iþlem byte byte yapýlýyor
	double dval = 4.1652316;
	unsigned char* p = (char*) &dval;
	for (size_t i = 0; i < sizeof(dval); i++) {
		printf("%u\n", p[i]);
	}

	// Bir pointer türünden void* / void* bir pointer türüne
	double d = 412.12421;
	void* vp = &dval;
	double* dp = (double*)vp;
	printf("%f", *dp);

	//Yapý nesnesinin kendi adresi ile yapý nesnesinin ilk elemanýn adresi ayný olmak zorunda ve aralarýnda dönüþüm yapýlabilir.
	Data mydata = {3.12321, 1, 2 ,3};
	printf("%f", *(double*)&mydata);
}
*/
// Þu anlýk yapýlar bitti devamýný ileride bitiricez.


/*----------------------------------------------------------------------------------------------------------------------------------------------*/



													/*						UNIONS(BIRLIKLER)						*/
/*
	Çok kýsa sürecek bu kýsým. Bir çok kýsmý structures ile ayný bundan dolayý sadece farklarýndan  bahsedilecek.

	- Unionlarýn elemanlarýnýn adresleri ayný. Ayný bellek alanýný paylaþýyorlar
		Yani bir birlik nesnesinin adresi ne ise bütün elemanlarýnýn adresi ayný.
	- Birliklerde sadece bir elemana ilk deðer verilebilir. struct gibi tek tek tüm elemanlara verilemez.
		Belirli bir elemana ilk deðer vermek istiyor isek ya o elemaný yapý nesnesinin ilk elemaný yapacaðýz ya da designated initializer kullanmak zorundayýz.

	Neden? 
		Birliklerin en çok kullandýlýðý tema; bir verinin farklý biçimlerde temsil edilmesi. 


typedef struct  {
	int a, b, c;
	double d;
}sData;
typedef union{
	int a, b, c;
	double d1, d2;
}uData;


int main(void) {
	printf("sData: %zu\n", sizeof(sData)); // sizeof 4
	printf("uData: %zu\n", sizeof(uData)); // sizeof 4
	// yukarýdaki printf çaðrýlarýndan sonra hem struct'a hem de union'a birer adet daha int eleman eklendi (int b)
	printf("sData: %zu\n", sizeof(sData)); // sizeof 8
	printf("uData: %zu\n", sizeof(uData)); // sizeof 4
	// yukarýdaki printf çaðrýlarýndan sonra hem struct'a hem de union'a birer adet daha int eleman eklendi (int c)
	printf("sData: %zu\n", sizeof(sData)); // sizeof 12
	printf("uData: %zu\n", sizeof(uData)); // sizeof 4
	// yukarýdaki printf çaðrýlarýndan sonra hem struct'a hem de union'a bir adet double eleman eklendi (double d)
	printf("sData: %zu\n", sizeof(sData)); // sizeof 24
	printf("uData: %zu\n", sizeof(uData)); // sizeof 8

	// Fark þu. struct'ýn sizeof deðeri elemanlarýnýn sizeof deðerinin toplamý iken
		// unionda bu durum sizeof deðerince en büyük elemanýn deðeri. Double 8 byte olduðu için ekrana 8 yazdýrýyor.
	uData mydata;
	printf("\nmydata:		%p\n", &mydata);
	printf("mydata.a:	%p\n", &mydata.a);
	printf("mydata.b:	%p\n", &mydata.b);
	printf("mydata.c:	%p\n", &mydata.c);
	printf("mydata.d1:	%p\n", &mydata.d1);
	printf("mydata.d2:	%p\n", &mydata.d2); 
	// birlik nesnesinin adresi ile elemanlarýnýn adresleri tamamen ayný
	// bundan dolayý herhangi bir elemanýna deðer kopyalamasý yapýldýðýnda bütün elemanlarýnýn deðeri deðiþir.	


	uData myunion = { 12 }; // Birliklerde sadece bir elemana ilk deðer verilebilir. struct gibi tek tek tüm elemanlara verilemez.
	uData myunion2 = { .c = 14 }; // designated initializer
	// uData myunion3 = { 12, 34, 45 }; // Yanlýþ
	// NOT: SADECE 1 INITIALIZER KULLANILABILIR.
}
*/

//Birliklerin en çok kullandýlýðý tema; bir verinin farklý biçimlerde temsil edilmesi. 
#include <stdint.h>
union Pack {
	uint32_t uval;
	uint8_t ar[4];
};
// ikisinin de sizeof deðeri 4 o yüzden bu union'ýn sizeof deðeri 4
// fakat uint32 32 bit iken, uint8 her elemaný 1byte olan 4 elemanlý bir dizi. Dýþarýdan gelen bytelarýn farklý þekillerde temsil edilebilmesi için 
	// iki farklý nesne var


/*
// Bunu C gibi bir dilde nasýl temsil edebiliriz?
	// genellikle türünü belirten bir struct ve union ile yapýlýr
typedef struct {
	int type; // veri türünün ne olduðunu bilgisi, enum da olabilir, 0 - Byte, 1 - uval, 2 - dval, 3 - str[16]
	union { // anonymous union
		unsigned char Byte; 
		unsigned int uval;
		double dval;
		char str[16];
	};
}Json;

int main(void) {
	Json jx;
	jx.type = 0;
	if (jx.type == 0)
		jx.Byte = 178;
	// bu þekilde oluþturulan unionlara discriminated union ya da tagged union deniyor. Ve çok sýk kullanýlan bir yapý.
}
*/
#include "Date.h"
#define		CHAR	0
#define		INT		0
#define		DOUBLE	0
#define		DATE	0

typedef struct {
	int type; // Hangi tür bir veri tuttuðunu söyleyecek. Bu type union içerisinde bulunan elemanlarýndan hangsinin kullanýlacaðýný söyleyecek aslýnda bize
	union {
		char c;
		int i;
		double d;
		Date dt;
	};
}Data;
int main(void) {
	Data mydata;
	// hangi türden bir deðiþken tutmak istiyorsak type'ý ona göre cast ediyoruz. Yukarýda bir kaç tane makro tanýmladýk.

	mydata.type = CHAR; // char tuttuðunu gösteriyoruz.
	mydata.c = 'F';

	mydata.type = DOUBLE; // double tuttuðunu gösteriyoruz.
	mydata.d = .4124;

	// Bir sonraki derste nasýl dizi oluþturabiliriz onu görücez. Dizinin bir elemanýnýn char tutarken diðerinin double tutmasý vs vs.

	Data mydataarr[100]; 

}
