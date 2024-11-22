#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // C99 ile eklendi
// Diyelim ki 32 - 16 ve 8 bitlik sayýlar tutmak istiyoruz(ayný veya farklý)  
	// sistem programlama tarafýnda çok kullanýlýyor bunlar
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
	printf("%zu", sizeof(Data)); // 4 byte en büyük nesnenin boyutu kadar yer kaplýyor unionlar. 
	Data mydata = { 123 }; // böyle yazýlýrsa ilk elemana deðer verilir. Eðer baþka  bir member'a eriþip deðer vermek istiyor
		// isek designated initiliazor kullanýlmalý
	Data mydeyta = { .low_bytes = 44u , .high_bytes = 7123u};

	Data data1;
	data1.byte_1 = 45u;
	data1.byte_2 = 44u;
	data1.byte_3 = 43u;
	data1.byte_4 = 42u;
	// En fazla kullaným þekli bu

	//////////////////////////////////////////////
}
*/

// Discriminated Uninon(tagged union) bir diðer kullaným þekli.
	// Öyle bir deðiþken olsun ki önceden belirlenmiþ farklý türlerden deðerler alabilsin.
	//CPP'de bunu standart kütüphane sunuyor. Buan 'variant' deniyor.
/*
	typedef union {
		char c;
		int i;
		double d;
		Date dt;
	}Data;
	
*/
	//Data türden bir deðiþkene istediðimiz türden nesneye istediðimiz deðeri verebiliriz fakat
		// hangi türden deðer tuttuðunu bilmeden bunu kullanamayacaðýmýz için bunu bir deðiþkende tutmamýz gerekiyor.
			// Bunun için bir struct oluþturuyoruz ve ayný zamanda tür verisini tutacak olan type adlý bir deðiþken oluþturuyoruz.
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
// Bellek ihtiyacýný azaltmak. 
	 Ayný verileri daha az bellek alaný kullanarak ifade etmek.
	 Öyle durumlar var ki; 
		-Bazen bir veri ile baþka veri ayný anda bulunamýyor. Yani A verisi varken B verisinin olma ihtimali yok.
			Bundan dolayý ikisini de farklý deðiþkende vs tutup bellekten yemek yerine ikisini de ayný bellek alanýnda kullanarak 
				bellek kullanýmýndan tasarruf ediliyor. 
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


	
//	struct MilInfo { // erkek çalýþanlar için askerlik durumu
//		char place[24];
//		int status;
//		char release_date[20];
//	};

//	char maiden_name[20]; // kadýn çalýþanlar için evli ise kýzlýk soyadý
	
	//	Þimdi yukarýdaki durumda eðer çalýþan erkek ise maiden_name boþa yer kaplýyor.
	//		Eðer çalýþan kadýn ise, askerlik bilgisi gereksiz yer kaplýyor. 24 + 20 + sizeof(int) kadar çok yüksek bir maliyet.
	//	Bunu union yaparak ayný bellek alanýný kullanarak çözebiliriz. Zaten bir kiþi hem kadýn hem erkek olamayacaðýna göre
	//		bazý bilgiler gereksiz olacak. Anonymous union yapýyoruz
	union{
		struct MilInfo { // erkek çalýþanlar için askerlik durumu
			char place[24];
			int status;
			char release_date[20];
		};
		char maiden_name[20]; 
		// Eðer erkek ise maiden name kullanýlamayacak, eðer kadýn ise milinfo struct'ý.
			// Daha önce 156 byte'lýk bir bellek allocate edilirken bu 136ya düþtü.	
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
 C'de uval'e deðer verip float deðiþkenini kullanmak UB deðil CPP'de UB
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
													//						Enumarations(numaralandýrma)						//
/*
	Problem domainindeki durumlarý ifade etmek için deðiþkenleri kullanýyoruz. Bunlar deðer alýp o deðeri tutuyor.
		Ama bazý eþyler var ki bunlar deðer tutmak yerine önceden belirlenmiþ ifadeleri alýyorlar.
	structures
	unions
	enumerations

	içindeki verilerin tamsayý karþýlýklarýný tutuyor.
	Her dil için verilen destek bu konuda farklý.

	C de bu destek az.

	Bune alternatif olarak macrolarda kullnýlabilir.tabi farklarý üstünlükleri var.
	#define CLUB	0
	#define DIAMOND 1
	#define HEART	2
	#define SPADE	3
	1. Dezavantaj: Derleyici bu isimleri bilmiyor. Derleyici açýsýndan bakýldýðýnda bu makrolar (club diamond vs) identifier deðil.
		Bir scopelarý yok bu yüzden.
	2. Dezavantaj: makrolarýn bir tür kapsamýnda deðerlendirilmiyor. namelookup gibi kurallarý olmuyor.
	Enum kullanýlýnca bir tür oluþturmuþ oluyoruz.
	Mesela, int suit; diye bir nesnemiz var ve bu nesne kartlarýn renklerini tutuyor. Ben bu suit'e;
	suit = CLUB; diyerek deðer atayabildiðim gibi
	suit = 31; deðerini de atayabilirim. Hiçbir hata ile karþýlaþmam çünkü suit int bir deðer. enum bunu engelliyor
*/

// Bir numaralandýrma oluþtururken enum keywordünü kullanýyoruz.

/*
* //enum tag (opsiyonel)
	keyword enumaration_tag{
	// union ve structlarda içerisinde tuttuðu nesnelere 'union' veya 'struct' member deniyordu. enumda ise aþaðýdaki 2 terim kullanýlýyor.
		enumaration constants;
		enumarator
	};
	NOT: enumaratorler için veri türü belirtmiyoruz.

	enum Suit{Club, Diamond, Hearts, Spade};
*/
typedef enum Suit{Club, Diamond, Heart, Spade}Suit;
/*
	Kullaným þekli struct ve union ile ayný. enum keywordü kullanýlmasý gerekiyor bir nesne tanýmlarken.
		keywordü kullanmak istemiyorsak typedef kullanabiliriz.
*/
	// CPP'de typedef bildirimi kullanmadan direkt olarak struct, union veya enumaration tagler kullanýlabilir. 
/*
enum Color{White, Gray, Red, Blue, Brown, Black};
	Bu isimler birer tam sayý sabiti. Club, Gray, Heart, Red vs.
	
	Peki bu sabitlerin deðerleri ne?
		Eðer ilave bir sentaks özelliði kullanýlarak deðer verilmedi ise 0'dan baþlayarak deðer alýrlar.
			Mesela suit enum'ý için 
						0		1		2	   3		
			enum Suit{Club, Diamond, Heart, Spade};
			Color enum'ý içinde ayný durum geçerli
						0		1	2		3	4		5
			enum Color{White, Gray, Red, Blue, Brown, Black};

	Kendi deðerimizi de verebiliriz bu enumlara.
	enum RGB{Red = 365, Green = 512, Blue = 123}; 
		Sentaks açýsýndan bir kusur yok
*/
#include <stdio.h>
enum Color{White, Gray, Red, Blue, Brown, Black};
enum Status{On = 500, Off = -1, Standby = 250, Idle}; 
/*
	Eðer manuel olarak deðer verilme iþlemi yapýldýysa deðer verilmeyen enumaration constantlar kendinden bir önceki enum'ýn deðerinin
		bir fazlasýný alýrlar. Status enum'ýnda bulunan Idle'a deðer verilmemesine raðmen kendinden önceki standby'ýn deðeri 250 olduðu
			deðeri 251 olacak. Eðer eksi olsaydý bir fazlasý olacaktý. -6 için Idle'ýn deðeri -5 olurdu.

	enum hem bir user defined types hem de bir integer types'ýn bir öðesi. Ekrana yazdýrma iþlemi yapacaðýmýz zaman iþaretli int türünün
		format specifier'ý kullanýlmalý
*/

int main(void) {
	White; // 0 deðerinde bu þu an. switch'in case'i olarak kullanýlabilir baya yaygýn. 
	int a[Gray]; // hata yok çünkü Gray bir constant(sabit)
	printf("%d %d %d %d %d %d\n", White, Gray, Red, Blue, Brown, Black);
	printf("%d %d %d %d", On, Off, Standby, Idle);
}
// Bütün typedef kurallarý enumda da geçerli.
1:07



