#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/**
 * @brief Считывает значения с клавиатуры с проверкой ввода
 * @return возвращает значение, если оно правильное, иначе завершает программу
 */
double getValue();

/**
 * @brief Функция для вычисления значения функции y = 3x - 4 * ln(x) - 5
 * @param x - аргумент функции
 * @return значение функции
 */
double calculateFunction(const double x);

/**
 * @brief Функция для проверки, что шаг положительный
 * @return шаг
 */
double getPositiveStep();

/**
 * @brief Точка входа в программу
 * @return 0
 */
int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Введите начальное значение x: ";
    double startX = getValue();

    cout << "Введите конечное значение x: ";
    double endX = getValue();

    if (startX > endX)
    {
        cout << "Ошибка: начальное значение x должно быть меньше, чем конечное" << endl;
        return 1;
    }

    double step = getPositiveStep();

    cout << "x | y" << endl;
    cout << "--------" << endl;

    for (double x = startX; x <= endX; x += step)
    {
        // Проверка на допустимость значения x для логарифма
        if (x <= 0)
        {
            cout << "Ошибка: логарифм не определен для x = " << x << endl;
            continue;
        }

        double y = calculateFunction(x);
        cout << x << " | " << y << endl;
    }

    return 0;
}

double getValue()
{
    double value;
    cin >> value;
    if (cin.fail())
    {
        cout << "Некорректное значение" << endl;
        abort();
    }
    return value;
}

double calculateFunction(const double x)
{
    return 3 * x - 4 * log(x) - 5; 
}

double getPositiveStep()
{
    double step;
    do {
        cout << "Введите шаг: ";
        step = getValue();
        if (step <= 0)
        {
            cout << "Ошибка. Шаг должен быть положительным. Повторите ввод." << endl;
        }
    } while (step <= 0);
    return step;
}
