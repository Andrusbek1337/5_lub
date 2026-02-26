#include "Lab5.h"
#include <iostream>

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << val << "\t";
        }
        std::cout << "\n";
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    try {
        // Создание тестовых файлов
        std::cout << "Создание тестовых файлов...\n";
        Lab5::createBinaryFileWithRandomData("task1.bin", 20);
        Lab5::createBinaryFileWithRandomData("task2.bin", 15);
        Lab5::createBinaryFileWithToys("task3.bin", 10);
        Lab5::createTextFileOnePerLine("task4.txt", 15);
        Lab5::createTextFileMultiplePerLine("task5.txt", 10, 5);
        Lab5::createTextFileWithText("task6.txt");

        // Задание 1
        std::cout << "\n=== Задание 1 ===\n";
        int diff = Lab5::task1("task1.bin");
        std::cout << "Разность максимального и минимального: " << diff << "\n";

        // Задание 2
        std::cout << "\n=== Задание 2 ===\n";
        int n = 4;
        auto matrix = Lab5::task2("task2.bin", n);
        std::cout << "Полученная матрица " << n << "x" << n << " (максимальный элемент заменен на 0):\n";
        printMatrix(matrix);

        // Задание 3
        std::cout << "\n=== Задание 3 ===\n";
        int k = 50;
        auto expensiveToys = Lab5::task3("task3.bin", k);
        std::cout << "Самые дорогие игрушки (цена отличается от максимальной не более чем на " << k << "):\n";
        for (const auto& name : expensiveToys) {
            std::cout << " - " << name << "\n";
        }

        // Задание 4
        std::cout << "\n=== Задание 4 ===\n";
        int maxCount = Lab5::task4("task4.txt");
        std::cout << "Количество вхождений максимального элемента: " << maxCount << "\n";

        // Задание 5
        std::cout << "\n=== Задание 5 ===\n";
        int evenCount = Lab5::task5("task5.txt");
        std::cout << "Количество чётных элементов: " << evenCount << "\n";

        // Задание 6
        std::cout << "\n=== Задание 6 ===\n";
        std::string substr = "форма";
        Lab5::task6("task6.txt", "task6_result.txt", substr);
        std::cout << "Строки, содержащие комбинацию \"" << substr << "\", записаны в файл task6_result.txt\n";

        // Вывод содержимого результата задания 6
        std::ifstream resultFile("task6_result.txt");
        std::cout << "Содержимое файла результата:\n";
        std::string line;
        while (std::getline(resultFile, line)) {
            std::cout << "  " << line << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
