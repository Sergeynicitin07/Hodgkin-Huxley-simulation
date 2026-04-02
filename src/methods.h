#ifndef UNTITLED35_METHODS_H
#define UNTITLED35_METHODS_H
#include "struct.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


void f(double *x, double *fx, void *context,int *global);


void midpoint (Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context, int *global);


void rk4 (Solver *solver, double *x, double h,
          void (*f) (double *x, double *fx, void *context, int *global),
          void *context, int *global);


double Dormand_Prince (Solver *solver, double *x, double h,
                       void (*f) (double *x, double *fx, void *context, int *global),
                       void *context,  double tol, int *global);


double absolute (double x4, double x5);


void trapezoid (Solver *solver, double *x, double h,
                void (*f) (double *x, double *fx, void *context, int *global),
                void *context, int *global);


double Errors (double *x, double *y, Solver *solver);


#endif //UNTITLED35_METHODS_H