#include "rubbish.h"
#include "great_app_test.h"
#include <stdlib.h>
#include "struct.h"
#include "methods.h"
#include "model.h"







// Здесь лежат не пошедшие дальше наработки







/*
void copy1 (double *x, Solver *solver) {
    int i;
    for (i = 0; i < solver->n; i ++) {
        solver->xideal[i] = x[i];
    }
}


void calculus1 (Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context,  double tol, double t_end) {
    int i;
    double h_local = h;

    // ideal case
    double toli = 1e-8;
    int global;
    double error;
    double x_ref[4];
    for (i = 0; i < solver->n; i++)
        x_ref[i] = x[i];

    double h_ref = 1e-4;
    double t = 0.0;
    int global_ref = 0;

    double h_tmp = h_ref;

    while (t < t_end) {
        h_tmp = Dormand_Prince(solver, x_ref, h_tmp, f, context, toli, &global_ref);
        t += h_tmp;
    }

    printf("method rk4\n");
    for (h = 0.5; h > 1e-6; h /= 2.0) {

        global = 0;
        copy1(x, solver);
        t = 0.0;
        while (t < t_end) {
            rk4 (solver, solver->xideal, h, f, context, &global);
            t += h;
        }
        error = Errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("h = %g error = %g calls = %d\n", h, error, global);

            break;
        }
    }

    printf("method midpoint\n");
    for (h = 0.5; h > 1e-5; h /= 2.0) {

        global = 0;
        t = 0.0;
        copy1(x, solver);
        while (t < t_end) {
            midpoint (solver, solver->xideal, h, f, context, &global);
            t += h;
        }
        error = Errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("h = %g error = %g calls = %d\n", h, error, global);
            break;
        }

    }

    printf("method Dormand_Prince\n");

    double eps = 1e-2;

    while (eps > 1e-15) {

        copy1(x, solver);
        t = 0.0;
        global = 0;


        while (t < t_end) {


            h_local = Dormand_Prince(
                    solver, solver->xideal,
                    h_local,
                    f, context,
                    eps,
                    &global
            );

            if (h_local < 1e-14)
                break;

            t += h_local;
        }

        error = Errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("eps = %g error = %g calls = %d\n", eps, error, global);
            break;
        }

        eps /= 10.0;
    }
    printf("method trapezoid\n");
    for (h = 0.5; h > 1e-12; h /= 2.0) {

        global = 0;
        t = 0.0;
        copy1(x, solver);
        while (t < t_end) {
            trapezoid (solver, solver->xideal, h, f, context, &global);
            t += h;
        }

        error = Errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("h = %g error = %g calls = %d\n", h, error, global);
            break;
        }
    }

}




void trapezoid (Solver *solver, double *x, double h,
                void (*f) (double *x, double *fx, void *context, int *global),
                void *context, int *global) {
    int i;
    // must to have new x[...]
    for (i = 0; i < solver->n; i++) {
        (*solver).xarr[i] = x[i];
    }
    // rk4 (solver, solver->xarr, h, f, context, &global);
    f(solver->xarr, solver->k1,
      context, global);

    for (i = 0; i < solver->n; i++)
        solver->xarr[i] = x[i] + h * solver->k1[i];
    f(solver->xarr, solver->k2,
      context, global);

    for (i = 0; i < solver->n; i++) {
        x[i] = x[i] + (h / 2) * (solver->k1[i] + solver->k2[i]);
    }
}

 double absolute (double x4, double x5) {
    if (x4 - x5 > 0.0)
        return (x4 - x5);
    else if (x5 - x4 > 0.0)
        return (x5 - x4);
    else
        return 0;
}
 */



