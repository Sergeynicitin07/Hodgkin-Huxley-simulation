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
        printf("EXCUSE ME, SER. YOU COULD REPEAT YOUR EXECUTION TOMORROW.");
        return;
    }
    fgets(beckett, sizeof(beckett), f);
    // мы передвигаем позицию чтения файла с первой строки, где нету чисел на вторую, где впервые появляются числовые данные.
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


    Params p;

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
            gNa = atof(argv[2]);

        if (argc > 3)
            gK = atof(argv[3]);

        if (argc > 4)
            gL = atof(argv[4]);

        if (argc > 5)
            VNa = atof(argv[5]);
        if (argc > 6)
            VK = atof(argv[6]);
        if (argc > 7)
            VL = atof(argv[7]);

        if (argc > 8)
            sn = atof(argv[8]);
        if (argc > 9)
            sm = atof(argv[9]);
        if (argc > 10)
            sh = atof(argv[10]);
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

    if (use_calculus == 1) {
        Test_slop *r = malloc(sizeof(Test_slop));
        Neural_data *j = malloc(sizeof(Neural_data));

        calculus(r, j, solver, x, h, f, &p, tol, t, t_end, &global, as, hk);

        free(r);
        free(j);
    } else if (use_calculus == 0){
        tol = 1e-14;
        double h_long = h;
        while (t < 51000.0) {
            printf("%15le %15le %15le %15le %15le\n",
                   t, -77.5 - x[0], x[1], x[2], x[3]);
            t += h;
        }
        while (t < t_end && t >= 51000) {

            printf("%15le %15le %15le %15le %15le\n",
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

        for (int i = 0; i < lord->n; i++) {
            fprintf(experiment, "%15le %15le\n",
                    lord->ignominious_time[i],
                    lord->ignominious_voltage[i]);
        }

        fclose(experiment);

        tol = 1e-14;
        double h_long = h;

        while (t < t_end) {

            printf("%15le %15le %15le %15le %15le\n",
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

    }

    solver_free(solver);
    lord_free(lord);
    return 0;
}
