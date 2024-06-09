/*

	-Ba�ka bir idiyomatik yap� da yaz� tutan pointer�n string'in ilk eleman�n�n adresini de�ilde sondaki null karakterini g�stermesini sa�lamak.
		Bo� yaz�lara dikkat!
			char str2[] = '\0'; -> bu bir bo� yaz�d�r. null karakteri yaz�n�n uzunlu�una dahil de�ildir.
			char* str[] = "UGUR" -> str'ye ula�t���m�z zaman UGUR\0 yazan dizinin adresini tutuyor.
			char* p = str;
				while(*p)
					++p;
				printf("idx = %d", p - str);
		int main(void){
			char* str[] = "UGUR" -> str'ye ula�t���m�z zaman UGUR\0 yazan dizinin adresini tutuyor.
			char* p = str;
				while(*p)
					++p;
				printf("idx = %d", p - str);
			//////////////////// 2. y�ntem
			while(*p++)
				;
			--p; // burada 1 azalt�yoruz ��nk� *p++ yan etkiden dolay� null karakterden sonraki yere gidiyor onu geri almak i�in yap�yoruz bunu
				printf("idx = %d", p - str);
			//////////////////// veya standart k�t�phaneden fonksiyonlar kullanabiliriz
			p += strlen(str); // bu null karaktere kadar yaz�n�n uzunlu�u verir. E�er ben bu uzunlu�u adresle toplarsam null karakterinin oldu�u adrese gider.
			p = strchr(str, '\0'); // bu ise null karakterini yaz�da arar, null karakterinin adresini geri d�n�� de�er� olarak sunar.
		}
//////////////////////////////////////////////////////////
				null karakteri ve NULL pointer
�sim:				null karakter				null pointer
G�sterili�:			'\0'						NULL
T�r:				int							address	
De�er:				0							hi�bir nesnenin olmayacak bir adres
//////////////////////////////////////////////////////////
	�yle bir idiom var ki NULLPTR VE null karakteri ayn� yerde kullan�l�yor.

int main(void){
	char str[SIZE] = "UGUR";
	char* p = str;
		// p e�er bir yaz�y� g�steriyor ise ve
			// p'nin g�sterdi�i yaz� bo� yaz� de�il ise.
	if(p ! = NULL && *p != '\0'){ // burada short-circuit behaviour var.
									// e�er olmasayd�, p NULLptr oldu�unda ve operat�r�n�n sa� operand�nda *p
										// NULLPTR'� dereference etti�i i�in Undefined Behaviour olu�urdu.
	}
	// Yukar�daki if ifadesi daha da k�salt�labilir.
		// p != NULL sadece p olarak yaz�labilir. ��nk� e�er p NULLptr de�ilse non-zero olacak, NULLptr ise zero olacak.
		// *p ise '\0' null karakterinin de�eri 0 oldu�u i�in, *p'nin null karakteri olmas� durumunda zero, olmamas� durumunda non-zero de�er olacak.
	if(p && *p) // bu �ekilde yaz�labilir, mis gibi bir �rnek!0
}
------------------------------------------------------------
int main(void){
	char str[SIZE] = "UGUR";
	char* p = str;
		// p e�er bir yaz�y� g�stermiyor ise ve
			// p'nin g�sterdi�i yaz� bo� ise.
	if(p == NULL || *p == '\0')
	if(!p || !*p)
}
//////////////////////////////////////////////////////////

	
		strcpy(char* pdest, const char* psrc); 
			// Bu bir yaz�m konvensiyonu. E�er bir fonksiyon 2 parametre al�yor ve bu 2 parametreyi okuma-yazma i�in kullan�l�yorsa
				// �st�ne yaz�m/d�zenleme i�lemi yap�lacak olan parametre ilk, okuma i�lemi yapacak parametre ikinci olarak yaz�l�r. 
			// size i�in bir parametresi yok. ��nk� ta�ma/ta��rma fonksiyonu �a��ran ki�inin dikkat etmesi gerek. E�er dizi ta�arsa
				// undefined behaviour olu�ur.
	-Tipik olarak e�er bir fonksiyon 
		a)bir adrese bir yaz� yerle�tiriyor ise
			b)bir adresteki yaz�y� de�i�tiriyor ise
				fonksiyonun geri d�n�� de�eri adres yap�l�r ve fonksiyonun de�i�tirdi�i yaz�n�n adresi d�nd�r�l�r.
char*(char* pdest, const char* psrc){ // null karakterini de kopyal�yor.
	char* ptemp = pdest;

}



*/


char* my_strcpy(char* pdest, const char* psource)
{
	char* ptemp = pdest; // hedefin adresini geri d�nd�rece�imiz i�in ptemp de�i�keninde adresi tutuyoruz.
								// ��nk� while i�erisindeki ifade'de pdest'in adresi de�i�ecek.
	while (*pdest++ = *psource++) // Burada kaynaktan hedefe do�ru kopyalama yap�l�r. Kaynaktan null karakter geldi�inde ve
		;						//atama operat�r� ile zero de�er pdest'e atan�r ve ifade zero olaca�� i�in
										// d�ng�den ��k�l�r ve hedef de�i�kenin adresi d�nd�r�l�r.
	return ptemp;
}

char* my_strcpy2(char* pdest, const char* psource)
{
	char* ptemp = pdest;
	while (*psource) {
		*pdest++ = *psource++;
	}
	*pdest = '\0'; // burada null karakteri ekliyoruz bunun sebebi sequence point. *psource++ null karakteri geldi�inde d�ng�den
	return ptemp;		// ��kmas�na sebep olaca��ndan dolay� null karakterini eklemeyecek. Bizde manuel olarak ekliyoruz
}

/* strcpy �nemli
	int main(void){
							 | // burada s harfinden itibaren gulseren yazd�rmak istiyorum. -> gulgulseren �eklinde olacak
		char str[SIZE] = "gulseren";
		strcpy(str + 3, str); // -> Undefined Behaviour -> Overlapped Block diye bir olaydan dolay�.
			// Overlap Block anlad���m kadar�yla bellek bloklar�n�n ortak kulland�klar� yer. Mesela gulseren bir blok seren de bir blok ve
				// aralar�ndaki ortak blok ise seren. Std k�t�phane fonksiyonlar� overlap blocklar�n kullan�lmas� durumunda ortaya ��kacak
					// durumlar� d�k�mante eder. E�er bir blokta okuma yaparken ayn� blo�u yazma i�in kullan�rsak bu strcpy() i�in 
						//undefined behaviourdur.
		strcpy(str + 3, str); // -> source arrayden kopyalarken de�i�ti�i i�in bunlar �ak���yor ve bu UB olu�turuyor.
		// Kayd�rma i�lemlerini bu t�r fonksiyonlarla yapmamak gerekiyor. �leri de g�rece�imiz memmove kullan�labilir. Kursun sonlar�na do�ru anlat�lacak.
		// Restrict pointer: restrict pointerin g�sterdi�i nesne bu pointer taraf�ndan g�sterilen tek nesne olmak zorunda. 
			//char* strcpy(char* restrict pdest, const char* restrict psrc); ->E�er burada psrc ve pdest ayn� nesneyi i�aret eder ise bu
				// hata olur. restrict bizden o adresin tek bir pointee taraf�dan g�sterildi�inin garantisini istiyor.
					// bunu kullanarak overlapped block probleminin �n�ne ge�mi� oluruz ��nk� strcpy kullan�lamaz :D

		
	}
//////////////////////////////////////////////               

	char* strcat(char* p1, const char* p2); // cat ==> concatante(birle�tirmek)
			bir yaz�n�n sonuna ba�ka bir yaz� ekler.concat ediyor.ya da birle�tiriyor.
 
		
	
*/

char* my_strcat(char* p1, const char* p2)
{
	char* ptemp = p1;

	while (*p1) // burada 
		++p1; // burada kopyalama i�lemi yap�lacak yaz�n�n null karakterini bulduk. Ve null karakteri dahil olmak �zere birle�tirmeye ba�layaca��z.

	while (*p1++ = *p2++) // null karakterinin oldu�u indexten itibaren yaz� yap��t�rma i�ia yap�l�yor.
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

	strcpy(s1, s3); // bunda bir s�k�nt� yok, burada UGUR s1'e kopyalan�r ve sonunda null karakteri de olur.
	strcat(s2, s3); // burada s�k�nt� var ��nk� strcat null karakterinden ba�layark yaz�yor. s2 dizisi initialize edilmedi�i i�in
						// dizinin i�erisindeki de�erler garbage value. Bundan dolay� '\0' null karakterini bulamaz.
							// bu durumun �n�ne ge�mek i�in s1 ve s2'yi 0 init edebiliriz. Veya statik olarak tan�mlayabiliriz
	/*
	* char s1[SIZE] = { 0 };
	* char s2[SIZE] = { 0 };
	---------------------------
	* static char s1[SIZE];
	* static char s2[SIZE];
	---------------------------
	* char s1[SIZE] = "";
	* char s2[SIZE] = "";
			Bu �ekilde tan�mlarsak s�k�nt�s�z �al���r yukar�daki kod. 
				Bu �ok s�k yap�lan bir hataym��. Bu fonksiyonlar� kullan�rken kullan�lan adreste NTBS OLMAK ZORUNDA.
	*/
	//E�er dizilerde ilk de�er atamas� bildirim yap�l�rken yap�lmaz ise dizinin tuttu�u k�sma null karakteri eklenmez.
	char arr[SIZE];
	arr[1] = "U";
	arr[2] = "G"; // arr[3] veya arr[SIZE]da null karakteri yok. Bundan dolay� strcat kullan�m� s�k�nt�l�.
	printf("%s\n", s1);
	printf("%s", s2);
}
//////////////////////////////////////////////////////////////////////////////////////////////////

/*
														YAZILARIN KAR�ILA�TIRILMASI
	
	int main(void)
	{
		char s1[SIZE] = "UGUR";
		char s2[SIZE] = "UGUR";

		if(s1==s2) // burada dizideki karkatelre de�il adresler kar��la�t�r�l�yor o y�zden yanl�� olacak.
			printf("DOGRU");
		else
			printf("YANLIS");
	}

	strcmp(const char* p1, const char* p2);
	strcmp return de�erlerinin anlamlar�:
		>0 ise birinci yaz� b�y�k
		<0 ise ikinci yaz� b�y�k
		== 0 ise ikiside e�it
	if(strcmp(s1, s2) == 0) // yaz�lar�n ikisi de e�it ise
	if(!strcmp(s1, s2)) // yaz�lar�n ikisi de e�it ise

	if(strcmp(s1, s2) != 0) // yaz�lar�n ikisi de e�it de�il ise
	if(strcmp(s1, s2)) // yaz�lar�n ikisi de e�it de�il ise

	if(strcmp(s1, s2) < 0) s2 > s1
	if(strcmp(s1, s2) > 0) s1 > s2
	container: dizi bir containerdir. Bunu ileride g�recekmi�iz bir �ey anlamad�m .d
	lexicographical compare: �ki dizi birbirine e�it olmas� i�in, konteyn�rlardaki ��e say�s�n�n birbirine e�it ve kar��l�kl�
		��elerin birbirine e�it olmas� gerekiyor.	
	2, 4, 6, 8, 10
					// bu iki dizi birbirine e�it.
	2, 4, 6, 8, 10

	1, 2, 3, 4,
	3, 5, // 2. dizi birinci diziden daha b�y�k. Dizinin boyutu bir k�stas de�il. Lexicographical compare kar��la�t�r�rken de�er de�i�mesi durumunda
		o an ki kar��la�t�rmadaki en b�y�k say�ya sahip olan diziyi en b�y�k dizi yap�yor.
	1 3 7 40  bu dizi daha b�y�k
	1 3 7

	1 5 7 9
	1 6		Bu daha b�y�k


	1 200 300 400 600 700
	2	bu daha b�y�k.
	
	ali ata bak
	veli		bu daha b�y�k.Asci deki yerine g�re

	masa	 // k���k harflerin ASCII de�erleri daha b�y�k. masa MASA'dan daha b�y�k
	MASA


	*/