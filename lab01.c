#include <stdio.h>
#include <math.h>

int main() {
    double x, y, U;
    double xn = 0, xk = 2, hx = 0.3;
    double yn = 0, yk = 1, hy = 0.4;
    double min_U = 1000000;
    double min_x, min_y;

    printf("Таблица значений функции U:\n");

    for (x = xn; x <= xk; x += hx) {
        for (y = yn; y <= yk; y += hy) {
            U = 4 * cos(cbrt(y)) * sin(x * fabs(pow(y, 3) - 1.4));    // я понял, что cbrt(y) — куб-ий корень, fabs(...) — модуль, pow(y, 3) — возведение в степень
            printf("%6.2lf | %5.2lf | %10.4lf\n", x, y, U);      // %6 .2 <-- сколько знаков оставить после запятой, lf -- вещественное число с плавающей точкой, тот же double

            if (U < min_U) {
                min_U = U;
                min_x = x;
                min_y = y;
            }
        }
    }

    printf("Минимум: U = %.4lf при x = %.2lf, y = %.2lf\n", min_U, min_x, min_y);
    return 0;
}
