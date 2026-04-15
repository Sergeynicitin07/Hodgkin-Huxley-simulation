#include "great_app_test.h"
#include <stdlib.h>
#include "methods.h"
#include "model.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

double get_time() {
#ifdef _WIN32
    static LARGE_INTEGER freq;
    static int initialized = 0;
    LARGE_INTEGER now;

    if (!initialized) {
        QueryPerformanceFrequency(&freq);
        initialized = 1;
    }

    QueryPerformanceCounter(&now);
    return (double)now.QuadPart / freq.QuadPart;

#else
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec / 1e9;
#endif
}


// Инициализация для точных данных
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

// Инициализация для гипотетических данных
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


void accuracy_calculus (Test_slop *r, Neural_data *n,  double tol, int *global, double *maxic, double h, int *chmuck) {
    int i = 0;
    int j = 0;

    double v_r1 = r->data[i * 2 + 1];
    double s;
    // Найдем ошибку при t = 0
    double time_slop = fmax(fabs(v_r1 -  n->data[1]), 0.0);

    for (i = 1; i < r->rows; i ++) {
        double t_r = r->data[i * 2 + 0];
        double v_r = r->data[i * 2 + 1];

        while (n->data[(j + 1) * 2] < t_r && j < n->rows - 1) {
            j++;
        }
        double t1 = n->data[j * 2 + 0];
        double v1 = n->data[j * 2 + 1];

        // t_r уже меньше t2
        double t2 = n->data[(j + 1) * 2 + 0];
        double v2 = n->data[(j + 1) * 2 + 1];

        if (t1 <= t_r && t2 >= t_r) {
            s = (t_r - t1) / (t2 - t1);
            time_slop = fmax(fabs(v_r - ((1 - s) * v1 + s * v2)), time_slop);
        }
        /*
        if (t1 <= t_r && t2 >= t_r) {
            if (fabs(t1 - t_r) <= fabs(t2 - t_r)){
                time_slop = fmax(fabs(v1 - v_r), time_slop);
            } else {
                time_slop = fmax(fabs(v2 - v_r), time_slop);
            }
        }*/

    }
    *maxic = time_slop;
    if (time_slop < tol) {
        *chmuck = 1;
        printf("MAX error - %.15le\t\tcount - %d\t\t\th - %15le\n", time_slop, *global, h);
    }
    // else printf("Measure is smaller than MAX - %15le    tol - %.15le    count - %d\n", time_slop, tol, *global);

}


void calculus (Test_slop *r, Neural_data *n, Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context,  double tol, double t, double t_end, int *global, double as, double hk) {
    double start = get_time();
    double time_limit = 15.0;
    double time_limit1 = 10.0;

    // ideal
    int tel = 0;
    double h5 = h;
    int *chmuck = &tel;
    Params *p = (Params *)context;
    double h1 = 5e-0;
    double h2 = h;
    double h3 = 5e-0;
    double super_h = 5e-6;

    double maxic = 0.0;
    double ideal_h = 5e-6;
    int key = 0;
    double tol1 = 1e-14;
    double tol2 = as;
    double dif = t_end - t;
    init(n, dif, ideal_h);
    initi(r, dif, h1);
    double h_long = ideal_h;
    int i;
    int ui = 0;
    int g = 14;
    int supremacist = 0;
    // Экспериментов много, сохраним входные данные
    double *xbasa = malloc(sizeof(double) * solver->n);
    turn_in(solver, x, xbasa);
    push_neural(n, t, x[0]);

    while (t < t_end) {
        rk4 (solver, x, super_h, f, &p, global);
        t += super_h;
        push_neural(n, t, x[0]);
        double elapsed = get_time() - start;
        if (elapsed > time_limit1) {
            printf("Time\tis\tover\tfor\tRK4\tideal.\tIdeal\th - %15le\n", super_h);
            supremacist = 1;
            break;
        }

    }
    start = get_time();
    if (supremacist) {
        *global = 0;
        super_h = 1e-3;

        printf("It`s\ttime\tfor\tnew\tideal\twith\tnew\th - %15le\n", super_h);
        t = 0.0;
        n->rows = 0;

        while (t < t_end) {
            double elapsed = get_time() - start;
            if (elapsed > time_limit) {
                printf("Time\tis\tover\tfor\tRK4\tideal.\tIdeal\th - %15le\n", super_h);
                key = 1;
                break;
            }
            rk4 (solver, x, super_h, f, &p, global);
            t += super_h;
            push_neural(n, t, x[0]);
        }


    }

    if (key) {
        printf("Time\tis\tover\tfor\tideal\tdata.\nWe\tshould\tto\tstop\tall.\n");
        exit(0);
    }
    start = get_time();
    /*
    while (t < t_end) {
        h_long = Dormand_Prince (solver, x, h_long, f, &p, tol1, global);
        if (h_long < 1e-14) {
            h_long = 1e-14;
        }
        t += h_long;
        if (elapsed > time_limit) {
            printf("Time\tis\tover\tfor\tideal\tdata.\nWe\tmust\tto\tstop.\n");
            break;
        }
        push_neural(n, t, x[0]);

    }*/
    printf("RK4_DEUS_EX_MACHINA\tIDOL\tcount - %d\tglobal\ttolerance - %.1le\n", *global, tol);
    start = get_time();
    printf("Runge-Kutte 4\n");
    for (i = 0; i < g; i ++) {
        *global = 0;
        *chmuck = 0;
        t = 0.0;
        if (i > 10) h1 *= 1e-1;
        else  h1 *= 0.5;

        maxic = 0.0;
        r->rows = 0;
        turn_out(solver, x, xbasa);
        push_neurali(r, t, x[0]);
        while (t < t_end) {
            double elapsed = get_time() - start;
            if (elapsed > time_limit) {
                printf("Time\tis\tover\tfor\tRK4.\n");
                ui = 1;
                break;
            }
            rk4 (solver, x, h1, f, &p, global);
            t += h1;
            push_neurali(r, t, x[0]);
        }
        if (ui) break;
        accuracy_calculus (r, n, tol, global, &maxic, h1, chmuck);
        if (maxic < tol) break;
    }
    if (*chmuck == 0 && ui == 0) {
        printf("Measure\tis\tsmaller\tthan\tmax\terror.\tcount - %d\t\th - %15le\n", *global, h1);
    }
    start = get_time();
    ui = 0;
    printf("Dormand_Prince\n");
    r->rows = 0;
    *global = 0;
    t = 0.0;
    *chmuck = 0;
    maxic = 0.0;
    turn_out(solver, x, xbasa);
    push_neurali(r, t, x[0]);
    while (t < t_end) {
        double elapsed = get_time() - start;
        if (elapsed > time_limit) {
            printf("Time\tis\tover\tfor\tDormand-Prince\n");
            ui = 1;
            break;
        }
        h2 = Dormand_Prince (solver, x, h2, f, &p, tol2, global);
        t += h2;
        push_neurali(r, t, x[0]);

    }
    accuracy_calculus (r, n, tol, global, &maxic, hk, chmuck);
    if (*chmuck == 0 && ui == 0) {
        printf("Measure\tis\tsmaller\tthan\tmax\terror.\tcount - %d\t\t\th - %15le\n", *global, hk);
    }
    ui = 0;
    start = get_time();
    printf("Midpoint\n");
    for (i = 0; i < g; i ++) {
        r->rows = 0;
        *global = 0;
        t = 0.0;
        maxic = 0.0;
        *chmuck = 0;

        if (i > 20) h3 *= 1e-1;
        else  h3 *= 0.5;
        turn_out(solver, x, xbasa);
        push_neurali(r, t, x[0]);
        while (t < t_end) {
            double elapsed = get_time() - start;
            if (elapsed > time_limit) {
                printf("Time\tis\tover\tfor\tMidpoint\n");
                ui = 1;
                break;
            }
            midpoint(solver, x, h3, f, &p, global);
            t += h3;
            push_neurali(r, t, x[0]);
        }
        if (ui) break;
        accuracy_calculus(r, n, tol, global, &maxic, h3, chmuck);
        if (maxic < tol) break;


    }
    if (*chmuck == 0 && ui == 0) {
        printf("Measure\tis\tsmaller\tthan\tmax\terror.\tcount - %d\t\t\th - %15le\n", *global, h3);
    }
    free(n->data);
    free(r->data);
    free(xbasa);
}
