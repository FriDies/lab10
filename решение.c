#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

double fa(double x);
double fb(double x);

double cos_n(double x, int N);
double cos_eps(double x, double eps);

float area_rhomboid(float height, float width);
void print_rhomboid_shape(int height, int width, char fill);

int main() 
{
    setlocale(LC_CTYPE, "RUS");
    int choice;

    do 
    {
        printf("\n=================================\n");
        printf("1. Задание 1\n");
        printf("2. Задание 2\n");
        printf("3. Домашнее задание\n");
        printf("0. Выход\n");
        printf("Выберите задание: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            double x;
            printf("\nВведите x: ");
            scanf("%lf", &x);

            double y1 = fa(x);
            double y2 = fb(x);
            printf("fa(x)=%.4lf, fb(x)=%.4lf\n", y1, y2);

            int op;
            printf("\nВыберите операцию:\n1 - произведение\n2 - разность квадратов\n3 - удвоенная сумма\n0 - выход\n");
            scanf("%d", &op);
            switch (op) 
            {
            case 1: printf("Произведение: %.4lf\n", y1 * y2); break;
            case 2: printf("Разность квадратов: %.4lf\n", pow(y1, 2) - pow(y2, 2)); break;
            case 3: printf("Удвоенная сумма: %.4lf\n", 2.0 * (y1 + y2)); break;
            case 0: break;
            default: printf("Неверный пункт меню\n");
            }
        }
        else if (choice == 2)
        {
            double x, eps;
            int N;
            printf("\nВведите x: ");
            scanf("%lf", &x);
            printf("Введите количество членов ряда N: ");
            scanf("%d", &N);
            printf("Введите точность eps (например 0.0001): ");
            scanf("%lf", &eps);

            double y_std = cos(x);
            double y_n = cos_n(x, N);
            double y_eps = cos_eps(x, eps);

            printf("\n1) Стандартная функция cos(x) = %.6lf\n", y_std);
            printf("2) Сумма %d членов ряда= %.6lf\n", N, y_n);
            printf("3) С точностью eps= %.6lf\n", y_eps);

            printf("\nТаблица сходимости:\n");
            printf("  N |    cos_N   | отклонение\n");
            printf("-------------------------------\n");
            for (int i = 1; i <= N; i++) {
                double yn = cos_n(x, i);
                printf("%3d | %10.6lf | %+10.4e\n", i, yn, y_std - yn);
            }
        }
        else if (choice == 3) 
        {
            int height, width;
            printf("\n=== Домашнее задание: Ромбоид ===\n");
            printf("Введите высоту ромбоида: ");
            scanf("%d", &height);
            printf("Введите ширину ромбоида: ");
            scanf("%d", &width);

            if (height <= 0 || width <= 0) {
                printf("Ошибка: размеры должны быть положительными!\n");
            }
            else 
            {
                int act;
                printf("\n1 - рассчитать площадь\n2 - вывести определение фигуры\n3 - нарисовать фигуру\n0 - выход\n");
                scanf("%d", &act);
                switch (act) 
                {
                case 1:
                    printf("Площадь ромбоида: %.2f\n", area_rhomboid((float)height, (float)width));
                    break;
                case 2:
                    if (height == width)
                        printf("Это ромбоид, который является квадратом (высота = ширина).\n");
                    else
                        printf("Это классический наклонный ромбоид (параллелограмм).\n");
                    break;
                case 3: 
                {
                    char fill;
                    printf("Введите символ для рисования: ");
                    scanf(" %c", &fill);
                    print_rhomboid_shape(height, width, fill);
                    break;
                }
                case 0: break;
                default: printf("Ошибка меню\n");
                }
            }
        }
    } while (choice != 0);

    return 0;
}

double fa(double x) 
{
    if (x <= 3.0) return pow(x, 2) - 3.0 * x + 9.0;
    else return 1.0 / (pow(x, 3) + 3.0);
}

double fb(double x) 
{
    return x * exp(sin(pow(x, 2)));
}

double cos_n(double x, int N) 
{
    double sum = 1.0;
    double term = 1.0;
    for (int k = 1; k < N; k++) 
    {
        term = -term * x * x / ((2.0 * k - 1.0) * (2.0 * k));
        sum += term;
    }
    return sum;
}

double cos_eps(double x, double eps)
{
    double sum = 1.0;
    double term = 1.0;
    int k = 1;
    while (fabs(term) > eps) 
    {
        term = -term * x * x / ((2.0 * k - 1.0) * (2.0 * k));
        sum += term;
        k++;
    }
    return sum;
}

float area_rhomboid(float height, float width) 
{
    return height * width;
}

void print_rhomboid_shape(int height, int width, char fill)
{
    for (int row = 0; row < height; row++) 
    {
        for (int space = 0; space < row; space++)
        {
            printf(" ");
        }
        for (int col = 0; col < width; col++) {
            printf("%c", fill);
        }
        printf("\n");
    }
}