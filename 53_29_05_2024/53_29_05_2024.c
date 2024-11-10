/*
	CPP'de classlar için protected, public, private gibi keywordler var. Bunlar bazý kodlarý/deðiþkenleri client codetan saklamak
		için kullanýlýyor. Kiþi dýþarýdan o kodlara müdahalede vs bulunamasýn diye.

	C'de böyle bir yapý yok o yüzden iki yöntem var.
		1- struct'ý tamamen client'ýn kullanýmýna görünümüne kapatýyoruz
		2- Client ile struct'a dokunmamasý adýna anlaþýyoruz. Onlarda struct'ý kullanmak için fonksiyonlarý vs kullanýyorlar. Direkt eriþim yok

	Þimdi o modülleri nasýl oluþturabiliriz? Bugün bol bol kod oluþturacaz


	Date adýnda bir tür oluþturucaz. Bu tür
		13 Mayýs 1232 gibi tarihleri tutacak. 
	Bunun için 2 adet dosya oluþturduk. Date.c ve Date.h
int main(void) {
	return 0;
}
*/

//////////////////////////////////////////////////// Buradan sonraki kýsým yeni bir konu, üstü Date.h Date.c ile alakalý kendi modülümüzü oluþturduk.
/*											 Bir yapýnýn elemanýnýn yapý türünden olmasý 
	Bir struct'ýn elemaný baþka bir struct türden nesne olabilir.
	Yapýnýn elemaný, baþka bir yapý türünden pointerda olabilir
		Bu elemanýn dereference edilebilmesi için hayatý devam eden, geçerli bir pointer nesnesi olmalý.

	Bir yapý türünün elemaný kendi türünden olamaz.
struct Eng {
	int x, y, z;
	// struct Eng ex; -> Bir yapý türünün elemaný kendi türünden olamaz sentaks hatasý
};

struct Ken {
	struct Eng n;
	struct Eng* ptr;
};

int main(void) {
	struct Ken e;
	// e.n.x;  // e. ile Ken yapýsýndaki n'ye eriþiyoruz daha sonra da Eng yapýsýndaki x elemanýna
	e.ptr->x; // ptr bir pointer olduðu için elemanlarýna ok ile eriþiyoruz.
	struct Ken* kenPtr;
	//.. code
	kenPtr->ptr->x; // Mantýk ayný. kenPtr bir pointer ve elemanlarýna -> ile eriþiyoruz. ptr nesnesi de pointer onunn da elemanlarýna -> ile eriþiyoruz
}
*/

													/*				Complete types - Incomplete types					*/
/*
	Derleyici tarafýndan compile time'da complete ya da incomplete olarak niteleniyor.

	Incomplete Types: Derleyici bir türün varlýðýndan haberdar fakat tanýmýný görmediyse -> Incomplete types

*/

struct Nec; // Derleyici bunu görüyor, fakat struct Nec'in tanýmý yok. Burada sadece bildirimi yapýlmýþ iþte buna incomplete type deniyor

struct Eng; // derleyici tanýmý görüyor hem de altýnda bildirimini görüyor bu da complete type
struct Eng {
	int x, y;
};

// Ne iþe yaradýðýný sonraki derste.