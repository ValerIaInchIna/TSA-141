#include <iostream>
#include <cmath> // Для sqrt и pow
using namespace std;

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return Введённое значение
 */
double getValue();

/**
 * @brief Проверяет, что значение является числом
 * @return Введённое значение
 */
void checkValue(const double value);

/**
 * @brief Вычисляет расстояние между двумя точками
 * @param x1 - координата x первой точки
 * @param y1 - координата y первой точки
 * @param x2 - координата x второй точки
 * @param y2 - координата y второй точки
 * @return Расстояние между точками
 */
double calculateDistance(const double x1,const  double y1,const  double x2,const double y2);

/**
 * @brief Точка входа в программу
 * @return 0 - если программа выполнена корректно, иначе - 1
 */
int main()
{
    setlocale(LC_ALL, "rus");

    cout << "Введите координаты первой точки (x1, y1):" << endl;
    double x1 = getValue();
    double y1 = getValue();

    cout << "Введите координаты второй точки (x2, y2):" << endl;
    double x2 = getValue();
    double y2 = getValue();

    double distance = calculateDistance(x1, y1, x2, y2);
    cout << "Расстояние между точками: " << distance << endl;

    return 0;
}

double getValue()
{
    double value;
    if (!(cin >> value))
    {
        cout << "Некорректное значение" << endl;
        abort();
    }
    return value;
}

void checkValue(const double value)
{
    if (value <= 0)
    {
        cout << "Значение должно быть больше нуля." << endl;
        abort();
    }
}

double calculateDistance(const double x1,const double y1,const double x2,const double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
