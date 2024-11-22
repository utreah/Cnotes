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

typedef struct Employee {
	int id;
	char name[40];
	char address[40];
	int gender;


	/*
	struct MilInfo{ // erkek çalýþanlar için askerlik durumu
		char place[24];
		int status;
		char release_date[20];
	};

	char maiden_name[20]; // kadýn çalýþanlar için evli ise kýzlýk soyadý
	*/
	/*
		Þimdi yukarýdaki durumda eðer çalýþan erkek ise maiden_name boþa yer kaplýyor.
			Eðer çalýþan kadýn ise, askerlik bilgisi gereksiz yer kaplýyor. 24 + 20 + sizeof(int) kadar çok yüksek bir maliyet.
		Bunu union yaparak ayný bellek alanýný kullanarak çözebiliriz.
	*/

}Employee;

int main(void) {
	printf("%zu", sizeof(Employee));
}