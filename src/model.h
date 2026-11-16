#ifndef UNTITLED35_MODEL_H
#define UNTITLED35_MODEL_H




typedef struct {
    double Iext;
    int ladder;
    int not_today_count;
    int not_today[10];
}
Params;


void f(double *x, double *fx, void *context, int *global);


#endif
