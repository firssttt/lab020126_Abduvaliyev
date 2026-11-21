/* Лабораторная работа №4. Сортировки.
 * Сборка: gcc -O2 -Wall -o lab4 main.c
 * Запуск: ./lab4
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Пузырёк: O(n^2), in-place, каждый проход "всплывает" максимум в конец. */
void bubbleSort(int *a, int n, long long *swaps)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                (*swaps)++;
            }
        }
    }
}

/* Вставками: O(n^2), in-place, сдвигаем влево, пока больше key. */
void insertionSort(int *a, int n, long long *swaps)
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
            (*swaps)++;
        }
        a[j + 1] = key;
    }
}

/* Слияние двух отсортированных половин [left..mid] и [mid+1..right].
 * Перестановок тут нет по сути — считаем записи в буфер как swaps.
 */
static void merge(int *a, int *buf, int left, int mid, int right,
                  long long *swaps)
{
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j]) {
            buf[k++] = a[i++];
        } else {
            buf[k++] = a[j++];
        }
        (*swaps)++;
    }
    while (i <= mid) { buf[k++] = a[i++]; (*swaps)++; }
    while (j <= right) { buf[k++] = a[j++]; (*swaps)++; }

    for (i = left; i <= right; i++) {
        a[i] = buf[i];
    }
}

/* Рекурсивное деление пополам. */
static void mergeSortRec(int *a, int *buf, int left, int right,
                         long long *swaps)
{
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSortRec(a, buf, left, mid, swaps);
    mergeSortRec(a, buf, mid + 1, right, swaps);
    merge(a, buf, left, mid, right, swaps);
}

/* Слиянием: O(n log n), не in-place — нужен буфер O(n). */
void mergeSort(int *a, int n, long long *swaps)
{
    if (n < 2) return;
    int *buf = (int *)malloc(n * sizeof(int));
    if (buf == NULL) {
        printf("Не хватило памяти под буфер\n");
        exit(1);
    }
    mergeSortRec(a, buf, 0, n - 1, swaps);
    free(buf);
}

/* Одинаковая сигнатура у всех сортировок — можно передавать как указатель. */
typedef void (*SortFunc)(int *, int, long long *);

/* Запуск одной сортировки на копии base и печать строки таблицы.
 * swaps передаётся адресом, чтобы функция могла его менять.
 */
void runSort(const char *name, SortFunc sort, int *base, int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] = base[i];
    }

    long long swaps = 0;
    clock_t start = clock();
    sort(arr, n, &swaps);
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%-22s | %7d | %12.6f | %14lld\n",
           name, n, seconds, swaps);
}

int main(void)
{
    int sizes[] = {10, 1000, 10000, 100000};
    int sizesCount = (int)(sizeof(sizes) / sizeof(sizes[0]));

    srand((unsigned)time(NULL));

    printf("+----------------------+---------+--------------+----------------+\n");
    printf("| Сортировка           | Размер  | Время (сек)  | Перестановки   |\n");
    printf("+----------------------+---------+--------------+----------------+\n");

    for (int s = 0; s < sizesCount; s++) {
        int n = sizes[s];

        /* base — исходные случайные данные, arr — рабочая копия для каждого алгоритма. */
        int *base = (int *)malloc(n * sizeof(int));
        int *arr  = (int *)malloc(n * sizeof(int));
        if (base == NULL || arr == NULL) {
            printf("Не удалось выделить память под массив размера %d\n", n);
            return 1;
        }

        for (int i = 0; i < n; i++) {
            base[i] = rand() % 100000;
        }

        runSort("Пузырьком", bubbleSort,    base, arr, n);
        runSort("Вставками", insertionSort, base, arr, n);
        runSort("Слиянием",  mergeSort,     base, arr, n);

        printf("+----------------------+---------+--------------+----------------+\n");

        free(base);
        free(arr);
    }

    printf("\n* Перестановки для сортировки слиянием — это количество\n");
    printf("  записей элементов в буферный массив при слиянии.\n");

    return 0;
}