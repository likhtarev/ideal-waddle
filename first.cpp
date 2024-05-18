#include <iostream>
#include <vector>
#include <random>
#include <thread>

// Функция для генерации случайных чисел от 1 до 10
int getRandomNumber() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 10);
    return dis(gen);
}

// Функция для генерации случайной матрицы размером rows x cols
std::vector<std::vector<int>> generateMatrix(int rows, int cols) {
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = getRandomNumber();
        }
    }
    return matrix;
}

// Функция для перемножения двух матриц однопоточным способом
std::vector<std::vector<int>> multiplyMatricesSingleThread(const std::vector<std::vector<int>>& matrix1,
                                                           const std::vector<std::vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2));

    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < cols2; ++j) {
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return result;
}

// Функция для перемножения двух матриц многопоточным способом
std::vector<std::vector<int>> multiplyMatricesMultiThread(const std::vector<std::vector<int>>& matrix1,
                                                          const std::vector<std::vector<int>>& matrix2) {
    int rows1 = matrix1.size();
    int cols1 = matrix1[0].size();
    int cols2 = matrix2[0].size();

    std::vector<std::vector<int>> result(rows1, std::vector<int>(cols2));

    std::vector<std::thread> threads;

    for (int i = 0; i < rows1; ++i) {
        threads.emplace_back([i, &matrix1, &matrix2, &result, cols1, cols2]() {
            for (int j = 0; j < cols2; ++j) {
                for (int k = 0; k < cols1; ++k) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}

// Функция для вывода матрицы на экран
void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int num : row) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int rows1, cols1, rows2, cols2;
    
    std::cout << "Введите количество строк и столбцов первой матрицы: ";
    std::cin >> rows1 >> cols1;
    
    std::cout << "Введите количество строк и столбцов второй матрицы: ";
    std::cin >> rows2 >> cols2;
    
    if (cols1 != rows2) {
        std::cout << "Умножение матриц невозможно." << std::endl;
        return 0;
    }
    
    // Генерация случайных матриц
    std::vector<std::vector<int>> matrix1 = generateMatrix(rows1, cols1);
    std::vector<std::vector<int>> matrix2 = generateMatrix(rows2, cols2);
    
    // Однопоточное перемножение матриц
    std::cout << "Однопоточное перемножение матриц:" << std::endl;
    std::vector<std::vector<int>> resultSingleThread = multiplyMatricesSingleThread(matrix1, matrix2);
    printMatrix(resultSingleThread);
    
    // Многопоточное перемножение матриц
    std::cout << "Многопоточное перемножение матриц:" << std::endl;
    std::vector<std::vector<int>> resultMultiThread = multiplyMatricesMultiThread(matrix1, matrix2);
    printMatrix(resultMultiThread);
    
    return 0;
}
