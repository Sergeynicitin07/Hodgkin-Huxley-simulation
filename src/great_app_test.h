#ifndef UNTITLED35_GREAT_APP_TEST_H
#define UNTITLED35_GREAT_APP_TEST_H
#include "struct.h"


typedef struct {
    double *data;
    int capacity;
    int rows;

} Test_slop;


typedef struct {
    double *data;
    int capacity;
    int rows;

} Neural_data;

// Инициализация
void init (Neural_data *n, double time, double h);


void push_neural (Neural_data *n, double h, double v);

// Инициализация
void initi (Test_slop *r, double time, double h);


void push_neurali (Test_slop *r, double h, double v);


void turn_in (Solver *solver, double *x, double *xbasa);


void turn_out (Solver *solver, double *x, double *xbasa);


double MAX (double a, double b);


void accuracy_calculus (Test_slop *r, Neural_data *n,  double tol, int *global, double *maxic, double h);


void calculus (Test_slop *r, Neural_data *n, Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context,  double tol, double t, double t_end, int *global, double as, double hk);


#endif //UNTITLED35_GREAT_APP_TEST_H
