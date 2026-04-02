#include <math.h>
#include "model.h"


void f(double *x, double *fx, void *context, int *global){
    (*global) ++;
    Params *p = (Params *)context;

    // "Потенциал действия"
    // V is the displacement of the membrane potential from its resting value
    // (depolarization negative)
    // Cмещение мембранного потенциала относительно его покоя
    // В момент покоя мембранное напряжение равняется -65 мВ
    // V = E - Er, E - мембранное напряжение, Er - значение в момент покоя.
    // В момент покоя -65 - (-65) = 0
    // Напряжение внутри мембраны во время спайка равняется 30-40 мВ
    double V = x[0];
    // Параметр активация натриевых каналов
    double m = x[1];
    // Параметр инактивация натриевых каналов
    double h = x[2];
    // Параметр активация калиевых каналов
    double n = x[3];
    // Ёмкость мембраны на единицу площади
    double Cm = 1.0;
    // Максимальная способность мембраны пропускать ионы
    double gNa = 120.0, gK = 36.0, gL = 0.3;
    // Равновесные потенциалы: V = En - Er
    // En - "настоящий" потенциал натрия
    // Er - потенциал спокойствия
    double VNa = -115.0, VK = 12.0, VL = -10.613;

    // Скорость открытия калиевых ворот
    double alpha_n = 0.01 * (V + 10.0) / (exp((V + 10.0) / 10.0) - 1.0);
    // Скорость закрытия калиевых ворот
    double beta_n  = 0.125 * exp(V / 80.0);
    //Скорость открытия натриевых активирующих ворот
    double alpha_m = 0.1 * (V + 25.0) / (exp((V + 25.0) / 10.0) - 1.0);
    // Скорость закрытия натриевых активирующих ворот
    double beta_m  = 4.0 * exp(V / 18.0);
    // Скорость снятия инактивации натрия
    double alpha_h = 0.07 * exp(V / 20.0);
    // Скорость инактивации натрия
    double beta_h  = 1.0 / (exp((30.0 + V) / 10.0) + 1.0);

    // Токи
    double INa = gNa * pow(m, 3) * h * (V - VNa);
    double IK  = gK * pow(n, 4) * (V - VK);
    double IL  = gL * (V - VL);

    // Подаем отрицательный ток, так как деполяризация отрицательная, значит,
    // в момент прибывания в данном состоянии, dV/dt отрицательная.
    fx[0] = (p->Iext - INa - IK - IL) / Cm;
    fx[1] = alpha_m * (1.0 - m) - beta_m * m;
    fx[2] = alpha_h * (1.0 - h) - beta_h * h;
    fx[3] = alpha_n * (1.0 - n) - beta_n * n;
}








/*

// Если деполяризация положительная
// -(-V) = V
// +V -> -V
void f_modern(double *x, double *fx, void *context, int *global) {
    (*global)++;
    Params *p = (Params *)context;

    double V = x[0];
    double m = x[1];
    double h = x[2];
    double n = x[3];

    double Cm = 1.0;
    double gNa = 120.0, gK = 36.0, gL = 0.3;

    double VNa = +115.0;
    double VK  = -12.0;
    double VL  = 10.613;

    double alpha_n = 0.01 * (10.0 - V) / (exp((10.0 - V)/10.0) - 1.0);
    double beta_n  = 0.125 * exp(-V / 80.0);

    double alpha_m = 0.1 * (25.0 - V) / (exp((25.0 - V)/10.0) - 1.0);
    double beta_m  = 4.0 * exp(-V / 18.0);

    double alpha_h = 0.07 * exp(-V / 20.0);
    double beta_h  = 1.0 / (exp((30.0 - V)/10.0) + 1.0);

    double INa = gNa * pow(m, 3) * h * (V - VNa);
    double IK  = gK * pow(n, 4) * (V - VK);
    double IL  = gL * (V - VL);

    // Подаем положительный ток, так как деполяризация положительная, значит,
    // в момент прибывания в данном состоянии, dV/dt положительный.
    fx[0] = (p->Iext - INa - IK - IL) / Cm;
    fx[1] = alpha_m * (1.0 - m) - beta_m * m;
    fx[2] = alpha_h * (1.0 - h) - beta_h * h;
    fx[3] = alpha_n * (1.0 - n) - beta_n * n;
}
 */