#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

/**
 * @brief Создает двумерный массив заданного размера
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданный массив
 */
int** createMatrix(size_t rows, size_t cols) {
    int** matrix = new int*[rows];
    for (size_t i = 0; i < rows; i++) {
        matrix[i] = new int[cols];
    }
    return matrix;
}

/**
 * @brief Освобождает память, занятую матрицей
 * @param matrix Указатель на матрицу
 * @param rows Количество строк в матрице
 */
void freeMatrix(int** matrix, size_t rows) {
    for (size_t i = 0; i < rows; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

/**
 * @brief Выводит матрицу на экран
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void printMatrix(int** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

/**
 * @brief Заполняет матрицу случайными числами
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param min Минимальное значение
 * @param max Максимальное значение
 */
void fillRandom(int** matrix, size_t rows, size_t cols, int min, int max) {
    srand(time(0));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

/**
 * @brief Заполняет матрицу значениями с клавиатуры
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void fillManual(int** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }
}

/**
 * @brief Заменяет максимальный элемент в каждой строке нулем
 * @param matrix Указатель на матрицу
 * @param rows Количество строк
 * @param cols Количество столбцов
 */
void replaceMaxWithZero(int** matrix, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; i++) {
        int maxVal = matrix[i][0];
        size_t maxPos = 0;
        
        // Находим максимальный элемент в строке
        for (size_t j = 1; j < cols; j++) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
                maxPos = j;
            }
        }
        
        // Заменяем его на 0
        matrix[i][maxPos] = 0;
    }
}

/**
 * @brief Вставляет строку из нулей перед строками, где первый элемент делится на 3
 * @param matrix Исходная матрица
 * @param rows Ссылка на количество строк (изменяется при вставке)
 * @param cols Количество столбцов
 * @return Новая матрица с добавленными строками
 */
int** insertZeroRows(int** matrix, size_t& rows, size_t cols) {
    // Считаем сколько строк нужно добавить
    size_t addRows = 0;
    for (size_t i = 0; i < rows; i++) {
        if (matrix[i][0] % 3 == 0) {
            addRows++;
        }
    }

    // Если нечего добавлять, возвращаем копию
    if (addRows == 0) {
        int** newMatrix = createMatrix(rows, cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                newMatrix[i][j] = matrix[i][j];
            }
        }
        return newMatrix;
    }

    // Создаем новую матрицу с дополнительными строками
    size_t newRows = rows + addRows;
    int** newMatrix = createMatrix(newRows, cols);

    size_t newIdx = 0;
    for (size_t i = 0; i < rows; i++) {
        // Если первый элемент делится на 3, добавляем строку нулей
        if (matrix[i][0] % 3 == 0) {
            for (size_t j = 0; j < cols; j++) {
                newMatrix[newIdx][j] = 0;
            }
            newIdx++;
        }

        // Копируем исходную строку
        for (size_t j = 0; j < cols; j++) {
            newMatrix[newIdx][j] = matrix[i][j];
        }
        newIdx++;
    }

    rows = newRows; // Обновляем количество строк
    return newMatrix;
}

int main() {
    size_t rows, cols;
    int choice, min, max;

    // Ввод размеров матрицы
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;

    // Создание матрицы
    int** matrix = createMatrix(rows, cols);

    // Выбор способа заполнения
    cout << "Choose input method:\n1. Random\n2. Manual\n> ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter min value: ";
        cin >> min;
        cout << "Enter max value: ";
        cin >> max;
        fillRandom(matrix, rows, cols, min, max);
    } else {
        fillManual(matrix, rows, cols);
    }

    // Вывод исходной матрицы
    cout << "\nOriginal matrix:\n";
    printMatrix(matrix, rows, cols);

    // Задание 1: Замена максимальных элементов нулями
    replaceMaxWithZero(matrix, rows, cols);
    cout << "\nAfter replacing max elements with zeros:\n";
    printMatrix(matrix, rows, cols);

    // Задание 2: Вставка строк нулей
    int** newMatrix = insertZeroRows(matrix, rows, cols);
    cout << "\nAfter inserting zero rows:\n";
    printMatrix(newMatrix, rows, cols);

    // Освобождение памяти
    freeMatrix(matrix, rows);
    freeMatrix(newMatrix, rows);

    return 0;
}
