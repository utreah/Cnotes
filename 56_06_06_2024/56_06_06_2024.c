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

typedef struct Employee {
	int id;
	char name[40];
	char address[40];
	int gender;


	/*
	struct MilInfo{ // erkek �al��anlar i�in askerlik durumu
		char place[24];
		int status;
		char release_date[20];
	};

	char maiden_name[20]; // kad�n �al��anlar i�in evli ise k�zl�k soyad�
	*/
	/*
		�imdi yukar�daki durumda e�er �al��an erkek ise maiden_name bo�a yer kapl�yor.
			E�er �al��an kad�n ise, askerlik bilgisi gereksiz yer kapl�yor. 24 + 20 + sizeof(int) kadar �ok y�ksek bir maliyet.
		Bunu union yaparak ayn� bellek alan�n� kullanarak ��zebiliriz.
	*/

}Employee;

int main(void) {
	printf("%zu", sizeof(Employee));
}