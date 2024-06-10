/*
		YAZILARIN KARÞILAÞTIRILMASI - 2
	char s1[SIZE] = {0};
	char s2[SIZE] = {0};

	printf("iki adet isim girin : ");
	(void)scanf("%s%s", s1, s2);

	int cmp_result = strcmp(s1, s2);

	if (cmp_result > 0) // herhangibir pozitif deðer 1 deðil
		printf("%s > %s", s1, s2);
	else if (cmp_result < 0) // herhangibir negatif deðer -1 deðil
		printf("%s < %s", s1, s2);
	else
		printf("%s = %s", s1, s2);

*/

int my_strcmp(const char* p1, const char* p2)
{
	while (*p1 == *p2) {
		if (*p1 == '\0') // eper *p1 NULL ise *p2'de null karakterdir. Çünkü while döngüsüne girerken ikisi de eþit olduðu için girdi.
			return 0;		// eðer farklý ise döngüden çýkacak zaten
		++p1;
		++p2;
	}

	return *p1 - *p2; // eðer *p1 büyükse pozitif, p2 büyükse negatif döndürecek. const char türünden 2 deðiþken iþleme giriyor.
						// integral promotiondan dolayý iþlem int türünde yapýlýr.

}
/*
	MÜLAKAT:
		Mülakatlarda belirli bir kelimenin sonda olup olmadýðýný bulabilecek bir program yazdýrýlabiliyor.
			-Sonda olup olmadýðýný kontrol etmek için arama yapýlacak metinin sonuna adresle yazýnýn boyutu toplanarak gidilir. (p1 + strlen(p1))
			-Eðer aranan kelime metinden/yazýdan uzun ise UB oluþturacaðýndan false(0) deðeri return edilir.
			-strcmp fonksiyonu kullanarak sonda olup olmadýðý kontrol edilir.
			-Parametre olarak, ilk parametre -> 'yazýnýn adresi + yazýnýn uzunluðu - aranan yazýnýn uzunluðu' olur. ikinci parametre ise
				aranan yazýnýn adresi.

*/
#include <stddef.h>
int is_at_end(const char* p1, const char* p2)
{
	size_t len1 = strlen(p1);
	size_t len2 = strlen(p2);
	if (len2 > len1)
		return 0; // p1 bizim içerisinde yazý arayacaðýmýz metin. Eðer aranacak kelime/yazýnýn uzunluðu ana metinden uzunsa bu
					// ub oluþturacaðý için uzunluklarýný karþýlaþtýrýyoruz. Eðer p2 daha uzunsa boolean 0 döndürüyoruz.

	return !my_strcmp(p1 + len1 - len2, p2); // p1 + len1 - len2 iþlemi bize ilk dizinin bittiði yerden aradýðýmýz kelimenin
												// uzunluðunu çýkararak strcmp'de arýyor. Eðer sonuç 0 ise kelime bulunmuþtur demek.
													// true olmasý için 'not' operatörü ile tersine çeviriyoruz. Çünkü fonksiyon yanlýþlýk durumunda
													// non-zero bir deðer döndürüyor.
}

char* prepend(char* p1, const char* p2) // ödev, append fonksiyonun tersi bu. Append yazýnýn sonuna ekleme yaparken prepend baþýna ekleme yapýyor.
{											// bunun kodunu yazmam gerek.

}


/*
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	==============================================================================================================================================================================================
	
*/
// Þu anlýk std fonksiyonlarýna ara verdik. Þimdi EN ZOR KISIMA BAÞLIYORUZ.
/*
	Neler bu konular?
-string literals
-pointer arrays
-pointer to pointer
-void pointers
-function pointers
-multi-dimensional arrays
-Dynamic Memory Management

*/
/*
		STRING LITERALS
	-Çift týrnak içinde bulunan yazýlar birer tokendýr. "UGUR" -> bu bir token ve adresi var. Bu tokenlara 'string literals' denir.
		Aslýnda "ugur" != "ersoy" gibi string literalleri karþýlaþtýrýlýrsa burada yazýlar deðil adresler karþýlaþtýrýlmýþ olur.
	-Literal, constant(sabit) anlamýna gelebiliyor. Bazý yerlerde constant bazý yerlerde literal denmesiyle karþýlaþabiliriz.
	-C'de 'A' -> bir karakter sabiti, CPP'de ise karakter literali olarak adlandýrýlmýþ.
	-String literallarinin sonunda da null karakteri vardýr.
	-"UGUR" -> bu 5 karakterli bir string literalý ve veri türü -> char[5] (Sonunda null karakter var ondan 5 karakter)
	-char str[3]; ben str'yi bir ifade içerisinde kullandýðýmda array decayden dolayý str'nin adresini nasýl yerini alýyorsa
		bir string literalini ifadede kullandýðýmda string literalinin adresi yerini alýr.
		-|*"ugur" -> string literali dereferencing(içerik) operatörünü alabilir. 
			-| string literalinde içerik operatörü kullanýldýðýnda deðeri o stringin ilk karakteridir.
				Mesela *"ugur" için -> 'u'
	-Eðer bir string literalinin yanýna subscript operatörü kullanýlýrsa: 
		-| "ugur"[2] -> burada 2. 'u' karakterinin adresi gösterilmiþ.
		-| 2["ugur"] -> burada da 2. 'u' karakterinin adresi gösteriliyor. Bu subscript operatörü kullanýldýðýnda derleyicinin ürettiði koddan dolayý.
			p[i] aslýnda *(p + i) bundan dolayý i[p] olduðunda da üretilen kod -> *(i + p) 

	-String literallarý fonksiyonlara adres deðiþkeni alan parametrelere direkt yollanabilir.
		char str[100];
		strcpy(str, "UGUR ERSOY"); // str dizisine UGUR ERSOY'u kopyalar

		char *p = "Oyku Ersoy"; // "Oyku Ersoy" þeklinde bir string literalý oluþturarak derleyiciye bir dizi oluþturtuyorum
									// ve bu dizinin adresini bir pointerda tutuyorum.
		puts(p); yukarýdakini yazdýrýr

		printf("uzunluk : %zu\n",strlen(p)); -> uzunluk 10 yazar.
		printf("uzunluk : %zu\n",strlen("OYKU ERSOY")); -> uzunluk 10 yazar.

	-String literallari hem C dilinde hem de CPP dilinde salt okuma(read-only) amaçlý kullanýlabilir.
		string literallarini deðiþtirme giriþimi her iki dilde de tanýmsýz davranýþtýr.
		-| char* p = "cetin";
		   puts(p); // ekrana cetin yazdýrýr
		   *p = 'M'; // hop tanýmsýz davranýþ
	-String literalleri veri türü olarak char[SIZE] olsa da sadece okuma amaçlý kullanýlabilirler. 
		-|Bundan dolayý string literalinin adresini bir deðiþkende tutacaksak o deðiþkeni 'const' keywordu ile bildirmeliyiz.
			-| const char* p = "string literali";
		-|C dilinde string literali char türünde, CPP'de ise const char türündedir.

	-Bir string literalini parametresi pointer olan bir fonksiyona argüman olarak gönderilecekse, parametrenin
		const char* türünden olmasý gerek!
	-string literalleri statik ömürlü dizilerdir.
		a)programýn sonuna kadar bellekte tutulduðu anlamýna geliyor
		b)özel bir segmentte tutuluyor
		c)çalýþtýðý sistemin ne olduðuna belli olarak alaný çok ya da az olabilir.
	
	-Bir fonksiyon asla dinamik ömürlü bir nesnenin adresini/deðerini döndürmemelidir.	
		-|Adres döndüren bir fonksiyon bir string literalini döndürebilir.

	-Ayný string literali ayný yerde ya da farklý yerlerde tutulmasý tamamen derleyiciye baðlý(line 184)
		Yani ayný string literali için deðiþik adreste kullanabilir, ayný adresi de kullanabilir. Tamamen derleyiciye baðlý.
		 "ahmet" == "ahmet" unspecified behaviour
			char *p1 = "emre";
			char *p2 = "emre";

			if(p1 == p2)
				printf("evet esit\n");			
			else
				printf("hayir degil\n");

			Evette yanlýþ
			hayýrda yanlýþ
			Unspecified behavior.belirsiz davranýþ.
			Birçok derleyicide evet yada yanlýþ olmasý durumunu seçebiliyoruz.


		soru
	1. char p[] = "maya";  UB mi
	2. char * ptr = "maya";  UB mi


	1. char diziye ilk deðer verme sentaksýnýn bileþeni.yani buradaki mert yazýsý bellekte ayrý bir
	dizide tutulmayacak.Ayrýca derleyici tarafýndan oluþturulan bir dizi yok.
	yani burada p[0] = 'K'; yapýlabilir. UB YOK.

	2. burada iki ayrý deðiþken var aslýnda.Az önce diziyi deðiþtirmek UB deðil dedik ama
	burada ptr bir string literalini gösterdiði için bu yazýyý(string literalini) deðiþtirmek UB dir.
	Ayrýca "maya" yazýsý(yani str literali) programýn baþýndan sonuna kadar memoryde kalacak.

	String Literalleri bir istisna hariç / yukarýdaki hariç yani
	------------------------------------------------------------

	1 compile time da static olarak bakýlýnca türü char olan dizilerdir.

	2 bu dizilerin set amaçlý kullanýlmasý UB dir.

	3 bu diziler static ömürlü dizilerdir.

	-printf("UGUR");
		-| printf'in parametresi const char* idf biz burada char*'a string literalinin adresini yollayarak ekrana 
			'UGUR' yazdýrýyoruz. Yani string literalini bir parametre olarak kullanabiliriz. Ek olarak, bunu bir kere çaðýrmýþ olsakta
				UGUR string literali programýn sonuna kadar bellekte kalacak.
	-string literallerinin statik olmasýnýn bizi ilgilendiren bazý þeyleri var.
		-| Dinamik ömürlü adres deðiþkenlerinin tuttuklarý adresler return edilemez. Bu Undefined Behaviour fakat string literallarinin adresi
			döndürülebilir çünkü statik.
				char * get_month_name(int m)
					{
						switch(m)
							{
								case 1: return "ocak";
								case 2: return "subat";
								....
								....
								....
								case 12: return "aralik";
			
							}
						return "";
					}

					mesela yukarýdaki kodda UB yok.
					çünkü string literalleri static ömürlü.
	-String literallarinin statik olmasýnýn dezavantajlarýda var. Mesela diyelim ki, öyle bir sistemde çalýþýyoruz ki belleðimiz kýsýtlý. 
		Bu durumda sürekli string literali kullanamayýz çünkü bellekte program sonuna kadar yer kaplýyor.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MÜLAKAT SORUSU: Benzerlikler ve farklýlýklar

	int main(void){
		char str[] = "UGUR"; // Burada str adýnda bir dizi tanýmlýyorz ve buna ilk deðer veriyoruz.
								// Bulunduðu blok/fonksiyondan çýkýnca ömrü sona erer.
								//Burada tanýmlanan 1 varlýk var, str.
		char* p = "ERSOY"; // Burada ise "ERSOY" string literalinin adresini bir adres tutan deðiþken türüne cast ediyoruz.
							// string literali programýn sonuna kadar bellekte tutulur
							// Burada tanýmlanan 2 varlýk var, p ve "ERSOY"
	
	}

		
*/
#include <string.h>
#include <stdio.h>
int main(void) {
	char str[] = "ugur";
	char* p = "ersoy";
	strcpy(p, str); // UB

}
int main(void) {
	char* p1 = "Ugur Ersoy";
	char* p2 = "Ugur Ersoy";

	if (p1 == p2) 
		printf("Dogru");
	else
		printf("Yanlýþ");


}

char old_file_name[SIZE];
char new_file_name[SIZE];

printf("Dosya ismini girin \n");
sgets(old_file_name);

//tasklar aþaðýda þimdi.

// dosya ismini new file name e kopyala.
strcpy(new_file_name, old_file_name);
printf("(%s) ---> (%s)\n", old_file_name, new_file_name);

// dosyanýn uzantýsý yoksa uzantýsýný txt yap.
// dosya uzantýsý jpg ise dosya uzantýsýný gif olarak deðiþtirin
// Eðer dosyanýn uzantýsý .xls ise uzantýsý silinecek.
// diðer tüm durumlarda uzantýyý .dat yapýnýz.

char* p = strrchr(new_file_name, '.'); // son nokta önemli çünkü dosya adýnda da . olabilir.

if (!p)
strcat(new_file_name, ".txt");

else if (!strcmp(p, ".jpg"))
strcpy(p, ".gif");

else if (!strcmp(p, ".xls"))
*p = '\0';  // strcmp(p,"") te olurdu

else
strcpy(p, ".dat");

printf("(%s) ---> (%s)\n", old_file_name, new_file_name);
/*

	puts("Ayhan\n");->ayhan yazar ve newline býrakýr.
	puts("Ayhan\tnecati\thasan"); tab býrakýr.
	mesela

	"mustafa" yazdýrmak istiyorum
	puts("\"mustafa\"");

	baþa ve sona \ iþareti koymak istersek
	puts("\\ahmet\\");

	puts("\\\\\"jale\"\\\\\n");

	file path yazarkende
	(void)fopen("c:\\files\\file.txt", "r");

	const char p* = "\x42URS\x41"; -> ekrana yazdýrdýðýmýz zaman BURSA yazar. \x42 -> B , \x41 -> A
	const char p* = 
	0"" -> string literalleri aslýnda karakter sabitleriyle deðerini almýþ dizilerdir.
	"burak" -> b nin kod no su, u nun kod nosu .... þeklinde gidiyor.

	mesela

	"\x42URS\x41" -> "BURSA" demektir. x42 B nin kodudur.
	burada U hexadecimal bir char eðil.
	puts("\x42ebe") burada hexadecimal digit gördüðü sürece dahil ediyor ve hata alýnýr burada.
	too big for character hatasý alýnýr.
	puts("\101") -> burasý octal sayý sisteminde yazýlmýþ ve 3 karakter limiti var.hata oluþmuyor.
	puts("\10132") -> mesela 32 yi dahil etmedi çünkü 3 karakter limiti var.

	puts("\10132\10243") -> A32B43 yazar.

	Çift týrnak kullanmak için
	""ugur"" -> þeklinde yazarsak hata.  Týrnaklarý escape sequence olarak yazmalýyýz.
	"\"ugur\"" -> böyle olursa "ugur" yazýlýr

	Alttaki bu string literali yanlýþ çünkü bir alt satýra geçtiðinden dolayý literal bozuldu. Bunu böyle kullanmak için araçlar var.
	"UGUR ERSOY C DERSLERÝNE MART AYINDAN BERÝ KATILMIYOR VE
	KAYITLARDA ÇOK GERÝ"

	1- Ters bölü karakteri koymak. (makrolardaki gibi) // Ters slash kullanýldýðýnda aradaki boþluklarda sayýlýyor.
		"UGUR ERSOY \
xxxxxxxxxxxVE OYKU ERSOY" // x'leri boþluk olarak düþün :D string literali print edildiðinde normalde 1 karakter boþluk olsa bile
							// alt satýra geçtikten sonra alignment için koyulan boþluklarda yazýya dahil edilir.

	2-Whitespace ile ayrýlmýþ, aralarýnda baþka bir karakter bulunmayan string literalleri compile time'da birleþtirilir
		-| "UGUR" "ve" "OYKU" "ERSOY" -> bu birleþtirilecek ve "UGUR ve OYKU ERSOY" olacak.
		-| char* p = "UGUR"
				"ve"
				"OYKU"
				"ERSOY"; // bu da birleþtirilir çünkü aralarýnda sadece whitespace karakteri var.



	"" -> null string literal -> '\0'null karakter.

*/


/*
	ÖDEV
	char *strprepen(char *pdest,const char * psource)
	pdest in baþýna psource u ekliyor. bunu yaz. umut kotankiran -> kotankiran umut yazacak

	========================================================================
	========================================================================
	========================================================================

	Birde fonksiyonlarýn n li hali var.fonksiyon bildiriminde fazladan n parametresi var.

	strcpy için strncpy  -> source adresteki yazýnýn ilk n karakterini dest e kopyalar.
	strcat için strncat  -> source adresteki yazýnýn ilk n karakterini dest in sonuna ekler
	strcmp için strncmp  -> source adresteki yazýnýn ilk n karakterini dest ile kýyaslar.

*/