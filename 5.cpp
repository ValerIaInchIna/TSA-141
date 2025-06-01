#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath> // Для функции abs()
using namespace std;

// Прототипы функций
int getValue();
size_t getSize();
void fillArray(int* arr, size_t n);
void printArray(int* arr, size_t n);
void replaceSecondWithMaxNegative(int* arr, size_t n);
int countPositiveLessOrEqualA(int* arr, size_t n, int A);
int findFirstPairWithSumLessThan(int* arr, size_t n, int number);

enum FillMethod { MANUAL, RANDOM };

int main() {
    // Установка русской локали
    setlocale(LC_ALL, "Russian");
    
    // Получение размера массива
    cout << "Введите размер массива: ";
    size_t n = getSize();
    
    // Создание и заполнение массива
    int* arr = new int[n];
    fillArray(arr, n);
    
    // Вывод исходного массива
    cout << "\nИсходный массив: ";
    printArray(arr, n);
    
    // Задание 1: Замена второго элемента
    replaceSecondWithMaxNegative(arr, n);
    cout << "Массив после замены: ";
    printArray(arr, n);
    
    // Задание 2: Подсчет элементов
    cout << "\nВведите число A для задания 2: ";
    int A = getValue();
    int count = countPositiveLessOrEqualA(arr, n, A);
    cout << "Количество элементов: " << count << endl;
    
    // Задание 3: Поиск пары
    cout << "\nВведите число для задания 3: ";
    int num = getValue();
    int pairIndex = findFirstPairWithSumLessThan(arr, n, num);
    if (pairIndex == -1) {
        cout << "Пара не найдена." << endl;
    } else {
        cout << "Индекс первого элемента пары: " << pairIndex << endl;
    }
    
    // Освобождение памяти
    delete[] arr;
    return 0;
}

// Функция для безопасного ввода числа
int getValue() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Пожалуйста, введите число: ";
    }
    return value;
}

// Функция для получения размера массива
size_t getSize() {
    int n;
    do {
        n = getValue();
        if (n <= 0) {
            cout << "Размер должен быть положительным. Повторите ввод: ";
        }
    } while (n <= 0);
    return static_cast<size_t>(n);
}

// Функция заполнения массива
void fillArray(int* arr, size_t n) {
    cout << "Выберите способ заполнения (0 - вручную, 1 - случайно): ";
    int choice;
    do {
        choice = getValue();
        if (choice != MANUAL && choice != RANDOM) {
            cout << "Неверный выбор. Введите 0 или 1: ";
        }
    } while (choice != MANUAL && choice != RANDOM);

    if (choice == RANDOM) {
        srand(time(0));
        for (size_t i = 0; i < n; i++) {
            arr[i] = -10 + rand() % 21; // [-10, 10]
        }
    } else {
        cout << "Введите " << n << " элементов массива (от -10 до 10):\n";
        for (size_t i = 0; i < n; i++) {
            do {
                cout << "Элемент " << i + 1 << ": ";
                arr[i] = getValue();
                if (arr[i] < -10 || arr[i] > 10) {
                    cout << "Число должно быть от -10 до 10. Повторите ввод.\n";
                }
            } while (arr[i] < -10 || arr[i] > 10);
        }
    }
}

// Функция вывода массива
void printArray(int* arr, size_t n) {
    for (size_t i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Задание 1: Замена второго элемента на максимальный отрицательный
void replaceSecondWithMaxNegative(int* arr, size_t n) {
    if (n < 2) {
        cout << "Массив слишком мал для замены второго элемента." << endl;
        return;
    }

    int maxNeg = -11; // Значение за пределами [-10,10]
    for (size_t i = 0; i < n; i++) {
        if (arr[i] < 0 && arr[i] > maxNeg) {
            maxNeg = arr[i];
        }
    }

    if (maxNeg == -11) {
        cout << "В массиве нет отрицательных элементов." << endl;
    } else {
        arr[1] = maxNeg;
        cout << "Второй элемент заменен на максимальный отрицательный: " << maxNeg << endl;
    }
}

// Задание 2: Подсчет положительных элементов, не превосходящих A по модулю
int countPositiveLessOrEqualA(int* arr, size_t n, int A) {
    int count = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] > 0 && abs(arr[i]) <= A) {
            count++;
        }
    }
    return count;
}

// Задание 3: Поиск первой пары соседних элементов с суммой меньше заданного числа
int findFirstPairWithSumLessThan(int* arr, size_t n, int number) {
    if (n < 2) {
        cout << "Массив слишком мал для поиска пар." << endl;
        return -1;
    }
    for (size_t i = 0; i < n - 1; i++) {
        if (arr[i] + arr[i + 1] < number) {
            return static_cast<int>(i);
        }
    }
    return -1;
}
