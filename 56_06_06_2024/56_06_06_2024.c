#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // C99 ile eklendi
// Diyelim ki 32 - 16 ve 8 bitlik say�lar tutmak istiyoruz(ayn� veya farkl�)  
	// sistem programlama taraf�nda �ok kullan�l�yor bunlar
/*
typedef union Data {
	uint32_t uval;
	struct {
		uint16_t low_bytes;
		uint16_t high_bytes;
	};

	struct {
		uint8_t byte_1;
		uint8_t byte_2;
		uint8_t byte_3;
		uint8_t byte_4;
	};

}Data;

int main(void) {
	printf("%zu", sizeof(Data)); // 4 byte en b�y�k nesnenin boyutu kadar yer kapl�yor unionlar. 
	Data mydata = { 123 }; // b�yle yaz�l�rsa ilk elemana de�er verilir. E�er ba�ka  bir member'a eri�ip de�er vermek istiyor
		// isek designated initiliazor kullan�lmal�
	Data mydeyta = { .low_bytes = 44u , .high_bytes = 7123u};

	Data data1;
	data1.byte_1 = 45u;
	data1.byte_2 = 44u;
	data1.byte_3 = 43u;
	data1.byte_4 = 42u;
	// En fazla kullan�m �ekli bu

	//////////////////////////////////////////////
}
*/

// Discriminated Uninon(tagged union) bir di�er kullan�m �ekli.
	// �yle bir de�i�ken olsun ki �nceden belirlenmi� farkl� t�rlerden de�erler alabilsin.
	//CPP'de bunu standart k�t�phane sunuyor. Buan 'variant' deniyor.
/*
	typedef union {
		char c;
		int i;
		double d;
		Date dt;
	}Data;
	
*/
	//Data t�rden bir de�i�kene istedi�imiz t�rden nesneye istedi�imiz de�eri verebiliriz fakat
		// hangi t�rden de�er tuttu�unu bilmeden bunu kullanamayaca��m�z i�in bunu bir de�i�kende tutmam�z gerekiyor.
			// Bunun i�in bir struct olu�turuyoruz ve ayn� zamanda t�r verisini tutacak olan type adl� bir de�i�ken olu�turuyoruz.
/*
#include "Date.h"
#include "nUtility.h"
#define SIZE 10
#define CHAR_TYPE 0
#define INT_TYPE 1
#define DOUBLE_TYPE 2
#define DATE_TYPE 3
typedef struct {
	int type;
	union {
		char c;
		int i;
		double d;
		Date dt;
	};
}Data;
double drand(void) {
	return (double)rand() / RAND_MAX + rand() + 1;
}
void set_random_value(Data* p) {
	switch (rand() % 4) {
		case CHAR_TYPE:	p->type = CHAR_TYPE; p->c = rand() % 26 + 'A'; break;
		case INT_TYPE:	p->type = INT_TYPE; p->i = rand(); break;
		case DOUBLE_TYPE: p->type = DOUBLE_TYPE; p->d = drand(); break;
		case DATE_TYPE:p->type = DATE_TYPE; set_random_date(&p->dt); break;
	}
}
void print_data_value(const Data* p) {
	switch (rand() % 4) {
	case CHAR_TYPE: printf("(%c)\n", p->c); break;
	case INT_TYPE: printf("[%d]\n", p->i);	break;
 	case DOUBLE_TYPE: printf("((%f))\n", p->d); break;
	case DATE_TYPE:	print_date(&p->dt);	break;
	}
}

int main(void) {
	Data ar[SIZE];
	randomize();
	for (int i = 0; i < SIZE; i++)
		set_random_value(ar + i);
	for (int i = 0; i < SIZE; i++) {
		print_data_value(ar + i);
		(void)getchar();
	}
}
*/


/*
// Bellek ihtiyac�n� azaltmak. 
	 Ayn� verileri daha az bellek alan� kullanarak ifade etmek.
	 �yle durumlar var ki; 
		-Bazen bir veri ile ba�ka veri ayn� anda bulunam�yor. Yani A verisi varken B verisinin olma ihtimali yok.
			Bundan dolay� ikisini de farkl� de�i�kende vs tutup bellekten yemek yerine ikisini de ayn� bellek alan�nda kullanarak 
				bellek kullan�m�ndan tasarruf ediliyor. 
*/

#include <stdlib.h>
#include <stdio.h>
#include "Date.h"
#include "nUtility.h"
/*
typedef struct Employee {
	int id;
	char name[40];
	char address[40];

	int gender;


	
//	struct MilInfo { // erkek �al��anlar i�in askerlik durumu
//		char place[24];
//		int status;
//		char release_date[20];
//	};

//	char maiden_name[20]; // kad�n �al��anlar i�in evli ise k�zl�k soyad�
	
	//	�imdi yukar�daki durumda e�er �al��an erkek ise maiden_name bo�a yer kapl�yor.
	//		E�er �al��an kad�n ise, askerlik bilgisi gereksiz yer kapl�yor. 24 + 20 + sizeof(int) kadar �ok y�ksek bir maliyet.
	//	Bunu union yaparak ayn� bellek alan�n� kullanarak ��zebiliriz. Zaten bir ki�i hem kad�n hem erkek olamayaca��na g�re
	//		baz� bilgiler gereksiz olacak. Anonymous union yap�yoruz
	union{
		struct MilInfo { // erkek �al��anlar i�in askerlik durumu
			char place[24];
			int status;
			char release_date[20];
		};
		char maiden_name[20]; 
		// E�er erkek ise maiden name kullan�lamayacak, e�er kad�n ise milinfo struct'�.
			// Daha �nce 156 byte'l�k bir bellek allocate edilirken bu 136ya d��t�.	
	};

}Employee;

int main(void) {
	printf("%zu", sizeof(Employee));
}
#include <stdint.h>

union Data {
	uint32_t uval;
	float f;
};
 C'de uval'e de�er verip float de�i�kenini kullanmak UB de�il CPP'de UB
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													//						Enumarations(numaraland�rma)						//
/*
	Problem domainindeki durumlar� ifade etmek i�in de�i�kenleri kullan�yoruz. Bunlar de�er al�p o de�eri tutuyor.
		Ama baz� e�yler var ki bunlar de�er tutmak yerine �nceden belirlenmi� ifadeleri al�yorlar.
	structures
	unions
	enumerations

	i�indeki verilerin tamsay� kar��l�klar�n� tutuyor.
	Her dil i�in verilen destek bu konuda farkl�.

	C de bu destek az.

	Bune alternatif olarak macrolarda kulln�labilir.tabi farklar� �st�nl�kleri var.
	#define CLUB	0
	#define DIAMOND 1
	#define HEART	2
	#define SPADE	3
	1. Dezavantaj: Derleyici bu isimleri bilmiyor. Derleyici a��s�ndan bak�ld���nda bu makrolar (club diamond vs) identifier de�il.
		Bir scopelar� yok bu y�zden.
	2. Dezavantaj: makrolar�n bir t�r kapsam�nda de�erlendirilmiyor. namelookup gibi kurallar� olmuyor.
	Enum kullan�l�nca bir t�r olu�turmu� oluyoruz.
	Mesela, int suit; diye bir nesnemiz var ve bu nesne kartlar�n renklerini tutuyor. Ben bu suit'e;
	suit = CLUB; diyerek de�er atayabildi�im gibi
	suit = 31; de�erini de atayabilirim. Hi�bir hata ile kar��la�mam ��nk� suit int bir de�er. enum bunu engelliyor
*/

// Bir numaraland�rma olu�tururken enum keyword�n� kullan�yoruz.

/*
* //enum tag (opsiyonel)
	keyword enumaration_tag{
	// union ve structlarda i�erisinde tuttu�u nesnelere 'union' veya 'struct' member deniyordu. enumda ise a�a��daki 2 terim kullan�l�yor.
		enumaration constants;
		enumarator
	};
	NOT: enumaratorler i�in veri t�r� belirtmiyoruz.

	enum Suit{Club, Diamond, Hearts, Spade};
*/
typedef enum Suit{Club, Diamond, Heart, Spade}Suit;
/*
	Kullan�m �ekli struct ve union ile ayn�. enum keyword� kullan�lmas� gerekiyor bir nesne tan�mlarken.
		keyword� kullanmak istemiyorsak typedef kullanabiliriz.
*/
	// CPP'de typedef bildirimi kullanmadan direkt olarak struct, union veya enumaration tagler kullan�labilir. 
/*
enum Color{White, Gray, Red, Blue, Brown, Black};
	Bu isimler birer tam say� sabiti. Club, Gray, Heart, Red vs.
	
	Peki bu sabitlerin de�erleri ne?
		E�er ilave bir sentaks �zelli�i kullan�larak de�er verilmedi ise 0'dan ba�layarak de�er al�rlar.
			Mesela suit enum'� i�in 
						0		1		2	   3		
			enum Suit{Club, Diamond, Heart, Spade};
			Color enum'� i�inde ayn� durum ge�erli
						0		1	2		3	4		5
			enum Color{White, Gray, Red, Blue, Brown, Black};

	Kendi de�erimizi de verebiliriz bu enumlara.
	enum RGB{Red = 365, Green = 512, Blue = 123}; 
		Sentaks a��s�ndan bir kusur yok
*/
#include <stdio.h>
enum Color{White, Gray, Red, Blue, Brown, Black};
enum Status{On = 500, Off = -1, Standby = 250, Idle}; 
/*
	E�er manuel olarak de�er verilme i�lemi yap�ld�ysa de�er verilmeyen enumaration constantlar kendinden bir �nceki enum'�n de�erinin
		bir fazlas�n� al�rlar. Status enum'�nda bulunan Idle'a de�er verilmemesine ra�men kendinden �nceki standby'�n de�eri 250 oldu�u
			de�eri 251 olacak. E�er eksi olsayd� bir fazlas� olacakt�. -6 i�in Idle'�n de�eri -5 olurdu.

	enum hem bir user defined types hem de bir integer types'�n bir ��esi. Ekrana yazd�rma i�lemi yapaca��m�z zaman i�aretli int t�r�n�n
		format specifier'� kullan�lmal�
*/

int main(void) {
	White; // 0 de�erinde bu �u an. switch'in case'i olarak kullan�labilir baya yayg�n. 
	int a[Gray]; // hata yok ��nk� Gray bir constant(sabit)
	printf("%d %d %d %d %d %d\n", White, Gray, Red, Blue, Brown, Black);
	printf("%d %d %d %d", On, Off, Standby, Idle);
}
// B�t�n typedef kurallar� enumda da ge�erli.
1:07



