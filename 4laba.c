#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i, j;

    printf("Введите N и M: ");
    scanf("%d %d", &n, &m);

    int **a = malloc(n * sizeof(int*));
    printf("Введите элементы матрицы:\n");
    for (i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
        for (j = 0; j < m; j++) scanf("%d", &a[i][j]);
    }

    int *min = malloc(n * sizeof(int));
    long long P = 1;
    for (i = 0; i < n; i++) {
        min[i] = a[i][0];
        for (j = 1; j < m; j++)
            if (a[i][j] < min[i]) min[i] = a[i][j];
        P *= min[i];
    }
    printf("P = %lld\n", P);

    printf("Измененная матрица:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (a[i][j] == min[i]) a[i][j] = P; 
            printf("%d ", a[i][j]);             
        }
        printf("\n");
    }

    for (i = 0; i < n; i++) free(a[i]);
    free(a); 
    free(min);

    return 0;
}
