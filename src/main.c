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
    double current_data;
    int index = 0;
    FILE *f = fopen("a1t18.csv", "r");
    // r - read data
    if (f == NULL) {
        printf("EXCUSE ME, SIR. YOU MIGHT REPEAT YOUR EXECUTION TOMORROW.");
        return;
    }
    if (fgets(beckett, sizeof(beckett), f) == NULL) {
        printf("You must keep a grip on your impulses.\n");
        fclose(f);
        return;
    }
    // мы передвигаем позицию чтения файла с первой строки, где нету чисел на вторую, где впервые появляются числовые данные.
    double v_data;
    while (i < lord->n && fscanf(f, "%lf, %lf", &v_data, &current_data) == 2) {

        if (index >= 175000 && index <= 235000)
                {


            lord->ignominious_time[i] =
            (index - 125000) * 0.008;

            lord->ignominious_voltage[i] =
                    v_data * 100.0;

            lord->ignominious_current[i] =
                    current_data * 5.0;

            i++;
        }
        index++;
    }
    lord->n = i;
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



int solve_10x10(double A[10][10], double b[10], double delta[10]) {


    double L[10][10] = {{0.0}};
    double y[10] = {0.0};






    for (int i = 0; i < 10; i++) {

        for (int j = 0; j <= i; j++) {

            double sum = A[i][j];

            for (int k = 0; k < j; k++) {
                sum -= L[i][k] * L[j][k];
            }

            if (i == j) {


                L[i][j] = sqrt(sum);

            } else {


                L[i][j] = sum / L[j][j];
            }
        }
    }


    for (int i = 0; i < 10; i++) {

        double sum = b[i];

        for (int j = 0; j < i; j++) {
            sum -= L[i][j] * y[j];
        }


        y[i] = sum / L[i][i];
    }


    for (int i = 9; i >= 0; i--) {





        double sum = y[i];


        for (int j = i + 1; j < 10; j++) {
            sum -= L[j][i] * delta[j];
        }





        delta[i] = sum / L[i][i];
    }

    return 1;
}



int main(int argc, char *argv[]) {


    // int independence = 125001;
    int independence = 250001;
    Ignominious *lord = lord_structure(independence);







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


    int gift = 0;
    Params p;
    p.ladder = 0;

    double h = 1e-3;
    double t = 0.0;
    double t_end = 1000.0;
    char method[20] = "rk4";
    int use_calculus = 2;
    p.Iext = 0.003666281829 * 5;

    if (argc > 1)
        use_calculus = atoi(argv[1]); // 1 = calculus режим
    double hk = 1e-1;
    double tol = 1e-1;
    int dim  = 4;
    double c  = 5.050330493860655e+01;

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
    int count_N_T = 0;
    p.not_today[0] = 0;
    for (int i = 0; i < 10; i++) {

        (p.not_today[i] = i);
    }
    if (use_calculus == 2) {

        p.not_today_count = 0;


        for (int arg = 2; arg < argc; arg++) {

            if (strcmp(argv[arg], "c") == 0) {
                p.not_today[p.not_today_count++] = 0;
            }
            else if (strcmp(argv[arg], "gNa") == 0) {
                p.not_today[p.not_today_count++] = 1;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "gK") == 0) {
                p.not_today[p.not_today_count++] = 2;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "gL") == 0) {
                p.not_today[p.not_today_count++] = 3;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "VNa") == 0) {
                p.not_today[p.not_today_count++] = 4;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "VK") == 0) {
                p.not_today[p.not_today_count++] = 5;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "VL") == 0) {
                p.not_today[p.not_today_count++] = 6;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "sn") == 0) {
                p.not_today[p.not_today_count++] = 7;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "sm") == 0) {
                p.not_today[p.not_today_count++] = 8;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "sh") == 0) {
                p.not_today[p.not_today_count++] = 9;
                count_N_T++;
            }
        }

        if (p.not_today_count == 0) {
            p.not_today_count = 10;
            count_N_T = 9;

            for (int i = 0; i < 10; i++)
                p.not_today[i] = i;
        }

        dim = 4 + count_N_T * 4;
    }

        /*
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


        p.not_today_count = 0;

        for (int arg = 12; arg < argc; arg++) {

            if (strcmp(argv[arg], "c") == 0) {
                p.not_today[p.not_today_count++] = 0;
            }
            else if (strcmp(argv[arg], "gNa") == 0) {
                p.not_today[p.not_today_count++] = 1;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "gK") == 0) {
                p.not_today[p.not_today_count++] = 2;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "gL") == 0) {
                p.not_today[p.not_today_count++] = 3;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "VNa") == 0) {
                p.not_today[p.not_today_count++] = 4;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "VK") == 0) {
                p.not_today[p.not_today_count++] = 5;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "VL") == 0) {
                p.not_today[p.not_today_count++] = 6;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "sn") == 0) {
                p.not_today[p.not_today_count++] = 7;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "sm") == 0) {
                p.not_today[p.not_today_count++] = 8;
                count_N_T++;
            }
            else if (strcmp(argv[arg], "sh") == 0) {
                p.not_today[p.not_today_count++] = 9;
                count_N_T++;
            }
        }

        if (p.not_today_count == 0) {
            p.not_today_count = 10;
            count_N_T = 9;

            for (int i = 0; i < 10; i++)
                p.not_today[i] = i;
        }

        dim = 4 + count_N_T * 4;
    }*/

    Solver *solver_sens = solver_unit(dim);

    for (int i = 0; i < dim; i++) {
        solver_sens->Atol[i] = 1e-12;
        solver_sens->Rtol[i] = 1e-9;
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
    double x[4] = {0.0, 0.05293, 0.59612, 0.31768};

    double x1[4] = {0.0, 0.042, 0.608, 0.6};

    double x2[44] = {0.0};




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

        for (int i = 0; i < lord->n; i++) {
            fprintf(experiment, "%15le %15le\n",
                    lord->ignominious_time[i],
                    lord->ignominious_voltage[i]);
        }

        fclose(experiment);

        double h_long = h;
        int diam = (dim - 4) / 4;

        int step = (int)(0.008 / h);
        int data_count = lord->n;


        double *good_times = malloc(diam * data_count * sizeof(double));
        double *r = malloc(data_count * sizeof(double));
        double delta[10];
        double alpha = 1e-4;

        x[0] = 0.0;
        x[1] = 0.042;
        x[2] = 0.608;
        x[3] = 0.6;

        int talon = 0;
        p.ladder = 0;
        p.Iext = -5.0;
        double t2 = -1.0;
        int count = 0;
        int index = 0;

        while (t2 <= 880.0) {

            if (count % step == 0 && t2 >= 400.0) {

                if (index >= data_count)
                    break;



                r[index] = -c - x[0]
                           - lord->ignominious_voltage[index];

                index++;
            }


            p.Iext = -5.0;
            rk4(solver, x, h, f, &p, &global);

            t2 += h;
            count++;
        }
        double sum_r_2 = 0.0;

        for (int i = 0; i < index; i++)
            sum_r_2 += r[i] * r[i];

        printf("sum_r_2 = %.15le\n", sum_r_2);
        printf("Root Mean Square Error  = %.15le\n", sqrt(sum_r_2 / index));
        for (int iteration = 0; iteration < gift; iteration++) {

            x1[0] = 0.0;
            x1[1] = 0.042;
            x1[2] = 0.608;
            x1[3] = 0.6;



            for (int i = 0; i < 44; i++)
                x2[i] = 0.0;

            x2[0] = 0.0;
            x2[1] = 0.042;
            x2[2] = 0.608;
            x2[3] = 0.6;

            t2 = -1.0;
            count = 0;
            index = 0;

            while (t2 <= 420.0) {

                if (count % step == 0 && t2 >= 400.0) {

                    if (index >= data_count)
                        break;

                    int q = 0;

                    for (int a = 0; a < p.not_today_count; a++) {

                        if (p.not_today[a] == 0)
                            continue;

                        good_times[q * data_count + index] =
                                x2[4 + q * 4];

                        q++;
                    }

                    r[index] = -c - x2[0]
                               - lord->ignominious_voltage[index];

                    index++;
                }

                p.Iext = -5.0;
                rk4(solver_sens, x2, h, f, &p, &global);

                t2 += h;
                count++;
            }

            int k = p.not_today_count;

            double A[10][10] = {{0.0}};
            double b[10] = {0.0};
            double J[10];

            for (int i = 0; i < data_count; i++) {

                int q = 0;

                for (int a = 0; a < k; a++) {

                    if (p.not_today[a] == 0) {
                        J[a] = -1.0;
                    }
                    else {
                        J[a] = -good_times[q * data_count + i];
                        q++;
                    }
                }

                for (int g = 0; g < k; g++) {

                    b[g] -= J[g] * r[i];

                    for (int j = 0; j < k; j++)
                        A[g][j] += J[g] * J[j];
                }
            }


            for (int q = k; q < 10; q++)
                A[q][q] = 1.0;
            sum_r_2 = 0.0;

            for (int i = 0; i < data_count; i++)
                sum_r_2 += r[i] * r[i];

            printf("%d: sum_r_2 = %.15le\n", iteration, sum_r_2);


            if (!solve_10x10(A, b, delta)) {
                printf("You shall abandon the lie. Your time in that way was a bad investment on my part.\n");
                return 1;
            }
            for (int i = 0; i < p.not_today_count; i++) {

                switch (p.not_today[i]) {

                    case 0:
                        c += alpha * delta[i];
                        printf("%d: c = %.15le\n", iteration, c);
                        break;

                    case 1:
                        gNa += alpha * delta[i];
                        printf("%d: gNa = %.15le\n", iteration, gNa);
                        break;

                    case 2:
                        gK += alpha * delta[i];
                        printf("%d: gK = %.15le\n", iteration, gK);
                        break;

                    case 3:
                        gL += alpha * delta[i];
                        printf("%d: gL = %.15le\n", iteration, gL);
                        break;

                    case 4:
                        VNa += alpha * delta[i];
                        printf("%d: VNa = %.15le\n", iteration, VNa);
                        break;

                    case 5:
                        VK += alpha * delta[i];
                        printf("%d: VK = %.15le\n", iteration, VK);
                        break;

                    case 6:
                        VL += alpha * delta[i];
                        printf("%d: VL = %.15le\n", iteration, VL);
                        break;

                    case 7:
                        sn += alpha * delta[i];
                        printf("%d: sn = %.15le\n", iteration, sn);
                        break;

                    case 8:
                        sm += alpha * delta[i];
                        printf("%d: sm = %.15le\n", iteration, sm);
                        break;

                    case 9:
                        sh += alpha * delta[i];
                        printf("%d: sh = %.15le\n", iteration, sh);
                        break;
                }
            }


        }

        t_end = 880.0;
        x[0] = 0.0;
        x[1] = 0.042;
        x[2] = 0.608;
        x[3] = 0.6;
        p.ladder = 0;

        t = -1.0;
        c   = 5.050330502654351e+01;

        p.ladder = 0;
        while (t <= t_end) {
            if (t >= 400.0)
                printf("%.15le %.15le %.15le %.15le %.15le\n",
                   t, -c - x[0], x[1], x[2], x[3]);
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
