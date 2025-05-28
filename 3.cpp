#include <iostream>
#include <cmath>

using namespace std;

// Определение константы PI
const double PI = 3.14159265358979323846;

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return Введённое значение
 */
double getValue();

/**
 * @brief Проверяет, расположены ли три точки на одной прямой
 * @param x1, y1 - координаты точки A
 * @param x2, y2 - координаты точки B
 * @param x3, y3 - координаты точки C
 * @return true, если точки на одной прямой, иначе false
 */
bool areCollinear(double x1, double y1, double x2, double y2, double x3, double y3);

/**
 * @brief Вычисляет угол B в градусах между AB и BC
 * @param x1, y1 - координаты точки A
 * @param x2, y2 - координаты точки B
 * @param x3, y3 - координаты точки C
 * @return Угол B в градусах
 */
double calculateAngleB(double x1, double y1, double x2, double y2, double x3, double y3);

/**
 * @brief Проверяет значение на корректность (больше нуля)
 * @param value - проверяемое значение
 */
void checkValue(double value);

int main() {
    setlocale(LC_ALL, "rus");

    cout << "Введите координаты точки A (x1, y1): " << endl;
    double x1 = getValue();
    double y1 = getValue();

    cout << "Введите координаты точки B (x2, y2): " << endl;
    double x2 = getValue();
    double y2 = getValue();

    cout << "Введите координаты точки C (x3, y3): " << endl;
    double x3 = getValue();
    double y3 = getValue();

    if (areCollinear(x1, y1, x2, y2, x3, y3)) {
        cout << "Точки A, B и C расположены на одной прямой." << endl;
    }
    else {
        double angleB = calculateAngleB(x1, y1, x2, y2, x3, y3);
        cout << "Точки A, B и C не расположены на одной прямой." << endl;
        cout << "Угол B: " << angleB << " градусов." << endl;
    }

    return 0;
}

double getValue() {
    double value;
    cin >> value;
    checkValue(value);
    return value;
}

bool areCollinear(double x1, double y1, double x2, double y2, double x3, double y3) {
    // Проверка на коллинеарность с использованием площади треугольника
    return (y2 - y1) * (x3 - x2) == (y3 - y2) * (x2 - x1);
}

double calculateAngleB(double x1, double y1, double x2, double y2, double x3, double y3) {
    // Вектор AB
    double ABx = x2 - x1;
    double ABy = y2 - y1;

    // Вектор BC
    double BCx = x3 - x2;
    double BCy = y3 - y2;

    // Вычисление угла между векторами AB и BC
    double dotProduct = ABx * BCx + ABy * BCy;
    double magnitudeAB = sqrt(ABx * ABx + ABy * ABy);
    double magnitudeBC = sqrt(BCx * BCx + BCy * BCy);

    // Угол в радианах
    double angleRadian = acos(dotProduct / (magnitudeAB * magnitudeBC));

    // Перевод угла в градусы
    return angleRadian * (180.0 / PI);
}

void checkValue(double value) {
    if (cin.fail() || value <= 0) {
        cout << "Ошибка: введено некорректное значение." << endl;
        cin.clear(); // Сбрасываем состояние потока
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер
        abort();
    }
}
