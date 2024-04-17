Fonksiyona baþka bir fonksiyon gönderilebiliyor.
Ve bu mekanizmaya "callback" deniyor.Pointerlarla alakalý. (Function pointer);

int get_random_char(int (*fp)(int)) -> // *fp burada fonksiyonun adresini alýyor ve bu sayede argüman olarak kullanmamýzý saðlýyor.
/*
--------------------------------------------------------------DÝZÝLER(ARRAYS)---------------------------------------------------------------
																																							*/


	Data Structure(s)->veri yapýlarý
	Verileri iþlemek için verileri bellekte tutmamýz gerekiyor.Ör: öðrencilerin okulda sýnavlardan aldýklarý notlar, günlerin ortalama sýcaklýk deðerleri gibi.
	Neden bir arada tutuyoruz ?
	Verilerinn üstünde bir takým iþlemler yapabilmek için, verileri bellekte tutuyoruz.
	Gerçekleþtirdiðimiz iþlemlere de algoritma denir.

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	Her bir deðer birbirinin peþi sýra(continous) þeklinde yerleþtirilmiþse buna "DYNAMIC ARRAY " deniyor.
	- Linked List
	Singly Linked List
	Double Linked List
	- Trees
	binary search tree
	red - black
	- Graph
	- Hashtable
	gibi veri yapýlarý vardýr.

	Bellekte bir þekilde tutulan verileri mantýksal þeklinde kullanmak için oluþturulmuþ düzeneklere "DATA STRUCTURES" deniyor.
	Neden bu kadar fazla veri yapýsý var ?
	-Kullanýlan veriye göre, yapýlan iþlemin maliyeti artýp ya da azalabiliyor.

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Algorithm Complexity
	Memory Complexity : Kullanýlan bellek alaný.
	Computational Complexity : Ýþi gerçekleþtirmek için yapýlan iþlem sayýsý.

	Constant - Time Algorithms : Öðe sayýsý artýyor olsa da maliyet her zaman ayný.
	Linear Complexity : Veri yapýsýndaki öðe sayýsý arttýkça, yapýlan iþlem miktarýda doðrusal olarak artýyor.

	Big O notation O() :
	Ýyiden->kötüye(farklý complexitylerde var daha iyi daha kötü)
	0(1)->constant time algorithm
	O(logn) ->
	O(n)->Linear complexity
	O(nlogn) ->
	O(n ^ 2)->Quadratic

	n elemanlý bir dizinin algoritma karmaþýklýðý O(n)'dir.'

	Binary Search Algorithm : Küçükten - büyüðe(veya tam tersi) sýralanmýþ bir dizide ortadaki deðer seçilir ve 3 durum oluþur;
1 - Seçtiðim deðer aradýðým deðer
2 - Seçtiðim deðer aradýðým deðerden büyük
3 - Seçtiðim deðer aradýðým deðerden küçük.
Bu iþlem istenilen sonuca ulaþýlýna kadar tekrarlanýr.Her seferinde ortadaki deðer seçilir ve gereksiz olan kýsým kullanýlmaz.
Duruma göre ihtiyacýmýzýn olmadýðý kýsým atýlýr ve kullanýlmaz.Bu sayede algoritma karmaþýklýðý O(logn)'e' kadar düþer.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Algoritmanýn karýþýklýðý veri yapýsýndaki niteliklere baðlý olabiliyor.
1 - Best Case
2 - Worst Case
3 - Average
Aksi söylenmedikçe average case kabul edilir.

Veri yapýlarýnýn önemli kýsmý dilin standart kütüphanesinde hazýr olarak geliyor.

Runtimeda dynamic array ile veri ekleyip silebiliyoruz.
Dynamic array üretimde en çok kullanýlan data type.Ve en önce öðrenilmesi gerekilen bir veri türü.

Fixed array ise eleman sayýsý programýn çalýþma zamanýnda asla ve asla deðiþmez.Ekleme ve silme iþlemi asla yapýlamaz.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

C ve CPP dizilerin sentakslarý % 85 ayný.
Bir dizi n tane deðiþkenin bir yerde tutulduðu bir yapýdýr.

Dizinin sentaksý -> int a[int_const_expr]; 
int_const_expr = size of array(dizinin  boyutu)
OLUR - OLMAZ;
int x = 10;
int a[]; ->olmaz çünkü braketlerin arasýnda bir constant olmalý.sentaks hatasý
int a[x]; x tanýmlý olsa dahi x bir constant olmadýðý için sentaks hatasý
int a[123 * 123 - 12]; sýkýntý olmaz constant.LEGAL
int dizi[0] veya int dizi[-1] olamaz.Dizinin boyutu 0 veya 0'ýn altýnda olamaz.'
// MACRO tanýmý kullanýlabilir.
#define SIZE 40

int a[SIZE];->SIKINTI YOK ÇALIÞIR.

eðer dizi dinamik ömürlü ise(a[5]) dizinin indexleri garbage value ile doldurulur.Bu þekilde kullanmak sakýncalý UNDEFINED BEHAVIOR olur.
statik ömürlü dizilerde ise deðerler 0 ile baþlar. -> static int a[10]->indexler 0 ile doldurulur.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE 100
// C ve CPP dillerinde fonksiyonlarýn parametre deðiþkenleri dizi olamaz. Pointer olur.
// Bir fonksiyonun geri dönüþ deðeri dizi olamaz, pointer olur. 
int arr[10]; // statik ömürlü, global alanda tanýmlanmýþ bir dizi. 
int main(void)
{
	int a[SIZE]; // otomatik ömürlü, Block scopetan çýktýðýnda ömrü bitecek. 
	// Dizinin elemanlarý memoryde art arda bulunur. 

	int arr1[5], arr2[14], x; // Diziler comma seperated list ile bildirilebilirler.
							// Kodun daha anlaþýlabilir olmasý için bunu kullanmaktan kaçýnýyoruz.
	int	arr_sub[50];
	arr_sub[5];			// Dizilerin elemanlarýna eriþmek için kullanýlan operatör -> indeks operatörü/subscript op. pointerler konusun da göreceðiz.
	arr_sub[90]; // Bu hata çalýþma zamanýnda fark edilir. Derleme zamanýnda fark edilmez. Undefined Behavior oluþturur. 
	
}


Köþeli parantez [] indeks operatörü daha yüksek önceliðe sahip olduðu için öncelik parantezine ihtiyaç duymaz.

&a[5] -> burada & operatörüu a[5] i operand olarak kullanýr.
a[5]-- -> burada -- operatörü a[5] ifadesini sað operand olarak kullanýr.
int main(void)
{
	int a[10];
	int b[10];
	a = b; // Atama operatörünü dizilerde bu þekilde kullanamazsýn. Sentaks hatasý. Sol operand olamaz! Sað olabilir.
		  //  Array decay: Dizi isimleri bir ifade içinde kullanýldýklarý zaman (bir kaç istisna dýþýnda) ilgili dizinin ilk 
		// elemanýnýn adresine dönüþtürülüyorlar. Veya array to pointer conversion olarakta bilinir.
	scanf("%d", &a); // -> scanf("%d", &a[0]) derleyici tarafýndan bu þekilde görülür. Bu dönüþümden dolayý l-value olma özelliðini kaybeder. 

}
L-value ikiye ayrýlýyor.
1-modifiable L value:
2-non-modifiable L value: Kullanýldýklarý ifade içerisinde kendisine atama yapýlamamasý.



// eðer bir dizinin elemanlarý baþka bir diziye kopyalanmak isteniyorsa;
// 1 - for döngüsü kullanýlarak
// 2 - memcpy

int main(void)
{
	int a[10];
	int b[10];

	for (int i = 0; i < 10; i++)
		a[i] = b[i]; // b'nýn elemanlarýný a dizisine aktarýlýr böyle.  

	printf("bir deger girin: ");
	scanf("%d", a);
	// scanf("%d", &a[0]); üstteki ile bu ayný. array to pointer conversion(array decay)

	printf("a[0] deðeri : %d", a[0]);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

DÝZÝLERDE ÝLK DEÐER ATAMASI(INITIALIZATION)
int main(void)
{
	int a[5] = { 1, 2, 3, 4, 5 }; // dizileri bu þekilde initialize edebiliriz. 
	// eðer dizinin tamamýna deðer verilmez ise deðer verilmeyen elemanlar 0 deðeri ile hayata baþlar.
	int b[5] = { 1, 2, 3 }; // b[3] ve b{4} elementleri 0 olur.
	int c[5] = { }; // C dilinde geçersiz, CPP'de geçerli. Curly bracelet içi boþ olamaz.
	int d[5] = { 0 }; // dizinin bütün elemanlarý 0 deðeri ile baþlar.
	int e[5] = { 0,1,2,3,4,5, }; // son indexten sonra konulan comma operatörü sentaks hatasý vermez. Buna "trailing comma" deniyor. Anlamda deðiþiklik yok.
	int f[] = { 1,2,3, }; // eðer dizinin size'ý yazýlmaz fakat ilk deðer verilirse, dizinin boyutu verilen ilk deðer boyutunda olur. Burada f[] dizisinin boyutu 3.
	int g[10] = { [2] = 56 };// designated initializer: C99 std ile eklenmiþ, CPP ile uyumlu deðil. 
							// dizinin içerisinde sadece belirli indexlere first initialize yapmamýzý saðlýyor. [2] = 56 sayesinde g dizisinin 2 nolu indexine 56 deðerini atayabiliyoruz.
	int h[25] = { [5] = 17,[13] = 25 };
	int j[25] = { [13] = 25 , [5] = 17}; // bu da olur
	int k[25] = { [13] = 25 , [5] = 17, 60, 70} //  bu da olur.çok kullanýlmýyor. 6 ve 7 indisli elemaný 60 ve 70 olur.
	int l[] = { [13] = 25, [5] = 17, 60, 70 } // bu da geçerli.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sizeof operator
- sizeof operatör olarak kullanýlan ilk keyword.;
- sizeof operatörü compile time operatörüdür.;
- Sentaksý fonksiyon çaðýrýsýna benziyor. sizeof(expr);
-sizeof operatörü ile oluþturulmuþ her ifade her zaman constanttýr(sabit).
- sizeof operatörünün ürettiði deðeri her zaman ÝÞARETSÝZ TAM SAYI olur, türü ise derleyiciye baðlý. (size_t)type alias(typedef) ile alakalý bir durum.;
sizeof kullanýmý;
- sizeof operatörünün operandý bir tür olmalý. -> sizeof(int);
- kullanýldýðý zaman kullandýðý türün byte boyutunu söyler. int için 4, long long için 8













