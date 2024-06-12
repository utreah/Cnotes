/*
	


*/

void foo(char* p)
{
	printf("[5] %zu \n", sizeof(p)); // 4 yazd�r�r
}
int main(void)
{
	char str[100] = "sertac";
	char* p = str;
	printf("[1] %zu \n", sizeof(str)); // 100 yazd�r�r 
	printf("[2] %zu \n", sizeof(*str)); // 1 yazd�r�r
	printf("[3] %zu \n", sizeof(p)); // -> bu derleyiciye ba�l�. Pointer de�i�keninin de�erini yazd�r�r benim derleyicim i�in 8 
	printf("[4] %zu \n", sizeof(*p)); // -> *p char t�r�nden oldu�undan dolay� 1 yazd�r�r
	foo(str); // 8 yazd�r�r pointer de�i�kenin de�eri
	printf("[6] %zu \n", strlen(p)); // str yaz�s�n�n boyutu : 6 
	printf("[7] %zu \n", sizeof(++p)); // �imdi bu biraz kar���k. Asl�nda bunun cevab� 8. Kar���k olan k�s�m sonraki i�in -> benim derleyicimde 8
	printf("[8] %zu \n", strlen(p)); // sizeof keywordunun operand� i�in kod �retilmez. Bundan dolay� bunun cevab� ilk g�ren birisi i�in 5 olabilir
									// sorunun as�l cevab� ise yaz�n�n uzunlu�u olan 6. sizeof operat�r�n�n operand� de�er �retmedi�i i�in 
										// ++p'nin yan etkisi yok. Bu �OK �NEML� M�LAKATTA SORARLAR.
	printf("[9] %zu \n", sizeof("sertac")); // 7 elemanl�, char dizi t�r� oldu�undan dolay� ==> 7
	printf("[10] %zu \n", sizeof(char[7])); // bir �sttekini peki�tirmek i�in
	printf("[11] %zu \n", strlen("sertac")); // sertac'�n harf say�s� ==> 6
	printf("[12] %zu \n", sizeof("")); // sadece null karakter var ==> 1
	printf("[13] %zu \n", strlen("")); // strlen yaz�n�n uzunlu�u d�nd�rd��� i�in ==> 0

	// "" -> buna null string literal deniyor. Boyutu 1, uzunlu�u 0.
}
//////////////////////////////////////////////////////////////////////////////////////////////
/*
	strpbrk = strpbrk bir string i�erisinde belirli bir karakter veya karakterleri ar�yor strstr'den fark� budur. strstr bir 
		string i�erisinde bir string ar�yor.
char* my_strpbrk(const char* p1, const char* p2) {
	while (*p) {
		if (strchr(p2, *p1))
			return (char*)*p1;
			++p;
	}
	return NULL;
}
*/

#include <stddef.h>
#define SIZE 100
int main(void) {
	char s1[SIZE] = { 0 };
	char s2[SIZE] = { 0 };
	char* p;
	printf("birinciyi girin :");
	sgets(s1);
	printf("ikinci girin :");
	sgets(s2);

	printf("%s yazisinda %s karakterlerinden biri araniyor\n", s1, s2);

	p = my_strpbrk(s1, s2);
	if (p == NULL)
		printf("%s yazisinda %s karanterlerinden biri bulunamadi\n", s1, s2);
	else
	{
		printf("bulundu. index = %d\n", p - s1);
		puts(p);
	}
}
/*
													POINTER ARRAYS
	int x = 10; // int t�r�nden 1 adet eleman 4 bytel�k yer kapl�yor ve tam say� de�eri tutuyor.
	int y[5]; // int t�r�nden 5 adet eleman 4 bytel�k yer kapl�yor(toplam 20) ve 20 adet tam say� de�eri tutuyor.
	int* ptr; // int*(pointer) t�r�nden 1 adet eleman. 4 bytel�k yer kapl�yor ve ADRES de�eri tutuyor.
	int* ptrarr[5];  // int* (pointer) t�r�nden 5 adet eleman 4 bytel�k yer kapl�yor(toplam 20) ve 20 adet ADRES de�eri tutuyor.


	ptrarr[0]; // pointer to int conversion
	////////////////////
	int x = 10;
	int* p = &x;
	int* arr[10];
	int* ptr;
	ptr = &x;
	arr[0] = %x; // uzun laf�n k�sas� pointer arraylerde adresleri bir dizide tutuyor.

	-T�m pointer t�rleri e�it yer kaplar
		-| char, int, double
////////////////////////////////

#include <stdio.h>

int x = 40;
int y = 60;
int z = 50;
int main(void){
	int* a[] = {&x, &y, &z}; // pointer dizilerine bu �ekilde ilk de�er atamas� yap�labilir.

	for(size_t i = 0; i < 3; i++)
		++*a[i];
	printf("x = %d\n", *a[0]); // 41
	printf("y = %d\n", *a[1]); // 61
	printf("z = %d\n", *a[2]); // 51
}

int main(void){
	int a[] = {1, 2, 3, 6}; 
	int b[] = {4,12,13,15};
	int c[] = {17, 45, 67, 98};

	int* p[] = {a, b, c};
	++p[2]; // Burada p int* dizisindeki c adl� dizinin adresine eri�iyoruz ve adresi 1 artt�r�yoruz.
				// (c + 0) iken (c + 1) oluyor ve c dizisinde art�k '45' de�erinin adresindeyiz. 
	++*p[2]; // bir �nceki i�lemde 45 de�erinin adresine gelmi�tik, burada da o adresi dereference ederek de�erini 1 artt�r�yoruz.
				// c[1] de�eri art�k 46 oldu.
	printf("%d\n", *(c + 1)); // 46


	int* f[5] = {&x, 0&y};
	f[3]; // ilk de�er verildi�i durumda bu NULL ptryi i�aret eder. Statik �m�rl� de�i�kenler ile ilk de�er verilmi�
			// otomatik �m�rl� dizi(de�i�kende dahil) doldurulmayan dizi elemanlar� nullptr'nin de�erini al�r.
}
int x, y, z;
int main(void){		  x44 x55 x66
	int* const p[] = {&x, &y, &z}; // B�yle bir durumda x, y ve z'nin i�erikleri de�i�tirilemez. Fakat dizideki
										// adresler ba�ka bir adres ile de�i�tirilebilir.
	p[1] = &t; // Bu C'de UB. ��nk� read-only bir dizinin eleman�n i�eri�ini de�i�tirmeye �al���yoruz.
	*p[1] = 543; de�eri de�i�ir 
	//////////////
	const int* p[] = {&x, &y, &z);
	p[1] = &t; // bunda s�k�nt� yok ��nk� const keyword� dizinin tuttu�u adres(ler)in de�erleri ile ilgileniyor.
	*p[1] = 10; // UB, ��nk� adresin g�sterdi�i de�eri de�i�tirmeye �al���yoruz YASAK KO�UM YASAK.
	/////////////

	char* carr[] = {"UGUR", "OYKU", "FIRUZE", "ERSOY"};
	carr[0] = "UTREAH"; // bunda s�k�nt� yok. ��nk� "UGUR" bir string literali ve biz onun �st�nde hi�bir de�i�iklik yapm�yoruz.
							// string literallari hem const hem de statik. Bundan dolay� de�er atamas�/de�i�ikli�i yapamay�z.
								// Biz line135'te dizinin 0 numaral� indexsine yeni bir ADRES ATIYORUZ
	*carr[0] = "X"; // UB, ��nk� string literallarinin de�eri de�i�tirilemez.
	
	// e�er string pointer dizileri string literallerini tutacak ise const ile tan�mlamakta fayda var.
		// e�er yukar�da const char* olarak tan�mlam�� olsayd�k UB yerine sentaks hatas� olacakt�.
			// UB olaca��na mermi ye daha iyi.



	Mant�ksal ili�ki i�erisindeki yap�lara do�rudan dizinin indexi ile eri�iliyor ise buna "lookup table" denir.
		char* arr[] = {"UGUR", "OYKU", "ERSOY}; 

		char* pdays = {"Pazartesi", "Sal�", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"};
			// �imdi ben burada pdays[2] = "mehmet"; �eklinde yazarak �ar�amban�n oldu�u indexi de�i�tirebilirim.
				// Bunun �n�ne ge�mek i�in 'char* const pdays[]' �eklinde tan�mlamal�y�m. Bu sayede yanl��l�kla
					// yap�labilecek de�i�ikliklerin �n�ne ge�mi� olurum ve sentaks hatas� al�r�m.
			//*pdays[3] = 'k'; yapt���mda bu sentaks hatas� de�il, UB. Bunun �n�ne ge�mek i�in char*'�n ba��na const koyabilirim.
				// const char* const pdays[];


int main(void) // ben b�yle yapt�m, hoca for ile yap�yor ve if(i<12) kontrol�n� kullan�yor.
{
    const char* const pdays[] = {"Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"};
    char entry[15];
    scanf("%s", entry);
    size_t i = 0;
    while(pdays[i]){
        if(!sstrcmp(pdays[i], entry)){ 
            printf("(%s) gunu (%zu.) gun ", entry, i+1); // burada print etmek yerine direkt break ile d�ng�den ��k�yor.
            break;
        }
        i++;
        
    }
	////////////////Necati hoca//////////////////
		// if(i < 12) // i hala 12den k���k ise istenileni bulmu� demek
            //printf("(%s) gunu (%zu.) gun ", entry, i+1);
		//	else // e�er 12den k���k de�il ise bulamam�� demek
			// printf("G�n bulunamad�");
	////////////////Necati hoca//////////////////
}
	E�ER!!
	// char* const p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"}; �eklinde e�er const keyword� y�ld�z�n solunda ise
		burada elemanlar� const olur. Yani elemanlarda de�i�iklik yap�lamaz.
	*p[3] = "UGUR"; // Bu zaten normalde UB. 
	p[3] = "UGUR"; // Bu da sentaks hatas� ��nk� "UGUR" bir adres ve biz elemanlar� const olan bir dizinin
					// eleman�n� de�i�tirmeye �al���yoruz.
	E�ER!!
	// const char* p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"}; �eklinde tan�mlan�r ise
	p[3] = "UGUR"; Bunda bir s�k�nt� yok. Burada const olan elemanlar de�il, i�erikler. Yani bir sonraki sat�ra bak
	*p[3] = "U"; // Zaten string literali read-only const oldu�u i�in de�i�iklik yap�lamaz. Bu normalde undefined behaviour.
					// ama biz bu pointer dizisini const olarak cast etti�imiz i�in bu UB de�il sentaks hatas�. Ayn� bok farkl� sonu�.

	�ZETLE;
		E�er const keyword� * operat�r�n�n solunda ise read-only, yani i�erik de�i�mez ama adres de�i�ebilir.
		E�er const keyword� * operat�r�n�n sa��nda ise adres de�i�mez ama i�erik de�i�ebilir(fakat string literallerinde i�erikte de�i�mez)

//////////////////////
	�ok b�y�k bir array yazd� 333 boyutlu.�nceden haz�rlanm��.
	Onunla ilgili kodlar yazacak.

const char const* pdays[] = {
	"Pazartesi",
	"Sali",
	"Carsamba",
	"Persembe",
	"Cuma",
	"Cumartesi",
	"Pazar"
	};
//sadece uzunlugunu yazdiran kod
for(size_t i = 0; i < sizeof(a) / sizeof(*a); i++) 
	printf("Gunun ismi: (%-16s) Uzunlugu: (%d)\n", pdays[i], strlen(pdays[i]); // Hem g�n�n ismini hem de uzunlu�unu yazd�r�r.
		// %16s yazm�� olsayd�m specifier k�sm�na yaz�y� yazd�r�rken sa�a 16 birim dayal� yazd�racakt�.
			// %-16s yazarak sola 16 birim dayal� oluyor ve bu sayede isimler ve uzunluklar daha d�zg�n g�z�k�yor.
//sadece ilk harflerini yazd�ran kod
for(size_t i = 0; i < sizeof(a) / sizeof(*a); i++) 
	printf("Gunun �smi: (%-16s) Ilk harfi:(%c)", pdays[i], *pdays[i]); // G�n ismi + o g�n�n ilk karakterini yazd�r�r. Pazartesi -> P
								// *pdays[i] yerine pdays[i][0] da yaz�labilirdi. pdays[i] bir yaz�n�n adresini tutuyor.
									// ve o yaz�da bir string literali oldu�u i�in ayn� zamanda char t�r�nden bir dizi.
										//Biz bu �ekilde yazarak asl�nda i'nin g�sterdi�i indexteki dizinin ilk eleman�na eri�mi� oluyoruz.
//sadece son harflerini yazd�ran kod
for(size_t i = 0; i < sizeof(pdays) / sizeof(*pdays); i++)
	printf("Gunun ismi: ( %-10s)  Son Harfi: (%c)\n", pdays[i], pdays[i][strlen(pdays[i]) - 1]);
									// strlen(pday[i]) - 1 yaparak dizinin uzunlu�u bulup dizinin bitti�i adresten
										// dizinin son eleman�na gidiyoruz.

//��inde hangi karakter olanlar� bul.
int ch = getchar();
for(size_t i = 0; i < sizeof(pdays) / sizeof(*pdays); i++)
	if(strchr(pdays[i], ch))
		printf("Gunun ismi: ( %-10s) Aranan Karakter: (%c)\n", pdays[i], ch);

//��inde belirli bir kelimeyi arama -> 'er' mesela
char entry[40];
printf("bir yazi giriniz\n");
(void)scanf("%s", entry);

//dizi i�inde yaz� i�eren kelimeler
for (size_t i = 0; i < asize(pdays); i++)
	if (strstr(pdays[i], entry))
		printf("%s\n", pdays[i]);
//Alfabetik s�ralama(a'dan z'ye) -> b�y�k boyutlu dizelerde �al��maz
for(size_t i = 0; i < asize(pdays); i++)
	for(size_t j = 0; j < asize(pdays) - 1 - i; j++)
		if(strcmp(pdays[i], pdays[j]) < 0){
			const char* temp = pdays[i];
			pdays[i] = pdays[j];
			pdays[j] = temp;
		}
//Alfabetik s�ralama hocan�n yazd��� kod
for(size_t i = 0; i < asize(pdays) - 1; i++)
	for(size_t j = 0; j < asize(pdays) - i - 1; j++)
		if(strcmp(pdays[j], pdays[j + 1]) > 0){
			const char* temp = pdays[j];
			pdays[j] = pdays[j + 1];
			pdays[j + 1] = temp;
		}
//�nce uzunluk olarak k���kten b�y��e s�ral�yor daha sonra da uzunluklar� ayn� olanlar aras�nda alfabetik s�raya sokuyor.	
	// bu benim yazd���m kod.
for(size_t i = 0; i < asize(pdays) - 1; i++)
	for(size_t j = 0; j < asize(pdays) - i - 1; j++){
		if(strlen(pdays[j]) > strlen(pdays[j+1])){
			const char* temp = pdays[j];
			pdays[j] = pdays[j + 1];
			pdays[j + 1] = temp;
		}
		else if(strcmp(pdays[j], pdays[j+1]) > 0 && strlen(pdays[j]) == strlen(pdays[j+1])){
			const char* temp = pdays[j];
			pdays[j] = pdays[j + 1];
			pdays[j + 1] = temp;
		}
	}
//�nce uzunluk olarak k���kten b�y��e s�ral�yor daha sonra da uzunluklar� ayn� olanlar aras�nda alfabetik s�raya sokuyor. Hocan�n kodu.
for(size_t i = 0; i < asize(pdays) - 1; i++)
	for(size_t j = 0; j < asize(pdays) - i - 1; j++){
		if(strlen(pdays[j]) > strlen(pdays[j+1]) || strcmp(pdays[j], pdays[j+1]) > 0 && strlen(pdays[j]) == strlen(pdays[j+1])){
			const char* temp = pdays[j];
			pdays[j] = pdays[j + 1];
			pdays[j + 1] = temp;
		}
	}
	// if'in ilk k�sm� i�in e�er ko�ul do�ruysa short circuittan faydalanarak uzunluk s�ralamas� yap�yoruz
		// E�er yanl�� ise, OR'�n sa� operand�na bak�yoruz. O da zaten benim yazd���m ko�ulun ayn�s�
/					GENEL KODLAMA KURALLARI												/
-Fonksiyonlar� �ok uzun yazmamak. Fonksyonlar�n i�eriklerini k�sa tutmal�y�z ki ileride yap�labilecek de�i�ikliklerde
	hem anlamas� kolay olsun hem de de�i�iklik yap�lmas� kolay olsun. 




*/






/*
========================================================================
========================================================================
========================================================================

�DEV
char* strprepen(char* pdest, const char* psource)
pdest in ba��na psource u ekliyor.bunu yaz.umut kotankiran->kotankiran umut yazacak

========================================================================
========================================================================
========================================================================
*/