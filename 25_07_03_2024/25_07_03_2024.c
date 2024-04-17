Fonksiyona ba�ka bir fonksiyon g�nderilebiliyor.
Ve bu mekanizmaya "callback" deniyor.Pointerlarla alakal�. (Function pointer);

int get_random_char(int (*fp)(int)) -> // *fp burada fonksiyonun adresini al�yor ve bu sayede arg�man olarak kullanmam�z� sa�l�yor.
/*
--------------------------------------------------------------D�Z�LER(ARRAYS)---------------------------------------------------------------
																																							*/


	Data Structure(s)->veri yap�lar�
	Verileri i�lemek i�in verileri bellekte tutmam�z gerekiyor.�r: ��rencilerin okulda s�navlardan ald�klar� notlar, g�nlerin ortalama s�cakl�k de�erleri gibi.
	Neden bir arada tutuyoruz ?
	Verilerinn �st�nde bir tak�m i�lemler yapabilmek i�in, verileri bellekte tutuyoruz.
	Ger�ekle�tirdi�imiz i�lemlere de algoritma denir.

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	Her bir de�er birbirinin pe�i s�ra(continous) �eklinde yerle�tirilmi�se buna "DYNAMIC ARRAY " deniyor.
	- Linked List
	Singly Linked List
	Double Linked List
	- Trees
	binary search tree
	red - black
	- Graph
	- Hashtable
	gibi veri yap�lar� vard�r.

	Bellekte bir �ekilde tutulan verileri mant�ksal �eklinde kullanmak i�in olu�turulmu� d�zeneklere "DATA STRUCTURES" deniyor.
	Neden bu kadar fazla veri yap�s� var ?
	-Kullan�lan veriye g�re, yap�lan i�lemin maliyeti art�p ya da azalabiliyor.

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Algorithm Complexity
	Memory Complexity : Kullan�lan bellek alan�.
	Computational Complexity : ��i ger�ekle�tirmek i�in yap�lan i�lem say�s�.

	Constant - Time Algorithms : ��e say�s� art�yor olsa da maliyet her zaman ayn�.
	Linear Complexity : Veri yap�s�ndaki ��e say�s� artt�k�a, yap�lan i�lem miktar�da do�rusal olarak art�yor.

	Big O notation O() :
	�yiden->k�t�ye(farkl� complexitylerde var daha iyi daha k�t�)
	0(1)->constant time algorithm
	O(logn) ->
	O(n)->Linear complexity
	O(nlogn) ->
	O(n ^ 2)->Quadratic

	n elemanl� bir dizinin algoritma karma��kl��� O(n)'dir.'

	Binary Search Algorithm : K���kten - b�y��e(veya tam tersi) s�ralanm�� bir dizide ortadaki de�er se�ilir ve 3 durum olu�ur;
1 - Se�ti�im de�er arad���m de�er
2 - Se�ti�im de�er arad���m de�erden b�y�k
3 - Se�ti�im de�er arad���m de�erden k���k.
Bu i�lem istenilen sonuca ula��l�na kadar tekrarlan�r.Her seferinde ortadaki de�er se�ilir ve gereksiz olan k�s�m kullan�lmaz.
Duruma g�re ihtiyac�m�z�n olmad��� k�s�m at�l�r ve kullan�lmaz.Bu sayede algoritma karma��kl��� O(logn)'e' kadar d��er.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Algoritman�n kar���kl��� veri yap�s�ndaki niteliklere ba�l� olabiliyor.
1 - Best Case
2 - Worst Case
3 - Average
Aksi s�ylenmedik�e average case kabul edilir.

Veri yap�lar�n�n �nemli k�sm� dilin standart k�t�phanesinde haz�r olarak geliyor.

Runtimeda dynamic array ile veri ekleyip silebiliyoruz.
Dynamic array �retimde en �ok kullan�lan data type.Ve en �nce ��renilmesi gerekilen bir veri t�r�.

Fixed array ise eleman say�s� program�n �al��ma zaman�nda asla ve asla de�i�mez.Ekleme ve silme i�lemi asla yap�lamaz.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

C ve CPP dizilerin sentakslar� % 85 ayn�.
Bir dizi n tane de�i�kenin bir yerde tutuldu�u bir yap�d�r.

Dizinin sentaks� -> int a[int_const_expr]; 
int_const_expr = size of array(dizinin  boyutu)
OLUR - OLMAZ;
int x = 10;
int a[]; ->olmaz ��nk� braketlerin aras�nda bir constant olmal�.sentaks hatas�
int a[x]; x tan�ml� olsa dahi x bir constant olmad��� i�in sentaks hatas�
int a[123 * 123 - 12]; s�k�nt� olmaz constant.LEGAL
int dizi[0] veya int dizi[-1] olamaz.Dizinin boyutu 0 veya 0'�n alt�nda olamaz.'
// MACRO tan�m� kullan�labilir.
#define SIZE 40

int a[SIZE];->SIKINTI YOK �ALI�IR.

e�er dizi dinamik �m�rl� ise(a[5]) dizinin indexleri garbage value ile doldurulur.Bu �ekilde kullanmak sak�ncal� UNDEFINED BEHAVIOR olur.
statik �m�rl� dizilerde ise de�erler 0 ile ba�lar. -> static int a[10]->indexler 0 ile doldurulur.

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define SIZE 100
// C ve CPP dillerinde fonksiyonlar�n parametre de�i�kenleri dizi olamaz. Pointer olur.
// Bir fonksiyonun geri d�n�� de�eri dizi olamaz, pointer olur. 
int arr[10]; // statik �m�rl�, global alanda tan�mlanm�� bir dizi. 
int main(void)
{
	int a[SIZE]; // otomatik �m�rl�, Block scopetan ��kt���nda �mr� bitecek. 
	// Dizinin elemanlar� memoryde art arda bulunur. 

	int arr1[5], arr2[14], x; // Diziler comma seperated list ile bildirilebilirler.
							// Kodun daha anla��labilir olmas� i�in bunu kullanmaktan ka��n�yoruz.
	int	arr_sub[50];
	arr_sub[5];			// Dizilerin elemanlar�na eri�mek i�in kullan�lan operat�r -> indeks operat�r�/subscript op. pointerler konusun da g�rece�iz.
	arr_sub[90]; // Bu hata �al��ma zaman�nda fark edilir. Derleme zaman�nda fark edilmez. Undefined Behavior olu�turur. 
	
}


K��eli parantez [] indeks operat�r� daha y�ksek �nceli�e sahip oldu�u i�in �ncelik parantezine ihtiya� duymaz.

&a[5] -> burada & operat�r�u a[5] i operand olarak kullan�r.
a[5]-- -> burada -- operat�r� a[5] ifadesini sa� operand olarak kullan�r.
int main(void)
{
	int a[10];
	int b[10];
	a = b; // Atama operat�r�n� dizilerde bu �ekilde kullanamazs�n. Sentaks hatas�. Sol operand olamaz! Sa� olabilir.
		  //  Array decay: Dizi isimleri bir ifade i�inde kullan�ld�klar� zaman (bir ka� istisna d���nda) ilgili dizinin ilk 
		// eleman�n�n adresine d�n��t�r�l�yorlar. Veya array to pointer conversion olarakta bilinir.
	scanf("%d", &a); // -> scanf("%d", &a[0]) derleyici taraf�ndan bu �ekilde g�r�l�r. Bu d�n���mden dolay� l-value olma �zelli�ini kaybeder. 

}
L-value ikiye ayr�l�yor.
1-modifiable L value:
2-non-modifiable L value: Kullan�ld�klar� ifade i�erisinde kendisine atama yap�lamamas�.



// e�er bir dizinin elemanlar� ba�ka bir diziye kopyalanmak isteniyorsa;
// 1 - for d�ng�s� kullan�larak
// 2 - memcpy

int main(void)
{
	int a[10];
	int b[10];

	for (int i = 0; i < 10; i++)
		a[i] = b[i]; // b'n�n elemanlar�n� a dizisine aktar�l�r b�yle.  

	printf("bir deger girin: ");
	scanf("%d", a);
	// scanf("%d", &a[0]); �stteki ile bu ayn�. array to pointer conversion(array decay)

	printf("a[0] de�eri : %d", a[0]);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

D�Z�LERDE �LK DE�ER ATAMASI(INITIALIZATION)
int main(void)
{
	int a[5] = { 1, 2, 3, 4, 5 }; // dizileri bu �ekilde initialize edebiliriz. 
	// e�er dizinin tamam�na de�er verilmez ise de�er verilmeyen elemanlar 0 de�eri ile hayata ba�lar.
	int b[5] = { 1, 2, 3 }; // b[3] ve b{4} elementleri 0 olur.
	int c[5] = { }; // C dilinde ge�ersiz, CPP'de ge�erli. Curly bracelet i�i bo� olamaz.
	int d[5] = { 0 }; // dizinin b�t�n elemanlar� 0 de�eri ile ba�lar.
	int e[5] = { 0,1,2,3,4,5, }; // son indexten sonra konulan comma operat�r� sentaks hatas� vermez. Buna "trailing comma" deniyor. Anlamda de�i�iklik yok.
	int f[] = { 1,2,3, }; // e�er dizinin size'� yaz�lmaz fakat ilk de�er verilirse, dizinin boyutu verilen ilk de�er boyutunda olur. Burada f[] dizisinin boyutu 3.
	int g[10] = { [2] = 56 };// designated initializer: C99 std ile eklenmi�, CPP ile uyumlu de�il. 
							// dizinin i�erisinde sadece belirli indexlere first initialize yapmam�z� sa�l�yor. [2] = 56 sayesinde g dizisinin 2 nolu indexine 56 de�erini atayabiliyoruz.
	int h[25] = { [5] = 17,[13] = 25 };
	int j[25] = { [13] = 25 , [5] = 17}; // bu da olur
	int k[25] = { [13] = 25 , [5] = 17, 60, 70} //  bu da olur.�ok kullan�lm�yor. 6 ve 7 indisli eleman� 60 ve 70 olur.
	int l[] = { [13] = 25, [5] = 17, 60, 70 } // bu da ge�erli.
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

sizeof operator
- sizeof operat�r olarak kullan�lan ilk keyword.;
- sizeof operat�r� compile time operat�r�d�r.;
- Sentaks� fonksiyon �a��r�s�na benziyor. sizeof(expr);
-sizeof operat�r� ile olu�turulmu� her ifade her zaman constantt�r(sabit).
- sizeof operat�r�n�n �retti�i de�eri her zaman ��ARETS�Z TAM SAYI olur, t�r� ise derleyiciye ba�l�. (size_t)type alias(typedef) ile alakal� bir durum.;
sizeof kullan�m�;
- sizeof operat�r�n�n operand� bir t�r olmal�. -> sizeof(int);
- kullan�ld��� zaman kulland��� t�r�n byte boyutunu s�yler. int i�in 4, long long i�in 8













