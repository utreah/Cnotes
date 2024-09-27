#include "C:\Users\Liver\Documents\GitHub\Cnotes\nUtility.h"
#include <stdio.h>

void swap_names(char* p1, char* p2)
{
	char temp[20];
	strcpy(temp, p1);
	strcpy(p1, p2);
	strcpy(p2, temp);
}
int main(void) {

	int a[10] = { 0 };

	// 'a' �eklinde yaz�l�rsa array decaye u�rayarak dizinin ilk eleman�n� adresini verir. 
		// bu ifade int* t�r�ndendir. 
	// '&a' ise a dizisinin kendi adresini verir. Bu ifadenin t�r� ise int (*)[10] t�r�ndendir.
	int	(*aPTR)[10] = &a; // *aPTR -> bu ifade derefence edildi�inde a dizisine eri�ilir. Dizinin ilk eleman�na de�il.

	int mdAR[5][4] = { 0 };
	// mdAR; yazd���m�zda &a[0]'y� g�stermeyecek. ��nk� bu ifade int (*)[4] t�r�nden bir ifade.
		// �ok boyutlu dizilerin int* t�r�nden olan ifadesi &mdAR[0][0]'d�r. -> bu �rnek i�in en az�ndan :D
	///////////////////////////////////////////////////////////////////////


	char names[][20] = {
		"Ugur", "Oyku", "Firuze", "Alptekin", "Alparslan", "Demir" "Borkay", "Necati", "Ersoy"
	};
	char *pnames[] = {
	"Ugur", "Oyku", "Firuze", "Alptekin", "Alparslan", "Demir" "Borkay", "Necati", "Ersoy"
	}; // bu yukar�daki ile ayn� de�il. Yukar�daki isimler names karakter dizisinin dinamik �m�rl� eleman(lar)� iken
			// burada ise statik �m�rl�, string literallerinin bir pointer dizisinde tutuldu�unu g�steriyor. Ayn� de�iller.
				// ve bu dizi read-only, de�i�iklik yap�lamaz. names dizisinde ise yap�labilir.

	const int a[10][20] = { 0 }; 
	a[3][3] = &x;
		// dizinin hi�bir eleman art�k de�i�tirilemez ��nk� const kullan�lm��
	
	////////////////////////////////////////////////////////////


	char sortnames[][20] = { "......." }; // hoca buraya �ok uzun bir isim listesi yap��t�rd�. 45. video dk 23

	char* ptr[sizeof(sortnames) / sizeof(sortnames[0][0])];
	for (size_t i = 0; i < sizeof(sortnames) / sizeof(sortnames[0][0]); i++)
	{
		ptr[i] = names[i]; // t�rleri ayn�, a��klama a�a��da.
	}
	// names in elemanlar�, char t�rden dizileri tutan elemanlard�r. 
		// t�r�  ->   char(*pf)[30].
	// names[i]'nin t�r� ise char* t�r�nden ��nk� adres belirtiyor her bir ��e.

	/*
		char *a[100] -> bunu tutacak pointer�n t�r� ise char **p �eklindedir.
		a[i] ise char *p ile tutulabilir.

		sonu�ta names[i] de char * t�rden, a[i] de char * t�rden.
		yani e�itlenebilir.
		
	*/
	// �imdi pointer dizisini bubblesort ile s�ralayabiliriz.
#define asize(p) (sizeof(p) / sizeof(p[0]))
		for (size_t i = 0; i < asize(ptr) - 1; i++)
			for (size_t j = 0; j < asize(ptr) - 1 - i; j++)
				if (strcmp(ptr[j], ptr[j + 1]) > 0)
				{
					swap_names(names[j], names[j + 1]);
				}
}
/*
	YAN� NAMES[][] D�Z�S�N� DE���T�RMED�K FAKAT CHAR * T�R�NDEN ELEMANLARI TUTAN B�R D�Z� YARATTIK.
	ADI P. P D�Z�S�NDEK� ADRESLER� YER DE���T�RD�K AMA NAMES D�Z�S� OLDU�U G�B� DURUYOR.
	NAMES DE���T�RMEDEN P �ZER�NDEN B�R SORT YAPIYORUZ.YAN� P N�N �LK ELEMANI ESK�DEN 0 �NDEXL� 
	ELEMANI G�STER�RKEN ��MD� EN UFAK OLANI G�STER�YOR.O DA 200 G�B� B�R DE�ER OLAB�L�R.
*/









////////////////////////////////////////////////////////////////////////////////////////////////
//Yaz�dan say�ya - Say�dan yaz�ya d�n���mler


int main(void) {
	char str[100];
	printf("dogum yilinizi giriniz: ");
	scanf("&s", str);
	puts(str); 
	atoi(str); // yaz�dan int'e d�n��t�r�yor. const char* t�r�nden bir de�i�ken al�yor.
					// ilk denk geldi�i non-digit karakterde �al��may� durduruyor. 3152ut yaz�ld���nda 3152'yi d�nd�r�r.
	atof(str); // yaz�dan double'a.
	atol(str); // long
	atoll(str); // long long
	///////////////////////////////

	char date[100];
	printf("Dogum tarihi dd-mm-yyyy formatinda giriniz: ");
	sgets(date);
	printf("[%s]\n", date);

	int day = atoi(date); // burada dd k�sm� yaz�lacak tire'ye gelince duracak.
	int mm = atoi(date + 3); // burada ise tireden sonraki ilk say�n�n oldu�u yerin adresinden ba�lat�yoruz. O da 'mm' k�sm�n� kaps�yor.
	int year = atoi(date + 6); // mant�k ayn�, yyyy k�sm�n� kaps�yor.

	printf("[%s] [%d/%d/%d]", date, day, mm, year);
}

///////////////////////////////////////////////////////////////////////////////
//														formatl� giri�-��k�� i�lemleri

/*
scanf standart input buffer�n� kullanan formatl� giri� i�lemidir	


sprintf, adresini ald��� dizinin belle�ine yaz�yor. (in-memory input/output deniyo bu i�lem(ler)e)
int sprintf(char* pdest, const char* pfm, ...)
	pdest -> yaz�lacak yer
	pfm -> standart outputa yazd���n� bu adrese yaz�yor
Mesela diyelim ki, standart outputa yazd�rd���m�z bir yaz�y� kullanmak istiyoruz. Bunu i�in sprintf'i kullanabiliriz.

#define SIZE 100
int main(void) {
	char name[SIZE]; // UGUR
	int year; // 2001
	int idx; // 31

	printf("isim - yil ve idx degerlerini giriniz: ");
	scanf("%s%d%d", name, &year, &idx);

	char file_name[SIZE]; // ugur_2001_031.txt olmas�n� istiyoruz dosyam�z�n ad�n�.
							// bunu std fonksiyonlar� kullanarakta yapabiliriz fakat hem zor hem de �ok maliyetli oluyor.
								// tek bir harf ve parametre eklemesi ile rahat�a yapabiliriz.
	sprintf(file_name, "%s_%d,%03d.txt", name, year, idx); // bu sayede ugur_2001_031.txt ismini file_name'e bellek �zerinden koyduk.
}
----------------------------------------------
int fprintf(FILE*, const char* pfm, ....); -> bu da dosyaya yaz�yor. Dosyalar da g�r�cez bunu.

int scanf(const char* pfm, ...)
int sscanf(const char* pfm, const char* pbuf, ...)
int scanf(FILE*, const char* pfm, ...)
*/
#define SIZE 100
int main(void) {
	char str[SIZE] = { "987     12345    432.2" };

	int x, y;
	double dval;

	sscanf(str, "%d%d%lf", &x, &y, &dval); // sscanf, str'de bulunan de�erleri standart output'�n buffer�ndaym�� gibi 
											// de�erleri okuyarak x, y ve dval'e at�yor. geri d�n�� de�eri scanf ile ayn� 'ba�ar� de�eri'
}



#define SIZE 100
int scmp(const void* vp1, const void* vp2) {

	// return strcmp((const char*)vp1, (const char*)vp2); -> bu yanl��, ��nk� char* p[] asl�nda char** t�r�nden bir dizi.
		// b�yle yazarak dizinin elemanlar�n�n tuttu�u adrese eri�miyoruz. Dizinin elemanlar�n�n adresine eri�iyoruz.

	return strcmp(*(char**)vp1, *(char**)vp2); // fonksiyon generic oldu�u i�in ve parametre olarak g�nderilen de�i�kenlerin
		// t�r�n�n const*[] t�r�nden (const**) olmas�ndan dolay� const** a implicit type conversion yap�ld�. Derefence edilerekte
			// dizide tutulan yaz�lar�n ADRES�NE eri�ildi kendisine de�il. Adresine eri�ilen elemanlar aras�nda strcmp ile s�ralama yap�ld�.
}
int main(void) {

	char* p[] = { "UGUR", "OYKU", "ERSOY", "AHMET", "NECATI", "ERGIN", "GERGIN" };
		// bu dizi char** t�r�nden bir dizi. Yani, string literallerinin adresine eri�mek yerine, o string lateralinin dizideki adresine
			// eri�ece�iz.

}