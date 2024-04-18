#ifndef NUTILITY_H
#define NUTILITY_H
// #define ISLEAP(y) ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
int isprime(int number);
int ndigit(int number);
void clear_input_buffer(void);
void put_star(void);
void set_array_random(int* p, int size);
void print_array(const int* p, int size);

#endif