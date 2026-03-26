#include <stdio.h>
#include "struct.h"
#include "methods.h"
#include "model.h"
#include <string.h>
#include <stdlib.h>

/*
void copy (double *x, Solver *solver) {
    int i;
    for (i = 0; i < solver->n; i ++) {
        solver->xideal[i] = x[i];
    }
}


void calculus (Solver *solver, double *x, double h,
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
        copy(x, solver);
        t = 0.0;
        while (t < t_end) {
            rk4 (solver, solver->xideal, h, f, context, &global);
            t += h;
        }
        error = errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("h = %g error = %g calls = %d\n", h, error, global);

            break;
        }
    }

    printf("method midpoint\n");
    for (h = 0.5; h > 1e-5; h /= 2.0) {

        global = 0;
        t = 0.0;
        copy(x, solver);
        while (t < t_end) {
            midpoint (solver, solver->xideal, h, f, context, &global);
            t += h;
        }
        error = errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("h = %g error = %g calls = %d\n", h, error, global);
            break;
        }

    }

    printf("method Dormand_Prince\n");

    double eps = 1e-2;

    while (eps > 1e-15) {

        copy(x, solver);
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

        error = errors(solver->xideal, x_ref, solver);

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
        copy(x, solver);
        while (t < t_end) {
            trapezoid (solver, solver->xideal, h, f, context, &global);
            t += h;
        }

        error = errors(solver->xideal, x_ref, solver);

        if (error < tol) {
            printf("h = %g error = %g calls = %d\n", h, error, global);
            break;
        }
    }

}
*/

int main(int argc, char *argv[]) {
    int n = 4;
    Solver *solver = solver_unit(n);
    Params p;
    double h = 1e-2;
    double t = 0.0;
    double t_end = 100.0;
    char method[20] = "rk4";
    // research
    if (argc > 1)
        strcpy(method, argv[1]);
    if (argc > 2)
        h = atof(argv[2]);
    if (argc > 3)
	p.Iext = atof(argv[3]);
    double tol = 1e-3;
    int global = 0;
    double h_long = h;
    double x[4] = {0.0, 0.05, 0.06, 0.32};
    //calculus (solver, x, h, f, &p, tol, t_end);
    while (t < t_end) {
        printf("%lf %lf %lf %lf %lf\n",
               t, x[0], x[1], x[2], x[3]);
        if (strcmp(method, "rk4") == 0) {
            rk4 (solver, x, h, f, &p, &global);
            t += h;
        }
        else if (strcmp(method, "dp") == 0) {
            h_long = Dormand_Prince (solver, x, h_long, f, &p, tol, &global);
            t += h_long;
        }
        else if (strcmp(method, "mid") == 0) {
            midpoint (solver, x, h, f, &p, &global);
            t += h;
        }
        else if (strcmp(method, "trap") == 0) {
            trapezoid (solver, x, h, f, &p, &global);
            t += h;
        } else return 1;
    }
    //printf("calls %d\n", global);
    solver_free(solver);
    return 0;
}
