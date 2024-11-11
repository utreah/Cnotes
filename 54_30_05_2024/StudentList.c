#include "StudentList.h"
#include "Student.h"
#include <stdlib.h>
#include <stdio.h>
typedef struct Node{
	Student s;	
	struct Node* pnext;
}Node;

void push_front(const Student*);
void pop_front(void);
void top(struct Student*);
size_t get_size(void);
int is_empty(void);
void make_empty(void);
void print_list(void);

static Node* gpfirst = NULL;
static size_t gsize = 0;
static Node* allocate_node(void) {
	Node* allocatedmem = (Node*)malloc(sizeof(Node));
	if (!allocatedmem) {
		fprintf(stderr, "Bellek yetersiz!");
		exit(EXIT_FAILURE);
	}
	return allocatedmem;
}

size_t get_size(void) {
	return gsize;
}

int is_empty(void) {
	return gpfirst == NULL;
	// return gsize == 0; ikisini de kullanabiliriz
}

void print_list(void) {
	for (Node* p = gpfirst; p != NULL; p = p->pnext) {
		print_student(&p->s);
	}
}

void top(struct Student* p) {
	if (is_empty())
		exit(EXIT_FAILURE);
	*p = gpfirst->s;
}

void push_front(const Student* p) { // bu fonksiyonu incelerken daha önce oluþturulmuþ node olmadýðýný aklýnda tut. 0 Node ile baþlýyorsun.
	// bu yüzden ilk oluþturduðun Node'un(n1 diyelim) pnext'i NULL, 2. nodu oluþturduðunda ise pnext'i n1, n1'in pnext'i NULL olacak.
	Node* pnewnode = allocate_node(); // yeni bir node allocate ettik
	pnewnode->s = *p;	// Student* p nesnesinin verileri yeni oluþturduðumuz node içeriisnde bulunan Student s nesnesine kopyalandý.
	pnewnode->pnext = gpfirst; // yeni oluþturulan node'un pnextine (varsa) ilk node'un adresi verildi.
	gpfirst = pnewnode; // yeni oluþturulan node listenin ilk node'u haline geldiði için adresini gpfirstte tutuyoruz
	++gsize; // artýk node yeni bir elemana sahip  olduðu için gsize 1 arttý
}

void pop_front(void) {
	if (is_empty()) {
		fprintf(stderr, "Pop hatasi");
		exit(EXIT_FAILURE);
	}
	
	Node* ptemp = gpfirst; // burada gpfirst'ün adresini ptemp nesnesine kopyalýyorum.
	gpfirst = gpfirst->pnext; // gpfirst->pnext sonraki düðümün adresini gpfirst nesnesine kopyalýyorum
	free(ptemp); // burada da free fonksiyonu ile allocate edilmiþ dinamik bellek free ediliyor. 
	--gsize;
}

void make_empty(void){
/*
	while (gpfirst != NULL) {
		Node* ptemp = gpfirst;
		gpfirst = gpfirst->pnext;
		free(ptemp);
	}
*/
	while (is_empty())
	pop_front();
}