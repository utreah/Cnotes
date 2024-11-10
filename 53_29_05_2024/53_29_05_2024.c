/*
	CPP'de classlar i�in protected, public, private gibi keywordler var. Bunlar baz� kodlar�/de�i�kenleri client codetan saklamak
		i�in kullan�l�yor. Ki�i d��ar�dan o kodlara m�dahalede vs bulunamas�n diye.

	C'de b�yle bir yap� yok o y�zden iki y�ntem var.
		1- struct'� tamamen client'�n kullan�m�na g�r�n�m�ne kapat�yoruz
		2- Client ile struct'a dokunmamas� ad�na anla��yoruz. Onlarda struct'� kullanmak i�in fonksiyonlar� vs kullan�yorlar. Direkt eri�im yok

	�imdi o mod�lleri nas�l olu�turabiliriz? Bug�n bol bol kod olu�turacaz


	Date ad�nda bir t�r olu�turucaz. Bu t�r
		13 May�s 1232 gibi tarihleri tutacak. 
	Bunun i�in 2 adet dosya olu�turduk. Date.c ve Date.h
int main(void) {
	return 0;
}
*/

//////////////////////////////////////////////////// Buradan sonraki k�s�m yeni bir konu, �st� Date.h Date.c ile alakal� kendi mod�l�m�z� olu�turduk.
/*											 Bir yap�n�n eleman�n�n yap� t�r�nden olmas� 
	Bir struct'�n eleman� ba�ka bir struct t�rden nesne olabilir.
	Yap�n�n eleman�, ba�ka bir yap� t�r�nden pointerda olabilir
		Bu eleman�n dereference edilebilmesi i�in hayat� devam eden, ge�erli bir pointer nesnesi olmal�.

	Bir yap� t�r�n�n eleman� kendi t�r�nden olamaz.
struct Eng {
	int x, y, z;
	// struct Eng ex; -> Bir yap� t�r�n�n eleman� kendi t�r�nden olamaz sentaks hatas�
};

struct Ken {
	struct Eng n;
	struct Eng* ptr;
};

int main(void) {
	struct Ken e;
	// e.n.x;  // e. ile Ken yap�s�ndaki n'ye eri�iyoruz daha sonra da Eng yap�s�ndaki x eleman�na
	e.ptr->x; // ptr bir pointer oldu�u i�in elemanlar�na ok ile eri�iyoruz.
	struct Ken* kenPtr;
	//.. code
	kenPtr->ptr->x; // Mant�k ayn�. kenPtr bir pointer ve elemanlar�na -> ile eri�iyoruz. ptr nesnesi de pointer onunn da elemanlar�na -> ile eri�iyoruz
}
*/

													/*				Complete types - Incomplete types					*/
/*
	Derleyici taraf�ndan compile time'da complete ya da incomplete olarak niteleniyor.

	Incomplete Types: Derleyici bir t�r�n varl���ndan haberdar fakat tan�m�n� g�rmediyse -> Incomplete types

*/

struct Nec; // Derleyici bunu g�r�yor, fakat struct Nec'in tan�m� yok. Burada sadece bildirimi yap�lm�� i�te buna incomplete type deniyor

struct Eng; // derleyici tan�m� g�r�yor hem de alt�nda bildirimini g�r�yor bu da complete type
struct Eng {
	int x, y;
};

// Ne i�e yarad���n� sonraki derste.