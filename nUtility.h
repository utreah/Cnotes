#ifndef NUTILITY_H
#define NUTILITY_H
#define _CRT_SECURE_NO_WARNINGS

// #define ISLEAP(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
int isprime(int number);
int ndigit(int number);
void clear_input_buffer(void);
void put_star(void);
void set_array_random(int* p, int size);
void print_array(const int* p, int size);
int* create_array(int n);
void randomize();
void sort_array(int* p, int size);
int icmp(const void* vp1, const void* vp2);
void sgets(char* p);
void swap(int* a, int* b);
void reverseArray(int* p, int size);
int* get_array_max(const int* p, int size);
int* get_array_min(const int* p, int size);
void selection_sort(int* p, int size);
#endif