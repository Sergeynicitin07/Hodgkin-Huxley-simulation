#include "great_app_test.h"
#include <stdlib.h>
#include "methods.h"
#include "model.h"

// Инициализация
void init (Neural_data *n, double time, double h) {
    n->capacity = (int) (time / h);
    n->rows = 0;
    n->data = malloc(n->capacity * 2 * sizeof(double ));
}


void push_neural (Neural_data *n, double h, double v) {
    if (n->rows >= n->capacity) {
        n->capacity *= 2;
        double *dat = realloc(n->data, n->capacity * 2 * sizeof(double));
        n->data = dat;
    }
    *(n->data + n->rows * 2 + 0) = h;
    *(n->data + n->rows * 2 + 1) = v;

    n->rows++;
}

// Инициализация
void initi (Test_slop *r, double time, double h) {
    r->capacity = (int) (time / h);
    r->rows = 0;
    r->data = malloc(r->capacity * 2 * sizeof(double));
}


void push_neurali (Test_slop *r, double h, double v) {
    if (r->rows >= r->capacity) {
        r->capacity *= 2;
        double *dat = realloc(r->data, r->capacity * 2 * sizeof(double));
        r->data = dat;
    }
    *(r->data + r->rows * 2 + 0) = h;
    *(r->data + r->rows * 2 + 1) = v;

    r->rows++;
}


void turn_in (Solver *solver, double *x, double *xbasa) {
    int i;
    for (i = 0; i < solver->n; i++) {
        xbasa[i] = x[i];
    }
}


void turn_out (Solver *solver, double *x, double *xbasa) {
    int i;
    for (i = 0; i < solver->n; i++) {
        x[i] = xbasa[i];
    }

}

// Максимум двух чисел
double MAX (double a, double b) {
    if (a >= b) return a;
    else
        return b;
}


void accuracy_calculus (Test_slop *r, Neural_data *n,  double tol, int *global) {
    int i = 0;
    int j = 0;

    double v_r1 = r->data[i * 2 + 1];
    // Найдем ошибку при t = 0
    double time_slop = MAX(absolute(v_r1, n->data[1]), 0.0);

    for (i = 1; i < r->rows; i ++) {
        double t_r = r->data[i * 2 + 0];
        double v_r = r->data[i * 2 + 1];

        while ( n->data[(j + 1) * 2] < t_r && j < n->rows - 1) {
            j++;
        }
        double t1 = n->data[j * 2 + 0];
        double v1 = n->data[j * 2 + 1];

        // t_r уже меньше t2
        double t2 = n->data[(j + 1) * 2 + 0];
        double v2 = n->data[(j + 1) * 2 + 1];
        if (t1 <= t_r && t2 >= t_r) {
            if (absolute(t1, t_r) <= absolute(t2, t_r)){
                time_slop = MAX(absolute(v1, v_r), time_slop);
            } else {
                time_slop = MAX(absolute(v2, v_r), time_slop);
            }
        }

    }
    if (time_slop < tol) {
        printf("MAX error - %.20f    tol - %.2e    count - %d\n", time_slop, tol, *global);
    }
    else printf("Measure is smaller than MAX - %lf\n", time_slop);

}


void calculus (Test_slop *r, Neural_data *n, Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context,  double tol, double t, double t_end, int *global) {
    // ideal
    Params *p = (Params *)context;
    double h1 = h;
    double h2 = h;
    double ideal_h = 1e-5;
    double tol1 = 1e-14;
    double dif = t_end - t;
    init(n, dif, ideal_h);
    initi(r, dif, h1);
    double h_long = ideal_h;
    // Экспериментов много, сохраним входные данные
    double *xbasa = malloc(sizeof(double) * solver->n);
    turn_in(solver, x, xbasa);
    push_neural(n, t, x[0]);
    while (t < t_end) {
        h_long = Dormand_Prince (solver, x, h_long, f, &p, tol1, global);
        if (h_long < 1e-14) {
            h_long = 1e-13;
        }
        t += h_long;

        push_neural(n, t, x[0]);

    }
    *global = 0;
    t = 0;
    turn_out(solver, x, xbasa);
    push_neurali(r, t, x[0]);
    while (t < t_end) {
        rk4 (solver, x, h1, f, &p, global);
        t += h1;
        push_neurali(r, t, x[0]);
    }
    accuracy_calculus (r, n, tol, global);
    r->rows = 0;
    *global = 0;
    t = 0;
    turn_out(solver, x, xbasa);
    push_neurali(r, t, x[0]);
    while (t < t_end) {
        h2 = Dormand_Prince (solver, x, h2, f, &p, tol, global);
        t += h2;
        push_neurali(r, t, x[0]);

    }
    accuracy_calculus (r, n, tol, global);
    r->rows = 0;
    *global = 0;
    t = 0;
    turn_out(solver, x, xbasa);
    push_neurali(r, t, x[0]);
    while (t < t_end) {
        midpoint (solver, x, h1, f, &p, global);
        t += h1;
        push_neurali(r, t, x[0]);


    }
    accuracy_calculus (r, n, tol, global);
    free(n->data);
    free(r->data);
    free(xbasa);

}