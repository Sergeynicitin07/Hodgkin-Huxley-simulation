#include "methods.h"


double absolute (double x4, double x5) {
    if (x4 - x5 > 0.0)
        return (x4 - x5);
    else if (x5 - x4 > 0.0)
        return (x5 - x4);
    else
        return 0;
}


double errors (double *x, double *y, Solver *solver) {
    int i;

    for (i = 0; i < solver->n; i++) {
        solver->err[i] = absolute(x[i], y[i]);
    }
    double err_max = 0.0;
    for (i = 0; i < solver->n; i++) {
        if (solver->err[i] > err_max) {
            err_max = solver->err[i];
        }
    }
    return err_max;
}


void rk4 (Solver *solver, double *x, double h,
          void (*f) (double *x, double *fx, void *context, int *global),
          void *context, int *global){
    int i;
    f(x, (*solver).k1,
            context, global);
    for (i = 0; i < solver->n; i ++) {
        solver->xmid[i] = x[i] + (h * 0.5) * solver->k1[i];
    }
    f(solver->xmid, solver->k2,
            context, global);
    for (i = 0; i < solver->n; i ++) {
        solver->xmid[i] = x[i] + (h * 0.5) * solver->k2[i];
    }
    f(solver->xmid, solver->k3,
            context, global);
    for (i = 0; i < solver->n; i ++) {
        solver->xmid[i] = x[i] + h * solver->k3[i];
    }
    f(solver->xmid, solver->k4,
            context, global);
    for (i = 0; i < solver->n; i ++) {
        x[i] += (h / 6) * (solver->k4[i] + 2 * solver->k3[i]
                           + 2 * solver->k2[i] + solver->k1[i]);
    }
}


void midpoint (Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context, int *global){
    int j;
    f(x, (*solver).k1,
      context, global);
    for (j = 0; j < solver->n; j ++) {
        solver->xmid[j] = x[j] + (h * 0.5) * solver->k1[j];
    }
    f(solver->xmid, solver->k2,
      context, global);
    for (j = 0; j < solver->n; j ++) {
        x[j] += h * solver->k2[j];
    }
}


double Dormand_Prince (Solver *solver, double *x, double h,
                       void (*f) (double *x, double *fx, void *context, int *global),
                       void *context,  double tol, int *global) {
    int i;
    double factor;
    while(1) {
        f(x, (*solver).k1,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->xmid[i] = x[i] + (h * 0.2) * solver->k1[i];
        }
        f(solver->xmid, solver->k2,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->xmid[i] = x[i] + h * ((3.0 / 40.0) * solver->k1[i]
                                          + (9.0 / 40.0) * solver->k2[i]);
        }
        f(solver->xmid, solver->k3,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->xmid[i] = x[i] + h * ((44.0 / 45.0) * solver->k1[i]
                                          + (-56.0 / 15.0) * solver->k2[i]
                                          + (32.0 / 9.0) * solver->k3[i]);
        }
        f(solver->xmid, solver->k4,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->xmid[i] = x[i] + h * ((19372.0 / 6561.0) * solver->k1[i]
                                          + (-25360.0 / 2187.0) * solver->k2[i]
                                          + (64448.0 / 6561.0) * solver->k3[i]
                                          + (-212.0 / 729.0) * solver->k4[i]);
        }
        f(solver->xmid, solver->k5,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->xmid[i] = x[i] + h * ((9017.0 / 3168.0) * solver->k1[i]
                                          + (-355.0 / 33.0) * solver->k2[i]
                                          + (46732.0 / 5247.0) * solver->k3[i]
                                          + (49.0 / 176.0) * solver->k4[i]
                                          + (-5103.0 / 18656.0) * solver->k5[i]);
        }
        f(solver->xmid, solver->k6,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->xmid[i] = x[i] + h * ((35.0 / 384.0) * solver->k1[i]
                                          + (0) * solver->k2[i]
                                          + (500.0 / 1113.0) * solver->k3[i]
                                          + (125.0 / 192.0) * solver->k4[i]
                                          + (-2187.0 / 6784.0) * solver->k5[i]
                                          + (11.0 / 84.0) * solver->k6[i]);
        }
        f(solver->xmid, solver->k7,
                context, global);
        for (i = 0; i < solver->n; i++) {
            solver->x5[i] = x[i] + h * ((35.0 / 384.0) * solver->k1[i]
                                        + (500.0 / 1113.0) * solver->k3[i]
                                        + (125.0 / 192.0) * solver->k4[i]
                                        + (-2187.0 / 6784.0) * solver->k5[i]
                                        + (11.0 / 84.0) * solver->k6[i]);
        }
        for (i = 0; i < solver->n; i++) {
            solver->x4[i] = x[i] + h * ((5179.0 / 57600.0) * solver->k1[i]
                                        + (7571.0 / 16695.0) * solver->k3[i]
                                        + (393.0 / 640.0) * solver->k4[i]
                                        + (-92097.0 / 339200.0) * solver->k5[i]
                                        + (187.0 / 2100.0) * solver->k6[i]
                                        + (1.0 / 40.0) * solver->k7[i]);
        }

        double err_max = errors(solver->x4, solver->x5, solver);

        if (err_max < tol) {
            for (i = 0; i < solver->n; i++) {
                x[i] = solver->x5[i];
            }
        }
        if (err_max == 0.0)
            factor = 2.0;
        else
            factor = 0.9 * pow(tol / err_max, 0.2);

        if (factor > 2.0) factor = 2.0;
        if (factor < 0.1) factor = 0.1;

        h = h * factor;

        if (err_max < tol)
            break;
    }


    return h;

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