#include <stdio.h>
#include "struct.h"
#include "methods.h"
#include "model.h"
#include <string.h>
#include <stdlib.h>
#include "great_app_test.h"
#include "trash.h"

/*
int main(int argc, char *argv[]) {
    int n = 4;
    Solver *solver = solver_unit(n);
    Params p;

    double h = 1e-5;
    double t = 0.0;
    double t_end = 1.0;
    char method[20] = "dp";
    // research
    if (argc > 1)
        strcpy(method, argv[1]);
    if (argc > 2)
        h = atof(argv[2]);
    if (argc > 3)
        p.Iext = -atof(argv[3]);
    p.Iext = -10.0;
    double tol = 1e-6;
    int global = 0;
    Test_slop *r = malloc(sizeof(Test_slop));
    Neural_data *j = malloc(sizeof(Neural_data));
    double x[4] = {0.0, 0.042, 0.608, 0.6};
    calculus (r, j, solver, x, h,
                   f,
                   &p, tol, t, t_end, &global);
    // big purge
    free(r);
    free(j);
}
*/



int main(int argc, char *argv[]) {
    int n = 4;
    Solver *solver = solver_unit(n);
    Params p;
    double h = 1e-3;
    double t = 0.0;
    double t_end = 100.0;
    char method[20] = "dp";
    // research
    if (argc > 1)
        strcpy(method, argv[1]);
    if (argc > 2)
        h = atof(argv[2]);
    if (argc > 3)
        p.Iext = -atof(argv[3]);
    p.Iext = -10.0;
    double tol = 1e-10;
    int global = 0;
    double h_long = h;
    double x[4] = {0.0, 0.042, 0.608, 0.6};
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
        }/*
        else if (strcmp(method, "trap") == 0) {
            trapezoid (solver, x, h, f, &p, &global);
            t += h;
        }*/
        else return 1;
    }
    //printf("calls %d\n", global);
    solver_free(solver);
    return 0;
}
