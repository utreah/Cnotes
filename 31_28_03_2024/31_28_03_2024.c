/*
int x = 10, * p1 = &x, * p2 = p1, * p3 = p2;
++* p1; // hepsi x in kendisi anlamýnda ve ++ operatörü ile iþleme girmiþ.
++* p2;
++* p3;
bu x i üç kere artýrýyor.x = 13 oluyor.

POINTER NE ÝÞE YARIYOR.

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

Yukarýdaki örnekte x en son kaçtýr ?
x halen 10 dur.çünkü fonksiyona gönderilen x ve daha sonrasýnda a olarak
fonksiyonda iþleme sokulan farklý bir obje, x deðil.
adreslere bakýlýrsa eðer görülür.Call by value.


void func(int a)
{
	a = 23;
	printf("&a = %p\n", a); // a nýn adresi
}

int main()
{
	int x = 10;
	func(x);
	printf("x = %d\n", x);
	printf("&x = %p\n", x); // x in adresi ve farklý objeler bunlar.
}

a ve x farklý adreslerde olduðunu yazar.

--------------------------------------


C de eðer bir yerel deðiþkenin baþka bir fonksiyon tarafýndan deðiþtirilmesini istiyorsak
bu deðiþkenin kendisini fonksiyona göndermemiz gerekiyor.
Baþka dillerde kullanýmý daha kolay olabilir fakat C de pointer semantiði ile
yapýlýyor bu iþ.Call by reference.

Neden call by reference?
1- Bir fonksiyona deðer iletmek için  kullanýlabilir. Bu da ikiye ayrýlýyor.
    -Pass by value -> sadece deðeri gönderir ve deðiþken üzerindeki deðeri deðiþmez(statik deðil ise)
    -Pass by reference(adresi göndermek) -> deðiþkenin adresini gönderir ve bu sayede deðiþkenin deðeri set edilir(dinamik olsa bile)
2- Geri dönüþ deðeri yerine kullanýlabilmesi.Bir adres gönderip hesaplatýp ayný adresteki nesneye yazabilir. -> geri dönüþ deðeri 
    türü kullanmak yerine adres deðiþkenleri ile fonksiyonda hesaplanan deðer bir deðiþkene
    atanabilir ve kullanýlabilir. (return'ü int olan bir deðiþkeni void yapýp adres türünden bir veri türü ile yapýlabilir)
    void calculate_average(int a, int b, double* avg) -> *p = (a+b)/2.;
    int calculate_average(int a, int b) -> return (a+b)/2.;
        -Burada pointer ile yapýlan görüntü kirliliði oluþturabilir çünkü deðeri bir deðiþkende tutma zorunluluðu var(kiþisel görüþ)
        -Geri dönüþ deðeri olan fonksiyonlarda bir adresteki nesneye yazýlýr. Bu da maliyet konusunu ortaya çýkarýr. sizeof deðeri
            4, 8, 16 gibi küçük deðerler ise bu return'ün yaptýðý kopyalamada büyük bir maliyet oluþturmuyor. int double gibi türlerde
            sýkýntý yok. user-defined types'ta maliyet problem olabilir.

            typedef struct{
            int row,col;
            int a[20][20];
            }Matrix;

            void add_matrix(Matrix *presult, Matrix p1, Matrix p2)
            ....

            Matrix x,y;
            Matrix z;
            add_matrix(&z,x,y); // burada matrix'e x ve y'yi blok kopyalama ile yolluyoruz. Bunun yerine direkt adreslerini yollayýp öyle
                                    iþleme tabii tutabiliriz bu da maliyeti azaltýr.
            void add_matrix(Matrix *presult, const Matrix* p1, const Matrix* p2); // const keywordünü öðrenecez. Anlamý bu deðiþkende deðiþiklik
                                                                                    yapmayacaðým onu sadece read-only olarak kullanýcam gibi bir anlamý var.
                                                                                    32. derste öðrenicez bunu.
            add_matrix(&z,&x,&y); // iki kod bir birinden çok farklý.

            // mesela bu örnekte matrix user-defined type 808 bytelýk alan kaplýyor. Burada return yerine bir address yolladýðýmýzda
                sadece 4 byte'lýk bir alan kullanýyoruz ve bu da maliyet açýsýndan daha iyi.

------------------------------------------------
double get_circle(double radius)
        return 3.14 *radius*radius


    double r = 23.4242
    double area

    area = get_circle(r)
    printf area

    yukarýdaki call by value

    --------------

    Call by reference ile yazarsak


    void get_circle(double radius,int *p_area)
        *p_area = 3.14 * radius * radius


    double r = 23.4242
    double area

    get_circle(r,&area)
    printf area

    // burada gönderdiðim area deðiþkenine atadý.

        Bu tip basit iþlemlerde call by value seçilebilir.
    Hesaplanacak deðer tamsayý veya reel sayý ise, call by reference yöntemi
    biraz daha karmaþýk hale getiriyor iþi.
    Call by value burada doðru tercih olabilir.


    AMA !
    Hesaplanacak deðer bellekte 50 byte 100 byte 200 byte yer kaplýyorsa,
    iki yöntem arasýnda çok büyük bir maliyet farký var.
    Assembly seviyesinde
    çaðrýlan fonksiyonun geri dönüþ deðeri geçici bir nesnede tutuluyor.
    bizde bu geçici nesneden x = func() gibi ifadeyle kendi nesnemize aktarýyoruz.
    sonra bu temp nesnede siliniyor.
    Yani 2 adet bellek kopyalama var.
    1. return deðerinin temp alanýna yazýmasý
    2. çaðýran kodun return deðerini kendi deðiþkenine aktarmasý.

    Burada Call by reference þeklinde kullanýlmasý çok daha iyidir.
    2.26 da struct yazýyor ve gösteriyor.ben yazmayacaðým.

    2 adet 1608Byte alan kopyalamak yerine 4 bytelýk bir pointer adresi yazýyoruz.
    Çok ciddi bir fark.

    AYný zamanda birden fazla deðeri deðiþtirebiliriz bu yöntemle.

    func(a,b,c,&d,&e,&f)  mesela burada d e f deðiþkenleri tamamen deðiþtirilip
    main functiondan eriþilebilir


------------------------------------------------

3- Dizi ileteceksek bunun tek yolu fonksiyonun parametre deðiþkeni pointer olmalý. hem paratmetre hemde geridönüþ deðeri pointer olabilir.dizi olamaz.
    Dizi gibi görünebilir.

4 - Fonksiyon birden fazla deðer iletecekse/döndürmesi gerekiyor ise, yani kaç tane deðer iletecekse
    void get_values(double x, double y, double *alpha, double *beta, double *gama); // bu fonksiyonda birden fazla iþlem yapýlacak ve
    gönderilen adresteki nesnelere yapýlan iþlemin cevaplarý set edilecek. onlarýn adreslerini alýp iþleme sokabilir.
Aþaðýdaki gibi yapýlýr.

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

iþte burada x = 100 görülür.

------------------------------------------------



Örnek
mesela iki deðiþkeni takas yapacaðým


int a, b;
printf("iki degisken girin : ");
(void)scanf("%d%d", &a, &b);


printf("a = %d    b = %d", a, b);


int temp = a;
a = b;
b = temp;


printf("a = %d    b = %d", a, b);


Yukarýdaki takas iþlemi gibi iþlemleri sýk sýk yapacaksam eðer,
bunu kod tekrarýný engellemek ve daha taþýnabilir bir kod olmasý amacýyla
function haline getirmek daha mantýklý.


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


Yukarýdaki kod x ile y nin yerini deðiþtirmez. :D
Çünkü a ve b, x ve y deðil.


------



Örnek
mesela iki deðiþkeni takas yapacaðým


int a, b;
printf("iki degisken girin : ");
(void)scanf("%d%d", &a, &b);


printf("a = %d    b = %d", a, b);


int temp = a;
a = b;
b = temp;


printf("a = %d    b = %d", a, b);


Yukarýdaki takas iþlemi gibi iþlemleri sýk sýk yapacaksam eðer,
bunu kod tekrarýný engellemek ve daha taþýnabilir bir kod olmasý amacýyla
function haline getirmek daha mantýklý.


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


Yukarýdaki kod x ile y nin yerini deðiþtirmez. :D
Çünkü a ve b, x ve y deðil.


----------------------------------------------------------------------------
*/
/*
Fonksiyonun parametre deðiþkeni olan pointer eðer deðer deðiþtirme iþlemi yapabiliyor ise bu fonksiyonlara;
-Mutator, -Setter, -Set function denir.
void func(T *p); // out param
Fakat fonksiyonun parametresi const Type * þeklinde ise o deðiþkenin adresinde deðiþiklik yapmama garantisi veriyor ve bu fonksiyonlara;
-Accessor, -Getter, -Get function denir.
void bar(const T * p); // in param

DÝKKAT
- Bir fonksiyonun parametresi dizi olamaz
- Bir fonksiyonun geri dönüþ deðeri dizi olamaz.
yani, bir fonksiyonun bir fonksiyona dizi göndermesi ne olursa olsun adres yoluyla olmalý.
int bar(int* param);
int foo(int param);
int main(void)
{
    int a[5] = { 1,2,3,4,5 };
    //foo(a); -> bu þekilde diziyi foo fonksiyonuna yollayamayýz. Çünkü array decaydan dolayý 0 indisli elemanýn adresini yolluyoruz.
    bar(a); // -> bu þekilde yollanabilir çünkü array decayden dolayý adresini yolluyoruz ve fonksiyonun parametresi pointer deðiþken.
}

----------------------------------------------------------------------------

        ----------------------------------------------------- DÝZÝLER VE POINTERLAR -----------------------------------------------------
                                                                POINTER ARÝTMETÝÐÝ
-    C DÝLÝNDE
-    bir adresle bir tamsayý toplanabilir.                                      (adres + n)     == adres
-    bir tamsayý ile bir adres toplanabilir.                                    (n + adres)     == adres
-    bir adresten bir tamsayý çýkartýlabilir.                                   (adres - n)     == adres
-    bir tamsayýdan bir adres ÇIKARTILAMAZ !!!                                  (n - adres)     != adres
-    bir adresten baþka bir adres çýkartýlabilir. deðeri iþaretli tamsayýdýr.   (adres - adres) == adres(signed)
-    bir adres ile baþka bir adres TOPLANAMAZ !!!                               (adres + adres) != adres

int main(void)
{
    int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
    int *p;


    a + 5; // geçerli 
    3 + p; // geçerli
    p - 2; // geçerli
    3 - a; // GEÇERSÝZ
    2 - p; // GEÇERSÝZ
    p + a; // GEÇERSÝZ
}

    elemanlarýn bellekteki yerlerine bakýlabilir.
    her adres arasý sizeof(Type) kadar fark var. Mesela bir adres ABC04 ise diðer adres ABC08 olur(int için)
    double olsaydý 8 byte
    int 4 byte
    char 1 byte

    Bir nesnenin adresine 1 toplarsak, ayný türden bir sonraki nesnenin adresini elde etmiþ oluruz.
    Bir nesnenin adresine 1 çýkarýrsak,ayný türden bir önceki nesnenin adresini elde etmiþ oluruz.
    &a[5]  ile  a + 5 ayný ifade // çünkü dizilerin ardý ardýna sýralanmýþ olmasý garantisi var. a bir adres ve 5 bir tam sayý bu yüzden
                                    a + 5 dediðimiz zaman a'nýn 5. indisinin adresine iþaret eder.
    yani
    &a(n)  ile    a + n ayný
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

    i[a]  bu ifade ile a[i] aynýdýr
    [] subscript operatörü a[i] ifadesini *(a+i) ye çeviriyor.
    i[a] == *(i + a) // a[i] == *(a + i)

    p = adres olarak referans alalým;
        p++;//bir sonrakine geçiyor bu ifade ya da p = p+1; ya da p+=1;
    int a[10] == {0, 1, 2, 3, 4, 5, 6, 7, 8, 9,};
    int* ptr = a + 5;
    printf("%d", *(ptr + 4)); // burada sentaks hatasý yok 9 numaralý indisteki deðeri yazdýrýr. UB yok.
    printf("%d", *(ptr + 7)); // burada sentaks hatasý yok, çalýþýr fakat *(ptr + 7)'ye eriþmeye çalýþýr isem UB VAR. Ekrana yazdýrmak UB deðil.
-----------------------------------------------------
    TEKRAR
    x[y]  -> derleyici subscript operatörünü görünce
    *(x + y) ye çevirir bunu
    yani
    x[y]  ile y[x] ayný ifade

    x[y] = *(x+y)  aþaðýdaki ile ayný.
    x[x] = *(y+x)
-----------------------------------------------------
    int x = 10;	// 1 elemanlý bir array gibi düþünülebilir.
    ++(&x)[0];  // x = 11
    ++*(&x+0); // x = 12
-----------------------------------------------------
                                                           SUBSCRIPT OPERATORU
- En yüksek öncelik seviyesinde(1. sýrada) -> soldan saða 
int main(void)
{
    int a[10] = { 0,1,2,3,4,5,6,7,8,9};
    int *ptr = a + 5;

    printf("%d\n",*ptr);   // 5
    printf("%d\n",ptr[0]);  // 5
    printf("%d\n",ptr[3]);  // 8
    printf("%d\n",ptr[-2]);  // 3
    printf("%d\n",*(ptr - 2));  // 3
    // Bu iþlemlerde diziyi taþýrýrsak bu Undefined Behavior.
    // mesela ptr[-15] bir sentaks hatasý deðil ama bir UB.

}
ptr, a isimli bir dizinin bir elemanýný göstermektedir.
    ptr nin gösterdiði dizi elamanýnýn indexi nedir
    ptr - a dýr.


    ptr, a isimli bir dizinin 5 indisli elemanýný gösteriyor. ptr ?
    ptr = a + 5 tir


    ================================================


    p[n] == *(p + n)
    p[-2] == *(p - 2)
    &p[n] == p + n
    *p = p[0]
    ================================================


    int x = 10;	// 1 elemanlý bir array gibi düþünülebilir.
    ++(&x)[0];  // x = 11
    ++*(&x+0); // x = 12
   ================================================
   - Dizileri fonksiyonlara gönderirken adresleri ve boyutlarý gönderilmeli.
   - Eðer dizinin boyutunu sizeof(arr) / sizeof(arr[0]) ile fonksiyonda hesaplamaya çalýþýrsak, sizeof compile timeda yapýldýðý için
        arr dizisini pointer olarak görecek(4 byte) ve arr[0] da int türü olduðu için 4 byte olarak gelecek ve cevap 1 olacak. BU YÜZDEN BU YANLIÞ!
        void func(int* arr)
            sizeof(arr) / sizeof(arr[0]); // bu yanlýþtýr!
        void bar(int* arr, int size) // int yerine size_t kullanmayý anlatacak necati hoca ileride 
    - 
// daha çok tercih edilen
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

	DÝKKAT!
	print_array de pointer olarak gönderilen nesne kesinlikle const keyword ü ile nitelenmeli.
	Yapýlmazsa büyük hata olur. Mülakatlarda çok dikkat ediyorlar.


	print_array(a,5);  // ilk 5 eleman
	print_array(a+5,3);  // 5,6,7 elemanlarýný çaðýrýr.
	print_array(a+5,3);  // 5,6,7 elemanlarýný çaðýrýr.
	print_array(a+SIZE-5,5 );  // son 5 elemanýnýn deðeri.SIZE büyüklüðünü gösteren makro olsun mesela.


	------------

	// bu bir yöntem
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

	//diðeri
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

	son örnek

	//kendi parametresine, argüman olarak gönderilen deðerleri, 
	//diðer fonksiyonu çaðýrýrken argüman olarak ekliyor.

	double get_mean(const int * ptr , int size)
	{
		return (double)sum_array(ptr,size) / size;
	}




	


}// daha çok tercih edilen
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

DÝKKAT!
print_array de pointer olarak gönderilen nesne kesinlikle const keyword ü ile nitelenmeli.
Yapýlmazsa büyük hata olur.Mülakatlarda çok dikkat ediyorlar.


print_array(a, 5);  // ilk 5 eleman
print_array(a + 5, 3);  // 5,6,7 elemanlarýný çaðýrýr.
print_array(a + 5, 3);  // 5,6,7 elemanlarýný çaðýrýr.
print_array(a + SIZE - 5, 5);  // son 5 elemanýnýn deðeri.SIZE büyüklüðünü gösteren makro olsun mesela.


------------

// bu bir yöntem
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

//diðeri
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

son örnek

//kendi parametresine, argüman olarak gönderilen deðerleri, 
//diðer fonksiyonu çaðýrýrken argüman olarak ekliyor.

double get_mean(const int* ptr, int size)
{
    return (double)sum_array(ptr, size) / size;
}



*/















