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

	// 'a' þeklinde yazýlýrsa array decaye uðrayarak dizinin ilk elemanýný adresini verir. 
		// bu ifade int* türündendir. 
	// '&a' ise a dizisinin kendi adresini verir. Bu ifadenin türü ise int (*)[10] türündendir.
	int	(*aPTR)[10] = &a; // *aPTR -> bu ifade derefence edildiðinde a dizisine eriþilir. Dizinin ilk elemanýna deðil.

	int mdAR[5][4] = { 0 };
	// mdAR; yazdýðýmýzda &a[0]'yý göstermeyecek. Çünkü bu ifade int (*)[4] türünden bir ifade.
		// Çok boyutlu dizilerin int* türünden olan ifadesi &mdAR[0][0]'dýr. -> bu örnek için en azýndan :D
	///////////////////////////////////////////////////////////////////////


	char names[][20] = {
		"Ugur", "Oyku", "Firuze", "Alptekin", "Alparslan", "Demir" "Borkay", "Necati", "Ersoy"
	};
	char *pnames[] = {
	"Ugur", "Oyku", "Firuze", "Alptekin", "Alparslan", "Demir" "Borkay", "Necati", "Ersoy"
	}; // bu yukarýdaki ile ayný deðil. Yukarýdaki isimler names karakter dizisinin dinamik ömürlü eleman(lar)ý iken
			// burada ise statik ömürlü, string literallerinin bir pointer dizisinde tutulduðunu gösteriyor. Ayný deðiller.
				// ve bu dizi read-only, deðiþiklik yapýlamaz. names dizisinde ise yapýlabilir.

	const int a[10][20] = { 0 }; 
	a[3][3] = &x;
		// dizinin hiçbir eleman artýk deðiþtirilemez çünkü const kullanýlmýþ
	
	////////////////////////////////////////////////////////////


	char sortnames[][20] = { "......." }; // hoca buraya çok uzun bir isim listesi yapýþtýrdý. 45. video dk 23

	char* ptr[sizeof(sortnames) / sizeof(sortnames[0][0])];
	for (size_t i = 0; i < sizeof(sortnames) / sizeof(sortnames[0][0]); i++)
	{
		ptr[i] = names[i]; // türleri ayný, açýklama aþaðýda.
	}
	// names in elemanlarý, char türden dizileri tutan elemanlardýr. 
		// türü  ->   char(*pf)[30].
	// names[i]'nin türü ise char* türünden çünkü adres belirtiyor her bir öðe.

	/*
		char *a[100] -> bunu tutacak pointerýn türü ise char **p þeklindedir.
		a[i] ise char *p ile tutulabilir.

		sonuçta names[i] de char * türden, a[i] de char * türden.
		yani eþitlenebilir.
		
	*/
	// Þimdi pointer dizisini bubblesort ile sýralayabiliriz.
#define asize(p) (sizeof(p) / sizeof(p[0]))
		for (size_t i = 0; i < asize(ptr) - 1; i++)
			for (size_t j = 0; j < asize(ptr) - 1 - i; j++)
				if (strcmp(ptr[j], ptr[j + 1]) > 0)
				{
					swap_names(names[j], names[j + 1]);
				}
}
/*
	YANÝ NAMES[][] DÝZÝSÝNÝ DEÐÝÞTÝRMEDÝK FAKAT CHAR * TÜRÜNDEN ELEMANLARI TUTAN BÝR DÝZÝ YARATTIK.
	ADI P. P DÝZÝSÝNDEKÝ ADRESLERÝ YER DEÐÝÞTÝRDÝK AMA NAMES DÝZÝSÝ OLDUÐU GÝBÝ DURUYOR.
	NAMES DEÐÝÞTÝRMEDEN P ÜZERÝNDEN BÝR SORT YAPIYORUZ.YANÝ P NÝN ÝLK ELEMANI ESKÝDEN 0 ÝNDEXLÝ 
	ELEMANI GÖSTERÝRKEN ÞÝMDÝ EN UFAK OLANI GÖSTERÝYOR.O DA 200 GÝBÝ BÝR DEÐER OLABÝLÝR.
*/









////////////////////////////////////////////////////////////////////////////////////////////////
//Yazýdan sayýya - Sayýdan yazýya dönüþümler


int main(void) {
	char str[100];
	printf("dogum yilinizi giriniz: ");
	scanf("&s", str);
	puts(str); 
	atoi(str); // yazýdan int'e dönüþtürüyor. const char* türünden bir deðiþken alýyor.
					// ilk denk geldiði non-digit karakterde çalýþmayý durduruyor. 3152ut yazýldýðýnda 3152'yi döndürür.
	atof(str); // yazýdan double'a.
	atol(str); // long
	atoll(str); // long long
	///////////////////////////////

	char date[100];
	printf("Dogum tarihi dd-mm-yyyy formatinda giriniz: ");
	sgets(date);
	printf("[%s]\n", date);

	int day = atoi(date); // burada dd kýsmý yazýlacak tire'ye gelince duracak.
	int mm = atoi(date + 3); // burada ise tireden sonraki ilk sayýnýn olduðu yerin adresinden baþlatýyoruz. O da 'mm' kýsmýný kapsýyor.
	int year = atoi(date + 6); // mantýk ayný, yyyy kýsmýný kapsýyor.

	printf("[%s] [%d/%d/%d]", date, day, mm, year);
}

///////////////////////////////////////////////////////////////////////////////
//														formatlý giriþ-çýkýþ iþlemleri

/*
scanf standart input bufferýný kullanan formatlý giriþ iþlemidir	


sprintf, adresini aldýðý dizinin belleðine yazýyor. (in-memory input/output deniyo bu iþlem(ler)e)
int sprintf(char* pdest, const char* pfm, ...)
	pdest -> yazýlacak yer
	pfm -> standart outputa yazdýðýný bu adrese yazýyor
Mesela diyelim ki, standart outputa yazdýrdýðýmýz bir yazýyý kullanmak istiyoruz. Bunu için sprintf'i kullanabiliriz.

#define SIZE 100
int main(void) {
	char name[SIZE]; // UGUR
	int year; // 2001
	int idx; // 31

	printf("isim - yil ve idx degerlerini giriniz: ");
	scanf("%s%d%d", name, &year, &idx);

	char file_name[SIZE]; // ugur_2001_031.txt olmasýný istiyoruz dosyamýzýn adýný.
							// bunu std fonksiyonlarý kullanarakta yapabiliriz fakat hem zor hem de çok maliyetli oluyor.
								// tek bir harf ve parametre eklemesi ile rahatça yapabiliriz.
	sprintf(file_name, "%s_%d,%03d.txt", name, year, idx); // bu sayede ugur_2001_031.txt ismini file_name'e bellek üzerinden koyduk.
}
----------------------------------------------
int fprintf(FILE*, const char* pfm, ....); -> bu da dosyaya yazýyor. Dosyalar da görücez bunu.

int scanf(const char* pfm, ...)
int sscanf(const char* pfm, const char* pbuf, ...)
int scanf(FILE*, const char* pfm, ...)
*/
#define SIZE 100
int main(void) {
	char str[SIZE] = { "987     12345    432.2" };

	int x, y;
	double dval;

	sscanf(str, "%d%d%lf", &x, &y, &dval); // sscanf, str'de bulunan deðerleri standart output'ýn bufferýndaymýþ gibi 
											// deðerleri okuyarak x, y ve dval'e atýyor. geri dönüþ deðeri scanf ile ayný 'baþarý deðeri'
}



#define SIZE 100
int scmp(const void* vp1, const void* vp2) {

	// return strcmp((const char*)vp1, (const char*)vp2); -> bu yanlýþ, çünkü char* p[] aslýnda char** türünden bir dizi.
		// böyle yazarak dizinin elemanlarýnýn tuttuðu adrese eriþmiyoruz. Dizinin elemanlarýnýn adresine eriþiyoruz.

	return strcmp(*(char**)vp1, *(char**)vp2); // fonksiyon generic olduðu için ve parametre olarak gönderilen deðiþkenlerin
		// türünün const*[] türünden (const**) olmasýndan dolayý const** a implicit type conversion yapýldý. Derefence edilerekte
			// dizide tutulan yazýlarýn ADRESÝNE eriþildi kendisine deðil. Adresine eriþilen elemanlar arasýnda strcmp ile sýralama yapýldý.
}
int main(void) {

	char* p[] = { "UGUR", "OYKU", "ERSOY", "AHMET", "NECATI", "ERGIN", "GERGIN" };
		// bu dizi char** türünden bir dizi. Yani, string literallerinin adresine eriþmek yerine, o string lateralinin dizideki adresine
			// eriþeceðiz.

}