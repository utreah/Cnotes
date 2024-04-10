GOTO STATEMENT / type-conversions


// Programýn akýþý baþka bir yerdeki, baþka bir bellek alanýndaki iþleme yönlendirilmesine "jump" denir.

// jump ikiye ayrýlýr;
-Local Jump
-Long (non-local) jump.


1-) Local jump: Ayný stack-frame içinde yapýlan sýçrama iþlemleri. goto kullanýlýr.
		Stack Frame: bir fonksiyonun iliþkin yerel deðiþkenlerin, parametre deðiþkenlerinin tutulduðu yer
2-) Long Jump: Bir fonksiyondan baþka bir fonksiyona programýn akýþý yönlediriliyorsa bu Long Jumptýr. setjmp, longjmp isimli fonksiyonlar yapar.

Amaçlarý farklý.

// Local Jump'ýn aracý goto statement.
// 	Not:
// iki üç tane while içerisinden bir koþula baðlý olarak hemen çýkmak için go to kullanýlabilir.Baya iyi olur.
// kullaným temalarýnýn dýþýnda da kullanmamak lazým.
	

// label(etiket) bir identifierdýr(isim) ve her ismin bir scope'u vardýr.
// ve kapsamlarýnda kategorileri vardýr. Kategoriler;
1) Function prototype scope(fonksiyon prototip bildiriminde parantez içinde bilinen kýsým)					3) File scope(global isim alanýnda dosyanýn sonuna kadar)
2) Function scope : bir label tanýmlanýr ve yukarýdan da aþaðýsýndan da bu label kullanýlabilir.labellar ayrý scope olduðu için
fonksiyon içindeki diðer isimlerle çakýþmaz.																4) Block scope(blok içinde yapýlan bildirim)

Labellar þu þekilde tanýmlanýr. 
'isim+:' -> out: labeldan sonra bir statement gelmeli. 
int main()
{
	int out = 5; // isim çakýþmasý olmaz çünkü label olan out: farklý bir scope
out:
	; // null statement olduðu için bir sýkýntý yok.
	return 0;
}


keywordler label identifier olarak kullanýlamazlar. default bir keywordtür ve eðer default: þeklinde tanýmlarsak derleyici hata verecek ve switch - case içerisinde bulunmadýðýný söyleyecektir.


	Ýsimlendirilmiþ bir labeli goto statement dýþýnda kullanýlma imkaný yoktur.

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
// Daha önceki bir statement'a(yukarý yönlü yönlendirme) goto ile gitmek sentaks hatasý olmasa da düzgün kullaným olarak kabul edilemez.
// if, while, switch, for gibi deyimlerde aslýnda goto gibi jump(jump statement) yapar. Biz görmesekte assembly kodunda gözükür.
// goto legitimate kullaným alanlarý


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
	; // labellardan sonra statement gelmeli bu yüzden null statement koyduk.
	return 0;
}

void foo(void)
{
	//... nec labelýný burada arar
	goto nec; // kendi bulunduðu scope içerisinde arar. bar fonksiyonu içerisindeki nec: labelýna eriþemediði için hata verecektir.
	//... nec labelýný burada arar
}

void bar(void)
{
nec:
	;
}

// type conversions

implicit type conversions(örtülü tür dönüþümü) : derleyici dilin kurallarý gereði durumdan vazife çýkarýp bir kod üretiyor.
explicit type conversions() : dönüþümün bir operatör kullanýlmasýyla yani manuel olarak talepte bulunmasýyla gerçekleþir.


	/*int*/ func(int); // bu fonksiyonda geri dönüþ türü belirtilmemiþ olsa da derleyici bu fonksiyonun geri dönüþ deðerini int olarak kabul ediyor.


/****************************************************************************************/

int main()
{
	func(12); // fonksiyon bildirimi olmasa da derleme zamanýnda bir problem yaþanmaz çünkü derleyici böyle bir fonksiyonun var olduðunu kabul ediyor. implicit
}

/****************************************************************************************/

iVal = dVal; // iki farklý veri türünden deðer iþleme giremiyor. Öncellikle bir deðiþkenin türü deðiþtirilir ve daha sonra iþlem yapýlýr. 
// kodu þu þekilde
iVal + dVal;
int temp = dVal;
iVal + temp; // bu yapýlan iþlem implicit type conversion

/****************************************************************************************/

// type conversionlar ikiye ayrýlýr
implicit type conversion : otomatik, derleyici tarafýndan yapýlýr.
explicit type conversion / type - cast operator : manuel, yazýlýmcý tarafýndan operatör kullanýlarak yapýlýr. // explicit daha sonra iþlenecek

/****************************************************************************************/

neden bu konu bu kadar önemli ?

1 - ) tur dönüþümü yapýldýðý veya yapýlmadýðý için kodumuz yanlýþ olabilir.En sýk yapýlan hatalar arasýnda.

int x = -1; unsigned int y = 1; 

(y > x) ? printf("true") : printf("false"); // gözle baktýðýmýzda true çýkmasý gerekirken false kýsmýna girecektir. Daha sonra açýklanacak buraya line notunu düþerim.

/****************************************************************************************/

int main(void)
{
	char c = 176;
	//c degismiyor
	c == 176 ? printf("true") : printf("false"); // çýktý false olacaktýr. 1011 0010 -> 0100 1110
}

/****************************************************************************************/

int main(void)
{
	int i = 10; 
	int k = 3;
	double dval = i / k;
	printf("dval = %f\n", dval); // burada da type conversionstan dolayý veri kaybý var.
	////////////////////////////////////////////////////////
	int ival;
	int doubleVal;
	ival = doubleVal; // doubleVal'ýn deðerine göre UB veya veri kaybý olabilir
}

/****************************************************************************************/

USUAL ARITHMETIC CONVERSIONS(örtülü dönüþüm senaryosu)
Atama veya initilization kýsmýnda yapýlan dönüþümler(örtülü dönüþüm senaryosu)

/****************************************************************************************/

// a + b, x > y veya a > b ? a : b gibi operatörlerde olabilir. Bu iþlemler yapýlýrkende eðer operandlardan birisi farklý ise tür dönüþümü yapýlýr.
1 - sol operandýn türü sað oðerandýn türüne mi deðiþecek
2 - sað operandýn türü sol oðerandýn türüne mi deðiþecek
3 - ikisininde türü farklý bir türe mi deðiþtirilecek.

/****************************************************************************************/

int          double  // bu dönüþüm KALICI deðil geçicidir. statik deðiþken kavramýndan dolayý deðiþkenin türü deðiþmez. 
a + b	// geçici bir kod üretilir ve iþlem öyle yapýlýr. line 112'deki örnek. Hem imp hem explicit temp kullanýr.

/****************************************************************************************/
// Bir rank var.
// en yüksek rank gerçek(reel) sayýlarda. sýralamasý da yukarýdan aþaðýya gidiyor
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

// ayný türün iþaretli ile iþaretsizi arasýnda fark yok. Ayný rank.
// ör: a + b -> a long double, b int ise iþlem long double olarak yapýlýr.
// a + b -> eðer long double deðilse double olup olmadýðýna bakýlýr o da deðilse float. Bu sýrada devam eder.

/****************************************************************************************/

ÇOK ÖNEMLÝ! // Integral promotion(tam sayý türüne yükseltme): Eðer operandlar intten küçük short, char, _Bool (int altý türler olarakta geçer) türlerindense tür dönüþümü önce int türüne
// yükseltilmesine 'integral promotion' deniyor.
// Operand iþaretli int türde ifade edilebilme sýnýrlarý içerisinde ise, signed int'e dönüþümü saðlanýyor. int altý türlerden birisi ama signed int sýnýrlarýndan büyük ise unsigned int'e dönüþtürülür.

char c1 = 5, c2 = 10;
c1 * c2; // iþlem int türünde yapýlýr.
long c1 = 5; char c2 = 10;
c1 * c2; // iþlem long türünde yapýlýr.

// Eðer operandlar birisi unsigned ise iþlem unsigned'a doðru yapýlýr.
int a = 5;
unsigned int b = 10;
a + b; // unsigned olarak yapýlýr.

// unsigned short integral promotion ile 4 byte olan inte  int olarak dönüþüm yapýlýr. Çünkü int bütün unsigned short deðerlerini tutabilecek büyüklükte. 
Rankler ayný ise, iþaretlerde ayný ise ilave  bir dönüþüm yapýlmaz. 
Eðer operandlarýn rankleri farklý ise yüksek rank iþaretsiz ise iþlem yüksek olan iþaretsiz rankte yapýlýr. 

/****************************************************************************************/

// unsigned long, int x // burada unsigned long rankinde iþlem yapýlacak.
// int x; unsigned int y; // burada rankler ayný olsa da iþlem unsigned int'te yapýlýr. 


// long x 
// unsigned int y 
//  
// yüksek olan long, iþaretsiz olan int 
// x + y -> rank i yüksek olan tür, düþük olan unsigned türün tüm deðerlerini tutabilecek büyüklükte ise
// o zaman iþlem rank i büyük olan long ta yapýlýr.
// AMA
// eðer rank i yüksek olan signed tür, rank i daha küçük olan unsigned türün tüm deðerlerini tutamayacak ise
// o zaman iþlem daha yüksek olan rankte fakat iþaretsiz olarak yapýlýyor.

// ÖRNEK
// long (4 byte)
// unsigned int (4 byte)	rank i yüksek olan long burada unsigned ýn tüm deðerkerini tutar mý ? 
//							hayýr tutamaz. mesela 3 milyarý 4 byte long tutamaz.
//							bu durumda unsigned long a dönüþür.

/****************************************************************************************/