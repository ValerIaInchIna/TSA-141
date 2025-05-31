#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>
using namespace std;

/**
 * @brief - Функция для вычисления A по заданному уравнению
 * @param x - значение переменной x
 * @param y - значение переменной y
 * @param z - значение переменной z
 * @return - возвращает рассчитанное значение
 */
double getA(const double x, const double y, const double z);

/**
 * @brief - Функция для вычисления B по заданному уравнению
 * @param x - значение переменной x
 * @param y - значение переменной y
 * @param z - значение переменной z
 * @return - возвращает рассчитанное значение
 */
double getB(const double x, const double y, const double z);

/**
 * @brief - Точка входа в программу
 * @return - возвращает 0, если программа выполнена корректно
 */
int main()
{
    const double x = 1.426;
    const double y = -1.22;
    const double z = 3.5;
    
    cout << "a = " << getA(x, y, z) << endl;
    cout << "b = " << getB(x, y, z);
    
    return 0;
}

double getA(const double x, const double y, const double z)
{
    return (2 * cos(x - M_PI / 6)) / (1 / 2 + pow(sin(y), 2));
}

double getB(const double x, const double y, const double z)
{
    return (1 + pow(z, 2) / 3 + pow(z, 2) / 5);
}
