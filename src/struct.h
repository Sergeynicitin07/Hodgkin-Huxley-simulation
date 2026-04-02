#ifndef UNTITLED35_STRUCT_H
#define UNTITLED35_STRUCT_H


typedef struct {
    int n;
    double *k1;
    double *k2;
    double *k3;
    double *k4;
    double *k5;
    double *k6;
    double *k7;
    double *x4;
    double *Y_4;
    double *Y_5;
    double *err;
    double *fx;
    double *xmid;
    double *xarr;
    double *xideal;
}
Solver;


Solver *solver_unit (int n);


void solver_free(Solver *solver);


#endif
