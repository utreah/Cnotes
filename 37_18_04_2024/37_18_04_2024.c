/*

	-Baþka bir idiyomatik yapý da yazý tutan pointerýn string'in ilk elemanýnýn adresini deðilde sondaki null karakterini göstermesini saðlamak.
		Boþ yazýlara dikkat!
			char str2[] = '\0'; -> bu bir boþ yazýdýr. null karakteri yazýnýn uzunluðuna dahil deðildir.
			char* str[] = "UGUR" -> str'ye ulaþtýðýmýz zaman UGUR\0 yazan dizinin adresini tutuyor.
			char* p = str;
				while(*p)
					++p;
				printf("idx = %d", p - str);
		int main(void){
			char* str[] = "UGUR" -> str'ye ulaþtýðýmýz zaman UGUR\0 yazan dizinin adresini tutuyor.
			char* p = str;
				while(*p)
					++p;
				printf("idx = %d", p - str);
			//////////////////// 2. yöntem
			while(*p++)
				;
			--p; // burada 1 azaltýyoruz çünkü *p++ yan etkiden dolayý null karakterden sonraki yere gidiyor onu geri almak için yapýyoruz bunu
				printf("idx = %d", p - str);
			//////////////////// veya standart kütüphaneden fonksiyonlar kullanabiliriz
			p += strlen(str); // bu null karaktere kadar yazýnýn uzunluðu verir. Eðer ben bu uzunluðu adresle toplarsam null karakterinin olduðu adrese gider.
			p = strchr(str, '\0'); // bu ise null karakterini yazýda arar, null karakterinin adresini geri dönüþ deðerý olarak sunar.
		}
//////////////////////////////////////////////////////////
				null karakteri ve NULL pointer
Ýsim:				null karakter				null pointer
Gösteriliþ:			'\0'						NULL
Tür:				int							address	
Deðer:				0							hiçbir nesnenin olmayacak bir adres
//////////////////////////////////////////////////////////
	Öyle bir idiom var ki NULLPTR VE null karakteri ayný yerde kullanýlýyor.

int main(void){
	char str[SIZE] = "UGUR";
	char* p = str;
		// p eðer bir yazýyý gösteriyor ise ve
			// p'nin gösterdiði yazý boþ yazý deðil ise.
	if(p ! = NULL && *p != '\0'){ // burada short-circuit behaviour var.
									// eðer olmasaydý, p NULLptr olduðunda ve operatörünün sað operandýnda *p
										// NULLPTR'ý dereference ettiði için Undefined Behaviour oluþurdu.
	}
	// Yukarýdaki if ifadesi daha da kýsaltýlabilir.
		// p != NULL sadece p olarak yazýlabilir. Çünkü eðer p NULLptr deðilse non-zero olacak, NULLptr ise zero olacak.
		// *p ise '\0' null karakterinin deðeri 0 olduðu için, *p'nin null karakteri olmasý durumunda zero, olmamasý durumunda non-zero deðer olacak.
	if(p && *p) // bu þekilde yazýlabilir, mis gibi bir örnek!0
}
------------------------------------------------------------
int main(void){
	char str[SIZE] = "UGUR";
	char* p = str;
		// p eðer bir yazýyý göstermiyor ise ve
			// p'nin gösterdiði yazý boþ ise.
	if(p == NULL || *p == '\0')
	if(!p || !*p)
}
//////////////////////////////////////////////////////////

	
		strcpy(char* pdest, const char* psrc); 
			// Bu bir yazým konvensiyonu. Eðer bir fonksiyon 2 parametre alýyor ve bu 2 parametreyi okuma-yazma için kullanýlýyorsa
				// üstüne yazým/düzenleme iþlemi yapýlacak olan parametre ilk, okuma iþlemi yapacak parametre ikinci olarak yazýlýr. 
			// size için bir parametresi yok. Çünkü taþma/taþýrma fonksiyonu çaðýran kiþinin dikkat etmesi gerek. Eðer dizi taþarsa
				// undefined behaviour oluþur.
	-Tipik olarak eðer bir fonksiyon 
		a)bir adrese bir yazý yerleþtiriyor ise
			b)bir adresteki yazýyý deðiþtiriyor ise
				fonksiyonun geri dönüþ deðeri adres yapýlýr ve fonksiyonun deðiþtirdiði yazýnýn adresi döndürülür.
char*(char* pdest, const char* psrc){ // null karakterini de kopyalýyor.
	char* ptemp = pdest;

}



*/


char* my_strcpy(char* pdest, const char* psource)
{
	char* ptemp = pdest; // hedefin adresini geri döndüreceðimiz için ptemp deðiþkeninde adresi tutuyoruz.
								// çünkü while içerisindeki ifade'de pdest'in adresi deðiþecek.
	while (*pdest++ = *psource++) // Burada kaynaktan hedefe doðru kopyalama yapýlýr. Kaynaktan null karakter geldiðinde ve
		;						//atama operatörü ile zero deðer pdest'e atanýr ve ifade zero olacaðý için
										// döngüden çýkýlýr ve hedef deðiþkenin adresi döndürülür.
	return ptemp;
}

char* my_strcpy2(char* pdest, const char* psource)
{
	char* ptemp = pdest;
	while (*psource) {
		*pdest++ = *psource++;
	}
	*pdest = '\0'; // burada null karakteri ekliyoruz bunun sebebi sequence point. *psource++ null karakteri geldiðinde döngüden
	return ptemp;		// çýkmasýna sebep olacaðýndan dolayý null karakterini eklemeyecek. Bizde manuel olarak ekliyoruz
}

/* strcpy önemli
	int main(void){
							 | // burada s harfinden itibaren gulseren yazdýrmak istiyorum. -> gulgulseren þeklinde olacak
		char str[SIZE] = "gulseren";
		strcpy(str + 3, str); // -> Undefined Behaviour -> Overlapped Block diye bir olaydan dolayý.
			// Overlap Block anladýðým kadarýyla bellek bloklarýnýn ortak kullandýklarý yer. Mesela gulseren bir blok seren de bir blok ve
				// aralarýndaki ortak blok ise seren. Std kütüphane fonksiyonlarý overlap blocklarýn kullanýlmasý durumunda ortaya çýkacak
					// durumlarý dökümante eder. Eðer bir blokta okuma yaparken ayný bloðu yazma için kullanýrsak bu strcpy() için 
						//undefined behaviourdur.
		strcpy(str + 3, str); // -> source arrayden kopyalarken deðiþtiði için bunlar çakýþýyor ve bu UB oluþturuyor.
		// Kaydýrma iþlemlerini bu tür fonksiyonlarla yapmamak gerekiyor. Ýleri de göreceðimiz memmove kullanýlabilir. Kursun sonlarýna doðru anlatýlacak.
		// Restrict pointer: restrict pointerin gösterdiði nesne bu pointer tarafýndan gösterilen tek nesne olmak zorunda. 
			//char* strcpy(char* restrict pdest, const char* restrict psrc); ->Eðer burada psrc ve pdest ayný nesneyi iþaret eder ise bu
				// hata olur. restrict bizden o adresin tek bir pointee tarafýdan gösterildiðinin garantisini istiyor.
					// bunu kullanarak overlapped block probleminin önüne geçmiþ oluruz çünkü strcpy kullanýlamaz :D

		
	}
//////////////////////////////////////////////               

	char* strcat(char* p1, const char* p2); // cat ==> concatante(birleþtirmek)
			bir yazýnýn sonuna baþka bir yazý ekler.concat ediyor.ya da birleþtiriyor.
 
		
	
*/

char* my_strcat(char* p1, const char* p2)
{
	char* ptemp = p1;

	while (*p1) // burada 
		++p1; // burada kopyalama iþlemi yapýlacak yazýnýn null karakterini bulduk. Ve null karakteri dahil olmak üzere birleþtirmeye baþlayacaðýz.

	while (*p1++ = *p2++) // null karakterinin olduðu indexten itibaren yazý yapýþtýrma iþia yapýlýyor.
		;

	return ptemp;	
}

char* mystrcat(char* p1, const char* p2)
{
	strcpy(p1 + strlen(p1), p2);
	return p1;
}

char* mystr_cat(char* p1, const char* p2) {

	strcpy(strchr(p1, '\0'), p2);
	return p1;
}
#define SIZE 100
#include <stdio.h>
#include <string.h>
int main(void)
{
	char s1[SIZE];
	char s2[SIZE];
	char s3[SIZE] = "UGUR";

	strcpy(s1, s3); // bunda bir sýkýntý yok, burada UGUR s1'e kopyalanýr ve sonunda null karakteri de olur.
	strcat(s2, s3); // burada sýkýntý var çünkü strcat null karakterinden baþlayark yazýyor. s2 dizisi initialize edilmediði için
						// dizinin içerisindeki deðerler garbage value. Bundan dolayý '\0' null karakterini bulamaz.
							// bu durumun önüne geçmek için s1 ve s2'yi 0 init edebiliriz. Veya statik olarak tanýmlayabiliriz
	/*
	* char s1[SIZE] = { 0 };
	* char s2[SIZE] = { 0 };
	---------------------------
	* static char s1[SIZE];
	* static char s2[SIZE];
	---------------------------
	* char s1[SIZE] = "";
	* char s2[SIZE] = "";
			Bu þekilde tanýmlarsak sýkýntýsýz çalýþýr yukarýdaki kod. 
				Bu çok sýk yapýlan bir hataymýþ. Bu fonksiyonlarý kullanýrken kullanýlan adreste NTBS OLMAK ZORUNDA.
	*/
	//Eðer dizilerde ilk deðer atamasý bildirim yapýlýrken yapýlmaz ise dizinin tuttuðu kýsma null karakteri eklenmez.
	char arr[SIZE];
	arr[1] = "U";
	arr[2] = "G"; // arr[3] veya arr[SIZE]da null karakteri yok. Bundan dolayý strcat kullanýmý sýkýntýlý.
	printf("%s\n", s1);
	printf("%s", s2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
														YAZILARIN KARÞILAÞTIRILMASI
	
	int main(void)
	{
		char s1[SIZE] = "UGUR";
		char s2[SIZE] = "UGUR";

		if(s1==s2) // burada dizideki karkatelre deðil adresler karþýlaþtýrýlýyor o yüzden yanlýþ olacak.
			printf("DOGRU");
		else
			printf("YANLIS");
	}

	strcmp(const char* p1, const char* p2);
	strcmp return deðerlerinin anlamlarý:
		>0 ise birinci yazý büyük
		<0 ise ikinci yazý büyük
		== 0 ise ikiside eþit
	if(strcmp(s1, s2) == 0) // yazýlarýn ikisi de eþit ise
	if(!strcmp(s1, s2)) // yazýlarýn ikisi de eþit ise

	if(strcmp(s1, s2) != 0) // yazýlarýn ikisi de eþit deðil ise
	if(strcmp(s1, s2)) // yazýlarýn ikisi de eþit deðil ise

	if(strcmp(s1, s2) < 0) s2 > s1
	if(strcmp(s1, s2) > 0) s1 > s2
	container: dizi bir containerdir. Bunu ileride görecekmiþiz bir þey anlamadým .d
	lexicographical compare: Ýki dizi birbirine eþit olmasý için, konteynýrlardaki öðe sayýsýnýn birbirine eþit ve karþýlýklý
		öðelerin birbirine eþit olmasý gerekiyor.	
	2, 4, 6, 8, 10
					// bu iki dizi birbirine eþit.
	2, 4, 6, 8, 10

	1, 2, 3, 4,
	3, 5, // 2. dizi birinci diziden daha büyük. Dizinin boyutu bir kýstas deðil. Lexicographical compare karþýlaþtýrýrken deðer deðiþmesi durumunda
		o an ki karþýlaþtýrmadaki en büyük sayýya sahip olan diziyi en büyük dizi yapýyor.
	1 3 7 40  bu dizi daha büyük
	1 3 7

	1 5 7 9
	1 6		Bu daha büyük


	1 200 300 400 600 700
	2	bu daha büyük.
	
	ali ata bak
	veli		bu daha büyük.Asci deki yerine göre

	masa	 // küçük harflerin ASCII deðerleri daha büyük. masa MASA'dan daha büyük
	MASA


	*/