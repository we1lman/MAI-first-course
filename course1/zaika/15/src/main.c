#include <stdio.h

const MAX_SIZE = 8;

void input_matrix(int (*)[], int *);
void master_solution(int (*)[], int);
void output_matrix(int (*)[], int);
int index_max(int (*), int);
int index_min(int (*), int);

int main(){
    int n, matrix[MAX_SIZE][MAX_SIZE] = {0};
    input_matrix(matrix, &n);
    
    master_solution(matrix, n);
    
    output_matrix(matrix, n);

    return 0;
}

void input_matrix(int (*ar)[MAX_SIZE], int *size){
    char filename[64];
    scanf("%s", filename);

    FILE *input_file;
    input_file = fopen(filename, "r");

    fscanf(input_file, "%d", size);
    int n = *size; 
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            int elem;
            fscanf(input_file, "%d", &elem);
            *(*(ar + i) + j) = elem;
        }
    }
}

void master_solution(int (*ar)[MAX_SIZE], int size){
    int compositions[MAX_SIZE] = {0};
    for (int i = 0; i < size; ++i){
        int sum_nums_of_line = 1;
        for (int j = 0; j < size; ++j){
            sum_nums_of_line *= *(*(ar + i) + j);
        }
        *(compositions+i) = sum_nums_of_line;
    }
    
    int temp_matrix[MAX_SIZE] = {0};
    int min_ind = index_min(compositions, size);
    int max_ind = index_max(compositions, size);
    
    for (int j = 0; j < size; ++j)
        *(temp_matrix + j) = *(*(ar + max_ind) + j);
    for (int j = 0; j < size; ++j)
        *(*(ar + max_ind) + j) = *(*(ar + min_ind) + j);
    for (int j = 0; j < size; ++j)
        *(*(ar + min_ind) + j) = *(temp_matrix + j);
}

void output_matrix(int (*ar)[MAX_SIZE], int size){
    printf("answer:\n");
    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            printf("%d ", *(*(ar + i) + j));
        }
        printf("\n");
    }
}

int index_max(int *ar, int n){
    int mx = -1e6, mx_ind = 0;
    for (int i = 0; i < n; ++i){
        if (*(ar + i) >= mx){
            mx_ind = i;
            mx = *(ar + i);
        }
    }

    return mx_ind;
}

int index_min(int *ar, int n){
    int mn = 1e6, mn_ind = n - 1;
    for (int i = 0; i < n; ++i){
        if (*(ar + i) <= mn){
            mn_ind = i;
            mn = *(ar + i);
        }
    }

    return mn_ind;
}