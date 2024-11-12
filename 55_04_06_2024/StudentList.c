#include "StudentList.h"
#include "Student.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct Node{
	Student s;	
	struct Node* pnext;
}Node;

void push_front(ListHandle, const Student*);
void pop_front(ListHandle);
void top(ListHandle, struct Student*);
size_t get_size(ListHandle);
int is_empty(ListHandle);
void make_empty(ListHandle);
void print_list(ListHandle);
ListHandle create_list(void);
void destory_list(ListHandle);
struct List { // gpfirst ve gsize b�t�n listeler taraf�ndan ortak kullan�lan de�i�kenler olduklar� i�in yap�n�n eleman� haline getirildi Handle tekni�i i�in
	Node* gpfirst;
	size_t gsize;
};
static Node* allocate_node(void) {
	Node* allocatedmem = (Node*)malloc(sizeof(Node));
	if (!allocatedmem) {
		fprintf(stderr, "Bellek yetersiz!");
		exit(EXIT_FAILURE);
	}
	return allocatedmem;
}
/*
size_t get_size(void) {
	return gsize;
}
*/

size_t get_size(ListHandle gs) {
	return gs->gsize; // art�k parametre de�i�keni olarak yollanm�� struct'�n i�erisindeki eleman�n�n tuttu�u size de�erini d�nd�r�yor.
}
/*
int is_empty(void) {
	return gpfirst == NULL;
	// return gsize == 0; ikisini de kullanabiliriz
}
*/
int is_empty(ListHandle bEmpty) {
	return bEmpty->gpfirst == NULL; // art�k parametre de�i�keni olarak yollanm�� struct'�n i�erisindeki elemana eri�erek dolu veya bo�lulu�unu d�nd�r�yor. boolean int
	// return bEmpty->gsize == 0; 
}

// Bir ka� fonksiyon �zerinde yap�lan de�i�iklikleri not ald�m geri kalan�n� almayaca��m ekstra bir de�i�iklik yok ise.
void print_list(ListHandle gpf) {
	for (Node* p = gpf->gpfirst; p != NULL; p = p->pnext) {
		print_student(&p->s);
	}
}

void top(ListHandle lh, struct Student* p) {
	if (is_empty(lh))
		exit(EXIT_FAILURE);
	*p = lh->gpfirst->s;
}

void push_front(ListHandle lh, const Student* p) { // bu fonksiyonu incelerken daha �nce olu�turulmu� node olmad���n� akl�nda tut. 0 Node ile ba�l�yorsun.
	// bu y�zden ilk olu�turdu�un Node'un(n1 diyelim) pnext'i NULL, 2. nodu olu�turdu�unda ise pnext'i n1, n1'in pnext'i NULL olacak.
	Node* pnewnode = allocate_node(); // yeni bir node allocate ettik
	pnewnode->s = *p;	// Student* p nesnesinin verileri yeni olu�turdu�umuz node i�eriisnde bulunan Student s nesnesine kopyaland�.
	pnewnode->pnext = lh->gpfirst; // yeni olu�turulan node'un pnextine (varsa) ilk node'un adresi verildi.
	lh->gpfirst = pnewnode; // yeni olu�turulan node listenin ilk node'u haline geldi�i i�in adresini gpfirstte tutuyoruz
	++lh->gsize; // art�k node yeni bir elemana sahip  oldu�u i�in gsize 1 artt�
}

void pop_front(ListHandle lh) {
	if (is_empty(lh)) {
		fprintf(stderr, "Pop hatasi");
		exit(EXIT_FAILURE);
	}
	
	Node* ptemp = lh->gpfirst; // burada gpfirst'�n adresini ptemp nesnesine kopyal�yorum.
	lh->gpfirst = lh->gpfirst->pnext; // gpfirst->pnext sonraki d���m�n adresini gpfirst nesnesine kopyal�yorum
	free(ptemp); // burada da free fonksiyonu ile allocate edilmi� dinamik bellek free ediliyor. 
	--lh->gsize;
}

void make_empty(ListHandle lh){
/*
	while (gpfirst != NULL) {
		Node* ptemp = gpfirst;
		gpfirst = gpfirst->pnext;
		free(ptemp);
	}
*/
	while (is_empty(lh))
	pop_front(lh);
}

ListHandle create_list(void){
	ListHandle alloclist = (ListHandle)malloc(sizeof(struct List)); // klasik malloc ve allocation status kontrol�
	if (!alloclist) {
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	alloclist->gpfirst = NULL; // allocate edilen struct'�n elemanlar�na ilk de�er verme i�lemi yap�l�yor.
	alloclist->gsize = 0; // allocate edilen struct'�n elemanlar�na ilk de�er verme i�lemi yap�l�yor.
	return alloclist; 
}
void destroy_list(ListHandle hl) {
	make_empty(hl); // handle'� kapatmadan �nce i�erisindeki d���mleri silmeliyiz.
	free(hl); // free() kullanma sebebimiz create_listte olu�turulan yap� dinamik �m�rl� bir nesne o y�zden free etmelyiiz.
}