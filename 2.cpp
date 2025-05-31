#include <iostream>
#include <cmath>
#include <limits> // Для numeric_limits
using namespace std;

double getValue();
void checkValue(const double value);
double calculateDistance(const double x1, const double y1, const double x2, const double y2);

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
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректное значение. Пожалуйста, введите число: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

void checkValue(const double value)
{
    if (value <= 0)
    {
        cout << "Значение должно быть больше нуля." << endl;
    }
}

double calculateDistance(const double x1, const double y1, const double x2, const double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
