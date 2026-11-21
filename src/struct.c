#include "struct.h"
#include <stdlib.h>


Solver *solver_unit (int n){
    Solver *solver = (Solver *)malloc(sizeof(Solver));
    if (!solver) return NULL;

    solver->n = n;

    solver->tol = (double *)malloc(sizeof(double) * n);
    if (!solver->tol) return NULL;

    solver->Atol = (double *)malloc(sizeof(double) * n);
    if (!solver->Atol) return NULL;

    solver->Rtol = (double *)malloc(sizeof(double) * n);
    if (!solver->Rtol) return NULL;

    solver->k1 = (double *)malloc(sizeof(double) * n);
    if (!solver->k1) return NULL;

    solver->k2 = (double *)malloc(sizeof(double) * n);
    if (!solver->k2) return NULL;

    solver->k3 = (double *)malloc(sizeof(double) * n);
    if (!solver->k3) return NULL;

    solver->k4 = (double *)malloc(sizeof(double) * n);
    if (!solver->k4) return NULL;

    solver->k5 = (double *)malloc(sizeof(double) * n);
    if (!solver->k5) return NULL;

    solver->k6 = (double *)malloc(sizeof(double) * n);
    if (!solver->k6) return NULL;

    solver->k7 = (double *)malloc(sizeof(double) * n);
    if (!solver->k7) return NULL;

    solver->x4 = (double *)malloc(sizeof(double) * n);
    if (!solver->x4) return NULL;

    solver->Y_4 = (double *)malloc(sizeof(double) * n);
    if (!solver->Y_4) return NULL;

    solver->err = (double *)malloc(sizeof(double) * n);
    if (!solver->err) return NULL;

    solver->fx = (double *)malloc(sizeof(double) * n);
    if (!solver->fx) return NULL;

    solver->xmid = (double *)malloc(sizeof(double) * n);
    if (!solver->xmid) return NULL;

    solver->xarr = (double *)malloc(sizeof(double) * n);
    if (!solver->xarr) return NULL;

    solver->xideal = (double *)malloc(sizeof(double) * n);
    if (!solver->xideal) return NULL;

    solver->Y_5 = (double *)malloc(sizeof(double) * n);
    if (!solver->Y_5) return NULL;

    return solver;
}


void solver_free(Solver *solver) {
    if (!solver) return;

    free(solver->tol);
    free(solver->Atol);
    free(solver->Rtol);
    free(solver->k1);
    free(solver->k2);
    free(solver->k3);
    free(solver->k4);
    free(solver->k5);
    free(solver->k6);
    free(solver->k7);
    free(solver->x4);
    free(solver->Y_4);
    free(solver->Y_5);
    free(solver->err);
    free(solver->fx);
    free(solver->xmid);
    free(solver->xarr);
    free(solver->xideal);
    free(solver);
}


Ignominious *lord_structure (int n) {
    // в нашем разборе n = 401000
    Ignominious *lord = (Ignominious *)malloc(sizeof(Ignominious));
    if (!lord) return NULL;


    lord->n = n;

    lord->ignominious_current = (double *)malloc(sizeof(double) * n);
    if (!lord->ignominious_current) return NULL;
    lord->ignominious_time = (double *)malloc(sizeof(double) * n);
    if (!lord->ignominious_time) return NULL;

    lord->ignominious_voltage = (double *)malloc(sizeof(double) * n);
    if (!lord->ignominious_voltage) return NULL;

    return lord;
}




/*
double gNa = 155.2553676323;
double gK  = 54.6590169572;
double gL  = 0.3736733955;

double VNa = -108.1395566600;
double VK  = 1.6149168422;
double VL  = -12.4414069498;

double sn  = 1.6241988865;
double sm  = 2.5211965215;
double sh  = 1.7019432075;
*/









/*
double gNa = 7.557339023246625e+01;
double gK  = 3.390079288566587e+01;
double gL  = 1.762344149365385e-01;

double VNa = -1.254597334707633e+02;
double VK  = 2.794740462391533e+00;
double VL  = -2.247857433533663e+01;

double sn = 1.676449088702419e+00;
double sm = 2.393620401345924e+00;
double sh = 1.570285971029515e+00;
*/




double gNa = 7.557339023246625e+01;
double gK  = 3.391353682239303e+01;
double gL  = 1.763638645751135e-01;

double VNa = -1.254570628913517e+02;
double VK  = 2.794396210688431e+00;
double VL  = -2.247434770867406e+01;

double sn = 1.676417199246550e+00;
double sm = 2.392943686051596e+00;
double sh = 1.570427631097533e+00;








void lord_free(Ignominious *lord) {
    if (!lord) return;

    free(lord->ignominious_voltage);
    free(lord->ignominious_time);

    free(lord);

}
