#ifndef UNTITLED35_STRUCT_H
#define UNTITLED35_STRUCT_H


typedef struct {
    int n;
    double *tol;
    double *Atol;
    double *Rtol;
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


typedef struct {
    int n;
    double *ignominious_time;
    double *ignominious_voltage;
} Ignominious;


extern double sn;
extern double sm;
extern double sh;


extern double gNa;
extern double gK;
extern double gL;


extern double VNa;
extern double VK;
extern double VL;


extern double tau;


extern double resistance_input;


extern double v_rest;


Ignominious *lord_structure (int n);


Solver *solver_unit (int n);


void solver_free(Solver *solver);


void lord_free(Ignominious *lord);


#endif
