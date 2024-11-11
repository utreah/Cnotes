#include "Student.h"

Student* set_random_student(Student*);
void print_student(const Student*);
int cmp_student(const Student*, const Student*);

Student* set_random_student(Student* p) {
	// Yaz�lar�n kopyalama i�lemlerini strcpy gibi fonksiyonlarla yap�yoruz. Sakin atama operat�r� kullanma. 
	p->m_no = 100 + rand() % 2000 + 1;
	strcpy(p->m_name, rname()); 
	strcpy(p->m_surname, rfname());
	strcpy(p->m_town, rtown());
	set_random_date(&p->mbdate); // -> �nceli�i daha y�ksek oldu�u i�in mbdate'e eri�tik ve daha sonra bunun adresini g�nderidk.
									// e�er bu �ekilde yapmasayd�k p de�i�keni Student* yap� t�r�nden, set_random_date ise Data yap� t�r�nden. Herhangi bir t�r d�n���m� yok burada
										// tek yolu mbdate'in (Date yap� t�r�nden) adresini yollamak.
	return p;
}
void print_student(const Student* p1) {
	printf("Student Full Name: [%s %s]\n", p1->m_name, p1->m_surname);
	printf("Student Number: %d\n", p1->m_no);
	printf("Student Town: %s\n", p1->m_town);
	printf("Student BirthDay: ");
	print_date(&p1->mbdate);
	put_star();
}
// isim -> soyisim -> sehir -> dogum tarihi -> numara kar��la�t�rma s�ram�z bu �ekilde 
int cmp_student(const Student* s1, const Student* s2) {
	int cmp_result = strcmp(s1->m_name, s2->m_name);
	if (cmp_result)
		return cmp_result;
	cmp_result = strcmp(s1->m_surname, s2->m_surname);
	if (cmp_result)
		return cmp_result;	
	cmp_result = strcmp(s1->m_town, s2->m_town);
	if (cmp_result)
		return cmp_result;

	cmp_result = cmp_date(&s1->mbdate, &s2->mbdate); // Do�um tarihi kar��la�t�r�lmas�
	if (cmp_result)
		return cmp_result;

	return s1->m_no - s2->m_no;
}