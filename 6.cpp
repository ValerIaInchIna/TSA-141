#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <clocale>

/**
 * @brief Создает двумерный массив заданного размера
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданный массив
 */
int** createMatrix(const size_t rows, const size_t cols);

/**
 * @brief Освобождает память, занятую матрицей
 * @param matrix Указатель на матрицу
 * @param rows Количество строк в матрице
 */
void freeMatrix(int** matrix, const size_t rows);

/**
 * @brief Выводит матрицу на экран
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void printMatrix(int** matrix, const size_t rows, const size_t cols);

/**
 * @brief Заполняет матрицу случайными числами
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param min Минимальное значение
 * @param max Максимальное значение
 */
void fillRandom(int** matrix, const size_t rows, const size_t cols, const int min, const int max);

/**
 * @brief Заполняет матрицу значениями с клавиатуры
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fillManual(int** matrix, const size_t rows, const size_t cols);

/**
 * @brief Создает копию матрицы
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на копию матрицы
 */
int** copyMatrix(int** matrix, const size_t rows, const size_t cols);

/**
 * @brief Заменяет максимальный элемент в каждой строке нулем
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void replaceMaxWithZero(int** matrix, size_t rows, size_t cols);

/**
 * @brief Подсчитывает количество строк, где первый элемент делится на 3
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Количество строк для вставки
 */
size_t countRowsToInsert(int** matrix, size_t rows, size_t cols);

/**
 * @brief Вставляет строку из нулей перед строками, где первый элемент делится на 3
 * @param matrix Исходная матрица
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param addRows Количество строк для вставки
 * @return Новая матрица с добавленными строками
 */
int** insertZeroRows(int** matrix, size_t rows, size_t cols, size_t addRows);

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return Введенное целое число
 */
int getValue();

/**
 * @brief Проверяет, что число положительное
 * @param n Число для проверки
 */
void checkPositive(const int n);

/**
 * @brief Получает размер (положительное число) с клавиатуры
 * @return Введенное положительное число
 */
size_t getSize();

using namespace std;

enum {RANDOM = 1, MANUAL = 2};

int main() {
    setlocale(LC_ALL, "Rus");
    
    cout << "Введите количество строк: ";
    size_t rows = getSize();
    cout << "Введите количество столбцов: ";
    size_t cols = getSize();

    int** matrix = createMatrix(rows, cols);

    cout << "Выберите способ заполнения:\n1. Случайными числами\n2. Вручную\n> ";
    int choice = getValue();
    int min = 0, max = 0;

    switch (choice) {
        case RANDOM:    cout << "Введите минимальное значение: ";
                        min = getValue();
                        cout << "Введите максимальное значение: ";
                        max = getValue();
                        fillRandom(matrix, rows, cols, min, max);
                        break;
        case MANUAL:    fillManual(matrix, rows, cols);
                        break;
        default:        cout << "Ошибка" << endl;
                        freeMatrix(matrix, rows);
                        return 1;
                        break;
    }

    cout << "\nИсходная матрица:\n";
    printMatrix(matrix, rows, cols);

    int** matrixCopy = copyMatrix(matrix, rows, cols);

    replaceMaxWithZero(matrixCopy, rows, cols);
    cout << "\nПосле замены максимальных элементов на нули:\n";
    printMatrix(matrixCopy, rows, cols);

    size_t addRows = countRowsToInsert(matrixCopy, rows, cols);
    if (addRows > 0) {
        int** newMatrix = insertZeroRows(matrixCopy, rows, cols, addRows);
        cout << "\nПосле добавления строк из нулей:\n";
        printMatrix(newMatrix, rows + addRows, cols);
        freeMatrix(newMatrix, rows + addRows);
    } else {
        cout << "\nНет строк для добавления\n";
    }

    freeMatrix(matrix, rows);
    freeMatrix(matrixCopy, rows);

    return 0;
}

int** createMatrix(const size_t rows, const size_t cols) {
    int** matrix = new int*[rows];
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

void freeMatrix(int** matrix, const size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void printMatrix(int** matrix, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

void fillRandom(int** matrix, const size_t rows, const size_t cols, const int min, const int max) {
    srand(time(0));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

void fillManual(int** matrix, const size_t rows, const size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << "matrix[" << i << "][" << j << "] = ";
            matrix[i][j] = getValue();
        }
    }
}

int** copyMatrix(int** matrix, const size_t rows, const size_t cols) {
    int** newMatrix = createMatrix(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }
    return newMatrix;
}

void replaceMaxWithZero(int** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        int maxVal = matrix[i][0];
        size_t maxPos = 0;
        
        for (size_t j = 1; j < cols; j++) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxPos = j;
            }
        }
        
        matrix[i][maxPos] = 0;
    }
}

size_t countRowsToInsert(int** matrix, size_t rows, size_t cols) {
    size_t addRows = 0;
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i][0] % 3 == 0) {
            addRows++;
        }
    }
    return addRows;
}

int** insertZeroRows(int** matrix, size_t rows, size_t cols, size_t addRows) {
    size_t newRows = rows + addRows;
    int** newMatrix = createMatrix(newRows, cols);

    size_t newIdx = 0;
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i][0] % 3 == 0) {
            for (size_t j = 0; j < cols; j++) {
                newMatrix[newIdx][j] = 0;
            }
            newIdx++;
        }

        for (size_t j = 0; j < cols; j++) {
            newMatrix[newIdx][j] = matrix[i][j];
        }
        newIdx++;
    }

    return newMatrix;
}

int getValue() {
    int value = 0;
    cin >> value;
    if (cin.fail()) {
        cout << "Ошибка" << endl;
        abort();
    }
    return value;
}

void checkPositive(const int n) {
    if (n <= 0) {
        cout << "Ошибка" << endl;
        abort();
    }
}

size_t getSize() {
    int n = getValue();
    checkPositive(n);
    return (size_t)n;
}
