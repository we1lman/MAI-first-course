#include <stdio.h>

const int STEPS_LIMIT = 50;

int min(int, int);
int max(int, int);
int sign(int);
int check_the_hit(int, int);
int remaind(int, int);

int main(){
    typedef  struct {
        int i, j, l;
    } Data;

    Data data = {26, 8, -3};
    Data prev = data;

    for (int step = 1; step <= STEPS_LIMIT; ++step){
        if (check_the_hit(data.i, data.j)){
            printf("answer: %d\n", step);
            return 0;
        }

        data.i = remaind(min(prev.i + prev.j, prev.i + prev.l) * step, 30);
        data.j = remaind(prev.j + sign(prev.j) * prev.l, 20) + remaind(step * sign(prev.i), 10);
        data.l = remaind(max(prev.i * prev.j, max(prev.i * prev.l, prev.j * prev.l)), 30);

        printf("|x  = %3d | y  = %3d | l  = %3d |\n", prev.i, prev.j, prev.l);

        prev = data;
    }
    printf("Missed..^((\nx = %d, y = %d, l = %d", data.i, data.j, data.l);
    
    return 0;
}

int min(int a, int b){
    return (a < b) ? a : b;
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int sign(int x) {
    return (x > 0) - (x < 0);
}

int check_the_hit(int x, int y){
    int equation_of_circle = (x - 10) * (x - 10) + (y - 10) * (y - 10);
    return (25 <= equation_of_circle) && (equation_of_circle <= 100);
}

int remaind(int a, int b){
    return a - (a / b) * b;
}
