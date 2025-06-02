/**
 * @file array_operations.cpp
 * @brief Программа для работы с одномерным массивом целых чисел.
 *
 * Программа позволяет:
 * - Заполнять массив вручную или случайными числами в интервале [-1000; 1000].
 * - Выполнять три задания:
 *   1. Находить сумму отрицательных элементов, кратных 10.
 *   2. Заменять первые k элементов массива на те же элементы в обратном порядке.
 *   3. Проверять наличие пары соседних элементов с заданным произведением.
 * - Выводить результаты на экран.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Объявления функций

/**
 * @brief Получает целое число от пользователя.
 * @return Введенное пользователем целое число.
 * @note В случае ошибки ввода программа завершается.
 */
int getValue();

/**
 * @brief Получает размер массива от пользователя.
 * @return Размер массива.
 * @note Проверяет корректность введенного размера (должен быть положительным).
 */
size_t getSize();

/**
 * @brief Проверяет корректность размера массива.
 * @param n Размер массива.
 * @note Если размер не положительный, программа завершается.
 */
void checkN(const int n);

/**
 * @brief Заполняет массив числами.
 * @param arr Указатель на массив.
 * @param n Размер массива.
 * @param randomFill Флаг: true - случайное заполнение, false - ручной ввод.
 */
void fillArray(int* arr, const int n, bool randomFill);

/**
 * @brief Выводит массив на экран.
 * @param arr Указатель на массив.
 * @param n Размер массива.
 */
void printArray(int* arr, const int n);

/**
 * @brief Вычисляет сумму отрицательных элементов, кратных 10.
 * @param arr Указатель на массив.
 * @param n Размер массива.
 * @return Сумма подходящих элементов.
 */
int sumNegativeMultiplesOf10(int* arr, const int n);

/**
 * @brief Заменяет первые k элементов массива на те же элементы в обратном порядке.
 * @param arr Указатель на массив.
 * @param n Размер массива.
 * @param k Количество элементов для замены.
 * @note Если k некорректно, выводится сообщение об ошибке.
 */
void reverseFirstK(int* arr, const int n, int k);

/**
 * @brief Проверяет наличие пары соседних элементов с заданным произведением.
 * @param arr Указатель на массив.
 * @param n Размер массива.
 * @param targetProduct Заданное произведение.
 * @return true, если такая пара найдена, иначе false.
 */
bool hasPairWithProduct(int* arr, const int n, int targetProduct);

int main() {
    srand(time(0)); // Инициализация генератора случайных чисел
    
    // Получаем размер массива от пользователя
    size_t n = getSize();
    int* arr = new int[n];
    
    // Выбор способа заполнения массива
    cout << "Заполнить массив случайными числами? (1 - да, 0 - нет): ";
    bool randomFill = getValue();
    fillArray(arr, n, randomFill);
    
    cout << "Исходный массив: ";
    printArray(arr, n);
    
    // Задание 1: Сумма отрицательных элементов, кратных 10
    int sum = sumNegativeMultiplesOf10(arr, n);
    cout << "Сумма отрицательных элементов, кратных 10: " << sum << endl;
    
    // Задание 2: Замена первых k элементов на те же элементы в обратном порядке
    cout << "Введите k для замены первых элементов: ";
    int k = getValue();
    int* copy1 = new int[n];
    for (size_t i = 0; i < n; i++) {
        copy1[i] = arr[i];
    }
    reverseFirstK(copy1, n, k);
    cout << "После замены первых " << k << " элементов: ";
    printArray(copy1, n);
    delete[] copy1;
    
    // Задание 3: Проверка наличия пары соседних элементов с заданным произведением
    cout << "Введите целевое произведение для проверки: ";
    int targetProduct = getValue();
    if (hasPairWithProduct(arr, n, targetProduct)) {
        cout << "Есть пара соседних элементов с произведением " << targetProduct << endl;
    } else {
        cout << "Нет пар соседних элементов с произведением " << targetProduct << endl;
    }
    
    delete[] arr;
    return 0;
}

int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Ошибка ввода" << endl;
        abort();
    }
    return value;
}

size_t getSize() {
    cout << "Введите размер массива n: ";
    int n = getValue();
    checkN(n);
    return static_cast<size_t>(n);
}

void checkN(const int n) {
    if (n <= 0) {
        cout << "Ошибка: размер массива должен быть положительным" << endl;
        abort();
    }
}

void fillArray(int* arr, const int n, bool randomFill) {
    if (randomFill) {
        for (size_t i = 0; i < n; i++) {
            arr[i] = rand() % 2001 - 1000; // Генерация чисел в интервале [-1000; 1000]
        }
    } else {
        for (size_t i = 0; i < n; i++) {
            cout << "Введите arr[" << i + 1 << "] = ";
            arr[i] = getValue();
        }
    }
}

void printArray(int* arr, const int n) {
    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int sumNegativeMultiplesOf10(int* arr, const int n) {
    int sum = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] < 0 && arr[i] % 10 == 0) {
            sum += arr[i];
        }
    }
    return sum;
}

void reverseFirstK(int* arr, const int n, int k) {
    if (k <= 0 || k > n) {
        cout << "Некорректное значение k" << endl;
        return;
    }
    
    for (int i = 0; i < k / 2; i++) {
        swap(arr[i], arr[k - 1 - i]);
    }
}

bool hasPairWithProduct(int* arr, const int n, int targetProduct) {
    if (n < 2) return false;
    
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] * arr[i + 1] == targetProduct) {
            return true;
        }
    }
    return false;
}
