#ifndef NUTILITY_H
#define NUTILITY_H
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
// #define ISLEAP(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
#define ASIZE(a) (sizeof(a) / sizeof(a[0]))
#define relem(a) (a[rand() % ASIZE(a)]) //random elem
int isprime(int number);
int ndigit(int number);
void clear_input_buffer(void);
void put_star(void);
void set_array_random(int* p, size_t size);
void print_array(const int* p, size_t size);
int* create_array(int n);
void randomize();
void sort_array(int* p, size_t size);
int icmp(const void* vp1, const void* vp2);
void sgets(char* p);
void swap(int* a, int* b);
void reverseArray(int* p, size_t size);
int* get_array_max(const int* p, size_t size);
int* get_array_min(const int* p, size_t size);
void selection_sort(int* p, size_t size);
void gswap(void* vp1, void* vp2, size_t size);
const char* rname(void);
const char* rfname(void);
const char* rtown(void);
#endif