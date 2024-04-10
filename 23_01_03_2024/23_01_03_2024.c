GOTO STATEMENT / type-conversions
// ��ARETL�, ��ARETS�Z d�n���mleri m�lakatlarda sorulabiliyor!!

// Program�n ak��� ba�ka bir yerdeki, ba�ka bir bellek alan�ndaki i�leme y�nlendirilmesine "jump" denir.

// jump ikiye ayr�l�r;
-Local Jump
-Long (non-local) jump.


1-) Local jump: Ayn� stack-frame i�inde yap�lan s��rama i�lemleri. goto kullan�l�r.
		Stack Frame: bir fonksiyonun ili�kin yerel de�i�kenlerin, parametre de�i�kenlerinin tutuldu�u yer
2-) Long Jump: Bir fonksiyondan ba�ka bir fonksiyona program�n ak��� y�nlediriliyorsa bu Long Jumpt�r. setjmp, longjmp isimli fonksiyonlar yapar.

Ama�lar� farkl�.

// Local Jump'�n arac� goto statement.
// 	Not:
// iki �� tane while i�erisinden bir ko�ula ba�l� olarak hemen ��kmak i�in go to kullan�labilir.Baya iyi olur.
// kullan�m temalar�n�n d���nda da kullanmamak laz�m.
	

// label(etiket) bir identifierd�r(isim) ve her ismin bir scope'u vard�r.
// ve kapsamlar�nda kategorileri vard�r. Kategoriler;
1) Function prototype scope(fonksiyon prototip bildiriminde parantez i�inde bilinen k�s�m)					3) File scope(global isim alan�nda dosyan�n sonuna kadar)
2) Function scope : bir label tan�mlan�r ve yukar�dan da a�a��s�ndan da bu label kullan�labilir.labellar ayr� scope oldu�u i�in
fonksiyon i�indeki di�er isimlerle �ak��maz.																4) Block scope(blok i�inde yap�lan bildirim)

Labellar �u �ekilde tan�mlan�r. 
'isim+:' -> out: labeldan sonra bir statement gelmeli. 
int main()
{
	int out = 5; // isim �ak��mas� olmaz ��nk� label olan out: farkl� bir scope
out:
	; // null statement oldu�u i�in bir s�k�nt� yok.
	return 0;
}


keywordler label identifier olarak kullan�lamazlar. default bir keywordt�r ve e�er default: �eklinde tan�mlarsak derleyici hata verecek ve switch - case i�erisinde bulunmad���n� s�yleyecektir.


	�simlendirilmi� bir labeli goto statement d���nda kullan�lma imkan� yoktur.

	goto sentaks -> goto + label;
	goto out;
void func(void)
{
 int x = 5;
		out:
		// statement1
		// statement2
		if (x == 5)
			goto out;
}
// Daha �nceki bir statement'a(yukar� y�nl� y�nlendirme) goto ile gitmek sentaks hatas� olmasa da d�zg�n kullan�m olarak kabul edilemez.
// if, while, switch, for gibi deyimlerde asl�nda goto gibi jump(jump statement) yapar. Biz g�rmesekte assembly kodunda g�z�k�r.
// goto legitimate kullan�m alanlar�


int main(void)
{
	int a[100];
	int b[100];
	int c[100];
	int i, j, k;
	int iVal = 2350;
	for (i = 0; i < 100; i++) 
		for (k = 0; k < 100; k++) 
			for (j = 0; j < 100; j++)
				if (a[i] + b[k] + c[j] == iVal)
					goto out;

out:
	; // labellardan sonra statement gelmeli bu y�zden null statement koyduk.
	return 0;
}

void foo(void)
{
	//... nec label�n� burada arar
	goto nec; // kendi bulundu�u scope i�erisinde arar. bar fonksiyonu i�erisindeki nec: label�na eri�emedi�i i�in hata verecektir.
	//... nec label�n� burada arar
}

void bar(void)
{
nec:
	;
}

// type conversions

implicit type conversions(�rt�l� t�r d�n���m�) : derleyici dilin kurallar� gere�i durumdan vazife ��kar�p bir kod �retiyor.
explicit type conversions() : d�n���m�n bir operat�r kullan�lmas�yla yani manuel olarak talepte bulunmas�yla ger�ekle�ir.


	/*int*/ func(int); // bu fonksiyonda geri d�n�� t�r� belirtilmemi� olsa da derleyici bu fonksiyonun geri d�n�� de�erini int olarak kabul ediyor.


/****************************************************************************************/

int main()
{
	func(12); // fonksiyon bildirimi olmasa da derleme zaman�nda bir problem ya�anmaz ��nk� derleyici b�yle bir fonksiyonun var oldu�unu kabul ediyor. implicit
}

/****************************************************************************************/

iVal = dVal; // iki farkl� veri t�r�nden de�er i�leme giremiyor. �ncellikle bir de�i�kenin t�r� de�i�tirilir ve daha sonra i�lem yap�l�r. 
// kodu �u �ekilde
iVal + dVal;
int temp = dVal;
iVal + temp; // bu yap�lan i�lem implicit type conversion

/****************************************************************************************/

// type conversionlar ikiye ayr�l�r
implicit type conversion : otomatik, derleyici taraf�ndan yap�l�r.
explicit type conversion / type - cast operator : manuel, yaz�l�mc� taraf�ndan operat�r kullan�larak yap�l�r. // explicit daha sonra i�lenecek

/****************************************************************************************/

neden bu konu bu kadar �nemli ?

1 - ) tur d�n���m� yap�ld��� veya yap�lmad��� i�in kodumuz yanl�� olabilir.En s�k yap�lan hatalar aras�nda.

int x = -1; unsigned int y = 1; 

(y > x) ? printf("true") : printf("false"); // g�zle bakt���m�zda true ��kmas� gerekirken false k�sm�na girecektir. Daha sonra a��klanacak buraya line notunu d��erim.

/****************************************************************************************/

int main(void)
{
	char c = 176;
	//c degismiyor
	c == 176 ? printf("true") : printf("false"); // ��kt� false olacakt�r. 1011 0010 -> 0100 1110
}

/****************************************************************************************/

int main(void)
{
	int i = 10; 
	int k = 3;
	double dval = i / k;
	printf("dval = %f\n", dval); // burada da type conversionstan dolay� veri kayb� var.
	////////////////////////////////////////////////////////
	int ival;
	int doubleVal;
	ival = doubleVal; // doubleVal'�n de�erine g�re UB veya veri kayb� olabilir
}

/****************************************************************************************/

//1-) USUAL ARITHMETIC CONVERSIONS(�rt�l� d�n���m senaryosu) Derleyici dilin kurallar� gere�i sormadan baz� durumlarda i�lemleri yapmak i�in
// t�rd�n���m� yap�yor.Buna implicit type conversion deniyor.�rt�l� yada otomotik t�r d�n���m�.
//2-) Atama veya initilization k�sm�nda yap�lan d�n���mler(�rt�l� d�n���m senaryosu)

/****************************************************************************************/

// a + b, x > y veya a > b ? a : b gibi operat�rlerde olabilir. Bu i�lemler yap�l�rkende e�er operandlardan birisi farkl� ise t�r d�n���m� yap�l�r.
1 - sol operand�n t�r� sa� o�erand�n t�r�ne mi de�i�ecek
2 - sa� operand�n t�r� sol o�erand�n t�r�ne mi de�i�ecek
3 - ikisininde t�r� farkl� bir t�re mi de�i�tirilecek.

/****************************************************************************************/

int          double  // bu d�n���m KALICI de�il ge�icidir. statik de�i�ken kavram�ndan dolay� de�i�kenin t�r� de�i�mez. 
a + b	// ge�ici bir kod �retilir ve i�lem �yle yap�l�r. line 112'deki �rnek. Hem imp hem explicit temp kullan�r.

/****************************************************************************************/
// Bir rank var.
// en y�ksek rank ger�ek(reel) say�larda. s�ralamas� da yukar�dan a�a��ya gidiyor
conversionn rank

long double
double
float

long long
long
int

short
char
_Bool

// ayn� t�r�n i�aretli ile i�aretsizi aras�nda fark yok. Ayn� rank.
// �r: a + b -> a long double, b int ise i�lem long double olarak yap�l�r.
// a + b -> e�er long double de�ilse double olup olmad���na bak�l�r o da de�ilse float. Bu s�rada devam eder.

/****************************************************************************************/

�OK �NEML�! // Integral promotion(tam say� t�r�ne y�kseltme): E�er operandlar intten k���k short, char, _Bool (int alt� t�rler olarakta ge�er) t�rlerindense t�r d�n���m� �nce int t�r�ne
// y�kseltilmesine 'integral promotion' deniyor.
// Operand i�aretli int t�rde ifade edilebilme s�n�rlar� i�erisinde ise, signed int'e d�n���m� sa�lan�yor. int alt� t�rlerden birisi ama signed int s�n�rlar�ndan b�y�k ise unsigned int'e d�n��t�r�l�r.

char c1 = 5, c2 = 10;
c1 * c2; // i�lem int t�r�nde yap�l�r.
long c1 = 5; char c2 = 10;
c1 * c2; // i�lem long t�r�nde yap�l�r.

// E�er operandlar birisi unsigned ise i�lem unsigned'a do�ru yap�l�r.
int a = 5;
unsigned int b = 10;
a + b; // unsigned olarak yap�l�r.

// unsigned short integral promotion ile 4 byte olan inte  int olarak d�n���m yap�l�r. ��nk� int b�t�n unsigned short de�erlerini tutabilecek b�y�kl�kte. 
Rankler ayn� ise, i�aretlerde ayn� ise ilave  bir d�n���m yap�lmaz. 
E�er operandlar�n rankleri farkl� ise y�ksek rank i�aretsiz ise i�lem y�ksek olan i�aretsiz rankte yap�l�r. 

/****************************************************************************************/

// unsigned long, int x // burada unsigned long rankinde i�lem yap�lacak.
// int x; unsigned int y; // burada rankler ayn� olsa da i�lem unsigned int'te yap�l�r. 


// long x 
// unsigned int y 
//  
// y�ksek olan long, i�aretsiz olan int 
// x + y -> rank i y�ksek olan t�r, d���k olan unsigned t�r�n t�m de�erlerini tutabilecek b�y�kl�kte ise
// o zaman i�lem rank i b�y�k olan long ta yap�l�r.
// AMA
// e�er rank i y�ksek olan signed t�r, rank i daha k���k olan unsigned t�r�n t�m de�erlerini tutamayacak ise
// o zaman i�lem daha y�ksek olan rankte fakat i�aretsiz olarak yap�l�yor.

// �RNEK
// long (4 byte)
// unsigned int (4 byte)	rank i y�ksek olan long burada unsigned �n t�m de�erkerini tutar m� ? 
//							hay�r tutamaz. mesela 3 milyar� 4 byte long tutamaz.
//							bu durumda unsigned long a d�n���r.

/****************************************************************************************/

int main(void)
{
	int ival = 10;

	ival / 3; // b�yle olursa sol operand int sa� int oldu�u i�in sonu� 3 olur yani int.
	ival / 3.; // b�yle olursa sol operand int, sa� double oldu�u i�in type-conversiondan dolay� sonu� double olur(rank� daha y�ksek) ve sonu� 3.333333333 olur.
}

// hatalar
//  double dval =  10/3   -> buras� 3.0000 olur 3.33 de�il 
//  ama
//  do�rusu
//  double dval = 10 / 3.	 -> buras� i�te do�ru 3.3333 ��kar.-

/****************************************************************************************/

int x = 5;
			�NEML�!			op  op
double dval = 10 / (x > 2 ? 3 : 3.); //�fadelerin t�rleri derleme zaman�nda belli oluyor. // ��kt� 3.33333
									//Burada ternary ilk operand�n do�ru ya da yanl�� olmas�n�yla ilgili de�il. T�r d�n���m� 2. ve 3. operand�n aras�nda oluyor. "3 + 3." gibi d���n sonu� double olurdu.


// �fadelerin t�rleri runtimeda belli olmaz. Compile timeda belli olur. Operandlar aras�nda t�r d�n���mleri olur.
				NOT
				//	��aretsiz bir pozitif de�er ile i�aretli bir negatif de�er ile i�leme sokulursa, sign x de�erini unsigned x e �evirecek. 
				//	
				//	int x = -1  // 1111 1111 1111 1111 -> bunun de�eri -1
				//	
				//	bunu i�aretsiz int e d�n��t�r�nce  -> art�k ba�taki 1, i�aret biti olmuyor ��nk� unsigned zaten
				//	dolay�s� ile 1111 1111 1111 1111 bunun unsigned de�eri al�n�r o da 4.2 milyar k�s�r.
				//	
				//	unsigned int y = 1 
				//	if y > x   printf(dogru) //yukar�da art�k x = 4.2 milyar k�s�r oldu. 1 > 4.2 false olur. bu sebeple false
				//	else printf(yanlis)  
				//	
				//	sonucu yanlistir.
				//
				//	Ayr�ca signed t�r�n ve unsigned t�r�n�n k�yaslanmas� warning mesaj� olarak ta ��kar
				//	signed/unsigned mismatch. bu hatalar� mutlaka incelemek laz�m.
				//
				//
				// -------------------------------------------------------------------------------------------------------------
				//    assignment/init ATAMA D�N���MLER�

				T x = expr; // T = T�r, x = identifier, expr = expression; x'in t�r�ne g�re ifadenin t�r� x'in t�r�ne atan�r ve expr x'e atan�r.
				y = expr; // expr'in t�r� y'nin t�r�ne d�n��t�r�l�r ve expr y de�i�kenine atan�r.
				void func(T x); // arg�man parametrenin t�r�ne d�n��t�r�l�r. Mesela parametre double arg�man int ise arg�man doublea d�n��t�r�l�r.
				func(x); //func in parametresi int olsun, arg�man ise double olsun.arg�man g�nderirken int e �evirir.
				return y; // y'nin t�r� return statement'�n t�r�ne d�n��t�r�l�r. 

				KURAL!!
				// - T�r d�n���m� her zaman ataman�n yap�ld��� kopyalaman�n yap�ld��� t�re g�re yap�l�r.
				�rn: int x = expr; // burada ifade ne olursa olsun expr int'e d�n��t�r�lecek. 
				dezavantaj�:

/****************************************************************************************/
				//	 b�y�k tam say� t�r�nden d���k tam say� t�r�ne ge�i� olurken veri kayb�na neden olabilir.!
				// bu i�lem explicit olarak yap�lmal� veri kayb�n� �nlemek i�in.
				//	char c; [-128 / 127] aral���n� tutar
//	int ival = 987;
//	c = i;    char 987 tutamayaca�� i�in veri kayb� olur.
//	printf("%d",c); --> -37 ��kar. char 1 byte yani 3DB'den 3 olmayacak. DB = 1101 1011 -> bu da i�aretli char t�rden negatif bir de�er (MSB 1 oldu�u i�in)
				// hesaplarken 2ye t�mleyeni al�yorsun 0010 0101 -> 37 -> -37'dir. 
				//	Warningde de conversion from int to char possible loss of data verir.
//	Bu kod yanl�� kabul edilir.
//	e�er bilerek yap�ld�ysa:
//	burada type-casting yap�lmal�.
//

/****************************************************************************************/



