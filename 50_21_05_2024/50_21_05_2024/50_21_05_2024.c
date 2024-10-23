/*Storage Specifiers*/

/*
	Volatile(oynak (balina)): Bu keyword ile bir point deðiþkeni nitelenebiliyor. Bu keyword ile nitelenen nesnelerin program dýþý kaynaklar tarafýndan müdahaleler ile deðiþtiribileceðinin
		bilgisi kodu okuyan kiþiye ve derleyiciye veriliyor. Dýþ güçlerin maþasý haline geliyor yani.
	Niye bunu kullanýyoruz?
		Sebebi compiler'ýn compile timeda üreteceði kodun doðru olmasýný saðlamak. Eðer, derleyici nesnenin deðerinin deðiþmediðini koda bakarak görürse
			o nesnenin bellekten deðerini okumak için kod üretmemesi durumu var. Diyelim ki ival adlý bir deðiþkenimiz var. Bu deðiþkeni oluþturduk ama projenin hiçbir yerinde
				deðerini deðiþtirmedik. Derleyici bunu gördüðünde optimizasyon için ival'in bellekten deðerini okumak için bir kod üretmeyecek. 

	volatile int x = 1000; // global namespace
	int main(void){
		while(x != 0){ // eðer x, volatile keywordü ile define edilmese idi derleyici bu while deyimini while(1) olarak kabul edebilirdi. Çünkü x'in deðerinin deðiþtiði bir ihtimal yoktu.
			//.. code		// volatile kullanarak, dýþarýdan müdahale olabileceði bilgisini veriyoruz.
		}
	}


	int x = 10;
	int main(void){
		volatile int* p = &x; // pointer to volatile int 
		*p; // volatile olan bu. 'p;' deðil  // *p volatile olduðu için pointer'ýn gösterdiði nesnenin deðerini her seferinde bellekten gidip get etmesi anlamýna geliyor.
		int* volatile p = &x; // volatile pointer to int // p'nin deðerini her çaðýrdýðýmda bellekten get edeceksin demek bu.
	}

	NOT: Eðer volatile asterisk(*) atomunun solunda ise, *p yani Type(int mesela) volatile olur ve deðeri bellekten get edilir.
		 Eðer volatile asterisk(*) atomunun saðýnda ise, p yani gösterdiði adres ne ise bellekten o deðer get edilir. 
			Bellekten get edilme durumu da, o nesneye her eriþim yapýldýðýnda belleðe gidip deðerini sorma durumu. Optimizasyon olmadýðý için böyle.
---------------------------------------------------
	volatile const int x = 10; // burada ise x nesnesinin bu proje/kod içerisinde deðiþtirilemeyeceði anlamýna geliyor. 
									//volatile ise dýþarýdan deðiþtirilebileceðini söylüyor. Projenin herhangi bir yerinde eriþim saðlandýðýnda x'in deðeri  bellekten her seferinde get edilecek.

---------------------------------------------------
int x = 10;
int main(void){
	int* ptr = &x;
	volatile int* p = ptr; // burada dönüþüm de sýkýntý yok.
	/////////
	volatile int* volptr = &x;
	int* ptr2 = volptr; // burada örtülü dönüþüm yok uyarý mesajý verecek derleyici.
		const int* -> int* dönüþümü nasýl yanlýþsa volatile int* -> int* dönüþümü de yanlýþ.


}
---------------------------------------------------
restrict (C99): restrict keywordü ile nitelenmiþ pointer deðiþkenlerinin unique olmasýný saðlýyor. Yani baþka bir pointer nesnesi, restrict ile tanýmlanmýþ bir pointer deðiþkeninin
	gösterdiði adresi göstermeyeceðinin garantisini veriyor. Bu garantinin çiðnenmesi ile Undefined Behaviour oluþur.

	Volatile, const gibi keywordlar hem pointer'ý hem de gösterdiði nesneyi nitelerken restrict keywordü sadece pointerin kendisini niteliyor.
	
	restrict keywordü ile tanýmlanan pointerlara restrict pointer deniyor.
		En çok karþýmýza çýkacaðý yer fonksiyonlarýn parametre deðiþkenleri.
	restrict, asterisk atomundan sonra kullanýlmak zorunda eðer önce kullanýlýrsa sentaks hatasý.

	void func(int* restrict p); // p bir restrict pointer
	int* restrict x = &var;

	int restrict *ptr; // sentaks hatasý
	Pointerlarýn her ikisininde ayný nesneye eriþmesine pointer-alliasing denir.
	void func(int* px, int* py, int* restrict pz)
	{
	}

	burada px ve py nin pz nin gösterdiði nesneyi gösterme ihtimali yok.bunu saðlýyor.
		bu derleyicinin daha iyi optimizasyon yapmasýný saðlýyor.
	eðer px = pz; yapýlýrsa bu bir UNDEFINED BAHAVIOR	

	ÖR:
	void func(int* px, int* py, int* restrict pz)
	{
		*px += *pz;

		// *pz ye eriþ ve onu registerda tut
		// *pz ye tekrar eriþmek yerine onu registerdaki deðeri ile kullan.
		//restrict olmasaydý px, pz yi gösteriyor olabilirdi ve *px deðiþince *pz de deðiþirdi.
		// bu deðeride get etmek için tekrar memory ye eriþmek gerekirdi. restrict ile bunu
		// ortadan kaldýrýyoruz. sadece pz bu deðeri tutabilir ve eriþebilir.
		//bu þekilde compiler optimizasyon yapýyor.

		*py += *pz;

	}
	CPPREFERENCE SERGEY ZUBKOV un örneði

	void f(int n, int * restrict p, const int * restrict q)
	{
		while(n-- > 0)
			*p++ = *q++; // none of the objects modified through *p is the same
						 // as any of the objects read through *q
						 // compiler free to optimize, vectorize, page map, etc.
	}
	void g(void)
	{
		extern int d[100];
		f(50, d + 50, d); // OK. Kesiþmiyor.birincisi d[49] da bitiyor ikinci dizi ise d[50] den baþlýyor.
							// overlapped blocklar yok.UB DEÐÝL.

		f(50, d + 1, d); // Undefined behavior: d[1] is accessed through both p and q in f
							//d[1] de kesiþiyorlar. UNDEFINED BEHAVIOR.
	}
	56:00
*/