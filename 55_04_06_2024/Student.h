#pragma once
#include "nUtility.h"
/*
	#define "Date.h"
	struct Student {
		struct Date mbdate;	
	};
	E�er date.h include etmi� olmasayd�k bu bildirim incomplete olaca�� i�in
		student.h'nin include edildi�i t�m dosyalarda sentaks hatas� olu�acakt�.

	��yle bir sorun var. student.h'y� include eden t�m dosyalara ayn� zamanda Date.h dosyas� da include edilmi� olacak.
		Ayn� zamanda, Date.h i�inde bulunan di�er ba�l�k dosyalar� da include edilecek. Bu Compile Time'�n uzamas�na sebep veriyor ��nk�
			derleyici her bildirimin tek tek �st�nden ge�iyor.
	Ba�ka bir problem ise, Date.h i�erisinde yap�lan herhangi bir de�i�iklik Date.h'i b�nyesinde bulunduran di�er dosyalar�nda yeniden derlenmesi
		gerekmesi zorunlulu�unu do�uracakt�r.

	Gereksiz yere ba�l�k dosyas� include etme! 
		Sadece mecbur isen include et. 
	
	E�er yap� t�r�n�n nesnesi, fonksiyonun parametresi veya geri d�n�� de�eri yap� t�r�n�n pointer nesnesi durumunda ise Incomplete type olarak b�rak�labilir.
		Bu sayede ba�l�k dosyas�n� include etme zorunlulu�u kalkar.
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
