#pragma once
#include "Student.h"
/*
	54. dosyadaki fonksiyonlarýn kaç tane parametre deðiþkeni var ise þu an hepsinin +1 daha fazla var.
		ListHandle adýnda bir type-alias oluþturduk. -> struct List*
		create_list ListHandle geri döndürüyor.
		destroy_list ise ListHandle alýyor.
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