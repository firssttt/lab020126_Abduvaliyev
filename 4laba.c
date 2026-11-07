#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, i, j;

    // 1. Ввод размеров
    printf("Введите N и M: ");
    scanf("%d %d", &n, &m);

    // Ввод матрицы (выделение памяти и ввод в одном цикле)
    int **a = malloc(n * sizeof(int*));
    printf("Введите элементы матрицы:\n");
    for (i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
        for (j = 0; j < m; j++) scanf("%d", &a[i][j]);
    }

    // 2. Поиск минимумов по строкам и произведение P
    int *min = malloc(n * sizeof(int));
    long long P = 1;
    for (i = 0; i < n; i++) {
        min[i] = a[i][0];
        for (j = 1; j < m; j++)
            if (a[i][j] < min[i]) min[i] = a[i][j];
        P *= min[i];
    }
    printf("P = %lld\n", P); // Важный вывод: произведение

    // 3. Замена минимума на P в каждой строке
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (a[i][j] == min[i]) { 
                a[i][j] = P; 
                break; // заменили первый минимум и вышли
            }
        }
    }

    // 4. Вывод результата
    printf("Измененная матрица:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) printf("%d ", a[i][j]);
        printf("\n");
    }

    // 5. Очистка памяти (обязательно по заданию)
    for (i = 0; i < n; i++) free(a[i]);
    free(a); 
    free(min);

    return 0;
}