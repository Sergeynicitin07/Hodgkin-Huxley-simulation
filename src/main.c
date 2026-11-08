#include <stdio.h>
#include "struct.h"
#include "methods.h"
#include "model.h"
#include <string.h>
#include <stdlib.h>
#include "great_app_test.h"
#include "rubbish.h"
#include <time.h>


void justice (Ignominious *lord) {
    // 27.09.2026 - the new project
    char beckett[256];

    int i = 0;
    FILE *f = fopen("data(13).csv", "r");
    // r - read data
    if (f == NULL) {
        printf("EXCUSE ME, SIR. YOU MIGHT REPEAT YOUR EXECUTION TOMORROW.");
        return;
    }
    if (fgets(beckett, sizeof(beckett), f) == NULL) {
        printf("You must keep a grip on your impulses.\n");
        fclose(f);
        return;
    }    // мы передвигаем позицию чтения файла с первой строки, где нету чисел на вторую, где впервые появляются числовые данные.
    double time_data;
    double v_data;
    while (i < lord->n && fscanf(f, "%lf, %lf", &time_data, &v_data) == 2) {
        if (time_data >= 51000.0 &&
                time_data <= 100999.0) {

            lord->ignominious_time[i] =
                    (time_data - 51000.0) * 0.02;

            lord->ignominious_voltage[i] =
                    v_data * 1000.0;

            i++;
        }
    }
    fclose(f);


}



void the_death_from_above(
        Ignominious *lord,
        double h,
        Params *p,
        int *global,
        Solver *solver,
        double x1[4],
        double t0,
        double t_end,
        int *talon,
        double *c
) {


    int step = (int)(0.02 / h);
    int count = 0;
    double vatoadmin = 0.0;

    int i = 3000;

    double c_ = *c;
    double sum_1 = 0.0; // ...
    double sum_2 = 0.0; // сумма квадратов разницы двух напряжений
    double sum_r_2 = 0.0; // сумма квадратов невязки
    double r = 0.0;
    double a;
    (*talon) = 0;
    while (t0 < t_end) {
        {
            if (t0 >= 60.0) {
                if (count % step == 0) {
                    a = (x1[0] + lord->ignominious_voltage[i]);
                    i ++;
                    sum_1 += a;
                    sum_2 += a * a;
                    r = a + c_;
                    sum_r_2 += r * r; // сумма квадратов невязок вводимого c
                    vatoadmin += 1.0;
                    (*talon)++;
                }
                count ++;


            }



            rk4(solver, x1, h, f, p, global);
            t0 += h;
        }
    }

    double s;

    *c = - sum_1 / vatoadmin;
    double sum_r_2_new = sum_2 - (sum_1 * sum_1) / vatoadmin; // сумма квадратов невязок нового параметра c
    printf("c_old: %.15le Sum of Squared Errors old: %.15le\n", c_, sum_r_2);
    printf("c_new: %.15le Sum of Squared Errors new:%.15le\n", *c, sum_r_2_new);
    FILE *file = fopen("parameters.txt", "w");
    if (file != NULL) {
        fprintf(file, "%.15le\n", *c);
        fclose(file);
    }
}



int solve_3x3(double A[3][3], double b[3], double delta[3]) {

    double M[3][4];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++)
            M[i][j] = A[i][j];

        M[i][3] = b[i];
    }

    for (int k = 0; k < 3; k++) {

        int p = k;

        for (int i = k + 1; i < 3; i++)
            if (fabs(M[i][k]) > fabs(M[p][k]))
                p = i;


        if (fabs(M[p][k]) < 1e-10)
            return 0;

        for (int j = k; j < 4; j++) {
            double temp = M[k][j];
            M[k][j] = M[p][j];
            M[p][j] = temp;
        }

        for (int i = k + 1; i < 3; i++) {
            double q = M[i][k] / M[k][k];

            for (int j = k; j < 4; j++)
                M[i][j] -= q * M[k][j];
        }
    }

    for (int i = 2; i >= 0; i--) {
        delta[i] = M[i][3];

        for (int j = i + 1; j < 3; j++)
            delta[i] -= M[i][j] * delta[j];

        delta[i] /= M[i][i];
    }

    return 1;
}





int main(int argc, char *argv[]) {


    double current = 430.000007822784;
    // пикоампер
    // 1pA = 10e−12A
    int independence = 50000;

    Ignominious *lord = lord_structure(independence);


    // resistance_input = 63.0 миллиона ом
    // tau - мембранная постоянная времени (ms)
    double capacity_cell_nF = tau / resistance_input;
    // перевод из нано в микро
    double capacity_cell_uF = capacity_cell_nF * 1e-3;

    double Cm = 0.5;
    double s = capacity_cell_uF / Cm;
    // перевод в микроамперы
    double I = current * 1e-6 / s;





    int n = 4;
    clock_t start = clock();
    double time_limit = 2.0;
    Solver *solver = solver_unit(n);
    solver->Atol[0] = 1e-15;
    solver->Atol[1] = 1e-15;
    solver->Atol[2] = 1e-15;
    solver->Atol[3] = 1e-15;

    solver->Rtol[0] = 1e-1;
    solver->Rtol[1] = 1e-1;
    solver->Rtol[2] = 1e-1;
    solver->Rtol[3] = 1e-15;
    Solver *solver_sens = solver_unit(16);

    for (int i = 0; i < 16; i++) {
        solver_sens->Atol[i] = 1e-12;
        solver_sens->Rtol[i] = 1e-9;
    }

    Params p;
    p.ladder = 0;

    double h = 1e-3;
    double t = 0.0;
    double t_end = 1000.0;
    char method[20] = "rk4";
    int use_calculus = 2;

    if (argc > 1)
        use_calculus = atoi(argv[1]); // 1 = calculus режим
    p.Iext = -I;
    double hk = 1e-1;
    double tol = 1e-1;

    double c = 53.5;
    double as = 1e-10;
    if (use_calculus == 1 || use_calculus == 0) {
        if (argc > 2)
            strcpy(method, argv[2]);

        if (argc > 3)
            p.Iext = -atof(argv[3]);

        if (argc > 4)
            t_end = atof(argv[4]);

        if (argc > 5)
            h = atof(argv[5]);
        if (argc > 6)
            tol = atof(argv[6]);
        if (argc > 7)
            as = atof(argv[7]);
    }
    if (use_calculus == 2) {

        if (argc > 2)
            c = atof(argv[2]);

        if (argc > 3)
            gNa = atof(argv[3]);

        if (argc > 4)
            gK = atof(argv[4]);

        if (argc > 5)
            gL = atof(argv[5]);

        if (argc > 6)
            VNa = atof(argv[6]);
        if (argc > 7)
            VK = atof(argv[7]);
        if (argc > 8)
            VL = atof(argv[8]);

        if (argc > 9)
            sn = atof(argv[9]);
        if (argc > 10)
            sm = atof(argv[10]);
        if (argc > 11)
            sh = atof(argv[11]);
    }

    /*
    if (argc > 8)
        solver->Rtol[0] = atof(argv[8]);
    if (argc > 9)
        solver->Rtol[1] = atof(argv[9]);
    if (argc > 10)
        solver->Rtol[2] = atof(argv[10]);
    if (argc > 11)
        solver->Rtol[4] = atof(argv[11]);
     */
    // Для calculus - теста
    int global = 0;
    double x[4] = {0.0, 0.042, 0.608, 0.6};

    double x1[4] = {0.0, 0.042, 0.608, 0.6};

    double x2[16] = {0.0, 0.042, 0.608, 0.6,
                     0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 0.0,
                     0.0, 0.0, 0.0, 0.0

    };


    if (use_calculus == 1) {
        Test_slop *r = malloc(sizeof(Test_slop));
        Neural_data *j = malloc(sizeof(Neural_data));

        calculus(r, j, solver, x, h, f, &p, tol, t, t_end, &global, as, hk);

        free(r);
        free(j);
    } else if (use_calculus == 0){
        tol = 1e-14;
        double h_long = h;
        while (t < t_end) {

            printf("%.15le %.15le %.15le %.15le %.15le\n",
                   t, -77.5 - x[0], x[1], x[2], x[3]);
            if (strcmp(method, "rk4") == 0) {
                rk4 (solver, x, h, f, &p, &global);
                t += h;
            }
            else if (strcmp(method, "dp") == 0) {
                h_long = Dormand_Prince (solver, x, h_long, f, &p, as, &global);
                t += h_long;
            }
            else if (strcmp(method, "mid") == 0) {
                midpoint (solver, x, h, f, &p, &global);
                t += h;
            }
            else {
                return 1;
            }
        }
    } else if (use_calculus == 2){

        justice(lord);
        FILE *experiment = fopen("experiment.txt", "w");

        if (experiment == NULL) {
            printf("That resource must be mobilized.\n");
            return 1;
        }

        for (int i = 3000; i < lord->n; i++) {
            fprintf(experiment, "%15le %15le\n",
                    lord->ignominious_time[i] - 3000 * 0.02,
                    lord->ignominious_voltage[i]);
        }

        fclose(experiment);

        double h_long = h;


        int step = (int)(0.02 / h);
        int data_count = lord->n - 3000;

        double *good_times = malloc(3 * data_count * sizeof(double));
        double *r = malloc(data_count * sizeof(double));
        double delta[3];
        double alpha;


        int talon = 0;
        the_death_from_above(
                lord, h, &p, &global, solver,
                x1, 0.0, t_end, &talon, &c
        );
        p.ladder = 1;

        for (int iteration = 0; iteration < 5; iteration++) {

            x1[0] = 0.0;
            x1[1] = 0.042;
            x1[2] = 0.608;
            x1[3] = 0.6;



            for (int i = 0; i < 16; i++)
                x2[i] = 0.0;

            x2[0] = 0.0;
            x2[1] = 0.042;
            x2[2] = 0.608;
            x2[3] = 0.6;

            double t2 = 0.0;
            int count = 0;
            int index = 0;

            while (t2 < t_end) {

                if (t2 >= 60.0 && count % step == 0) {

                    if (index >= data_count)
                        break;

                    good_times[index] = x2[4];
                    good_times[data_count + index] = x2[8];
                    good_times[2 * data_count + index] = x2[12];

                    r[index] = -c - x2[0]
                               - lord->ignominious_voltage[index + 3000];

                    index++;
                }

                if (t2 >= 60.0)
                    count++;

                rk4(solver_sens, x2, h, f, &p, &global);

                t2 += h;
            }



            double A[3][3] = {{0.0}};
            double b[3] = {0.0, 0.0, 0.0};

            for (int i = 0; i < data_count; i++) {

                double J[3];

                for (int q = 0; q < 3; q++)
                    J[q] = - good_times[q * data_count + i];

                for (int q = 0; q < 3; q++) {

                    b[q] -= J[q] * r[i];

                    for (int j = 0; j < 3; j++)
                        A[q][j] += J[q] * J[j];
                }
            }
            double sum_r_2 = 0.0;

            for (int i = 0; i < data_count; i++)
                sum_r_2 += r[i] * r[i];

            printf("%d: sum_r_2 = %.15le\n", iteration, sum_r_2);

            alpha = 0.5;

            if (!solve_3x3(A, b, delta)) {
                printf("You shall abandon the lie. Your time in that way was a bad investment on my part.\n");
                return 1;
            }
            gNa += alpha * delta[0];
            gK  += alpha * delta[1];
            gL  += alpha * delta[2];
            printf("%d: gNa = %.15le, gK = %.15le, gL = %.15le\n",
                   iteration, gNa, gK, gL);

        }


        x1[0] = 0.0;
        x1[1] = 0.042;
        x1[2] = 0.608;
        x1[3] = 0.6;

        p.ladder = 0;

        the_death_from_above(
                lord, h, &p, &global, solver,
                x1, 0.0, t_end, &talon, &c
        );


        while (t < t_end) {

            if (t >= 60.0)
                printf("%.15le %.15le %.15le %.15le %.15le\n",
                   t - 60.0, -c - x[0], x[1], x[2], x[3]);
            if (strcmp(method, "rk4") == 0) {
                rk4 (solver, x, h, f, &p, &global);
                t += h;
            }
            else if (strcmp(method, "dp") == 0) {
                h_long = Dormand_Prince (solver, x, h_long, f, &p, as, &global);
                t += h_long;
            }
            else if (strcmp(method, "mid") == 0) {
                midpoint (solver, x, h, f, &p, &global);
                t += h;
            }
            else {
                return 1;
            }
        }

    }


    solver_free(solver_sens);
    solver_free(solver);
    lord_free(lord);
    return 0;
}
