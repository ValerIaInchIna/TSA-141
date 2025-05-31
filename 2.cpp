#include <iostream>
#include <cmath>
#include <limits> // Для numeric_limits
using namespace std;

/**
 * @brief Получает числовое значение от пользователя с проверкой ввода
 * @return Корректно введенное пользователем число типа double
 * @note При некорректном вводе запрашивает повторный ввод
 */
double getValue()
{
    double value = 0;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Пожалуйста, введите число: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

/**
 * @brief Проверяет, что значение больше нуля
 * @param value Проверяемое значение
 * @note Выводит предупреждение, если значение <= 0
 */
void checkValue(const double value)
{
    if (value <= 0)
    {
        cout << "Внимание: значение должно быть больше нуля." << endl;
    }
}

/**
 * @brief Вычисляет расстояние между двумя точками на плоскости
 * @param x1 Координата x первой точки
 * @param y1 Координата y первой точки
 * @param x2 Координата x второй точки
 * @param y2 Координата y второй точки
 * @return Расстояние между точками
 * @note Использует формулу расстояния между точками: sqrt((x2-x1)² + (y2-y1)²)
 */
double calculateDistance(const double x1, const double y1, const double x2, const double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/**
 * @brief Главная функция программы
 * @details Программа запрашивает координаты двух точек на плоскости,
 *          вычисляет расстояние между ними и выводит результат.
 *          Реализована проверка корректности ввода координат.
 * @return 0 при успешном выполнении программы
 */
int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Программа вычисления расстояния между двумя точками\n";
    cout << "--------------------------------------------------\n";
    
    cout << "Введите координаты первой точки (x1, y1):" << endl;
    double x1 = getValue();
    double y1 = getValue();
    checkValue(x1);
    checkValue(y1);

    cout << "Введите координаты второй точки (x2, y2):" << endl;
    double x2 = getValue();
    double y2 = getValue();
    checkValue(x2);
    checkValue(y2);

    double distance = calculateDistance(x1, y1, x2, y2);
    cout << "--------------------------------------------------\n";
    cout << "Результат: расстояние между точками = " << distance << endl;
    
    return 0;
}
