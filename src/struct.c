#include "struct.h"
#include <stdlib.h>


Solver *solver_unit (int n){
    Solver *solver = (Solver *)malloc(sizeof(Solver));
    if (!solver) return NULL;

    solver->n = n;

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
    if (!solver->xarr) return NULL;

    solver->Y_5 = (double *)malloc(sizeof(double) * n);
    if (!solver->Y_5) return NULL;

    return solver;
}


void solver_free(Solver *solver) {
    if (!solver) return;

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