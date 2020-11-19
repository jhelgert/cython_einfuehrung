#ifndef OUR_SIMPLE_C_LIB_H
#define OUR_SIMPLE_C_LIB_H

typedef struct{
	double* data;
	int size;
} c_vec;

c_vec* clib_init(int n);
void clib_fill(c_vec* v);
void clib_print(c_vec* v);
double clib_sum(c_vec* v);
void clib_free(c_vec* v);

#endif // OUR_SIMPLE_C_LIB_H