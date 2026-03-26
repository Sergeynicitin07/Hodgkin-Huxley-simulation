#include <math.h>
#include "model.h"


static double safe_exp(double x) {
    if (x > 50.0) return exp(50.0);
    if (x < -50.0) return exp(-50.0);
    return exp(x);
}


static double vtrap(double x, double y) {
    if (fabs(x / y) < 1e-6)
        return y * (1.0 - x / (2.0 * y));
    return x / (exp(x / y) - 1.0);
}


void f(double *x, double *fx, void *context, int *global){
    (*global) ++;
    Params *p = (Params *)context;

    double V = x[0] + 65.0;
    double m = x[1];
    double h = x[2];
    double n = x[3];

    double Cm = 1.0;
    double gNa = 120.0, gK = 36.0, gL = 0.3;
    double ENa = 115.0, EK = -12.0, EL = 10.6;

    double alpha_n = 0.01 * vtrap(10.0 - V, 10.0);
    double beta_n  = 0.125 * safe_exp(-V / 80.0);

    double alpha_m = 0.1 * vtrap(25.0 - V, 10.0);
    double beta_m  = 4.0 * safe_exp(-V / 18.0);

    double alpha_h = 0.07 * safe_exp(-V / 20.0);
    double beta_h  = 1.0 / (safe_exp((30.0 - V) / 10.0) + 1.0);

    double INa = gNa * pow(m, 3) * h * (V - ENa);
    double IK  = gK * pow(n, 4) * (V - EK);
    double IL  = gL * (V - EL);

    fx[0] = (p->Iext - INa - IK - IL) / Cm;
    fx[1] = alpha_m * (1.0 - m) - beta_m * m;
    fx[2] = alpha_h * (1.0 - h) - beta_h * h;
    fx[3] = alpha_n * (1.0 - n) - beta_n * n;
}