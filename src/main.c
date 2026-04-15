#include <stdio.h>
#include "struct.h"
#include "methods.h"
#include "model.h"
#include <string.h>
#include <stdlib.h>
#include "great_app_test.h"
#include "rubbish.h"
#include <time.h>


int main(int argc, char *argv[]) {
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

    double h = 1e-1;
    double t = 0.0;
    double t_end = 10.0;
    char method[20] = "mid";
    int use_calculus = 1;

    if (argc > 1)
        strcpy(method, argv[1]);

    if (argc > 2)
        use_calculus = atoi(argv[2]); // 1 = calculus режим


    p.Iext = -10.0;
    double hk = 1e-1;
    double tol = 1e-1;
    double as = 1e-10;
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

    if (use_calculus) {
        Test_slop *r = malloc(sizeof(Test_slop));
        Neural_data *j = malloc(sizeof(Neural_data));

        calculus(r, j, solver, x, h, f, &p, tol, t, t_end, &global, as, hk);

        free(r);
        free(j);
    } else {
        tol = 1e-14;
        double h_long = hk;

        while (t < t_end) {
            double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
            if (elapsed > time_limit) {
                printf("Time is over for data in 0 control unit  test\n");
                break;
            }
            printf("%lf %lf %lf %lf %lf\n",
                   t, x[0], x[1], x[2], x[3]);
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
    return 0;
}
