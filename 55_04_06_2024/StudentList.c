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
struct List { // gpfirst ve gsize bütün listeler tarafýndan ortak kullanýlan deðiþkenler olduklarý için yapýnýn elemaný haline getirildi Handle tekniði için
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
	return gs->gsize; // artýk parametre deðiþkeni olarak yollanmýþ struct'ýn içerisindeki elemanýnýn tuttuðu size deðerini döndürüyor.
}
/*
int is_empty(void) {
	return gpfirst == NULL;
	// return gsize == 0; ikisini de kullanabiliriz
}
*/
int is_empty(ListHandle bEmpty) {
	return bEmpty->gpfirst == NULL; // artýk parametre deðiþkeni olarak yollanmýþ struct'ýn içerisindeki elemana eriþerek dolu veya boþluluðunu döndürüyor. boolean int
	// return bEmpty->gsize == 0; 
}

// Bir kaç fonksiyon üzerinde yapýlan deðiþiklikleri not aldým geri kalanýný almayacaðým ekstra bir deðiþiklik yok ise.
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

void push_front(ListHandle lh, const Student* p) { // bu fonksiyonu incelerken daha önce oluþturulmuþ node olmadýðýný aklýnda tut. 0 Node ile baþlýyorsun.
	// bu yüzden ilk oluþturduðun Node'un(n1 diyelim) pnext'i NULL, 2. nodu oluþturduðunda ise pnext'i n1, n1'in pnext'i NULL olacak.
	Node* pnewnode = allocate_node(); // yeni bir node allocate ettik
	pnewnode->s = *p;	// Student* p nesnesinin verileri yeni oluþturduðumuz node içeriisnde bulunan Student s nesnesine kopyalandý.
	pnewnode->pnext = lh->gpfirst; // yeni oluþturulan node'un pnextine (varsa) ilk node'un adresi verildi.
	lh->gpfirst = pnewnode; // yeni oluþturulan node listenin ilk node'u haline geldiði için adresini gpfirstte tutuyoruz
	++lh->gsize; // artýk node yeni bir elemana sahip  olduðu için gsize 1 arttý
}

void pop_front(ListHandle lh) {
	if (is_empty(lh)) {
		fprintf(stderr, "Pop hatasi");
		exit(EXIT_FAILURE);
	}
	
	Node* ptemp = lh->gpfirst; // burada gpfirst'ün adresini ptemp nesnesine kopyalýyorum.
	lh->gpfirst = lh->gpfirst->pnext; // gpfirst->pnext sonraki düðümün adresini gpfirst nesnesine kopyalýyorum
	free(ptemp); // burada da free fonksiyonu ile allocate edilmiþ dinamik bellek free ediliyor. 
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
	ListHandle alloclist = (ListHandle)malloc(sizeof(struct List)); // klasik malloc ve allocation status kontrolü
	if (!alloclist) {
		fprintf(stderr, "Not enough memory");
		exit(EXIT_FAILURE);
	}
	alloclist->gpfirst = NULL; // allocate edilen struct'ýn elemanlarýna ilk deðer verme iþlemi yapýlýyor.
	alloclist->gsize = 0; // allocate edilen struct'ýn elemanlarýna ilk deðer verme iþlemi yapýlýyor.
	return alloclist; 
}
void destroy_list(ListHandle hl) {
	make_empty(hl); // handle'ý kapatmadan önce içerisindeki düðümleri silmeliyiz.
	free(hl); // free() kullanma sebebimiz create_listte oluþturulan yapý dinamik ömürlü bir nesne o yüzden free etmelyiiz.
}