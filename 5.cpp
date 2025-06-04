#include <iostream>
#include <cstdlib>
#include <ctime>
#include <locale>
using namespace std;

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return Введенное значение
 */
int getValue();

/**
 * @brief Считывает размер массива
 * @return Размер массива (size_t)
 */
size_t getSize();

/**
 * @brief Проверка введённого размера массива
 * @param n - размер массива
 */
void checkN(const int n);

/**
 * @brief Ввод элементов массива с клавиатуры
 * @param array - массив
 * @param n - размер массива
 */
void fillArray(int* array, const int n);

/**
 * @brief Вывод массива в консоль
 * @param array - массив
 * @param n - размер массива
 */
void printArray(const int* array, const int n);

/**
 * @brief Заполнение массива случайными числами в заданном интервале
 * @param array - массив
 * @param n - размер массива
 * @param start - начало интервала
 * @param end - конец интервала
 */
void fillRandom(int* array, const size_t n, const int start, const int end);

/**
 * @brief Находит сумму отрицательных элементов, кратных 10
 * @param array - массив
 * @param n - размер массива
 * @return Сумма элементов
 */
int sumOfNegativeElementsDivisibleBy10(const int* array, const int n);

/**
 * @brief Заменяет первые k элементов массива на те же элементы в обратном порядке
 * @param array - массив
 * @param n - размер массива
 * @param k - количество элементов для замены
 */
void reverseFirstKElements(int* array, const int n, const int k);

/**
 * @brief Проверяет, есть ли пара соседних элементов с произведением, равным заданному числу
 * @param array - массив
 * @param n - размер массива
 * @param target - заданное число
 * @return true, если такая пара существует, иначе false
 */
bool hasPairWithProduct(const int* array, const int n, const int target);

int main() {
    setlocale(LC_ALL, "Rus");
    enum { RANDOM = 1, MANUAL = 2 };
    cout << "Введите размер массива n: ";
    size_t n = getSize();
    int* array = new int[n];

    cout << "Выберите способ заполнения массива: " << (int)MANUAL << " - вручную, " << (int)RANDOM << " - случайными числами: ";
    int choice = getValue();
    int start = 0;
    int end = 0;

    switch (choice) {
    case RANDOM:
        cout << "Введите начало интервала: ";
        start = getValue();
        cout << "Введите конец интервала: ";
        end = getValue();
        if (start > end) {
            cout << "Ошибка: начало интервала должно быть меньше или равно концу." << endl;
            delete[] array;
            return 1;
        }
        fillRandom(array, n, start, end);
        break;
    case MANUAL:
        fillArray(array, n);
        break;
    default:
        cout << "Ошибка: неверный выбор." << endl;
        delete[] array;
        return 1;
    }

    printArray(array, n);

    // 1. Найти сумму отрицательных элементов, кратных 10
    int sumNegatives = sumOfNegativeElementsDivisibleBy10(array, n);
    cout << "Сумма отрицательных элементов, кратных 10: " << sumNegatives << endl;

    // 2. Заменить первые k элементов массива на те же элементы в обратном порядке
    cout << "Введите количество элементов k для замены: ";
    int k = getValue();
    if (k > 0 && k <= n) {
        reverseFirstKElements(array, n, k);
        cout << "Массив после замены первых " << k << " элементов: ";
        printArray(array, n);
    } else {
        cout << "Ошибка: неверное значение k." << endl;
    }

    // 3. Проверить, есть ли пара соседних элементов с произведением, равным заданному числу
    cout << "Введите заданное число для проверки произведения: ";
    int target = getValue();
    if (hasPairWithProduct(array, n, target)) {
        cout << "Найдена пара соседних элементов с произведением " << target << "." << endl;
    } else {
        cout << "Пара соседних элементов с произведением " << target << " не найдена." << endl;
    }

    delete[] array;
    return 0;
}

int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Ошибка ввода." << endl;
        abort();
    }
    return value;
}

size_t getSize() {
    int n = getValue();
    checkN(n);
    return (size_t)n;
}

void checkN(const int n) {
    if (n <= 0) {
        cout << "Ошибка: размер массива должен быть положительным." << endl;
        abort();
    }
}

void fillArray(int* array, const int n) {
    for (size_t i = 0; i < n; i++) {
        cout << "Введите элемент массива [" << i + 1 << "]: ";
        array[i] = getValue();
    }
}

void printArray(const int* array, const int n) {
    cout << "Массив: ";
    for (size_t i = 0; i < n; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

void fillRandom(int* array, const size_t n, const int start, const int end) {
    srand(time(0));
    for (size_t i = 0; i < n; i++) {
        array[i] = rand() % (end - start + 1) + start;
    }
}

int sumOfNegativeElementsDivisibleBy10(const int* array, const int n) {
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        if (array[i] < 0 && array[i] % 10 == 0) {
            sum += array[i];
        }
    }
    return sum;
}

void reverseFirstKElements(int* array, const int n, const int k) {
    for (int i = 0; i < k / 2; i++) {
        swap(array[i], array[k - 1 - i]);
    }
}

bool hasPairWithProduct(const int* array, const int n, const int target) {
    for (size_t i = 0; i < n - 1; i++) {
        if (array[i] * array[i + 1] == target) {
            return true;
        }
    }
    return false;
} // Добавлена закрывающая скобка для функции hasPairWithProduct
