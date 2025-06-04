#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

enum InputMethod {
    RANDOM = 1,
    MANUAL = 2
};

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
 * @brief Вставляет строку из нулей перед строками, где первый элемент делится на 3
 * @param matrix Исходная матрица
 * @param rows Ссылка на количество строк (изменяется при вставке)
 * @param cols Количество столбцов
 * @return Новая матрица с добавленными строками
 */
int** insertZeroRows(int** matrix, size_t& rows, size_t cols);

/**
 * @brief Считывает значение с клавиатуры с проверкой ввода
 * @return Введенное положительное целое число
 */
int getValue() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Invalid input. Enter a positive integer: ";
        } else {
            return value;
        }
    }
}

/** 
 * @brief Точка входа в программу 
 */
int main() {
    size_t rows, cols;
    int choice, min, max;


    cout << "Enter number of rows: ";
    rows = getValue();
    cout << "Enter number of columns: ";
    cols = getValue();

    int** matrix = createMatrix(rows, cols);

    cout << "Choose input method:\n1. Random\n2. Manual\n> ";
    choice = getValue();

    if (choice == RANDOM) {
        do {
            cout << "Enter min value: ";
            min = getValue();
            cout << "Enter max value: ";
            max = getValue();
            if (min >= max) {
                cout << "Error: min must be less than max. Try again." << endl;
            }
        } while (min >= max);
        fillRandom(matrix, rows, cols, min, max);
    } else {
        fillManual(matrix, rows, cols);
    }

    cout << "\nOriginal matrix:\n";
    printMatrix(matrix, rows, cols);

    int** matrixCopy = copyMatrix(matrix, rows, cols);

    replaceMaxWithZero(matrixCopy, rows, cols);
    cout << "\nAfter replacing max elements with zeros:\n";
    printMatrix(matrixCopy, rows, cols);

    size_t originalRows = rows;
    int** newMatrix = insertZeroRows(matrixCopy, rows, cols);
    cout << "\nAfter inserting zero rows:\n";
    printMatrix(newMatrix, rows, cols);

    // Освобождение памяти
    freeMatrix(matrix, originalRows);     
    freeMatrix(matrixCopy, originalRows); 
    freeMatrix(newMatrix, rows);          

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

int** insertZeroRows(int** matrix, size_t& rows, size_t cols) {
    size_t addRows = 0;
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i][0] % 3 == 0) {
            addRows++;
        }
    }

    if (addRows == 0) {
        return copyMatrix(matrix, rows, cols);
    }

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

    rows = newRows;
    return newMatrix;
}
