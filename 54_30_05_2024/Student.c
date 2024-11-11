#include "Student.h"

Student* set_random_student(Student*);
void print_student(const Student*);
int cmp_student(const Student*, const Student*);

Student* set_random_student(Student* p) {
	// Yazýlarýn kopyalama iþlemlerini strcpy gibi fonksiyonlarla yapýyoruz. Sakin atama operatörü kullanma. 
	p->m_no = 100 + rand() % 2000 + 1;
	strcpy(p->m_name, rname()); 
	strcpy(p->m_surname, rfname());
	strcpy(p->m_town, rtown());
	set_random_date(&p->mbdate); // -> önceliði daha yüksek olduðu için mbdate'e eriþtik ve daha sonra bunun adresini gönderidk.
									// eðer bu þekilde yapmasaydýk p deðiþkeni Student* yapý türünden, set_random_date ise Data yapý türünden. Herhangi bir tür dönüþümü yok burada
										// tek yolu mbdate'in (Date yapý türünden) adresini yollamak.
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
// isim -> soyisim -> sehir -> dogum tarihi -> numara karþýlaþtýrma sýramýz bu þekilde 
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

	cmp_result = cmp_date(&s1->mbdate, &s2->mbdate); // Doðum tarihi karþýlaþtýrýlmasý
	if (cmp_result)
		return cmp_result;

	return s1->m_no - s2->m_no;
}