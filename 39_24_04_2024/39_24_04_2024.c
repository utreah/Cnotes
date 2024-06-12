/*
	


*/

void foo(char* p)
{
	printf("[5] %zu \n", sizeof(p)); // 4 yazdýrýr
}
int main(void)
{
	char str[100] = "sertac";
	char* p = str;
	printf("[1] %zu \n", sizeof(str)); // 100 yazdýrýr 
	printf("[2] %zu \n", sizeof(*str)); // 1 yazdýrýr
	printf("[3] %zu \n", sizeof(p)); // -> bu derleyiciye baðlý. Pointer deðiþkeninin deðerini yazdýrýr benim derleyicim için 8 
	printf("[4] %zu \n", sizeof(*p)); // -> *p char türünden olduðundan dolayý 1 yazdýrýr
	foo(str); // 8 yazdýrýr pointer deðiþkenin deðeri
	printf("[6] %zu \n", strlen(p)); // str yazýsýnýn boyutu : 6 
	printf("[7] %zu \n", sizeof(++p)); // þimdi bu biraz karýþýk. Aslýnda bunun cevabý 8. Karýþýk olan kýsým sonraki için -> benim derleyicimde 8
	printf("[8] %zu \n", strlen(p)); // sizeof keywordunun operandý için kod üretilmez. Bundan dolayý bunun cevabý ilk gören birisi için 5 olabilir
									// sorunun asýl cevabý ise yazýnýn uzunluðu olan 6. sizeof operatörünün operandý deðer üretmediði için 
										// ++p'nin yan etkisi yok. Bu ÇOK ÖNEMLÝ MÜLAKATTA SORARLAR.
	printf("[9] %zu \n", sizeof("sertac")); // 7 elemanlý, char dizi türü olduðundan dolayý ==> 7
	printf("[10] %zu \n", sizeof(char[7])); // bir üsttekini pekiþtirmek için
	printf("[11] %zu \n", strlen("sertac")); // sertac'ýn harf sayýsý ==> 6
	printf("[12] %zu \n", sizeof("")); // sadece null karakter var ==> 1
	printf("[13] %zu \n", strlen("")); // strlen yazýnýn uzunluðu döndürdüðü için ==> 0

	// "" -> buna null string literal deniyor. Boyutu 1, uzunluðu 0.
}
//////////////////////////////////////////////////////////////////////////////////////////////
/*
	strpbrk = strpbrk bir string içerisinde belirli bir karakter veya karakterleri arýyor strstr'den farký budur. strstr bir 
		string içerisinde bir string arýyor.
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
	int x = 10; // int türünden 1 adet eleman 4 bytelýk yer kaplýyor ve tam sayý deðeri tutuyor.
	int y[5]; // int türünden 5 adet eleman 4 bytelýk yer kaplýyor(toplam 20) ve 20 adet tam sayý deðeri tutuyor.
	int* ptr; // int*(pointer) türünden 1 adet eleman. 4 bytelýk yer kaplýyor ve ADRES deðeri tutuyor.
	int* ptrarr[5];  // int* (pointer) türünden 5 adet eleman 4 bytelýk yer kaplýyor(toplam 20) ve 20 adet ADRES deðeri tutuyor.


	ptrarr[0]; // pointer to int conversion
	////////////////////
	int x = 10;
	int* p = &x;
	int* arr[10];
	int* ptr;
	ptr = &x;
	arr[0] = %x; // uzun lafýn kýsasý pointer arraylerde adresleri bir dizide tutuyor.

	-Tüm pointer türleri eþit yer kaplar
		-| char, int, double
////////////////////////////////

#include <stdio.h>

int x = 40;
int y = 60;
int z = 50;
int main(void){
	int* a[] = {&x, &y, &z}; // pointer dizilerine bu þekilde ilk deðer atamasý yapýlabilir.

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
	++p[2]; // Burada p int* dizisindeki c adlý dizinin adresine eriþiyoruz ve adresi 1 arttýrýyoruz.
				// (c + 0) iken (c + 1) oluyor ve c dizisinde artýk '45' deðerinin adresindeyiz. 
	++*p[2]; // bir önceki iþlemde 45 deðerinin adresine gelmiþtik, burada da o adresi dereference ederek deðerini 1 arttýrýyoruz.
				// c[1] deðeri artýk 46 oldu.
	printf("%d\n", *(c + 1)); // 46


	int* f[5] = {&x, 0&y};
	f[3]; // ilk deðer verildiði durumda bu NULL ptryi iþaret eder. Statik ömürlü deðiþkenler ile ilk deðer verilmiþ
			// otomatik ömürlü dizi(deðiþkende dahil) doldurulmayan dizi elemanlarý nullptr'nin deðerini alýr.
}
int x, y, z;
int main(void){		  x44 x55 x66
	int* const p[] = {&x, &y, &z}; // Böyle bir durumda x, y ve z'nin içerikleri deðiþtirilemez. Fakat dizideki
										// adresler baþka bir adres ile deðiþtirilebilir.
	p[1] = &t; // Bu C'de UB. Çünkü read-only bir dizinin elemanýn içeriðini deðiþtirmeye çalýþýyoruz.
	*p[1] = 543; deðeri deðiþir 
	//////////////
	const int* p[] = {&x, &y, &z);
	p[1] = &t; // bunda sýkýntý yok çünkü const keywordü dizinin tuttuðu adres(ler)in deðerleri ile ilgileniyor.
	*p[1] = 10; // UB, çünkü adresin gösterdiði deðeri deðiþtirmeye çalýþýyoruz YASAK KOÇUM YASAK.
	/////////////

	char* carr[] = {"UGUR", "OYKU", "FIRUZE", "ERSOY"};
	carr[0] = "UTREAH"; // bunda sýkýntý yok. Çünkü "UGUR" bir string literali ve biz onun üstünde hiçbir deðiþiklik yapmýyoruz.
							// string literallari hem const hem de statik. Bundan dolayý deðer atamasý/deðiþikliði yapamayýz.
								// Biz line135'te dizinin 0 numaralý indexsine yeni bir ADRES ATIYORUZ
	*carr[0] = "X"; // UB, çünkü string literallarinin deðeri deðiþtirilemez.
	
	// eðer string pointer dizileri string literallerini tutacak ise const ile tanýmlamakta fayda var.
		// eðer yukarýda const char* olarak tanýmlamýþ olsaydýk UB yerine sentaks hatasý olacaktý.
			// UB olacaðýna mermi ye daha iyi.



	Mantýksal iliþki içerisindeki yapýlara doðrudan dizinin indexi ile eriþiliyor ise buna "lookup table" denir.
		char* arr[] = {"UGUR", "OYKU", "ERSOY}; 

		char* pdays = {"Pazartesi", "Salý", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"};
			// Þimdi ben burada pdays[2] = "mehmet"; þeklinde yazarak Çarþambanýn olduðu indexi deðiþtirebilirim.
				// Bunun önüne geçmek için 'char* const pdays[]' þeklinde tanýmlamalýyým. Bu sayede yanlýþlýkla
					// yapýlabilecek deðiþikliklerin önüne geçmiþ olurum ve sentaks hatasý alýrým.
			//*pdays[3] = 'k'; yaptýðýmda bu sentaks hatasý deðil, UB. Bunun önüne geçmek için char*'ýn baþýna const koyabilirim.
				// const char* const pdays[];


int main(void) // ben böyle yaptým, hoca for ile yapýyor ve if(i<12) kontrolünü kullanýyor.
{
    const char* const pdays[] = {"Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"};
    char entry[15];
    scanf("%s", entry);
    size_t i = 0;
    while(pdays[i]){
        if(!sstrcmp(pdays[i], entry)){ 
            printf("(%s) gunu (%zu.) gun ", entry, i+1); // burada print etmek yerine direkt break ile döngüden çýkýyor.
            break;
        }
        i++;
        
    }
	////////////////Necati hoca//////////////////
		// if(i < 12) // i hala 12den küçük ise istenileni bulmuþ demek
            //printf("(%s) gunu (%zu.) gun ", entry, i+1);
		//	else // eðer 12den küçük deðil ise bulamamýþ demek
			// printf("Gün bulunamadý");
	////////////////Necati hoca//////////////////
}
	EÐER!!
	// char* const p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"}; þeklinde eðer const keywordü yýldýzýn solunda ise
		burada elemanlarý const olur. Yani elemanlarda deðiþiklik yapýlamaz.
	*p[3] = "UGUR"; // Bu zaten normalde UB. 
	p[3] = "UGUR"; // Bu da sentaks hatasý çünkü "UGUR" bir adres ve biz elemanlarý const olan bir dizinin
					// elemanýný deðiþtirmeye çalýþýyoruz.
	EÐER!!
	// const char* p[5] = {"Ali","Veli","Hasan","Huseyin","Mert"}; þeklinde tanýmlanýr ise
	p[3] = "UGUR"; Bunda bir sýkýntý yok. Burada const olan elemanlar deðil, içerikler. Yani bir sonraki satýra bak
	*p[3] = "U"; // Zaten string literali read-only const olduðu için deðiþiklik yapýlamaz. Bu normalde undefined behaviour.
					// ama biz bu pointer dizisini const olarak cast ettiðimiz için bu UB deðil sentaks hatasý. Ayný bok farklý sonuç.

	ÖZETLE;
		Eðer const keywordü * operatörünün solunda ise read-only, yani içerik deðiþmez ama adres deðiþebilir.
		Eðer const keywordü * operatörünün saðýnda ise adres deðiþmez ama içerik deðiþebilir(fakat string literallerinde içerikte deðiþmez)

//////////////////////
	çok büyük bir array yazdý 333 boyutlu.Önceden hazýrlanmýþ.
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
	printf("Gunun ismi: (%-16s) Uzunlugu: (%d)\n", pdays[i], strlen(pdays[i]); // Hem günün ismini hem de uzunluðunu yazdýrýr.
		// %16s yazmýþ olsaydým specifier kýsmýna yazýyý yazdýrýrken saða 16 birim dayalý yazdýracaktý.
			// %-16s yazarak sola 16 birim dayalý oluyor ve bu sayede isimler ve uzunluklar daha düzgün gözüküyor.
//sadece ilk harflerini yazdýran kod
for(size_t i = 0; i < sizeof(a) / sizeof(*a); i++) 
	printf("Gunun Ýsmi: (%-16s) Ilk harfi:(%c)", pdays[i], *pdays[i]); // Gün ismi + o günün ilk karakterini yazdýrýr. Pazartesi -> P
								// *pdays[i] yerine pdays[i][0] da yazýlabilirdi. pdays[i] bir yazýnýn adresini tutuyor.
									// ve o yazýda bir string literali olduðu için ayný zamanda char türünden bir dizi.
										//Biz bu þekilde yazarak aslýnda i'nin gösterdiði indexteki dizinin ilk elemanýna eriþmiþ oluyoruz.
//sadece son harflerini yazdýran kod
for(size_t i = 0; i < sizeof(pdays) / sizeof(*pdays); i++)
	printf("Gunun ismi: ( %-10s)  Son Harfi: (%c)\n", pdays[i], pdays[i][strlen(pdays[i]) - 1]);
									// strlen(pday[i]) - 1 yaparak dizinin uzunluðu bulup dizinin bittiði adresten
										// dizinin son elemanýna gidiyoruz.

//Ýçinde hangi karakter olanlarý bul.
int ch = getchar();
for(size_t i = 0; i < sizeof(pdays) / sizeof(*pdays); i++)
	if(strchr(pdays[i], ch))
		printf("Gunun ismi: ( %-10s) Aranan Karakter: (%c)\n", pdays[i], ch);

//Ýçinde belirli bir kelimeyi arama -> 'er' mesela
char entry[40];
printf("bir yazi giriniz\n");
(void)scanf("%s", entry);

//dizi içinde yazý içeren kelimeler
for (size_t i = 0; i < asize(pdays); i++)
	if (strstr(pdays[i], entry))
		printf("%s\n", pdays[i]);
//Alfabetik sýralama(a'dan z'ye) -> büyük boyutlu dizelerde çalýþmaz
for(size_t i = 0; i < asize(pdays); i++)
	for(size_t j = 0; j < asize(pdays) - 1 - i; j++)
		if(strcmp(pdays[i], pdays[j]) < 0){
			const char* temp = pdays[i];
			pdays[i] = pdays[j];
			pdays[j] = temp;
		}
//Alfabetik sýralama hocanýn yazdýðý kod
for(size_t i = 0; i < asize(pdays) - 1; i++)
	for(size_t j = 0; j < asize(pdays) - i - 1; j++)
		if(strcmp(pdays[j], pdays[j + 1]) > 0){
			const char* temp = pdays[j];
			pdays[j] = pdays[j + 1];
			pdays[j + 1] = temp;
		}
//Önce uzunluk olarak küçükten büyüðe sýralýyor daha sonra da uzunluklarý ayný olanlar arasýnda alfabetik sýraya sokuyor.	
	// bu benim yazdýðým kod.
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
//Önce uzunluk olarak küçükten büyüðe sýralýyor daha sonra da uzunluklarý ayný olanlar arasýnda alfabetik sýraya sokuyor. Hocanýn kodu.
for(size_t i = 0; i < asize(pdays) - 1; i++)
	for(size_t j = 0; j < asize(pdays) - i - 1; j++){
		if(strlen(pdays[j]) > strlen(pdays[j+1]) || strcmp(pdays[j], pdays[j+1]) > 0 && strlen(pdays[j]) == strlen(pdays[j+1])){
			const char* temp = pdays[j];
			pdays[j] = pdays[j + 1];
			pdays[j + 1] = temp;
		}
	}
	// if'in ilk kýsmý için eðer koþul doðruysa short circuittan faydalanarak uzunluk sýralamasý yapýyoruz
		// Eðer yanlýþ ise, OR'ýn sað operandýna bakýyoruz. O da zaten benim yazdýðým koþulun aynýsý
/					GENEL KODLAMA KURALLARI												/
-Fonksiyonlarý çok uzun yazmamak. Fonksyonlarýn içeriklerini kýsa tutmalýyýz ki ileride yapýlabilecek deðiþikliklerde
	hem anlamasý kolay olsun hem de deðiþiklik yapýlmasý kolay olsun. 




*/






/*
========================================================================
========================================================================
========================================================================

ÖDEV
char* strprepen(char* pdest, const char* psource)
pdest in baþýna psource u ekliyor.bunu yaz.umut kotankiran->kotankiran umut yazacak

========================================================================
========================================================================
========================================================================
*/