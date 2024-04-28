/*
int x = 10, * p1 = &x, * p2 = p1, * p3 = p2;
++* p1; // hepsi x in kendisi anlam�nda ve ++ operat�r� ile i�leme girmi�.
++* p2;
++* p3;
bu x i �� kere art�r�yor.x = 13 oluyor.

POINTER NE ��E YARIYOR.

void func(int a)
{
	a = 23;
}

int main()
{
	int x = 10;
	func(x);
	printf("x = %d", x);
}

Yukar�daki �rnekte x en son ka�t�r ?
x halen 10 dur.��nk� fonksiyona g�nderilen x ve daha sonras�nda a olarak
fonksiyonda i�leme sokulan farkl� bir obje, x de�il.
adreslere bak�l�rsa e�er g�r�l�r.Call by value.


void func(int a)
{
	a = 23;
	printf("&a = %p\n", a); // a n�n adresi
}

int main()
{
	int x = 10;
	func(x);
	printf("x = %d\n", x);
	printf("&x = %p\n", x); // x in adresi ve farkl� objeler bunlar.
}

a ve x farkl� adreslerde oldu�unu yazar.

--------------------------------------


C de e�er bir yerel de�i�kenin ba�ka bir fonksiyon taraf�ndan de�i�tirilmesini istiyorsak
bu de�i�kenin kendisini fonksiyona g�ndermemiz gerekiyor.
Ba�ka dillerde kullan�m� daha kolay olabilir fakat C de pointer semanti�i ile
yap�l�yor bu i�.Call by reference.

Neden call by reference?
1- Bir fonksiyona de�er iletmek i�in  kullan�labilir. Bu da ikiye ayr�l�yor.
    -Pass by value -> sadece de�eri g�nderir ve de�i�ken �zerindeki de�eri de�i�mez(statik de�il ise)
    -Pass by reference(adresi g�ndermek) -> de�i�kenin adresini g�nderir ve bu sayede de�i�kenin de�eri set edilir(dinamik olsa bile)
2- Geri d�n�� de�eri yerine kullan�labilmesi.Bir adres g�nderip hesaplat�p ayn� adresteki nesneye yazabilir. -> geri d�n�� de�eri 
    t�r� kullanmak yerine adres de�i�kenleri ile fonksiyonda hesaplanan de�er bir de�i�kene
    atanabilir ve kullan�labilir. (return'� int olan bir de�i�keni void yap�p adres t�r�nden bir veri t�r� ile yap�labilir)
    void calculate_average(int a, int b, double* avg) -> *p = (a+b)/2.;
    int calculate_average(int a, int b) -> return (a+b)/2.;
        -Burada pointer ile yap�lan g�r�nt� kirlili�i olu�turabilir ��nk� de�eri bir de�i�kende tutma zorunlulu�u var(ki�isel g�r��)
        -Geri d�n�� de�eri olan fonksiyonlarda bir adresteki nesneye yaz�l�r. Bu da maliyet konusunu ortaya ��kar�r. sizeof de�eri
            4, 8, 16 gibi k���k de�erler ise bu return'�n yapt��� kopyalamada b�y�k bir maliyet olu�turmuyor. int double gibi t�rlerde
            s�k�nt� yok. user-defined types'ta maliyet problem olabilir.

            typedef struct{
            int row,col;
            int a[20][20];
            }Matrix;

            void add_matrix(Matrix *presult, Matrix p1, Matrix p2)
            ....

            Matrix x,y;
            Matrix z;
            add_matrix(&z,x,y); // burada matrix'e x ve y'yi blok kopyalama ile yolluyoruz. Bunun yerine direkt adreslerini yollay�p �yle
                                    i�leme tabii tutabiliriz bu da maliyeti azalt�r.
            void add_matrix(Matrix *presult, const Matrix* p1, const Matrix* p2); // const keyword�n� ��renecez. Anlam� bu de�i�kende de�i�iklik
                                                                                    yapmayaca��m onu sadece read-only olarak kullan�cam gibi bir anlam� var.
                                                                                    32. derste ��renicez bunu.
            add_matrix(&z,&x,&y); // iki kod bir birinden �ok farkl�.

            // mesela bu �rnekte matrix user-defined type 808 bytel�k alan kapl�yor. Burada return yerine bir address yollad���m�zda
                sadece 4 byte'l�k bir alan kullan�yoruz ve bu da maliyet a��s�ndan daha iyi.

------------------------------------------------
double get_circle(double radius)
        return 3.14 *radius*radius


    double r = 23.4242
    double area

    area = get_circle(r)
    printf area

    yukar�daki call by value

    --------------

    Call by reference ile yazarsak


    void get_circle(double radius,int *p_area)
        *p_area = 3.14 * radius * radius


    double r = 23.4242
    double area

    get_circle(r,&area)
    printf area

    // burada g�nderdi�im area de�i�kenine atad�.

        Bu tip basit i�lemlerde call by value se�ilebilir.
    Hesaplanacak de�er tamsay� veya reel say� ise, call by reference y�ntemi
    biraz daha karma��k hale getiriyor i�i.
    Call by value burada do�ru tercih olabilir.


    AMA !
    Hesaplanacak de�er bellekte 50 byte 100 byte 200 byte yer kapl�yorsa,
    iki y�ntem aras�nda �ok b�y�k bir maliyet fark� var.
    Assembly seviyesinde
    �a�r�lan fonksiyonun geri d�n�� de�eri ge�ici bir nesnede tutuluyor.
    bizde bu ge�ici nesneden x = func() gibi ifadeyle kendi nesnemize aktar�yoruz.
    sonra bu temp nesnede siliniyor.
    Yani 2 adet bellek kopyalama var.
    1. return de�erinin temp alan�na yaz�mas�
    2. �a��ran kodun return de�erini kendi de�i�kenine aktarmas�.

    Burada Call by reference �eklinde kullan�lmas� �ok daha iyidir.
    2.26 da struct yaz�yor ve g�steriyor.ben yazmayaca��m.

    2 adet 1608Byte alan kopyalamak yerine 4 bytel�k bir pointer adresi yaz�yoruz.
    �ok ciddi bir fark.

    AYn� zamanda birden fazla de�eri de�i�tirebiliriz bu y�ntemle.

    func(a,b,c,&d,&e,&f)  mesela burada d e f de�i�kenleri tamamen de�i�tirilip
    main functiondan eri�ilebilir


------------------------------------------------

3- Dizi ileteceksek bunun tek yolu fonksiyonun parametre de�i�keni pointer olmal�. hem paratmetre hemde gerid�n�� de�eri pointer olabilir.dizi olamaz.
    Dizi gibi g�r�nebilir.

4 - Fonksiyon birden fazla de�er iletecekse/d�nd�rmesi gerekiyor ise, yani ka� tane de�er iletecekse
    void get_values(double x, double y, double *alpha, double *beta, double *gama); // bu fonksiyonda birden fazla i�lem yap�lacak ve
    g�nderilen adresteki nesnelere yap�lan i�lemin cevaplar� set edilecek. onlar�n adreslerini al�p i�leme sokabilir.
A�a��daki gibi yap�l�r.

void func(int* ptr)
{
	*ptr = 100;
}

int main()
{
	int x = 10;

	func(&x);

	printf("x = %d\n", x);
}

i�te burada x = 100 g�r�l�r.

------------------------------------------------



�rnek
mesela iki de�i�keni takas yapaca��m


int a, b;
printf("iki degisken girin : ");
(void)scanf("%d%d", &a, &b);


printf("a = %d    b = %d", a, b);


int temp = a;
a = b;
b = temp;


printf("a = %d    b = %d", a, b);


Yukar�daki takas i�lemi gibi i�lemleri s�k s�k yapacaksam e�er,
bunu kod tekrar�n� engellemek ve daha ta��nabilir bir kod olmas� amac�yla
function haline getirmek daha mant�kl�.


void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}


int main()
{
    int a, b;
    printf("iki degisken girin : ");
    (void)scanf("%d%d", &a, &b);


    printf("a = %d    b = %d", a, b);


    swap(a, b);


    printf("a = %d    b = %d", a, b);


}


Yukar�daki kod x ile y nin yerini de�i�tirmez. :D
��nk� a ve b, x ve y de�il.


------



�rnek
mesela iki de�i�keni takas yapaca��m


int a, b;
printf("iki degisken girin : ");
(void)scanf("%d%d", &a, &b);


printf("a = %d    b = %d", a, b);


int temp = a;
a = b;
b = temp;


printf("a = %d    b = %d", a, b);


Yukar�daki takas i�lemi gibi i�lemleri s�k s�k yapacaksam e�er,
bunu kod tekrar�n� engellemek ve daha ta��nabilir bir kod olmas� amac�yla
function haline getirmek daha mant�kl�.


void swap(int x, int y)
{
    int temp = x;
    x = y;
    y = temp;
}


int main()
{
    int a, b;
    printf("iki degisken girin : ");
    (void)scanf("%d%d", &a, &b);


    printf("a = %d    b = %d", a, b);


    swap(a, b);


    printf("a = %d    b = %d", a, b);


}


Yukar�daki kod x ile y nin yerini de�i�tirmez. :D
��nk� a ve b, x ve y de�il.


----------------------------------------------------------------------------
*/
/*
Fonksiyonun parametre de�i�keni olan pointer e�er de�er de�i�tirme i�lemi yapabiliyor ise bu fonksiyonlara;
-Mutator, -Setter, -Set function denir.
void func(T *p); // out param
Fakat fonksiyonun parametresi const Type * �eklinde ise o de�i�kenin adresinde de�i�iklik yapmama garantisi veriyor ve bu fonksiyonlara;
-Accessor, -Getter, -Get function denir.
void bar(const T * p); // in param

D�KKAT
- Bir fonksiyonun parametresi dizi olamaz
- Bir fonksiyonun geri d�n�� de�eri dizi olamaz.
yani, bir fonksiyonun bir fonksiyona dizi g�ndermesi ne olursa olsun adres yoluyla olmal�.
int bar(int* param);
int foo(int param);
int main(void)
{
    int a[5] = { 1,2,3,4,5 };
    //foo(a); -> bu �ekilde diziyi foo fonksiyonuna yollayamay�z. ��nk� array decaydan dolay� 0 indisli eleman�n adresini yolluyoruz.
    bar(a); // -> bu �ekilde yollanabilir ��nk� array decayden dolay� adresini yolluyoruz ve fonksiyonun parametresi pointer de�i�ken.
}

----------------------------------------------------------------------------

        ----------------------------------------------------- D�Z�LER VE POINTERLAR -----------------------------------------------------
                                                                POINTER AR�TMET���
-    C D�L�NDE
-    bir adresle bir tamsay� toplanabilir.                                      (adres + n)     == adres
-    bir tamsay� ile bir adres toplanabilir.                                    (n + adres)     == adres
-    bir adresten bir tamsay� ��kart�labilir.                                   (adres - n)     == adres
-    bir tamsay�dan bir adres �IKARTILAMAZ !!!                                  (n - adres)     != adres
-    bir adresten ba�ka bir adres ��kart�labilir. de�eri i�aretli tamsay�d�r.   (adres - adres) == adres(signed)
-    bir adres ile ba�ka bir adres TOPLANAMAZ !!!                               (adres + adres) != adres

int main(void)
{
    int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
    int *p;


    a + 5; // ge�erli 
    3 + p; // ge�erli
    p - 2; // ge�erli
    3 - a; // GE�ERS�Z
    2 - p; // GE�ERS�Z
    p + a; // GE�ERS�Z
}

    elemanlar�n bellekteki yerlerine bak�labilir.
    her adres aras� sizeof(Type) kadar fark var. Mesela bir adres ABC04 ise di�er adres ABC08 olur(int i�in)
    double olsayd� 8 byte
    int 4 byte
    char 1 byte

    Bir nesnenin adresine 1 toplarsak, ayn� t�rden bir sonraki nesnenin adresini elde etmi� oluruz.
    Bir nesnenin adresine 1 ��kar�rsak,ayn� t�rden bir �nceki nesnenin adresini elde etmi� oluruz.
    &a[5]  ile  a + 5 ayn� ifade // ��nk� dizilerin ard� ard�na s�ralanm�� olmas� garantisi var. a bir adres ve 5 bir tam say� bu y�zden
                                    a + 5 dedi�imiz zaman a'n�n 5. indisinin adresine i�aret eder.
    yani
    &a(n)  ile    a + n ayn�
    &a[i] == a + i == i + a
    a[i] == *(a + i) == *(i + a) Bu ifadeler AYNI!
-----------------------------------------------------
#include <stdio.h>
void foo(int *p, int size)
{

    for(int i = 0; i < size; i++)
    printf("%d\n", *p++);

}
int main()
{
    int a[10] = { 0,1,2,3,4,5,6,7,8,9 };

    foo(a, 10);

}
-----------------------------------------------------
    NOT !!!

    i[a]  bu ifade ile a[i] ayn�d�r
    [] subscript operat�r� a[i] ifadesini *(a+i) ye �eviriyor.
    i[a] == *(i + a) // a[i] == *(a + i)

    p = adres olarak referans alal�m;
        p++;//bir sonrakine ge�iyor bu ifade ya da p = p+1; ya da p+=1;
    int a[10] == {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
    int* ptr = a + 5;
    printf("%d", *(ptr + 4)); // burada sentaks hatas� yok 9 numaral� indisteki de�eri yazd�r�r. UB yok.
    printf("%d", *(ptr + 7)); // burada sentaks hatas� yok, �al���r fakat *(ptr + 7)'ye eri�meye �al���r isem UB VAR. Ekrana yazd�rmak UB de�il.
-----------------------------------------------------
    TEKRAR
    x[y]  -> derleyici subscript operat�r�n� g�r�nce
    *(x + y) ye �evirir bunu
    yani
    x[y]  ile y[x] ayn� ifade

    x[y] = *(x+y)  a�a��daki ile ayn�.
    x[x] = *(y+x)
-----------------------------------------------------
    int x = 10;	// 1 elemanl� bir array gibi d���n�lebilir.
    ++(&x)[0];  // x = 11
    ++*(&x+0); // x = 12
-----------------------------------------------------
                                                           SUBSCRIPT OPERATORU
- En y�ksek �ncelik seviyesinde(1. s�rada) -> soldan sa�a 
int main(void)
{
    int a[10] = { 0,1,2,3,4,5,6,7,8,9};
    int *ptr = a + 5;

    printf("%d\n",*ptr);   // 5
    printf("%d\n",ptr[0]);  // 5
    printf("%d\n",ptr[3]);  // 8
    printf("%d\n",ptr[-2]);  // 3
    printf("%d\n",*(ptr - 2));  // 3
    // Bu i�lemlerde diziyi ta��r�rsak bu Undefined Behavior.
    // mesela ptr[-15] bir sentaks hatas� de�il ama bir UB.

}
ptr, a isimli bir dizinin bir eleman�n� g�stermektedir.
    ptr nin g�sterdi�i dizi elaman�n�n indexi nedir
    ptr - a d�r.


    ptr, a isimli bir dizinin 5 indisli eleman�n� g�steriyor. ptr ?
    ptr = a + 5 tir


    ================================================


    p[n] == *(p + n)
    p[-2] == *(p - 2)
    &p[n] == p + n
    *p = p[0]
    ================================================


    int x = 10;	// 1 elemanl� bir array gibi d���n�lebilir.
    ++(&x)[0];  // x = 11
    ++*(&x+0); // x = 12
   ================================================
   - Dizileri fonksiyonlara g�nderirken adresleri ve boyutlar� g�nderilmeli.
   - E�er dizinin boyutunu sizeof(arr) / sizeof(arr[0]) ile fonksiyonda hesaplamaya �al���rsak, sizeof compile timeda yap�ld��� i�in
        arr dizisini pointer olarak g�recek(4 byte) ve arr[0] da int t�r� oldu�u i�in 4 byte olarak gelecek ve cevap 1 olacak. BU Y�ZDEN BU YANLI�!
        void func(int* arr)
            sizeof(arr) / sizeof(arr[0]); // bu yanl��t�r!
        void bar(int* arr, int size) // int yerine size_t kullanmay� anlatacak necati hoca ileride 
    - 
// daha �ok tercih edilen
	void print_array(const int * ptr, int size)
	{
		while(size--)
		{
			printf("%d ",*ptr);
			ptr++;
		}
		printf("\n--------------------------\n");
	}

	int main()
	{
		int a[10] = { 0,1,2,3,4,5,6,7,8,9};
		print_array(a,10);
	
	}

	D�KKAT!
	print_array de pointer olarak g�nderilen nesne kesinlikle const keyword � ile nitelenmeli.
	Yap�lmazsa b�y�k hata olur. M�lakatlarda �ok dikkat ediyorlar.


	print_array(a,5);  // ilk 5 eleman
	print_array(a+5,3);  // 5,6,7 elemanlar�n� �a��r�r.
	print_array(a+5,3);  // 5,6,7 elemanlar�n� �a��r�r.
	print_array(a+SIZE-5,5 );  // son 5 eleman�n�n de�eri.SIZE b�y�kl���n� g�steren makro olsun mesela.


	------------

	// bu bir y�ntem
	int sum_array(const int *ptr,int size)
	{
		int sum = 0;
		while(size--)
		{
			sum += *ptr;
			ptr++;
		}
		return sum;
	}

	//di�eri
	int sumArray(const int *a,int size)
	{
		int sum = 0;
		for(int i = 0; i<size;i++)
			sum += a[i];
	
		return sum;
	}

	randomize();
	set_random_array(a,SIZE);
	
	printf("sum = %d\n",sum_array(a,SIZE));
	printf("sum = %d\n",sumArray(a,SIZE));

	-------------------------------------
	-------------------------------------

	son �rnek

	//kendi parametresine, arg�man olarak g�nderilen de�erleri, 
	//di�er fonksiyonu �a��r�rken arg�man olarak ekliyor.

	double get_mean(const int * ptr , int size)
	{
		return (double)sum_array(ptr,size) / size;
	}




	


}// daha �ok tercih edilen
void print_array(const int* ptr, int size)
{
    while (size--)
    {
        printf("%d ", *ptr);
        ptr++;
    }
    printf("\n--------------------------\n");
}

int main()
{
    int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
    print_array(a, 10);

}

D�KKAT!
print_array de pointer olarak g�nderilen nesne kesinlikle const keyword � ile nitelenmeli.
Yap�lmazsa b�y�k hata olur.M�lakatlarda �ok dikkat ediyorlar.


print_array(a, 5);  // ilk 5 eleman
print_array(a + 5, 3);  // 5,6,7 elemanlar�n� �a��r�r.
print_array(a + 5, 3);  // 5,6,7 elemanlar�n� �a��r�r.
print_array(a + SIZE - 5, 5);  // son 5 eleman�n�n de�eri.SIZE b�y�kl���n� g�steren makro olsun mesela.


------------

// bu bir y�ntem
int sum_array(const int* ptr, int size)
{
    int sum = 0;
    while (size--)
    {
        sum += *ptr;
        ptr++;
    }
    return sum;
}

//di�eri
int sumArray(const int* a, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += a[i];

    return sum;
}

randomize();
set_random_array(a, SIZE);

printf("sum = %d\n", sum_array(a, SIZE));
printf("sum = %d\n", sumArray(a, SIZE));

------------------------------------ -
------------------------------------ -

son �rnek

//kendi parametresine, arg�man olarak g�nderilen de�erleri, 
//di�er fonksiyonu �a��r�rken arg�man olarak ekliyor.

double get_mean(const int* ptr, int size)
{
    return (double)sum_array(ptr, size) / size;
}



*/















