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
 * @brief считывает рамер массива
 * @param n -размер массива
 * @return (size_t)n
 */
size_t getSize();

/**
 *@brief проверка введённого размера массива
 *@param n-размер массива
 */
void checkN(const int n);

/**
 *@brief ввод элементов массива с клавиатуры
 * @param array[i]
 */
void fillArray(int* array, const int n);
/**
 *@brief вывод массива в консоль
 * @param array[i]
 */
void printArray(const int* array, const int n);
/**
 * @brief суммирует отрицательные элементы массива
 * @param array[i]<0
 */
int sumOfNegativeElements(const int* array, const int n);
/**
 * @brief сумма элементов значение которых не больше A
 * @param A-число введённое пользователем
 */
int countPositiveLessThanA(const int* array, const int n, const int A);
/**
 *@brief-вычисление номера последней пары соседних элементов с разными знаками
 *@param array[i]
 */
int findLastPair(const int* array, const int n);
/**
 *@brief-функция для заполнения массива случайными числами промежутка
 */
void fillRandom(int* array, const size_t n, const int start, const int end);


/**
 * @brief Точка входа в программу
 * @return возвращает 0, если программа выполнена верно
*/
int main() {
    setlocale(LC_ALL, "Rus");
    enum { RANDOM = 1, MANUAL = 2 };
    cout << "Enter n: ";
    size_t n = getSize();
    // Создаем массив
    int* array = new int[n]; // Выделяем память для массива
    cout << "Enter the way to fill array: " << (int)MANUAL <<
        " to fill manually, " << (int)RANDOM << " to fill randomly: ";
    int choice = getValue();
    int start = 0;
    int end = 0;

    switch (choice) {
    case RANDOM:
        cout << "Enter start: ";
        start = getValue();
        cout << "Enter end: ";
        end = getValue();
        if (start <= end)
        {
            abort();
        }

        fillRandom(array, n, start, end); // Заполняем массив случайными числами
        break;
    case MANUAL:
        fillArray(array, n); // Заполняем массив вручную
        break;
    default:
        cout << "Error" << endl;
        delete[] array; // Освобождаем память перед выходом
        return 1;
    }
    printArray(array, n);
    // 1. Найти сумму отрицательных элементов
    int sumNegatives = sumOfNegativeElements(array, n);
    cout << "Сумма отрицательных элементов: " << sumNegatives << endl;
    // 2. Найти количество положительных элементов, не превосходящих A
    cout << "Введите число A: ";
    int A = getValue();
    int countPositives = countPositiveLessThanA(array, n, A);
    cout << "Количество положительных элементов, не превосходящих " << A << ": " << countPositives << endl;
    // 3. Найти номер последней пары соседних элементов с разными знаками
    int lastPairIndex = findLastPair(array, n);
    if (lastPairIndex != -1) {
        cout << "Номер последней пары соседних элементов с разными знаками: " << lastPairIndex + 1 << endl;
    }
    else {
        cout << "Нет пар соседних элементов с разными знаками." << endl;
    }
}
int getValue()
{
    int value = 0;
    cin >> value;
    if (cin.fail())
    {
        cout << "Error" << endl;
        abort();
    }
    return value;
}

size_t getSize()
{
    std::cout << "Введите размер массива" << endl;
    int n = getValue();
    checkN(n);
    return (size_t)n;
}
void checkN(const int n)
{
    if (n <= 0)
    {
        cout << "Error, некорректное значение" << endl;
        abort();
    }
}
void fillArray(int* array, const int n)
{
    for (size_t i = 0; i < n; i++) {
        cout << "Введите arr[" << i + 1 << "] = ";
        array[i] = getValue();
    }
}
void fillArrayRandom(int* array, const int n, const int start, const int end)
{
    if (start < end) { abort(); }
    for (size_t i = 0; i < n; i++) {
        array[i] = rand() % (end - start + 1); // Генерация случайных чисел в диапазоне [-100; 200]
    }
}
void printArray(const int* array, const int n)
{
    cout << "Массив: ";
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}
int sumOfNegativeElements(const int* array, const int n)
{
    int sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (array[i] < 0)
        {
            sum += array[i];
        }
    }
    return sum;
}
int countPositiveLessThanA(const int* array, const int n, const int A)
{
    int count = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (array[i] > 0 && array[i] <= A)
        {
            count++;
        }
    }
    return count;
}
int findLastPair(const int* array, const int n)
{
    for (int i = n - 2; i >= 0; i--)
    {
        if ((array[i] < 0 && array[i + 1] >= 0) || (array[i] >= 0 && array[i + 1] < 0))
        {
            return i; // Возвращаем индекс первого элемента пары
        }
    }
    return -1; // Если не нашли
}
void fillRandom(int* array, const size_t n, const int start, const int end)
{
    srand(time(0));
    for (size_t i = 0; i < n; i++)
    {

        array[i] = rand() % (end - start + 1) + start;
    }
