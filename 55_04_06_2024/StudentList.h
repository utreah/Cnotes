#pragma once
#include "Student.h"
/*
	54. dosyadaki fonksiyonlar�n ka� tane parametre de�i�keni var ise �u an hepsinin +1 daha fazla var.
		ListHandle ad�nda bir type-alias olu�turduk. -> struct List*
		create_list ListHandle geri d�nd�r�yor.
		destroy_list ise ListHandle al�yor.
*/
struct List;
typedef struct List* ListHandle;
	void push_front(ListHandle, const Student*);
	void pop_front(ListHandle);
	void top(ListHandle, struct Student*);
	size_t get_size(ListHandle);
	int is_empty(ListHandle);
	void make_empty(ListHandle);
	void print_list(ListHandle);
	ListHandle create_list(void);
	void destroy_list(ListHandle);