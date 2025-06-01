КОММЕНТАРИЯМИ
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

/**
 * @brief Считывает целое значение с клавиатуры с проверкой ввода
 * @return Введенное значение
 */
int getValue();

/**
 * @brief Получает и проверяет размер массива
 * @return Размер массива
 */
size_t getSize();

/**
 * @brief Создает двумерный массив (матрицу) размером m x n
 * @param m Количество строк в массиве
 * @param n Количество строк в массиве
 * @return Cозданный двумерный массив
 * */
int** getNewArray(const size_t m, const size_t n);

/**
 * @brief Выводит массив в форматированном виде
 * @param array Массив для вывода
 * @param m Количество строк
 * @param n Количество столбцов
 */
void printArray(int** array, const size_t m, const size_t n);

/**
 * @brief Выводит массив в форматированном виде
 * @param array Массив для вывода
 * @param m Количество строк
 * @param n Количество столбцов
 */
void printArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заполняет массив вручную через консоль
 * @param array Целевой массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
void fillArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заполняет массив случайными числами
 * @param array Целевой массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @param start Нижняя граница значений
 * @param end Верхняя граница значений
 */
void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end);

/**
 * @brief Освобождает память двумерного массива
 * @param array Указатель на массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
void deleteArray(int** array, const size_t m, const size_t n);

/**
 * @brief Создает копию массива
 * @param array Исходный массив для копирования
 * @param m Количество строк
 * @param n Количество столбцов
 * @return Новый массив-копию
 */
int** copyArray(int** array, const size_t m, const size_t n);

/**
 * @brief Заменяет минимальный по модулю элемент каждого столбца нулем
 * @param array Целевой массив
 * @param m Количество строк
 * @param n Количество столбцов
 */
void replaceMinAbsWithZero(int** array, size_t m, size_t n);

/**
 * @brief Удаляет все столбцы, в которых первый элемент больше последнего
 * @param array Исходный массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @param new_n Количество столбцов в новом массиве
 */
int** removeColumnsWhereFirstGreaterThanLast(int** array, size_t m, size_t n, size_t new_n);
/**
 * @brief Расчитывает старый размер массива для удаления столбцов
 * @param array Исходный массив
 * @param m Количество строк
 * @param n Количество столбцов
 * @param new_n Количество столбцов в новом массиве
 */
int GetCount(int** array, size_t m, size_t n);

/**
* @brief Перечисление для выбора способа заполнения данных
* @param MANUALY Выбор ручного заполнения массива
* @param RANDOM Выбор автоматического заполнения массива
*/
enum { RANDOM = 1, MANUAL = 2 };

/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
*/
int main()
{
    cout << "Enter m (rows): ";
    size_t m = getSize();
    cout << "Enter n (columns): ";
    size_t n = getSize();

    int** array = getNewArray(m, n);

    cout << "Enter the way to fill array: " << MANUAL << " to fill manually, " << RANDOM << " to fill randomly: ";
    int choice = getValue();
    int start = 0, end = 0;

    switch (choice)
    {
    case RANDOM:
        cout << "Enter start: ";
        start = getValue();
        cout << "Enter end: ";
        end = getValue();
        fillRandom(array, m, n, start, end);
        break;
    case MANUAL:
        fillArray(array, m, n);
        break;
    default:
        cout << "Error";
        deleteArray(array, m, n);
        return 1;
    }

    cout << "Original array:";
    cout << "";
    printArray(array, m, n);

    int** task1Array = copyArray(array, m, n);

    replaceMinAbsWithZero(task1Array, m, n);
    cout << "After Task 1 (replaced even elements with column's max absolute):";
    cout << " ";
    printArray(task1Array, m, n);
    deleteArray(task1Array, m, n);

    size_t count = GetCount(array, m, n);
    size_t new_n = n - count;
    int** task2Array = removeColumnsWhereFirstGreaterThanLast(array, m, n, new_n);
    cout << "After Task 2 (removed columns with even first element):";
    cout << " ";
    if (task2Array != nullptr && new_n > 0)
    {
        printArray(task2Array, m, new_n);
        deleteArray(task2Array, m, new_n);
    }
    else
    {
        cout << "No columns left.";
    }

    deleteArray(array, m, n);
    return 0;
}
int** getNewArray(const size_t m, const size_t n)
{
    int** array = new int* [m];
    for (size_t i = 0; i < m; i++)
    {
        array[i] = new int[n];
    }
    return array;
}

void deleteArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        delete[] array[i];
    }
    delete[] array;
}

void printArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << setw(6) << array[i][j];
        }
        cout << endl;
    }
}

void fillArray(int** array, const size_t m, const size_t n)
{
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            cout << "Enter array[" << i << "][" << j << "]: ";
            array[i][j] = getValue();
        }
    }
}

void fillRandom(int** array, const size_t m, const size_t n, const int start, const int end)
{
    srand(time(0));
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            array[i][j] = rand() % (end - start + 1) + start;
        }
    }
}

int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cerr << "Invalid input!" << endl;
        abort();
    }
    return value;
}

size_t getSize()
{
    int size = getValue();
    if (size <= 0)
    {
        cerr << "Size must be positive!" << endl;
        abort();
    }
    return static_cast<size_t>(size);
}

int** copyArray(int** array, const size_t m, const size_t n)
{
    int** newArray = getNewArray(m, n);
    for (size_t i = 0; i < m; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            newArray[i][j] = array[i][j];
        }
    }
    return newArray;
}

void replaceMinAbsWithZero(int** array, size_t m, size_t n)
{
    for (size_t j = 0; j < n; j++)
    {

        int min_abs = abs(array[0][j]);
        int min_val = array[0][j];
        size_t min_index = 0;

        for (size_t i = 1; i < m; i++)
        {
            if (abs(array[i][j]) < min_abs)
            {
                min_abs = abs(array[i][j]);
                min_val = array[i][j];
                min_index = i;
            }
        }


        array[min_index][j] = 0;
    }
}

int GetCount(int** array, size_t m, size_t n) {
    size_t count = 0;
    for (size_t j = 0; j < n; j++) {
        if (array[0][j] > array[m - 1][j]) {
            count++;
        }
    }
    return count;
}

int** removeColumnsWhereFirstGreaterThanLast(int** array, size_t m, size_t n, size_t new_n) {
    if (new_n == 0) {
        return nullptr;
    }

    int** newArray = getNewArray(m, new_n);
    size_t new_j = 0;
    for (size_t j = 0; j < n; j++) {
        if (array[0][j] <= array[m - 1][j]) {
            for (size_t i = 0; i < m; i++) {
                newArray[i][new_j] = array[i][j];
            }
            new_j++;
        }
    }
    return newArray;
}
