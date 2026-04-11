#include "methods.h"


double Errors (double *x, double *y, Solver *solver) {
    int i;

    for (i = 0; i < solver->n; i++) {
        solver->err[i] = fabs(x[i] - y[i]);
    }
    double err_max = 0.0;
    for (i = 0; i < solver->n; i++) {
        if (solver->err[i] > err_max) {
            err_max = solver->err[i];
        }
    }
    return err_max;
}

// Нахождение ошибки методом с лекции (MC number one)
double Errors1 (Solver *solver) {
    int i;
    double m = solver->n;
    for (i = 0; i < solver->n; i++) {
        solver->tol[i] = solver->Atol[i] + solver->Rtol[i] * fmax(fabs(solver->Y_5[i]), fabs(solver->Y_4[i]));
    }


    for (i = 0; i < solver->n; i++) {
        solver->err[i] = (fabs(solver->Y_4[i] - solver->Y_5[i]) / solver->tol[i]);
    }
    double err_GIPER_SUPER_GIGA_SLOP = 0.0;
    for (i = 0; i < solver->n; i++) {
        err_GIPER_SUPER_GIGA_SLOP += solver->err[i] * solver->err[i];
    }
    err_GIPER_SUPER_GIGA_SLOP = sqrt(1.0 / m * err_GIPER_SUPER_GIGA_SLOP);
    return err_GIPER_SUPER_GIGA_SLOP;
}


// Методом Рунге-Кутты 4
void rk4 (Solver *solver, double *x, double h,
          void (*f) (double *x, double *fx, void *context, int *global),
          void *context, int *global){
    if (h > 5e-2) h = 5e-2;
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

// Метод средней точки
void midpoint (Solver *solver, double *x, double h,
               void (*f) (double *x, double *fx, void *context, int *global),
               void *context, int *global){
    int j;
    if (h > 5e-2) h = 5e-2;
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
                       void *context,  double delta, int *global) {
    int i;
    int count = 0;
    if (delta < 1e-14) delta = 1e-14;
    // Параметр оптимального интервала времени
    double hopt = h;
    // Создадим цикл для нахождения оптимального значения и интервала
    while(1) {
        f(x, (*solver).k1,
                context, global);
        for (i = 0; i < solver->n; i++) {
            // xmid = x + (1 / 5) * k1
            // k1 = h * f(x)
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

        // Найдем значение следующего шага
        // Вычисление методом Рунге-Кутты порядка 5
        // Получим значение, имеющее высокую точность
        for (i = 0; i < solver->n; i++) {
            // Мы вынуждены умножить сумму на h, ввиду того, что значения
            // каждого ki-го представляют собой взятую функцию f от нужного xmid
            solver->Y_5[i] = x[i] + h * ((35.0 / 384.0) * solver->k1[i]
                                        + (500.0 / 1113.0) * solver->k3[i]
                                        + (125.0 / 192.0) * solver->k4[i]
                                        + (-2187.0 / 6784.0) * solver->k5[i]
                                        + (11.0 / 84.0) * solver->k6[i]);
        }
        // Две формулы Рунге-Кутты имеют порядки q и p
        // (q > p) обычно q = p + 1
        // Возьмем p = 4, он представляет порядок формулы, ошибку которой мы оцениваем
        double p = 4.0;
        // Вычисление методом Рунге-Кутты порядка 4
        for (i = 0; i < solver->n; i++) {
            solver->Y_4[i] = x[i] + h * ((5179.0 / 57600.0) * solver->k1[i]
                                        + (7571.0 / 16695.0) * solver->k3[i]
                                        + (393.0 / 640.0) * solver->k4[i]
                                        + (-92097.0 / 339200.0) * solver->k5[i]
                                        + (187.0 / 2100.0) * solver->k6[i]
                                        + (1.0 / 40.0) * solver->k7[i]);
        }

        // Найдем норму бесконечности (infinity norm)
        double E = Errors(solver->Y_5, solver->Y_4, solver);
        // this method to deserve the out
        /*
        double E1 = Errors1(solver);

        if (E1 < 1.0) {
            for (i = 0; i < solver->n; i++) {
                x[i] = solver->Y_5[i];

            }

            // delta / E будет больше 1.0
            // Шаг увеличивается
            if (E1 > 1e-15) {
                // Мы вычисляем оптимальный интервал времени
                hopt = h * pow((1.0 / E1), 1.0 / p);
            } else {
                // Обработка нуля
                E1 = 1e-15;
                hopt = h * pow((1.0 / E1), 1.0 / p);
            }
            break;
        }


        // Error per step control
        if (E1 > 1.0) {
            // Мы вычисляем оптимальный интервал времени
            hopt = h * pow((1.0 / E1), 1.0 / p);
            h = hopt;
        } else {
            // Обработка 1.0
            E1 = 1.0;
            hopt = h * pow((1.0 / E1), 1.0 / p);
            h = hopt;
        }

        count ++;
        if (count > 100) {
            for (i = 0; i < solver->n; i++) {
                x[i] = solver->Y_5[i];

            }
            break;
        }

    }

    // Возвращаем оптимальную единицу шага типа double
    return hopt;*/


        // Если максимальный модуль разницы меньше дельта -> получаем результат
        if (E < delta) {
            for (i = 0; i < solver->n; i++) {
                x[i] = solver->Y_5[i];

            }

            // delta / E будет больше 1.0
            // Шаг увеличивается
            if (E > 1e-15) {
                // Мы вычисляем оптимальный интервал времени
                hopt = 0.9 * h * pow(((delta) / (E)), ((1.0) / (p + 1.0)));
            } else {
                // Обработка нуля
                E = 1e-15;
                hopt = 0.9 * h * pow(((delta) / (E)), ((1.0) / (p + 1.0)));
            }
            break;
        }


        // Error per step control
        if (E > 1e-15) {
            // Мы вычисляем оптимальный интервал времени
            hopt = 0.9 * h * pow(((delta) / (E)), ((1.0) / (p + 1.0)));
            h = hopt;
        } else {
            // Обработка нуля
            E = 1e-15;
            hopt = 0.9 * h * pow(((delta) / (E)), ((1.0) / (p + 1.0)));
            h = hopt;
        }

        count ++;
        if (count > 100) {
            for (i = 0; i < solver->n; i++) {
                x[i] = solver->Y_5[i];

            }
            break;
        }

    }

    // Возвращаем оптимальную единицу шага типа double
    return hopt;

}
