													/* HANDLE TEKN��� */
/*
	Handle Tekni�i Linked List'e ba�l� bir y�ntem de�il. Bir k�t�phane olu�turma tekni�i
	HANDLE LAR SADECE BA�LI L�STELERDE YOK.HERYERDE KULLANILAB�L�YOR.
	�rnekler bir �nceki StudentList �zerinden yap�l�yor. Oradaki kaynak ve ba�l�k dosyalar�n� da kullan�n.

	StudentList kullanarak 2 ayr� liste olu�turabilir miyiz? Mesela, s�n�ftan ge�enler ve kalanlar. Hay�r Linked List ile bu m�mk�n de�il.
		Linked List kullan�rken 2. listeyi olu�turmak i�in �nce ilk liste tamamen bo�alt�lmal� ve ba�ka bir kod taraf�ndan tekrar tekrar �a��r�larak doldurulmal�.

	StudentList �rne�ini yaparken fonksiyonlar i�lemlerini yapabilmek i�in 2 adet internal-linkage'a ait(client kod g�remiyor bu nesneleri) global nesne kullan�yordu.
		Bunlar gpfirst ve gsize. Bir liste i�in 2 tane bu de�i�kenden gerekmi�ti. 2. liste i�in, fonksiyonlar i�lemlerini yapabilmesi i�in, 2 tane daha ayn� nesneye ihtiya� duyacakt�. 
			Handle tekni�i bize bunu sa�l�yor. Her list i�in gereken de�i�kenleri sa�l�yor. Bunu da, ortak kullan�lan nesneleri bir yap�n�n eleman� yaparak sa�l�yor.


		Bu sayede her yeni link i�in yeni bir de�i�ken tan�mlamak yerine yap� t�r�nden bir nesne kullanarak yapabiliyoruz bu i�lemi.
	struct NewLink{
		int data1, data2;
	}; // Bu �ekilde her seferinde fonksiyona o nesnelerin adresini tek tek yollamak yerine struct NewLink t�r�nden bir nesnenin adresini yolluyoruz.
	
		Bu yap� nesnelerinin olu�turulmas�n�n da kolay bir yolu var. StudentList'i d�zenlerken daha detayl� �ekilde ya burada ya da kaynak dosyas�nda not al�r�m.
			Bu yap�lana Open/Create i�lemi denir. Bu fonksiyon olu�turulan yeni struct'�n adresini geri d�nd�recek.

			struct NewLink* create_newlink(???);
		
		E�er client kod yeni bir link olu�turmak isterse create_newlink fonksiyonunu �a��racak ve bu fonksiyonun d�nd�rd��� adresi tutacak.
			��lem yapan fonksiyonlarda bu geri d�nd�r�len pointer� isteyecek client koddan. Bu tarz pointerlara da 'Handle' deniyor.

		D�nd�r�len adresle i�lemler yap�l�p o �ekilde b�rak�l�rsa, yani nodelar free edilmezse 'kaynak s�z�nt�s�' olur. 
			Bunu yapmak i�inde yard�mc� bir fonksiyon daha kullan�caz. Bu yap�lana destroy/close i�lemi denir.

		CPP'de bu tarz i�lemlere gerek yok.	
			OOP dillerindeki constructor destructor gibi fonksiyonlar bu i�e yar�yor. 

		struct List { 
			Node* gpfirst;
			size_t gsize;
			// void* -> veri elemanlar�n� direkt eri�imi engellemek, daha fazla gizlemek i�in void* kullan�labiliyor.
		};


int main(void) {
	// student_list_test.txt 
}
*/



													/*						Alignment(Hizalama)						*/
/*
	��lemciler belirli i�lemleri yapmak i�in belleklere eri�iyorlar.
		��lemciler eri�tikleri bu nesnelerde get,set vs gibi i�lemler yap�labilmeleri i�in, bu nesnelerin 2-4-8'in katlar� olan adreslere yerle�tirilmesi gerekiyor.
			Daha rahat eri�meleri i�in yap�l�yor bu 'hizalama' ve i�lemciden i�lemciye de�i�ebilir. Buna alignment requirement deniyor. Sisteme ba�l�.
				Mesela int nesnelere daha rahat eri�mek i�in(benim sistemimde) 4'�n katlar� kullan�l�yor.
	 E�er i�lemcinin belirledi�i alignment requirement'a uygun s�ralanmaz ise;
		- (i�lemcinin t�r�ne ba�l�) Ekstra maliyet ile eri�ir o yerlere
		- �yle bir eri�im Donan�msal ya da yaz�l�msal bir hata olur.




int main(void) {

	int x = 10, y = 20;

	double d1 = .4, d2 = 3.2;

	printf("%p\n", &x); // 4'�n kat� olacak
	printf("%p\n", &y); // 4'�n kat� olacak
	printf("%p\n", &d1); // 8in kat� olacak
	printf("%p\n", &d2); // 8in kat� olacak 
		// ��te buna alignment requirement
}
*/
/*
	C11 ile eklenen bir keyword ile bunu elde edebiliyoruz.
	_Alignof(T) // compile time operat�r�
		Bu keyword/operat�r operand olarak ald��� t�r�n alignment requirement de�erini g�steriyor. 
	struct nesnelerinin de alignment requirement� vard�r. sizeof de�eri ile kar��t�rma.

	define makrosu ile yap�lan tan�m ile alignof �eklinde de kullan�labilir. Bir fark� yok ayn� i�lem yap�l�yor. 
		bu makro ba�l�k dosyas� i�erisinde yap�lm�� halde. (#include <stdalign.h>)
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
	Baz� sebeplerden dolay�, performans ya da ba�ka bir �ey, bu alignment requirement'� de�i�tirebiliyoruz.
		Bunu yapmam�z� sa�layan keyword ise _Alignas(kat). Bunu kullanarak int i�in 4'�n katlar� yerine 8in katlar� �eklinde yerle�tirebiliriz.
			Kat yerine ka��n kat�n olmas�n� istiyor isek onu yaz�yoruz.


	Her struct'�n alignment requirement'� oldu�u gibi memberlar�n�nda var. �rne�in.

		struct Eng{
			char c1;
			int x;
			char c2;
		};
	Nesne		Adres
	c1			1000 // c1 nesnesi 1000. adreste 
	x			1001 // bu hem olabilir hem de yanl��. Ekstra maliyet ile x'e eri�ilebilir(i�lemciye ba�l�) ya da bu hata(yukar�da bahsettim)
	

	Padding byte denilen bir �ey var. Padding byte, alignment requirement i�in uyulmas� gereken kurallara uygun �ekilde kullan�lmayan byteler� dolduruyor.
		int i�in 4'�n katlar� olmas� gerekiyor. char i�in 1'in katlar�(XD)

	Nesne		Adres
	c1			1000 // �imdi bundan sonraki 3 byte padding bytelar ile doldurulacak. Bu sayede int nesnesi 4�n kat� olan bir byteta olabilecek.
	pdbyte		1001 // bu padding bytelar bir nesneye ba�l� de�il.
	pdbyte		1002
	pdbyte	1	1003
	x			1004
	x			1005
	x			1007
	x			1008
	c2			1009
	pdbyte		1010
	pdbyte		1011
	�zet olarak, padding byteler 2 �ekilde kullan�l�yor.
		- Nesnenin alignment gereksinimlerini kar��lamak i�in kullan�lmayan ve/veya kullan�lamayacak olan nesneleri padding byteler ile dolduruyor.
			int nesnesi 4'�n katlar� olmas� gerekti�i i�in 2 veya 3'�n katlar�nda kullan�lamaz. Bunlar� padding byte ile dolduracak ve 4'�n katlar�nda saklanacak.
		- Bir yap� nesnesinin sonunu, kullan�lmayan veya orada bir nesne olmayan, padding byte kullan�lmamas� i�in kapat�r.

	Yap�n�n i�erisindeki memberlar�n yaz�m s�ras� sizeof de�erinin de�i�mesine sebep olabilir.
	Yap� nesnesinin sonunda padding byte olabilir fakat ba��nda padding byte olamaz. 

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
	printf("%zu\n", sizeof(struct Eng));// sizeof de�eri 12, ��nk� b�t�n elemanlar padding byte'a gerek duymadan alignment gereksinimini kar��l�yor.
	printf("%zu\n", sizeof(struct Agr));// sizeof de�eri 12, (normalde olmas� gereken 6) fakat 6 bytel�k padding byte var.
	printf("%zu\n", sizeof(struct Agr2));// sizeof de�eri 8, ��nk� elemanlar�n�n tan�m s�ras� farkl� oldu�u i�in padding byte kullan�m� da farkl�.
											// char c1 1001, char c2 1002 adresleriin tutuyor. int alignment requirement 4 ve kat� oldu�u i�in 1003 ve 1004 adreslerine
												// birer adet byte ekleniyor(toplam 2 byte) birde struct'�n elemanlar�n�n bitti�i yere 2 padding byte daha ekleniyor bu sayede 8 oluyor.
	Agr myagr;
	// &myagr = &myagr.c1; Yap� nesnesinin ba��nda padding byte olmaz. Bu bilgiye g�re, yap� t�r�nden olu�turulan bir nesnenin adresi ile o yap� t�r�n�n ilk eleman�n�n adresi ayn�
		// olmak zorunda.
	printf("%02p %02p ", &myagr, &myagr.c1); // burada ikisinin de adresi ayn�.
}
*/
/*
	Padding byte " " 

	- ��lemlerin daha k���k maliyetle yap�lmas�n� sa�l�yor.
	- Yap� nesnelerinin dizimine g�re yap� nesnesinin ihtiyac� oldu�u bellek alan�n�n miktar� artabilir veya azalabilir.
		padding byte'a ba�l� bu.
	- Yap� nesnesinin elemanlar�n� pointer aritmeti�i kullanarak eri�memeliyiz. ��nk� pointer aritmeti�i padding bytelar� dikkate almaz. 
		Padding byteler, garbage value olaca�� i�in bu adreslerin dereference edilmesi UB.
		Padding bytelar� dikkate alarak istenen nesnenin adresini alan bir fonksiyonel makro var. stddef.h i�erisinde tan�mlanm�� olan bi fonksiyonel makroya
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
		printf("%d\n", *(int*)(p + 2)); // bu undefined behaviour ��nk� pointer aritmeti�i padding bytelar� dikkate almayaca��ndan dolay� ��p de�ere eri�iriz bu da UB.

		//	Padding bytelar� dikkate alarak istenen nesnenin adresini alan bir fonksiyonel makro var. stddef.h i�erisinde tan�mlanm�� olan bi fonksiyonel makroya
		//		offsetof deniyor.

		printf("%zu\n", offsetof(Data, c1));
		printf("%zu\n", offsetof(Data, x));
		printf("%zu\n", offsetof(Data, c2));

	}	
*/ 

/*
	offsetof makrosunu nas�l implemete edilir
		1-�ncellikle struct t�r�n� ve member t�r�n� alan 2 adet fonksiyonel makro operand� tan�ml�yoruz.
			#define Offsetof(s, memberT)
		2-Daha sonra s'i kullanarak 0'�n adresini al�yoruz.
			#define Offsetof(s, memberT)		(s*)0
		3-Struct'�n ald���m�z 0'�n adresi �st�nden member'a eri�iyoruz. Bunu yapmadan �nce (s*)0'� �ncelik parantezine al�yoruz.
			#define Offsetof(s, memberT)		((s*)0)->m // (
		4-Daha sonra bu eri�ti�imiz member'�n adresini al�yoruz.
			#define Offsetof(s, memberT)		&(((s*)0)->m) // adresini almadan �nce t�m �eyi kapsamas� i�in t�m i�lemi parantez i�ine al�p ve �yle adresini ald�k.
		5-�u an elimizde olan de�er bir adres. Bunu size_t t�r�ne cast ederek 0, 1 ,2, 4, 8 vs vs gibi de�erler elde ediyoruz.
			#define Offsetof(s, memberT)		(size_t)(&(((s*)0)->m)) 
			
*/
/*
	offsetof makrosu m�lakatlarda soruluyormu�.
		Sen nas�l tan�mlard�n gibisinden.

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
	// data �zerinden x'in adresini almak istiyorum.
	int* x3 = (int*)((char*)dataptr + offsetof(Data, x)); //char* a cast ediyoruz ki yap�lan i�lem byte byte yap�ls�n int* veya b�aka bir pointer de�i�kenine yapsayd�k i�lem do�ru olmazd�
	int* x2 = (int*)((int*)dataptr + offsetof(Data, x));
	int* x1 = ((int*)dataptr + offsetof(Data, x));
	//////////////////////////

	Data d1 = { 12, 129, 45 };
	Data d2 = { 12,	129, 45 };
	// bu yap� t�r�nden nesnelerin e�itli�ini kontrol etmek i�in her iki yap� nesnesinde de kar��l�k gelen nesnelerin kar��la�t�r�lmas� gerekiyor.
	if (d1.c1 == d2.c1 && d1.x == d2.x && d1.c2 == d2.c2); // bu ok ama 10 tane eleman oldu�unu d���n. O zaman ne olacak?

	// string.h i�erisinde bulunan memcpy ile bellek bloklar�n�n kar��la�t�rmas�n� yapabiliyorduk.
	if (!memcmp(&d1, &d2, sizeof(Data))) // e�er e�it ise 0 de�eri d�nece�i i�in ! kullan�yoruz
		printf("Yapilar ayni\n");
	else
		printf("Esit degil\n");

	// yukar�daki kod do�ru g�z�k�yor fakat e�it de�il k�sm�na girecek. Bunun sebebi ise padding bytes. strcmp fonksiyonu paddingbytes� dikkate alm�yor.
		// e�er iki yap� nesnesini kar��la�t�rmak istiyor ise padding bytelar� 0 yapmam�z gerekiyor. Bunu da memseti bir fonksiyonel makroya �evirerek yap�yoruz -> clear_struct

	//memset(&d1, 0, sizeof(d1));
	//memset(&d2, 0, sizeof(d2)); bu �ekilde yazmak yerine
	Data data1;
	Data data2;
	clear_struct(data1);
	clear_struct(data2);
	// �imdi ise struct'�n memberlar�na de�erleri veriyoruz.
	data1.c1 = 32;		data1.x = 12521; 	data1.c2 = 43;
	data2.c1 = 32;		data2.x = 12521;	data2.c2 = 43;
	if (!memcmp(&data1, &data2, sizeof(Data)))
		printf("Yapilar ayni\n");
	else
		printf("Esit degil");
	// Art�k yapilar ayn� k�sm�na girecek ��nk� paddingbyteler ��p de�er yerine 0 de�erinde
	// E�er yap�lar kar��la�t�rma i�lemi i�in d��ar�dan geliyor ise temizlenmi� halde bize g�nderilmesi gerek. E�er temizlenmediyse tek tek t�m elemanlar� kar��la�t�rmam�z gerekli. Ba�ka yolu yok.
}
*/
/*
	E�er �nceli�imiz bellek/alan kullan�m� ise, eri�im maliyetinin d���kl��� gibi durumlar �nemli de�il ise 
		derleyicinin padding byte kullanmas�n� belirli makro/fonksiyonlarla engelleyebiliriz. (derleyici de izin vermeli) 
	Bunlardan bir tanesi
		#pragma pack(1) bunu yazd�ktan sonra padding bytelar kullan�lmayacak bir de�i�kenin bittikten sonraki byte�ndan sonra di�er de�i�ken ba�layacak.
			Alignment requirements g�z ard� edilecek.



#include <stdio.h>
typedef struct Data {
	double dval;
	int a, b, c;

}Data;
int main(void) {
	float f = 4.12421f;
	// printf("%d",*(int*)f); // tan�ms�z davran��.
	// standart�n belirtti�i durumlar d���nda(compatible types), bir nesnenin de�erini okumak/de�i�tirmek/kopyalamak i�in ba�ka bir t�rden adrese d�n��t�r�p derefence etmemeliyiz.
		// sizeof de�erlerinin ayn� olmas� yap�labilece�i anlam�na gelmez! Standart�n belirledi�i baz� senaryolarda ayn� olur. Bunlara compatible types denir.

	// ayn� tam say�lar�n i�aretli/i�aretsiz aras�nda hallerinin aras�ndaki de�i�im
	unsigned int x = 874353987;
	int y = *(int*)&x; // bunlar compatible type. ��nk� ayn� say� t�r�n�n signed/unsigned t�r d�n���m�.

	//char t�rlerine yap�lan d�n���mlerde de undefined behaviour yok. ��nk� i�lem byte byte yap�l�yor
	double dval = 4.1652316;
	unsigned char* p = (char*) &dval;
	for (size_t i = 0; i < sizeof(dval); i++) {
		printf("%u\n", p[i]);
	}

	// Bir pointer t�r�nden void* / void* bir pointer t�r�ne
	double d = 412.12421;
	void* vp = &dval;
	double* dp = (double*)vp;
	printf("%f", *dp);

	//Yap� nesnesinin kendi adresi ile yap� nesnesinin ilk eleman�n adresi ayn� olmak zorunda ve aralar�nda d�n���m yap�labilir.
	Data mydata = {3.12321, 1, 2 ,3};
	printf("%f", *(double*)&mydata);
}
*/
// �u anl�k yap�lar bitti devam�n� ileride bitiricez.


/*----------------------------------------------------------------------------------------------------------------------------------------------*/



													/*						UNIONS(BIRLIKLER)						*/
/*
	�ok k�sa s�recek bu k�s�m. Bir �ok k�sm� structures ile ayn� bundan dolay� sadece farklar�ndan  bahsedilecek.

	- Unionlar�n elemanlar�n�n adresleri ayn�. Ayn� bellek alan�n� payla��yorlar
		Yani bir birlik nesnesinin adresi ne ise b�t�n elemanlar�n�n adresi ayn�.
	- Birliklerde sadece bir elemana ilk de�er verilebilir. struct gibi tek tek t�m elemanlara verilemez.
		Belirli bir elemana ilk de�er vermek istiyor isek ya o eleman� yap� nesnesinin ilk eleman� yapaca��z ya da designated initializer kullanmak zorunday�z.

	Neden? 
		Birliklerin en �ok kulland�l��� tema; bir verinin farkl� bi�imlerde temsil edilmesi. 


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
	// yukar�daki printf �a�r�lar�ndan sonra hem struct'a hem de union'a birer adet daha int eleman eklendi (int b)
	printf("sData: %zu\n", sizeof(sData)); // sizeof 8
	printf("uData: %zu\n", sizeof(uData)); // sizeof 4
	// yukar�daki printf �a�r�lar�ndan sonra hem struct'a hem de union'a birer adet daha int eleman eklendi (int c)
	printf("sData: %zu\n", sizeof(sData)); // sizeof 12
	printf("uData: %zu\n", sizeof(uData)); // sizeof 4
	// yukar�daki printf �a�r�lar�ndan sonra hem struct'a hem de union'a bir adet double eleman eklendi (double d)
	printf("sData: %zu\n", sizeof(sData)); // sizeof 24
	printf("uData: %zu\n", sizeof(uData)); // sizeof 8

	// Fark �u. struct'�n sizeof de�eri elemanlar�n�n sizeof de�erinin toplam� iken
		// unionda bu durum sizeof de�erince en b�y�k eleman�n de�eri. Double 8 byte oldu�u i�in ekrana 8 yazd�r�yor.
	uData mydata;
	printf("\nmydata:		%p\n", &mydata);
	printf("mydata.a:	%p\n", &mydata.a);
	printf("mydata.b:	%p\n", &mydata.b);
	printf("mydata.c:	%p\n", &mydata.c);
	printf("mydata.d1:	%p\n", &mydata.d1);
	printf("mydata.d2:	%p\n", &mydata.d2); 
	// birlik nesnesinin adresi ile elemanlar�n�n adresleri tamamen ayn�
	// bundan dolay� herhangi bir eleman�na de�er kopyalamas� yap�ld���nda b�t�n elemanlar�n�n de�eri de�i�ir.	


	uData myunion = { 12 }; // Birliklerde sadece bir elemana ilk de�er verilebilir. struct gibi tek tek t�m elemanlara verilemez.
	uData myunion2 = { .c = 14 }; // designated initializer
	// uData myunion3 = { 12, 34, 45 }; // Yanl��
	// NOT: SADECE 1 INITIALIZER KULLANILABILIR.
}
*/

//Birliklerin en �ok kulland�l��� tema; bir verinin farkl� bi�imlerde temsil edilmesi. 
#include <stdint.h>
union Pack {
	uint32_t uval;
	uint8_t ar[4];
};
// ikisinin de sizeof de�eri 4 o y�zden bu union'�n sizeof de�eri 4
// fakat uint32 32 bit iken, uint8 her eleman� 1byte olan 4 elemanl� bir dizi. D��ar�dan gelen bytelar�n farkl� �ekillerde temsil edilebilmesi i�in 
	// iki farkl� nesne var


/*
// Bunu C gibi bir dilde nas�l temsil edebiliriz?
	// genellikle t�r�n� belirten bir struct ve union ile yap�l�r
typedef struct {
	int type; // veri t�r�n�n ne oldu�unu bilgisi, enum da olabilir, 0 - Byte, 1 - uval, 2 - dval, 3 - str[16]
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
	// bu �ekilde olu�turulan unionlara discriminated union ya da tagged union deniyor. Ve �ok s�k kullan�lan bir yap�.
}
*/
#include "Date.h"
#define		CHAR	0
#define		INT		0
#define		DOUBLE	0
#define		DATE	0

typedef struct {
	int type; // Hangi t�r bir veri tuttu�unu s�yleyecek. Bu type union i�erisinde bulunan elemanlar�ndan hangsinin kullan�laca��n� s�yleyecek asl�nda bize
	union {
		char c;
		int i;
		double d;
		Date dt;
	};
}Data;
int main(void) {
	Data mydata;
	// hangi t�rden bir de�i�ken tutmak istiyorsak type'� ona g�re cast ediyoruz. Yukar�da bir ka� tane makro tan�mlad�k.

	mydata.type = CHAR; // char tuttu�unu g�steriyoruz.
	mydata.c = 'F';

	mydata.type = DOUBLE; // double tuttu�unu g�steriyoruz.
	mydata.d = .4124;

	// Bir sonraki derste nas�l dizi olu�turabiliriz onu g�r�cez. Dizinin bir eleman�n�n char tutarken di�erinin double tutmas� vs vs.

	Data mydataarr[100]; 

}
