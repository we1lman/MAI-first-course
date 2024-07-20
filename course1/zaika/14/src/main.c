#include <stdio.h>

/*
данные на вход:
4
1 3 6 10
2 5 9 13
4 8 12 15
7 11 14 16
*/

int main(){
    int n, matrix[7][7] = {0};
    scanf("%d", &n);

    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("\nanswer: ");
    for (int i = 0; i < n; ++i){
        int current_i = i;

        for (int j = 0; j < n; ++j){
            if (current_i >= 0)
                printf("%d ", matrix[current_i--][j]);
            else
                break;
        }
    }

    for (int j = 1; j < n; ++j){
        int current_j = j;

        for (int i = n - 1; i > 0; --i){
            if (current_j < n)
                printf("%d ", matrix[i][current_j++]);
            else
                break;
        }
    }

    return 0;
}