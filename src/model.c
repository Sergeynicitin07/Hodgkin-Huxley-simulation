#include <math.h>
#include "model.h"
#include "struct.h"


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
    double Cm = 0.5;
    // Максимальная способность мембраны пропускать ионы
    // Равновесные потенциалы: V = En - Er
    // En - "настоящий" потенциал натрия
    // Er - потенциал спокойствия

    // Скорость открытия калиевых ворот
    double alpha_n = sn * (0.01 * (V + 10.0) / (exp((V + 10.0) / 10.0) - 1.0));
    // Скорость закрытия калиевых ворот
    double beta_n  = sn * (0.125 * exp(V / 80.0));
    //Скорость открытия натриевых активирующих ворот
    double alpha_m = sm * (0.1 * (V + 25.0) / (exp((V + 25.0) / 10.0) - 1.0));
    // Скорость закрытия натриевых активирующих ворот
    double beta_m  = sm * (4.0 * exp(V / 18.0));
    // Скорость снятия инактивации натрия
    double alpha_h = sh * (0.07 * exp(V / 20.0));
    // Скорость инактивации натрия
    double beta_h  = sh * (1.0 / (exp((30.0 + V) / 10.0) + 1.0));

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

    if (p->ladder == 1) {



        double alpha_n_v = sn * 0.01 *
                           ((exp((V + 10.0) / 10.0) - 1.0) - (V + 10.0) * exp((V + 10.0) / 10.0) / 10.0)
                           / ((exp((V + 10.0) / 10.0) - 1.0) * (exp((V + 10.0) / 10.0) - 1.0));

        double beta_n_v = beta_n / 80.0;

        double alpha_m_v = sm * 0.1 *
                           ((exp((V + 25.0) / 10.0) - 1.0) - (V + 25.0) * exp((V + 25.0) / 10.0) / 10.0)
                           / ((exp((V + 25.0) / 10.0) - 1.0) * (exp((V + 25.0) / 10.0) - 1.0));

        double beta_m_v = beta_m / 18.0;

        double alpha_h_v = alpha_h / 20.0;

        double beta_h_v = -sh * exp((V + 30.0) / 10.0) /
                          (10.0 * (exp((V + 30.0) / 10.0) + 1.0) * (exp((V + 30.0) / 10.0) + 1.0));


        // Производные
        double df_dx[4][4] = {{0.0}};

        df_dx[0][0] =
                -(gNa * m * m * m * h
                  + gK * n * n * n * n + gL) / Cm;

        df_dx[0][1] =
                -3.0 * gNa * m * m * h * (V - VNa) / Cm;

        df_dx[0][2] =
                -gNa * m * m * m * (V - VNa) / Cm;

        df_dx[0][3] =
                -4.0 * gK * n * n * n * (V - VK) / Cm;


        df_dx[1][0] = alpha_m_v * (1.0 - m) - beta_m_v * m;
        df_dx[1][1] = -alpha_m - beta_m;

        df_dx[2][0] = alpha_h_v * (1.0 - h) - beta_h_v * h;
        df_dx[2][2] = -alpha_h - beta_h;

        df_dx[3][0] = alpha_n_v * (1.0 - n) - beta_n_v * n;
        df_dx[3][3] = -alpha_n - beta_n;


        // Производные правой части по gNa, gK, gL
        double df_dg[4][3] = {{0.0}};

        df_dg[0][0] = -m * m * m * h * (V - VNa) / Cm;
        df_dg[0][1] = -n * n * n * n * (V - VK) / Cm;
        df_dg[0][2] = -(V - VL) / Cm;


        for (int all = 0; all < 3; all++) {

            for (int i = 0; i < 4; i++) {

                double appeal = df_dg[i][all];

                for (int j = 0; j < 4; j++) {
                    appeal += df_dx[i][j] *
                             x[4 + all * 4 + j];
                }

                fx[4 + all * 4 + i] = appeal;
            }
        }
    }

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
