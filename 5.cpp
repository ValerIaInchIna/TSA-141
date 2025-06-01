#include <iostream>
#include <cstdlib>
#include <ctime>
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
 * @brief Проверяет корректность размера массива
 * @param n Проверяемое значение размера
 * @return Завершает программу при n <= 0
 */
void checkN(const int n);

/**
 * @brief Заполняет массив значениями
 * @param arr Указатель на массив
 * @param n Размер массива
 * 
 */
void fillArray(int* arr, size_t);

/**
 * @brief Находит максимальный отрицательный элемент массива
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Максимальное отрицательное значение или -11 если таких элементов нет
 */
void printArray(int* arr, size_t);

/**
 * @brief Заменяет второй элемент массива на максимальный отрицательный
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Выводит предупреждение если массив слишком мал или нет отрицательных элементов
 */
int findMaxNegative(int* arr, size_t);

/**
 * @brief Заменяет второй элемент массива на максимальный отрицательный
 * @param arr Указатель на массив
 * @param n Размер массива
 * @return Выводит предупреждение если массив слишком мал или нет отрицательных элементов
 */
void replaceSecondWithFirstNegative(int* arr, size_t);

/**
 * @brief Считает количество положительных элементов, не превышающих A
 * @param arr Указатель на массив
 * @param n Размер массива
 * @param A Верхняя граница значений
 * @return Количество элементов удовлетворяющих условию
 */
int countPositiveLessThanA(int* arr, size_t n, int A);

/**
 * @brief Ищет первую пару соседних элементов с суммой меньше заданного числа
 * @param arr Указатель на массив
 * @param n Размер массива
 * @param number Целевая сумма для сравнения
 * @return Индекс первого элемента пары или -1 если пара не найдена
 */
int findFirstPairSumLessThan(int* arr, size_t n, int number);

/**
* @brief Перечисление для выбора способа заполнения данных
* @param MANUALY Выбор ручного заполнения массива
* @param RANDOM Выбор автоматического заполнения массива
*/
enum {MANUALY, RANDOM};

/**
 * @brief Точка входа в программу
 * @return 0 при успешном выполнении
 */
int main() 
{
    size_t n = getSize();
    int* arr = new int[n];
    fillArray(arr, n);
    cout << "Original array: ";
    printArray(arr, n);

    replaceSecondWithFirstNegative(arr, n);
    cout << "Array after replacing second element with max negative: ";
    printArray(arr, n);

    cout << "Enter A for task 2: ";
    int A = getValue();
    int count = countPositiveLessThanA(arr, n, A);
    cout << "Number of positive elements <= A: " << count << endl;

    cout << "Enter number for task 3: ";
    int num = getValue();
    int pairIndex = findFirstPairSumLessThan(arr, n, num);
    if (pairIndex == -1) 
    {
        cout << "No such pair found." << endl;
    } else 
    {
        cout << "First pair index: " << pairIndex << endl;
    }

    delete[] arr;
    return 0;
}

int getValue() 
{
    int value =0;
    cin >> value;
    if (cin.fail()) 
    {
        cout << "Invalid input. Aborting." << endl;
        abort();
    }
    return value;
}

size_t getSize() 
{
    cout << "Enter n: ";
    int n = getValue();
    checkN(n);
    return size_t(n);
}

void checkN(const int n) 
{
    if (n <= 0) 
    {
        cout << "Invalid size. Aborting." << endl;
        abort();
    }
}

void fillArray(int* arr, const size_t n) 
{
    cout << "Choose input method ("<<RANDOM<<" - random, "<<MANUALY<<" - manual): ";
    int choice = getValue();
    switch (choice) 
    {
        case RANDOM: 
        {
            srand(time(0));
            for (size_t i = 0; i < n; i++) 
            {
                int min = -10;
                int max = 10;
                arr[i] = min + rand() % (max - min + 1);
            }
            break;
        }
        case MANUALY: 
        {
            for (size_t i = 0; i < n; i++) 
            {
                while (true) 
                {
                    cout << "Enter arr[" << i + 1 << "] (-10 to 10): ";
                    int value = getValue();
                    
                    if (value >= -10 && value <= 10) 
                    {
                        arr[i] = value;
                        break;
                    }
                    cout << "Error! Value must be between -10 and 10. Try again.";
                }
            }
            break;
        }
        default:
            cout << "Invalid choice. Aborting." << endl;
            abort();
    }
}

void printArray(int* arr, const size_t n) 
{
    for (size_t i = 0; i < n; i++) 
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int findMaxNegative(int* arr, const size_t n) 
{
    int maxNeg = -11;
    for (size_t i = 0; i < n; i++) 
    {
        if (arr[i] < 0 && arr[i] > maxNeg) 
        {
            maxNeg = arr[i];
        }
    }
    return maxNeg;
}

void replaceSecondWithFirstNegative(int* arr, const size_t n) 
{
    if (n < 2) 
    {
        cout << "The array is too small to replace the second element." << endl;
        return;
    }
    
    int firstNeg = -11;
    for (size_t i = 0; i < n; i++) 
    {
        if (arr[i] < 0) 
        {
            firstNeg = arr[i];
            break;
        }
    }
    
    if (firstNeg == -11) 
    {
        cout << "There are no negative elements. The second element has not been changed." << endl;
    } 
    else 
    {
        arr[1] = firstNeg; 
    }
}
int countPositiveLessThanA(int* arr, size_t n, int A) 
{
    int count = 0;
    for (size_t i = 0; i < n; i++) 
    {
        if (arr[i] > 0 && arr[i] <= A)
         {
            count++;
        }
    }
    return count;
}

int findFirstPairSumLessThan(int* arr, size_t n, int number) 
{
    for (size_t i = 0; i < n - 1; i++) 
    {
        if (arr[i] + arr[i + 1] < number) 
        {
            return i;
        }
    }
    return -1;
}
