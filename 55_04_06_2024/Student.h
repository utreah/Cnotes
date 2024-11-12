#pragma once
#include "nUtility.h"
/*
	#define "Date.h"
	struct Student {
		struct Date mbdate;	
	};
	Eðer date.h include etmiþ olmasaydýk bu bildirim incomplete olacaðý için
		student.h'nin include edildiði tüm dosyalarda sentaks hatasý oluþacaktý.

	Þöyle bir sorun var. student.h'yý include eden tüm dosyalara ayný zamanda Date.h dosyasý da include edilmiþ olacak.
		Ayný zamanda, Date.h içinde bulunan diðer baþlýk dosyalarý da include edilecek. Bu Compile Time'ýn uzamasýna sebep veriyor çünkü
			derleyici her bildirimin tek tek üstünden geçiyor.
	Baþka bir problem ise, Date.h içerisinde yapýlan herhangi bir deðiþiklik Date.h'i bünyesinde bulunduran diðer dosyalarýnda yeniden derlenmesi
		gerekmesi zorunluluðunu doðuracaktýr.

	Gereksiz yere baþlýk dosyasý include etme! 
		Sadece mecbur isen include et. 
	
	Eðer yapý türünün nesnesi, fonksiyonun parametresi veya geri dönüþ deðeri yapý türünün pointer nesnesi durumunda ise Incomplete type olarak býrakýlabilir.
		Bu sayede baþlýk dosyasýný include etme zorunluluðu kalkar.
			struct Student{
				Date* dateptr;	
			};

			Date* foo(Date* p1);
*/
#include "Date.h"
#define MAX_NAME_LENGTH 20
#define MAX_SURNAME_LENGTH 25
#define MAX_TOWN_LENGTH 30
typedef struct Student {
	int	 m_no;
	char m_name[MAX_NAME_LENGTH + 1];
	char m_surname[MAX_SURNAME_LENGTH + 1];
	char m_town[MAX_TOWN_LENGTH + 1];
	Date mbdate;
}Student;


Student* set_random_student(Student*);
void print_student(const Student*);
int cmp_student(const Student*, const Student*);
